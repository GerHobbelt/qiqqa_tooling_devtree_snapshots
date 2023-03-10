
/*
 * Copyright (c) 2012, Frank Warmerdam <warmerdam@pobox.com>
 *
 * Permission to use, copy, modify, distribute, and sell this software and 
 * its documentation for any purpose is hereby granted without fee, provided
 * that (i) the above copyright notices and this permission notice appear in
 * all copies of the software and related documentation, and (ii) the names of
 * Sam Leffler and Silicon Graphics may not be used in any advertising or
 * publicity relating to the software without the specific, prior written
 * permission of Sam Leffler and Silicon Graphics.
 * 
 * THE SOFTWARE IS PROVIDED "AS-IS" AND WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS, IMPLIED OR OTHERWISE, INCLUDING WITHOUT LIMITATION, ANY 
 * WARRANTY OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.  
 * 
 * IN NO EVENT SHALL SAM LEFFLER OR SILICON GRAPHICS BE LIABLE FOR
 * ANY SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY KIND,
 * OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
 * WHETHER OR NOT ADVISED OF THE POSSIBILITY OF DAMAGE, AND ON ANY THEORY OF 
 * LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE 
 * OF THIS SOFTWARE.
 */

/*
 * TIFF Library
 *
 * -- Module copied from custom_dir.c --
 *===========  Purpose ===================================================================================
 * Test DoubleToRational() function interface and accuracy
 *
 */




#pragma warning( disable : 4101)

#include "tif_config.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <errno.h>

#ifdef HAVE_UNISTD_H 
# include <unistd.h> 
#endif 

#include "tiffio.h"
#include "tiffiop.h"
#include "tif_dir.h"
#include "tifftest.h"

#include "ElapseTimer.hpp"

 /*--: Rational2Double: limits.h for definition of ULONG_MAX etc. */
//#include <stdio.h>
//#include <stdlib.h>
//#include <math.h>
#include <float.h>
#include <limits.h>

/* Defines from  tif_dirwrite.c */
void DoubleToRational(double f, uint32 *num, uint32 *denom);
void DoubleToSrational(double f, int32 *num, int32 *denom);
void DoubleToRational_direct(double value, unsigned long *num, unsigned long *denom);
void DoubleToSrational_direct(double value, long *num, long *denom);

/* Defines from original functions at end of this module */
void DoubleToRational2(double f, uint32 *num, uint32 *denom);
void DoubleToSrational2(double f, int32 *num, int32 *denom);
void DoubleToRationalOld(double f, unsigned long *num, unsigned long *denom);
void DoubleToSrationalOld(double f, long *num, long *denom);


void printFile(FILE* fpFile, int idx, double dblIn, long long uNum, long long uDenom, long long uNumOld, long long uDenomOld, long long uNum3, long long uDenom3)
{
	double auxDouble, auxDoubleOld;
	double dblDiff, dblDiffToDouble, dblDiffToDoubleOld, dblDiffToDouble3;
	int		oldBetter;
	if (fpFile != NULL) {
		auxDouble = (double)uNum / (double)uDenom;
		auxDoubleOld = (double)uNumOld / (double)uDenomOld;
		dblDiff = auxDoubleOld - auxDouble;
		dblDiffToDouble = auxDouble - dblIn;
		dblDiffToDoubleOld = auxDoubleOld - dblIn;
		dblDiffToDouble3 = (double)uNum3 / (double)uDenom3 - dblIn;
		oldBetter = 0;
		if (fabs(dblDiffToDouble) < fabs(dblDiffToDoubleOld)) oldBetter = 1;
		if (fabs(dblDiffToDouble) > fabs(dblDiffToDoubleOld)) oldBetter = 2;
		if (fabs(dblDiffToDouble) > fabs(dblDiffToDouble3) && fabs(dblDiffToDoubleOld) > fabs(dblDiffToDouble3)) oldBetter = 3;
		fprintf(fpFile, "\n%4d:%26.12f -> %14lld / %12lld = %24.12f diff=%15.8e |  %14lld / %12lld = %24.12f diff=%15.8e | %d", idx, dblIn, uNum, uDenom, auxDouble, dblDiffToDouble, uNumOld, uDenomOld, auxDoubleOld, dblDiffToDoubleOld, oldBetter);
		if (oldBetter == 3) fprintf(fpFile, " | %14lld / %12lld = %24.12f diff=%15.8e", uNum3, uDenom3, (double)uNum3 / (double)uDenom3, dblDiffToDouble3);
	}
}

