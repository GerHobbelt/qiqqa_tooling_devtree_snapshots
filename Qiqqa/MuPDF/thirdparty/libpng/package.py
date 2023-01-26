# -*- coding: utf-8 -*-

name = "libpng"

version = "1.6.38"

authors = [
    "Cosmin Truta",
    "Guy Eric Schalnat",
    "Andreas Dilger",
    "Glenn Randers-Pehrson",
]

requires = [
    "gcc",
    "cmake",
]

def commands():
    env.PNG_ROOT = "{root}"
    env.PNG_LOCATION = "{root}"
    env.PATH.append("{root}/bin")

uuid = "repository.libpng"
