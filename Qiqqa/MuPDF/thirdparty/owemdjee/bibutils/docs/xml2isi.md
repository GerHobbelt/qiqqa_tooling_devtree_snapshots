# xml2isi

xml2isi converts the MODS XML bibliography to an ISI-format bibliography file.

## Usage

xml2isi usage is as for other tools

```
xml2isi xml_file.xml > output_file.isi
```

## Flags

| Flag | Description |
| --- | --- |
| \-h, --help | report help |
| \-v, --version | report version information |
| \-nb, --no-bom | do not write Byte Order Mark in UTF8 output |
| \-s, --single-refperfile | put one reference per file name by the reference number |
| \-i, --input-encoding | interpret the input file as using the requested character set (use w/o argument for current list) unicode is now a character set option |
| \-o, --output-encoding | write the output file using the requested character set (use w/o argument for current list) |
| \--verbose | for verbose output |
| \--debug | for debug output |
