/*
 * This is an OpenSSL-compatible implementation of the RSA Data Security, Inc.
 * MD5 Message-Digest Algorithm (RFC 1321).
 */

#include <xanadu-core/header.h>
#include "XHashMD5.h"

/*
 * The basic MD5 functions.
 *
 * F and G are optimized compared to their RFC 1321 definitions for
 * architectures that lack an AND-NOT instruction, just like in Colin Plumb's
 * implementation.
 */
#define F(x, y, z)			((z) ^ ((x) & ((y) ^ (z))))
#define G(x, y, z)			((y) ^ ((z) & ((x) ^ (y))))
#define H(x, y, z)			(((x) ^ (y)) ^ (z))
#define H2(x, y, z)			((x) ^ ((y) ^ (z)))
#define I(x, y, z)			((y) ^ ((x) | ~(z)))

/*
 * The MD5 transformation for all four rounds.
 */
#define STEP(f, a, b, c, d, x, t, s) \
	(a) += f((b), (c), (d)) + (x) + (t); \
	(a) = (((a) << (s)) | (((a) & 0xffffffff) >> (32 - (s)))); \
	(a) += (b);

/*
 * SET reads 4 input bytes in little-endian byte order and stores them in a
 * properly aligned word in host byte order.
 *
 * The check for little-endian architectures that tolerate unaligned memory
 * accesses is just an optimization.  Nothing will break if it fails to detect
 * a suitable architecture.
 *
 * Unfortunately, this optimization may be a C strict aliasing rules violation
 * if the caller's data buffer has effective type that cannot be aliased by
 * std::uint32_t.  In practice, this problem may occur if these MD5 routines are
 * inlined into a calling function, or with future and dangerously advanced
 * link-time optimizations.  For the time being, keeping these MD5 routines in
 * their own translation unit avoids the problem.
 */
#if defined(__i386__) || defined(__x86_64__) || defined(__vax__)
#define SET(n) \
	(*(std::uint32_t *)&ptr[(n) * 4])
#define GET(n) \
	SET(n)
#else
#define SET(n) \
	(_Context->block[(n)] = \
	(std::uint32_t)ptr[(n) * 4] | \
	((std::uint32_t)ptr[(n) * 4 + 1] << 8) | \
	((std::uint32_t)ptr[(n) * 4 + 2] << 16) | \
	((std::uint32_t)ptr[(n) * 4 + 3] << 24))
#define GET(n) \
	(_Context->block[(n)])
#endif

/*
 * This processes one or more 64-byte _Data blocks, but does NOT update the bit
 * counters.  There are no alignment requirements.
 */
