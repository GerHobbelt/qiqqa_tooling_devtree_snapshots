
#pragma once

#if defined(BUILD_MONOLITHIC)

#ifdef __cplusplus
extern "C" {
#endif

int cmph_bdz_gen_lookup_table_main(int argc, const char **argv);
int cmph_benchmark_test_main(int argc, const char **argv);
int cmph_bm_index_main(int argc, const char **argv);
int cmph_bm_map_main(int argc, const char **argv);
int cmph_bm_numbers_main(int argc, const char **argv);
int cmph_compressed_rank_tests_main(int argc, const char **argv);
int cmph_compressed_seq_tests_main(int argc, const char **argv);
int cmph_cxxcmph_main(int argc, const char **argv);
int cmph_file_adapter_ex2_main(int argc, const char **argv);
int cmph_graph_tests_main(int argc, const char **argv);
int cmph_hollow_iterator_test_main(void);
int cmph_main(int argc, const char **argv);
int cmph_mph_bits_test_main(int argc, const char **argv);
int cmph_mph_index_test_main(int argc, const char **argv);
int cmph_mphf_tests_main(int argc, const char **argv);
int cmph_packed_mphf_tests_main(int argc, const char **argv);
int cmph_seeded_has_test_main(int argc, const char **argv);
int cmph_select_tests_main(int argc, const char **argv);
int cmph_small_set_ex4_main(void);
int cmph_struct_vector_adapter_ex3_main(int argc, const char **argv);
int cmph_test_main(void);
int cmph_trigraph_test_main(int argc, const char **argv);
int cmph_vector_adapter_ex1_main(int argc, const char **argv);
int cmph_perfect_cuckoo_test_main(int argc, const char **argv);
int cmph_mph_map_test_main(int argc, const char **argv);
int cmph_flatten_iterator_test_main(int argc, const char **argv);
int cmph_debruijn_index_main(int argc, const char **argv);
int cmph_bfcr_map_test_main(int argc, const char **argv);

#ifdef __cplusplus
}
#endif

#endif
