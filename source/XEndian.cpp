#include <xanadu-core/XEndian.h>



// constructor
XEndian::XEndian() noexcept = default;

// constructor
XEndian::XEndian(const XEndian& _Other) noexcept = default;

// constructor
XEndian::XEndian(XEndian&& _Other) noexcept = default;

// destructor
XEndian::~XEndian() noexcept = default;





// operator overload =
XEndian& XEndian::operator = (const XEndian& _Endian) noexcept = default;

// operator overload =
XEndian& XEndian::operator = (XEndian&& _Endian) noexcept = default;





// 检查操作系统是否为大端字节序
bool XEndian::is_big() noexcept
{
	return XEndian::native == XEndian::big;
}

// 检查操作系统是否为小端字节序
bool XEndian::is_little() noexcept
{
	return XEndian::native == XEndian::little;
}

// 检查操作系统是否为PDP字节序
bool XEndian::is_pdp() noexcept
{
	return XEndian::native == XEndian::pdp;
}





// reverse : memory
void XEndian::reverse(void* _Memory, std::size_t _Size) noexcept
{
	if(_Memory != nullptr && _Size > 0)
	{
		auto		vBuffer = (char*)_Memory;
		char		vTemp = 0;
		for(std::size_t vIndex = 0; vIndex < _Size / 2; ++vIndex)
		{
			vTemp = vBuffer[vIndex];
			vBuffer[vIndex] = vBuffer[_Size - vIndex - 1];
			vBuffer[_Size - vIndex - 1] = vTemp;
		}
	}
}





// reverse : short
short XEndian::reverse(short _Number) noexcept
{
	return (short)XEndian::reverse((unsigned short)_Number);
}

// reverse : unsigned short
unsigned short XEndian::reverse(unsigned short _Number) noexcept
{
	return (((_Number & 0x00FF) << 8) | ((_Number & 0xFF00) >> 8));
}

// reverse : int
int XEndian::reverse(int _Number) noexcept
{
	return (int)XEndian::reverse((unsigned int)_Number);
}

// reverse : unsigned int
unsigned int XEndian::reverse(unsigned int _Number) noexcept
{
	return (((_Number & 0xFF000000) >> 24) | ((_Number & 0x00FF0000) >> 8) | ((_Number & 0x0000FF00) << 8) | ((_Number & 0x000000FF) << 24));
}

// reverse : long
long XEndian::reverse(long _Number) noexcept
{
	return (long)XEndian::reverse((unsigned long)_Number);
}

// reverse : unsigned long
unsigned long XEndian::reverse(unsigned long _Number) noexcept
{
	if constexpr (sizeof(unsigned long) == 4)
	{
		return (unsigned long)XEndian::reverse((unsigned int)_Number);
	}
	else
	{
		return (unsigned long)XEndian::reverse((unsigned long long)_Number);
	}
}

// reverse : long long
long long XEndian::reverse(long long _Number) noexcept
{
	return (long long)XEndian::reverse((unsigned long long)_Number);
}

// reverse : unsigned short
unsigned long long XEndian::reverse(unsigned long long _Number) noexcept
{
	return (((_Number & 0x00000000000000FFULL) << 56) | ((_Number & 0x000000000000FF00ULL) << 40) |
		((_Number & 0x0000000000FF0000ULL) << 24) | ((_Number & 0x00000000FF000000ULL) << 8) |
		((_Number & 0x000000FF00000000ULL) >> 8) | ((_Number & 0x0000FF0000000000ULL) >> 24) |
		((_Number & 0x00FF000000000000ULL) >> 40) | ((_Number & 0xFF00000000000000ULL) >> 56));
}





// Conversion from native byte order to network byte order : short
short XEndian::host_to_network(short _Number) noexcept
{
	return (short)XEndian::host_to_network((unsigned short)_Number);
}

// Conversion from native byte order to network byte order : unsigned short
unsigned short XEndian::host_to_network(unsigned short _Number) noexcept
{
	if(XEndian::is_little())
	{
		return XEndian::reverse(_Number);
	}
	return _Number;
}

// Conversion from native byte order to network byte order : int
int XEndian::host_to_network(int _Number) noexcept
{
	return (int)XEndian::host_to_network((unsigned int)_Number);
}

// Conversion from native byte order to network byte order : unsigned int
unsigned int XEndian::host_to_network(unsigned int _Number) noexcept
{
	if(XEndian::is_little())
	{
		return XEndian::reverse(_Number);
	}
	return _Number;
}

// Conversion from native byte order to network byte order : long
long XEndian::host_to_network(long _Number) noexcept
{
	return (long)XEndian::host_to_network((unsigned long)_Number);
}

