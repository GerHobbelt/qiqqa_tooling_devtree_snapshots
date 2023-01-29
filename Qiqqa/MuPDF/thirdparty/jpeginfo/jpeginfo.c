 /*******************************************************************
 *
 * JPEGinfo
 * Copyright (c) Timo Kokkonen, 1995-2009.
 *
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "mupdf/fitz.h"

#include <stdio.h>
#if HAVE_GETOPT_H && HAVE_GETOPT_LONG
  #include <getopt.h>
#else
  #include "getopt.h"
#endif
#include <stdlib.h>
#include <string.h>
#if HAVE_STRINGS_H
#include "strings.h"
#endif
#include <setjmp.h>
#include <ctype.h>
#include <jpeglib.h>
#include <jerror.h>

#include "md5.h"
#include "jpeginfo.h"


#define VERSION     "1.6.2beta"
#define BUF_LINES   255

#ifndef HOST_TYPE
#define HOST_TYPE ""
#endif


#define EXIF_JPEG_MARKER   JPEG_APP0+1
#define EXIF_IDENT_STRING  "Exif\000\000"


struct my_error_mgr {
  struct jpeg_error_mgr pub;
  jmp_buf setjmp_buffer;
};
typedef struct my_error_mgr * my_error_ptr;

static struct option long_options[] = {
  {"verbose",0,0,'v'},
  {"delete",0,0,'d'},
  {"mode",1,0,'m'},
  {"file",1,0,'f'},
  {"check",0,0,'c'},
  {"help",0,0,'h'},
  {"quiet",0,0,'q'},
  {"lsstyle",0,0,'l'},
  {"info",0,0,'i'},
  {"md5",0,0,'5'},
  {"version",0,0,'V'},
  {"comments",0,0,'C'},
  {0,0,0,0}
};

static FILE *infile = NULL;
static FILE *listfile = NULL;
static int global_error_counter;
static int global_total_errors;
static int verbose_mode = 0;
static int quiet_mode = 0;
static int delete_mode = 0;
static int check_mode = 0;
static int com_mode = 0;
static int del_mode = 0;
static int opt_index = 0;
static int list_mode = 0;
static int longinfo_mode = 0;
static int input_from_file = 0;
static int md5_mode = 0;
static const char *current = NULL;

/*****************************************************************/


#define JZ_CTX_FROM_CINFO(c) ((fz_context *)((c)->client_data_ref))

static void*
jpi_jpeg_mem_alloc(j_common_ptr cinfo, size_t size)
{
	fz_context* ctx = JZ_CTX_FROM_CINFO(cinfo);
	return fz_malloc_no_throw(ctx, size);
}

static void
jpi_jpeg_mem_free(j_common_ptr cinfo, void* object, size_t size)
{
	fz_context* ctx = JZ_CTX_FROM_CINFO(cinfo);
	fz_free(ctx, object);
}

static long
jpi_jpeg_mem_init(j_common_ptr cinfo)
{
	return 0;			/* just set max_memory_to_use to 0 */
}

static void
jpi_jpeg_mem_term(j_common_ptr cinfo)
{
	cinfo->client_data_ref = NULL;
	cinfo->client_init_callback = NULL;
}

static size_t
jpi_jpeg_mem_available(j_common_ptr cinfo, size_t min_bytes_needed,
	size_t max_bytes_needed,
	size_t already_allocated)
{
	// Here we always say, "we got all you want bud!"
	long ret = max_bytes_needed;

	return ret;
}

static void
jpi_jpeg_open_backing_store(j_common_ptr cinfo,
	backing_store_ptr info,
	long total_bytes_needed)
{
	ERREXIT(cinfo, JERR_NO_BACKING_STORE);
}