int
main()
{
	static const char filename[] = "DoubleToRational_Test.txt";
	FILE *			fpFile;

	int				ret, i;
	int				errorNo;
	float			auxFloat;
	double			dblIn;
	double			auxDouble = 0.0;
	double			auxDoubleOld = 0.0;

	uint32			uNum, uDenom;
	int32			sNum, sDenom;
	uint32			uNumOld, uDenomOld;
	int32			sNumOld, sDenomOld;
	uint32			uNum3, uDenom3;
	int32			sNum3, sDenom3;

#define N_SIZE  2000

	double		auxDoubleArrayW[2 * N_SIZE];
	double		dblDiff, dblDiffLimit;
	double		dblDiffToDouble, dblDiffToDoubleOld;
	float		fltDiff, fltDiffLimit;
#define RATIONAL_EPS (1.0/30000.0) /* reduced difference of rational values, approx 3.3e-5 */

	ElapseTimer eTimer;
	double		dblElapsedTm[30*N_SIZE];
	int			iTm = 0;

	/*-- Fill test data arrays for writing ----------- */
	/* special values */
	i = 0;
	auxDoubleArrayW[i] = 5.0 / 2.0; i++;
	//auxDoubleArrayW[i] = 13.0 / 7.0; i++;
	auxDoubleArrayW[i] = (double)0x7FFFFFFFU; i++;
	auxDoubleArrayW[i] = (double)0xFFFFFFFFU; i++;
	auxDoubleArrayW[i] = 3.1415926535897932384626433832795f; i++; /* PI in float-precision */
	auxDoubleArrayW[i] = 3.1415926535897932384626433832795; i++;  /* PI in double-precision */
	auxDoubleArrayW[i] = sqrt(2.0); i++;
	//auxDoubleArrayW[i] = (13.0 / 7.0)*34535353.0; i++;
	assert(i < N_SIZE); /* check, if i is still in range of array */
	for (; i < N_SIZE/2; i++) {
		auxDoubleArrayW[i] = (double)((i + 1) * 36897) / 4.5697;
	}
int stop = 1817; /*debugging*/
	for (; i < N_SIZE; i++) {
		if (i == stop) /*debugging*/
			int a = 2;
		auxDouble = (4.0*(double)ULONG_MAX / (double)N_SIZE);
		auxDoubleArrayW[i] = (double)i * auxDouble / 4.3;
		auxDoubleArrayW[i] = (double)(i * 4.0 * ULONG_MAX/N_SIZE) / 4.3;
		//if (auxDoubleArrayW[i] > 3633742097.0)
	}

	/*-- Output file -- */
	fpFile = NULL;
	fpFile = fopen(filename, "at");
	fprintf(fpFile, "\n\n=======================================================");


	/*-- compare old and new routines --*/
	for (i = 0; i < N_SIZE; i++) {
		if (i==stop) /*debugging*/
				int b = 2;
		/*-- UN-Signed --*/
		dblIn = auxDoubleArrayW[i];
		eTimer.Duration(true);
		DoubleToRational2(auxDoubleArrayW[i], &uNum, &uDenom);
		dblElapsedTm[iTm] = eTimer.Duration(true); iTm++;
		DoubleToRationalOld(auxDoubleArrayW[i], (unsigned long *)&uNumOld, (unsigned long *)&uDenomOld);
		dblElapsedTm[iTm] = eTimer.Duration(true); iTm++;
		DoubleToRational_direct(auxDoubleArrayW[i], (unsigned long *)&uNum3, (unsigned long *)&uDenom3);
		dblElapsedTm[iTm] = eTimer.Duration(true); iTm++;
		auxDouble = (double)uNum / (double)uDenom;
		auxDoubleOld = (double)uNumOld / (double)uDenomOld;
		dblDiff = auxDoubleOld - auxDouble;
		dblDiffToDouble = auxDouble - dblIn;
		dblDiffToDoubleOld = auxDoubleOld - dblIn;
		//if (uNum != uNumOld || uDenom != uDenomOld || fabs(dblDiff) > RATIONAL_EPS || _isnan(dblDiff)) {
		//	printf("DoubleToRational unterschied f?r %f (%f): New= %d / %d; Old = %d / %d", auxDoubleArrayW[i], dblDiff, uNum, uDenom, uNumOld, uDenomOld);
		//}
		printFile(fpFile, i, dblIn, uNum, uDenom, uNumOld, uDenomOld, uNum3, uDenom3);
		/*-- Reciprocal --*/
		dblIn = 1.0 / auxDoubleArrayW[i];
		eTimer.Duration(true);
		DoubleToRational2(dblIn, &uNum, &uDenom);
		dblElapsedTm[iTm] = eTimer.Duration(true); iTm++;
		DoubleToRationalOld(dblIn, (unsigned long *)&uNumOld, (unsigned long *)&uDenomOld);
		dblElapsedTm[iTm] = eTimer.Duration(true); iTm++;
		DoubleToRational_direct(auxDoubleArrayW[i], (unsigned long *)&uNum3, (unsigned long *)&uDenom3);
		dblElapsedTm[iTm] = eTimer.Duration(true); iTm++;
		auxDouble = (double)uNum / (double)uDenom;
		auxDoubleOld = (double)uNumOld / (double)uDenomOld;
		dblDiff = auxDoubleOld - auxDouble;
		dblDiffToDouble = auxDouble - dblIn;
		dblDiffToDoubleOld = auxDoubleOld - dblIn;
		//if (uNum != uNumOld || uDenom != uDenomOld || fabs(dblDiff) > RATIONAL_EPS || _isnan(dblDiff)) {
		//	printf("DoubleToRational unterschied f?r %f (%f): New= %d / %d; Old = %d / %d", dblIn, dblDiff, uNum, uDenom, uNumOld, uDenomOld);
		//}
		printFile(fpFile, i, dblIn, uNum, uDenom, uNumOld, uDenomOld, uNum3, uDenom3);

		/*-- Signed --*/
		dblIn = -1.0 * auxDoubleArrayW[i];
		eTimer.Duration(true);
		DoubleToSrational2(dblIn, &sNum, &sDenom);
		dblElapsedTm[iTm] = eTimer.Duration(true); iTm++;
		DoubleToSrationalOld(dblIn, (long *)&sNumOld, (long *)&sDenomOld);
		dblElapsedTm[iTm] = eTimer.Duration(true); iTm++;
		DoubleToSrational_direct(auxDoubleArrayW[i], (long *)&sNum3, (long *)&sDenom3);
		dblElapsedTm[iTm] = eTimer.Duration(true); iTm++;
		auxDouble = (double)sNum / (double)sDenom;
		auxDoubleOld = (double)sNumOld / (double)sDenomOld;
		dblDiff = auxDoubleOld - auxDouble;
		dblDiffToDouble = auxDouble - dblIn;
		dblDiffToDoubleOld = auxDoubleOld - dblIn;
		//if (sNum != sNumOld || sDenom != sDenomOld || fabs(dblDiff) > RATIONAL_EPS || _isnan(dblDiff)) {
		//	printf("DoubleToRational unterschied f?r %f (%f): New= %d / %d; Old = %d / %d", dblIn, dblDiff, sNum, sDenom, sNumOld, sDenomOld);
		//}
		printFile(fpFile, i, dblIn, sNum, sDenom, sNumOld, sDenomOld, sNum3, sDenom3);
		/*-- Signed - Reciprocal --*/
		dblIn = -1.0 / auxDoubleArrayW[i];
		eTimer.Duration(true);
		DoubleToSrational2(dblIn, &sNum, &sDenom);
		dblElapsedTm[iTm] = eTimer.Duration(true); iTm++;
		DoubleToSrationalOld(dblIn, (long *)&sNumOld, (long *)&sDenomOld);
		dblElapsedTm[iTm] = eTimer.Duration(true); iTm++;
		DoubleToSrational_direct(auxDoubleArrayW[i], (long *)&sNum3, (long *)&sDenom3);
		dblElapsedTm[iTm] = eTimer.Duration(true); iTm++;
		auxDouble = (double)sNum / (double)sDenom;
		auxDoubleOld = (double)sNumOld / (double)sDenomOld;
		dblDiff = auxDoubleOld - auxDouble;
		dblDiffToDouble = auxDouble - dblIn;
		dblDiffToDoubleOld = auxDoubleOld - dblIn;
		//if (sNum != sNumOld || sDenom != sDenomOld || fabs(dblDiff) > RATIONAL_EPS || _isnan(dblDiff)) {
		//	printf("DoubleToRational unterschied f?r %f (%f): New= %d / %d; Old = %d / %d", dblIn, dblDiff, sNum, sDenom, sNumOld, sDenomOld);
		//}
		printFile(fpFile, i, dblIn, sNum, sDenom, sNumOld, sDenomOld, sNum3, sDenom3);
	}



	fclose(fpFile);

} /* main() */




