
cc_library(
    name = "mysql_connector",
    srcs =glob( [
        "mysql-connector-cpp/build/target/lib64/*.so",
    ]),
    hdrs = glob([
        # "mysql-connector-cpp/build/target/include/jdbc/cppconn/*.h",
        "mysql-connector-cpp/build/target/include/**/*.h",
    ]),
    # hdrs = ["mysql-connector-cpp/include/jdbc/cppconn/driver.h"],
    includes = [
        # "mysql-connector-cpp/build/target/include/jdbc/cppconn/",
    ],
    # include_prefix = "third_party/mysql-connector/include/jdbc/cppconn",
    linkstatic = 0,
    visibility = [
        "//visibility:public",
    ],
)


# cc_library(
#     name = "mysqlcpp",
#     # or use -Lxxx -lstatic.a option in cc_binary linkopts to link to static library
#     srcs = select({
#         "@bazel_tools//src/conditions:darwin": ["mysqlcppconn_prebuilt/lib64/libmysqlcppconn8.dylib"],
#         "@bazel_tools//src/conditions:linux_x86_64": ["mysqlcppconn_prebuilt/lib64/libmysqlcppconn8.so"],
#         "//conditions:default": ["mysqlcppconn_prebuilt/lib64/libmysqlcppconn8.so"]
#         }
#            ),
#     hdrs = glob(["mysqlcppconn_prebuilt/include/**/*.h"]),
#     includes = ["mysqlcppconn_prebuilt/include"],
#     visibility = ["//visibility:public"]
#     )