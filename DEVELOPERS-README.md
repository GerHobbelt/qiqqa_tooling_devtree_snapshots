
# For developers

Currently supported: MSVC 2022 (Microsoft Visual Studio 2022) ::

- `/platform/win32/mupdf.sln` (**main project/repository Visual Studio solution**)
- `/platform/win32/mupdf_dev.sln`  (**primarily for qiqqa backend tooling devs, but when you get here, that's who you are 😉 **)


# Prerequisites

## A working `nodeJS` install

Preferrably via "nvm for windows": https://github.com/coreybutler/nvm-windows/releases

Install & "add to PATH" when asked.

Then run these commands in a "git for windows" `bash` shell console window:

```
cd ~
nvm list available
# --> pick the latest LTS version (18 now) at least;
#     if you feel frisky, add the dev + latest stable as well. These are NOT mandatory.
nvm install 18
# Optional extra 2:
nvm install 19
nvm install 20
# make sure you "activate" the LTS version.
nvm use 18
# and check its REPL mode is working...
node -i
```

... and while you're at it, make sure your Python 3.\* install is done and available via Windows search PATH by running this command in the same console window:

```
python --version
# --> Python 3.11.3
```


## NASM (Assembler) + Visual Studio add-on

> When missing, you'll see "*missing `nasm.props`*" errors when attempting a build.

You need to install the *NASM for Visual Studio add-on*:

- First, you'll first need to **install NASM** by way of https://github.com/netwide-assembler/nasm --> https://nasm.us/ --> https://www.nasm.us/pub/nasm/releasebuilds/2.16.01/win64/

  + run the downloaded NASM installer **As Administrator** and install for Everybody.
  + add `nasm` to your system `PATH` via: Windows Explorer > This PC (right-click) > Properties > Advanced System Settings > (Advanced Tab) \[Environment Variables\] > System Variables > Edit > Add
  + verify that `nasm` is found by opening a `CMD` console window and typing `nasm -v` --> expected output: `NASM version 2.16.01 compiled on Dec 21 2022`

- Then you can install the required Visual Studio 2022 add-on (VSNASM), which can be found at: https://github.com/ShiftMediaProject/VSNASM -- for install instruction, see the README there.
  + you MAY want to edit the install `.bat` script first, changing the listed NASM version from 2.16 to 2.16.01 (*iff* t hasn't been updated at the repo already)
  + you MAY want to edit the install `.bat` script first, adding a check for an already present `nasm` -- which you previously installed. (*iff* t hasn't been updated at the repo already)
  + extract the VSNASM.zip file to a fresh directory, e.g. `"C:\Users\Ger\Downloads\VSNASM"` and then run a MSVC2022 CMD **as Administrator** via: Start > Visual Studio 2022 (open submenu in Start) > Developer Command Prompt for VS 2022 (right click) > More > Run as Administrator
  + then execute these commands (or their local equivalent!) in that console window:
  
    ```
	rem CD to the VSNASM extract directory you just created:
	cd C:\Users\Ger\Downloads\VSNASM
	install_script.bat
	rem :: expected output:
	rem :: 	
	rem :: Detected 64 bit system...
	rem :: Existing Visual Studio 2022 environment detected...
	rem :: Installing build customisations...
	rem :: Checking for existing NASM in your PATH...
	rem :: NASM version 2.16.01 compiled on Dec 21 2022
	rem :: Using existing NASM binary...
	rem :: Finished Successfully
	rem :: Press any key to continue . . .
	```
	
  


## Visual Studio ATL/MFC C++ SDK component

(rewrite)

> error: "*missing `afxres.h`*"

Definitely a case of von Moltke ("no plan survives first contact")  :-) 

The `afxres.h` one is resolved by installing the MFC component in Microsoft Developer Studio, as it is obtained from there. We don't use MFC otherwise, not yet anyway. Turns out I don't suffer from this error as I always install the MFC SDK out of old habit.

You can fix this by having a look in the Visual Studio installer and see if you can get the MFC SDK/component installed. 
- Visual Studio Installer > (select VS2022) > Modify > Installation Details: Desktop Development with C++ > make sure the top few checkboxes are ticked (they mention "v143" and/or "ATL") > [Install]
- another ay is to go through the "Individual Components" list and making sure the few boxes selecting latest MFC & ATL are ticked.


![screenshot](vs-setup-img1.png)

This is a view of the Visual Studio 2022 Installer (which sits in your Windows Start menu): note the blue checks for C++ and .NET development; when you fold the right side open (as shown) for the C++ development entry, you'll notice I've got ATL + MFC ticked ON: that combo is what produces the `afxres.h` file. (And I think these might be expected as well when we start to include wxWidgets GUI work later on, so it's good to install those anyway, if they aren't already.)






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



## Known (potential) errors

### Project: libjpeg-xl

#### `Error: Command failed: git rev-parse --short HEAD`

```
    throw new Error(error);
    ^

Error : error : Command failed: git rev-parse --short HEAD
fatal: detected dubious ownership in repository at 'E:/q/qiqqa_tooling_devtree_snapshots'
'E:/q/qiqqa_tooling_devtree_snapshots' is owned by:
	'S-1-5-21-293542405-1715775699-4289769830-1001'
but the current user is:
	'S-1-5-21-3299557434-1170137790-938242690-1001'
To add an exception for this directory, call:

	git config --global --add safe.directory E:/q/qiqqa_tooling_devtree_snapshots

    at E:\q\qiqqa_tooling_devtree_snapshots\Qiqqa\MuPDF\platform\win32\patch-all-library-version-numbers.js:9:13
```

Happened to me after transporting the entire git repo across from previous hardware+disk: `git` these days is a little pickier than before when it comes to MSWindows file ownership and access rights. You might want to go through your directory tree and fix those ownership/ACL settings that came off the old sow -- I pulled this NVMe dev disk from the previous hardware rig and plugged it into the new mobo. That's when this sort of thing easily happens and your swift transfer will require some post work in Windows after all. :facepalm:

See https://stackoverflow.com/questions/73824389/how-can-i-change-the-owner-of-a-file-in-windows-command-line for one way (MSWindows system tooling) to fix this. 

> E.g. 
>
> ```
> cd
> rem :: E:\q\qiqqa_tooling_devtree_snapshots
> cd ..
> takeown /F q\* /R > NUL:
> ```
>
> from a "Run as Administrator" *elevated* `CMD` console window when you like to live dangerously.

**WARNING**: 
when you're not working on a machine you administer yourself, i.e. you're working on a machine owned by your employer/sponsor/anybody, you might need to run that suggested `git` command instead and consult your local administrator, just in case. But when you've got access to tools like `icalcs` and `takeown` on your system, then, heck yeah, you're probably your own admin. :wink: :innocent:


And this error report immediately led MSVC to produce the next one in MSVC:



#### `Error MSB3073: The command "node ./patch-all-library-version-numbers.js   jpeg-xl" exited with code 1`

```
The command "node ./patch-all-library-version-numbers.js   jpeg-xl
error MSB3073: :VCEnd" exited with code 1.
Done building project "libjpeg-xl.vcxproj" -- FAILED.
```

This means there's something oddly wrong with your git dev tree (or you haven't got one *at all*).

:thinking: I might have to patch that utility script for the occasion, I guess...




## /TBD/ *Make sure to read the [detailed DEVELOPER NOTES](Qiqqa/MuPDF/docs/Notes/DEVELOPERS-README.md)* /TBD/ 

> Those notes are managed using [Obsidian](https://obsidian.md/); it might be handy to install that tool as it simplifies browsing through those wiki-style Markdown notes stored in `/docs/Notes/`.

