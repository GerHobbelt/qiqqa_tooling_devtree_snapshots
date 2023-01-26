# xml2bib

xml2bib converts the MODS XML bibliography into a BibTeX-formatted reference file.

## Usage

xml2bib usage is as for other tools

xml2bib xml\_file.xml > output\_file.bib

Starting with 3.24, xml2bib output uses lowercase tags and mixed case reference types for better interaction with Emacs. The older behavior with all uppercase tags/reference types can still be generated using the command-line switch -U/--uppercase.

## Flags

| Flag | Description |
| --- | --- |
| \-h, --help | report help |
| \-v, --version | report version information |
| \-at, --abbreviatedtitles | use abbreviated titles, if available |
| \-fc, --finalcomma | add final comma in the BibTeX output for those that want it |
| \-sd, --singledash | use one dash instead of two (latex endash) in page ranges |
| \-b, --brackets | use brackets instead of quotation marks around field data |
| \-w, --whitespace | add beautifying whitespace to output |
| \-sk, --strictkey | ensure only alphanumeric characters are used BibTeX reference keys (overly strict but useful for other programs) |
| \-nl, --no-latex | do not convert characters that can be converted to latex entities into latex entities |
| \-nb, --no-bom | do not write Byte Order Mark in UTF8 output |
| \-U, --uppercase | use all uppercase for tags (field names) and reference types (pre-3.24 behavior) |
| \-s, --single-refperfile | put one reference per file name by the reference number |
| \-i, --input-encoding | interpret the input file as using the requested character set (use w/o argument for current list), UTF8 unicode is now the default option |
| \-o, --output-encoding | write the input file with the requested character set (use w/o argument for current list), unicode is now a character set option |
| \--verbose | verbose output |
| \--debug | debug output |

## Default Output

```
@Article{Putnam1992, 
author="C. D. Putnam
and C. S. Pikaard",
year="1992",
month="Nov",
title="Cooperative binding of the Xenopus RNA polymerase I transcription 
factor xUBF to repetitive ribosomal gene enhancers",
journal="Mol Cell Biol",
volume="12",
pages="4970--4980",
number="11"}
```

## Final Comma

```
@Article{Putnam1992, 
author="C. D. Putnam
and C. S. Pikaard",
year="1992",
month="Nov",
title="Cooperative binding of the Xenopus RNA polymerase I transcription 
factor xUBF to repetitive ribosomal gene enhancers",
journal="Mol Cell Biol",
volume="12",
pages="4970--4980",
number="11",}
```

## Single Dash

```
@Article{Putnam1992, 
author="C. D. Putnam
and C. S. Pikaard",
year="1992",
month="Nov",
title="Cooperative binding of the Xenopus RNA polymerase I transcription 
factor xUBF to repetitive ribosomal gene enhancers",
journal="Mol Cell Biol",
volume="12",
pages="4970-4980",
number="11"}
```

## Whitespace

```
@Article{Putnam1992,
  author =      "C. D. Putnam
                and C. S. Pikaard",
  year =        "1992",
  month =       "Jan",
  title =       "Cooperative binding of the Xenopus RNA polymerase I
 transcription factor xUBF to repetitive ribosomal gene enhancers",
  journal =     "Mol Cell Biol",
  volume =      "12",
  pages =       "4970--4980"
}
```

## Brackets

```
@Article{Putnam1992,
author={Putnam, C. D.
and Pikaard, C. S.},
title={Cooperative binding of the Xenopus 
RNA polymerase I transcription factor xUBF 
to repetitive ribosomal gene enhancers},
journal={Mol Cell Biol},
year={1992},
month={Nov},
volume={12},
number={11},
pages={4970--4980}
}
```

## Uppercase

```
@ARTICLE{Putnam1992,
AUTHOR="Putnam, C. D.
and Pikaard, C. S.",
TITLE="Cooperative binding of the Xenopus
RNA polymerase I transcription factor xUBF
to repetitive ribosomal gene enhancers",
JOURNAL="Mol Cell Biol",
YEAR="1992",
MONTH="Nov",
VOLUME="12",
NUMBER="11",
PAGES="4970--4980"
}
```