//#define DOUBLE2RAT_DEBUGOUTPUT
   /** -----  Rational2Double: Double To Rational Conversion ----------------------------------------------------------
   * There is a mathematical theorem to convert real numbers into a rational (integer fraction) number.
   * This is called "continuous fraction" which uses the Euclidean algorithm to find the greatest common divisor (GCD).
   *  (ref. e.g. https://de.wikipedia.org/wiki/Kettenbruch or https://en.wikipedia.org/wiki/Continued_fraction
   *             https://en.wikipedia.org/wiki/Euclidean_algorithm)
   * The following functions implement the 
   * - ToRationalEuclideanGCD()		auxiliary function which mainly implements euclidian GCD
   * - DoubleToRational()			conversion function for un-signed rationals
   * - DoubleToSrational()			conversion function for signed rationals
   ------------------------------------------------------------------------------------------------------------------*/

/**---- ToRationalEuclideanGCD() -----------------------------------------
 * Calculates the rational fractional of a double input value
 * using the Euclidean algorithm to find the greatest common divisor (GCD)
------------------------------------------------------------------------*/
void ToRationalEuclideanGCD(double value, int blnUseSignedRange, int blnUseSmallRange, unsigned long long *ullNum, unsigned long long *ullDenom)
{
	/* Internally, the integer variables can be bigger than the external ones,
	* as long as the result will fit into the external variable size.
	*/
	unsigned long long val, numSum[3] = { 0, 1, 0 }, denomSum[3] = { 1, 0, 0 };
	unsigned long long aux, bigNum, bigDenom;
	unsigned long long returnLimit;
	int i;
	unsigned long long nMax;
	double fMax;
	unsigned long maxDenom;
	/*-- nMax and fMax defines the initial accuracy of the starting fractional,
	*   or better, the highest used integer numbers used within the starting fractional (bigNum/bigDenom).
	*   There are two approaches, which can accidentially lead to different accuracies just depending on the value.
	*   Therefore, blnUseSmallRange steers this behaviour.
	*   For long long nMax = ((9223372036854775807-1)/2); for long nMax = ((2147483647-1)/2);
	*/
	if (blnUseSmallRange) {
		nMax = (unsigned long long)((ULONG_MAX - 1) / 2);
	}
	else {
		nMax = (ULLONG_MAX - 1) / 2;
	}
	fMax = (double)nMax;

	/*-- For the Euclidean GCD define the denominator range, so that it stays within size of unsigned long variables.
	*   maxDenom should be LONG_MAX for negative values and ULONG_MAX for positive ones.
	*   Also the final returned value of ullNum and ullDenom is limited according to signed- or unsigned-range.
	*/
	if (blnUseSignedRange) {
		maxDenom = LONG_MAX;
		returnLimit = LONG_MAX;
	}
	else {
		maxDenom = ULONG_MAX;
		returnLimit = ULONG_MAX;
	}

	/*-- First generate a rational fraction (bigNum/bigDenom) which represents the value
	*   as a rational number with the highest accuracy. Therefore, unsigned long long (uint64) is needed.
	*   This rational fraction is then reduced using the Euclidean algorithm to find the greatest common divisor (GCD).
	*   bigNum   = big numinator of value without fraction (or cut residual fraction)
	*   bigDenom = big denominator of value
	*-- Break-criteria so that uint64 cast to "bigNum" introduces no error and bigDenom has no overflow,
	*   and stop with enlargement of fraction when the double-value of it reaches an integer number without fractional part.
	*/
	bigDenom = 1;
	while ((value != floor(value)) && (value < fMax) && (bigDenom < nMax)) {
		bigDenom <<= 1;
		value *= 2;
	}
	bigNum = (unsigned long long)value;

	/*-- Start Euclidean algorithm to find the greatest common divisor (GCD) -- */
#define MAX_ITERATIONS 64
	for (i = 0; i < MAX_ITERATIONS; i++) {
		/* if bigDenom is not zero, calculate integer part of fraction. */
		if (bigDenom == 0) {
			val = 0;
			if (i > 0) break;	/* if bigDenom is zero, exit loop, but execute loop just once */
		}
		else {
			val = bigNum / bigDenom;
		}

		/* Set bigDenom to reminder of bigNum/bigDenom and bigNum to previous denominator bigDenom. */
		aux = bigNum;
		bigNum = bigDenom;
		bigDenom = aux % bigDenom;

		/* calculate next denominator and check for its given maximum */
		aux = val;
		if (denomSum[1] * val + denomSum[0] >= maxDenom) {
			aux = (maxDenom - denomSum[0]) / denomSum[1];
			if (aux * 2 >= val || denomSum[1] >= maxDenom)
				i = (MAX_ITERATIONS + 1);			/* exit but execute rest of for-loop */
			else
				break;
		}
		/* calculate next numerator to numSum2 and save previous one to numSum0; numSum1 just copy of numSum2. */
		numSum[2] = aux * numSum[1] + numSum[0];
		numSum[0] = numSum[1];
		numSum[1] = numSum[2];
		/* calculate next denominator to denomSum2 and save previous one to denomSum0; denomSum1 just copy of denomSum2. */
		denomSum[2] = aux * denomSum[1] + denomSum[0];
		denomSum[0] = denomSum[1];
		denomSum[1] = denomSum[2];
	}

	/*-- Check and adapt for final variable size and return values; reduces internal accuracy; denominator is kept in ULONG-range with maxDenom -- */
	while (numSum[1] > returnLimit || denomSum[1] > returnLimit) {
		numSum[1] = numSum[1] / 2;
		denomSum[1] = denomSum[1] / 2;
	}

	/* return values */
	*ullNum = numSum[1];
	*ullDenom = denomSum[1];

}  /*-- euclideanGCD() -------------- */


