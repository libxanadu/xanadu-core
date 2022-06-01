#include <xanadu-core/header.h>
#include "XHashSHA1.h"

#if defined( _MSC_VER ) && ( _MSC_VER > 800 )
#pragma intrinsic(memcpy)
#pragma intrinsic(memset)
#endif

#if 0 && defined(_MSC_VER)
#define rotl32  _lrotl
#define rotr32  _lrotr
#else
#define rotl32(x,n)   (((x) << n) | ((x) >> (32 - n)))
#define rotr32(x,n)   (((x) >> n) | ((x) << (32 - n)))
#endif

#if !defined(bswap_32)
#define bswap_32(x) ((rotr32((x), 24) & 0x00ff00ff) | (rotr32((x), 8) & 0xff00ff00))
#endif

#if (PLATFORM_BYTE_ORDER == IS_LITTLE_ENDIAN)
#define SWAP_BYTES
#else
#undef  SWAP_BYTES
#endif

#if defined(SWAP_BYTES)
#define bsw_32(p,n) \
    { int _i = (n); while(_i--) ((std::uint32_t*)p)[_i] = bswap_32(((std::uint32_t*)p)[_i]); }
#else
#define bsw_32(p,n)
#endif

#define SHA1_MASK   (SHA1_BLOCK_SIZE - 1)

#if 0

#define ch(x,y,z)       (((x) & (y)) ^ (~(x) & (z)))
#define parity(x,y,z)   ((x) ^ (y) ^ (z))
#define maj(x,y,z)      (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))

#else   /* Discovered by Rich Schroeppel and Colin Plumb   */

#define ch(x,y,z)       ((z) ^ ((x) & ((y) ^ (z))))
#define parity(x,y,z)   ((x) ^ (y) ^ (z))
#define maj(x,y,z)      (((x) & (y)) | ((z) & ((x) ^ (y))))

#endif

/* Compile 64 bytes of hash data into SHA1 context. Note    */
/* that this routine assumes that the byte order in the     */
/* ctx->wbuf[] at this point is in such an order that low   */
/* address bytes in the ORIGINAL byte stream will go in     */
/* this buffer to the high end of 32-bit words on BOTH big  */
/* and little XEndian systems                                */

#ifdef ARRAY
#define q(v,n)  v[n]
#else
#define q(v,n)  v##n
#endif

#define one_cycle(v,a,b,c,d,e,f,k,h)		\
	q(v,e) += rotr32(q(v,a),27) +		\
	f(q(v,b),q(v,c),q(v,d)) + k + h;	\
	q(v,b)  = rotr32(q(v,b), 2)

#define five_cycle(v,f,k,i)			\
	one_cycle(v, 0,1,2,3,4, f,k,hf(i  ));	\
	one_cycle(v, 4,0,1,2,3, f,k,hf(i+1));	\
	one_cycle(v, 3,4,0,1,2, f,k,hf(i+2));	\
	one_cycle(v, 2,3,4,0,1, f,k,hf(i+3));	\
	one_cycle(v, 1,2,3,4,0, f,k,hf(i+4))

