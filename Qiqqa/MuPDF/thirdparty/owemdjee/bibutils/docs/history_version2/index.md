## 2.18

7/23/2004

XML2BIB

*   ensure that there's no spaces or tabs in the auto-generated bibtex  
    keys
*   bump version number to 1.9

## 2.17

7/19/2004

BIB2XML

*   fix bug where stdin input didn't write XML and REFERENCES wrappers
*   fix up some name handling
*   lots of cleanups
*   add --verbose flag
*   add @STRING{} support to bibtex files
*   bump version number to 1.8

ISI2XML

*   fix bug in adding periods after initials of first names
*   fix bug where stdin input didn't write XML and REFERENCES wrappers
*   convert isi2xml to use fields package
*   lots of cleanups
*   bump version number to 1.2

RIS2XML

*   fix bug in adding periods after initials of first names
*   fix bug causing last reference to be missed with corrupted end-of-record tag
*   fix bug where stdin input didn't write XML and REFERENCES wrappers
*   convert ris2xml to use fields package
*   lots of cleanups
*   bump version number to 1.12

FIELDS

*   bug fixes in field memory allocation from version 3

## 2.16

4/26/2004

BIB2XML

*   use fields\_init()
*   version number 1.7

END2XML

*   fix restriction in which %0 tag was expected to begin all references
*   use fields\_init()
*   remove dead code
*   version number 1.3

ISI2XML

*   add periods after initials of first names
*   version number 1.1

RIS2XML

*   add periods after initials of first names
*   version number 1.11

FIELDS

*   bug fixes in field memory allocation error paths from version 3
*   add fields\_init() function

XML2BIB

*   fix bug where non-numeric MONTH tags always output as January
*   ensure no spaces are put into the bibtex reference key
*   version number 1.8

## 2.15

2/19/2004

ISI2XML

*   write program, version number 1.0

## 2.14

12/03/2003

END2XML

*   fix bug when non-endnote references are seen, get coredump
*   bump version number to 1.2

XML2BIB

*   add -b, --brackets flag to allow data elements to be placed  
    in output instead of quotations
*   add -w, --whitespace flag to include beautifying whitespace  
    in output
*   clean up code a bit
*   bump version number to 1.7

XMLREPLACE

*   fix bug introduced when newstring library was upgraded
*   fix bug where it tried to add empty field/find/replace elements  
    on blank lines in the rule file
*   use dynamic allocation for subnodes
*   clean up code a bit
*   bump version number to 1.1

## 2.13

11/28/2003

BIB2XML

*   fix bug where whitespace in long input lines was clobbered
*   clean dead code
*   bump version number to 1.6

## 2.12

11/07/2003

END2XML

*   fix bug where input line buffer isn't cleared initially
*   fix initialization of fields that can core dump on non-endnote  
    input files
*   bump version number to 1.1

RIS2XML

*   fix core dump in output\_type() when no type exists
*   prevent empty references from being output with stray "ER -"  
    tags
*   fix bug where input line buffer isn't cleared initially
*   bump version number to 1.10

## 2.11

11/03/2003

GENERAL

*   fix processing of HTML entities so that they don't require  
    xml entity definitions
*   fix output of Latin-1 encoded elements so they don't put  
    bad characters into the XML
*   extract is\_ws() function for general use

BIB2XML

*   fix xml processing for first names
*   bump version number to 1.5

END2XML

*   new program (backported from bibutils 3.0 alpha), version number 1.0

RIS2XML

*   fix core dumping if ris2xml doesn't see any RIS tags in a file
*   use a more sophisticated line extractor to more cleanly handle  
    mac/dos/unix end-of-line differences in text files (backport  
    from bibutils 3.0 alpha)
*   bump version number to 1.9

MED2XML

*   bump version number to 1.7

## 2.10

11/01/2003

GENERAL

*   ensure that quotations, less-than, greater-than, and ampersand  
    characters are recoded as proper xml and then decoded back to  
    normal characters afterwards

BIB2XML

*   fix bug in which tags for entire list surround output for  
    each file rather than for one set around output from all files
*   fix core dump when no references are recognized
*   bump version number to 1.4