/**---- DoubleToRational() -----------------------------------------------
* Calculates the rational fractional of a double input value 
* for UN-SIGNED rationals,
* using the Euclidean algorithm to find the greatest common divisor (GCD)
------------------------------------------------------------------------*/
void DoubleToRational2(double value, uint32 *num, uint32 *denom)
{
	/*---- UN-SIGNED RATIONAL ---- */
	int i;

	unsigned long	num2, denom2;
	double dblDiff, dblDiff2;
	unsigned long long ullNum, ullDenom, ullNum2, ullDenom2;

	/*-- Check for negative values. If so it is an error. */
	if (value < 0) {
		*num = *denom = 0;
		TIFFErrorExt(0, "TIFFLib: DoubeToRational()", " Negative Value for Unsigned Rational given.");
		return;
	}

	/*-- Check for too big numbers (> ULONG_MAX) -- */
	if (value > ULONG_MAX) {
		*num = 0xFFFFFFFF;
		*denom = 0;
		return;
	}
	/*-- Check for easy integer numbers -- */
	if (value == (unsigned long)(value)) {
		*num = (unsigned long)value;
		*denom = 1;
		return;
	}
	/*-- Check for too small numbers for "unsigned long" type rationals -- */
	if (value < 1.0 / (double)0xFFFFFFFFU) {
		*num = 0;
		*denom = 0xFFFFFFFFU;
		return;
	}

	/*-- There are two approaches using the Euclidean algorithm, 
	 *   which can accidentially lead to different accuracies just depending on the value.
	 *   Try both and define which one was better.
	 */
	ToRationalEuclideanGCD(value, FALSE, FALSE, &ullNum, &ullDenom);
	ToRationalEuclideanGCD(value, FALSE, TRUE, &ullNum2, &ullDenom2);
	/*-- Double-Check, that returned values fit into ULONG :*/
	if (ullNum > ULONG_MAX || ullDenom > ULONG_MAX || ullNum2 > ULONG_MAX || ullDenom2 > ULONG_MAX)
		assert(0);

	/* Check, which one has higher accuracy and take that. */
	dblDiff = fabs(value - ((double)ullNum / (double)ullDenom));
	dblDiff2 = fabs(value - ((double)ullNum2 / (double)ullDenom2));
	if (dblDiff < dblDiff2) {
		*num = (unsigned long)ullNum;
		*denom = (unsigned long)ullDenom;
	} else {
		*num = (unsigned long)ullNum2;
		*denom = (unsigned long)ullDenom2;
	}
}  /*-- DoubleToRational2() -------------- */

