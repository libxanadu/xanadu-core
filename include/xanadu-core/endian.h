#ifndef			_XANADU_CORE_ENDIAN_H_
#define			_XANADU_CORE_ENDIAN_H_

#include <xanadu-core/header.h>


/// namespace xanadu
namespace x
{
	/// class endian
	class _XCOREAPI_ endian
	{
	public:
		using				endian_type = x::size_type;

	public:
#if defined(XANADU_SYSTEM_WINDOWS)
		static const endian_type	little = 0;
		static const endian_type	big = 1;
		static const endian_type	pdp = 2;
		static const endian_type	native = little;
#elif defined(XANADU_COMPILER_CLANG) || defined(XANADU_COMPILER_GNUC)
		static const endian_type	little = __ORDER_LITTLE_ENDIAN__;
		static const endian_type	big = __ORDER_BIG_ENDIAN__;
		static const endian_type	pdp = __ORDER_PDP_ENDIAN__;
		static const endian_type	native = __BYTE_ORDER__;
#else
		static const endian_type	little = 0;
		static const endian_type	big = 1;
		static const endian_type	pdp = 2;
		static const endian_type	native = little;
#endif

	public:
		// constructor
		endian() noexcept;

		// destructor
		virtual ~endian() noexcept;

	public:
		// operator overload =
		endian& operator = (const endian& _Endian) noexcept;

		// operator overload =
		endian& operator = (endian&& _Endian) noexcept;

	public:
		// 检查操作系统是否为大端字节序
		static bool is_big() noexcept;

		// 检查操作系统是否为小端字节序
		static bool is_little() noexcept;

		// 检查操作系统是否为PDP字节序
		static bool is_pdp() noexcept;

	public:
		// reverse : memory
		static void reverse(void* _Memory, std::size_t _Size) noexcept;

	public:
		// reverse : short
		static short reverse(short _Number) noexcept;

		// reverse : unsigned short
		static unsigned short reverse(unsigned short _Number) noexcept;

		// reverse : int
		static int reverse(int _Number) noexcept;

		// reverse : unsigned int
		static unsigned int reverse(unsigned int _Number) noexcept;

		// reverse : long
		static long reverse(long _Number) noexcept;

		// reverse : unsigned long
		static unsigned long reverse(unsigned long _Number) noexcept;

		// reverse : long long
		static long long reverse(long long _Number) noexcept;

		// reverse : unsigned long long
		static unsigned long long reverse(unsigned long long _Number) noexcept;

	public:
		// Conversion from native byte order to network byte order : short
		static short host_to_network(short _Number) noexcept;

		// Conversion from native byte order to network byte order : unsigned short
		static unsigned short host_to_network(unsigned short _Number) noexcept;

		// Conversion from native byte order to network byte order : int
		static int host_to_network(int _Number) noexcept;

		// Conversion from native byte order to network byte order : unsigned int
		static unsigned int host_to_network(unsigned int _Number) noexcept;

		// Conversion from native byte order to network byte order : long
		static long host_to_network(long _Number) noexcept;

		// Conversion from native byte order to network byte order : unsigned long
		static unsigned long host_to_network(unsigned long _Number) noexcept;

		// Conversion from native byte order to network byte order : long long
		static long long host_to_network(long long _Number) noexcept;

		// Conversion from native byte order to network byte order : unsigned short
		static unsigned long long host_to_network(unsigned long long _Number) noexcept;

	public:
		// Conversion from network byte order to native byte order : short
		static short network_to_host(short _Number) noexcept;

		// Conversion from network byte order to native byte order : unsigned short
		static unsigned short network_to_host(unsigned short _Number) noexcept;

		// Conversion from network byte order to native byte order : int
		static int network_to_host(int _Number) noexcept;

		// Conversion from network byte order to native byte order : unsigned int
		static unsigned int network_to_host(unsigned int _Number) noexcept;

		// Conversion from network byte order to native byte order : long
		static long network_to_host(long _Number) noexcept;

		// Conversion from network byte order to native byte order : unsigned long
		static unsigned long network_to_host(unsigned long _Number) noexcept;

