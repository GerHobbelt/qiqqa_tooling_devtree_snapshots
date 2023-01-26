
#pragma once

#if defined(BUILD_MONOLITHIC)

#ifdef __cplusplus
extern "C" {
#endif

extern int qjscpp_main(int argc, const char ** argv);

extern int qjscpp_class_test_main(void);
extern int qjscpp_conversions_test_main(void);
extern int qjscpp_enum_test_main(void);
extern int qjscpp_example_main(void);
extern int qjscpp_exception_test_main(void);
extern int qjscpp_function_call_test_main(void);
extern int qjscpp_inheritance_test_main(void);
extern int qjscpp_jobs_test_main(void);
extern int qjscpp_module_loader_test_main(void);
extern int qjscpp_multicontext_test_main(void);
extern int qjscpp_point_test_main(void);
extern int qjscpp_unhandled_rejection_test_main(void);
extern int qjscpp_value_test_main(void);
extern int qjscpp_variant_test_main(void);

#ifdef __cplusplus
}
#endif

#endif