static int jpi_jpg_sys_mem_register(j_common_ptr cinfo)
{
	cinfo->sys_mem_if.get_small = jpi_jpeg_mem_alloc;
	cinfo->sys_mem_if.free_small = jpi_jpeg_mem_free;

	cinfo->sys_mem_if.get_large = jpi_jpeg_mem_alloc;
	cinfo->sys_mem_if.free_large = jpi_jpeg_mem_free;

	cinfo->sys_mem_if.mem_available = jpi_jpeg_mem_available;

	cinfo->sys_mem_if.open_backing_store = jpi_jpeg_open_backing_store;

	cinfo->sys_mem_if.mem_init = jpi_jpeg_mem_init;
	cinfo->sys_mem_if.mem_term = jpi_jpeg_mem_term;

	return 0;
}

/*****************************************************************/

static void
my_error_exit (j_common_ptr cinfo)
{
  my_error_ptr myerr = (my_error_ptr)cinfo->err;
  (*cinfo->err->output_message) (cinfo);
  longjmp(myerr->setjmp_buffer,1);
}


static void
my_output_message (j_common_ptr cinfo)
{
  char buffer[JMSG_LENGTH_MAX];

  (*cinfo->err->format_message) (cinfo, buffer);
  if (quiet_mode < 2) printf(" %s ",buffer);
  global_error_counter++;
  global_total_errors++;
}


static void no_memory(void)
{
  fprintf(stderr,"jpeginfo: not enough memory!\n");
  exit(3);
}


static void p_usage(void)
{
 if (!quiet_mode) {
  fprintf(stderr,"jpeginfo v" VERSION
	  " Copyright (c) Timo Kokkonen, 1995-2020.\n");

  fprintf(stderr,
       "Usage: jpeginfo [options] <filenames>\n\n"
       "  -c, --check     check files also for errors\n"
       "  -C, --comments  display comments (from COM markers)\n"
       "  -d, --delete    delete files that have errors\n"
       "  -f<filename>,  --file<filename>\n"
       "                  read the filenames to process from given file\n"
       "                  (for standard input use '-' as a filename)\n"
       "  -h, --help      display this help and exit\n"
       "  -5, --md5       calculate MD5 checksum for each file\n"
       "  -i, --info      display even more information about pictures\n"
       "  -l, --lsstyle   use alternate listing format (ls -l style)\n"
       "  -v, --verbose   enable verbose mode (positively chatty)\n"
       "  --version	  print program version and exit\n"
       "  -q, --quiet     quiet mode, output just jpeg infos\n"
       "  -m<mode>, --mode=<mode>\n"
       "                  defines which jpegs to remove (when using"
	                 " the -d option).\n"
       "                  Mode can be one of the following:\n"
       "                    erronly     only files with serious errrors\n"
       "                    all         files containing warnings or errors"
       " (default)\n\n\n");
 }

 exit(0);
}

/*****************************************************************/
static void error_exit(j_common_ptr cinfo)
{
	char msg[JMSG_LENGTH_MAX];
	fz_context* ctx = fz_get_global_context();

	cinfo->err->format_message(cinfo, msg);
	fz_throw(ctx, FZ_ERROR_GENERIC, "jpeg error: %s", msg);
}

/*****************************************************************/

#if defined(BUILD_MONOLITHIC)
#define main(cnt, arr) jpeginfo_main(cnt, arr)
#endif

