# Xanadu.Core

*A cross-platform C++ extension library*


## Explain

This is a collection of C++ extension classes, which can make some C++ calls more convenient.


### Function
    XString             : A string processing class of UTF-8.
    XByteArray          : Byte array processing
    XBase64             : Base64 codec
    XCoreApplication    : Some basic application operations
    XLibrary            : Dynamic library loading
    XMutex              : Mutex
    XShell              : Shell operation, xanadu to call the command line and return output
    XLog                : Multiple levels of log output
    XVariant            : Variant
    XHash               : Provide calculation of MD5 / CRC32 / SHA1
    XException          : Exception handling
    more...


## Note

If you want to commit any changes, write the code in the following format.

set encoding=utf-8

set tabstop=8

set shiftwidth=8



## Comment format

```shell
/// <summary>
/// The description of the current function
/// </summary>
/// <param name="_ParameterName"> Parameter description </param>
/// <returns> Return value description</returns>
/// <examples> Examples </examples>
```


## Installation

### Ubuntu Linux

First install all required dependencies and build tools:
```shell
sudo apt install git
sudo apt install autoconf
sudo apt install automake
sudo apt install libtool-bin
sudo apt install cmake
```

Then clone the actual project Repository:
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

README Updated on: 2021-09-09