// Conversion from native byte order to network byte order : unsigned long
unsigned long XEndian::host_to_network(unsigned long _Number) noexcept
{
	if constexpr (sizeof(unsigned long) == 4)
	{
		return (unsigned long)XEndian::host_to_network((unsigned int)_Number);
	}
	else
	{
		return (unsigned long)XEndian::host_to_network((unsigned long long)_Number);
	}
}

// Conversion from native byte order to network byte order : long long
long long XEndian::host_to_network(long long _Number) noexcept
{
	return (long long)XEndian::host_to_network((unsigned long long)_Number);
}

// Conversion from native byte order to network byte order : unsigned short
unsigned long long XEndian::host_to_network(unsigned long long _Number) noexcept
{
	if(XEndian::is_little())
	{
		return XEndian::reverse(_Number);
	}
	return _Number;
}





// Conversion from network byte order to native byte order : short
short XEndian::network_to_host(short _Number) noexcept
{
	return (short)XEndian::network_to_host((unsigned short)_Number);
}

// Conversion from network byte order to native byte order : unsigned short
unsigned short XEndian::network_to_host(unsigned short _Number) noexcept
{
	if(XEndian::is_little())
	{
		return XEndian::reverse(_Number);
	}
	return _Number;
}

// Conversion from network byte order to native byte order : int
int XEndian::network_to_host(int _Number) noexcept
{
	return (int)XEndian::network_to_host((unsigned int)_Number);
}

// Conversion from network byte order to native byte order : unsigned int
unsigned int XEndian::network_to_host(unsigned int _Number) noexcept
{
	if(XEndian::is_little())
	{
		return XEndian::reverse(_Number);
	}
	return _Number;
}

// Conversion from network byte order to native byte order : long
long XEndian::network_to_host(long _Number) noexcept
{
	return (long)XEndian::network_to_host((unsigned long)_Number);
}

// Conversion from network byte order to native byte order : unsigned long
unsigned long XEndian::network_to_host(unsigned long _Number) noexcept
{
	if constexpr (sizeof(unsigned long) == 4)
	{
		return (unsigned long)XEndian::network_to_host((unsigned int)_Number);
	}
	else
	{
		return (unsigned long)XEndian::network_to_host((unsigned long long)_Number);
	}
}

// Conversion from network byte order to native byte order : long long
long long XEndian::network_to_host(long long _Number) noexcept
{
	return (long long)XEndian::network_to_host((unsigned long long)_Number);
}

// Conversion from network byte order to native byte order : unsigned short
unsigned long long XEndian::network_to_host(unsigned long long _Number) noexcept
{
	if(XEndian::is_little())
	{
		return XEndian::reverse(_Number);
	}
	return _Number;
}





// Conversion from native byte order to big-endian order : short
short XEndian::host_to_big(short _Number) noexcept
{
	return XEndian::host_to_network(_Number);
}

// Conversion from native byte order to big-endian order : unsigned short
unsigned short XEndian::host_to_big(unsigned short _Number) noexcept
{
	return XEndian::host_to_network(_Number);
}

// Conversion from native byte order to big-endian order : int
int XEndian::host_to_big(int _Number) noexcept
{
	return XEndian::host_to_network(_Number);
}

// Conversion from native byte order to big-endian order : unsigned int
unsigned int XEndian::host_to_big(unsigned int _Number) noexcept
{
	return XEndian::host_to_network(_Number);
}

// Conversion from native byte order to big-endian order : long
long XEndian::host_to_big(long _Number) noexcept
{
	return XEndian::host_to_network(_Number);
}

// Conversion from native byte order to big-endian order : unsigned long
unsigned long XEndian::host_to_big(unsigned long _Number) noexcept
{
	return XEndian::host_to_network(_Number);
}

// Conversion from native byte order to big-endian order : long long
long long XEndian::host_to_big(long long _Number) noexcept
{
	return XEndian::host_to_network(_Number);
}

// Conversion from native byte order to big-endian order : unsigned short
unsigned long long XEndian::host_to_big(unsigned long long _Number) noexcept
{
	return XEndian::host_to_network(_Number);
}





// Conversion from big-endian order to native byte order : short
short XEndian::big_to_host(short _Number) noexcept
{
	return XEndian::network_to_host(_Number);
}

// Conversion from big-endian order to native byte order : unsigned short
unsigned short XEndian::big_to_host(unsigned short _Number) noexcept
{
	return XEndian::network_to_host(_Number);
}

// Conversion from big-endian order to native byte order : int
int XEndian::big_to_host(int _Number) noexcept
{
	return XEndian::network_to_host(_Number);
}