/**---- DoubleToRational() -----------------------------------------------
* Calculates the rational fractional of a double input value
* for SIGNED rationals,
* using the Euclidean algorithm to find the greatest common divisor (GCD)
------------------------------------------------------------------------*/
void DoubleToSrational2(double value, int32 *num, int32 *denom)
{
	/*---- SIGNED RATIONAL ----*/
	int i, neg = 1;
	long	num2, denom2;
	double dblDiff, dblDiff2;
	unsigned long long ullNum, ullDenom, ullNum2, ullDenom2;

	/*-- Check for negative values and use then the positive one for internal calculations. */
	if (value < 0) { neg = -1; value = -value; }

	/*-- Check for too big numbers (> LONG_MAX) -- */
	if (value > LONG_MAX) {
		*num = 0x7FFFFFFF;
		*denom = 0;
		return;
	}
	/*-- Check for easy numbers -- */
	if (value == (long)(value)) {
		*num = (long)value;
		*denom = 1;
		return;
	}
	/*-- Check for too small numbers for "long" type rationals -- */
	if (value < 1.0 / (double)0x7FFFFFFF) {
		*num = 0;
		*denom = 0x7FFFFFFF;
		return;
	}


	/*-- There are two approaches using the Euclidean algorithm,
	*   which can accidentially lead to different accuracies just depending on the value.
	*   Try both and define which one was better.
	*   Furthermore, set behaviour of ToRationalEuclideanGCD() to the range of signed-long.
	*/
	ToRationalEuclideanGCD(value, TRUE, FALSE, &ullNum, &ullDenom);
	ToRationalEuclideanGCD(value, TRUE, TRUE, &ullNum2, &ullDenom2);
	/*-- Double-Check, that returned values fit into LONG :*/
	if (ullNum > LONG_MAX || ullDenom > LONG_MAX || ullNum2 > LONG_MAX || ullDenom2 > LONG_MAX)
		assert(0);

	/* Check, which one has higher accuracy and take that. */
	dblDiff = fabs(value - ((double)ullNum / (double)ullDenom));
	dblDiff2 = fabs(value - ((double)ullNum2 / (double)ullDenom2));
	if (dblDiff < dblDiff2) {
		*num = (long)(neg * (long)ullNum);
		*denom = (long)ullDenom;
	} else {
		*num = (long)(neg * (long)ullNum2);
		*denom = (long)ullDenom2;
	}
}  /*-- DoubleToSrational2() --------------*/






