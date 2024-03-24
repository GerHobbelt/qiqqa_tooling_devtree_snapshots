//
// part of googletest
//

#pragma once

#if defined(BUILD_MONOLITHIC)

#ifdef __cplusplus
extern "C" {
#endif

int gtest_sample10_main(int argc, const char** argv);
int gtest_sample11_main(int argc, const char** argv);
int gtest_sample9_main(int argc, const char** argv);
int gtest_main(int argc, const char** argv);
int gtest_break_on_failure_test_main(int argc, const char** argv);
int gtest_catch_exceptions_test_main(int argc, const char** argv);
int gtest_color_test_main(int argc, const char** argv);
int gtest_death_test_main(int argc, const char** argv);
int gtest_env_var_test_main(int argc, const char** argv);
int gtest_failfast_test_main(int argc, const char** argv);
int gtest_filter_test_main(int argc, const char** argv);
int gtest_global_env_test_main(int argc, const char** argv);
int gtest_list_test_main(int argc, const char** argv);
int gtest_listener_test_main(int argc, const char** argv);
int gtest_output_test_main(int argc, const char** argv);
int gtest_param_inv_name1_test_main(int argc, const char** argv);
int gtest_param_inv_name2_test_main(int argc, const char** argv);
int gtest_param_test_main(int argc, const char** argv);
int gtest_shuffle_test_main(int argc, const char** argv);
int gtest_throw_on_fail_test_main(int argc, const char** argv);
int gtest_uninitialized_test_main(int argc, const char** argv);
int gtest_api_test_main(int argc, const char** argv);
int gtest_assert_ex_test_main(int argc, const char** argv);
int gtest_env_test_main(int argc, const char** argv);
int gtest_list_output_test_main(int argc, const char** argv);
int gtest_no_test_main(int argc, const char** argv);
int gtest_premature_exit_test_main(int argc, const char** argv);
int gtest_repeat_test_main(int argc, const char** argv);
int gtest_skip_env_test_main(int argc, const char** argv);
int gtest_stress_test_main(int argc, const char** argv);
int gtest_stress_test_main(int argc, const char** argv);
int gtest_macro_stack_footprint_test_main(int argc, const char** argv);
int gtest_throw_on_fail_ex_test_main(int argc, const char** argv);
int gtest_user_exception_test_main(int argc, const char** argv);
int gtest_xml_output_test_main(int argc, const char** argv);

#ifdef __cplusplus
}
#endif

#endif
