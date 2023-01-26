# xml2wordbib

xml2wordbib converts the MODS XML bibliography to Word 2007-formatted XML bibliography file.

## Usage

xml2word usage is as for other tools

```
xml2wordbib xml_file.xml > output_file.word.xml
```

## Flags

| Flag | Description |
| --- | --- |
| \-h, --help | display help |
| \-v, --version | display program version |
| \-nb, --no-bom | do not write Byte Order Mark if writing UTF8 |
| \-s, --single-refperfile | put one reference per file name by the reference number |
| \-i, --input-encoding | interpret the input file as using the requested character set (use w/o argument for current list) unicode is now a character set option |
| \-o, --output-encoding | write the output file with the requested character set (use w/o argument for current list) |
| \--verbose | for verbose output |
| \--debug | for debug output |