int main(int argc, const char** argv)
{
  JSAMPARRAY buf = malloc(sizeof(JSAMPROW)*BUF_LINES);
  jpeg_saved_marker_ptr exif_marker, cmarker;
  MD5_CTX *MD5 = malloc(sizeof(MD5_CTX));
  volatile int i;
  int c, j;
  unsigned char ch;
  char namebuf[1024];
  long fs;
  unsigned char *md5buf, digest[16];
  char digest_text[33];
  size_t last_read;
  fz_context* ctx = fz_get_global_context();

  global_total_errors = 0;

  struct jpeg_decompress_struct cinfo = { 0 };
  struct my_error_mgr jerr = { 0 };

  cinfo.mem = NULL;
  cinfo.global_state = 0;
  cinfo.err = jpeg_std_error(&jerr.pub);

  cinfo.client_data_ref = ctx;
  cinfo.client_init_callback = jpi_jpg_sys_mem_register;

  fz_try(ctx)
  {
	  jpeg_create_decompress(&cinfo);
	  jerr.pub.error_exit = my_error_exit;
	  jerr.pub.output_message = my_output_message;

	  if (!buf || !MD5) no_memory();
	  if (argc < 2) {
		  if (quiet_mode < 2) fprintf(stderr, "jpeginfo: file arguments missing\n"
			  "Try 'jpeginfo "
			  "--help"
			  "' for more information.\n");
		  exit(1);
	  }

	  /* parse command line parameters */
	  while (1) {
		  opt_index = 0;
		  if ((c = getopt_long(argc, argv, "livVdcChqm:f:5",
			  long_options, &opt_index)) == -1)
			  break;
		  switch (c) {
		  case 'm':
			  if (!strcasecmp(optarg, "all")) del_mode = 0;
			  else if (!strcasecmp(optarg, "erronly")) del_mode = 1;
			  else if (!quiet_mode)
				  fprintf(stderr, "Unknown parameter for -m, --mode.\n");
			  break;
		  case 'f':
			  if (!strcmp(optarg, "-")) listfile = stdin;
			  else if ((listfile = fopen(optarg, "r")) == NULL) {
				  fprintf(stderr, "Cannot open file '%s'.\n", optarg);
				  exit(2);
			  }
			  input_from_file = 1;
			  break;
		  case 'v':
			  verbose_mode = 1;
			  break;
		  case 'V':
			  fprintf(stderr, "jpeginfo v" VERSION "  " HOST_TYPE
				  "\nCopyright (c) Timo Kokkonen, 1995-2002.\n");
			  exit(0);
		  case 'd':
			  delete_mode = 1;
			  break;
		  case 'c':
			  check_mode = 1;
			  break;
		  case 'h':
			  p_usage();
			  break;
		  case 'q':
			  quiet_mode++;
			  break;
		  case 'l':
			  list_mode = 1;
			  break;
		  case 'i':
			  longinfo_mode = 1;
			  break;
		  case '5':
			  md5_mode = 1;
			  break;
		  case 'C':
			  com_mode = 1;
			  break;
		  case '?':
			  break;

		  default:
			  if (!quiet_mode)
				  fprintf(stderr, "jpeginfo: error parsing parameters.\n");
		  }
	  }

	  if (delete_mode && verbose_mode && !quiet_mode)
		  fprintf(stderr, "jpeginfo: delete mode enabled (%s)\n",
			  !del_mode ? "normal" : "errors only");

	  i = 1;
	  do {
		  if (input_from_file) {
			  if (!fgetstr(namebuf, sizeof(namebuf), listfile)) break;
			  current = namebuf;
		  }
		  else current = argv[i];

		  if (current[0] == 0) continue;
		  if (current[0] == '-' && !input_from_file) continue;

		  if (setjmp(jerr.setjmp_buffer)) {
			  jpeg_abort_decompress(&cinfo);
			  fclose(infile);
			  if (list_mode && quiet_mode < 2) printf(" %s", current);
			  if (quiet_mode < 2) printf(" [ERROR]\n");
			  if (delete_mode) delete_file(current, verbose_mode, quiet_mode);
			  continue;
		  }

		  if ((infile = fopen(current, "rb")) == NULL) {
			  if (!quiet_mode) fprintf(stderr, "jpeginfo: can't open '%s'\n", current);
			  continue;
		  }
		  if (is_dir(infile)) {
			  fclose(infile);
			  if (verbose_mode) printf("directory: '%s' skipped\n", current);
			  continue;
		  }

		  fs = filesize(infile);

		  if (md5_mode) {
			  md5buf = malloc(fs);
			  if (!md5buf) no_memory();
			  last_read = fread(md5buf, 1, fs, infile);
			  if (last_read < fs) {
				  fprintf(stderr, "jpeginfo: failed to read entire file: '%s'\n", current);
				  continue;
			  }
			  rewind(infile);

			  MD5Init(MD5);
			  MD5Update(MD5, md5buf, fs);
			  MD5Final(digest, MD5);
			  md2str(digest, digest_text);

			  free(md5buf);
		  }

		  if (!list_mode && quiet_mode < 2) printf("%s ", current);

		  global_error_counter = 0;
		  if (com_mode) jpeg_save_markers(&cinfo, JPEG_COM, 0xffff);
		  jpeg_save_markers(&cinfo, EXIF_JPEG_MARKER, 0xffff);
		  jpeg_stdio_src(&cinfo, infile);
		  jpeg_read_header(&cinfo, TRUE);

		  /* check for Exif marker */
		  exif_marker = NULL;
		  cmarker = cinfo.marker_list;
		  while (cmarker) {
			  if (cmarker->marker == EXIF_JPEG_MARKER) {
				  if (!memcmp(cmarker->data, EXIF_IDENT_STRING, 6)) exif_marker = cmarker;
			  }
			  cmarker = cmarker->next;
		  }

		  if (quiet_mode < 2) {
			  printf("%4d x %-4d %2dbit ", (int)cinfo.image_width,
				  (int)cinfo.image_height, (int)cinfo.num_components * 8);

			  if (exif_marker) printf("Exif  ");
			  else if (cinfo.saw_JFIF_marker) printf("JFIF  ");
			  else if (cinfo.saw_Adobe_marker) printf("Adobe ");
			  else printf("n/a   ");

			  if (longinfo_mode) {
				  printf("%s %s", (cinfo.progressive_mode ? "Progressive" : "Normal"),
					  (cinfo.arith_code ? "Arithmetic" : "Huffman"));

				  if (cinfo.density_unit == 1 || cinfo.density_unit == 2)
					  printf(",%ddp%c", MIN(cinfo.X_density, cinfo.Y_density),
						  (cinfo.density_unit == 1 ? 'i' : 'c'));

				  if (cinfo.CCIR601_sampling) printf(",CCIR601");
				  printf(" %7ld ", fs);

			  }
			  else printf("%c %7ld ", (cinfo.progressive_mode ? 'P' : 'N'), fs);

			  if (md5_mode) printf("%s ", digest_text);
			  if (list_mode) printf("%s ", current);

			  if (com_mode) {
				  cmarker = cinfo.marker_list;
				  while (cmarker) {
					  if (cmarker->marker == JPEG_COM) {
						  printf("\"");
						  for (j = 0; j < cmarker->data_length; j++) {
							  ch = cmarker->data[j];
							  if (ch < 32 || iscntrl(ch)) continue;
							  printf("%c", cmarker->data[j]);
						  }
						  printf("\" ");
					  }
					  cmarker = cmarker->next;
				  }
			  }
		  }

		  if (check_mode) {
			  cinfo.out_color_space = JCS_GRAYSCALE; /* to speed up the process... */
			  cinfo.scale_denom = 8;
			  cinfo.scale_num = 1;
			  jpeg_start_decompress(&cinfo);

			  for (j = 0; j < BUF_LINES; j++) {
				  buf[j] = malloc(sizeof(JSAMPLE) * cinfo.output_width *
					  cinfo.out_color_components);
				  if (!buf[j]) no_memory();
			  }

			  while (cinfo.output_scanline < cinfo.output_height) {
				  jpeg_read_scanlines(&cinfo, buf, BUF_LINES);
			  }

			  jpeg_finish_decompress(&cinfo);
			  for (j = 0; j < BUF_LINES; j++) free(buf[j]);
			  fclose(infile);

			  if (!global_error_counter) {
				  if (quiet_mode < 2) printf(" [OK]\n");
			  }
			  else {
				  if (quiet_mode < 2) printf(" [WARNING]\n");
				  if (delete_mode && !del_mode)
					  delete_file(current, verbose_mode, quiet_mode);
			  }
		  }
		  else { /* !check_mode */
			  if (quiet_mode < 2) printf("\n");
			  jpeg_abort_decompress(&cinfo);
			  fclose(infile);
		  }
	  } while (++i < argc || input_from_file);
  }
  fz_catch(ctx)
  {
	  jpeg_destroy_decompress(&cinfo);
	  free(buf);
	  free(MD5);
  }

  return (global_total_errors>0?1:0); /* return 1 if any errors found file(s)
					 we checked */
}

/* :-) */
