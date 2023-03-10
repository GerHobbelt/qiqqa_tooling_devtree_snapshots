/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_artifex_mupdf_fitz_Pixmap */

#ifndef _Included_com_artifex_mupdf_fitz_Pixmap
#define _Included_com_artifex_mupdf_fitz_Pixmap
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_artifex_mupdf_fitz_Pixmap
 * Method:    finalize
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_artifex_mupdf_fitz_Pixmap_finalize
  (JNIEnv *, jobject);

/*
 * Class:     com_artifex_mupdf_fitz_Pixmap
 * Method:    newNative
 * Signature: (Lcom/artifex/mupdf/fitz/ColorSpace;IIIIZ)J
 */
JNIEXPORT jlong JNICALL Java_com_artifex_mupdf_fitz_Pixmap_newNative
  (JNIEnv *, jobject, jobject, jint, jint, jint, jint, jboolean);

/*
 * Class:     com_artifex_mupdf_fitz_Pixmap
 * Method:    clear
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_artifex_mupdf_fitz_Pixmap_clear
  (JNIEnv *, jobject);

/*
 * Class:     com_artifex_mupdf_fitz_Pixmap
 * Method:    clearWithValue
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_com_artifex_mupdf_fitz_Pixmap_clearWithValue
  (JNIEnv *, jobject, jint);

/*
 * Class:     com_artifex_mupdf_fitz_Pixmap
 * Method:    saveAsPNG
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_artifex_mupdf_fitz_Pixmap_saveAsPNG
  (JNIEnv *, jobject, jstring);

/*
 * Class:     com_artifex_mupdf_fitz_Pixmap
 * Method:    getX
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_artifex_mupdf_fitz_Pixmap_getX
  (JNIEnv *, jobject);

/*
 * Class:     com_artifex_mupdf_fitz_Pixmap
 * Method:    getY
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_artifex_mupdf_fitz_Pixmap_getY
  (JNIEnv *, jobject);

/*
 * Class:     com_artifex_mupdf_fitz_Pixmap
 * Method:    getWidth
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_artifex_mupdf_fitz_Pixmap_getWidth
  (JNIEnv *, jobject);

/*
 * Class:     com_artifex_mupdf_fitz_Pixmap
 * Method:    getHeight
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_artifex_mupdf_fitz_Pixmap_getHeight
  (JNIEnv *, jobject);

/*
 * Class:     com_artifex_mupdf_fitz_Pixmap
 * Method:    getStride
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_artifex_mupdf_fitz_Pixmap_getStride
  (JNIEnv *, jobject);

/*
 * Class:     com_artifex_mupdf_fitz_Pixmap
 * Method:    getNumberOfComponents
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_artifex_mupdf_fitz_Pixmap_getNumberOfComponents
  (JNIEnv *, jobject);

/*
 * Class:     com_artifex_mupdf_fitz_Pixmap
 * Method:    getAlpha
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_com_artifex_mupdf_fitz_Pixmap_getAlpha
  (JNIEnv *, jobject);

/*
 * Class:     com_artifex_mupdf_fitz_Pixmap
 * Method:    getColorSpace
 * Signature: ()Lcom/artifex/mupdf/fitz/ColorSpace;
 */
JNIEXPORT jobject JNICALL Java_com_artifex_mupdf_fitz_Pixmap_getColorSpace
  (JNIEnv *, jobject);

/*
 * Class:     com_artifex_mupdf_fitz_Pixmap
 * Method:    getSamples
 * Signature: ()[B
 */
JNIEXPORT jbyteArray JNICALL Java_com_artifex_mupdf_fitz_Pixmap_getSamples
  (JNIEnv *, jobject);

/*
 * Class:     com_artifex_mupdf_fitz_Pixmap
 * Method:    getSample
 * Signature: (III)B
 */
JNIEXPORT jbyte JNICALL Java_com_artifex_mupdf_fitz_Pixmap_getSample
  (JNIEnv *, jobject, jint, jint, jint);

/*
 * Class:     com_artifex_mupdf_fitz_Pixmap
 * Method:    getPixels
 * Signature: ()[I
 */
JNIEXPORT jintArray JNICALL Java_com_artifex_mupdf_fitz_Pixmap_getPixels
  (JNIEnv *, jobject);

/*
 * Class:     com_artifex_mupdf_fitz_Pixmap
 * Method:    getXResolution
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_artifex_mupdf_fitz_Pixmap_getXResolution
  (JNIEnv *, jobject);

/*
 * Class:     com_artifex_mupdf_fitz_Pixmap
 * Method:    getYResolution
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_artifex_mupdf_fitz_Pixmap_getYResolution
  (JNIEnv *, jobject);

/*
 * Class:     com_artifex_mupdf_fitz_Pixmap
 * Method:    invert
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_artifex_mupdf_fitz_Pixmap_invert
  (JNIEnv *, jobject);

/*
 * Class:     com_artifex_mupdf_fitz_Pixmap
 * Method:    invertLuminance
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_artifex_mupdf_fitz_Pixmap_invertLuminance
  (JNIEnv *, jobject);

/*
 * Class:     com_artifex_mupdf_fitz_Pixmap
 * Method:    gamma
 * Signature: (F)V
 */
JNIEXPORT void JNICALL Java_com_artifex_mupdf_fitz_Pixmap_gamma
  (JNIEnv *, jobject, jfloat);

/*
 * Class:     com_artifex_mupdf_fitz_Pixmap
 * Method:    tint
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_com_artifex_mupdf_fitz_Pixmap_tint
  (JNIEnv *, jobject, jint, jint);

#ifdef __cplusplus
}
#endif
#endif
