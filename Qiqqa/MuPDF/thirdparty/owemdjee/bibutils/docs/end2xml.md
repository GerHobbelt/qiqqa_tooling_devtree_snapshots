# end2xml

end2xml converts a text endnote-formatted reference file to an XML-intermediate bibliography file. This program will not work on the binary library; the file needs to be exported first.

## Refer-formatted Endnote

Endnote tagged formats ("Refer" format export) look like:

```
%0 Journal Article
%A C. D. Putnam
%A C. S. Pikaard
%D 1992
%T Cooperative binding of the Xenopus RNA polymerase I 
 transcription factor xUBF to repetitive ribosomal gene enhancers
%J Mol Cell Biol
%V 12
%P 4970-4980
%F Putnam1992
```

There are very nice instructions for making sure that you are properly exporting this at [http://www.sonnysoftware.com/endnoteimport.html](http://www.sonnysoftware.com/endnoteimport.html)

## Usage

end2xml endnote\_file.end > output\_file.xml

## Flags

Several flags available for input and MODS XML output:

| Flag | Description |
| --- | --- |
| \-h, --help | display help |
| \-v, --version | display version |
| \-a, --add-refcount | add "\_#", where # is reference count to reference id |
| \-s, --single-refperfile | put one reference per file name by the reference number |
| \-i, --input-encoding | interpret the input file as using the requested character set (use w/o argument for current list of character sets) unicode is now a character set option |
| \-u, --unicode-characters | encode unicode characters directly in the file rather than as XML entities (default) |
| \-un,--unicode-no-bom | as -u, but don't include a byte order mark |
| \-x, --xml-entities | change default UTF8-encoded characters to XML entities (opposite of -u) |
| \-nl, --no-latex | do not covert latex character combinations (bib2xml) |
| \-d, --drop-key | don't put citation key in the mods id field |
| \-c, --corporation-file | with argument specifying a file containing a list of corporation names to be placed in <name type="corporate"></name> instead of type="personal" and eliminate name mangling |
| \-as, --asis | specify file of names that shouldn't be mangled |
| \-nt, --nosplit-title | don't split titles into TITLE/SUBTITLES pairs |
| \--verbose | verbose output |
| \--debug | very verbose output (mostly for debugging) |
