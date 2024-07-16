
#define BUILD_MONOLITHIC 1
#include "monolithic_examples.h"

#ifdef _WIN32
#define INSTANTIATE_WINGETOPT_GLOBALS   1
#include "wingetopt.h"
#endif

#define USAGE_NAME   "cmph"

#include "monolithic_main_internal_defs.h"

MONOLITHIC_CMD_TABLE_START()

	{ "cmph", { .fa = cmph_main }},
	{ "cxxcmph", { .fa = cmph_cxxcmph_main }},
	{ "vector_adapter_ex1", { .fa = cmph_vector_adapter_ex1_main }},
	{ "file_adapter_ex2", { .fa = cmph_file_adapter_ex2_main }},
	{ "struct_vector_adapter_ex3", { .fa = cmph_struct_vector_adapter_ex3_main }},
	{ "small_set_ex4", { .f = cmph_small_set_ex4_main }},
	{ "bdz_gen_lookup_table", { .fa = cmph_bdz_gen_lookup_table_main }},

#if defined(BUILDING_CMPH_HASHER_TESTS)
	{ "benchmark_test", {.fa = cmph_benchmark_test_main } },
	{ "bm_index", {.fa = cmph_bm_index_main } },
	{ "bm_map", {.fa = cmph_bm_map_main } },
	{ "bm_numbers", {.fa = cmph_bm_numbers_main } },
	{ "compressed_rank_tests", {.fa = cmph_compressed_rank_tests_main } },
	{ "compressed_seq_tests", {.fa = cmph_compressed_seq_tests_main } },
	{ "file_adapter_ex2", {.fa = cmph_file_adapter_ex2_main } },
	{ "graph_tests", {.fa = cmph_graph_tests_main } },
	{ "hollow_iterator_test", {.f = cmph_hollow_iterator_test_main } },
	{ "mph_bits_test", {.fa = cmph_mph_bits_test_main } },
	{ "mph_index_test", {.fa = cmph_mph_index_test_main } },
	{ "mphf_tests", {.fa = cmph_mphf_tests_main } },
	{ "packed_mphf_tests", {.fa = cmph_packed_mphf_tests_main } },
	{ "seeded_has_test", {.fa = cmph_seeded_has_test_main } },
	{ "select_tests", {.fa = cmph_select_tests_main } },
	{ "trigraph_test", {.fa = cmph_trigraph_test_main } },
	{ "perfect_cuckoo_test", {.fa = cmph_perfect_cuckoo_test_main } },
	{ "mph_map_test", { .fa = cmph_mph_map_test_main } },
	{ "flatten_iterator_test", { .fa = cmph_flatten_iterator_test_main } },
	{ "debruijn_index", { .fa = cmph_debruijn_index_main } },
	{ "bfcr_map_test", { .fa = cmph_bfcr_map_test_main } },
#endif

MONOLITHIC_CMD_TABLE_END();

#include "monolithic_main_tpl.h"