//#define DOUBLE2RAT_DEBUGOUTPUT
/* -----  Double To Rational Conversion ---------------------
* From: http://rosettacode.org/wiki/Convert_decimal_number_to_rational
* Here's another version of best rational approximation of a floating point number.
* Especially for small numbers as needed for EXIF GPS tags latitude and longitude in WGS84.
*/
/* f : number to convert.
* num, denom: returned parts of the rational.
* md: max denominator value.  Note that machine floating point number
*     has a finite resolution (10e-16 ish for 64 bit double), so specifying
*     a "best match with minimal error" is often wrong, because one can
*     always just retrieve the significand and return that divided by
*     2**52, which is in a sense accurate, but generally not very useful:
*     1.0/7.0 would be "2573485501354569/18014398509481984", for example.
*     md=65536 seems to be sufficient for double values and long num/denom
*/
void DoubleToRationalOld(double f, unsigned long *num, unsigned long *denom)
{
	//---- UN-SIGNED RATIONAL ----
	/*  a: continued fraction coefficients. */
	//-- Internally, the integer variables can be bigger than the external ones,
	//   as long as the result will fit into the external variable size.
	unsigned long long a, h[3] = { 0, 1, 0 }, k[3] = { 1, 0, 0 };
	unsigned long long x, d, n = 1;
	int i, neg = 1;
	unsigned long long nMax = ((9223372036854775807 - 1) / 2);		// for long long nMax = ((9223372036854775807-1)/2); for long nMax = ((2147483647-1)/2);
	double fMax = (double)((9223372036854775807i64 - 1) / 2); 					// fMax has to be smaller than max value of "d" /2	

																				//-- For check of better accuracy of "direct" method.
	unsigned long	num2, denom2;

	//-- For debugging purposes, check accuracy of this routine --
#ifdef DOUBLE2RAT_DEBUGOUTPUT
	double dblDiff, dblDiff2;
#endif

	unsigned long md = ULONG_MAX;	// this guarantees that denominator stays within size of long variables.
									//-- if md would be a parameter to the subroutine, then the following check is necessary:
									//if (md <= 1) { *denom = 1; *num = (long) f; return; }

									//-- Check for negative values. If so it is an error.
	if (f < 0) {
		neg = -1; f = -f; *num = *denom = 0;
		TIFFErrorExt(0, "TIFFLib: DoubeToRational()", " Negative Value for Unsigned Rational given."); return;
	}

	//-- Check for too big numbers (> LONG_MAX) --
	if (f > ULONG_MAX) {
		*num = 0xFFFFFFFF;
		*denom = 0;
		return;
	}
	//-- Check for easy numbers --
	if (f == (long)(f)) {
		*num = (long)f;
		*denom = 1;
		return;
	}
	//-- Check for too small numbers for "long" type rationals --
	if (f < 1.0 / 0xFFFFFFFF) {
		*num = 0;
		*denom = 0xFFFFFFFF;
		return;
	}

	//-- Generate Integer value from double with fractional.
	//   d = big numinator of value without fraction (or cut residual fraction)
	//   n = big denominator of value
	//-- Break-criteria so that cast to "d" introduces no error and n has no overflow.
	while ((f != floor(f)) && (f < fMax) && (n < nMax)) { 
		n <<= 1; 
		f *= 2; 
	}
	d = (unsigned long long)f;

	/* continued fraction and check denominator each step */
	for (i = 0; i < 64; i++) {
		a = n ? d / n : 0;						// if n is not zero, calculate integer part of original number.
		if (i && !a) break;						// if n is zero, exit loop

		x = d; d = n; n = x % n;				// set n to reminder of d/n and  d to previous denominator n.

		x = a;
		if (k[1] * a + k[0] >= md) {			// calculate next denominator and check for its given maximum
			x = (md - k[0]) / k[1];
			if (x * 2 >= a || k[1] >= md)
				i = 65;
			else
				break;
		}
		h[2] = x * h[1] + h[0]; h[0] = h[1]; h[1] = h[2];  // calculate next numerator to h2 and save previous one to h0; h1 just copy of h2.
		k[2] = x * k[1] + k[0]; k[0] = k[1]; k[1] = k[2];  // calculate next denominator to k2 and save previous one to k0; k1 just copy of k2.
	}
	//-- Check and adapt for final variable size and return values --
	while (h[1] > ULONG_MAX) {
		h[1] = h[1] / 2;
		k[1] = k[1] / 2;
	}
	*denom = (unsigned long)k[1];
	*num = (unsigned long)h[1];

	//-- Generally, this routine has a higher accuracy than the original "direct" method.
	//   However, in some cases the "direct" method provides better results. Therefore, check here.
	//DoubleToRational_direct(f_in, &num2, &denom2);
	//if (fabs(f_in - ((double)*num / (double)*denom)) > fabs(f_in - ((double)num2 / (double)denom2))) {
	//	*denom = denom2;
	//	*num = num2;
	//}

#ifdef DOUBLE2RAT_DEBUGOUTPUT
	dblDiff = fabs(f_in - ((double)*num / (double)*denom));	//debugging
	dblDiff2 = fabs(f_in - ((double)num2 / (double)denom2)); //debugging
	if (fabs(f_in - ((double)*num / (double)*denom)) > fabs(f_in - ((double)num2 / (double)denom2))) {
		TIFFErrorExt(0, "TIFFLib: DoubeToRational()", " Old Method is better for %f: new dif=%f old-dif=%f .\n", f_in, dblDiff, dblDiff2);
		*denom = denom2;
		*num = num2;
	}
	else TIFFErrorExt(0, "TIFFLib: DoubeToSrational()", " New is better for %f: new dif=%f old-dif=%f .\n", f_in, dblDiff, dblDiff2);
#endif
}  //-- DoubleToRationalOld() --------------


