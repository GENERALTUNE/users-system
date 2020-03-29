/*
 *
 * Copyright 2015 gRPC authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#include <sstream>
#include <iostream>
#include <memory>
#include <string>
#include <fstream>

#include <grpcpp/grpcpp.h>

// #ifdef BAZEL_BUILD
// #include "examples/protos/user.grpc.pb.h"
// #else
#include "user.grpc.pb.h"
// #endif

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using user::UserLoginRequest;
using user::UserLoginReply;
using user::UserRegisterRequest;
using user::UserRegisterReply;
using user::User;



void read ( const std::string& filename, std::string& data ){
  std::ifstream file ( filename.c_str (), std::ios::in );
    if ( file.is_open () )
    {
        std::stringstream ss;
        ss << file.rdbuf ();
        file.close ();
        data = ss.str ();
    }

    return;
}


class UserClient {
 public:
  UserClient(std::shared_ptr<Channel> channel)
      : stub_(User::NewStub(channel)) {}

  // Assembles the client's payload, sends it and presents the response back
  // from the server.
  std::string Login(const std::string& username, const std::string& password) {
    // Data we are sending to the server.
    UserLoginRequest request;
    request.set_username(username);
    request.set_password(password);

    // Container for the data we expect from the server.
    UserLoginReply reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = stub_->Login(&context, request, &reply);

    // Act upon its status.
    if (status.ok()) {
      return reply.message();
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return "RPC failed";
    }
  }

  std::string Register(const std::string& username, const std::string& password, const std::string& cardnum, const std::string& name) {
    // Data we are sending to the server.
    UserRegisterRequest request;
    request.set_username(username);
    request.set_password(password);
    request.set_cardnum(cardnum);
    request.set_name(name);

    // Container for the data we expect from the server.
    UserRegisterReply reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = stub_->Register(&context, request, &reply);

    // Act upon its status.
    if (status.ok()) {
      return reply.message();
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return "RPC failed";
    }
  }

 private:
  std::unique_ptr<User::Stub> stub_;
};

int main(int argc, char** argv) {
  // Instantiate the client. It requires a channel, out of which the actual RPCs
  // are created. This channel models a connection to an endpoint (in this case,
  // localhost at port 50051). We indicate that the channel isn't authenticated
  // (use of InsecureChannelCredentials()).
  // std::string key;
  // std::string cert;
  // std::string root;

  // read ( "ca.crt", root );

  // grpc::SslCredentialsOptions opts ={root,key,cert};


  // auto channel_creds = grpc::SslCredentials(grpc::SslCredentialsOptions(opts));

  // auto channel = grpc::CreateChannel("localhost:6613", channel_creds);

  // GreeterClient user(grpc::CreateChannel(
  //     "localhost:50051", channel_creds));

    UserClient user(grpc::CreateChannel(
      "106.14.56.249:3389", grpc::InsecureChannelCredentials()));
    std::string choose_func;
    std::cout << "请选择功能: 1 登录  2 注册"<<std::endl;
    std::cin >> choose_func ;
    if ( choose_func == "1") {
      // 登录逻辑
      std::cout << "请输入你的账号"<<std::endl;
      std::string username;
      std::string password;
      std::cin>>username;
      std::cout << "请输入你的密码"<<std::endl;
      std::cin>>password;  
      std::cout<< "已输入账号密码为："<<username << password<<std::endl;
      std::string reply = user.Login(username, password);
      std::cout << "服务器返回信息: " << reply << std::endl;


    } else if (choose_func == "2") {
      //注册逻辑
      std::string username;
      std::string password;
      std::string cardnum;
      std::string name;
      std::cout << "请输入账号"<<std::endl;
      std::cin >> username;
      std::cout << "请输入密码"<<std::endl;
      std::cin >> password;
      std::cout << "请输入身份证号"<<std::endl;
      std::cin >> cardnum;
      std::cout << "请输入昵称"<<std::endl;
      std::cin >> name;
      std::cout<< "已输入账号密码身份证昵称为："<<username << password<<std::endl;
      std::string reply = user.Register(username, password, cardnum, name);
      std::cout << "服务器返回信息: " << reply << std::endl;


    } else {
      //输入错误！
      std::cout<< "输入错误！"<<std::endl;
      return 1;
    }


  return 0;
}
