/*
 * utf8_test.c
 *
 * Copyright (c) 2012-2018
 *
 * Source code released under the GPL version 2
 *
 */
#include "cross_platform_porting.h"
#include <stdio.h>
#include <stdlib.h>
#ifdef HAVE_DIRENT_H
#include <dirent.h>
#else
// ripped from https://github.com/tronkko/dirent
#include "../win32/include/dirent.h"
#endif
#ifdef HAVE_IO_H
#include <io.h>
#endif
#ifdef HAVE_DIRECT_H
#include <direct.h>
#endif
#include <string.h>
#include <sys/stat.h>
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#include <limits.h>

#include "bibutils.h"
#include "bibformats.h"
#include "tomods.h"
#include "bibprog.h"
#include "measure_time.h"

#ifdef BUNDLE_BIBUTILS_TESTS
#include "bibutils_tests.h"
#endif

#include "monolithic_examples.h"


#ifndef F_OK
#define F_OK 0
#endif


#ifndef MAX
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#endif


static const char progname[] = "bibutils_test";

#if defined(BUILD_MONOLITHIC)
#define main     bibutils_test_main
#endif

// Based on http://nion.modprobe.de/blog/archives/357-Recursive-directory-creation.html

static int mkdirRecursiveForFile(const char* path) {
    char opath[MAX(PATH_MAX + 1, 2048)];
    char* p;
    size_t len;

    strncpy_s(opath, countof(opath), path, strlen(path));
    opath[sizeof(opath) - 1] = '\0';
    len = strlen(opath);
    if (len == 0)
        return 0;
#if 0
    else if (strchr("/\\", opath[len - 1]))
        opath[len - 1] = '\0';
#endif
    for (p = opath; *p; p++) {
        if (strchr("/\\", *p)) {
            *p = '\0';
            if (_access_s(opath, F_OK)) {
                _mkdir(opath);
            }
            *p = '/';
        }
    }
#if 0
    if (_access_s(opath, F_OK)) {         /* if path is not terminated with / */
        _mkdir(opath);
    }
#endif
    return 0;
}

struct closure {
    const char* srcfile;
    const char* dstfile;
    int subpart_offset;
    int dst_subpart_offset;

    param* p;

    bibl b;
    errno_t err;
};

// int measure(work_fn work, report_fn report, void* closure);

static int loadIntoBibl(const char *title, struct closure* closure)
{
    FILE* fp;

    bibl_init(&closure->b);

    fprintf(stderr, "%s: Processing input file '%s'...\n", title, closure->srcfile + closure->subpart_offset);

    closure->err = fopen_s(&fp, closure->srcfile, "r");
    if (fp) {
        closure->err = bibl_read(&closure->b, fp, closure->srcfile, closure->p);
        if (closure->err) bibl_reporterr(closure->err);
        fclose(fp);
    }
    else {
        bibl_reporterr(closure->err);
    }
    return closure->err;
}

static int storeFromBibl(const char *title, struct closure* closure)
{
    FILE* fp;

    fprintf(stderr, "%s: Writing processed data to output file '%s'...\n", title, closure->dstfile + closure->dst_subpart_offset);

    closure->err = mkdirRecursiveForFile(closure->dstfile);
    if (closure->err) {
        return closure->err;
    }

    closure->err = fopen_s(&fp, closure->dstfile, "w");
    if (fp) {
        closure->err = bibl_write(&closure->b, fp, closure->p);
        if (closure->err) bibl_reporterr(closure->err);
        fclose(fp);
    }
    else {
        bibl_reporterr(closure->err);
    }
    if (closure->p->progname) fprintf(stderr, "%s: ", closure->p->progname);
    fprintf(stderr, "Processed %ld references.\n", closure->b.n);
    bibl_free(&closure->b);
    return EXIT_SUCCESS;
}

static int workReporter(double ms, const char* title, struct closure* closure)
{
    fprintf(stderr, "\n%s: ***** task '%s' took %0.3lf msecs to run. *****\n\n", title, closure->srcfile + closure->subpart_offset, ms);
    return 0;
}

// rip & patch from bibprog():
static int bibprog2(const char* srcfile, const char* dstfile, int subpart_filepath_offset, int dstsubpart_filepath_offset, param* p)
{
    struct closure closure = {
        .srcfile = srcfile,
        .dstfile = dstfile,
        .subpart_offset = subpart_filepath_offset,
        .dst_subpart_offset = dstsubpart_filepath_offset,
        .p = p
    };

    int rv = measure(loadIntoBibl, workReporter, "LOAD.DATA", &closure);

    if (!rv) {
        rv += measure(storeFromBibl, workReporter, "SAVE.XML", &closure);
    }

    return rv;
}

