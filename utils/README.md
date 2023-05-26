
[`grab_snapshot.sh`](https://github.com/GerHobbelt/qiqqa_tooling_devtree_snapshots/blob/main/utils/grab_snapshot.sh) is the script we run to produce each *snapshot*.

As stated in the script itself, this assumes you're running on MS Windows and have a fully kited out git-on-windows dev rig set up, including a working `bash` and `PATH` set up properly so we can invoke MSWindows tools such as `robocopy` to do our bidding.

---

### Note

The other shell scripts in here are an addendum, meant to help with overly large files in the actual snapshot, if & when those occur: github/git doesn't accept those unless you have additional *git LFS* space set up and I've found that that one is way too much hassle for the few suspects that *may* trigger github/git limits: I expect a few `tesseract` training files *may* end up too large, when we produce tesseract 5.x+3.x *training archives*.
