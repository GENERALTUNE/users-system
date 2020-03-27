cc_library(
    name = "lib",
    deps = [":user_cc_proto"],
)

cc_proto_library(
    name = "user_cc_proto",
    deps = [":user_proto"],
)

proto_library(
    name = "user_proto",
    srcs = ["../protos/user.proto"]
)



#load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
# load(
#     "//bazel:grpc_build_system.bzl",
#     "grpc_cc_library",
#     "grpc_generate_one_off_targets",
#     "grpc_upb_proto_library",
#     "python_config_settings",
# )
##引入grpc start ##############################
# http_archive(
#     name = "com_github_grpc_grpc",
#     urls = [
#         "https://github.com/grpc/grpc/archive/YOUR_GRPC_COMMIT_SHA.tar.gz",
#     ],
#     strip_prefix = "grpc-YOUR_GRPC_COMMIT_SHA",
# )

# load("@com_github_grpc_grpc//bazel:grpc_deps.bzl", "grpc_deps")

# grpc_deps()

# load("@rules_cc//cc:defs.bzl", "cc_binary")

# cc_binary(
#     name = "server",
#     srcs = ["server.cc"],
# )

# cc_binary(
#     name = "client",
#     srcs = ["client.cc"],
# )

##引入grpc end ##############