void DoubleToSrationalOld(double f, long *num, long *denom)
{
	//---- SIGNED RATIONAL ----
	/*  a: continued fraction coefficients. */
	//-- Internally, the integer variables can be bigger than the external ones,
	//   as long as the result will fit into the external variable size.
	unsigned long long a, h[3] = { 0, 1, 0 }, k[3] = { 1, 0, 0 };
	unsigned long long x, d, n = 1;
	int i, neg = 1;
	unsigned long long nMax = ((9223372036854775807 - 1) / 2);		// for long long nMax = ((9223372036854775807-1)/2); for long nMax = ((2147483647-1)/2);
	double fMax = (double)((9223372036854775807i64 - 1) / 2); 					// fMax has to be smaller than max value of "d" /2	

																				//-- For check of better accuracy of "direct" method.
	double f_in = f;
	long	num2, denom2;

	//-- For debugging purposes, check accuracy of this routine --
#ifdef DOUBLE2RAT_DEBUGOUTPUT
	double dblDiff, dblDiff2;
#endif

	long md = LONG_MAX;	// this guarantees that denominator stays within size of long variables.
						//-- if md would be a parameter to the subroutine, then the following check is necessary:
						//if (md <= 1) { *denom = 1; *num = (long) f; return; }

						//-- Check for negative values
	if (f < 0) { neg = -1; f = -f; }

	//-- Check for too big numbers (> LONG_MAX) --
	if (f > LONG_MAX) {
		*num = 0x7FFFFFFF;
		*denom = 0;
		return;
	}
	//-- Check for easy numbers --
	if (f == (long)(f)) {
		*num = (long)f;
		*denom = 1;
		return;
	}
	//-- Check for too small numbers for "long" type rationals --
	if (f < 1.0 / 0x7FFFFFFF) {
		*num = 0;
		*denom = 0x7FFFFFFF;
		return;
	}

	//-- Generate Integer value from double with fractional.
	//   d = big numinator of value without fraction (or cut residual fraction)
	//   n = big denominator of value
	//-- Break-criteria so that cast to "d" introduces no error and n has no overflow.
	while ((f != floor(f)) && (f < fMax) && (n < nMax)) { n <<= 1; f *= 2; }
	d = (unsigned long long)f;

	/* continued fraction and check denominator each step */
	for (i = 0; i < 64; i++) {
		a = n ? d / n : 0;						// if n is not zero, calculate integer part of original number.
		if (i && !a) break;						// if n is zero, exit loop

		x = d; d = n; n = x % n;				// set n to reminder of d/n and  d to previous denominator n.

		x = a;
		if (k[1] * a + k[0] >= md) {			// calculate next denominator and check for its given maximum
			x = (md - k[0]) / k[1];
			if (x * 2 >= a || k[1] >= md)
				i = 65;
			else
				break;
		}
		h[2] = x * h[1] + h[0]; h[0] = h[1]; h[1] = h[2];  // calculate next numerator to h2 and save previous one to h0; h1 just copy of h2.
		k[2] = x * k[1] + k[0]; k[0] = k[1]; k[1] = k[2];  // calculate next denominator to k2 and save previous one to k0; k1 just copy of k2.
	}
	//-- Check and adapt for final variable size and return values --
	while (h[1] > LONG_MAX) {
		h[1] = h[1] / 2;
		k[1] = k[1] / 2;
	}
	*denom = (long)k[1];
	*num = neg * (long)h[1];

	//-- Generally, this routine has a higher accuracy than the original "direct" method.
	//   However, in some cases the "direct" method provides better results. Therefore, check here.
	DoubleToSrational_direct(f_in, &num2, &denom2);
	if (fabs(f_in - ((double)*num / (double)*denom)) > fabs(f_in - ((double)num2 / (double)denom2))) {
		*denom = denom2;
		*num = num2;
	}

#ifdef DOUBLE2RAT_DEBUGOUTPUT
	dblDiff = fabs(f_in - ((double)*num / (double)*denom));	//debugging
	dblDiff2 = fabs(f_in - ((double)num2 / (double)denom2)); //debugging
	if (fabs(f_in - ((double)*num / (double)*denom)) > fabs(f_in - ((double)num2 / (double)denom2))) {
		TIFFErrorExt(0, "TIFFLib: DoubeToRational()", " Old Method is better for %f: new dif=%f old-dif=%f .\n", f_in, dblDiff, dblDiff2);
		*denom = denom2;
		*num = num2;
	}
	else TIFFErrorExt(0, "TIFFLib: DoubeToSrational()", " New is better for %f: new dif=%f old-dif=%f .\n", f_in, dblDiff, dblDiff2);
#endif
}  //-- DoubleToSrationalOld() --------------


