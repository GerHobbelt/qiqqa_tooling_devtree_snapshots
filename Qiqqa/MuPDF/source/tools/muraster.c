// Copyright (C) 2004-2024 Artifex Software, Inc.
//
// This file is part of MuPDF.
//
// MuPDF is free software: you can redistribute it and/or modify it under the
// terms of the GNU Affero General Public License as published by the Free
// Software Foundation, either version 3 of the License, or (at your option)
// any later version.
//
// MuPDF is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more
// details.
//
// You should have received a copy of the GNU Affero General Public License
// along with MuPDF. If not, see <https://www.gnu.org/licenses/agpl-3.0.en.html>
//
// Alternative licensing terms are available from the licensor.
// For commercial licensing, see <https://www.artifex.com/> or contact
// Artifex Software, Inc., 39 Mesa Street, Suite 108A, San Francisco,
// CA 94129, USA, for further information.

/*
 * muraster -- Convert a document to a raster file.
 *
 * Deliberately simple. Designed to be a basis for what
 * printer customers would need.
 *
 * Therefore; only supports pgm, ppm, pam, pbm, pkm,
 * and then only dependent on the FZ_PLOTTERS_{G,RGB,CMYK}
 * flags.
 * Only supports banding.
 * Supports auto fallback to grey if possible.
 * Supports threading.
 * Supports fallback in low memory cases.
 */

/*
	CONFIGURATION SECTION

	The first bit of configuration for this is actually in
	how the muthreads helper library is built. If muthreads
	does not know how to support threading on your system
	then it will ensure that DISABLE_MUTHREADS is set. All
	the muthreads entrypoints/types will still be defined
	(as dummy types/functions), but attempting to use them
	will return errors.

	Configuration options affecting threading should be
	turned off if DISABLE_MUTHREADS is set.

	Integrators can/should define the following
	MURASTER_CONFIG_ values. If not set, we'll
	attempt to set sensible defaults.
*/

/*
	MURASTER_CONFIG_RENDER_THREADS: The number of render
	threads to use. Typically you would set this to the
	number of CPU cores - 1 (or -2 if background printing
	is used).

	If no threading library exists for your OS set this
	to 0.

	If undefined, we will use a default of
	3 - MURASTER_CONFIG_BGPRINT.
*/
/* #define MURASTER_CONFIG_RENDER_THREADS 3 */

/*
	MURASTER_CONFIG_BGPRINT: 0 or 1. Set to 1 to
	enable background printing. This relies on
	a threading library existing for the OS.

	If undefined, we will use a default of 1.
*/
/* #define MURASTER_CONFIG_BGPRINT 1 */

/*
	MURASTER_CONFIG_X_RESOLUTION: The default X resolution
	in dots per inch. If undefined, taken to be 300dpi.
*/
/* #define MURASTER_CONFIG_X_RESOLUTION 300 */

/*
	MURASTER_CONFIG_Y_RESOLUTION: The default Y resolution
	in dots per inch. If undefined, taken to be 300dpi.
*/
/* #define MURASTER_CONFIG_Y_RESOLUTION 300 */

/*
	MURASTER_CONFIG_WIDTH: The printable page width
	(in inches)
*/
/* #define MURASTER_CONFIG_WIDTH 8.27f */

/*
	MURASTER_CONFIG_HEIGHT: The printable page height
	(in inches)
*/
/* #define MURASTER_CONFIG_HEIGHT 11.69f */

/*
	MURASTER_CONFIG_STORE_SIZE: The maximum size to use
	for the fz_store.

	If undefined, then on Linux we will attempt to guess
	the memory size, and we'll use that for the store
	size. This will be too large, but it should work OK.

	If undefined and NOT linux, then we'll use the default
	store size.
*/
/* #define MURASTER_CONFIG_STORE_SIZE FZ_STORE_DEFAULT */

/*
	MURASTER_CONFIG_MIN_BAND_HEIGHT: The minimum band
	height we will ever use. This might correspond to the
	number of nozzles on an inkjet head.

	By default, we'll use 32.
*/
/* #define MURASTER_CONFIG_MIN_BAND_HEIGHT 32 */

/*
	MURASTER_CONFIG_BAND_MEMORY: The maximum amount of
	memory (in bytes) to use for any given band.

	We will need MURASTER_CONFIG_RENDER_THREADS of these,
	one for each render thread.

	Having this be a multiple of
	MURASTER_CONFIG_MIN_BAND_HEIGHT * MURASTER_CONFIG_MAX_WIDTH * MURASTER_CONFIG_X_RESOLUTION * N
	would be sensible.

	(Where N = 1 for greyscale, 3 for RGB, 4 for CMYK)
*/
/* #define MURASTER_CONFIG_BAND_MEMORY (32*10*300*4*16) */

/*
	MURASTER_CONFIG_GREY_FALLBACK: 0, 1 or 2.

	Set to 1 to fallback to grey rendering if the page
	is definitely grey. Any images in colored color
	spaces will be assumed to be color. This may refuse
	to fallback in some cases when it could have done.

	Set to 2 to fallback to grey rendering if the page
	is definitely grey. Any images in colored color
	spaces will be exhaustively checked. This will
	fallback whenever possible, at the expense of some
	runtime as more processing is required to check.
*/
#define MURASTER_CONFIG_GREY_FALLBACK 2

/*
	END OF CONFIGURATION SECTION
*/

#include "mupdf/fitz.h"
#include "mupdf/mutool.h"
#include "mupdf/helpers/dir.h"
#include "mupdf/assertions.h"
#include "mupdf/helpers/mu-threads.h"
#include "mupdf/helpers/cpu.h"
#include "mupdf/helpers/system-header-files.h"
#include "mupdf/helpers/jmemcust.h"

#if FZ_ENABLE_RENDER_CORE 

#include "timeval.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/*
	After this point, we convert the #defines set (or not set)
	above into sensible values we can work with. Don't edit
	these for configuration.
*/

/* If we have threading, and we haven't already configured BGPRINT,
 * enable it. */
#ifndef DISABLE_MUTHREADS
#ifndef MURASTER_CONFIG_BGPRINT
#define MURASTER_CONFIG_BGPRINT 1
#endif
#endif

#ifdef MURASTER_CONFIG_X_RESOLUTION
#define X_RESOLUTION MURASTER_CONFIG_X_RESOLUTION
#else
#define X_RESOLUTION 300
#endif

#ifdef MURASTER_CONFIG_Y_RESOLUTION
#define Y_RESOLUTION MURASTER_CONFIG_Y_RESOLUTION
#else
#define Y_RESOLUTION 300
#endif

#ifdef MURASTER_CONFIG_WIDTH
#define PAPER_WIDTH MURASTER_CONFIG_WIDTH
#else
#define PAPER_WIDTH 8.27f
#endif

#ifdef MURASTER_CONFIG_HEIGHT
#define PAPER_HEIGHT MURASTER_CONFIG_HEIGHT
#else
#define PAPER_HEIGHT 11.69f
#endif

#ifdef MURASTER_CONFIG_STORE_SIZE
#define STORE_SIZE MURASTER_CONFIG_STORE_SIZE
#else
#define STORE_SIZE FZ_STORE_SIZE
#endif

#ifdef MURASTER_CONFIG_MIN_BAND_HEIGHT
#define MIN_BAND_HEIGHT MURASTER_CONFIG_MIN_BAND_HEIGHT
#else
#define MIN_BAND_HEIGHT 32
#endif

#ifdef MURASTER_CONFIG_BAND_MEMORY
#define BAND_MEMORY MURASTER_CONFIG_BAND_MEMORY
#else
#if defined(FZ_PLOTTERS_CMYK) || defined(FZ_PLOTTERS_N)
#define BAND_MEMORY (MIN_BAND_HEIGHT * PAPER_WIDTH * X_RESOLUTION * 4 * 16)
#elif defined(FZ_PLOTTERS_RGB)
#define BAND_MEMORY (MIN_BAND_HEIGHT * PAPER_WIDTH * X_RESOLUTION * 3 * 16)
#else
#define BAND_MEMORY (MIN_BAND_HEIGHT * PAPER_WIDTH * X_RESOLUTION * 1 * 16)
#endif
#endif

#ifdef MURASTER_CONFIG_GREY_FALLBACK
#define GREY_FALLBACK MURASTER_CONFIG_GREY_FALLBACK
#else
#ifdef FZ_PLOTTERS_N
#define GREY_FALLBACK 1
#elif defined(FZ_PLOTTERS_G) && (defined(FZ_PLOTTERS_RGB) || defined(FZ_PLOTTERS_CMYK))
#define GREY_FALLBACK 1
#else
#define GREY_FALLBACK 0
#endif
#endif

#if GREY_FALLBACK != 0 && !defined(FZ_PLOTTERS_N) && !defined(FZ_PLOTTERS_G)
#error MURASTER_CONFIG_GREY_FALLBACK requires either FZ_PLOTTERS_N or FZ_PLOTTERS_G
#endif

/* Enable for helpful threading debug */
#if 01
#define DEBUG_THREADS(code) do { if (verbosity >= 2) { code; } } while (0)
#else
#define DEBUG_THREADS(code) do { } while (0)
#endif

enum {
	OUT_NONE,
	OUT_PNG,
	OUT_TIFF,
	OUT_WEBP,
	OUT_PAM,
	OUT_PBM,
	OUT_PGM,
	OUT_PPM,
	OUT_PKM
};