_XCOREAPI_ void __xcall__ Xanadu::sha1_compile(XANADU_CORE_SHA1_CONTEXT _Context[1]) noexcept
{
	std::uint32_t    *w = _Context->wbuf;

#ifdef ARRAY
	std::uint32_t    v[5];
	x_posix_memcpy(v, _Context->hash, sizeof(_Context->hash));
#else
	std::uint32_t    v0, v1, v2, v3, v4;
	v0 = _Context->hash[0]; v1 = _Context->hash[1];
	v2 = _Context->hash[2]; v3 = _Context->hash[3];
	v4 = _Context->hash[4];
#endif

#define hf(i)   w[i]

	five_cycle(v, ch, 0x5a827999,  0);
	five_cycle(v, ch, 0x5a827999,  5);
	five_cycle(v, ch, 0x5a827999, 10);
	one_cycle(v,0,1,2,3,4, ch, 0x5a827999, hf(15)); \

#undef  hf
#define hf(i) (w[(i) & 15] = rotl32(                    \
                 w[((i) + 13) & 15] ^ w[((i) + 8) & 15] \
               ^ w[((i) +  2) & 15] ^ w[(i) & 15], 1))

	one_cycle(v,4,0,1,2,3, ch, 0x5a827999, hf(16));
	one_cycle(v,3,4,0,1,2, ch, 0x5a827999, hf(17));
	one_cycle(v,2,3,4,0,1, ch, 0x5a827999, hf(18));
	one_cycle(v,1,2,3,4,0, ch, 0x5a827999, hf(19));

	five_cycle(v, parity, 0x6ed9eba1,  20);
	five_cycle(v, parity, 0x6ed9eba1,  25);
	five_cycle(v, parity, 0x6ed9eba1,  30);
	five_cycle(v, parity, 0x6ed9eba1,  35);

	five_cycle(v, maj, 0x8f1bbcdc,  40);
	five_cycle(v, maj, 0x8f1bbcdc,  45);
	five_cycle(v, maj, 0x8f1bbcdc,  50);
	five_cycle(v, maj, 0x8f1bbcdc,  55);

	five_cycle(v, parity, 0xca62c1d6,  60);
	five_cycle(v, parity, 0xca62c1d6,  65);
	five_cycle(v, parity, 0xca62c1d6,  70);
	five_cycle(v, parity, 0xca62c1d6,  75);

#ifdef ARRAY
	_Context->hash[0] += v[0]; _Context->hash[1] += v[1];
	_Context->hash[2] += v[2]; _Context->hash[3] += v[3];
	_Context->hash[4] += v[4];
#else
	_Context->hash[0] += v0; _Context->hash[1] += v1;
	_Context->hash[2] += v2; _Context->hash[3] += v3;
	_Context->hash[4] += v4;
#endif
}

_XCOREAPI_ void __xcall__ Xanadu::sha1_begin(XANADU_CORE_SHA1_CONTEXT ctx[1]) noexcept
{
	x_posix_memset(ctx, 0, sizeof(XANADU_CORE_SHA1_CONTEXT));
	ctx->hash[0] = 0x67452301;
	ctx->hash[1] = 0xefcdab89;
	ctx->hash[2] = 0x98badcfe;
	ctx->hash[3] = 0x10325476;
	ctx->hash[4] = 0xc3d2e1f0;
}

/* SHA1 hash _Data in an array of bytes into hash buffer and */
/* call the hash_compile function as required. For both the */
/* bit and byte orientated versions, the block length '_Length' */
/* must not be greater than 2^32 - 1 bits (2^29 - 1 bytes)  */
_XCOREAPI_ void __xcall__ Xanadu::sha1_hash(const unsigned char _Data[], std::uint64_t _Length, XANADU_CORE_SHA1_CONTEXT _Context[1]) noexcept
{
	std::uint32_t pos = (std::uint32_t)((_Context->count[0] >> 3) & SHA1_MASK);
	const unsigned char *sp = _Data;
	unsigned char *w = (unsigned char*)_Context->wbuf;
#if SHA1_BITS == 1
	std::uint32_t ofs = (_Context->count[0] & 7);
#else
	_Length <<= 3;
#endif
	if((_Context->count[0] += static_cast<std::uint32_t>(_Length)) < _Length)
	{
		++(_Context->count[1]);
	}
#if SHA1_BITS == 1
	if(ofs)                 /* if not on a byte boundary    */
	{
		if(ofs + _Length < 8)   /* if no added bytes are needed */
		{
			w[pos] |= (*sp >> ofs);
		}
		else                /* otherwise and add bytes      */
		{
			unsigned char part = w[pos];

			while((int)(ofs + (_Length -= 8)) >= 0)
			{
				w[pos++] = part | (*sp >> ofs);
				part = *sp++ << (8 - ofs);
				if(pos == SHA1_BLOCK_SIZE)
				{
					bsw_32(w, SHA1_BLOCK_SIZE >> 2);
					Xanadu::sha1_compile(_Context);
					pos = 0;
				}
			}

			w[pos] = part;
		}
	}
	else    /* _Data is byte aligned */
#endif
	{
		std::uint32_t space = SHA1_BLOCK_SIZE - pos;

		while(_Length >= (space << 3))
		{
			x_posix_memcpy(w + pos, sp, space);
			bsw_32(w, SHA1_BLOCK_SIZE >> 2);
			Xanadu::sha1_compile(_Context);
			sp += space;
			_Length -= (space << 3);
			space = SHA1_BLOCK_SIZE;
			pos = 0;
		}
		x_posix_memcpy(w + pos, sp, (std::size_t)((_Length + 7 * SHA1_BITS) >> 3));
	}
}

