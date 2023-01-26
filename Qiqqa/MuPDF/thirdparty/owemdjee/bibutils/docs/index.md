## Description:

The bibutils program set interconverts between various bibliography formats using a common MODS-format XML intermediate. For example, one can convert RIS-format files to Bibtex by doing two transformations: RIS->MODS->Bibtex. By using a common intermediate for N formats, only 2N programs are required and not N²-N. These programs operate on the command line and are styled after standard UNIX-like filters.

I primarily use these tools at the command line, but they are suitable for scripting and have been incorporated into a number of different bibliographic projects.

The Library of Congress's Metadata Object Description Schema (MODS) XML format is described [here](http://www.loc.gov/standards/mods/). I've written a [short introduction](Working.with.MODS.html) to using MODS that might be useful.

## Programs:

| Program | Description |
| --- | --- |
| [bib2xml](bib2xml.html) | convert BibTeX to MODS XML intermediate |
| [biblatex2xml](biblatex2xml.html) | convert BibLaTeX to MODS XML intermediate |
| [bibdiff](bibdiff.html) | compare two bibliographies after reading into the bibutils internal format |
| [copac2xml](copac2xml.html) | convert COPAC format references to MODS XML intermediate |
| [end2xml](end2xml.html) | convert EndNote (Refer format) to MODS XML intermediate |
| [endx2xml](endx2xml.html) | convert EndNote XML to MODS XML intermediate |
| [isi2xml](isi2xml.html) | convert ISI web of science to MODS XML intermediate |
| [med2xml](med2xml.html) | convert Pubmed XML references to MODS XML intermediate |
| [modsclean](modsclean.html) | a MODS to MODS converter for testing puposes mostly |
| nbib2xml | convert Pubmed/National Library of Medicine nbib format to MODS XML intermedidate |
| [ris2xml](ris2xml.html) | convert RIS format to MODS XML intermediate |
| [xml2ads](xml2ads.html) | convert MODS XML intermediate into Smithsonian Astrophysical Observatory (SAO)/National Aeronautics and Space Administration (NASA) Astrophyics Data System or ADS reference format (converter submitted by Richard Mathar) |
| [xml2bib](xml2bib.html) | convert MODS XML intermediate into BibTeX |
| xml2biblatex | convert MODS XML intermediate into BibLaTeX |
| [xml2end](xml2end.html) | convert MODS XML intermediate into format for EndNote |
| [xml2isi](xml2isi.html) | convert MODS XML intermediate to ISI format |
| xml2nbib | convert MODS XML intermediate to Pubmed/National Library of Medicine nbib format |
| [xml2ris](xml2ris.html) | convert MODS XML intermediate into RIS format |
| [xml2wordbib](xml2wordbib.html) | convert MODS XML intermediate into Word 2007 bibliography format |

## Development History:

*   [Version 6](history_version6/index.html). Library changes forced change of major version.
*   [Version 5](history_version5/index.html). User visible changes change default input and output character set to UTF-8 Unicode and ability to write MODS XML in multiple character sets.
*   [Version 4](history_version4/index.html). User visible changes are alteration of library API.
*   [Version 3](history_version3/index.html)
*   [Version 2](history_version2/index.html)

## Frequently Asked Questions:

_The programs don't run for me. What am I doing wrong?_ If you send me this question, I would immediately have to ask for more information. So do us both a favor and provide more information. The follow items address specific problems:

_"command not found"_ The message "command not found" on Linux/UNIX/MacOSX systems indicates that the commands cannot be found. This could mean that the programs are not flagged as being executable (run "chmod ugo+x xml2bib" for the appropriate binaries) or the executables are not in your current path (and have to be specified directly like ./xml2bib). A quick web search on chmod or path variables should provide many detailed resources.

_I'm running MacOSX and I just get a terminal when I double-click on the programs._ Simply put, this is not the way to run the programs. You want to run the terminal first and then issue the commands at the command line. It should be under Applications->Utilities->Terminal on most MacOSX systems I've seen. If you just double-click the program, the terminal corresponds to the input to the tool. Not so useful. Some links to get you started running the terminal in a standard UNIX-like fashion are at [TerminalBasics.pdf](http://homepage.mac.com/rgriff/files/TerminalBasics.pdf), [macdevcenter.com](http://www.macdevcenter.com/pub/ct/51), and [ee.surrey.ac.uk](http://www.ee.surrey.ac.uk/Teaching/Unix/).

_This stuff is great, how can I help?_ OK, I actually don't get this question so often, though I have gotten very useful help through people who have willingly sent useful bug reports and sample problematic data to allow me to test these programs. I willingly accept bug reports, patches, new filters, suggestions on program improvements or better documentation and the like. All I can say is that users (or programmers) who contact me with these sorts of things are far more likely to get their itches scratched.

I am interested in bug reports and problems in conversions. Feel free to e-mail me if you run into these issues. The absolute best bug reports provide error messages from the operating systems and/or input and outputs that detail the problems. Please remember that I'm not looking over your shoulder and I cannot read your mind to figure out what you are doing--"It doesn't work." isn't a bug report I can help you with.

## License

All versions of bibutils are relased under the GNU Public License (GPL) version 2. In a nutshell, feel free to download, run, and modify these programs as required. If you re-release these, you need to release the modified version of the source. (And I'd appreciate patches as well...if you care enough to make the change, then I'd like to see what you're adding or fixing.)
