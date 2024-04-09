# Rpc
#  1.环境配置
## 1.1 环境搭建
开发环境：Linux(Ubuntu 22.04.03 LTS),gcc version 11.4.0  
开发工具：VsCode,VMware Workstation Pro,MobaXterm,通过ssh远程连接linux机器
## 1.2 依赖库安装
### 1.2.1 protobuf
安装过程：  
```
//借鉴：https://zhuanlan.zhihu.com/p/631291781  
https://github.com/protocolbuffers/protobuf/releases/tag/v21.11  
tar -xzvf protobuf-3.21.11.tar.gz  
```
指定安装目录  
```
./configure --prefix=/usr/local/protobuf  
sudo apt install make //报错找不到libtool路径  
sudo apt install libtool-bin  
//重新执行配置  
./configure --prefix=/usr/local/protobuf  
make -j4  
sudo make install  
```
在系统配置文件中添加以下内容  
```
sudo vim /etc/profile  

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/protobuf/lib/  
#(静态库搜索路径) 程序编译期间查找动态链接库时指定查找共享库的路径  
export LIBRARY_PATH=$LIBRARY_PATH:/usr/local/protobuf/lib/  
#执⾏程序搜索路径  
export PATH=$PATH:/usr/local/protobuf/bin/  
#c程序头⽂件搜索路径  
export C_INCLUDE_PATH=$C_INCLUDE_PATH:/usr/local/protobuf/include/  
#c++程序头⽂件搜索路径  
export CPLUS_INCLUDE_PATH=$CPLUS_INCLUDE_PATH:/usr/local/protobuf/include/  
#pkg-config 路径  
export PKG_CONFIG_PATH=/usr/local/protobuf/lib/pkgconfig/  

source /etc/profile/ 
```
 ### 1.2.2 tinxml
 项目采用到配置模块，使用xml作为配置文件，使用tinyxml解析xml文件
 安装过程：
 ```
 https://sourceforge.net/projects/tinyxml/files/latest/download
 unzip tinyxml_2_6_2.zip
 //修改OUPUT xmltest为libtinyxml.a
 make -j4
 //将头文件和库文件移动到对应位置
 cd /usr/local/
 sudo mkdir tinyxml
 cd tinyxml
 sudo mkdir include
 sudo mkdir lib
 ...
 sudo cp *h /usr/local/tinyxml/include
 sudo cp libtinyxml.a /usr/local/tinyxml/lib
 ```
# 2.模块开发
## 2.1 日志模块
1.日志级别
2.打印大文件，以日期命名滚动
3.以c风格
4.支持线程安全

LogLevel:
```
Debug
Info
Error
```

LogEvent:
```
文件名、行号
Msg
Tread id
proc id
日期及时间精确到毫秒
自定义消息
```