MED2XML

*   fix bug where working groups (separated from author list by  
    a semi-colon) wasn't being properly removed and would  
    garble the last author
*   fix bug where translated titles in brackets were garbled by  
    the parser
*   fix bug in which tags for entire list surround output for  
    each file rather than for one set around output from all files
*   remove used function output\_abstract()
*   reduce unnecessary malloc'ing and free'ing of newstrings by  
    using newstr\_empty() instead of newstr\_free() for each  
    reference
*   various cleanups
*   bump version number to 1.6

RIS2XML

*   fix bug in which tags for entire list surround output for  
    each file rather than for one set around output from all files
*   bump version number to 1.8

XML2BIB

*   add -sd, --singledash command line option so page ranges can be  
    set to have a single dash between them (instead of the "--" default  
    which looks good in latex)
*   bump version number to 1.6

XML2EN

*   bump version number to 1.2

XML2RIS

*   add number field output
*   bump version number to 1.3

## 2.9

10/20/2003

BIB2XML

*   fix problem where tex-encoded quotations weren't being ignored
*   bump version number to 1.3

RIS2XML

*   fix problems in identification of tags with Mac-end of lines  
    with multi-line tagged fields
*   bump version number to 1.7

XML2BIB

*   fix missing commas before ISSN, ISBN, and serial number  
    output
*   add -fc or --finalcomma flag so that a final unnecessary  
    comma is added to the bibtex output for those that want it
*   bump version number to 1.5

## 2.8

10/16/2003

MED2XML

*   fix bug in pages output
*   crush core dump
*   add number output for journals
*   bump version number to 1.5

RIS2XML

*   fix extra spaces in tag output
*   bump version number to 1.6

XML2BIB

*   have output distinguish between ISSN and ISBN and unidentifiable  
    serial number
*   bump version number to 1.4

## 2.7

9/02/2003

BIB2XML

*   have Report and TechReport types be outputted as "REPORT" type

XML2EN

*   output REPORT type as report

## 2.6

8/29/2003

BIB2XML

*   rename process\_article() to more accurate process\_cite()
*   fix parsing code for bibtex files generated by pybliographer
*   have all unrecognized tags outputed into xml file rather than  
    being silently dropped
*   bump version number 1.2

## 2.5

5/23/2003

UNIQBIB

*   fix bug introduced by newstring library changes in 2.3
*   clean code a bit
*   bump version number 1.1

## 2.4

4/02/2003

NEWSTR

*   add newstr\_empty() prototype

RIS2XML

*   fix core dump due to uninitialized variables (thanks Lukasz Helcyznski)
*   bump version numer 1.5

## 2.3

3/27/2003

NEWSTR

*   dramatically increase the speed of the string library by tracking  
    string length and eliminate a number of N-squared algorithms that  
    looked for string terminators

RIS2XML

*   ensure that null strings are not written out (from IEEE "RIS" format)
*   if ABSTRACT is output, do NOTES2 as well
*   don't add spaces or tabs that lead data after tag
*   fix REFNUM naming from name/year with multiauthor names
*   fix incorrect appending of line to values in scidirect ris output
*   change "error" about bad tags to "warning"
*   move all tags/values allocation/reallocation into addtag()
*   fix bug that wouldn't initialize tags/values added after reallocation
*   bump version number to 1.4

XML2BIB

*   ensure NOTES2 gets passed through
*   bump version number to 1.3

## 2.2

2/16/2003

NEWSTR

*   change name from newstr\_clear() to newstr\_free()
*   fix int/unsigned long issues in newstr\_realloc() so that truncation  
    in string length does not occur by stuffing sizes down to ints
*   fix incorrect fprintf() format for unsigned long value
*   similar int/unsigned long and unsigned int/unsigned long fixes  
    everywhere in the internal core of newstr.c
*   create newstr\_empty() to blank strings

XML

*   fix xml\_extractdata() to return the end of the string if the tagged  
    information cannot be found rather than NULL
*   switch to newstr\_empty() in xml\_readrefs()

RIS2XML

