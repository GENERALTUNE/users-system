load("@rules_cc//cc:defs.bzl", "cc_proto_library")
load("@rules_proto//proto:defs.bzl", "proto_library")
load("@com_github_grpc_grpc//bazel:cc_grpc_library.bzl", "cc_grpc_library")

cc_binary(
    name = "server",
    srcs = glob(["server.cc", "server/*.cc", "server/*.h", "server/**/*.h"]),
    copts = [
      #   "-I/usr/local/include",
	    	# "-I/usr/local/include/mysql",
	   ],
    linkopts = [
		# "-L//third_party/mysql-connector-cpp/build/target/lib64 -lmysqlcppconn8",
		# "-L/usr/lib64/mysql  -lmysqlclient"
         ],
    deps = [
    	"//src/protos:usersystem_cc_grpc",
    	"@com_github_grpc_grpc//:grpc++",
        "//third_party:mysql_connector"
    ]
)

# cc_binary(
#     name = "client",
#     srcs = ["client.cc"], 
#     deps = [
#     	"//src/protos:user_cc_grpc",
#     	"@com_github_grpc_grpc//:grpc++"
#     ]
# )

# cc_binary(
#     name = "test",
#     srcs = ["test.cc"], 
#     deps = [
#         "//src/protos:user_cc_proto",
#         "@com_github_grpc_grpc//:grpc++"
#     ],
# )