enum {
	CS_GRAY,
	CS_RGB,
	CS_CMYK
};

typedef struct
{
	const char *suffix;
	int format;
	int cs;
} suffix_t;

static const suffix_t suffix_table[] =
{
	{ ".png", OUT_PNG, CS_RGB },
	{ ".webp", OUT_WEBP, CS_RGB },
	{ ".tiff", OUT_TIFF, 0 },
#if FZ_PLOTTERS_G || FZ_PLOTTERS_N
	{ ".pgm", OUT_PGM, CS_GRAY },
#endif
#if FZ_PLOTTERS_RGB || FZ_PLOTTERS_N
	{ ".ppm", OUT_PPM, CS_RGB },
#endif
#if FZ_PLOTTERS_CMYK || FZ_PLOTTERS_N
	{ ".pam", OUT_PAM, CS_CMYK },
#endif
#if FZ_PLOTTERS_G || FZ_PLOTTERS_N
	{ ".pbm", OUT_PBM, CS_GRAY },
#endif
#if FZ_PLOTTERS_CMYK || FZ_PLOTTERS_N
	{ ".pkm", OUT_PKM, CS_CMYK }
#endif
};

static fz_cookie master_cookie = { 0 };

/*
	In the presence of pthreads or Windows threads, we can offer
	a multi-threaded option. In the absence of such we degrade
	nicely.
*/
#ifndef DISABLE_MUTHREADS

static mu_mutex mutexes[FZ_LOCK_MAX];

static void muraster_lock(void *user, int lock)
{
	mu_lock_mutex(&mutexes[lock]);
}

static void muraster_unlock(void *user, int lock)
{
	mu_unlock_mutex(&mutexes[lock]);
}

static fz_locks_context muraster_locks =
{
	NULL, muraster_lock, muraster_unlock
};

static void fin_muraster_locks(void)
{
	int i;

	for (i = 0; i < FZ_LOCK_MAX; i++)
		mu_destroy_mutex(&mutexes[i]);
}

static fz_locks_context *init_muraster_locks(void)
{
	int i;
	int failed = 0;

	for (i = 0; i < FZ_LOCK_MAX; i++)
		failed |= mu_create_mutex(&mutexes[i]);

	if (failed)
	{
		fin_muraster_locks();
		return NULL;
	}

	return &muraster_locks;
}

#endif

#ifdef MURASTER_CONFIG_RENDER_THREADS
#define NUM_RENDER_THREADS MURASTER_CONFIG_RENDER_THREADS
#elif defined(DISABLE_MUTHREADS)
#define NUM_RENDER_THREADS 0
#else
#define NUM_RENDER_THREADS     fz_get_cpu_core_count()
#endif

#ifdef MURASTER_CONFIG_BGPRINT
#define BGPRINT MURASTER_CONFIG_BGPRINT
#elif defined(DISABLE_MUTHREADS)
#define BGPRINT 0
#else
#define BGPRINT 1
#endif

#if defined(DISABLE_MUTHREADS) && BGPRINT != 0
#error "Can't have MURASTER_CONFIG_BGPRINT > 0 without having a threading library!"
#endif

typedef struct worker_t {
	fz_context *ctx;
	int started;
	int status;
	int num;
	int band_start; /* -1 to shutdown, or offset of band to render */
	fz_display_list *list;
	fz_matrix ctm;
	fz_rect tbounds;
	fz_pixmap *pix;
	fz_bitmap *bit;
	fz_cookie cookie;
#ifndef DISABLE_MUTHREADS
	mu_semaphore start;
	mu_semaphore stop;
	mu_thread thread;
#endif
} worker_t;

static int muraster_is_toplevel_ctx = 0;

static fz_context *ctx = NULL;
static const char *output = NULL;
static fz_output *out = NULL;

static const char *format = NULL;
static const suffix_t *output_format = NULL;

static int rotation = -1;
static float x_resolution;
static float y_resolution;
static int res_specified = 0;
static int width = 0;
static int height = 0;
static int fit = 0;

static float layout_w = FZ_DEFAULT_LAYOUT_W;
static float layout_h = FZ_DEFAULT_LAYOUT_H;
static float layout_em = FZ_DEFAULT_LAYOUT_EM;
static const char *layout_css = NULL;
static int layout_use_doc_css = 1;
static float min_line_width = 0.0f;

static int showtime = 0;
static int showmemory = 0;

static int no_icc = 0;
static int ignore_errors = 0;
static int alphabits_text = 8;
static int alphabits_graphics = 8;
static int subpix_preset = 0;

static int min_band_height;
static size_t max_band_memory;
static int lowmemory = 0;

static int verbosity = 1;
static int errored = 0;
static fz_colorspace *colorspace;
static const char *filename;
static int files = 0;
static int num_workers = 0;
static worker_t *workers = NULL;

typedef struct render_details
{
	/* Page */
	fz_page *page;

	/* Display list */
	fz_display_list *list;

	/* Raw bounds */
	fz_rect bounds;

	/* Transformed bounds */
	fz_rect tbounds;

	/* Rounded transformed bounds */
	fz_irect ibounds;

	/* Transform matrix */
	fz_matrix ctm;

	/* How many min band heights are we working in? */
	int band_height_multiple;

	/* What colorspace are we working in? (Adjusted for fallback) */
	enum fz_colorspace_type colorspace;

	/* What output format? (Adjusted for fallback) */
	int format;

	/* During the course of the rendering, this keeps track of
	 * how many 'min_band_heights' have been safely rendered. */
	int bands_rendered;

	/* The maximum number of workers we'll try to use. This
	 * will start at the maximum value, and may drop to 0
	 * if we have problems with memory. */
	int num_workers;

	/* The band writer to output the page */
	fz_band_writer *bander;

	/* Number of components in image */
	int n;
} render_details;

enum
{
	RENDER_OK = 0,
	RENDER_RETRY = 1,
	RENDER_FATAL = 2
};

static struct {
	int active;
	int started;
	int solo;
	int status;
	fz_context *ctx;
#ifndef DISABLE_MUTHREADS
	mu_thread thread;
	mu_semaphore start;
	mu_semaphore stop;
#endif
	int pagenum;
	const char *filename;
	render_details render;
	int interptime;
	fz_cookie cookie;
} bgprint = { 0 };

static struct {
	int count, total;
	int min, max;
	int mininterp, maxinterp;
	int minpage, maxpage;
	const char *minfilename;
	const char *maxfilename;
	int layout;
	int minlayout, maxlayout;
	const char *minlayoutfilename;
	const char *maxlayoutfilename;
} timing = { 0 };

static int usage(void)
{
	fz_info(ctx,
		"muraster version " FZ_VERSION "\n"
		"usage: muraster [options] file [pages]\n"
		"  -p -  password\n"
		"\n"
		"  -o -  output file name (%%d or ### for page number, '-' for stdout)\n"
		"  -F -  output format (default inferred from output file name)\n"
		"    png, pam, pbm, pgm, pkm, ppm\n"
		"\n"
		"  -q    be quiet (don't print progress messages)\n"
		"  -v    verbose ~ not quiet (repeat to increase the chattiness of the application)\n"
		"  -s -  show extra information:\n"
		"     m      show memory use\n"
		"     t      show timings\n"
		"\n"
		"  -R {auto,0,90,180,270}\n"
		"        rotate clockwise (default: auto)\n"
		"  -r -{,_}  x and y resolution in dpi (default: %dx%d)\n"
		"  -w -  printable width (in inches) (default: %.2f)\n"
		"  -h -  printable height (in inches) (default: %.2f)\n"
		"  -f    fit file to page if too large\n"
		"  -B -  minimum band height (e.g. 32)\n"
		"  -M -  max band memory (e.g. 655360)\n"
#ifndef DISABLE_MUTHREADS
		"  -T -  number of threads to use for rendering (banded mode only), where number arg\n"
		"        is one of:\n"
		"     N      equals the number of (virtual) CPU cores on this machine\n"   
		"     *      = N\n"   
		"     4      or any other positive integer number\n"   
		"     50%    or any other percentage of N\n"
		"     -2     or any other negative integer: so many less than N. (Hence keeps\n"
		"            cores free for independent tasks.\n"
#else
		"  -T -  number of threads to use for rendering (disabled in this non-threading\n"
		"        build)\n"
#endif
#ifndef DISABLE_MUTHREADS
		"  -P    parallel interpretation/rendering\n"
#else
		"  -P    parallel interpretation/rendering (disabled in this non-threading build)\n"
#endif
		"\n"
		"  -W -  page width for EPUB layout\n"
		"  -H -  page height for EPUB layout\n"
		"  -S -  font size for EPUB layout\n"
		"  -U -  file name of user stylesheet for EPUB layout\n"
		"  -X    disable document styles for EPUB layout\n"
		"\n"
		"  -A -  number of bits of anti-aliasing (0 to 8)\n"
		"  -A -/-  number of bits of anti-aliasing (0 to 8) (graphics, text)\n"
		"  -A -/-/-  number of bits of antialiasing (0 to 8) (graphics, text)\n"
		"            subpix preset: 0 = default, 1 = reduced\n"
		"  -J -  set PNG output compression level: 0 (none), 1 (fast)..9 (best)\n"
		"\n"
		"  -m -  specify custom memory limits:\n"
		"    sNNN   set memory limit to NNN bytes: the application will not be allowed\n"
		"           to consume more that NNN bytes heap memory at any time\n"
		"    aNNN   set alloc limit to NNN: the application will not execute more than\n"
		"           NNN heap allocation requests.\n"
		"    NNN    set memory limit to NNN bytes (same as 'sNNN' above)\n"
		"  -L    low memory mode (avoid caching, clear objects after each page)\n"
		"\n"
		"  -V    display the version of this application and terminate\n"
		"\n"
		"\tpages\tcomma separated list of page numbers and ranges\n",
		X_RESOLUTION, Y_RESOLUTION, PAPER_WIDTH, PAPER_HEIGHT
	);

	return EXIT_FAILURE;
}

