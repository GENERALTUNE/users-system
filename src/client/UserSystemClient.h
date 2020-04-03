
#ifndef USERSYSTEM_USERSYSTEMCLIENT_H
#define USERSYSTEM_USERSYSTEMCLIENT_H

#include <iostream>
#include <memory>
#include <string>
// #include <grpc++/grpc++.h>
#include <grpcpp/grpcpp.h>
// #include "usersystem.pb.h"
// #include "usersystem.grpc.pb.h"
#include "src/protos/usersystem.grpc.pb.h"

class UserSystemClient {

public:
    explicit UserSystemClient(std::shared_ptr<grpc::Channel> channel) :
            _stub(usersystem::UserSystem::NewStub(channel)) {
    }

    usersystem::RegisterResponse Register(const std::string& username, const std::string& password, const std::string& device_id, usersystem::Platform platform);
    usersystem::LoginResponse Login(const std::string& username, const std::string& password, const std::string& device_id, usersystem::Platform platform);
    usersystem::CheckLoginResponse CheckLogin(const std::string& username, const std::string& token, const std::string& device_id, usersystem::Platform platform);
    usersystem::CommonResponse Logout(const std::string& username, const std::string& token);

private:
    std::unique_ptr<usersystem::UserSystem::Stub> _stub;
};


#endif //USERSYSTEM_USERSYSTEMCLIENT_H
