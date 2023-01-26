
# For developers

Currently supported: MSVC 2022 (Microsoft Visual Studio 2022) :: `/platform/win32/mupdf.sln`


# Building the tools & libraries

- Open the `mupdf.sln` solution in `Qiqqa/MuPDF/platform/win32/`

- In Visual Studio, make sure one of these build modes is selected (as shown in the Visual Studio toolbar below the main menu):

  + Debug / x64          (our preferred dev/debug build mode)
  + Release / x64       
  
  + Debug / Win32        (for 32bit machines. Not tested often, so MAY fail.)
  + Release / Win32
  
  **ANY OTHER build mode (such as 'Debug/Any CPU') WILL NOT work as expected!**
  
- select the project named `__build_target_mupdf` and right-click for pop-up menu.

- select 'Build' or 'Rebuild All', depending on whether you updated the repo / source tree or wish to build everything again from scratch.

- all compiled binaries (executables, etc.) will be produced in the directory

        Qiqqa/MuPDF/platform/win32/bin/<Debug|Release>-Unicode-<32|64>bit-x<86/64>/
	
  (Some test files and the tesseract-required trained data file sets will have been copied there too.)

- use as desired.  


## /TBD/ *Make sure to read the [detailed DEVELOPER NOTES](docs/Notes/DEVELOPER-NOTES.md)* /TBD/ 

> Those notes are managed using [Obsidian](https://obsidian.md/); it might be handy to install that tool as it simplifies browsing through those wiki-style Markdown notes stored in `/docs/Notes/`.