static int gettime_once = 1;

static int gettime(void)
{
	static struct curltime first;
	struct curltime now;
	if (gettime_once)
	{
		first = Curl_now();
		gettime_once = 0;
	}
	now = Curl_now();
	return Curl_timediff(now, first);
}

static int drawband(fz_context *ctx, fz_page *page, fz_display_list *list, fz_matrix ctm, fz_rect tbounds, int band_start, fz_pixmap *pix, fz_bitmap **bit)
{
	fz_device *dev = NULL;

	*bit = NULL;

	fz_var(dev);

	fz_try(ctx)
	{
		fz_clear_pixmap_with_value(ctx, pix, 255);

		dev = fz_new_draw_device(ctx, fz_identity, pix);

		if (lowmemory)
			fz_enable_device_hints(ctx, dev, FZ_NO_CACHE);
		if (alphabits_graphics == 0)
			fz_enable_device_hints(ctx, dev, FZ_DONT_INTERPOLATE_IMAGES);
		if (list)
			fz_run_display_list(ctx, list, dev, ctm, tbounds);
		else
			fz_run_page(ctx, page, dev, ctm);
		fz_close_device(ctx, dev);
		fz_drop_device(ctx, dev);
		dev = NULL;

		if ((output_format->format == OUT_PBM) || (output_format->format == OUT_PKM))
			*bit = fz_new_bitmap_from_pixmap_band(ctx, pix, NULL, band_start);
	}
	fz_catch(ctx)
	{
		fz_drop_device(ctx, dev);
		return RENDER_RETRY;
	}
	return RENDER_OK;
}

static int dodrawpage(fz_context *ctx, int pagenum, render_details *render)
{
	fz_pixmap *pix = NULL;
	fz_bitmap *bit = NULL;
	int errors_are_fatal = 0;
	fz_irect ibounds = render->ibounds;
	fz_rect tbounds = render->tbounds;
	int total_height = ibounds.y1 - ibounds.y0;
	int start_offset = min_band_height * render->bands_rendered;
	int remaining_start = ibounds.y0 + start_offset;
	int remaining_height = ibounds.y1 - remaining_start;
	int band_height = min_band_height * render->band_height_multiple;
	int bands = (remaining_height + band_height - 1) / band_height;
	fz_matrix ctm = render->ctm;
	int band;

	fz_var(pix);
	fz_var(bit);
	fz_var(errors_are_fatal);

	fz_try(ctx)
	{
		/* Set up ibounds and tbounds for a single band_height band.
		 * We will adjust ctm as we go. */
		ibounds.y1 = ibounds.y0 + band_height;
		tbounds.y1 = tbounds.y0 + band_height + 2;
		DEBUG_THREADS(fz_info(ctx, "Using %d Bands\n", bands));
		ctm.f += start_offset;

		if (render->num_workers > 0)
		{
			for (band = 0; band < fz_mini(render->num_workers, bands); band++)
			{
				int band_start = start_offset + band * band_height;
				worker_t *w = &workers[band];
				w->band_start = band_start;
				w->ctm = ctm;
				w->tbounds = tbounds;
				//fz_clean_cookie(ctx, &w->cookie);
				w->cookie = master_cookie;
				w->list = render->list;
				if (remaining_height < band_height)
					ibounds.y1 = ibounds.y0 + remaining_height;
				remaining_height -= band_height;
				w->pix = fz_new_pixmap_with_bbox(ctx, colorspace, ibounds, NULL, 0);
				w->pix->y += band * band_height;
				fz_set_pixmap_resolution(ctx, w->pix, x_resolution, y_resolution);
				w->started = 1;
#ifndef DISABLE_MUTHREADS
				DEBUG_THREADS(fz_info(ctx, "Worker %d, Pre-triggering band %d\n", band, band));
				mu_trigger_semaphore(&w->start);
#endif
			}
			//pix = workers[0].pix;
		}
		else
		{
			pix = fz_new_pixmap_with_bbox(ctx, colorspace, ibounds, NULL, 0);
			fz_set_pixmap_resolution(ctx, pix, x_resolution, y_resolution);
		}

		for (band = 0; band < bands; band++)
		{
			int status;
			int band_start = start_offset + band * band_height;
			int draw_height = total_height - band_start;

			if (draw_height > band_height)
				draw_height = band_height;

			if (render->num_workers > 0)
			{
				worker_t *w = &workers[band % render->num_workers];
#ifndef DISABLE_MUTHREADS
				DEBUG_THREADS(fz_info(ctx, "Waiting for worker %d to complete band %d\n", w->num, band));
				mu_wait_semaphore(&w->stop);
#endif
				w->started = 0;
				status = w->status;
				pix = w->pix;
				bit = w->bit;
				w->bit = NULL;
				ASSERT(ctx != w->ctx);
				ctx->cookie->d.errors += w->cookie.d.errors;
			}
			else
			{
				status = drawband(ctx, render->page, render->list, ctm, tbounds, band_start, pix, &bit);
			}

			if (status != RENDER_OK)
				fz_throw(ctx, FZ_ERROR_GENERIC, "Render failed");

			render->bands_rendered += render->band_height_multiple;

			if (out)
			{
				/* If we get any errors while outputting the bands, retrying won't help. */
				errors_are_fatal = 1;
				ASSERT(render->bander);
				ASSERT(render->bander->n == pix->n);
				ASSERT(render->bander->w == pix->w);
				ASSERT(draw_height <= pix->h);
				fz_write_band(ctx, render->bander, bit ? bit->stride : pix->stride, draw_height, bit ? bit->samples : pix->samples);
				errors_are_fatal = 0;
			}
			fz_drop_bitmap(ctx, bit);
			bit = NULL;

			if (render->num_workers > 0 && band + render->num_workers < bands)
			{
				worker_t *w = &workers[band % render->num_workers];
				w->band_start = band_start;
				w->ctm = ctm;
				w->tbounds = tbounds;
				//fz_clean_cookie(w->ctx, &w->cookie);
				w->cookie = master_cookie;
				w->started = 1;
#ifndef DISABLE_MUTHREADS
				DEBUG_THREADS(fz_info(ctx, "Triggering worker %d for band_start= %d\n", w->num, w->band_start));
				mu_trigger_semaphore(&w->start);
#endif
			}
			if (render->num_workers <= 0)
				pix->y += draw_height;
		}
	}
	fz_always(ctx)
	{
		fz_drop_bitmap(ctx, bit);
		bit = NULL;
		if (render->num_workers > 0)
		{
			int band;
			for (band = 0; band < fz_mini(render->num_workers, bands); band++)
			{
				worker_t *w = &workers[band];
				w->cookie.d.abort = 1;
				if (w->started)
				{
#ifndef DISABLE_MUTHREADS
					DEBUG_THREADS(fz_info(ctx, "Waiting on worker %d to finish processing\n", band));
					mu_wait_semaphore(&w->stop);
#endif
					w->started = 0;
				}
				fz_drop_pixmap(ctx, w->pix);
				w->pix = NULL;
			}
		}
		else
		{
			fz_drop_pixmap(ctx, pix);
		}
	}
	fz_catch(ctx)
	{
		/* Swallow error */
		if (errors_are_fatal)
			return RENDER_FATAL;
		return RENDER_RETRY;
	}
	if (ctx->cookie->d.errors)
		errored = 1;

	return RENDER_OK;
}

