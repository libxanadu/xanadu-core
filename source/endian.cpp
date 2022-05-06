#include <xanadu-core/endian.h>



// constructor
xanadu::endian::endian() noexcept = default;

// destructor
xanadu::endian::~endian() noexcept = default;



// operator overload =
xanadu::endian& xanadu::endian::operator = (const endian& _Endian) noexcept = default;

// operator overload =
xanadu::endian& xanadu::endian::operator = (endian&& _Endian) noexcept = default;



// 检查操作系统是否为大端字节序
bool xanadu::endian::is_big() noexcept
{
	return xanadu::endian::native == xanadu::endian::big;
}

// 检查操作系统是否为小端字节序
bool xanadu::endian::is_little() noexcept
{
	return xanadu::endian::native == xanadu::endian::little;
}

// 检查操作系统是否为PDP字节序
bool xanadu::endian::is_pdp() noexcept
{
	return xanadu::endian::native == xanadu::endian::pdp;
}



// reverse : memory
void xanadu::endian::reverse(void* _Memory, std::size_t _Size) noexcept
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
short xanadu::endian::reverse(short _Number) noexcept
{
	return (short)xanadu::endian::reverse((unsigned short)_Number);
}

// reverse : unsigned short
unsigned short xanadu::endian::reverse(unsigned short _Number) noexcept
{
	return (((_Number & 0x00FF) << 8) | ((_Number & 0xFF00) >> 8));
}

// reverse : int
int xanadu::endian::reverse(int _Number) noexcept
{
	return (int)xanadu::endian::reverse((unsigned int)_Number);
}

// reverse : unsigned int
unsigned int xanadu::endian::reverse(unsigned int _Number) noexcept
{
	return (((_Number & 0xFF000000) >> 24) | ((_Number & 0x00FF0000) >> 8) | ((_Number & 0x0000FF00) << 8) | ((_Number & 0x000000FF) << 24));
}

// reverse : long
long xanadu::endian::reverse(long _Number) noexcept
{
	return (long)xanadu::endian::reverse((unsigned long)_Number);
}

// reverse : unsigned long
unsigned long xanadu::endian::reverse(unsigned long _Number) noexcept
{
	if (sizeof(unsigned long) == 4)
	{
		return (unsigned long)xanadu::endian::reverse((unsigned int)_Number);
	}
	else
	{
		return (unsigned long)xanadu::endian::reverse((unsigned long long)_Number);
	}
}

// reverse : long long
long long xanadu::endian::reverse(long long _Number) noexcept
{
	return (long long)xanadu::endian::reverse((unsigned long long)_Number);
}

// reverse : unsigned short
unsigned long long xanadu::endian::reverse(unsigned long long _Number) noexcept
{
	return (((_Number & 0x00000000000000FFULL) << 56) | ((_Number & 0x000000000000FF00ULL) << 40) |
		((_Number & 0x0000000000FF0000ULL) << 24) | ((_Number & 0x00000000FF000000ULL) << 8) |
		((_Number & 0x000000FF00000000ULL) >> 8) | ((_Number & 0x0000FF0000000000ULL) >> 24) |
		((_Number & 0x00FF000000000000ULL) >> 40) | ((_Number & 0xFF00000000000000ULL) >> 56));
}





// Conversion from native byte order to network byte order : short
short xanadu::endian::host_to_network(short _Number) noexcept
{
	return (short)xanadu::endian::host_to_network((unsigned short)_Number);
}

// Conversion from native byte order to network byte order : unsigned short
unsigned short xanadu::endian::host_to_network(unsigned short _Number) noexcept
{
	if(xanadu::endian::is_little())
	{
		return xanadu::endian::reverse(_Number);
	}
	return _Number;
}

// Conversion from native byte order to network byte order : int
int xanadu::endian::host_to_network(int _Number) noexcept
{
	return (int)xanadu::endian::host_to_network((unsigned int)_Number);
}

// Conversion from native byte order to network byte order : unsigned int
unsigned int xanadu::endian::host_to_network(unsigned int _Number) noexcept
{
	if(xanadu::endian::is_little())
	{
		return xanadu::endian::reverse(_Number);
	}
	return _Number;
}

// Conversion from native byte order to network byte order : long
long xanadu::endian::host_to_network(long _Number) noexcept
{
	return (long)xanadu::endian::host_to_network((unsigned long)_Number);
}

// Conversion from native byte order to network byte order : unsigned long
unsigned long xanadu::endian::host_to_network(unsigned long _Number) noexcept
{
	if (sizeof(unsigned long) == 4)
	{
		return (unsigned long)xanadu::endian::host_to_network((unsigned int)_Number);
	}
	else
	{
		return (unsigned long)xanadu::endian::host_to_network((unsigned long long)_Number);
	}
}

