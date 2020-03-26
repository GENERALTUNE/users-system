

cc_test(
    name = "server_test",
    # srcs = ["server_test.cc"],
    srcs = glob(["**/*.cc"]),
    copts = ["-Iexternal/gtest/include"],
    deps = [
        "@googletest//:gtest_main",
        # "//lib:hello-greet",
    ],
)

# cc_test(
#     name = "bazeltests",
#     srcs = glob(["**/*.cc"]),
#     deps = [
#         "//src/lib:GreetingLib",
#         "@googletest//:gtest_main",
#     ],
# )

# cc_test(
#     name = "tests",
#     srcs = glob(["**/*.cc"]),
#     deps = [
#         "//src/lib:GreetingLib",
#         "@googletest//:gtest_main",
#     ],
# )


## execute it   cd ..   bazel test //test:server_test
#  execute it  cd .. bazel   test  //test:bazeltests