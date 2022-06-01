
#ifndef			_XANADU_CORE_HASH_SHA2_H_
#define			_XANADU_CORE_HASH_SHA2_H_

#include <xanadu-core/header.h>

/* define for bit or byte oriented SHA   */
#if 1
#  define SHA2_BITS 0   /* byte oriented */
#else
#  define SHA2_BITS 1   /* bit oriented  */
#endif

/* define the hash functions that you need  */
/* define for 64-bit SHA384 and SHA512      */
#define SHA_64BIT
#define SHA_2   /* for dynamic hash length  */
#define SHA_224
#define SHA_256
#ifdef SHA_64BIT
#  define SHA_384
#  define SHA_512
#  define NEED_uint64_t
#endif

#define SHA2_MAX_DIGEST_SIZE   64
#define SHA2_MAX_BLOCK_SIZE   128

/* Note that the following function prototypes are the same */
/* for both the bit and byte oriented implementations.  But */
/* the length fields are in bytes or bits as is appropriate */
/* for the version used.  Bit sequences are arrays of bytes */
/* in which bit sequence indexes increase from the most to  */
/* the least significant end of each byte.  The value 'len' */
/* in sha<nnn>_hash for the byte oriented versions of SHA2  */
/* is limited to 2^29 bytes, but multiple calls will handle */
/* longer data blocks.                                      */

#define SHA224_DIGEST_SIZE  28
#define SHA224_BLOCK_SIZE   64

#define SHA256_DIGEST_SIZE  32
#define SHA256_BLOCK_SIZE   64

/* type to hold the SHA256 (and SHA224) context */

typedef struct _XANADU_CORE_SHA256_CONTEXT
{
	std::uint32_t			count[2];
	std::uint32_t			hash[SHA256_DIGEST_SIZE >> 2];
	std::uint32_t			wbuf[SHA256_BLOCK_SIZE >> 2];
}XANADU_CORE_SHA256_CONTEXT;

typedef XANADU_CORE_SHA256_CONTEXT  sha224_ctx;

_XCOREAPI_ void __xcall__ sha256_compile(XANADU_CORE_SHA256_CONTEXT ctx[1]);

_XCOREAPI_ void __xcall__ sha224_begin(sha224_ctx ctx[1]);
#define sha224_hash sha256_hash
_XCOREAPI_ void __xcall__ sha224_end(unsigned char hval[], sha224_ctx ctx[1]);
_XCOREAPI_ void __xcall__ sha224(unsigned char hval[], const unsigned char data[], unsigned long len);

_XCOREAPI_ void __xcall__ sha256_begin(XANADU_CORE_SHA256_CONTEXT ctx[1]);
_XCOREAPI_ void __xcall__ sha256_hash(const unsigned char data[], unsigned long len, XANADU_CORE_SHA256_CONTEXT ctx[1]);
_XCOREAPI_ void __xcall__ sha256_end(unsigned char hval[], XANADU_CORE_SHA256_CONTEXT ctx[1]);
_XCOREAPI_ void __xcall__ sha256(unsigned char hval[], const unsigned char data[], unsigned long len);

#ifndef SHA_64BIT

typedef struct _XANADU_CORE_SHA2_CONTEXT
{
	union
	{
		XANADU_CORE_SHA256_CONTEXT  ctx256[1];
	} uu[1];
	std::uint32_t			sha2_len;
}XANADU_CORE_SHA2_CONTEXT;

#else

#define SHA384_DIGEST_SIZE  48
#define SHA384_BLOCK_SIZE  128

#define SHA512_DIGEST_SIZE  64
#define SHA512_BLOCK_SIZE  128

#define SHA512_128_DIGEST_SIZE 16
#define SHA512_128_BLOCK_SIZE  SHA512_BLOCK_SIZE

#define SHA512_192_DIGEST_SIZE 24
#define SHA512_192_BLOCK_SIZE  SHA512_BLOCK_SIZE

#define SHA512_224_DIGEST_SIZE 28
#define SHA512_224_BLOCK_SIZE  SHA512_BLOCK_SIZE

#define SHA512_256_DIGEST_SIZE 32
#define SHA512_256_BLOCK_SIZE  SHA512_BLOCK_SIZE

/* type to hold the SHA384 (and SHA512) context */

