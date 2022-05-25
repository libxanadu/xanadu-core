#include <xanadu-core/endian.h>



// constructor
x::endian::endian() noexcept = default;

// destructor
x::endian::~endian() noexcept = default;



// operator overload =
x::endian& x::endian::operator = (const endian& _Endian) noexcept = default;

// operator overload =
x::endian& x::endian::operator = (endian&& _Endian) noexcept = default;



// 检查操作系统是否为大端字节序
bool x::endian::is_big() noexcept
{
	return x::endian::native == x::endian::big;
}

// 检查操作系统是否为小端字节序
bool x::endian::is_little() noexcept
{
	return x::endian::native == x::endian::little;
}

// 检查操作系统是否为PDP字节序
bool x::endian::is_pdp() noexcept
{
	return x::endian::native == x::endian::pdp;
}



// reverse : memory
void x::endian::reverse(void* _Memory, std::size_t _Size) noexcept
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
short x::endian::reverse(short _Number) noexcept
{
	return (short)x::endian::reverse((unsigned short)_Number);
}

// reverse : unsigned short
unsigned short x::endian::reverse(unsigned short _Number) noexcept
{
	return (((_Number & 0x00FF) << 8) | ((_Number & 0xFF00) >> 8));
}

// reverse : int
int x::endian::reverse(int _Number) noexcept
{
	return (int)x::endian::reverse((unsigned int)_Number);
}

// reverse : unsigned int
unsigned int x::endian::reverse(unsigned int _Number) noexcept
{
	return (((_Number & 0xFF000000) >> 24) | ((_Number & 0x00FF0000) >> 8) | ((_Number & 0x0000FF00) << 8) | ((_Number & 0x000000FF) << 24));
}

// reverse : long
long x::endian::reverse(long _Number) noexcept
{
	return (long)x::endian::reverse((unsigned long)_Number);
}

// reverse : unsigned long
unsigned long x::endian::reverse(unsigned long _Number) noexcept
{
	if (sizeof(unsigned long) == 4)
	{
		return (unsigned long)x::endian::reverse((unsigned int)_Number);
	}
	else
	{
		return (unsigned long)x::endian::reverse((unsigned long long)_Number);
	}
}

// reverse : long long
long long x::endian::reverse(long long _Number) noexcept
{
	return (long long)x::endian::reverse((unsigned long long)_Number);
}

// reverse : unsigned short
unsigned long long x::endian::reverse(unsigned long long _Number) noexcept
{
	return (((_Number & 0x00000000000000FFULL) << 56) | ((_Number & 0x000000000000FF00ULL) << 40) |
		((_Number & 0x0000000000FF0000ULL) << 24) | ((_Number & 0x00000000FF000000ULL) << 8) |
		((_Number & 0x000000FF00000000ULL) >> 8) | ((_Number & 0x0000FF0000000000ULL) >> 24) |
		((_Number & 0x00FF000000000000ULL) >> 40) | ((_Number & 0xFF00000000000000ULL) >> 56));
}





// Conversion from native byte order to network byte order : short
short x::endian::host_to_network(short _Number) noexcept
{
	return (short)x::endian::host_to_network((unsigned short)_Number);
}

// Conversion from native byte order to network byte order : unsigned short
unsigned short x::endian::host_to_network(unsigned short _Number) noexcept
{
	if(x::endian::is_little())
	{
		return x::endian::reverse(_Number);
	}
	return _Number;
}

// Conversion from native byte order to network byte order : int
int x::endian::host_to_network(int _Number) noexcept
{
	return (int)x::endian::host_to_network((unsigned int)_Number);
}

// Conversion from native byte order to network byte order : unsigned int
unsigned int x::endian::host_to_network(unsigned int _Number) noexcept
{
	if(x::endian::is_little())
	{
		return x::endian::reverse(_Number);
	}
	return _Number;
}

// Conversion from native byte order to network byte order : long
long x::endian::host_to_network(long _Number) noexcept
{
	return (long)x::endian::host_to_network((unsigned long)_Number);
}

// Conversion from native byte order to network byte order : unsigned long
unsigned long x::endian::host_to_network(unsigned long _Number) noexcept
{
	if (sizeof(unsigned long) == 4)
	{
		return (unsigned long)x::endian::host_to_network((unsigned int)_Number);
	}
	else
	{
		return (unsigned long)x::endian::host_to_network((unsigned long long)_Number);
	}
}