void DoubleToRational_direct(double value, unsigned long *num, unsigned long *denom)
{
	/*--- OLD Code for debugging and comparison  ---- */
	/* code merged from TIFFWriteDirectoryTagCheckedRationalArray() and TIFFWriteDirectoryTagCheckedRational() */

	/* First check for zero and also check for negative numbers (which are illegal for RATIONAL)
	* and also check for "not-a-number". In each case just set this to zero to support also rational-arrays.
	*/
	if (value <= 0.0 || value != value)
	{
		*num = 0;
		*denom = 1;
	}
	else if (value <= 0xFFFFFFFFU && (value == (double)(uint32)(value)))	/* check for integer values */
	{
		*num = (uint32)(value);
		*denom = 1;
	}
	else if (value<1.0)
	{
		*num = (uint32)((value) * (double)0xFFFFFFFFU);
		*denom = 0xFFFFFFFFU;
	}
	else
	{
		*num = 0xFFFFFFFFU;
		*denom = (uint32)((double)0xFFFFFFFFU / (value));
	}
}  /*-- DoubleToRational_direct() -------------- */

void DoubleToSrational_direct(double value, long *num, long *denom)
{
	/*--- OLD Code for debugging and comparison -- SIGNED-version ----*/
	/*  code was amended from original TIFFWriteDirectoryTagCheckedSrationalArray() */

	/* First check for zero and also check for negative numbers (which are illegal for RATIONAL)
	* and also check for "not-a-number". In each case just set this to zero to support also rational-arrays.
	*/
	if (value<0.0)
	{
		if (value == (int32)(value))
		{
			*num = (int32)(value);
			*denom = 1;
		}
		else if (value>-1.0)
		{
			*num = -(int32)((-value) * (double)0x7FFFFFFF);
			*denom = 0x7FFFFFFF;
		}
		else
		{
			*num = -0x7FFFFFFF;
			*denom = (int32)((double)0x7FFFFFFF / (-value));
		}
	}
	else
	{
		if (value == (int32)(value))
		{
			*num = (int32)(value);
			*denom = 1;
		}
		else if (value<1.0)
		{
			*num = (int32)((value)  *(double)0x7FFFFFFF);
			*denom = 0x7FFFFFFF;
		}
		else
		{
			*num = 0x7FFFFFFF;
			*denom = (int32)((double)0x7FFFFFFF / (value));
		}
	}
}  /*-- DoubleToSrational_direct() --------------*/


