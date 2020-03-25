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

#include <iostream>
#include <memory>
#include <string>
#include <fstream>

#include <grpcpp/grpcpp.h>

#ifdef BAZEL_BUILD
#include "examples/protos/user.grpc.pb.h"
#else
#include "user.grpc.pb.h"
#endif

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
      : stub_(Greeter::NewStub(channel)) {}

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
    request.set_password(cardnum);
    request.set_password(name);

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

    GreeterClient user(grpc::CreateChannel(
      "localhost:50051", grpc::InsecureChannelCredentials()));

    std::cout << "请输入你的账号密码"<<std::endl;
    std::string username;
    std::string password;
    std::cin>>username>>password;                                                                                      86    std::cout<< "账号密码位："<<user << password<<std::endl;
    std::string reply = user.Login(username, password);
    
    std::cout << "User received: " << reply << std::endl;

  return 0;
}
