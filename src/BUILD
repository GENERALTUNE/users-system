

load("@rules_cc//cc:defs.bzl", "cc_proto_library")
load("@rules_proto//proto:defs.bzl", "proto_library")
load("@com_github_grpc_grpc//bazel:cc_grpc_library.bzl", "cc_grpc_library")

cc_binary(
    name = "server",
    srcs = ["server.cc"],
    deps = ["//src/protos:user_cc_grpc"]
)



cc_binary(
    name = "client",
    srcs = ["client.cc"], 
    deps = [
    	"//src/protos:user_cc_grpc",
    	"@com_github_grpc_grpc//:grpc++"
    ]
)


# cc_binary(
#     name = "test",
#     srcs = ["test.cc"], 
#     deps = [
#         "//src/protos:user_cc_proto",
#         "@com_github_grpc_grpc//:grpc++"
#     ],
# )

