// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: user.proto

#include "user.pb.h"
#include "user.grpc.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/channel_interface.h>
#include <grpcpp/impl/codegen/client_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/message_allocator.h>
#include <grpcpp/impl/codegen/method_handler.h>
#include <grpcpp/impl/codegen/rpc_service_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/server_callback_handlers.h>
#include <grpcpp/impl/codegen/server_context.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/sync_stream.h>
namespace user {

static const char* User_method_names[] = {
  "/user.User/Login",
  "/user.User/Register",
};

std::unique_ptr< User::Stub> User::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< User::Stub> stub(new User::Stub(channel));
  return stub;
}

User::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel)
  : channel_(channel), rpcmethod_Login_(User_method_names[0], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_Register_(User_method_names[1], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status User::Stub::Login(::grpc::ClientContext* context, const ::user::UserLoginRequest& request, ::user::UserLoginReply* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_Login_, context, request, response);
}

void User::Stub::experimental_async::Login(::grpc::ClientContext* context, const ::user::UserLoginRequest* request, ::user::UserLoginReply* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_Login_, context, request, response, std::move(f));
}

void User::Stub::experimental_async::Login(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::user::UserLoginReply* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_Login_, context, request, response, std::move(f));
}

void User::Stub::experimental_async::Login(::grpc::ClientContext* context, const ::user::UserLoginRequest* request, ::user::UserLoginReply* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_Login_, context, request, response, reactor);
}

void User::Stub::experimental_async::Login(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::user::UserLoginReply* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_Login_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::user::UserLoginReply>* User::Stub::AsyncLoginRaw(::grpc::ClientContext* context, const ::user::UserLoginRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::user::UserLoginReply>::Create(channel_.get(), cq, rpcmethod_Login_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::user::UserLoginReply>* User::Stub::PrepareAsyncLoginRaw(::grpc::ClientContext* context, const ::user::UserLoginRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::user::UserLoginReply>::Create(channel_.get(), cq, rpcmethod_Login_, context, request, false);
}

::grpc::Status User::Stub::Register(::grpc::ClientContext* context, const ::user::UserRegisterRequest& request, ::user::UserRegisterReply* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_Register_, context, request, response);
}

void User::Stub::experimental_async::Register(::grpc::ClientContext* context, const ::user::UserRegisterRequest* request, ::user::UserRegisterReply* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_Register_, context, request, response, std::move(f));
}

void User::Stub::experimental_async::Register(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::user::UserRegisterReply* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_Register_, context, request, response, std::move(f));
}

void User::Stub::experimental_async::Register(::grpc::ClientContext* context, const ::user::UserRegisterRequest* request, ::user::UserRegisterReply* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_Register_, context, request, response, reactor);
}

void User::Stub::experimental_async::Register(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::user::UserRegisterReply* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_Register_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::user::UserRegisterReply>* User::Stub::AsyncRegisterRaw(::grpc::ClientContext* context, const ::user::UserRegisterRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::user::UserRegisterReply>::Create(channel_.get(), cq, rpcmethod_Register_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::user::UserRegisterReply>* User::Stub::PrepareAsyncRegisterRaw(::grpc::ClientContext* context, const ::user::UserRegisterRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::user::UserRegisterReply>::Create(channel_.get(), cq, rpcmethod_Register_, context, request, false);
}

User::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      User_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< User::Service, ::user::UserLoginRequest, ::user::UserLoginReply>(
          std::mem_fn(&User::Service::Login), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      User_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< User::Service, ::user::UserRegisterRequest, ::user::UserRegisterReply>(
          std::mem_fn(&User::Service::Register), this)));
}

User::Service::~Service() {
}

::grpc::Status User::Service::Login(::grpc::ServerContext* context, const ::user::UserLoginRequest* request, ::user::UserLoginReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status User::Service::Register(::grpc::ServerContext* context, const ::user::UserRegisterRequest* request, ::user::UserRegisterReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace user
