

cc_binary(
    name = "server",
    srcs = ["server.cc"],
    deps = [":user_cc_proto"],
)


cc_binary(
    name = "client",
    srcs = ["client.cc"], 
    deps = [
    	"//src/protos:user_cc_proto",
    	# "@com_github_grpc_grpc//:grpc++"
    ],
)


cc_binary(
    name = "test",
    srcs = ["test.cc"], 
    deps = [
        "//src/protos:user_cc_proto",
        # "@com_github_grpc_grpc//:grpc++"
    ],
)