// Conversion from big-endian order to native byte order : unsigned int
unsigned int XEndian::big_to_host(unsigned int _Number) noexcept
{
	return XEndian::network_to_host(_Number);
}

// Conversion from big-endian order to native byte order : long
long XEndian::big_to_host(long _Number) noexcept
{
	return XEndian::network_to_host(_Number);
}

// Conversion from big-endian order to native byte order : unsigned long
unsigned long XEndian::big_to_host(unsigned long _Number) noexcept
{
	return XEndian::network_to_host(_Number);
}

// Conversion from big-endian order to native byte order : long long
long long XEndian::big_to_host(long long _Number) noexcept
{
	return XEndian::network_to_host(_Number);
}

// Conversion from big-endian order to native byte order : unsigned short
unsigned long long XEndian::big_to_host(unsigned long long _Number) noexcept
{
	return XEndian::network_to_host(_Number);
}




// Conversion from native byte order to little-endian order : short
short XEndian::host_to_little(short _Number) noexcept
{
	return (short)XEndian::host_to_little((unsigned short)_Number);
}

// Conversion from native byte order to little-endian order : unsigned short
unsigned short XEndian::host_to_little(unsigned short _Number) noexcept
{
	if(XEndian::is_little())
	{
		return _Number;
	}
	return XEndian::reverse(_Number);
}

// Conversion from native byte order to little-endian order : int
int XEndian::host_to_little(int _Number) noexcept
{
	return (int)XEndian::host_to_little((unsigned int)_Number);
}

// Conversion from native byte order to little-endian order : unsigned int
unsigned int XEndian::host_to_little(unsigned int _Number) noexcept
{
	if(XEndian::is_little())
	{
		return _Number;
	}
	return XEndian::reverse(_Number);
}

// Conversion from native byte order to little-endian order : long
long XEndian::host_to_little(long _Number) noexcept
{
	return (long)XEndian::host_to_little((unsigned long)_Number);
}

// Conversion from native byte order to little-endian order : unsigned long
unsigned long XEndian::host_to_little(unsigned long _Number) noexcept
{
	if constexpr (sizeof(unsigned long) == 4)
	{
		return (unsigned long)XEndian::host_to_little((unsigned int)_Number);
	}
	else
	{
		return (unsigned long)XEndian::host_to_little((unsigned long long)_Number);
	}
}

// Conversion from native byte order to little-endian order : long long
long long XEndian::host_to_little(long long _Number) noexcept
{
	return (long long)XEndian::host_to_little((unsigned long long)_Number);
}

// Conversion from native byte order to little-endian order : unsigned short
unsigned long long XEndian::host_to_little(unsigned long long _Number) noexcept
{
	if(XEndian::is_little())
	{
		return _Number;
	}
	return XEndian::reverse(_Number);
}





// Conversion from little-endian order to native byte order : short
short XEndian::little_to_host(short _Number) noexcept
{
	return (short)XEndian::little_to_host((unsigned short)_Number);
}

// Conversion from little-endian order to native byte order : unsigned short
unsigned short XEndian::little_to_host(unsigned short _Number) noexcept
{
	if(XEndian::is_little())
	{
		return _Number;
	}
	return XEndian::reverse(_Number);
}

// Conversion from little-endian order to native byte order : int
int XEndian::little_to_host(int _Number) noexcept
{
	return (int)XEndian::little_to_host((unsigned int)_Number);
}

// Conversion from little-endian order to native byte order : unsigned int
unsigned int XEndian::little_to_host(unsigned int _Number) noexcept
{
	if(XEndian::is_little())
	{
		return _Number;
	}
	return XEndian::reverse(_Number);
}

// Conversion from little-endian order to native byte order : long
long XEndian::little_to_host(long _Number) noexcept
{
	return (long)XEndian::little_to_host((unsigned long)_Number);
}

// Conversion from little-endian order to native byte order : unsigned long
unsigned long XEndian::little_to_host(unsigned long _Number) noexcept
{
	if constexpr (sizeof(unsigned long) == 4)
	{
		return (unsigned long)XEndian::little_to_host((unsigned int)_Number);
	}
	else
	{
		return (unsigned long)XEndian::little_to_host((unsigned long long)_Number);
	}
}

// Conversion from little-endian order to native byte order : long long
long long XEndian::little_to_host(long long _Number) noexcept
{
	return (long long)XEndian::little_to_host((unsigned long long)_Number);
}

// Conversion from little-endian order to native byte order : unsigned short
unsigned long long XEndian::little_to_host(unsigned long long _Number) noexcept
{
	if(XEndian::is_little())
	{
		return _Number;
	}
	return XEndian::reverse(_Number);
}
