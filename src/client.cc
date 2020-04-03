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

#include <cstdlib>
#include "client/UserSystemClient.h"
#include <chrono>

#include <grpcpp/grpcpp.h>

// #ifdef BAZEL_BUILD
// #include "examples/protos/user.grpc.pb.h"
// #else
// #include "src/protos/user.grpc.pb.h"
#include "src/protos/usersystem.grpc.pb.h"
// #endif

const char* CERT_PEM = R"cert(
-----BEGIN CERTIFICATE-----
MIICmDCCAh6gAwIBAgIJAMLiaeoJDFRqMAoGCCqGSM49BAMCMIGJMQswCQYDVQQG
EwJ6aDESMBAGA1UECAwJZ3Vhbmdkb25nMRIwEAYDVQQHDAlndWFuZ3pob3UxEDAO
BgNVBAoMB2dlcmFudGUxDTALBgNVBAsMBGtlamkxEDAOBgNVBAMMB2dlcmFudGUx
HzAdBgkqhkiG9w0BCQEWEDU3NzE3NDA0MkBxcS5jb20wHhcNMjAwMzI0MDQyMzE0
WhcNMzAwMzIyMDQyMzE0WjCBiTELMAkGA1UEBhMCemgxEjAQBgNVBAgMCWd1YW5n
ZG9uZzESMBAGA1UEBwwJZ3Vhbmd6aG91MRAwDgYDVQQKDAdnZXJhbnRlMQ0wCwYD
VQQLDARrZWppMRAwDgYDVQQDDAdnZXJhbnRlMR8wHQYJKoZIhvcNAQkBFhA1Nzcx
NzQwNDJAcXEuY29tMHYwEAYHKoZIzj0CAQYFK4EEACIDYgAEHWdDWkaCGeT+auNx
+X9QkRqrM0KZZlKQTaG2lAydMWUDO3YsqldR8nWnXGrXR/zfGPOPSNWVCyw8vyRN
hJst88yjARKN6K/Cc0llkCwRLBgEYlxZyl3bcP37Yio8/q7co1AwTjAdBgNVHQ4E
FgQUo7XbKkQCGk2nUIAUI2PYp4NFLDkwHwYDVR0jBBgwFoAUo7XbKkQCGk2nUIAU
I2PYp4NFLDkwDAYDVR0TBAUwAwEB/zAKBggqhkjOPQQDAgNoADBlAjEAqNesAS3A
FZodsZddaeolwAc7pjeUaXN8RvjZ5W4iqzQ+RyxqLEBME0DUxUnKXO9lAjAlEcoP
SecfH3e1D+VnlZnngRz/mjgo38VeNUf9OhWL0jwnmoma5mdWxMgk7vhi7pc=
-----END CERTIFICATE-----
)cert";

static std::string GenerateTimestampDeviceID()
{
    return std::to_string(std::chrono::system_clock().now().time_since_epoch().count());
}

// using grpc::Channel;
// using grpc::ClientContext;
// using grpc::Status;
// using user::UserLoginRequest;
// using user::UserLoginReply;
// using user::UserRegisterRequest;
// using user::UserRegisterReply;
// using user::User;



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

    UserSystemClient user_client(grpc::CreateChannel(
      "106.14.56.249:3389", grpc::InsecureChannelCredentials()));

     std::string device_id = GenerateTimestampDeviceID();

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

      auto loginResponse = user_client.Login("john", "123456", device_id, usersystem::Platform::Type_Desktop);
      if (loginResponse.response().code() == usersystem::ResponseCode::OK) {
          std::cout << "登录成功！ " << loginResponse.usermodel().username() << ' '
                    << loginResponse.token() << std::endl;
      } else {
          if (loginResponse.response().code() == usersystem::ResponseCode::ERROR_LOGIN_WRONG_USERNAME) {
              std::cerr << "用户名错误！" << std::endl;
          } else if (loginResponse.response().code() == usersystem::ResponseCode::ERROR_LOGIN_WRONG_PASSWORD) {
              std::cerr << "密码错误！" << std::endl;
          }
      }
      // std::string reply = user.Login(username, password);
      // std::cout << "服务器返回信息: " << reply << std::endl;

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
      // std::cout << "请输入身份证号"<<std::endl;
      // std::cin >> cardnum;
      // std::cout << "请输入昵称"<<std::endl;
      // std::cin >> name;
      std::cout<< "已输入账号密码为："<<username << password<<std::endl;
      auto response = user_client.Register(username, password, device_id, usersystem::Platform::Type_Desktop);
      if (response.response().code() == usersystem::ResponseCode::ERROR_REGISTER_USERNAME_HAS_BEEN_TAKEN) {
          std::cerr << "已存在用户！" <<  response.response().code() << std::endl;
      } else {
          std::cout << "注册成功！" << response.usermodel().username() << ' '
                    << response.usermodel().id() << std::endl;
      }

    } else {
      //输入错误！
      std::cout<< "输入错误！"<<std::endl;
      return 1;
    }


  return 0;
}
