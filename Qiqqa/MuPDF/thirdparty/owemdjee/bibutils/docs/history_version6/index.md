## 6.10

3/23/20

*   Fix build errors in 6.9

## 6.9

3/17/20

*   Add xml2biblatex converter
*   Fix bug where --no-latex/-nl isn't respected when outputting names
*   Replace latex parser
*   xml2isi - add publisher address to output
*   Cleanups to converter core
*   Fixes to some fuzzer-identified bugs

## 6.8

8/27/19

*   Improve ISI output
*   Lots of cleanups

## 6.7

8/31/2018

*   Remove exit() calls from library and fully implement error tracking in struct str (requested by Vasiliy Glazov)
*   Add "DOI:" to doi entries in xml2ads (reported by Richard Mathar)
*   Eliminate duplication of doi information in xml2ads (reported by Richard Mathar)
*   Improve handling of non-ascii letters for ADS %R tags (patch from Richard Mathar)
*   Suppress warnings on Windows compilers with 32 bit longs (reported by Vaclav Haisman)

## 6.6

7/02/2018

*   Allow distros to inject LDFLAGS via LDFLAGIN into bibutils builds (reported by Jens-Ulrik Petersen)
*   Add xml2nbib converter

## 6.5

6/12/2018

*   Handle both genres "unpublished" and "manuscript" (reported by Chip Maguire)
*   Recognize all MARC role abbreviations (reported by Chip Maguire)
*   Handle Licentiate theses (reported by Chip Maguire)
*   Fix bug in nbib2xml (reported by Vaclav Haisman)
*   Fix hangs in bib2xml/biblatex2xml found by american-fuzzy-lop

## 6.4

6/05/18

*   Add missing return in bibtexout.c (reported by Vaclav Haisman)
*   Fix accidentally deleted extern in xml.h to fix hs-bibutils build (reported  
    by Vaclav Haisman)

## 6.3

6/04/18

*   Add bibdiff program
*   Fix header guards in iso639\_1.h and iso639\_3.h (reported by Vaclav Haisman)
*   Fix nbib support for bibutils as a library (reported by Vaclav Haisman)
*   Add authority="bibutilsgt" for bibutils-recognized genres not in MARC authority
*   Switch from GENRE/NGENRE/UGENRE to GENRE:MARC/GENRE:BIBUTILS/GENRE:UNKNOWN
*   General cleanups and fixes to cppcheck/clang warnings
*   Fix CVE-2018-10773, CVE-2018-10774, CVE-2018-10775

## 6.2

8/09/17

DOI

*   Output as url in addition to doi for ads, bibtex, and ris formats

## 6.1

7/31/17

BUILD

*   Fix recognition of Linux ppc64le machines (reported by Michaela Buchanan)

GLOBAL

*   Handle new crossref URL for DOI's [https://doi.org/](https://doi.org/) (reported by Murali Raju)

RISIN

*   Handle mangled RIS sources that have three spaces in the tag instead of two (reported by Vaclav Haisman)

## 6.0

7/4/17

GLOBAL

*   Switch newstr/list to str/slist
*   Fix build problems

RISIN

*   Fix parsing bug in RIS (patch from Vaclav Haisman)

BIBTEXIN/OUT

*   Improve handling of eprintClass/primaryClass for arXiv references (reported by Chris Karakas)
