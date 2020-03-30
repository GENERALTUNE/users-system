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
#include "mysql/mysql.h"

// #ifdef BAZEL_BUILD
// #include "examples/protos/user.grpc.pb.h"
// #else
#include "src/protos/user.grpc.pb.h"
// #endif

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using user::UserLoginRequest;
using user::UserLoginReply;
using user::UserRegisterRequest;
using user::UserRegisterReply;
using user::User;


MYSQL mysql;
MYSQL_FIELD *fd;  //字段列数组
char field[32][32];  //存字段名二维数组
MYSQL_RES *res; //这个结构代表返回行的一个查询结果集
MYSQL_ROW column; //一个行数据的类型安全(type-safe)的表示，表示数据行的列
char query[150]; //查询语句


bool InsertData();		//增
bool ModifyData();		//改
bool DeleteData();		//删
bool QueryData();		//查



void banner(){
	std::cout<<"Welcome to 注册登录系统\n";
	std::cout<<" _______  _____  _     _ _______  ______ _______ __   _ _______ _______\n";
	std::cout<<" |       |     | |_____| |______ |_____/ |______ | \\  | |       |______\n";
	std::cout<<" |_____  |_____| |     | |______ |    \\_ |______ |  \\_| |_____  |______\n";
	std::cout<<"\n";
	std::cout<<"\"Privacy is the power to selectively reveal oneself to the world.\" \n";
	std::cout<<"gerante\n";
	std::cout<<"\n";
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

   public:
  ~UserServiceImpl() {
  	// 销毁工作
   // this->Shutdown(); 
    // 数据库连接
    mysql_close( &mysql ); /* 关闭连接 */

  }
  Status Login(ServerContext* context, const UserLoginRequest* request,
                  UserLoginReply* reply) override {
    std::string ret_msg;
    std::cout<< "收到客户端登录信息"<< request->username() <<request->password()<< std::endl;
    // 设定数据库查询的编码格式为utf-8
    mysql_query(&mysql, "set names utf8");
    std::string query_sql("select * from user_info  where username='" +request->username()+ "' and password='"+ request->password() +"'");

    if (mysql_query(&mysql, query_sql.c_str())) 
    {
    	std::cout<< "数据库查询失败"<<mysql_error(&mysql) << std::endl;
		ret_msg = mysql_error(&mysql);
    	reply->set_message("数据库查询失败: " + ret_msg);

    } else {

    	// 获得查询的数据
    	res = mysql_store_result(&mysql);
    	// 获取返回数据的行数
    	int data_num = mysql_affected_rows(&mysql);
		std::cout<< "数据库返回的数据条数: "<< data_num << std::endl;

		if (data_num < 1) {
			reply->set_message("无法登陆，不存在此人！");
		} else {
				// 获取返回数据的列名 存储在field中
			for (int i = 0; fd = mysql_fetch_field(res); i++)  //获取字段名  
				std::strcpy(field[i], fd->name);

			int j = mysql_num_fields(res);  // 获取列数  
			// for (int i = 0; i<j; i++)  //打印字段  
				// printf("%10s\t", field[i]);
			// printf("\n");

			while (column = mysql_fetch_row(res))
			{
				for (int i = 0; i<j; i++)
				{
					std::string field_tmp = field[i];
					if (field_tmp == "id_card_num") {
						ret_msg = column[i];
						reply->set_message("登录成功！身份证号码为: " + ret_msg);
					}
				}
				// 	printf("%10s\t", column[i]);
				// printf("\n");
			}
		}
		
    }

    return Status::OK;
  }
  Status Register(ServerContext* context, const UserRegisterRequest* request,
                  UserRegisterReply* reply) override {

	std::string ret_msg;

    std::cout<< "收到客户端注册信息"<< request->username() <<request->password()<<request->cardnum()<<request->name()<< std::endl;
//	//可以想办法实现手动在控制台手动输入指令  
	std::string  insert_sql = "insert into user_info (username, password, name, id_card_num, state)values ( '" + request->username() + "', '" + 
		request->password() + "','" + request->name() + "','" + request->cardnum() + "','1');";
    std::cout<< insert_sql << std::endl;
	mysql_query(&mysql, "set names utf8");
	if (mysql_query(&mysql, insert_sql.c_str()))        //执行SQL语句  
	{
		ret_msg = mysql_error(&mysql);
		reply->set_message("注册失败: " + ret_msg);
	}
	else
	{
		reply->set_message("注册成功！: " + ret_msg);
	}

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



	std::string server_address("0.0.0.0:3389");
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

	//启动数据库的连接
	mysql_init(&mysql);
	//mysql_options(&mysql,MYSQL_PORT, "33060");
	if (mysql_real_connect(&mysql,"106.14.56.249","root","MyNewPass@123","gerante", 33060,NULL,0))
	{  
		//printf("连接成功!\n");
		std::cout<<"连接成功！"<<std::endl;
	}
	else
	{
		// fprintf(stderr, "Failed to connect to database: Error: %s\n", mysql_error(&mysql));
		std::cout<<stderr<<"Failed to connect to database: Error: "<< mysql_error(&mysql)<< std::endl;
	}


	std::cout << "Server listening on " << server_address << std::endl;

	// Wait for the server to shutdown. Note that some other thread must be
	// responsible for shutting down the server for this call to ever return.
	server->Wait();
}

int main(int argc, char** argv) {
  RunServer();
  return 0;
}







//插入数据  
bool InsertData()
{
	std::string  username;
	std::string  name;
	std::string  id_card_num;
	std::string  password;
	std::cout<<"请输入账号名称"<<std::endl;
	std::cin>> username;  
	std::cout<<"请输入昵称"<< std::endl;
	std::cin>>name;
	std::cout<<"请输入身份证号码"<< std::endl;
	std::cin>>id_card_num;
	std::cout<< "请输入密码"<<std::endl;
	std::cin>>password;

	//	//可以想办法实现手动在控制台手动输入指令  
	std::string  insert_sql = "insert into user_info (username, password, name, id_card_num, state)values ( '" + username + "', '" + 
		password + "','" + name + "','" + id_card_num + "','1');";
    std::cout<< insert_sql << std::endl;
	mysql_query(&mysql, "set names utf8");
	if (mysql_query(&mysql, insert_sql.c_str()))        //执行SQL语句  
	{
		printf("Query failed (%s)\n", mysql_error(&mysql));
		return false;
	}
	else
	{
		printf("Insert success\n");
		return true;
	}
}

//																	 //修改数据  
bool ModifyData()
{
    std::string name;
	std::string username;
	std::cout<<"请输入需要更改的账号名:"<<std::endl;
	std::cin>>username;
	std::cout<<"请输入需要更改的昵称:"<<std::endl;
	std::cin>>name;

	std::string modify_sql = "update user_info set name='" + name +"' where username='"+ username +"'";
	std::cout<< modify_sql<<std::endl;
	mysql_query(&mysql, "set names utf8");
	if (mysql_query(&mysql, modify_sql.c_str()))        //执行SQL语句  
	{
		printf("Query failed (%s)\n", mysql_error(&mysql));
		return false;
	}
	else
	{
		printf("修改成功！ success\n");
		return true;
	}
}
//删除数据  
bool DeleteData()
{
	/*sprintf(query, "delete from user where id=6");*/
	std::string delete_sql = "";
	std::cout<<"please input the sql:"<<std::endl;
	std::cin>> delete_sql ;  //这里手动输入sql语句  
	if (mysql_query(&mysql, delete_sql.c_str()))        //执行SQL语句  
	{
		printf("Query failed (%s)\n", mysql_error(&mysql));
		return false;
	}
	else
	{
		std::cout<<"Insert success"<<std::endl;
		return true;
	}
}
