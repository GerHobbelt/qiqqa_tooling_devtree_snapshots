//
// part of Demo 
//

#pragma once

#if defined(BUILD_MONOLITHIC)

#ifdef __cplusplus
extern "C" {
#endif

int chaos_benchmark_graph_main(void);
int chaos_file_checksum_main(int argc, const char **argv);
int chaos_machine_interface_main(void);
int chaos_interface_main(void);
int chaos_long_period_urandom_main(void);
int chaos_normal_dist_diagram_main(void);
int chaos_tests_library_main(void);
int chaos_tests_testU01_main(void);
int chaos_truely_random_main(void);
int chaos_deep_main(int argc, const char **argv);
int chaos_sandbox_main(void);
int chaos_testu01_main(void);

#ifdef __cplusplus
}
#endif

#endif
