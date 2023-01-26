# xml2end

xml2end converts the MODS XML bibliography to tagged Endnote (refer-format) bibliography file.

## Usage

xml2end usage is as for other tools

```
xml2end xml_file.xml > output_file.end
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
