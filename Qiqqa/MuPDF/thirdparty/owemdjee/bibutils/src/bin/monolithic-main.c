
#include "monolithic_examples.h"

#define USAGE_NAME   "bibutils"

#include "monolithic_main_internal_defs.h"

MONOLITHIC_CMD_TABLE_START()
	{ "bib2xml", { .fa = bibutils_bib2xml_main } },
	{ "bibdiff", { .fa = bibutils_bibdiff_main } },
	{ "biblatex2xml", { .fa = bibutils_biblatex2xml_main } },
	{ "copac2xml", { .fa = bibutils_copac2xml_main } },
	{ "ebi2xml", { .fa = bibutils_ebi2xml_main } },
	{ "end2xml", { .fa = bibutils_end2xml_main } },
	{ "endx2xml", { .fa = bibutils_endx2xml_main } },
	{ "hash_bu", { .fa = bibutils_hash_bu_main } },
	{ "hash_marc", { .fa = bibutils_hash_marc_main } },
	{ "isi2xml", { .fa = bibutils_isi2xml_main } },
	{ "med2xml", { .fa = bibutils_med2xml_main } },
	{ "modsclean", { .fa = bibutils_modsclean_main } },
	{ "nbib2xml", { .fa = bibutils_nbib2xml_main } },
	{ "ris2xml", { .fa = bibutils_ris2xml_main } },
	{ "wordbib2xml", { .fa = bibutils_wordbib2xml_main } },
	{ "xml2ads", { .fa = bibutils_xml2ads_main } },
	{ "xml2bib", { .fa = bibutils_xml2bib_main } },
	{ "xml2biblatex", { .fa = bibutils_xml2biblatex_main } },
	{ "xml2end", { .fa = bibutils_xml2end_main } },
	{ "xml2isi", { .fa = bibutils_xml2isi_main } },
	{ "xml2nbib", { .fa = bibutils_xml2nbib_main } },
	{ "xml2ris", { .fa = bibutils_xml2ris_main } },
	{ "xml2wordbib", { .fa = bibutils_xml2wordbib_main } },

	{ "buauth_test", { .fa = bibutils_buauth_test_main } },
	{ "doi_test", { .f = bibutils_doi_test_main } },
	{ "entities_test", { .f = bibutils_entities_test_main } },
	{ "fields_test", { .fa = bibutils_fields_test_main } },
	{ "intlist_test", { .f = bibutils_intlist_test_main } },
	{ "marcauth_test", { .fa = bibutils_marcauth_test_main } },
	{ "slist_test", { .f = bibutils_slist_test_main } },
	{ "str_test", { .f = bibutils_str_test_main } },
	{ "test", { .fa = bibutils_test_main } },
	{ "utf8_test", { .f = bibutils_utf8_test_main } },
	{ "vplist_test", { .f = bibutils_vplist_test_main } },
MONOLITHIC_CMD_TABLE_END();

#include "monolithic_main_tpl.h"
