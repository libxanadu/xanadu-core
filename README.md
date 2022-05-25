# xanadu-core
*C++ Support Library for X-Series Core*



## Explain
This project is for C++ support for the X-Series, providing more calls than the standard library.



### Function
~~~
bytearray	: Byte array handling
endian		: Judgment and conversion of big and small endian byte order
library		: Encapsulation class for dynamic library related operations
mutex		: Mutex is a pure C-based C++ package
process		: Process traversal and operation collection
string		: String handling
ternary		: Action class with three states (true/false/null)
thread		: Thread ID and sleep
uuid		: Create UUID and convert to and from strings
~~~



## Note
If you want to commit any changes, write the code in the following format.

set encoding=utf-8 with BOM

set tabstop=8

set shiftwidth=8



## Note
If you want to commit any changes, write the code in the following format.

set encoding=utf-8 with BOM

set tabstop=8

set shiftwidth=8




## Comment format

```shell
/// Function description
/// \param _Value : Parameter explanation
/// \return : Return value description
```



## Installation

### Linux

First install all required dependencies and build tools:
```shell
sudo apt install git
sudo apt install autoconf
sudo apt install automake
sudo apt install libtool-bin
sudo apt install cmake
```

Resolve all dependencies:

[xanadu-posix](https://github.com/libxanadu/xanadu-posix)

Then clone the actual project repository:
```shell
git clone https://github.com/libxanadu/xanadu-core.git
svn checkout https://github.com/libxanadu/xanadu-core/trunk
cd xanadu-core
```

Now you can build and install it:
```shell
cmake .
make
sudo make install
```



## License

This library is licensed under the [GNU Lesser General Public License v2.1](https://www.gnu.org/licenses/lgpl-2.1.en.html),
also included in the repository in the `LICENSE` file.