/* This functions tries to render a page, falling back repeatedly to try and make it work. */
static int try_render_page(fz_context *ctx, int pagenum, int start, int interptime, const char *fname, int bg, int solo, render_details *render)
{
	int status;

	if (out && !(bg && solo))
	{
		/* Output any page level headers (for banded formats). Don't do this if
		 * we're running in solo bgprint mode, cos we've already done it once! */
		fz_try(ctx)
		{
			int w = render->ibounds.x1 - render->ibounds.x0;
			int h = render->ibounds.y1 - render->ibounds.y0;
			fz_write_header(ctx, render->bander, w, h, render->n, 0, 0, 0, 0, 0, NULL);
		}
		fz_catch(ctx)
		{
			/* Failure! */
			return RENDER_FATAL;
		}
	}

	while (1)
	{
		status = dodrawpage(ctx, pagenum, render);
		if (status == RENDER_OK || status == RENDER_FATAL)
			break;

		/* If we are bgprinting, then ask the caller to try us again in solo mode. */
		if (bg && !solo)
		{
			DEBUG_THREADS(fz_info(ctx, "Render failure; trying again in solo mode\n"));
			return RENDER_RETRY; /* Avoids all the cleanup below! */
		}

		/* Try again with fewer threads */
		if (render->num_workers > 1)
		{
			render->num_workers >>= 1;
			DEBUG_THREADS(fz_info(ctx, "Render failure; trying again with %d render threads\n", render->num_workers));
			continue;
		}

		/* Halve the band height, if we still can. */
		if (render->band_height_multiple > 2)
		{
			render->band_height_multiple >>= 1;
			DEBUG_THREADS(fz_info(ctx, "Render failure; trying again with %d band height multiple\n", render->band_height_multiple));
			continue;
		}

		/* If all else fails, ditch the list and try again. */
		if (render->list)
		{
			fz_drop_display_list(ctx, render->list);
			render->list = NULL;
			DEBUG_THREADS(fz_info(ctx, "Render failure; trying again with no list\n"));
			continue;
		}

		/* Give up. */
		DEBUG_THREADS(fz_info(ctx, "Render failure; nothing else to try\n"));
		break;
	}

	fz_close_band_writer(ctx, render->bander);

	fz_drop_page(ctx, render->page);
	fz_drop_display_list(ctx, render->list);
	fz_drop_band_writer(ctx, render->bander);

	if (showtime)
	{
		int end = gettime();
		int diff = end - start;

		if (bg)
		{
			if (diff + interptime < timing.min)
			{
				timing.min = diff + interptime;
				timing.mininterp = interptime;
				timing.minpage = pagenum;
				timing.minfilename = fname;
			}
			if (diff + interptime > timing.max)
			{
				timing.max = diff + interptime;
				timing.maxinterp = interptime;
				timing.maxpage = pagenum;
				timing.maxfilename = fname;
			}
			timing.total += diff + interptime;
			timing.count ++;

			fz_info(ctx, " pagenum=%d :: %dms (interpretation) %dms (rendering) %dms (total)", pagenum, interptime, diff, diff + interptime);
		}
		else
		{
			if (diff < timing.min)
			{
				timing.min = diff;
				timing.minpage = pagenum;
				timing.minfilename = fname;
			}
			if (diff > timing.max)
			{
				timing.max = diff;
				timing.maxpage = pagenum;
				timing.maxfilename = fname;
			}
			timing.total += diff;
			timing.count ++;

			fz_info(ctx, " pagenum=%d :: %dms (total)", pagenum, diff);
		}
	}

	if (lowmemory)
		fz_empty_store(ctx);

	if (showmemory)
	{
		fz_dump_glyph_cache_stats(ctx);
	}

	fz_flush_warnings(ctx);

	return status;
}

static int wait_for_bgprint_to_finish(void)
{
	if (!bgprint.active || !bgprint.started)
		return 0;

#ifndef DISABLE_MUTHREADS
	mu_wait_semaphore(&bgprint.stop);
#endif
	bgprint.started = 0;
	return bgprint.status;
}

static void
get_page_render_details(fz_context *ctx, fz_page *page, render_details *render)
{
	float page_width, page_height;
	int rot;
	float s_x, s_y;

	render->page = page;
	render->list = NULL;
	render->num_workers = num_workers;

	render->bounds = fz_bound_page(ctx, page);
	page_width = (render->bounds.x1 - render->bounds.x0) / 72;
	page_height = (render->bounds.y1 - render->bounds.y0) / 72;

	s_x = x_resolution / 72;
	s_y = y_resolution / 72;
	if (rotation == -1)
	{
		/* Automatic rotation. If we fit, use 0. If we don't, and 90 would be 'better' use that. */
		if (page_width <= width && page_height <= height)
		{
			/* Page fits, so use no rotation. */
			rot = 0;
		}
		else if (fit)
		{
			/* Use whichever gives the biggest scale */
			float sx_0 = width / page_width;
			float sy_0 = height / page_height;
			float sx_90 = height / page_width;
			float sy_90 = width / page_height;
			float s_0, s_90;
			s_0 = fz_min(sx_0, sy_0);
			s_90 = fz_min(sx_90, sy_90);
			if (s_0 >= s_90)
			{
				rot = 0;
				if (s_0 < 1)
				{
					s_x *= s_0;
					s_y *= s_0;
				}
			}
			else
			{
				rot = 90;
				if (s_90 < 1)
				{
					s_x *= s_90;
					s_y *= s_90;
				}
			}
		}
		else
		{
			/* Use whichever crops the least area */
			float lost0 = 0;
			float lost90 = 0;

			if (page_width > width)
				lost0 += (page_width - width) * (page_height > height ? height : page_height);
			if (page_height > height)
				lost0 += (page_height - height) * page_width;

			if (page_width > height)
				lost90 += (page_width - height) * (page_height > width ? width : page_height);
			if (page_height > width)
				lost90 += (page_height - width) * page_width;

			rot = (lost0 <= lost90 ? 0 : 90);
		}
	}
	else
	{
		rot = rotation;
	}

	render->ctm = fz_pre_scale(fz_rotate(rot), s_x, s_y);
	render->tbounds = fz_transform_rect(render->bounds, render->ctm);
	render->ibounds = fz_round_rect(render->tbounds);
}

static void
initialise_banding(fz_context *ctx, render_details *render, int color)
{
	size_t min_band_mem;
	int bpp, h, w, reps;
	const int compression_effort = 0;

	render->colorspace = output_format->cs;
	render->format = output_format->format;
#if GREY_FALLBACK != 0
	if (color == 0)
	{
		if (render->colorspace == CS_RGB)
		{
			/* Fallback from PPM to PGM */
			render->colorspace = CS_GRAY;
			render->format = OUT_PGM;
		}
		else if (render->colorspace == CS_CMYK)
		{
			render->colorspace = CS_GRAY;
			if (render->format == OUT_PKM)
				render->format = OUT_PBM;
			else
				render->format = OUT_PGM;
		}
	}
#endif

	switch (render->colorspace)
	{
	case CS_GRAY:
		bpp = 1;
		break;
	case CS_RGB:
		bpp = 2;
		break;
	default:
	case CS_CMYK:
		bpp = 3;
		break;
	}

	w = render->ibounds.x1 - render->ibounds.x0;
	h = render->ibounds.y1 - render->ibounds.y0;
	if (w <= 0 || h <= 0)
		fz_throw(ctx, FZ_ERROR_ARGUMENT, "Invalid page dimensions");


	min_band_mem = (size_t)bpp * w * min_band_height;
	if (min_band_mem > 0)
		reps = (int)(max_band_memory / min_band_mem);
	if (min_band_mem == 0 || reps < 1)
		reps = 1;

	/* Adjust reps to even out the work between threads */
	if (render->num_workers > 0)
	{
		int runs, num_bands;
		num_bands = (h + min_band_height - 1) / min_band_height;
		/* num_bands = number of min_band_height bands */
		runs = (num_bands + reps - 1) / reps;
		/* runs = number of worker runs of reps min_band_height bands */
		runs = ((runs + render->num_workers - 1) / render->num_workers) * render->num_workers;
		/* runs = number of worker runs rounded up to make use of all our threads */
		reps = (num_bands + runs - 1) / runs;
	}

	render->band_height_multiple = reps;
	render->bands_rendered = 0;

	if (output_format->format == OUT_PGM || output_format->format == OUT_PPM)
	{
		render->bander = fz_new_pnm_band_writer(ctx, out);
		render->n = output_format->format == OUT_PGM ? 1 : 3;
	}
	else if (output_format->format == OUT_PAM)
	{
		render->bander = fz_new_pam_band_writer(ctx, out);
		render->n = 4;
	}
	else if (output_format->format == OUT_PBM)
	{
		render->bander = fz_new_pbm_band_writer(ctx, out);
		render->n = 1;
	}
	else if (output_format->format == OUT_PKM)
	{
		render->bander = fz_new_pkm_band_writer(ctx, out);
		render->n = 4;
	}
	else if (output_format->format == OUT_PNG)
	{
		render->bander = fz_new_png_band_writer(ctx, out, compression_effort);
		render->n = 3;
	}
	else if (output_format->format == OUT_WEBP)
	{
		render->bander = fz_new_webp_band_writer(ctx, out, compression_effort);
		render->n = 3;
	}
	else if (output_format->format == OUT_TIFF)
	{
		render->bander = fz_new_tiff_band_writer(ctx, out, compression_effort);
		render->n = 3;
	}
	else
	{
		assert(!"Should never get here! All possible output formats should be covered in the if/elif list above!");
	}
}

