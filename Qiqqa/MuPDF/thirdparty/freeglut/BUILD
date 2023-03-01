# FIXME, only works on linux.
cc_library(
    name = "glut",
    srcs = glob(
        [
            "src/*.c",
            "src/x11/*.c", # fixme
            # "src/egl/*.c"
        ],
        exclude = [
            "src/gles_stubs.c"
        ]
    ),
    hdrs = glob(
        [
            "src/*.h",
            "src/x11/*.h", # fixme
            "src/egl/*.h"
        ],
    ),
    deps = [
        ":includes",
        ":utils",
    ],
    includes = ["src"],
    linkopts = ["-lGL", "-lX11"],
    visibility = ["//visibility:public"]
)

cc_library(
    name = "utils",
    srcs = [
        "src/util/xparsegeometry_repl.c", 
        "src/util/xparsegeometry_repl.h"
    ],
)


cc_library(
    name = "includes",
    hdrs = glob(["include/GL/*.h"]),
    includes = ["include"],
    visibility = ["//visibility:public"]
)