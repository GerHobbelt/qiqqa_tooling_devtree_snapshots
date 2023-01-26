## 5.11

11/7/16

NBIB2XML

*   Add program

BIBTEXOUT

*   Handle MRNUMBER

## 5.10

11/2/16

BIBTEXIN

*   Handle MRNUMBER and CODEN tags

## 5.9

9/12/16

GLOBAL

*   Allow bibutils to properly process references with several authors of the same name (reported by Jason Annadani).

MODSIN

*   Fix processing of mods input files where given name information isn't as finely parsed as bibutils mods files are (reported by Dan Gildea).

## 5.8

5/23/16

INTERNAL

*   Change xxx\_convertf() functions to use tables of function pointers
    
*   Use generic function pointers whenever possible to decrease duplicated code
    

ADSOUT

\*Improve URL handling

BIBLATEXIN

*   Identify JSTOR

BIBTEXOUT

*   Handle PMC identifiers
    
*   Fix chapter/title for @inbook references (reported by Vivek Botcha)
    

RISOUT

*   Handle PMC identifiers

## 5.7

2/15/16

MODSIN

*   Handle relatedItem original information (reported by John Vandenberg)

BIBTEXOUT

*   Resolve INBOOK/MISC problems (reported by John Vandenberg)
    
*   Improve output of latex macros (reported by John Vandenberg)
    

RISIN

*   Recognize URL's buried in the notes field
    
*   Properly propagate situation when journal name in RIS is under "T2"--short title, not "JF"--journal title (reported by Mary Martin)
    

GLOBAL

*   Update library components to current versions
    
*   Improve error propagation
    
*   Lots of small fixes found by clang --analyze
    

## 5.6

1/26/15

MODSOUT

*   Fix array that was too small (reported by dcb314@users.sf.net)
    
*   Lots of cleanups
    

## 5.5

11/15/14

GLOBAL

*   Improve error propagation in library

MODSIN

*   Improve handling of language information and handle iso639-1, iso639-2, and iso639-3 codes

XML2END

*   Output DOI as '%R' in addition to url in '%U'
    
*   Improve recognition of reference types in MODS records
    

XML2RIS

*   Improve recognition of reference types in MODS records

## 5.4

03/24/14

BIB2XML/BIBLATEX2XML

*   Do not use latex in references to external files (reported by JVilhena)

WORDOUT

*   Output url information (reported by danieldedo)

## 5.3

03/06/14

BUILD

*   Remove type 'uint' from lib/bibtexin.c and lib/biblatexin.c
    
*   Handle additional latex forms of C with cedilla
    

## 5.2

09/03/13

BIBLATEXIN

*   Protect conversion of tilde in URLs

## 5.1

09/03/13

BUILD

*   Fix make install (reported by Jens Petersen)
*   Fix cygwin skipping of ranlib (reported by Doug McIlroy)

BIBTEXIN

*   Fix string concatenation and string variable usage

BIBLATEXIN

*   Fix string concatenation and string variable usage
*   Add additional recognized reference types (reported by Nick Bart)

## 5.0

05/27/13

USER VISIBLE CHANGES

*   Make default character set unicode
*   Enable -o --output-encoding for the xxx2xml converters

BUILD

*   Ensure binary directory target exists (reported by Thomas Fischer)
*   Tell cp to preserve symbolic links when copying dynamic library (reported by Thomas Fischer)
*   Remove bashisms from sh script (reported by JeffH)

BIBLATEXIN

*   Handle 'shorttitle' tag (reported by Nick Bart)
*   Make asis/corp file work again (reported by JeffH)
*   Map 'pubstate' tag to note type="publication status" similar to [http://ufdc.ufl.edu/help/pubstatus](http://ufdc.ufl.edu/help/pubstatus) (suggested by Nick Bart)
*   Handle 'series' tag in [@report](https://sourceforge.net/u/report/) (reported by Nick Bart)
*   Map 'series' in [@article](https://sourceforge.net/u/article/) to partName of journal title (reported by Nick Bart)
*   Write 'annotation' as special type of note (reported by Nick Bart)

BIBTEXIN

*   Make asis/corp file work again (reported by JeffH)

RISOUT

*   Ensure that BT fields are written for conference publications (reported by Matthias Stevens)
*   Ensure that ED fields are used for editors of conference publications (reported by Matthias Stevens)

MODS

*   Fix inappropriate "language" tags under languageOfCataloging (reported by Nick Bart)

NAME MANGLING

*   Improve handling of prefixes to given names, e.g. "van der" in "van der Sande"
