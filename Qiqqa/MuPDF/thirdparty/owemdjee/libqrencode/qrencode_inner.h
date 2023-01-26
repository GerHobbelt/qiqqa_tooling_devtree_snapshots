/**
 * qrencode - QR Code encoder
 *
 * Header for test use
 * Copyright (C) 2006-2017 Kentaro Fukuchi <kentaro@fukuchi.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifndef QRENCODE_INNER_H
#define QRENCODE_INNER_H

/**
 * This header file includes definitions for test use.
 */

/******************************************************************************
 * Raw code
 *****************************************************************************/

typedef struct {
	int dataLength;
	int eccLength;
	unsigned char *data;
	unsigned char *ecc;
} RSblock;

typedef struct {
	int version;
	int dataLength;
	int eccLength;
	unsigned char *datacode;
	unsigned char *ecccode;
	int b1;
	int blocks;
	RSblock *rsblock;
	int count;
} QRRawCode;

QRRawCode *QRraw_new(QRinput *input);
unsigned char QRraw_getCode(QRRawCode *raw);
void QRraw_free(QRRawCode *raw);

/******************************************************************************
 * Raw code for Micro QR Code
 *****************************************************************************/

typedef struct {
	int version;
	int dataLength;
	int eccLength;
	unsigned char *datacode;
	unsigned char *ecccode;
	RSblock *rsblock;
	int oddbits;
	int count;
} MQRRawCode;

MQRRawCode *MQRraw_new(QRinput *input);
unsigned char MQRraw_getCode(MQRRawCode *raw);
void MQRraw_free(MQRRawCode *raw);

/******************************************************************************
 * Frame filling
 *****************************************************************************/
unsigned char *FrameFiller_test(int version);
unsigned char *FrameFiller_testMQR(int version);

/******************************************************************************
 * QR-code encoding
 *****************************************************************************/
QRcode *QRcode_encodeMask(QRinput *input, int mask);
QRcode *QRcode_encodeMaskMQR(QRinput *input, int mask);
#ifdef WITH_TESTS
QRcode *QRcode_new(int version, int width, unsigned char *data);
#endif

#endif /* QRENCODE_INNER_H */
