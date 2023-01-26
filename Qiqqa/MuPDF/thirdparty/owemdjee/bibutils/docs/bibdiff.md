# bibdiff

bibdiff compares two bibliography files after conversion into an internal representation

## Usage

Specify file(s) to be converted on the command line. Files containing BibTeX substitutions strings should be specified before the files where substitutions are specified (or in the same file before their use). If no files are specified, then BibTeX information will be read from standard in.

```
bib2xml [--format1 FORMAT] file1.txt [--format2 FORMAT] file2.txt
```

Valid formats are bibtex, biblatex, copac, ebi, endnote, endnote-xml, medline, mods, nbib, ris, word2007.