static void drawpage(fz_context *ctx, fz_document *doc, int pagenum)
{
	fz_page *page;
	fz_display_list *list = NULL;
	fz_device *list_dev = NULL;
	int start;
#if GREY_FALLBACK != 0
	fz_device *test_dev = NULL;
	int is_color = 0;
#else
	int is_color = 2;
#endif
	render_details render;
	int status;

	fz_var(list);
	fz_var(list_dev);
	fz_var(test_dev);

	for (;;)
	{
		start = (showtime ? gettime() : 0);

		page = fz_load_page(ctx, doc, pagenum - 1);

		/* Calculate Page bounds, transform etc */
		get_page_render_details(ctx, page, &render);

		/* Make the display list, and see if we need color */
		fz_try(ctx)
		{
			list = fz_new_display_list(ctx, render.bounds);
			list_dev = fz_new_list_device(ctx, list);
#if GREY_FALLBACK != 0
			test_dev = fz_new_test_device(ctx, &is_color, 0.01f, 0, list_dev);
			fz_run_page(ctx, page, test_dev, fz_identity);
			fz_close_device(ctx, test_dev);
#else
			fz_run_page(ctx, page, list_dev, fz_identity);
#endif
			fz_close_device(ctx, list_dev);
		}
		fz_always(ctx)
		{
#if GREY_FALLBACK != 0
			fz_drop_device(ctx, test_dev);
#endif
			fz_drop_device(ctx, list_dev);
		}
		fz_catch(ctx)
		{
			fz_drop_display_list(ctx, list);
			list = NULL;
			/* Just continue with no list. Also, we can't do multiple
			 * threads if we have no list. */
			render.num_workers = 1;
		}
		render.list = list;

#if GREY_FALLBACK != 0
		if (list == NULL)
		{
			/* We need to know about color, but the previous test failed
			 * (presumably) due to the size of the list. Rerun direct
			 * from file. */
			fz_try(ctx)
			{
				test_dev = fz_new_test_device(ctx, &is_color, 0.01f, 0, NULL);
				if (lowmemory)
					fz_enable_device_hints(ctx, test_dev, FZ_NO_CACHE);
				fz_run_page(ctx, page, test_dev, fz_identity);
				fz_close_device(ctx, test_dev);
			}
			fz_always(ctx)
			{
				fz_drop_device(ctx, test_dev);
				test_dev = NULL;
			}
			fz_catch(ctx)
			{
				/* We failed. Just give up. */
				fz_drop_page(ctx, page);
				fz_rethrow(ctx);
			}

			if (bgprint.active && showtime)
			{
				int end = gettime();
				start = end - start;
			}
		}
#endif

#if GREY_FALLBACK == 2
		/* If we 'possibly' need color, find out if we 'really' need color. */
		if (is_color == 1)
		{
			/* We know that the device has images or shadings in
			 * colored spaces. We have been told to test exhaustively
			 * so we know whether to use color or grey rendering. */
			is_color = 0;
			fz_try(ctx)
			{
				test_dev = fz_new_test_device(ctx, &is_color, 0.01f, FZ_TEST_OPT_IMAGES | FZ_TEST_OPT_SHADINGS, NULL);
				if (lowmemory)
					fz_enable_device_hints(ctx, test_dev, FZ_NO_CACHE);
				if (list)
					fz_run_display_list(ctx, list, test_dev, fz_identity, fz_infinite_rect);
				else
					fz_run_page(ctx, page, test_dev, fz_identity);
				fz_close_device(ctx, test_dev);
			}
			fz_always(ctx)
			{
				fz_drop_device(ctx, test_dev);
				test_dev = NULL;
			}
			fz_catch(ctx)
			{
				fz_drop_display_list(ctx, list);
				fz_drop_page(ctx, page);
				fz_rethrow(ctx);
			}
		}
#endif

		// close file and create a fresh one for output formats which DO NOT support multi-page image outputs:
		if (out && out != fz_stdout(ctx) && (output_format->format == OUT_PNG || output_format->format == OUT_WEBP))
		{
			fz_close_output(ctx, out);
			fz_drop_output(ctx, out);
			out = NULL;

			bgprint.solo = 0;
		}

		if (!out)
		{
			if (!output || *output == 0 || !strcmp(output, "-"))
			{
#ifdef _WIN32
				/* Windows specific code to make stdout binary. */
				setmode(fileno(stdout), O_BINARY);
#endif
				out = fz_stdout(ctx);
			}
			else
			{
				char fbuf[PATH_MAX];
				fz_format_output_path(ctx, fbuf, sizeof fbuf, output, pagenum);
				fz_normalize_path(ctx, fbuf, sizeof fbuf, fbuf);
				fz_sanitize_path(ctx, fbuf, sizeof fbuf, fbuf);
				out = fz_new_output_with_path(ctx, fbuf, 0);
			}
		}

		/* Figure out banding */
		initialise_banding(ctx, &render, is_color);

		if (bgprint.active && showtime)
		{
			int end = gettime();
			start = end - start;
		}

		/* If we're not using bgprint, then no need to wait */
		if (!bgprint.active)
			break;

		/* If we are using it, then wait for it to finish. */
		status = wait_for_bgprint_to_finish();
		if (status == RENDER_OK)
		{
			/* The background bgprint completed successfully. Drop out of the loop,
			 * and carry on with our next page. */
			break;
		}

		/* The bgprint in the background failed! This might have been because
		 * we were using memory etc in the foreground. We'd better ditch
		 * everything we can and try again. */
		fz_drop_display_list(ctx, list);
		fz_drop_page(ctx, page);

		if (status == RENDER_FATAL)
		{
			/* We failed because of not being able to output. No point in retrying. */
			fz_throw(ctx, FZ_ERROR_GENERIC, "Failed to render page");
		}
		bgprint.started = 1;
		bgprint.solo = 1;
#ifndef DISABLE_MUTHREADS
		mu_trigger_semaphore(&bgprint.start);
#endif
		status = wait_for_bgprint_to_finish();
		if (status != 0)
		{
			/* Hard failure */
			fz_throw(ctx, FZ_ERROR_GENERIC, "Failed to render page");
		}
		/* Loop back to reload this page */
	}

	if (showtime)
	{
		fz_info(ctx, "page %s %d", filename, pagenum);
	}
	if (bgprint.active)
	{
		bgprint.started = 1;
		bgprint.solo = 0;
		bgprint.render = render;
		bgprint.filename = filename;
		bgprint.pagenum = pagenum;
		bgprint.interptime = start;
#ifndef DISABLE_MUTHREADS
		mu_trigger_semaphore(&bgprint.start);
#endif
	}
	else
	{
		if (try_render_page(ctx, pagenum, start, 0, filename, 0, 0, &render))
		{
			/* Hard failure */
			fz_throw(ctx, FZ_ERROR_GENERIC, "Failed to render page");
		}
	}
}

/* Wait for the final page being printed by bgprint to complete,
 * retrying if necessary. */
static void
finish_bgprint(fz_context *ctx)
{
	int status;

	if (!bgprint.active)
		return;

	/* If we are using it, then wait for it to finish. */
	status = wait_for_bgprint_to_finish();
	if (status == RENDER_OK)
	{
		/* The background bgprint completed successfully. */
		return;
	}

	if (status == RENDER_FATAL)
	{
		/* We failed because of not being able to output. No point in retrying. */
		fz_throw(ctx, FZ_ERROR_GENERIC, "Failed to render page");
	}
	bgprint.started = 1;
	bgprint.solo = 1;
#ifndef DISABLE_MUTHREADS
	mu_trigger_semaphore(&bgprint.start);
#endif
	status = wait_for_bgprint_to_finish();
	if (status != 0)
	{
		/* Hard failure */
		fz_throw(ctx, FZ_ERROR_GENERIC, "Failed to render page");
	}
}

/* Signal workers to abort work ASAP. */
static void
abort_bgprint(fz_context* ctx)
{
#ifndef DISABLE_MUTHREADS
	// bgprint also uses the workers, hence we MUST shut down bgprint BEFORE the workers themselves:
	if (bgprint.active)
	{
		bgprint.pagenum = -1;
		mu_trigger_semaphore(&bgprint.start);
	}

	if (num_workers > 0)
	{
		int i;
		DEBUG_THREADS(fz_info(ctx, "Asking workers to shutdown, then destroy their resources\n"));
		for (i = 0; i < num_workers; i++)
		{
			workers[i].band_start = -1;
			mu_trigger_semaphore(&workers[i].start);
		}
	}
#endif /* DISABLE_MUTHREADS */
}

static void drawrange(fz_context *ctx, fz_document *doc, const char *range)
{
	int page, spage, epage, pagecount;

	pagecount = fz_count_pages(ctx, doc);

	while ((range = fz_parse_page_range(ctx, range, &spage, &epage, pagecount)))
	{
		if (spage < epage)
			for (page = spage; page <= epage; page++)
			{
				fz_try(ctx)
					drawpage(ctx, doc, page);
				fz_catch(ctx)
				{
					if (ignore_errors)
						fz_warn(ctx, "ignoring error on page %d in '%s'", page, filename);
					else
						fz_rethrow(ctx);
				}
			}
		else
			for (page = spage; page >= epage; page--)
			{
				fz_try(ctx)
					drawpage(ctx, doc, page);
				fz_catch(ctx)
				{
					if (ignore_errors)
						fz_warn(ctx, "ignoring error on page %d in '%s'", page, filename);
					else
						fz_rethrow(ctx);
				}
			}
	}
}

typedef struct
{
	size_t size;
	size_t seqnum;
#if defined(_M_IA64) || defined(_M_AMD64) || defined(_WIN64)
	size_t magic;
	size_t align128;
#else
	size_t magic;
#endif
} trace_header;

struct trace_info
{
	int sequence_number;
	size_t current;
	size_t peak;
	size_t total;
	size_t allocs;
	size_t mem_limit;
	size_t alloc_limit;
};

static struct trace_info trace_info = { 1, 0, 0, 0, 0, 0, 0 };

static void *hit_limit(void *val)
{
	return val;
}

static void *hit_memory_limit(struct trace_info *info, int is_malloc, size_t oldsize, size_t size)
{
	if (is_malloc)
		fz_error(ctx, "Memory limit (%zu) hit upon malloc(%zu) when %zu already allocated.", info->mem_limit, size, info->current);
	else
		fz_error(ctx, "Memory limit (%zu) hit upon realloc(%zu) from %zu bytes when %zu already allocated.", info->mem_limit, size, oldsize, info->current);
	return hit_limit(NULL);
}


