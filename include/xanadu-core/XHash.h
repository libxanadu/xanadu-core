#ifndef			_XANADU_CORE_HASH_H_
#define			_XANADU_CORE_HASH_H_

#include <xanadu-core/header.h>
#include <xanadu-core/XByteArray.h>
#include <xanadu-core/XString.h>

class XHashPrivate;

///  <summary>
/// A public class that evaluates the hash value.
/// Contains common algorithm such as MD5, SHA1, SHA256.
///  </summary>
class _XCOREAPI_ XHash
{
public:
	// Enumeration of common algorithms
	enum Algorithm
	{
		MD5 = 0,
		SHA1,
		CRC32,
	};

private:
	// Private structures
	XHashPrivate*				_Info;

public:
	// Structure
	XHash(Algorithm _Algorithm) noexcept;

	// destructor
	virtual ~XHash() noexcept;

public:
	// Empty data
	virtual void reset() noexcept;

	// Add Data
	virtual void append(const void* _Data, std::uint64_t _Length) noexcept;

	// Add Data
	virtual void append(const XByteArray& _Bytes) noexcept;

	// View the results
	virtual XByteArray result() const noexcept;

public:
	// Static method: Calculates the hash value
	static XByteArray hash(const void* _Buffer, std::uint64_t _Length, Algorithm _Algorithm) noexcept;

	// Static method: Calculates the hash value
	static XByteArray hash(const XByteArray& _Bytes, Algorithm _Algorithm) noexcept;

	// Static method: Calculates the hash value
	static XByteArray hash(const XString& _File, Algorithm _Algorithm) noexcept;

	// Static method: Gets the result length of the specified algorithm
	static std::size_t hashLength(Algorithm _Algorithm) noexcept;
};

#endif
