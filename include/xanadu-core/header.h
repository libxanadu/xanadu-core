#ifndef			_XANADU_CORE_HEADER_H_
#define			_XANADU_CORE_HEADER_H_

#include <xanadu-posix/xanadu.h>
#include <xanadu-core/sys/types.h>
#include <memory>
#include <list>
#include <vector>
#include <map>
#include <string>
#include <stdexcept>
#include <istream>
#include <ostream>
#include <functional>
#include <mutex>


// xanadu export declaration used by the project
#if defined(XANADU_CORE_BUILD_STATIC)
#define			_XCOREAPI_
#else
#if defined(XANADU_CORE_BUILD_LOCAL)
#define			_XCOREAPI_					XANADU_COMPILER_API_EXP
#else
#define			_XCOREAPI_					XANADU_COMPILER_API_IMP
#endif
#endif


/// namespace xanadu
namespace xanadu
{
	// Case Sensitivity enum
	typedef enum CaseSensitivity
	{
		CaseInsensitive,						// no
		CaseSensitive,							// yes
	}CaseSensitivity;
}


/// namespace xanadu 类型定义
namespace xanadu
{
#if defined(XANADU_PLATFORM_BIT_32)
	using	ssize_t			= int;
	using	size_t			= unsigned int;
	using	ptrdiff_t		= int;
	using	intptr_t		= int;
#else
	using	ssize_t			= long long;
	using	size_t			= unsigned long long;
	using	ptrdiff_t		= long long;
	using	intptr_t		= long long;
#endif

	using	int8_t			= char;
	using	uint8_t			= unsigned char;
	using	int16_t			= short;
	using	uint16_t		= unsigned short;
	using	int32_t			= int;
	using	uint32_t		= unsigned int;
	using	int64_t			= long long;
	using	uint64_t		= unsigned long long;

	using	size_type		= xanadu::size_t;
	using	pos_type		= xanadu::size_t;
	using	difference_type		= ptrdiff_t;
}


#endif