static void *hit_alloc_limit(struct trace_info *info, int is_malloc, size_t oldsize, size_t size)
{
	if (is_malloc)
		fz_error(ctx, "Allocation limit (%zu) hit upon malloc(%zu) when %zu already allocated.", info->alloc_limit, size, info->current);
	else
		fz_error(ctx, "Allocation limit (%zu) hit upon realloc(%zu) from %zu bytes when %zu already allocated.", info->alloc_limit, size, oldsize, info->current);
	return hit_limit(NULL);
}

static void *
trace_malloc(void *arg, size_t size   FZDBG_DECL_ARGS)
{
	struct trace_info *info = (struct trace_info *) arg;
	trace_header *p;
	if (size == 0)
		return NULL;
	if (size > SIZE_MAX - sizeof(trace_header))
		return NULL;
	if (info->mem_limit > 0 && size > info->mem_limit - info->current)
		return hit_memory_limit(info, 1, 0, size);
	if (info->alloc_limit > 0 && info->allocs > info->alloc_limit)
		return hit_alloc_limit(info, 1, 0, size);
	p = _malloc_dbg(size + sizeof(trace_header), _NORMAL_BLOCK, trace_srcfile, trace_srcline);
	if (p == NULL)
		return NULL;
	p[0].size = size;
	p[0].magic = 0xEAD;
	p[0].seqnum = info->sequence_number++;
	info->current += size;
	info->total += size;
	if (info->current > info->peak)
		info->peak = info->current;
	info->allocs++;
	return (void *)&p[1];
}

static void
trace_free(void *arg, void *p_)
{
	struct trace_info *info = (struct trace_info *) arg;
	trace_header *p = (trace_header *)p_;

	if (p_ == NULL)
		return;

	size_t size = p[-1].size;
	int rotten = 0;
	info->current -= size;
	if (p[-1].magic != 0xEAD)
	{
		fz_error(ctx, "*!* double free! %d", (int)(p[-1].magic - 0xEAD));
		p[-1].magic++;
		rotten = 1;
	}
	if (rotten)
	{
		fz_error(ctx, "*!* corrupted heap record! %p", &p[-1]);
	}
	else
	{
		free(&p[-1]);
	}
}

static void *
trace_realloc(void *arg, void *p_, size_t size   FZDBG_DECL_ARGS)
{
	struct trace_info *info = (struct trace_info *) arg;
	trace_header *p = (trace_header *)p_;
	size_t oldsize;

	if (size == 0)
	{
		trace_free(arg, p_);
		return NULL;
	}

	if (p_ == NULL)
		return trace_malloc(arg, size   FZDBG_PASS);
	if (size > SIZE_MAX - sizeof(trace_header))
		return NULL;
	oldsize = p[-1].size;
	if (info->mem_limit > 0 && size > info->mem_limit - info->current + oldsize)
		return hit_memory_limit(info, 0, oldsize, size);
	if (info->alloc_limit > 0 && info->allocs > info->alloc_limit)
		return hit_alloc_limit(info, 0, oldsize, size);

	int rotten = 0;
	oldsize = p[-1].size;
	if (p[-1].magic != 0xEAD)
	{
		fz_error(ctx, "*!* double free! %d", (int)(p[-1].magic - 0xEAD));
		p[-1].magic++;
		rotten = 1;
	}
	if (rotten)
	{
		fz_error(ctx, "*!* corrupted heap record! %p", &p[-1]);
		return NULL;
	}
	else
	{
		p = _realloc_dbg(&p[-1], size + sizeof(trace_header), _NORMAL_BLOCK, trace_srcfile, trace_srcline);
		if (p == NULL)
			return NULL;
		info->current += size - oldsize;
		if (size > oldsize)
			info->total += size - oldsize;
		if (info->current > info->peak)
			info->peak = info->current;
		p[0].size = size;
		info->allocs++;
		return &p[1];
	}
}

#ifndef DISABLE_MUTHREADS
static void worker_thread(void *arg)
{
	worker_t *me = (worker_t *)arg;
	int band_start;

	do
	{
		DEBUG_THREADS(fz_info(ctx, "Worker %d waiting\n", me->num));
		mu_wait_semaphore(&me->start);
		band_start = me->band_start;
		DEBUG_THREADS(fz_info(ctx, "Worker %d woken for band_start %d\n", me->num, me->band_start));
		me->status = RENDER_OK;
		if (band_start >= 0)
		{
			me->status = drawband(me->ctx, NULL, me->list, me->ctm, me->tbounds, band_start, me->pix, &me->bit);
		}
		DEBUG_THREADS(fz_info(ctx, "Worker %d completed band_start %d (status=%d)\n", me->num, band_start, me->status));
		mu_trigger_semaphore(&me->stop);
	}
	while (band_start >= 0);
	DEBUG_THREADS(fz_info(ctx, "Worker %d shutting down\n", me->num));
}

static void bgprint_worker(void *arg)
{
	int pagenum;

	(void)arg;

	do
	{
		DEBUG_THREADS(fz_info(ctx, "BGPrint waiting\n"));
		mu_wait_semaphore(&bgprint.start);
		pagenum = bgprint.pagenum;
		DEBUG_THREADS(fz_info(ctx, "BGPrint woken for pagenum %d\n", pagenum));
		if (pagenum >= 0)
		{
			int start = gettime();
			fz_clean_cookie(ctx, &bgprint.cookie);
			bgprint.status = try_render_page(bgprint.ctx, pagenum, start, bgprint.interptime, bgprint.filename, 1, bgprint.solo, &bgprint.render);
		}
		DEBUG_THREADS(fz_info(ctx, "BGPrint completed page %d\n", pagenum));
		mu_trigger_semaphore(&bgprint.stop);
	}
	while (pagenum >= 0);
	DEBUG_THREADS(fz_info(ctx, "BGPrint shutting down\n"));
}
#endif

static void
read_resolution(const char *arg)
{
	char *sep = strchr(arg, ',');

	if (sep == NULL)
		sep = strchr(arg, 'x');
	if (sep == NULL)
		sep = strchr(arg, ':');
	if (sep == NULL)
		sep = strchr(arg, ';');

	x_resolution = fz_atoi(arg);
	if (sep && sep[1])
		y_resolution = fz_atoi(arg);
	else
		y_resolution = x_resolution;

	if (x_resolution <= 0 || y_resolution <= 0)
	{
		fprintf(stderr, "Ignoring invalid resolution\n");
		x_resolution =  X_RESOLUTION;
		y_resolution =  Y_RESOLUTION;
	}
}

static int
read_rotation(const char *arg)
{
	int i;

	if (strcmp(arg, "auto"))
	{
		return -1;
	}

	i = fz_atoi(arg);

	i = i % 360;
	if (i % 90 != 0)
	{
		fz_error(ctx, "Ignoring invalid rotation");
		i = 0;
	}

	return i;
}

static float humanize(size_t value, const char** unit)
{
	float result;
	if (value >= 1024 * 1024 * 1024.0f)
	{
		*unit = "G";
		result = value / (1024 * 1024 * 1024.0f);
	}
	else if (value >= 1024 * 1024.0f)
	{
		*unit = "M";
		result = value / (1024 * 1024.0f);
	}
	else if (value >= 1024.0f)
	{
		*unit = "k";
		result = value / 1024.0f;
	}
	else
	{
		*unit = "";
		result = value;
	}

	return result;
}

/* Reduced quality sub pix quantizer, intended to match pdfium. */
static void reduced_sub_pix_quantizer(float size, int *x, int *y)
{
	*x = 3;
	*y = 1;
}

static void mu_drop_context(void)
{
	if (muraster_is_toplevel_ctx)
	{
		if (trace_info.allocs && (trace_info.mem_limit || trace_info.alloc_limit || showmemory))
		{
			float total, peak, current;
			const char* total_unit;
			const char* peak_unit;
			const char* current_unit;

			ASSERT(ctx != NULL);

			total = humanize(trace_info.total, &total_unit);
			peak = humanize(trace_info.peak, &peak_unit);
			current = humanize(trace_info.current, &current_unit);

			fz_info(ctx, "Memory use total=%.2f%s peak=%.2f%s current=%.2f%s",
				total, total_unit, peak, peak_unit, current, current_unit);
			fz_info(ctx, "Allocations total=%zu", trace_info.allocs);

			// reset heap tracing after reporting: this atexit handler MAY be invoked multiple times!
			memset(&trace_info, 0, sizeof(trace_info));
		}
	}

	// WARNING: as we point `ctx` at the GLOBAL context in the app init phase, it MAY already be an INVALID
	// pointer reference by now!
	// 
	// WARNING: this assert fires when you run `mutool raster` (and probably other tools as well) and hit Ctrl+C
	// to ABORT/INTERRUPT the running application: the MSVC RTL calls this function in the atexit() handler
	// and the assert fires due to (ctx->error.top != ctx->error.stack).
	//
	// We are okay with that, as that scenario is an immediate abort anyway and the OS will be responsible
	// for cleaning up. That our fz_try/throw/catch exception stack hasn't been properly rewound at such times
	// is obvious, I suppose...
	ASSERT_AND_CONTINUE(!ctx || !fz_has_global_context() || (ctx->error.top == ctx->error.stack_base));

	if (ctx != __fz_get_RAW_global_context())
	{
		fz_drop_context(ctx); // also done here for those rare exit() calls inside the library code.
		ctx = NULL;
	}

	// nuke the locks last as they are still used by the heap free ('drop') calls in the lines just above!
	if (muraster_is_toplevel_ctx)
	{
		// as we registered a global context, we should clean the locks on it now
		// so the atexit handler won't have to bother with it.
		ASSERT_AND_CONTINUE(fz_has_global_context());
		if (fz_has_global_context())
		{
			ctx = fz_get_global_context();
			fz_drop_context_locks(ctx);
		}
		ctx = NULL;

		fz_drop_global_context();

#ifndef DISABLE_MUTHREADS
		fin_muraster_locks();
#endif /* DISABLE_MUTHREADS */

		muraster_is_toplevel_ctx = 0;
	}
}

