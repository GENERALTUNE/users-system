load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

git_repository(
    name = "googletest",
    remote = "https://github.com/google/googletest",
    tag = "release-1.8.1",
)

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive", "http_file")

# **************************************************************
# cpp
# **************************************************************

# load("@build_stack_rules_proto//cpp:deps.bzl", "cpp_grpc_library")
# cpp_grpc_library()
# load("@com_github_grpc_grpc//bazel:grpc_deps.bzl", "grpc_deps")
# grpc_deps()

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

#http_archive(
#    name = "rules_cc",
#    sha256 = "35f2fb4ea0b3e61ad64a369de284e4fbbdcdba71836a5555abb5e194cf119509",
#    strip_prefix = "rules_cc-624b5d59dfb45672d4239422fa1e3de1822ee110",
#    urls = [
#        "https://mirror.bazel.build/github.com/bazelbuild/rules_cc/archive/624b5d59dfb45672d4239422fa1e3de1822ee110.tar.gz",
#        "https://github.com/bazelbuild/rules_cc/archive/624b5d59dfb45672d4239422fa1e3de1822ee110.tar.gz",
#    ],
#)
#load("@rules_cc//cc:repositories.bzl", "rules_cc_dependencies")

#rules_cc_dependencies()


http_archive(
    name = "rules_proto",
    sha256 = "602e7161d9195e50246177e7c55b2f39950a9cf7366f74ed5f22fd45750cd208",
    strip_prefix = "rules_proto-97d8af4dc474595af3900dd85cb3a29ad28cc313",
    urls = [
        "https://mirror.bazel.build/github.com/bazelbuild/rules_proto/archive/97d8af4dc474595af3900dd85cb3a29ad28cc313.tar.gz",
        "https://github.com/bazelbuild/rules_proto/archive/97d8af4dc474595af3900dd85cb3a29ad28cc313.tar.gz",
    ],
)
load("@rules_proto//proto:repositories.bzl", "rules_proto_dependencies", "rules_proto_toolchains")
rules_proto_dependencies()
rules_proto_toolchains()

http_archive(
    name = "com_github_grpc_grpc",
    sha256 = "d6af0859d3ae4693b1955e972aa2e590d6f4d44baaa82651467c6beea453e30e",
    strip_prefix = "grpc-1.26.0-pre1",
    urls = [
        "https://github.com/grpc/grpc/archive/v1.26.0-pre1.tar.gz",
        ],
)
load("@com_github_grpc_grpc//bazel:grpc_deps.bzl", "grpc_deps")
grpc_deps()

load("@com_github_grpc_grpc//bazel:grpc_extra_deps.bzl", "grpc_extra_deps")
grpc_extra_deps()
