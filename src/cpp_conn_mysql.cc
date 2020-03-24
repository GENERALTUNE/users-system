#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <string>
#include "mysql/mysql.h"

bool InsertData();		//增
bool ModifyData();		//改
bool DeleteData();		//删
bool QueryData();		//查

MYSQL mysql;
MYSQL_FIELD *fd;  //字段列数组
char field[32][32];  //存字段名二维数组
MYSQL_RES *res; //这个结构代表返回行的一个查询结果集
MYSQL_ROW column; //一个行数据的类型安全(type-safe)的表示，表示数据行的列
char query[150]; //查询语句


int main( int argc, char *argv[] )
{

	mysql_init(&mysql);
	//mysql_options(&mysql,MYSQL_PORT, "33060");
	if (mysql_real_connect(&mysql,"106.14.56.249","root","MyNewPass@123","gerante", 33060,NULL,0))
	{  
		//printf("连接成功!\n");
		std::cout<<"连接成功！"<<std::endl;
	}
	else
	{
		fprintf(stderr, "Failed to connect to database: Error: %s\n",
				mysql_error(&mysql));
	}

	InsertData();
	QueryData();
	ModifyData();
	QueryData();

	mysql_free_result(res);  //释放一个结果集合使用的内存。
	mysql_close( &mysql ); /* 关闭连接 */
	return (EXIT_SUCCESS);
}

bool QueryData() {

	mysql_query(&mysql, "set names utf8");

	//返回0 查询成功，返回1查询失败  
	if (mysql_query(&mysql, "select * from user_info"))        //执行SQL语句  
	{
		printf("Query failed (%s)\n", mysql_error(&mysql));
		return false;
	}
	else
	{
		printf("query success\n");
	}
	res = mysql_store_result(&mysql);
	//														//打印数据行数  
	printf("number of dataline returned: %d\n", mysql_affected_rows(&mysql));
	for (int i = 0; fd = mysql_fetch_field(res); i++)  //获取字段名  
		std::strcpy(field[i], fd->name);
	int j = mysql_num_fields(res);  // 获取列数  
	for (int i = 0; i<j; i++)  //打印字段  
		printf("%10s\t", field[i]);
	printf("\n");
	while (column = mysql_fetch_row(res))
	{
		for (int i = 0; i<j; i++)
			printf("%10s\t", column[i]);
		printf("\n");
	}

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

