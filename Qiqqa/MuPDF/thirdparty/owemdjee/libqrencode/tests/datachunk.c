#if HAVE_CONFIG_H
#include "../config.h"
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef HAVE_ICONV_H
#include <iconv.h>
#endif
#include "datachunk.h"

DataChunk *DataChunk_new(QRencodeMode mode)
{
	DataChunk *chunk;

	chunk = (DataChunk *)calloc(1, sizeof(DataChunk));
	if(chunk == NULL) return NULL;

	chunk->mode = mode;

	return chunk;
}

void DataChunk_free(DataChunk *chunk)
{
	if(chunk) {
		if(chunk->data) free(chunk->data);
		free(chunk);
	}
}

void DataChunk_freeList(DataChunk *list)
{
	DataChunk *next;

	while(list != NULL) {
		next = list->next;
		DataChunk_free(list);
		list = next;
	}
}

static void dumpNum(DataChunk *chunk)
{
	printf("%s\n", chunk->data);
}

static void dumpAn(DataChunk *chunk)
{
	printf("%s\n", chunk->data);
}

static void dump8(DataChunk *chunk)
{
	size_t i, j;
	unsigned char c;
	size_t count = 0;
	unsigned char buf[16];

	for(i=0; i<chunk->size; i++) {
		buf[count] = chunk->data[i];
		c = chunk->data[i];
		if(c >= ' ' && c <= '~') {
			putchar(c);
		} else {
			putchar('.');
		}
		count++;

		if(count >= 16) {
			putchar(' ');
			for(j=0; j<16; j++) {
				printf(" %02x", buf[j]);
			}
			count = 0;
			putchar('\n');
		}
	}
	if(count > 0) {
		for(i=0; i<16 - count; i++) {
			putchar(' ');
		}
		putchar(' ');
		for(j=0; j<count; j++) {
			printf(" %02x", buf[j]);
		}
		count = 0;
		putchar('\n');
	}
}

#ifdef HAVE_ICONV_H

static void dumpKanji(DataChunk *chunk)
{
	iconv_t conv;
	char *inbuf, *outbuf, *outp;
	size_t inbytes, outbytes, ret;

	conv = iconv_open("UTF-8", "SHIFT_JIS");
	inbytes = chunk->size;
	inbuf = (char *)chunk->data;
	outbytes = inbytes * 4 + 1;
	outbuf = (char *)malloc(inbytes * 4 + 1);
	outp = outbuf;
	ret = iconv(conv, &inbuf, &inbytes, &outp, &outbytes);
	if(ret == (size_t) -1) { perror(NULL); }
	*outp = '\0';

	printf("%s\n", outbuf);

	iconv_close(conv);
	free(outbuf);
}

#endif

static void dumpChunk(DataChunk *chunk)
{
	switch(chunk->mode) {
		case QR_MODE_NUM:
			printf("Numeric: %zu bytes\n", chunk->size);
			dumpNum(chunk);
			break;
		case QR_MODE_AN:
			printf("AlphaNumeric: %zu bytes\n", chunk->size);
			dumpAn(chunk);
			break;
		case QR_MODE_8:
			printf("8-bit data: %zu bytes\n", chunk->size);
			dump8(chunk);
			break;
		case QR_MODE_KANJI:
#ifdef HAVE_ICONV_H
			printf("Kanji: %zu bytes\n", chunk->size);
			dumpKanji(chunk);
#else
			printf("Kanji dump is not supported in this version (iconv is not built-in)\n");
#endif
			break;
		case QR_MODE_NUL:
		case QR_MODE_STRUCTURE:
		case QR_MODE_ECI:
		case QR_MODE_FNC1FIRST:
		case QR_MODE_FNC1SECOND:
			printf("Invalid or reserved: %zu bytes\n", chunk->size);
			dump8(chunk);
			break;
	}
}

void DataChunk_dumpChunkList(DataChunk *list)
{
	while(list != NULL) {
		dumpChunk(list);
		list = list->next;
	}
}

int DataChunk_totalSize(DataChunk *list)
{
	int size = 0;

	while(list != NULL) {
		size += list->size;
		list = list->next;
	}

	return size;
}

unsigned char *DataChunk_concatChunkList(DataChunk *list, int *retsize)
{
	int size, idx;
	unsigned char *data;

	size = DataChunk_totalSize(list);
	if(size <= 0) return NULL;

	data = (unsigned char *)malloc((size_t)size + 1);
	idx = 0;
	while(list != NULL) {
		memcpy(&data[idx], list->data, list->size);
		idx += list->size;
		list = list->next;
	}
	data[size] = '\0';

	*retsize = size;
	return data;
}
