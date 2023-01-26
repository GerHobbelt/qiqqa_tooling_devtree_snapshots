
#pragma once

#if defined(BUILD_MONOLITHIC)

#ifdef __cplusplus
extern "C" {
#endif

extern int qjscpp_async_example_main(int argc, const char** argv);
extern int qjscpp_classes_example_main(int argc, const char** argv);
extern int qjscpp_closures_example_main(int argc, const char** argv);
extern int qjscpp_exception_example_main(int argc, const char** argv);
extern int qjscpp_simple_example_main(int argc, const char** argv);

#ifdef __cplusplus
}
#endif

#endif
