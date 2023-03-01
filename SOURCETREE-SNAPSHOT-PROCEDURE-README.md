
# Snapshot procedure for developers working on the original git submodules tree

When at least mupdf.sln :: __build_target_mupdf builds without errors, then do a snapshot.

Steps:

- label the snapshot as `snapshot-YYYYMMDD.REV` in the source git repo (currently only done for Qiqqa/MuPDF as Qiqqa/ itself is not yet viable!)

- run `utils/grab_snapshot.sh` from the snapshot repo base dir like so:

  ```sh
  utils/grab_snapshot.sh
  ```
  
  > NOTE: currently sourcetree directories are assumed to be on the Z:\ drive -- artifact from original developer.
  
- go to `Qiqqa/MuPDF\platform\win32\` and open the `mupdf.sln` MSVC solution.

- **verify** the solution's `__build_target_mupdf` does build without errors. (this step may be skipped; second **verify action** beelow may not!)

- commit the sourcetree snapshot to git repo.

- nuke the sourcetree to ensure we are not unknowingly dependant on some file that didn't geet committed into the repo:

  ```sh
  rm -rf Qiqqa/
  git reset --hard
  ```
  
- **verify** the solution's `__build_target_mupdf` does build without errors. (this step may be skipped; second **verify action** below may not!)

  > When the verification fails, fix it, append/overwrite the last git commit and re-run the nuke dirtree + verification cycle until all is well.
  
- *Extra*: label commit with same tag as done with the original repo.  

- push repo.