*   fix potential infinite loop in SUFF recognition for names
*   handle multiple keywords separated by semi-colons
*   handle multiple authors separated by semi-colons
*   handle items like abstracts that can go multi-line
*   bump version to 1.3

XML2BIB

*   month now uses three letter month abbreviation, not number
*   add KEYWORDS, SERIALNUM (ISBN), ISSUE (NUMBER), NOTES (NOTE),  
    REPRINTSTATUS, SECONDARYTITLE
*   bump version to 1.2

XML2RIS

*   generalize author output to person output
*   handle suffix output
*   add proper editor output
*   remove process\_authors()
*   add seriesauthors output
*   bump version to 1.2

XMLREPLACE

*   remove redefined TRUE/FALSE macros

## 2.1

2/10/2003

GENERAL

*   fix build process so easier on MacOSX's
*   add bibutils suite version stamp

XML

*   change name space: find\_xmlstartdata() to xml\_findstartdata(),  
    find\_xmlenddata() to xml\_findenddata(),  
    extract\_xmldata() to xml\_extractdata()
*   xml\_extractdata() no longer takes pointers to newstrings and  
    does not allocate them
*   make sure xml\_extractdata() clears the output string so that an  
    empty output indicates no tag
*   clean-up xml\_readrefs() and move to library xml.c--it's getting  
    replicated in xml2bib, xml2ris, xml2en anyway

NEWSTR

*   add newstring\_segcat() and newstring\_segcpy() to ease copying sections  
    out of other strings

XML2BIB

*   fix xml2bib's usage of xml\_extractdata()
*   xml2bib now passes a newstring of the extracted reference rather than a  
    bare string
*   change bibtex output to use braces around each reference rather than  
    parentheses (bibtex takes both, but WinEdt v5.3 is far more useful  
    to the user if braces are used).
*   remove dead code, switch to xml\_readref()
*   in process\_article() tags were used for both xml and bibtex, which worked  
    due to the way I set up the xml stuff, but is very difficult to ensure,  
    so setup xmltags\[\] and bibtextags\[\] so they can be different
*   handle URL items
*   handle editors like authors and generalize process\_authors() to  
    process\_people()
*   handle name suffixes in process\_people()
*   add -h/--help -v/--version flags
*   add month/day support to bibtex

XML2RIS

*   fix xml2ris's usage of xml\_extractdata()
*   legal tags can have uppercase letter _or_ digit at second position, a  
    change from the older (circa 1996) documentation
*   process\_article() gets newstring rather than a bare string
*   remove #define for number of fields in process\_article()
*   every tagged line must end in carrige return/line feed combination  
    (ASCII 13 10), another change from the circa 1996 docs -- fix
*   REFNUM in the XML should map to the ID tag, not the KW (keyword) tag
*   add NOTES/N1, SERIALNUM/SN, ISSUE/IS, URL/UR
*   remove dead code, switch to xml\_readref()
*   fix year output to handle year/month/day/other format
*   add -h/--help -v/--version flags

XML2EN

*   fix xml2en's usage of xml\_extractdata()
*   process\_article() gets newstring rather than a bare string
*   remove #define for number of fields in process\_article()
*   remove dead code, migrate to central xml\_readref()
*   add -h/--help -v/--version flags
*   switch from the tab-deliminated format to the "Tagged EndNote Import"  
    format

RIS2XML

*   update tag definition so that second character can be either  
    uppercase letter or digit
*   handle all journal tags: JO/JA/JF, picking the abbreviated forms  
    (user-defined J1/J2 then standard JO/JA) over the full form (JF) if present
*   handle all primary title tags T1/TI/CT, secondary title T2, series title  
    T3, and booktitle BT
*   take REFNUM from ID first, or build from author/year if ID absent
*   handle N1 - notes, N2/AB -abstract, UR - URL
*   handle AU/A1 - primary authors, A2/ED - editors, A3 - series authors
*   handle KW - keywords
*   add suffix support to name format
*   handle date format year/month/day/other fields
*   add -h/--help -v/--version flags

MED2XML

*   add -h/--help -v/--version flags
*   add month and day parsing

BIB2XML

*   remove dead code
*   add -h/--help -v/--version flags
*   add month and day support

XMLREPLACE

*   write program
