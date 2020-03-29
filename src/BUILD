cc_binary(
    name = "server",
    srcs = ["server.cc"],
    deps = [":user_cc_proto"],
)

cc_binary(
    name = "client",
    srcs = ["client.cc"],
    deps = ["//src/protos:user_cc_proto"],
)

