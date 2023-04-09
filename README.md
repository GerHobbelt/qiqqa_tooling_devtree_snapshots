# Qiqqa tooling dev source tree snapshots

⚠️ **Experimental!** ⚠️

## What?

This repo carries full source tree snapshots of [the Qiqqa tooling dev source tree](https://github.com/GerHobbelt/mupdf) for when you don't want to be bothered with git/submodules management intricacies.

Unused / unreferenced research libraries are not included in these snapshots: this monolithic source tree attempts to represent only those bits of the R&D dev tree that *build* to usable tools. *This does not mean we exclude test applications: those are *useful* too, if from a slightly different developer perspective.*


## Why & For Whom?

Two reasons (or *three*...):

- provide a simplified, *monolithic = all-you-need-is-in-here*, dev source tree to (*re*)build all the tools from source: utilities, main application(s), tests (as applications) for everyone who doesn't want to be bothered about managing git repo trees (a.k.a. git submodules management)
- reference point for future releases and patches/updates, where we don't want a sliver of doubt about the *precise* state of all the source code involved when backpedalling during debug/diagnostic sessions following bug reports and such-like. This repo then serves as a 'second \[reference\] opinion' whenever we question the master dev source tree state.
- provide a second, *Builds-At-Head* home on the big dev box, while we are doing bleeding edge / riskier stuff in [the mainline repo tree](https://github.com/GerHobbelt/mupdf). So we always have a second set of the same tools available, which are known to work (more or less[^1])

[^1]: we don't guarantee everything in here is faultless *or will even build correctly*, **but:** we do guarantee that every snapshot at least has a minimal set of tools that *do* build/link correctly. We try not to introduce *completely b0rked* snapshots, though quality of build & operations may temporarily decrease as we proceed towards a better future. 😉


# How?

- the snapshots are created using tooling ([scripts 'n' stuff](https://github.com/GerHobbelt/qiqqa_tooling_devtree_snapshots/tree/main/utils)); initially some parts might be done manually. The *goal* is to have the snapshot process manually triggered (management decision!) and then executed fully automatically.
- **when you use this repo as a dev and apply changes, be very cautious about feeding those changes back into the master dev tree!** As this feeding-back is a hairy and costly process (due to this repo storing *snapshots* which are, by definition, historical, i.e. *lagging behind*), we DO NOT accept pull-reqs on this nor do we endorse or advise using this snapshot source tree repo for any other purpose than *non-modifiable reference material* applications, such as mentioned in the 'Why?' section above.


