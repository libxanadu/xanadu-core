#include <xanadu-core/XHash.h>
#include "Hash/XHashMD5.h"
#include "Hash/XHashSHA1.h"
#include "Hash/XHashSHA2.h"
#include "Hash/XHashCRC32.h"


class XHashPrivate
{
public:
	XHash::Algorithm			_Algorithm;
	union
	{
		XANADU_CORE_MD5_CONTEXT		_MD5Context;
		XANADU_CORE_SHA1_CONTEXT	_SHA1Context;
		XANADU_CORE_CRC32_CONTEXT	_CRC32Context;
	};
	XByteArray				_Result;
};

// Structure
XHash::XHash(Algorithm _Algorithm) noexcept
{
	this->_Info = new(std::nothrow) XHashPrivate();
	this->_Info->_Algorithm = _Algorithm;
	this->reset();
}

// destructor
XHash::~XHash() noexcept
{
	XANADU_DELETE_PTR(this->_Info);
}




// Empty data
void XHash::reset() noexcept
{
	switch (this->_Info->_Algorithm)
	{
		case MD5:
			Xanadu::MD5_Init(&(this->_Info->_MD5Context));
			break;
		case SHA1:
			Xanadu::sha1_begin(&(this->_Info->_SHA1Context));
			break;
		case CRC32:
			Xanadu::CRC32_Init(&(this->_Info->_CRC32Context));
			break;
	}
}

// Add Data
void XHash::append(const void* _Data, std::uint64_t _Length) noexcept
{
	switch (this->_Info->_Algorithm)
	{
		case MD5:
			Xanadu::MD5_Update(&(this->_Info->_MD5Context), _Data, _Length);
			break;
		case SHA1:
			Xanadu::sha1_hash((const unsigned char*)_Data, _Length, &(this->_Info->_SHA1Context));
			break;
		case CRC32:
			Xanadu::CRC32_Update(&(this->_Info->_CRC32Context), _Data, _Length);
			break;
	}
}

// Add Data
void XHash::append(const XByteArray& _Bytes) noexcept
{
	XHash::append(_Bytes.data(), _Bytes.size());
}

// View the results
XByteArray XHash::result() const noexcept
{
	if (this->_Info->_Result.empty())
	{
		unsigned char 		vResult[128] = {0};
		switch (this->_Info->_Algorithm)
		{
			case MD5:
				Xanadu::MD5_Final(vResult, &(this->_Info->_MD5Context));
				break;
			case SHA1:
				Xanadu::sha1_end(vResult, &(this->_Info->_SHA1Context));
				break;
			case CRC32:
				Xanadu::CRC32_Final(vResult, &(this->_Info->_CRC32Context));
				break;
		}
		this->_Info->_Result = XByteArray((const char*)vResult, XHash::hashLength(this->_Info->_Algorithm));
	}
	return this->_Info->_Result;
}






// Static method: Calculates the hash value
XByteArray XHash::hash(const void* _Buffer, std::uint64_t _Length, Algorithm _Algorithm) noexcept
{
	auto		vClass = XHash(_Algorithm);
	vClass.reset();
	vClass.append(_Buffer, _Length);
	return vClass.result();
}

// Static method: Calculates the hash value
XByteArray XHash::hash(const XByteArray& _Bytes, Algorithm _Algorithm) noexcept
{
	return XHash::hash(_Bytes.data(), _Bytes.size(), _Algorithm);
}

// Static method: Calculates the hash value
XByteArray XHash::hash(const XString& _File, Algorithm _Algorithm) noexcept
{
	auto		vClass = XHash(_Algorithm);
	auto		vResult = XByteArray();
#if defined(XANADU_SYSTEM_WINDOWS)
	auto		vHandle = x_posix_wfopen(_File.toWString().data(), L"rb");
#else
	auto		vHandle = x_posix_fopen(_File.data(), "rb");
#endif
	if (vHandle)
	{
		auto		vMemory = new(std::nothrow) char[XANADU_SIZE_MB];
		if(vMemory)
		{
			vClass.reset();
			while(!x_posix_feof(vHandle))
			{
				auto		vSync = x_posix_fread(vMemory, 1, XANADU_SIZE_MB, vHandle);
				if(vSync <= 0)
				{
					break;
				}
				vClass.append(vMemory, vSync);
			};
			vResult = vClass.result();
			XANADU_DELETE_ARR(vMemory);
		}
		x_posix_fclose(vHandle);
	}
	return vResult;
}

// Static method: Gets the result length of the specified algorithm
std::size_t XHash::hashLength(Algorithm _Algorithm) noexcept
{
	switch (_Algorithm)
	{
		case MD5:
			return 16;
		case SHA1:
			return 20;
		case CRC32:
			return 4;
		default:
			return 0;
	}
}