#if !defined(MURASTER_STANDALONE) && defined(BUILD_MONOLITHIC)
#define main(cnt, arr)      muraster_main(cnt, arr)
#endif

int main(int argc, const char** argv)
{
	const char *password = "";
	int c;
	fz_alloc_context trace_alloc_ctx = { &trace_info, trace_malloc, trace_realloc, trace_free };
	fz_alloc_context *alloc_ctx = NULL;
	fz_locks_context *locks = NULL;
	size_t max_store = FZ_STORE_DEFAULT;

	// reset global vars: this tool MAY be re-invoked via bulktest or others and should RESET completely between runs:
	//mudraw_is_toplevel_ctx = 0;
	//ctx = NULL;
	output = NULL;
	out = NULL;

	output_format = NULL;

	rotation = -1;
	width = 0;
	height = 0;
	fit = 0;

	layout_w = FZ_DEFAULT_LAYOUT_W;
	layout_h = FZ_DEFAULT_LAYOUT_H;
	layout_em = FZ_DEFAULT_LAYOUT_EM;
	layout_css = NULL;
	layout_use_doc_css = 1;
	min_line_width = 0.0f;

	showtime = 0;
	showmemory = 0;

	memset(&trace_info, 0, sizeof trace_info);

	no_icc = 0;
	ignore_errors = 0;
	alphabits_text = 8;
	alphabits_graphics = 8;
	subpix_preset = 0;

	lowmemory = 0;

	verbosity = 1;
	errored = 0;
	files = 0;

	memset(&bgprint, 0, sizeof(bgprint));
	memset(&timing, 0, sizeof(timing));

	memset(&master_cookie, 0, sizeof(master_cookie));

	gettime_once = 1;

	// ---

	bgprint.active = 0;			/* set by -P */
	min_band_height = MIN_BAND_HEIGHT;
	max_band_memory = BAND_MEMORY;
	width = 0;
	height = 0;
	num_workers = NUM_RENDER_THREADS;
	x_resolution = X_RESOLUTION;
	y_resolution = Y_RESOLUTION;
	res_specified = 0;

	fz_getopt_reset();
	while ((c = fz_getopt(argc, argv, "p:o:F:R:r:w:h:fB:M:s:A:iW:H:S:T:U:XLvVPl:Nm:hJ:")) != -1)
	{
		switch (c)
		{
		default: return usage();

		case 'q': verbosity = 0; fz_default_error_warn_info_mode(1, 1, 1); break;
		case 'v': verbosity++; fz_default_error_warn_info_mode(0, 0, 0); break;

		case 'p': password = fz_optarg; break;

		case 'o': output = fz_optarg; break;
		case 'F': format = fz_optarg; break;

		case 'R': rotation = read_rotation(fz_optarg); break;
		case 'r': read_resolution(fz_optarg); res_specified = 1; break;
		case 'w': width = fz_atof(fz_optarg); break;
		case 'h': height = fz_atof(fz_optarg); break;
		case 'f': fit = 1; break;
		case 'B': min_band_height = atoi(fz_optarg); break;
		case 'M': max_band_memory = atoi(fz_optarg); break;
		case 'J': fz_default_png_compression_level(fz_atoi(fz_optarg)); break;

		case 'W': layout_w = fz_atof(fz_optarg); break;
		case 'H': layout_h = fz_atof(fz_optarg); break;
		case 'S': layout_em = fz_atof(fz_optarg); break;
		case 'U': layout_css = fz_optarg; break;
		case 'X': layout_use_doc_css = 0; break;

		case 's':
			if (strchr(fz_optarg, 't')) ++showtime;
			if (strchr(fz_optarg, 'm')) ++showmemory;
			break;

		case 'A':
		{
			char *sep;
			alphabits_graphics = atoi(fz_optarg);
			sep = strchr(fz_optarg, '/');
			if (sep)
			{
				alphabits_text = atoi(sep+1);
				sep = strchr(sep+1, '/');
				if (sep)
				{
					subpix_preset = atoi(sep+1);
				}
			}
			else
				alphabits_text = alphabits_graphics;
			break;
		}
		case 'l': min_line_width = fz_atof(fz_optarg); break;
		case 'i': ignore_errors = 1; break;
		case 'N': no_icc = 1; break;

		case 'T':
#ifndef DISABLE_MUTHREADS
			num_workers = fz_parse_pool_threadcount_preference(fz_optarg, 0, 0, 0);
			break;
#else
			fz_warn(ctx, "Threads not enabled in this build");
			break;
#endif
		case 'm':
			if (fz_optarg[0] == 's') trace_info.mem_limit = fz_atoi64(&fz_optarg[1]);
			else if (fz_optarg[0] == 'a') trace_info.alloc_limit = fz_atoi64(&fz_optarg[1]);
			else trace_info.mem_limit = fz_atoi64(fz_optarg);
			break;
		case 'L': lowmemory = 1; break;
		case 'P':
#ifndef DISABLE_MUTHREADS
			bgprint.active = 1;
			if (!num_workers)
				num_workers = fz_maxi(2, fz_get_cpu_core_count());
			break;
#else
			fz_warn(ctx, "Threads not enabled in this build");
			break;
#endif
		case 'V': fz_info(ctx, "muraster version %s", FZ_VERSION); return EXIT_FAILURE;
		}
	}

	if (width == 0)
		width = x_resolution * PAPER_WIDTH;

	if (height == 0)
		height = y_resolution * PAPER_HEIGHT;

	if (fz_optind == argc)
	{
		fz_error(ctx, "No files specified to process\n\n");
		return usage();
	}

	if (min_band_height <= 0)
	{
		fz_error(ctx, "Require a positive minimum band height");
		return EXIT_FAILURE;
	}

#ifndef DISABLE_MUTHREADS
	locks = init_muraster_locks();
	if (locks == NULL)
	{
		fz_error(ctx, "mutex initialisation failed");
		return EXIT_FAILURE;
	}
#endif

	if (trace_info.mem_limit || trace_info.alloc_limit || showmemory)
		alloc_ctx = &trace_alloc_ctx;

	if (lowmemory)
		max_store = 1;

	if (!fz_has_global_context())
	{
		ASSERT(ctx == NULL);
		
		ctx = fz_new_context(alloc_ctx, locks, max_store);
		if (!ctx)
		{
			fz_error(ctx, "cannot initialise MuPDF context");
			return EXIT_FAILURE;
		}
		fz_set_global_context(ctx);

		muraster_is_toplevel_ctx = 1;
	}

	// register a mupdf-aligned default heap memory manager for jpeg/jpeg-turbo
	fz_set_default_jpeg_sys_mem_mgr();

	atexit(mu_drop_context);

	if (ctx != __fz_get_RAW_global_context())
	{
		fz_drop_context(ctx); // drop our previous context IFF this happens to be a re-run in monolithic mode.
		ctx = NULL;
	}

	ctx = fz_new_context(NULL, NULL, max_store);
	if (!ctx)
	{
		fz_error(ctx, "cannot initialise MuPDF context");
		return EXIT_FAILURE;
	}

	fz_attach_cookie_to_context(ctx, &master_cookie);

	fz_try(ctx)
	{
		fz_set_text_aa_level(ctx, alphabits_text);
		fz_set_graphics_aa_level(ctx, alphabits_graphics);
		fz_set_graphics_min_line_width(ctx, min_line_width);
		if (subpix_preset)
			fz_set_graphics_sub_pix_quantizer(ctx, reduced_sub_pix_quantizer);
		if (no_icc)
			fz_disable_icc(ctx);
		else
			fz_enable_icc(ctx);

#ifndef DISABLE_MUTHREADS
		// do not bgprint when there won't be any bg threads available, ever.
		if (num_workers < 1)
		{
			bgprint.active = 0;
		}

		if (bgprint.active)
		{
			int fail = 0;
			bgprint.ctx = fz_clone_context(ctx);
			fz_attach_cookie_to_context(bgprint.ctx, &bgprint.cookie);
			fail |= mu_create_semaphore(&bgprint.start);
			fail |= mu_create_semaphore(&bgprint.stop);
			fail |= mu_create_thread(&bgprint.thread, bgprint_worker, NULL);
			if (fail)
			{
				fz_detach_cookie_from_context(bgprint.ctx);
				mu_destroy_semaphore(&bgprint.start);
				mu_destroy_semaphore(&bgprint.stop);
				fz_throw(bgprint.ctx, FZ_ERROR_GENERIC, "bgprint startup failed");
			}
		}

		if (num_workers > 0)
		{
			int i;
			int fail = 0;
			workers = fz_calloc(ctx, num_workers, sizeof(*workers));
			for (i = 0; i < num_workers; i++)
			{
				workers[i].ctx = fz_clone_context(ctx);
				workers[i].num = i;
				fz_attach_cookie_to_context(workers[i].ctx, &workers[i].cookie);
				fail |= mu_create_semaphore(&workers[i].start);
				fail |= mu_create_semaphore(&workers[i].stop);
				fail |= mu_create_thread(&workers[i].thread, worker_thread, &workers[i]);
			}
			if (fail)
			{
				for (i = 0; i < num_workers; i++)
				{
					fz_detach_cookie_from_context(workers[i].ctx);
					mu_destroy_semaphore(&workers[i].start);
					mu_destroy_semaphore(&workers[i].stop);
					mu_destroy_thread(&workers[i].thread);
					fz_drop_context(workers[i].ctx);
				}
				fz_free(ctx, workers);
				fz_throw(ctx, FZ_ERROR_GENERIC, "worker startup failed");
			}
		}
#endif /* DISABLE_MUTHREADS */

		if (layout_css)
		{
			fz_buffer *buf = fz_read_file(ctx, layout_css);
			fz_set_user_css(ctx, fz_string_from_buffer(ctx, buf));
			fz_drop_buffer(ctx, buf);
		}

		fz_set_use_document_css(ctx, layout_use_doc_css);

		// default output format: first slot in the lookup table:
		output_format = &suffix_table[0];

		if (format)
		{
			int i;

			for (i = 0; i < (int)nelem(suffix_table); i++)
			{
				if (!stricmp(format, suffix_table[i].suffix+1))
				{
					output_format = &suffix_table[i];
					break;
				}
			}
			if (i == (int)nelem(suffix_table))
			{
				fz_throw(ctx, FZ_ERROR_GENERIC, "Unknown output format '%s'", format);
			}
		}
		else if (output)
		{
			const char *suffix = fz_name_extension(output);
			int i;

			for (i = 0; i < (int)nelem(suffix_table); i++)
			{
				if (!stricmp(suffix, suffix_table[i].suffix))
				{
					output_format = &suffix_table[i];
					break;
				}
			}
		}

		switch (output_format->cs)
		{
		case CS_GRAY:
			colorspace = fz_device_gray(ctx);
			break;
		case CS_RGB:
			colorspace = fz_device_rgb(ctx);
			break;
		case CS_CMYK:
			colorspace = fz_device_cmyk(ctx);
			break;
		}

#if 0
		if (!output || *output == 0 || !strcmp(output, "-"))
		{
			// No need to set quiet mode when writing to stdout as all error/warn/info/debug info is sent via stderr!
#if 0
			verbosity = 0; /* automatically be quiet if printing to stdout */
			fz_default_error_warn_info_mode(1, 1, 1);
#endif

#ifdef _WIN32
			/* Windows specific code to make stdout binary. */
			setmode(fileno(stdout), O_BINARY);
#endif
			out = fz_stdout(ctx);
		}
		else
		{
			char file_path[PATH_MAX];
			fz_format_output_path(ctx, file_path, sizeof file_path, output, 0);
			fz_normalize_path(ctx, file_path, sizeof file_path, file_path);
			fz_sanitize_path(ctx, file_path, sizeof file_path, file_path);
			out = fz_new_output_with_path(ctx, file_path, 0);
		}
#endif

		timing.count = 0;
		timing.total = 0;
		timing.min = 1 << 30;
		timing.max = 0;
		timing.mininterp = 1 << 30;
		timing.maxinterp = 0;
		timing.minpage = 0;
		timing.maxpage = 0;
		timing.minfilename = "";
		timing.maxfilename = "";
		timing.layout = 0;
		timing.minlayout = 1 << 30;
		timing.maxlayout = 0;
		timing.minlayoutfilename = "";
		timing.maxlayoutfilename = "";
		if (showtime && bgprint.active)
			timing.total = gettime();

		fz_try(ctx)
		{
			fz_register_document_handlers(ctx);

			while (fz_optind < argc)
			{
				int layouttime;
				fz_document* doc = NULL;

				fz_var(doc);

				fz_try(ctx)
				{
					filename = argv[fz_optind++];
					files++;

					doc = fz_open_document(ctx, filename);

					if (fz_needs_password(ctx, doc))
					{
						if (!fz_authenticate_password(ctx, doc, password))
						fz_throw(ctx, FZ_ERROR_ARGUMENT, "cannot authenticate password: %s", filename);
					}

					layouttime = gettime();
					fz_layout_document(ctx, doc, layout_w, layout_h, layout_em);
					(void) fz_count_pages(ctx, doc);   // added to ensure a more proper layouttime figure
					layouttime = gettime() - layouttime;

					timing.layout += layouttime;
					if (layouttime < timing.minlayout)
					{
						timing.minlayout = layouttime;
						timing.minlayoutfilename = filename;
					}
					if (layouttime > timing.maxlayout)
					{
						timing.maxlayout = layouttime;
						timing.maxlayoutfilename = filename;
					}

					if (fz_optind == argc || !fz_is_page_range(ctx, argv[fz_optind]))
						drawrange(ctx, doc, "1-N");
					if (fz_optind < argc && fz_is_page_range(ctx, argv[fz_optind]))
						drawrange(ctx, doc, argv[fz_optind++]);
				}
				fz_always(ctx)
				{
					fz_drop_document(ctx, doc);
					doc = NULL;
				}
				fz_catch(ctx)
				{
					if (!ignore_errors)
					{
						abort_bgprint(ctx);

						fz_rethrow(ctx);
					}

					fz_report_error(ctx);
					fz_warn(ctx, "ignoring error in '%s'", filename);
				}
			}
		}
		fz_always(ctx)
		{
			finish_bgprint(ctx);
		}
		fz_catch(ctx)
		{
			fz_report_error(ctx);
			fz_log_error_printf(ctx, "cannot draw '%s'", filename);
			errored = 1;
		}
	}
	fz_always(ctx)
	{
		if (showtime)
		{
			if (timing.count > 0)
			{
				if (bgprint.active)
					timing.total = gettime() - timing.total;

				if (files == 1)
				{
					fz_info(ctx, "total %dms (%dms layout) / %d pages for an average of %dms",
						timing.total, timing.layout, timing.count, timing.total / timing.count);
					if (bgprint.active)
					{
						fz_info(ctx, "fastest page %d: %dms (interpretation) %dms (rendering) %dms(total)",
							timing.minpage, timing.mininterp, timing.min - timing.mininterp, timing.min);
						fz_info(ctx, "slowest page %d: %dms (interpretation) %dms (rendering) %dms(total)",
							timing.maxpage, timing.maxinterp, timing.max - timing.maxinterp, timing.max);
					}
					else
					{
						fz_info(ctx, "fastest page %d: %dms", timing.minpage, timing.min);
						fz_info(ctx, "slowest page %d: %dms", timing.maxpage, timing.max);
					}
				}
				else
				{
					fz_info(ctx, "total %dms (%dms layout) / %d pages for an average of %dms in %d files",
						timing.total, timing.layout, timing.count, timing.total / timing.count, files);
					fz_info(ctx, "fastest layout: %dms (%s)", timing.minlayout, timing.minlayoutfilename);
					fz_info(ctx, "slowest layout: %dms (%s)", timing.maxlayout, timing.maxlayoutfilename);
					fz_info(ctx, "fastest page %d: %dms (%s)", timing.minpage, timing.min, timing.minfilename);
					fz_info(ctx, "slowest page %d: %dms (%s)", timing.maxpage, timing.max, timing.maxfilename);
				}
			}

			fz_dump_lock_times(ctx, gettime());
		}

#ifndef DISABLE_MUTHREADS
		// bgprint also uses the workers, hence we MUST shut down bgprint BEFORE the workers themselves:
		if (bgprint.active)
		{
			bgprint.pagenum = -1;
			mu_trigger_semaphore(&bgprint.start);
			mu_wait_semaphore(&bgprint.stop);
			mu_destroy_semaphore(&bgprint.start);
			mu_destroy_semaphore(&bgprint.stop);
			mu_destroy_thread(&bgprint.thread);
			fz_drop_context(bgprint.ctx);
			bgprint.ctx = NULL;
			bgprint.active = 0;
		}

		if (num_workers > 0)
		{
			int i;
			DEBUG_THREADS(fz_info(ctx, "Asking workers to shutdown, then destroy their resources\n"));
			for (i = 0; i < num_workers; i++)
			{
				workers[i].band_start = -1;
				mu_trigger_semaphore(&workers[i].start);
				mu_wait_semaphore(&workers[i].stop);
				mu_destroy_semaphore(&workers[i].start);
				mu_destroy_semaphore(&workers[i].stop);
				mu_destroy_thread(&workers[i].thread);
				fz_drop_context(workers[i].ctx);
			}
			fz_free(ctx, workers);
		}
#endif /* DISABLE_MUTHREADS */
	}
	fz_catch(ctx)
	{
		fz_report_error(ctx);
		if (!errored) {
			fz_error(ctx, "Rendering failed.");
			errored = 1;
		}
	}

	if (!errored)
	{
		fz_close_output(ctx, out);
	}
	fz_drop_output(ctx, out);
	out = NULL;

	fz_flush_warnings(ctx);
	mu_drop_context();

	return errored;
}

#endif
