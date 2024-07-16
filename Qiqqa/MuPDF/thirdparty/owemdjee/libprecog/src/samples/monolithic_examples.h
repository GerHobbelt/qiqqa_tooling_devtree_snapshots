
#pragma once

#if defined(BUILD_MONOLITHIC)

#ifdef __cplusplus
extern "C" {
#endif

int prl_backgroundNormalization_sample_main(int argc, const char** argv);
int prl_balanceColor_sample_main(int argc, const char** argv);
int prl_balanceGrayWorldWhite_sample_main(int argc, const char** argv);
int prl_balanceSimpleWhite_sample_main(int argc, const char** argv);
int prl_balanceGammaCorrection_sample_main(int argc, const char** argv);
int prl_binarizeByLocalVariances_sample_main(int argc, const char** argv);
int prl_binarizeCOCOCLUST_sample_main(int argc, const char** argv);
int prl_binarizeBCITB_sample_main(int argc, const char** argv);
int prl_binarizeFeng_sample_main(int argc, const char** argv);
int prl_binarizeLocalOtsu_sample_main(int argc, const char** argv);
int prl_binarizeMokji_sample_main(int argc, const char** argv);
int prl_binarizeNativeAdaptive_sample_main(int argc, const char** argv);
int prl_binarizeNiblack_sample_main(int argc, const char** argv);
int prl_binarizeNICK_sample_main(int argc, const char** argv);
int prl_binarizeSauvola_sample_main(int argc, const char** argv);
int prl_binarizeWolfJolion_sample_main(int argc, const char** argv);
int prl_borderDetectAutoCrop_sample_main(int argc, const char** argv);
int prl_cleanBackgroundToWhite_sample_main(int argc, const char** argv);
int prl_correctNUL_sample_main(int argc, const char** argv);
int prl_deblurBasic_sample_main(int argc, const char** argv);
int prl_deblurWienerFilter_sample_main(int argc, const char** argv);
int prl_denoiseSaltPepper_sample_main(int argc, const char** argv);
int prl_denoiseKuwaharaFilter_sample_main(int argc, const char** argv);
int prl_deskew_sample_main(int argc, const char** argv);
int prl_removeDots_sample_main(int argc, const char** argv);
int prl_removeHolePunch_sample_main(int argc, const char** argv);
int prl_removeLines_sample_main(int argc, const char** argv);
int prl_segmentation_sample_main(int argc, const char** argv);
int prl_thinGuoHall_sample_main(int argc, const char** argv);
int prl_thinZhangSuen_sample_main(int argc, const char** argv);
int prl_warp_sample_main(int argc, const char** argv);

#ifdef __cplusplus
}
#endif

#endif