		// Conversion from network byte order to native byte order : long long
		static long long network_to_host(long long _Number) noexcept;

		// Conversion from network byte order to native byte order : unsigned short
		static unsigned long long network_to_host(unsigned long long _Number) noexcept;

	public:
		// Conversion from native byte order to big-endian order : short
		static short host_to_big(short _Number) noexcept;

		// Conversion from native byte order to big-endian order : unsigned short
		static unsigned short host_to_big(unsigned short _Number) noexcept;

		// Conversion from native byte order to big-endian order : int
		static int host_to_big(int _Number) noexcept;

		// Conversion from native byte order to big-endian order : unsigned int
		static unsigned int host_to_big(unsigned int _Number) noexcept;

		// Conversion from native byte order to big-endian order : long
		static long host_to_big(long _Number) noexcept;

		// Conversion from native byte order to big-endian order : unsigned long
		static unsigned long host_to_big(unsigned long _Number) noexcept;

		// Conversion from native byte order to big-endian order : long long
		static long long host_to_big(long long _Number) noexcept;

		// Conversion from native byte order to big-endian order : unsigned short
		static unsigned long long host_to_big(unsigned long long _Number) noexcept;

	public:
		// Conversion from big-endian order to native byte order : short
		static short big_to_host(short _Number) noexcept;

		// Conversion from big-endian order to native byte order : unsigned short
		static unsigned short big_to_host(unsigned short _Number) noexcept;

		// Conversion from big-endian order to native byte order : int
		static int big_to_host(int _Number) noexcept;

		// Conversion from big-endian order to native byte order : unsigned int
		static unsigned int big_to_host(unsigned int _Number) noexcept;

		// Conversion from big-endian order to native byte order : long
		static long big_to_host(long _Number) noexcept;

		// Conversion from big-endian order to native byte order : unsigned long
		static unsigned long big_to_host(unsigned long _Number) noexcept;

		// Conversion from big-endian order to native byte order : long long
		static long long big_to_host(long long _Number) noexcept;

		// Conversion from big-endian order to native byte order : unsigned short
		static unsigned long long big_to_host(unsigned long long _Number) noexcept;

	public:
		// Conversion from native byte order to little-endian order : short
		static short host_to_little(short _Number) noexcept;

		// Conversion from native byte order to little-endian order : unsigned short
		static unsigned short host_to_little(unsigned short _Number) noexcept;

		// Conversion from native byte order to little-endian order : int
		static int host_to_little(int _Number) noexcept;

		// Conversion from native byte order to little-endian order : unsigned int
		static unsigned int host_to_little(unsigned int _Number) noexcept;

		// Conversion from native byte order to little-endian order : long
		static long host_to_little(long _Number) noexcept;

		// Conversion from native byte order to little-endian order : unsigned long
		static unsigned long host_to_little(unsigned long _Number) noexcept;

		// Conversion from native byte order to little-endian order : long long
		static long long host_to_little(long long _Number) noexcept;

		// Conversion from native byte order to little-endian order : unsigned short
		static unsigned long long host_to_little(unsigned long long _Number) noexcept;

	public:
		// Conversion from little-endian order to native byte order : short
		static short little_to_host(short _Number) noexcept;

		// Conversion from little-endian order to native byte order : unsigned short
		static unsigned short little_to_host(unsigned short _Number) noexcept;

		// Conversion from little-endian order to native byte order : int
		static int little_to_host(int _Number) noexcept;

		// Conversion from little-endian order to native byte order : unsigned int
		static unsigned int little_to_host(unsigned int _Number) noexcept;

		// Conversion from little-endian order to native byte order : long
		static long little_to_host(long _Number) noexcept;

		// Conversion from little-endian order to native byte order : unsigned long
		static unsigned long little_to_host(unsigned long _Number) noexcept;

		// Conversion from little-endian order to native byte order : long long
		static long long little_to_host(long long _Number) noexcept;

		// Conversion from little-endian order to native byte order : unsigned short
		static unsigned long long little_to_host(unsigned long long _Number) noexcept;
	};
}

#endif