static const void* body(XANADU_CORE_MD5_CONTEXT* _Context, const void* _Data, unsigned long _Size)
{
	const unsigned char *ptr;
	std::uint32_t a, b, c, d;
	std::uint32_t saved_a, saved_b, saved_c, saved_d;

	ptr = (const unsigned char *)_Data;

	a = _Context->a;
	b = _Context->b;
	c = _Context->c;
	d = _Context->d;

	do {
		saved_a = a;
		saved_b = b;
		saved_c = c;
		saved_d = d;

/* Round 1 */
		STEP(F, a, b, c, d, SET(0), 0xd76aa478, 7)
		STEP(F, d, a, b, c, SET(1), 0xe8c7b756, 12)
		STEP(F, c, d, a, b, SET(2), 0x242070db, 17)
		STEP(F, b, c, d, a, SET(3), 0xc1bdceee, 22)
		STEP(F, a, b, c, d, SET(4), 0xf57c0faf, 7)
		STEP(F, d, a, b, c, SET(5), 0x4787c62a, 12)
		STEP(F, c, d, a, b, SET(6), 0xa8304613, 17)
		STEP(F, b, c, d, a, SET(7), 0xfd469501, 22)
		STEP(F, a, b, c, d, SET(8), 0x698098d8, 7)
		STEP(F, d, a, b, c, SET(9), 0x8b44f7af, 12)
		STEP(F, c, d, a, b, SET(10), 0xffff5bb1, 17)
		STEP(F, b, c, d, a, SET(11), 0x895cd7be, 22)
		STEP(F, a, b, c, d, SET(12), 0x6b901122, 7)
		STEP(F, d, a, b, c, SET(13), 0xfd987193, 12)
		STEP(F, c, d, a, b, SET(14), 0xa679438e, 17)
		STEP(F, b, c, d, a, SET(15), 0x49b40821, 22)

/* Round 2 */
		STEP(G, a, b, c, d, GET(1), 0xf61e2562, 5)
		STEP(G, d, a, b, c, GET(6), 0xc040b340, 9)
		STEP(G, c, d, a, b, GET(11), 0x265e5a51, 14)
		STEP(G, b, c, d, a, GET(0), 0xe9b6c7aa, 20)
		STEP(G, a, b, c, d, GET(5), 0xd62f105d, 5)
		STEP(G, d, a, b, c, GET(10), 0x02441453, 9)
		STEP(G, c, d, a, b, GET(15), 0xd8a1e681, 14)
		STEP(G, b, c, d, a, GET(4), 0xe7d3fbc8, 20)
		STEP(G, a, b, c, d, GET(9), 0x21e1cde6, 5)
		STEP(G, d, a, b, c, GET(14), 0xc33707d6, 9)
		STEP(G, c, d, a, b, GET(3), 0xf4d50d87, 14)
		STEP(G, b, c, d, a, GET(8), 0x455a14ed, 20)
		STEP(G, a, b, c, d, GET(13), 0xa9e3e905, 5)
		STEP(G, d, a, b, c, GET(2), 0xfcefa3f8, 9)
		STEP(G, c, d, a, b, GET(7), 0x676f02d9, 14)
		STEP(G, b, c, d, a, GET(12), 0x8d2a4c8a, 20)

/* Round 3 */
		STEP(H, a, b, c, d, GET(5), 0xfffa3942, 4)
		STEP(H2, d, a, b, c, GET(8), 0x8771f681, 11)
		STEP(H, c, d, a, b, GET(11), 0x6d9d6122, 16)
		STEP(H2, b, c, d, a, GET(14), 0xfde5380c, 23)
		STEP(H, a, b, c, d, GET(1), 0xa4beea44, 4)
		STEP(H2, d, a, b, c, GET(4), 0x4bdecfa9, 11)
		STEP(H, c, d, a, b, GET(7), 0xf6bb4b60, 16)
		STEP(H2, b, c, d, a, GET(10), 0xbebfbc70, 23)
		STEP(H, a, b, c, d, GET(13), 0x289b7ec6, 4)
		STEP(H2, d, a, b, c, GET(0), 0xeaa127fa, 11)
		STEP(H, c, d, a, b, GET(3), 0xd4ef3085, 16)
		STEP(H2, b, c, d, a, GET(6), 0x04881d05, 23)
		STEP(H, a, b, c, d, GET(9), 0xd9d4d039, 4)
		STEP(H2, d, a, b, c, GET(12), 0xe6db99e5, 11)
		STEP(H, c, d, a, b, GET(15), 0x1fa27cf8, 16)
		STEP(H2, b, c, d, a, GET(2), 0xc4ac5665, 23)

/* Round 4 */
		STEP(I, a, b, c, d, GET(0), 0xf4292244, 6)
		STEP(I, d, a, b, c, GET(7), 0x432aff97, 10)
		STEP(I, c, d, a, b, GET(14), 0xab9423a7, 15)
		STEP(I, b, c, d, a, GET(5), 0xfc93a039, 21)
		STEP(I, a, b, c, d, GET(12), 0x655b59c3, 6)
		STEP(I, d, a, b, c, GET(3), 0x8f0ccc92, 10)
		STEP(I, c, d, a, b, GET(10), 0xffeff47d, 15)
		STEP(I, b, c, d, a, GET(1), 0x85845dd1, 21)
		STEP(I, a, b, c, d, GET(8), 0x6fa87e4f, 6)
		STEP(I, d, a, b, c, GET(15), 0xfe2ce6e0, 10)
		STEP(I, c, d, a, b, GET(6), 0xa3014314, 15)
		STEP(I, b, c, d, a, GET(13), 0x4e0811a1, 21)
		STEP(I, a, b, c, d, GET(4), 0xf7537e82, 6)
		STEP(I, d, a, b, c, GET(11), 0xbd3af235, 10)
		STEP(I, c, d, a, b, GET(2), 0x2ad7d2bb, 15)
		STEP(I, b, c, d, a, GET(9), 0xeb86d391, 21)

		a += saved_a;
		b += saved_b;
		c += saved_c;
		d += saved_d;

		ptr += 64;
	} while (_Size -= 64);

	_Context->a = a;
	_Context->b = b;
	_Context->c = c;
	_Context->d = d;

	return ptr;
}

