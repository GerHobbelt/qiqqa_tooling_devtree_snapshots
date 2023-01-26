## 4.17

01/24/13

BUILD

*   Large changes to build process; more changes for MINGW32/Cygwin
*   Remove attempt to build powerpc-supporting binaries for MacOSX

GLOBAL

*   Attempt to include iso639-2b codes for languages when possible
*   Make output consistent with MODS version 3.4 by adding language/languageTerm (reported by Nick Bart)
*   Fix accidental duplication of roles in MODS output (reported by Nick Bart)

BIBLATEXIN

*   Map 'hyphenation' to recordInfo/languageOfCataloging (reported by Nick Bart)
*   Map biblatex 'version' to edition (reported by Nick Bart)
*   Fix series fields in @inbook (reported by Nick Bart)
*   Fix issues with @periodical (reported by Nick Bart)
*   Handle entrysubtypes for [@article](https://sourceforge.net/u/article/) (reported by Nick Bart)
*   Handle origdate (reported by Nick Bart)
*   Fix corporate editors (reported by Nick Bart)
*   Process report 'isrn' field (reported by Nick Bart)

MEDIN

*   Handle iso639-2b language input and output as full language name

## 4.16

01/09/13

BUILD

*   Add version to GPL for Fedora/Redhat
*   Add recognition of x86\_64 MacOSX as Intel Macintoshes to configure
*   Add recognition of OpenBSD to configure
*   Add recognition of MINGW32 architecture to configure
*   Remove explicit use of 'make' in Makefiles and use $(MAKE) instead
*   Switch to sh version of configure script (thanks to Adrian Devries)
*   Switch to sh version of maketgz script (thanks to Adrian Devries)
*   Switch to sh version of makedeb script

GLOBAL

*   Improve propagation of memory errors in libraries to calling programs
*   Update help messages
*   Rewrite name parsing/mangling code
*   Do cast for ctype.h functions to handle MINGW32 architecture (reported by Adrian Devries)

ADSOUT

*   Fix bug where partial matches for journal titles identified journals
*   Add Windows-specific format string for MINGW32 architecture (reported by Adrian Devries)
*   Update list of journal abbreviations

BIBTEXIN

*   Fix bug where spaces following an escaped quotation mark (as with the -nl, no latex, flag) are lost (reported by Raoul Blankertz)
*   Fix bug where pages had to be completely numeric (reported by Nick Bart)
*   Import series information for @Techreport
*   Rewrite name parsing
*   Improve recognition of urls put in inappropriate fields
*   Improve handling of tilde/sticky space
*   Add latex recognition of alternative ways to express the (Polish) capital and lowercase slashed L
*   Improve recognition of URL identifiers in note fields
*   Map 'howpublished' to publisher (reported by Nick Bart)

BIBLATEXIN

*   Add 'date' field to every reference type, regardless if it's in the reference documentation or not (reported by Nick Bart)
*   Fix bug where pages had to be completely numeric (reported by Nick Bart)
*   Add support for 'institution' and 'type' for report references (reported by Nick Bart)
*   Add strings support (reported by Nick Bart)
*   Handle editor types, including bibtex-chicago variants (reported by Nick Bart)
*   Map 'introduction', 'foreward', 'afterward' to "author of introduction/foreward/afterward" (reported by Nick Bart)
*   Ignore 'school' in biblatexin reference if 'institution' is available like biblatex(reported by Nick Bart)
*   Improve biblatex thesis type recognition
*   Rewrite name parsing
*   Improve handlning of tilde/sticky space
*   Map 'howpublished' to publisher (reported by Nick Bart)
*   Handle 'titleaddon' field (reported by Nick Bart)
*   Output number field differently for type report (reported by Nick Bart)

BIBTEXOUT

*   Output series information for @Techreport
*   Output all keywords in single entry as semi-colon deliminated list

COPACIN

*   Fix pre-name mangling that prevents recognition by asis/corporation lists

ENDIN

*   Add better support for series information

ENDOUT

*   Add better support for series information

MODSIN

*   Add support for common MARC role codes (role abbreviations)

RISIN

*   Add recognition of map type
*   Improve support for series information (reported by Mattheis Steffens)

RISOUT

*   Add recognition of map type (reported by Mattheis Steffens)
*   Fix bug in date output (reported by Mattheis Steffens)
*   Improve support for series information (reported by Mattheis Steffens)

## 4.15

9/26/12

BIBTEXIN

*   [@article](https://sourceforge.net/u/article/) 'number' -> MODS 'issue'
*   @conference = @inproceedings
*   'organization' -> publisher if publisher not available, otherwise output  
    as \\<name\\>\\<namepart\\>xx\\</namepart\\>\\<role\\>\\<roleterm\\>organizer of meeting\\</roleterm\\>\\\\</name></role\\></name\\>

BIBLATEXIN

*   Add missing month parsing

## 4.14

9/04/12

BIBTEXIN

*   Split individual keywords in the keywords field separated by semi-colons

RISIN

*   Handle URL schemes from L1 and L4 fields (reported by Martin Kucej)

RISOUT

*   PY outputs only year, DA outputs year/month/day combination (reported by Nelson Hart)
*   L1 and L4 fields need to be URL's (reported by Martin Kucej)

WORD2007OUT

*   Replace b:PeriodicalName with b:PeriodicalTitle

## 4.13

8/28/12

BUILD

*   Fix build problem with test subdirectory (patch by David Bremner)
*   Avoid hard-coded dynamic library to help out Debian (path by David Bremner)
*   Add patch to bibutils.dbk (patch by David Bremner)

CHARSETS

*   Add more latex character <-> Unicode conversions
*   Fix caron (and other) errors in export (reported by Philip Eisenlohr)

FIELDS

*   Update internals, add vplist component, and convert to new interface

BIBTEXIN

*   Fix chapter in @inbook, @inproceedings, and @incollection from overwriting the title of the section being cited (reported by Brian Keese)
*   Cleanly handle "illegal" @inbook entries that have both "title" and "booktitle" fields and really want to be @incollection entries (reported by Brian Keese)
*   Remove mbox commands from input

RISIN

*   Add recognition of more RIS fields (reported by Nelson Hart)

RISOUT

*   Use 'AB' instead of 'N2' tag for abstracts (reported by Nelson Hart)
*   Use 'DO' tag instead of building a complete URL for DOI's (reported by Nelson Hart)
*   Use 'ET' tag for edition output (reported by Nelson Hart)
*   Use 'LA' tag for language
*   Add recognition of non-official genres "book chapter" and "journal article" (reported by Nelson Hart)

## 4.12

10/10/2010

BUILD

*   Allow smaller static libraries to be built
*   Add --dynamic and --static (default) options to configure script
*   Add --install-lib to configure script to controll installation of dynamic libraries

XML2ADS

*   Fix overflow of page value with really large page numbers
*   Update journal abbreviation list

XML2BIB

*   Add command-line option -d or --drop-key to prevent xml2bib from  
    adding tags (so they can be generated by programs like JabRef)

## 4.11

9/14/2010

BUILD

*   Include some "unused" flags like LDFLAGS so that people with particular build  
    environments can have these flags respected (from Gentoo  
    [http://bugs.gentoo.org/show\_bug.cgi?id=336237](http://bugs.gentoo.org/show_bug.cgi?id=336237))
*   Add test programs to "make test" protocol

TEST

*   Fix some signedness issues (bit rot) in the test programs (from Mandriva  
    packager, Stéphane Téletchéa

XML2BIB

*   Add command-line option -at or --abbreviatedtitles to force xml2bib to  
    use abbreviated titles for journals (books and other host types), if present  
    in the MODS input

## 4.10

8/30/2010

BIBLATEX2XML

*   fix organization/event handling (thanks to Johannes Wilms)

MODSIN

*   support the presence of the reference identifier/key in  
    mods:recordInfo:recordIdentifier

## 4.9

4/9/2010

BIBLATEX2XML

*   Many, many changes thanks to Johannes Wilms

BIB2XML

*   Some improvements in thesis handling derived from biblatex2xml changes

BUILD

*   Fix build for \_x86\_64 (amd64) (Thanks to patch from Colin Bell).

## 4.8

2/2/2010

BIB2XML

*   Handle bibtex annote tags

XML2BIB

*   Handle bibtex annote tags

## 4.7

12/11/2009

XML2ADS

*   Fix not outputting multiple authors from "ASIS" and "CORP" categories.

XML2END

*   Fix not outputting multiple authors from "ASIS" and "CORP" categories.

XML2ISI

*   Fix not outputting multiple authors from "ASIS" and "CORP" categories.

## 4.6

11/02/2009

BIB2XML

*   Fix inefficiency in latex2char() that gives roughly a 10x speed increase  
    in bib2xml. Thanks to Stephan Washietl for the patch.

NAME MANGLING

*   Fix bug with uninitalized pointer. Thanks to David Bremner for patch.

NEWSTRING

*   Add newstrs versions of various commands.

## 4.5

10/24/2009

BIB2XML

*   Identify and use byte-order-mark in UTF8-encoded files
*   Support file attachments with "pdf" tags (old JabRef), "sentelink" (Sente),  
    and "file" (new JabRef, Zotero, Mendeley). (Thanks to Richard Karnesky)

COPAC2XML

*   Identify and use byte-order-mark in UTF8-encoded files

ISI2XML

*   Identify and use byte-order-mark in UTF8-encoded files

RIS2XML

*   Add support for DOI tags DO and DI from Scopus (Thanks to Fred Howell)
*   Identify and use byte-order-mark in UTF8-encoded files
*   Add support for L1 file attachment tags (Thanks to Richard Karnesky)

XML2ADS

*   Output file attachments as URLs

XML2BIB

*   Add support for "file" file attachment tag in the JabRef/Mendeley/Zotero format

XML2END

*   Output file attachments as URLs

XML2ISI

*   Output file attachments as URLs

XML2RIS

*   Add support for L1 file attachment tags

## 4.4

10/05/2009

BIB2XML

*   Add -nt --nosplit-title command line option to avoid splitting titles  
    with colons or question marks into title/subtitle MODS pairs

COPAC2XML

*   Add -nt --nosplit-title command line option to avoid splitting titles  
    with colons or question marks into title/subtitle MODS pairs

END2XML

*   Add -nt --nosplit-title command line option to avoid splitting titles  
    with colons or question marks into title/subtitle MODS pairs
*   Add support for electronic-source-num as potential location of DOI
*   Add support for language

END2XML

*   Fix support for number field in report/book/book section/edited book  
    reference types

ENDXML2XML

*   Support pdf-url in endnote XML file

ISI2XML

*   Add -nt --nosplit-title command line option to avoid splitting titles  
    with colons or question marks into title/subtitle MODS pairs

RIS2XML

*   Add -nt --nosplit-title command line option to avoid splitting titles  
    with colons or question marks into title/subtitle MODS pairs

## 4.3

7/31/09

BIB2XML

*   Add support for recognizing howpublished = {arXiv:xxxx} entries

LATEX

*   Fix bug for {\\c{c}} output

XML2END

*   Add support for Pubmed ID's (PMID) as %U [http://www.ncbi.nlm.nih.gov/pubmed/..](http://www.ncbi.nlm.nih.gov/pubmed/..)  
    .
*   Add support for arXiv identifiers as %U [http://arxiv.org/abs/...](http://arxiv.org/abs/...)

XML2RIS

*   Add support for Pubmed ID's (PMID) as UR - [http://www.ncbi.nlm.nih.gov/pubmed/](http://www.ncbi.nlm.nih.gov/pubmed/)  
    ..
*   Add support for arXiv identifiers as UR - [http://arxiv.org/abs/...](http://arxiv.org/abs/...)
*   Change abstract output from "AB" tag to "N2"

XML2WORDBIB

*   Add support to handle inventors in patent type
*   Fix inappropriate output of empty author or editor lists

## 4.2

06/25/09

BUILD

*   Add support for 'Power Macintosh' as MacOSX\_ppc. Thanks to Matthias  
    Steffens for the fix.
*   Fix additional MacOSX build bugs, thanks to David Sanson

END2XML

*   Add %1 parsing to journal articles
*   Fix bug not recognizing %\[ and elements as valid tags
*   Add support for Conference Paper

ENDX2XML

*   Add support for pub-location tags
*   Add support for Conference Paper

LATEX

*   Fix bug for {\\AA} conversion, patch thanks to Joseph Barillari.

MED2XML

*   Recognized medline entries from MEDLINE in addition to PUBMED. Thanks to  
    Hamish McWilliam for providing useful information.

MODSIN

*   Handle pages provided as list, patch thanks to Heiko Jansen

NAME MANGLING

*   Handle hyphenated names better
*   Handle "et al." in name lists better

XML2BIB

*   Add recognition of genre "article", patch thanks to Heiko Jansen

XML2END

*   Add export of DOI as %U [http://dx.doi.org/....](http://dx.doi.org/....) Thanks to Mattheis  
    Stevens for the report

XML2RIS

*   Add export of DOI as UR - [http://dx.doi.org/....](http://dx.doi.org/....) Thanks to Mattheis  
    Stevens for the report

XML2WORD

*   Add support for more types of sources.

## 4.1

12/21/08

BIBLATEX2XML

*   Lots of bug fixes

BUILD

*   Try to make changes to bin/Makefile to fix problem on FreeBSD. Still  
    awaiting feedback to see if problem is solved.

END2XML

*   Handle DOI placed in %1 custom field by Wiley

RIS2XML

*   Add pattern matching for new DOI output by Science Direct

XML2ADS

*   Fix putting comma after the first keyword (thanks to Richard Mathar)

## 4.0

12/14/08

BIBLATEX2XML

*   Initial alpha version of the program -- mapping certain fields to MODS  
    hasn't been done yet.

BUILD

*   Move files/functions around so all of the code necessary to support  
    the converters but not part of the bibutils libraries are in the  
    bin subdirectory.

CHARSET CONVERSION

*   add partial recognition of Chinese GB18030 character set (containing  
    the GBK superset)
*   Revert 3.41 patch from Luc Pardon default that made unicode/utf8 take  
    precedence over latex now that -nl, --no-latex flag is available

END2XML

*   support %G language tag
*   support %H translator tag

ENDX2XML

*   fix bug caused by style tags in author fields

LIBRARY HANDLING

*   Remove requirement for defining lists for "as-is" and "corporation" names  
    to be read from the file -- embed in the param structure instead (help  
    for Haskell bindings)
*   Modify the library API so that input and output formats are stored in  
    struct param and do not need to be repeated in bibl\_read() and bibl\_write()  
    calls.

XML2BIB

*   Turn off latex encoding if we're using the GB18030 character set.

XML2END

*   support %G language tag
*   support %H translator tag
*   add better support for MARC-authority genre tags