typedef struct _XANADU_CORE_SHA512_CONTEXT
{
	std::uint64_t			count[2];
	std::uint64_t			hash[SHA512_DIGEST_SIZE >> 3];
	std::uint64_t			wbuf[SHA512_BLOCK_SIZE >> 3];
}XANADU_CORE_SHA512_CONTEXT;

typedef XANADU_CORE_SHA512_CONTEXT  XANADU_CORE_SHA384_CONTEXT;

typedef struct _XANADU_CORE_SHA2_CONTEXT
{
	union
	{
		XANADU_CORE_SHA256_CONTEXT	ctx256[1];
		XANADU_CORE_SHA512_CONTEXT	ctx512[1];
	} uu[1];
	std::uint32_t			sha2_len;
} XANADU_CORE_SHA2_CONTEXT;

_XCOREAPI_ void __xcall__ sha512_compile(XANADU_CORE_SHA512_CONTEXT ctx[1]);

_XCOREAPI_ void __xcall__ sha384_begin(XANADU_CORE_SHA384_CONTEXT ctx[1]);
#define sha384_hash sha512_hash
_XCOREAPI_ void __xcall__ sha384_end(unsigned char hval[], XANADU_CORE_SHA384_CONTEXT ctx[1]);
_XCOREAPI_ void __xcall__ sha384(unsigned char hval[], const unsigned char data[], unsigned long len);

_XCOREAPI_ void __xcall__ sha512_begin(XANADU_CORE_SHA512_CONTEXT ctx[1]);
_XCOREAPI_ void __xcall__ sha512_hash(const unsigned char data[], unsigned long len, XANADU_CORE_SHA512_CONTEXT ctx[1]);
_XCOREAPI_ void __xcall__ sha512_end(unsigned char hval[], XANADU_CORE_SHA512_CONTEXT ctx[1]);
_XCOREAPI_ void __xcall__ sha512(unsigned char hval[], const unsigned char data[], unsigned long len);

_XCOREAPI_ void __xcall__ sha512_256_begin(XANADU_CORE_SHA512_CONTEXT ctx[1]);
#define sha512_256_hash sha512_hash
_XCOREAPI_ void __xcall__ sha512_256_end(unsigned char hval[], XANADU_CORE_SHA512_CONTEXT ctx[1]);
_XCOREAPI_ void __xcall__ sha512_256(unsigned char hval[], const unsigned char data[], unsigned long len);

_XCOREAPI_ void __xcall__ sha512_224_begin(XANADU_CORE_SHA512_CONTEXT ctx[1]);
#define sha512_224_hash sha512_hash
_XCOREAPI_ void __xcall__ sha512_224_end(unsigned char hval[], XANADU_CORE_SHA512_CONTEXT ctx[1]);
_XCOREAPI_ void __xcall__ sha512_224(unsigned char hval[], const unsigned char data[], unsigned long len);

_XCOREAPI_ void __xcall__ sha512_192_begin(XANADU_CORE_SHA512_CONTEXT ctx[1]);
#define sha512_192_hash sha512_hash
_XCOREAPI_ void __xcall__ sha512_192_end(unsigned char hval[], XANADU_CORE_SHA512_CONTEXT ctx[1]);
_XCOREAPI_ void __xcall__ sha512_192(unsigned char hval[], const unsigned char data[], unsigned long len);

_XCOREAPI_ void __xcall__ sha512_128_begin(XANADU_CORE_SHA512_CONTEXT ctx[1]);
#define sha512_128_hash sha512_hash
_XCOREAPI_ void __xcall__ sha512_128_end(unsigned char hval[], XANADU_CORE_SHA512_CONTEXT ctx[1]);
_XCOREAPI_ void __xcall__ sha512_128(unsigned char hval[], const unsigned char data[], unsigned long len);

_XCOREAPI_ int __xcall__  sha2_begin(unsigned long size, XANADU_CORE_SHA2_CONTEXT ctx[1]);
_XCOREAPI_ void __xcall__ sha2_hash(const unsigned char data[], unsigned long len, XANADU_CORE_SHA2_CONTEXT ctx[1]);
_XCOREAPI_ void __xcall__ sha2_end(unsigned char hval[], XANADU_CORE_SHA2_CONTEXT ctx[1]);
_XCOREAPI_ int __xcall__  sha2(unsigned char hval[], unsigned long size, const unsigned char data[], unsigned long len);

#endif // SHA_64BIT

#endif // _XANADU_CORE_HASH_SHA2_H_
