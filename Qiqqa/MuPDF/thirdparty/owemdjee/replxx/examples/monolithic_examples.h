
#pragma once

#if defined(BUILD_MONOLITHIC)

#ifdef __cplusplus
extern "C" {
#endif

int replxx_c_api_main(int argc, const char** argv);
int replxx_cpp_api_main(int argc, const char** argv);

#ifdef __cplusplus
}
#endif

#endif