static int process_input_file(const char* filepath, const char* filepath_subtree_part, struct dirent* ent)
{
    // ignore hidden dot files:
    if (ent->d_name[0] == '.') return EXIT_SUCCESS;

    str dst;
    str_initstrc(&dst, filepath);
    str_findreplace(&dst, "inputs", "outputs");
    if (0 == strcmp(str_cstr(&dst), filepath)) {
        fprintf(stderr, "Input path must point to a file inside a 'inputs' directory somewhere; output will then be written to the equivalent 'outputs' directory.");
        return EXIT_FAILURE;
    }
    str_strcatc(&dst, ".xml");
    int offset = filepath_subtree_part - filepath;
    int dstoffset = offset + strlen("outputs") - strlen("inputs");

    const char *dstpath = str_cstr(&dst);

    const char* ext = strrchr(ent->d_name, '.');
    if (strcasecmp(ext, ".bib") == 0) {
        param p;
        bibtexin_initparams(&p, progname);
        modsout_initparams(&p, progname);
        const char* argv[] = {
            progname,
            filepath,
            NULL
        };
        int argc = countof(argv) - 1;
        int rc = tomods_processargs(&argc, argv, &p, NULL, NULL);
		if (rc < 0)
			return EXIT_FAILURE;
        rc = bibprog2(filepath, dstpath, offset, dstoffset, &p);
        bibl_freeparams(&p);
		if (rc)
			return EXIT_FAILURE;
		return EXIT_SUCCESS;
    }
    else if (strcasecmp(ext, ".biblatex") == 0) {
        param p;
        biblatexin_initparams(&p, progname);
        modsout_initparams(&p, progname);
        const char* argv[] = {
            progname,
            filepath,
            NULL
        };
        int argc = countof(argv) - 1;
        int rc = tomods_processargs(&argc, argv, &p, NULL, NULL);
		if (rc < 0)
			return EXIT_FAILURE;
		rc = bibprog2(filepath, dstpath, offset, dstoffset, &p);
        bibl_freeparams(&p);
		if (rc)
			return EXIT_FAILURE;
		return EXIT_SUCCESS;
    }

    printf("Don't know how to process '%s' input file: %s", ext + 1, filepath);
    return EXIT_FAILURE;
}

static int scan_dirtree(const char* base, const char *subtree_part)
{
    struct dirent** files;
    int i;
    int n;
    int rv = 0;

    /* Scan files in directory */
    n = scandir(base, &files, NULL, alphasort);
    if (n >= 0) {
        /* Loop through file names */
        for (i = 0; i < n; i++) {
            struct dirent* ent;

            /* Get pointer to file entry */
            ent = files[i];

            char filepath[MAX(PATH_MAX + 1, 2048)];
            sprintf_s(filepath, countof(filepath), "%s%s%s", base, (strchr("/\\", base[strlen(base) - 1]) ? "" : "/"), ent->d_name);
            const char* filepath_subtree_part = filepath + (subtree_part ? subtree_part - base : strlen(base) + (strchr("/\\", base[strlen(base) - 1]) ? 0 : 1));

            /* Output file name */
            switch (ent->d_type) {
            case DT_REG:
                printf("%s\n", filepath_subtree_part);
                rv += process_input_file(filepath, filepath_subtree_part, ent);
                continue;

            case DT_DIR:
                if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0) continue;
                printf("%s/\n", filepath_subtree_part);
                rv += scan_dirtree(filepath, filepath_subtree_part);
                continue;

            case DT_LNK:
                printf("%s@\n", filepath_subtree_part);
                continue;

            default:
                printf("%s*\n", filepath_subtree_part);
                continue;
            }
        }

        /* Release file names */
        for (i = 0; i < n; i++) {
            free(files[i]);
        }
        free(files);
        return rv;
    }
    else {
        char errbuf[4096];
        strerror_s(errbuf, countof(errbuf), errno);
        fprintf(stderr, "Cannot open %s (%s)\n", base, errbuf);
        return EXIT_FAILURE;
    }
}

int main(int argc, const char** argv)
{
	int failed = 0;
#ifndef BUNDLE_BIBUTILS_TESTS
	printf("FAIL: the bibutils unit tests have not been included in this test.");
	failed += 1;
#else
	failed += utf8_test();
	failed += str_test();
	failed += intlist_test();
	failed += slist_test();
	failed += vplist_test();
	failed += entities_test();
	failed += doi_test();
#endif

    if (argc < 2) {
        printf("FAILED: Must specify base directory to test files as commandline argument.");
        failed += 1;
    }
    else {
        failed += scan_dirtree(argv[1], NULL);
    }

	if ( !failed ) {
		printf( "%s: PASSED\n", progname );
		return EXIT_SUCCESS;
	} else {
		printf( "%s: FAILED\n", progname );
		return EXIT_FAILURE;
	}
}

