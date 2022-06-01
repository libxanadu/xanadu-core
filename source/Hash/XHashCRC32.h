#ifndef			_XANADU_CORE_HASH_CRC32_H_
#define			_XANADU_CORE_HASH_CRC32_H_

#include <xanadu-core/header.h>

// CRC32 context
typedef struct _XANADU_CORE_CRC32_CONTEXT
{
	std::uint32_t			hash;
}XANADU_CORE_CRC32_CONTEXT;

namespace Xanadu
{
	// CRC32 initialization
	_XCOREAPI_ void __xcall__ CRC32_Init(XANADU_CORE_CRC32_CONTEXT* _Context) noexcept;

	// CRC32 updates the data
	_XCOREAPI_ void __xcall__ CRC32_Update(XANADU_CORE_CRC32_CONTEXT* _Context, const void* _Data, std::uint64_t _Size) noexcept;

	// CRC32 retrieves the results
	_XCOREAPI_ void __xcall__ CRC32_Final(unsigned char* _Result, XANADU_CORE_CRC32_CONTEXT* _Context) noexcept;
};

#endif
