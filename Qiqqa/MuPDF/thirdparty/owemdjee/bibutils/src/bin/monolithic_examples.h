
#pragma once

#if defined(BUILD_MONOLITHIC)

#ifdef __cplusplus
extern "C" {
#endif

extern int bibutils_bib2xml_main(int argc, const char** argv);
extern int bibutils_bibdiff_main(int argc, const char** argv);
extern int bibutils_biblatex2xml_main(int argc, const char** argv);
extern int bibutils_buauth_test_main(int argc, const char** argv);
extern int bibutils_copac2xml_main(int argc, const char** argv);
extern int bibutils_doi_test_main(void);
extern int bibutils_ebi2xml_main(int argc, const char** argv);
extern int bibutils_end2xml_main(int argc, const char** argv);
extern int bibutils_endx2xml_main(int argc, const char** argv);
extern int bibutils_entities_test_main(void);
extern int bibutils_fields_test_main(int argc, const char** argv);
extern int bibutils_hash_bu_main(int argc, const char** argv);
extern int bibutils_hash_marc_main(int argc, const char** argv);
extern int bibutils_intlist_test_main(void);
extern int bibutils_isi2xml_main(int argc, const char** argv);
extern int bibutils_marcauth_test_main(int argc, const char** argv);
extern int bibutils_med2xml_main(int argc, const char** argv);
extern int bibutils_modsclean_main(int argc, const char** argv);
extern int bibutils_nbib2xml_main(int argc, const char** argv);
extern int bibutils_ris2xml_main(int argc, const char** argv);
extern int bibutils_slist_test_main(void);
extern int bibutils_str_test_main(void);
extern int bibutils_test_main(int argc, const char** argv);
extern int bibutils_utf8_test_main(void);
extern int bibutils_vplist_test_main(void);
extern int bibutils_wordbib2xml_main(int argc, const char** argv);
extern int bibutils_xml2ads_main(int argc, const char** argv);
extern int bibutils_xml2bib_main(int argc, const char** argv);
extern int bibutils_xml2biblatex_main(int argc, const char** argv);
extern int bibutils_xml2end_main(int argc, const char** argv);
extern int bibutils_xml2isi_main(int argc, const char** argv);
extern int bibutils_xml2nbib_main(int argc, const char** argv);
extern int bibutils_xml2ris_main(int argc, const char** argv);
extern int bibutils_xml2wordbib_main(int argc, const char** argv);

#ifdef __cplusplus
}
#endif

#endif
