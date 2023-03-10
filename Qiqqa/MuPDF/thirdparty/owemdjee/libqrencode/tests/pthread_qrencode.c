#include <stdio.h>
#include <stdlib.h>
#if HAVE_CONFIG_H
#include "../config.h"
#endif
#ifdef HAVE_SYS_TIME_H
#include <sys/time.h>
#endif
#include <pthread.h>
#include <errno.h>
#include "../qrencode.h"

#define THREADS (10)

static pthread_t threads[THREADS];

#ifdef _MSC_VER
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
static LARGE_INTEGER startTime;
static LARGE_INTEGER frequency = { .QuadPart = 0 };
#else
static struct timeval tv;
#endif

static void timerStart(const char *str)
{
	printf("%s: START\n", str);
#ifdef _MSC_VER
	(void) QueryPerformanceCounter(&startTime);
#else
	gettimeofday(&tv, NULL);
#endif
}

static void timerStop(void)
{
#ifdef _MSC_VER
	LARGE_INTEGER endTime, elapsed;
	(void) QueryPerformanceCounter(&endTime);
	if (frequency.QuadPart == 0) {
		(void) QueryPerformanceFrequency(&frequency);
	}

	elapsed.QuadPart = endTime.QuadPart - startTime.QuadPart;
	elapsed.QuadPart *= 1000;
	elapsed.QuadPart /= frequency.QuadPart;

	printf("STOP: %lld msec\n", elapsed.QuadPart);
#else
	struct timeval tc;

	gettimeofday(&tc, NULL);
	printf("STOP: %ld msec\n", (tc.tv_sec - tv.tv_sec) * 1000
			+ (tc.tv_usec - tv.tv_usec) / 1000);
#endif
}

static void *encode_ver1to10(void *arg)
{
	QRcode *code;
	int i;
	int version;
	static const char *data = "This is test.";

	for(i=0; i<500; i++) {
		for(version = 0; version < 11; version++) {
			code = QRcode_encodeString(data, version, QR_ECLEVEL_L, QR_MODE_8, 0);
			if(code == NULL) {
				perror("Failed to encode:");
			} else {
				QRcode_free(code);
			}
		}
	}

	return NULL;
}

static void prof_ver1to10(void)
{
	int i;

	timerStart("Version 1 - 10 (500 symbols for each)");
	for(i=0; i<THREADS; i++) {
		pthread_create(&threads[i], NULL, encode_ver1to10, NULL);
	}
	for(i=0; i<THREADS; i++) {
		pthread_join(threads[i], NULL);
	}
	timerStop();
}

static void *encode_ver31to40(void *arg)
{
	QRcode *code;
	int i;
	int version;
	static const char *data = "This is test.";

	for(i=0; i<50; i++) {
		for(version = 31; version < 41; version++) {
			code = QRcode_encodeString(data, version, QR_ECLEVEL_L, QR_MODE_8, 0);
			if(code == NULL) {
				perror("Failed to encode:");
			} else {
				QRcode_free(code);
			}
		}
	}

	return NULL;
}

static void prof_ver31to40(void)
{
	int i;

	timerStart("Version 31 - 40 (50 symbols for each)");
	for(i=0; i<THREADS; i++) {
		pthread_create(&threads[i], NULL, encode_ver31to40, NULL);
	}
	for(i=0; i<THREADS; i++) {
		pthread_join(threads[i], NULL);
	}
	timerStop();
}


#if defined(BUILD_MONOLITHIC)
#define main      qrencode_pthread_test_main
#endif

int main(void)
{
	prof_ver1to10();
	prof_ver31to40();

	return 0;
}