// Conversion from native byte order to network byte order : long long
long long xanadu::endian::host_to_network(long long _Number) noexcept
{
	return (long long)xanadu::endian::host_to_network((unsigned long long)_Number);
}

// Conversion from native byte order to network byte order : unsigned short
unsigned long long xanadu::endian::host_to_network(unsigned long long _Number) noexcept
{
	if(xanadu::endian::is_little())
	{
		return xanadu::endian::reverse(_Number);
	}
	return _Number;
}





// Conversion from network byte order to native byte order : short
short xanadu::endian::network_to_host(short _Number) noexcept
{
	return (short)xanadu::endian::network_to_host((unsigned short)_Number);
}

// Conversion from network byte order to native byte order : unsigned short
unsigned short xanadu::endian::network_to_host(unsigned short _Number) noexcept
{
	if(xanadu::endian::is_little())
	{
		return xanadu::endian::reverse(_Number);
	}
	return _Number;
}

// Conversion from network byte order to native byte order : int
int xanadu::endian::network_to_host(int _Number) noexcept
{
	return (int)xanadu::endian::network_to_host((unsigned int)_Number);
}

// Conversion from network byte order to native byte order : unsigned int
unsigned int xanadu::endian::network_to_host(unsigned int _Number) noexcept
{
	if(xanadu::endian::is_little())
	{
		return xanadu::endian::reverse(_Number);
	}
	return _Number;
}

// Conversion from network byte order to native byte order : long
long xanadu::endian::network_to_host(long _Number) noexcept
{
	return (long)xanadu::endian::network_to_host((unsigned long)_Number);
}

// Conversion from network byte order to native byte order : unsigned long
unsigned long xanadu::endian::network_to_host(unsigned long _Number) noexcept
{
	if (sizeof(unsigned long) == 4)
	{
		return (unsigned long)xanadu::endian::network_to_host((unsigned int)_Number);
	}
	else
	{
		return (unsigned long)xanadu::endian::network_to_host((unsigned long long)_Number);
	}
}

// Conversion from network byte order to native byte order : long long
long long xanadu::endian::network_to_host(long long _Number) noexcept
{
	return (long long)xanadu::endian::network_to_host((unsigned long long)_Number);
}

// Conversion from network byte order to native byte order : unsigned short
unsigned long long xanadu::endian::network_to_host(unsigned long long _Number) noexcept
{
	if(xanadu::endian::is_little())
	{
		return xanadu::endian::reverse(_Number);
	}
	return _Number;
}





// Conversion from native byte order to big-endian order : short
short xanadu::endian::host_to_big(short _Number) noexcept
{
	return xanadu::endian::host_to_network(_Number);
}

// Conversion from native byte order to big-endian order : unsigned short
unsigned short xanadu::endian::host_to_big(unsigned short _Number) noexcept
{
	return xanadu::endian::host_to_network(_Number);
}

// Conversion from native byte order to big-endian order : int
int xanadu::endian::host_to_big(int _Number) noexcept
{
	return xanadu::endian::host_to_network(_Number);
}

// Conversion from native byte order to big-endian order : unsigned int
unsigned int xanadu::endian::host_to_big(unsigned int _Number) noexcept
{
	return xanadu::endian::host_to_network(_Number);
}

// Conversion from native byte order to big-endian order : long
long xanadu::endian::host_to_big(long _Number) noexcept
{
	return xanadu::endian::host_to_network(_Number);
}

// Conversion from native byte order to big-endian order : unsigned long
unsigned long xanadu::endian::host_to_big(unsigned long _Number) noexcept
{
	return xanadu::endian::host_to_network(_Number);
}

// Conversion from native byte order to big-endian order : long long
long long xanadu::endian::host_to_big(long long _Number) noexcept
{
	return xanadu::endian::host_to_network(_Number);
}

// Conversion from native byte order to big-endian order : unsigned short
unsigned long long xanadu::endian::host_to_big(unsigned long long _Number) noexcept
{
	return xanadu::endian::host_to_network(_Number);
}





// Conversion from big-endian order to native byte order : short
short xanadu::endian::big_to_host(short _Number) noexcept
{
	return xanadu::endian::network_to_host(_Number);
}

// Conversion from big-endian order to native byte order : unsigned short
unsigned short xanadu::endian::big_to_host(unsigned short _Number) noexcept
{
	return xanadu::endian::network_to_host(_Number);
}

// Conversion from big-endian order to native byte order : int
int xanadu::endian::big_to_host(int _Number) noexcept
{
	return xanadu::endian::network_to_host(_Number);
}

// Conversion from big-endian order to native byte order : unsigned int
unsigned int xanadu::endian::big_to_host(unsigned int _Number) noexcept
{
	return xanadu::endian::network_to_host(_Number);
}