// Conversion from native byte order to network byte order : long long
long long x::endian::host_to_network(long long _Number) noexcept
{
	return (long long)x::endian::host_to_network((unsigned long long)_Number);
}

// Conversion from native byte order to network byte order : unsigned short
unsigned long long x::endian::host_to_network(unsigned long long _Number) noexcept
{
	if(x::endian::is_little())
	{
		return x::endian::reverse(_Number);
	}
	return _Number;
}





// Conversion from network byte order to native byte order : short
short x::endian::network_to_host(short _Number) noexcept
{
	return (short)x::endian::network_to_host((unsigned short)_Number);
}

// Conversion from network byte order to native byte order : unsigned short
unsigned short x::endian::network_to_host(unsigned short _Number) noexcept
{
	if(x::endian::is_little())
	{
		return x::endian::reverse(_Number);
	}
	return _Number;
}

// Conversion from network byte order to native byte order : int
int x::endian::network_to_host(int _Number) noexcept
{
	return (int)x::endian::network_to_host((unsigned int)_Number);
}

// Conversion from network byte order to native byte order : unsigned int
unsigned int x::endian::network_to_host(unsigned int _Number) noexcept
{
	if(x::endian::is_little())
	{
		return x::endian::reverse(_Number);
	}
	return _Number;
}

// Conversion from network byte order to native byte order : long
long x::endian::network_to_host(long _Number) noexcept
{
	return (long)x::endian::network_to_host((unsigned long)_Number);
}

// Conversion from network byte order to native byte order : unsigned long
unsigned long x::endian::network_to_host(unsigned long _Number) noexcept
{
	if (sizeof(unsigned long) == 4)
	{
		return (unsigned long)x::endian::network_to_host((unsigned int)_Number);
	}
	else
	{
		return (unsigned long)x::endian::network_to_host((unsigned long long)_Number);
	}
}

// Conversion from network byte order to native byte order : long long
long long x::endian::network_to_host(long long _Number) noexcept
{
	return (long long)x::endian::network_to_host((unsigned long long)_Number);
}

// Conversion from network byte order to native byte order : unsigned short
unsigned long long x::endian::network_to_host(unsigned long long _Number) noexcept
{
	if(x::endian::is_little())
	{
		return x::endian::reverse(_Number);
	}
	return _Number;
}





// Conversion from native byte order to big-endian order : short
short x::endian::host_to_big(short _Number) noexcept
{
	return x::endian::host_to_network(_Number);
}

// Conversion from native byte order to big-endian order : unsigned short
unsigned short x::endian::host_to_big(unsigned short _Number) noexcept
{
	return x::endian::host_to_network(_Number);
}

// Conversion from native byte order to big-endian order : int
int x::endian::host_to_big(int _Number) noexcept
{
	return x::endian::host_to_network(_Number);
}

// Conversion from native byte order to big-endian order : unsigned int
unsigned int x::endian::host_to_big(unsigned int _Number) noexcept
{
	return x::endian::host_to_network(_Number);
}

// Conversion from native byte order to big-endian order : long
long x::endian::host_to_big(long _Number) noexcept
{
	return x::endian::host_to_network(_Number);
}

// Conversion from native byte order to big-endian order : unsigned long
unsigned long x::endian::host_to_big(unsigned long _Number) noexcept
{
	return x::endian::host_to_network(_Number);
}

// Conversion from native byte order to big-endian order : long long
long long x::endian::host_to_big(long long _Number) noexcept
{
	return x::endian::host_to_network(_Number);
}

// Conversion from native byte order to big-endian order : unsigned short
unsigned long long x::endian::host_to_big(unsigned long long _Number) noexcept
{
	return x::endian::host_to_network(_Number);
}





// Conversion from big-endian order to native byte order : short
short x::endian::big_to_host(short _Number) noexcept
{
	return x::endian::network_to_host(_Number);
}

// Conversion from big-endian order to native byte order : unsigned short
unsigned short x::endian::big_to_host(unsigned short _Number) noexcept
{
	return x::endian::network_to_host(_Number);
}

// Conversion from big-endian order to native byte order : int
int x::endian::big_to_host(int _Number) noexcept
{
	return x::endian::network_to_host(_Number);
}

// Conversion from big-endian order to native byte order : unsigned int
unsigned int x::endian::big_to_host(unsigned int _Number) noexcept
{
	return x::endian::network_to_host(_Number);
}

