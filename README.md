# xanadu-core
*Xanadu系列的核心C++支持库*



## 说明
此工程用于支持libxanadu项目的一些基础操作。



### 功能
~~~
endian		: 大小端判断与值转换
library		: 动态库相关操作的封装类
mutex		: 纯C的Mutex封装
process		: 进程的遍历与操作集合
string		: 字符串处理
ternary		: 三种状态的操作类 (true/false/null)
thread		: 线程的ID与休眠
uuid		: 创建UUID并且和字符串互相转换
~~~



## 注意
如果要提交拉取请求，请按以下格式编写代码。

set encoding=utf-8 with BOM

set tabstop=8

set shiftwidth=8



## 安装

### Linux

首先安装所有必需的依赖项和构建工具:
```shell
sudo apt install git
sudo apt install autoconf
sudo apt install automake
sudo apt install libtool-bin
sudo apt install cmake
```

解决所有依赖项:

*[libxanadu/xanadu-posix](https://github.com/libxanadu/xanadu-posix)*


然后克隆实际的项目存储库:
```shell
git clone https://github.com/libxanadu/xanadu-core.git
svn checkout https://github.com/libxanadu/xanadu-core/trunk
cd xanadu-core
```

现在您可以构建和安装它:
```shell
cmake .
make
sudo make install
```



## License

这个库是根据 [GNU Lesser General Public License v2.1](https://www.gnu.org/licenses/lgpl-2.1.en.html) 获得的许可，
存储库中也包含“许可证”文件。