// Conversion from big-endian order to native byte order : long
long xanadu::endian::big_to_host(long _Number) noexcept
{
	return xanadu::endian::network_to_host(_Number);
}

// Conversion from big-endian order to native byte order : unsigned long
unsigned long xanadu::endian::big_to_host(unsigned long _Number) noexcept
{
	return xanadu::endian::network_to_host(_Number);
}

// Conversion from big-endian order to native byte order : long long
long long xanadu::endian::big_to_host(long long _Number) noexcept
{
	return xanadu::endian::network_to_host(_Number);
}

// Conversion from big-endian order to native byte order : unsigned short
unsigned long long xanadu::endian::big_to_host(unsigned long long _Number) noexcept
{
	return xanadu::endian::network_to_host(_Number);
}




// Conversion from native byte order to little-endian order : short
short xanadu::endian::host_to_little(short _Number) noexcept
{
	return (short)xanadu::endian::host_to_little((unsigned short)_Number);
}

// Conversion from native byte order to little-endian order : unsigned short
unsigned short xanadu::endian::host_to_little(unsigned short _Number) noexcept
{
	if(xanadu::endian::is_little())
	{
		return _Number;
	}
	return xanadu::endian::reverse(_Number);
}

// Conversion from native byte order to little-endian order : int
int xanadu::endian::host_to_little(int _Number) noexcept
{
	return (int)xanadu::endian::host_to_little((unsigned int)_Number);
}

// Conversion from native byte order to little-endian order : unsigned int
unsigned int xanadu::endian::host_to_little(unsigned int _Number) noexcept
{
	if(xanadu::endian::is_little())
	{
		return _Number;
	}
	return xanadu::endian::reverse(_Number);
}

// Conversion from native byte order to little-endian order : long
long xanadu::endian::host_to_little(long _Number) noexcept
{
	return (long)xanadu::endian::host_to_little((unsigned long)_Number);
}

// Conversion from native byte order to little-endian order : unsigned long
unsigned long xanadu::endian::host_to_little(unsigned long _Number) noexcept
{
	if (sizeof(unsigned long) == 4)
	{
		return (unsigned long)xanadu::endian::host_to_little((unsigned int)_Number);
	}
	else
	{
		return (unsigned long)xanadu::endian::host_to_little((unsigned long long)_Number);
	}
}

// Conversion from native byte order to little-endian order : long long
long long xanadu::endian::host_to_little(long long _Number) noexcept
{
	return (long long)xanadu::endian::host_to_little((unsigned long long)_Number);
}

// Conversion from native byte order to little-endian order : unsigned short
unsigned long long xanadu::endian::host_to_little(unsigned long long _Number) noexcept
{
	if(xanadu::endian::is_little())
	{
		return _Number;
	}
	return xanadu::endian::reverse(_Number);
}





// Conversion from little-endian order to native byte order : short
short xanadu::endian::little_to_host(short _Number) noexcept
{
	return (short)xanadu::endian::little_to_host((unsigned short)_Number);
}

// Conversion from little-endian order to native byte order : unsigned short
unsigned short xanadu::endian::little_to_host(unsigned short _Number) noexcept
{
	if(xanadu::endian::is_little())
	{
		return _Number;
	}
	return xanadu::endian::reverse(_Number);
}

// Conversion from little-endian order to native byte order : int
int xanadu::endian::little_to_host(int _Number) noexcept
{
	return (int)xanadu::endian::little_to_host((unsigned int)_Number);
}

// Conversion from little-endian order to native byte order : unsigned int
unsigned int xanadu::endian::little_to_host(unsigned int _Number) noexcept
{
	if(xanadu::endian::is_little())
	{
		return _Number;
	}
	return xanadu::endian::reverse(_Number);
}

// Conversion from little-endian order to native byte order : long
long xanadu::endian::little_to_host(long _Number) noexcept
{
	return (long)xanadu::endian::little_to_host((unsigned long)_Number);
}

// Conversion from little-endian order to native byte order : unsigned long
unsigned long xanadu::endian::little_to_host(unsigned long _Number) noexcept
{
	if (sizeof(unsigned long) == 4)
	{
		return (unsigned long)xanadu::endian::little_to_host((unsigned int)_Number);
	}
	else
	{
		return (unsigned long)xanadu::endian::little_to_host((unsigned long long)_Number);
	}
}

// Conversion from little-endian order to native byte order : long long
long long xanadu::endian::little_to_host(long long _Number) noexcept
{
	return (long long)xanadu::endian::little_to_host((unsigned long long)_Number);
}

// Conversion from little-endian order to native byte order : unsigned short
unsigned long long xanadu::endian::little_to_host(unsigned long long _Number) noexcept
{
	if(xanadu::endian::is_little())
	{
		return _Number;
	}
	return xanadu::endian::reverse(_Number);
}