// SHA1 final padding and digest calculation
_XCOREAPI_ void __xcall__ Xanadu::sha1_end(unsigned char _Hval[], XANADU_CORE_SHA1_CONTEXT _Context[1]) noexcept
{
	auto		i = (std::uint32_t)((_Context->count[0] >> 3) & SHA1_MASK);
	auto		m1 = static_cast<std::uint32_t>(0);

	/* put bytes in the buffer in an order in which references to   */
	/* 32-bit words will put bytes with lower addresses into the    */
	/* top of 32 bit words on BOTH big and little XEndian machines   */
	bsw_32(_Context->wbuf, (i + 3 + SHA1_BITS) >> 2);

	/* we now need to mask valid bytes and add the padding which is */
	/* a single 1 bit and as many zero bits as necessary. Note that */
	/* we can always add the first padding byte here because the    */
	/* buffer always has at least one empty slot                    */
	m1 = (unsigned char)0x80 >> (_Context->count[0] & 7);
	_Context->wbuf[i >> 2] &= ((0xffffff00 | (~m1 + 1)) << 8 * (~i & 3));
	_Context->wbuf[i >> 2] |= (m1 << 8 * (~i & 3));

	/* we need 9 or more empty positions, one for the padding byte  */
	/* (above) and eight for the length count. If there is not      */
	/* enough space, pad and empty the buffer                       */
	if(i > SHA1_BLOCK_SIZE - 9)
	{
		if(i < 60) _Context->wbuf[15] = 0;
		Xanadu::sha1_compile(_Context);
		i = 0;
	}
	else    /* compute a word index for the empty buffer positions  */
	{
		i = (i >> 2) + 1;
	}

	while(i < 14) /* and zero pad all but last two positions        */
	{
		_Context->wbuf[i++] = 0;
	}

	/* the following 32-bit length fields are assembled in the      */
	/* wrong byte order on little XEndian machines but this is       */
	/* corrected later since they are only ever used as 32-bit      */
	/* word values.                                                 */
	_Context->wbuf[14] = _Context->count[1];
	_Context->wbuf[15] = _Context->count[0];
	Xanadu::sha1_compile(_Context);

	/* extract the hash value as bytes in case the hash buffer is   */
	/* misaligned for 32-bit words                                  */
	for(i = 0; i < SHA1_DIGEST_SIZE; ++i)
	{
		_Hval[i] = ((_Context->hash[i >> 2] >> (8 * (~i & 3))) & 0xff);
	}
}

_XCOREAPI_ void __xcall__ Xanadu::sha1(unsigned char _Hval[], const unsigned char _Data[], unsigned long _Length) noexcept
{
	XANADU_CORE_SHA1_CONTEXT    _Context[1];
	Xanadu::sha1_begin(_Context);
	Xanadu::sha1_hash(_Data, _Length, _Context);
	Xanadu::sha1_end(_Hval, _Context);
}