// Conversion from big-endian order to native byte order : long
long x::endian::big_to_host(long _Number) noexcept
{
	return x::endian::network_to_host(_Number);
}

// Conversion from big-endian order to native byte order : unsigned long
unsigned long x::endian::big_to_host(unsigned long _Number) noexcept
{
	return x::endian::network_to_host(_Number);
}

// Conversion from big-endian order to native byte order : long long
long long x::endian::big_to_host(long long _Number) noexcept
{
	return x::endian::network_to_host(_Number);
}

// Conversion from big-endian order to native byte order : unsigned short
unsigned long long x::endian::big_to_host(unsigned long long _Number) noexcept
{
	return x::endian::network_to_host(_Number);
}




// Conversion from native byte order to little-endian order : short
short x::endian::host_to_little(short _Number) noexcept
{
	return (short)x::endian::host_to_little((unsigned short)_Number);
}

// Conversion from native byte order to little-endian order : unsigned short
unsigned short x::endian::host_to_little(unsigned short _Number) noexcept
{
	if(x::endian::is_little())
	{
		return _Number;
	}
	return x::endian::reverse(_Number);
}

// Conversion from native byte order to little-endian order : int
int x::endian::host_to_little(int _Number) noexcept
{
	return (int)x::endian::host_to_little((unsigned int)_Number);
}

// Conversion from native byte order to little-endian order : unsigned int
unsigned int x::endian::host_to_little(unsigned int _Number) noexcept
{
	if(x::endian::is_little())
	{
		return _Number;
	}
	return x::endian::reverse(_Number);
}

// Conversion from native byte order to little-endian order : long
long x::endian::host_to_little(long _Number) noexcept
{
	return (long)x::endian::host_to_little((unsigned long)_Number);
}

// Conversion from native byte order to little-endian order : unsigned long
unsigned long x::endian::host_to_little(unsigned long _Number) noexcept
{
	if (sizeof(unsigned long) == 4)
	{
		return (unsigned long)x::endian::host_to_little((unsigned int)_Number);
	}
	else
	{
		return (unsigned long)x::endian::host_to_little((unsigned long long)_Number);
	}
}

// Conversion from native byte order to little-endian order : long long
long long x::endian::host_to_little(long long _Number) noexcept
{
	return (long long)x::endian::host_to_little((unsigned long long)_Number);
}

// Conversion from native byte order to little-endian order : unsigned short
unsigned long long x::endian::host_to_little(unsigned long long _Number) noexcept
{
	if(x::endian::is_little())
	{
		return _Number;
	}
	return x::endian::reverse(_Number);
}





// Conversion from little-endian order to native byte order : short
short x::endian::little_to_host(short _Number) noexcept
{
	return (short)x::endian::little_to_host((unsigned short)_Number);
}

// Conversion from little-endian order to native byte order : unsigned short
unsigned short x::endian::little_to_host(unsigned short _Number) noexcept
{
	if(x::endian::is_little())
	{
		return _Number;
	}
	return x::endian::reverse(_Number);
}

// Conversion from little-endian order to native byte order : int
int x::endian::little_to_host(int _Number) noexcept
{
	return (int)x::endian::little_to_host((unsigned int)_Number);
}

// Conversion from little-endian order to native byte order : unsigned int
unsigned int x::endian::little_to_host(unsigned int _Number) noexcept
{
	if(x::endian::is_little())
	{
		return _Number;
	}
	return x::endian::reverse(_Number);
}

// Conversion from little-endian order to native byte order : long
long x::endian::little_to_host(long _Number) noexcept
{
	return (long)x::endian::little_to_host((unsigned long)_Number);
}

// Conversion from little-endian order to native byte order : unsigned long
unsigned long x::endian::little_to_host(unsigned long _Number) noexcept
{
	if (sizeof(unsigned long) == 4)
	{
		return (unsigned long)x::endian::little_to_host((unsigned int)_Number);
	}
	else
	{
		return (unsigned long)x::endian::little_to_host((unsigned long long)_Number);
	}
}

// Conversion from little-endian order to native byte order : long long
long long x::endian::little_to_host(long long _Number) noexcept
{
	return (long long)x::endian::little_to_host((unsigned long long)_Number);
}

// Conversion from little-endian order to native byte order : unsigned short
unsigned long long x::endian::little_to_host(unsigned long long _Number) noexcept
{
	if(x::endian::is_little())
	{
		return _Number;
	}
	return x::endian::reverse(_Number);
}
