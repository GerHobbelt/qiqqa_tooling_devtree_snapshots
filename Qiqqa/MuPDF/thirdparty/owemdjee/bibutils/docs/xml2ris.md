# xml2ris

xml2ris converts the MODS XML bibliography to RIS-formatted bibliography file. xml2ris usage is as for other tools

xml2ris xml\_file.xml > output\_file.ris

## Flags

| Flag | Description |
| --- | --- |
| \-h, --help | report help |
| \-v, --version | report version information |
| \-nb, --no-bom | do not write Byte Order Mark if writing UTF-8 |
| \-s, --single-refperfile | put one reference per file name by the reference number |
| \-i, --input-encoding | interpret the input file as using the requested character set (use w/o argument for current list) unicode is now a character set option |
| \-o, --output-encoding | write the output file using the requested character set (use w/o argument for current list) unicode is now a character set option |
| \--verbose | for verbose output |
| \--debug | for debug output |
