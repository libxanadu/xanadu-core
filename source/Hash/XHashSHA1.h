#ifndef			_XANADU_CORE_HASH_SHA1_H_
#define			_XANADU_CORE_HASH_SHA1_H_

#include <xanadu-core/header.h>

// define for bit or byte oriented SHA
#if 1
#  define SHA1_BITS		0   /* byte oriented */
#else
#  define SHA1_BITS		1   /* bit oriented  */
#endif

#define SHA1_BLOCK_SIZE		64
#define SHA1_DIGEST_SIZE	20

// type to hold the SHA256 context
typedef struct _XANADU_CORE_SHA1_CONTEXT
{
	std::uint32_t			count[2];
	std::uint32_t			hash[SHA1_DIGEST_SIZE >> 2];
	std::uint32_t			wbuf[SHA1_BLOCK_SIZE >> 2];
}XANADU_CORE_SHA1_CONTEXT;

/* Note that these prototypes are the same for both bit and */
/* byte oriented implementations. However the length fields */
/* are in bytes or bits as appropriate for the version used */
/* and bit sequences are input as arrays of bytes in which  */
/* bit sequences run from the most to the least significant */
/* end of each byte. The value 'len' in sha1_hash for the   */
/* byte oriented version of SHA1 is limited to 2^29 bytes,  */
/* but multiple calls will handle longer data blocks.       */

namespace Xanadu
{
	_XCOREAPI_ void __xcall__ sha1_compile(XANADU_CORE_SHA1_CONTEXT _Context[1]) noexcept;

	_XCOREAPI_ void __xcall__ sha1_begin(XANADU_CORE_SHA1_CONTEXT _Context[1]) noexcept;

	_XCOREAPI_ void __xcall__ sha1_hash(const unsigned char _Data[], std::uint64_t _Length, XANADU_CORE_SHA1_CONTEXT _Context[1]) noexcept;

	// SHA1 final padding and digest calculation
	_XCOREAPI_ void __xcall__ sha1_end(unsigned char _Hval[], XANADU_CORE_SHA1_CONTEXT _Context[1]) noexcept;

	_XCOREAPI_ void __xcall__ sha1(unsigned char _Hval[], const unsigned char _Data[], unsigned long _Length) noexcept;
};

#endif // _XANADU_CORE_HASH_SHA1_H_
