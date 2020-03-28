#!/bin/sh

# 测试用例
bazel  test  //test:server_test
# 项目构建
bazel  build //src/protos:user_cc_grpc

