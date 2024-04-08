# Rpc
#  1.环境配置
## 1.1 环境搭建
开发环境：Linux(Ubuntu 22.04.03 LTS),gcc version 11.4.0  
开发工具：VsCode,VMware Workstation Pro,MobaXterm,通过ssh远程连接linux机器
## 1.2 依赖库安装
### 1.2.1 protobuf
安装过程：  
'''  
//借鉴：https://zhuanlan.zhihu.com/p/631291781  
https://github.com/protocolbuffers/protobuf/releases/tag/v21.11  
tar -xzvf protobuf-3.21.11.tar.gz  
'''  
指定安装目录  
'''  
./configure --prefix=/usr/local/protobuf  
sudo apt install make //报错找不到libtool路径  
sudo apt install libtool-bin  
//重新执行配置  
./configure --prefix=/usr/local/protobuf  
make -j4  
sudo make install  
'''  
在系统配置文件中添加以下内容
'''  
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
'''  
