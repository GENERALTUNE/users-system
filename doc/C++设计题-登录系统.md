# C++ 设计题

## 特性要求

- 设计一套登录系统，具备  注册账户、登录 功能
- 1 个账户只能在 1 个终端上登录，当切换终端登录时，其他已登录终端会被踢出

## 技术要求

- 使用 C++ 实现客户端（命令行交互即可）、服务端，代码风格良好
- 账户信息需要存储，且需考虑数据安全和传输安全，存储选型不限
- 代码托管到 [Github](https://github.com/)
- 使用 [gRPC](https://grpc.io) 框架
- 使用 [bazel]( https://bazel.build/ ) 管理编译
- 使用 [googletest]( https://github.com/google/googletest ) 做单元测试
- 接入[Travis流水线](https://travis-ci.org/)

## 交付物

- `must` 源代码、设计文档、说明文档
- `better` 已部署好的服务端

## 时间要求

- 1 周