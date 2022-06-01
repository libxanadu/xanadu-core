#ifndef			_XANADU_CORE_BASE64_H_
#define			_XANADU_CORE_BASE64_H_

#include <xanadu-core/header.h>
#include <xanadu-core/XByteArray.h>

///  <summary>
///  Base64 codec
///  </summary>
class _XCOREAPI_ XBase64
{
public:
	// constructor
	XBase64() noexcept;

	// destructor
	virtual ~XBase64() noexcept;

public:
	// Encode the memory of the specified length as Base64
	static XByteArray encode(const void* _Memory, size_t _Length) noexcept;

	// Encode a byte array as Base64
	static XByteArray encode(const XByteArray& _Bytes) noexcept;

public:
	// Decode a segment of Base64 memory
	static XByteArray decode(const void* _Memory, size_t _Length) noexcept;

	// Decode a byte array of Base64
	static XByteArray decode(const XByteArray& _Bytes) noexcept;
};

#endif
