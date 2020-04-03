# 说明文档

## cgi
http://www.gnu.org/software/cgicc/doc/index.html

### 编译数据库连接语句
 g++    cpp_conn_mysql.cc -L /usr/include/mysql   -L /usr/lib64/mysql -lmysqlclient

##  bazel

### 查看依赖图
bazel query --nohost_deps --noimplicit_deps 'deps(//main:hello-world)' --output graph

## Centos7.3编译安装grpc

###  安装工具
```shell
yum install -y gcc gcc-c++ autoconf libtool
yum groupinstall -y "Development Tools"

```
### 下载源码
```shell
git clone https://github.com/grpc/grpc.git
cd grpc
git submodule update --init
```

### 编译安装protobuf
```shell
cd third_party/protobuf/
./autogen.sh
./configure
make
make install
ldconfig # refresh shared library cache.
which protoc
protoc --version
```
## 编译安装 grpc
```shell
make  
make install
```


## 测试C++ Demo
```shell
cd examples/cpp/helloworld
make
```

### 启动服务器端和客户端
```shell
#启动服务器
./greeter_server 
# 启动客户端
./greeter_client

```
报错  ./greeter_client: error while loading shared libraries: libprotobuf.so.22: cannot open shared object file: No such file or directory
### 解决
```shell
export LD_LIBRARY_PATH=/usr/local/lib

echo $LD_LIBRARY_PATH
export LD_LIBRARY_PATH=/usr/local/lib/:/root/git/grpc/libs/opt/
export LD_LIBRARY_PATH=/usr/local/lib/:/root/grpc/libs/opt/
```

### 报错解决
echo $PKG_CONFIG_PATH
export PKG_CONFIG_PATH=/root/git/grpc/libs/opt/pkgconfig:/root/git/grpc/third_party/protobuf
export PKG_CONFIG_PATH=/root/grpc/libs/opt/pkgconfig:/root/grpc/third_party/protobuf


相关命令简介:
    make uninstall : 卸载命令
    make clean : 清除编译产生的可执行文件及目标文件 (object file，*.o)。
    make distclean : 除了清除可执行文件和目标文件外，把 configure 所产生的 Makefile 也清除掉。
    ldconfig : 更新共享库缓存
    ldconfig -p|grep proto : 查看protobuf库相关的库
    which protoc : 查看软件的安装位置
    protoc --version : 检查是否安装成功
配置环境变量
```shell
vim ~/.bash_profile
    PATH=$PATH:$HOME/bin:/root/grpc/bins/opt
    export PATH
    export LD_LIBRARY_PATH=/usr/local/lib/:/root/grpc/libs/opt
    export PKG_CONFIG_PATH=$PKG_CONFIG_PATH:/usr/local/lib/pkgconfig
source ~/.bash_profile
ldconfig
```


## ubuntu 16.04 
 wget  https://cdn.mysql.com//Downloads/Connector-C++/libmysqlcppconn-dev_8.0.19-1ubuntu16.04_amd64.deb
 sudo dpkg -i libmysqlcppconn-dev_8.0.19-1ubuntu16.04_amd64.deb
 
 sudo dpkg -i mysql-apt-config_0.8.10-1_all.deb
下载
  wget https://repo.mysql.com//mysql-apt-config_0.8.10-1_all.deb 
<!-- dpkg -i -->
<!-- rpm -ivh your-package -->



## 参考
c++ 持久化解决方案
https://blog.csdn.net/dean_zhang5757/article/details/104845096
https://www.codesynthesis.com/products/odb/doc/manual.xhtml
windows下安装grpc
https://blog.csdn.net/liyangbinbin/article/details/100134465
### travis 
https://www.cnblogs.com/morang/p/7228488.html
### travis & bazel
https://www.geek-share.com/detail/2758685060.html
### bazel c++
https://blog.csdn.net/elaine_bao/article/details/78668657
### c++ 连接mysql
https://blog.csdn.net/yuhan61659/article/details/82706072


## 制作签名证书
```shell
openssl ecparam -genkey -name secp384r1 -out server.key

openssl req -new -x509 -sha256 -key server.key -out server.pem -days 3650
```

## grpc 支持 ssl/ts
https://blog.csdn.net/m0_46083365/article/details/103744750?utm_source=blogxgwz7