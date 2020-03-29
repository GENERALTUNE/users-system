package(default_visibility = ["//visibility:public"])

load("@rules_cc//cc:defs.bzl", "cc_proto_library")
load("@rules_proto//proto:defs.bzl", "proto_library")
load("@com_github_grpc_grpc//bazel:cc_grpc_library.bzl", "cc_grpc_library")

proto_library(
    name = "user_proto",
    srcs = ["user.proto"],
)

cc_proto_library(
    name = "user_cc_proto",
    deps = [":user_proto"],
)

cc_grpc_library(
    name = "user_cc_grpc",
    srcs = [":user_proto"],
    deps = [":user_cc_proto"],
    # grpc_only = True,
)
