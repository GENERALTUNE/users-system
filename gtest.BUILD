cc_library(
    name = "main",
    srcs = glob(
        ["test/*.cc"],
        exclude = []
    ),
    hdrs = glob([
        "include/**/*.h",
        # "src/*.h"
    ]),
    copts = ["-Iexternal/gtest/include"],
    linkopts = ["-pthread"],
    visibility = ["//visibility:public"],
)
