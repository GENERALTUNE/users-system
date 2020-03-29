

load("@rules_cc//cc:defs.bzl", "cc_proto_library")
load("@rules_proto//proto:defs.bzl", "proto_library")
load("@com_github_grpc_grpc//bazel:cc_grpc_library.bzl", "cc_grpc_library")

cc_binary(
    name = "server",
    srcs = ["server.cc"],
    deps = [":user_cc_proto"]
)




proto_library(
    name = "user_proto",
    srcs = ["protos/user.proto"],
)

cc_proto_library(
    name = "user_cc_proto",
    deps = [":user_proto"],
)

cc_grpc_library(
    name = "user_cc_grpc",
    srcs = [":user_proto"],
    deps = [":user_cc_proto"],
    grpc_only = True,
)



cc_binary(
    name = "client",
    srcs = ["client.cc"], 
    deps = [
    	":user_cc_proto",
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

