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
#include "examples/protos/User.grpc.pb.h"
#else
#include "User.grpc.pb.h"
#endif

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using User::UserLoginRequest;
using User::UserLoginReply;
using User::UserRegisterRequest;
using User::UserRegisterReply;
using User::User;


void banner(){
  cout<<"Welcome to 注册登录系统\n";
  cout<<" _______  _____  _     _ _______  ______ _______ __   _ _______ _______\n";
  cout<<" |       |     | |_____| |______ |_____/ |______ | \\  | |       |______\n";
  cout<<" |_____  |_____| |     | |______ |    \\_ |______ |  \\_| |_____  |______\n";
  cout<<"\n";
  cout<<"\"Privacy is the power to selectively reveal oneself to the world.\" \n";
  cout<<"gerante\n";
  cout<<"\n";
}

void read_fs ( const std::string& filename, std::string& data ){
  std::ifstream file ( filename.c_str (), std::ios::in );
	if ( file.is_open () ){
		std::stringstream ss;
		ss << file.rdbuf ();
		file.close ();
		data = ss.str ();
	}
	return;
}



// Logic and data behind the server's behavior.
class UserServiceImpl final : public User::Service {
  Status Login(ServerContext* context, const UserLoginRequest* request,
                  UserLoginReply* reply) override {
    std::string prefix("Hello ");
    std::cout<< "收到客户端登录信息"<< request->username() <<request.password()<< std::endl;

    reply->set_message(prefix + request->username());

    return Status::OK;
  }
  Status Register(ServerContext* context, const UserRegisterRequest* request,
                  UserRegisterReply* reply) override {

    std::string prefix("Hello ");
     std::cout<< "收到客户端注册信息"<< request->username() <<request.password()<< std::endl;
    reply->set_message(prefix + request->username());
    return Status::OK;
  }
};

void RunServer() {

	// std::string key;
	// std::string cert;
	// std::string root;

	// read_fs ( "server.crt", cert );
	// read_fs ( "server.key", key );
	// read_fs ( "ca.crt", root );


 //    grpc::SslServerCredentialsOptions::PemKeyCertPair keycert ={key,cert};
 //    grpc::SslServerCredentialsOptions sslOps;
 //    sslOps.pem_root_certs = root;
 //    sslOps.pem_key_cert_pairs.push_back ( keycert );

    // std::string server_address(addr.c_str());

    // ServerBuilder builder;
    // builder.AddListeningPort(server_address, grpc::SslServerCredentials( sslOps ));
    // builder.RegisterService(&service_);
    // cq_ = builder.AddCompletionQueue();
    // server_ = builder.BuildAndStart();



	std::string server_address("0.0.0.0:50051");
	UserServiceImpl service;

	ServerBuilder builder;
	// Listen on the given address without any authentication mechanism.
	// builder.AddListeningPort(server_address, grpc::SslServerCredentials( sslOps ));
	builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
	// Register "service" as the instance through which we'll communicate with
	// clients. In this case it corresponds to an *synchronous* service.
	builder.RegisterService(&service);
	// Finally assemble the server.
	std::unique_ptr<Server> server(builder.BuildAndStart());
	std::cout << "Server listening on " << server_address << std::endl;

	// Wait for the server to shutdown. Note that some other thread must be
	// responsible for shutting down the server for this call to ever return.
	server->Wait();
}

int main(int argc, char** argv) {
  RunServer();

  return 0;
}