_XCOREAPI_ void __xcall__ Xanadu::MD5_Init(XANADU_CORE_MD5_CONTEXT* _Context) noexcept
{
	_Context->a = 0x67452301;
	_Context->b = 0xefcdab89;
	_Context->c = 0x98badcfe;
	_Context->d = 0x10325476;

	_Context->lo = 0;
	_Context->hi = 0;
}

_XCOREAPI_ void __xcall__ Xanadu::MD5_Update(XANADU_CORE_MD5_CONTEXT* _Context, const void* _Data, std::uint64_t _Size) noexcept
{
	auto 		saved_lo = static_cast<std::uint32_t>(0U);
	auto 		used = static_cast<std::uint64_t>(0U);
	auto 		available = static_cast<std::uint64_t>(0U);

	saved_lo = _Context->lo;
	if ((_Context->lo = (saved_lo + _Size) & 0x1fffffff) < saved_lo)
	{
		_Context->hi++;
	}
	_Context->hi += static_cast<std::uint32_t>(_Size >> 29);

	used = saved_lo & 0x3f;

	if (used)
	{
		available = 64 - used;

		if (_Size < available)
		{
			x_posix_memcpy(&_Context->buffer[used], _Data, (std::size_t)_Size);
			return;
		}

		x_posix_memcpy(&_Context->buffer[used], _Data, (std::size_t)available);
		_Data = (const unsigned char *)_Data + available;
		_Size -= available;
		body(_Context, _Context->buffer, 64);
	}

	if (_Size >= 64)
	{
		_Data = body(_Context, _Data, _Size & ~(unsigned long)0x3f);
		_Size &= 0x3f;
	}

	x_posix_memcpy(_Context->buffer, _Data, (std::size_t)_Size);
}

#define MD5_OUT(dst, src) \
	(dst)[0] = (unsigned char)(src); \
	(dst)[1] = (unsigned char)((src) >> 8); \
	(dst)[2] = (unsigned char)((src) >> 16); \
	(dst)[3] = (unsigned char)((src) >> 24);

_XCOREAPI_ void __xcall__ Xanadu::MD5_Final(unsigned char* _Result, XANADU_CORE_MD5_CONTEXT* _Context) noexcept
{
	unsigned long used, available;

	used = _Context->lo & 0x3f;

	_Context->buffer[used++] = 0x80;

	available = 64 - used;

	if (available < 8) {
		memset(&_Context->buffer[used], 0, available);
		body(_Context, _Context->buffer, 64);
		used = 0;
		available = 64;
	}

	x_posix_memset(&_Context->buffer[used], 0, available - 8);

	_Context->lo <<= 3;
	MD5_OUT(&_Context->buffer[56], _Context->lo)
	MD5_OUT(&_Context->buffer[60], _Context->hi)

	body(_Context, _Context->buffer, 64);

	MD5_OUT(&_Result[0], _Context->a)
	MD5_OUT(&_Result[4], _Context->b)
	MD5_OUT(&_Result[8], _Context->c)
	MD5_OUT(&_Result[12], _Context->d)

	x_posix_memset(_Context, 0, sizeof(*_Context));
}
