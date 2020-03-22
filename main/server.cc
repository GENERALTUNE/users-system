#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>


using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;


int main(int argc, char** argv) {

	printf("%s\n", "你好！");
	return 0;
}