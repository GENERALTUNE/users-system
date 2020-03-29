#!/bin/sh

# 测试用例
bazel  test  //test:server_test

# bazel  build //src:client

# 项目构建
bazel  build //src/main/cpp:greeter_server

