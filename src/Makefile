HOST_SYSTEM = $(shell uname | cut -f 1 -d_)
SYSTEM ?= $(HOST_SYSTEM)
CXX = g++
CPPFLAGS += `pkg-config --cflags protobuf grpc`
CXXFLAGS += -std=c++11
ifeq ($(SYSTEM),Darwin)
	LDFLAGS += -L/usr/local/lib `pkg-config --libs protobuf grpc++`\
			   -L/usr/lib64/mysql -lmysqlclient\
			   -I/usr/include/mysql\
			   -pthread\
			   -lgrpc++_reflection\
			   -ldl
	else
	LDFLAGS += -L/usr/local/lib `pkg-config --libs protobuf grpc++`\
			   -L/usr/lib64/mysql  -lmysqlclient\
			   -I/usr/include/mysql\
			   -pthread\
			   -Wl,--no-as-needed -lgrpc++_reflection -Wl,--as-needed\
			   -ldl
	endif
	PROTOC = protoc
	GRPC_CPP_PLUGIN = grpc_cpp_plugin
	GRPC_CPP_PLUGIN_PATH ?= `which $(GRPC_CPP_PLUGIN)`

PROTOS_PATH = ../../protos

vpath %.proto $(PROTOS_PATH)

all: cpp_conn_mysql

cpp_conn_mysql: cpp_conn_mysql.cc 
	$(CXX) $^ $(LDFLAGS) -o $@
