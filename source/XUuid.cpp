#include <xanadu-core/XUuid.h>



// constructor
XUuid::XUuid() noexcept
{
	this->_uuid_data_1 = 0;
	this->_uuid_data_2 = 0;
	this->_uuid_data_3 = 0;
	for(unsigned char & vItem : this->_uuid_data_4)
	{
		vItem = 0;
	}

	this->update();
}

// constructor
XUuid::XUuid(uint32_t _D1, uint16_t _D2, uint16_t _D3, uint8_t _D41, uint8_t _D42, uint8_t _D43, uint8_t _D44, uint8_t _D45, uint8_t _D46, uint8_t _D47, uint8_t _D48) noexcept
{
	this->_uuid_data_1 = _D1;
	this->_uuid_data_2 = _D2;
	this->_uuid_data_3 = _D3;
	this->_uuid_data_4[0] = _D41;
	this->_uuid_data_4[1] = _D42;
	this->_uuid_data_4[2] = _D43;
	this->_uuid_data_4[3] = _D44;
	this->_uuid_data_4[4] = _D45;
	this->_uuid_data_4[5] = _D46;
	this->_uuid_data_4[6] = _D47;
	this->_uuid_data_4[7] = _D48;
}

// constructor
XUuid::XUuid(const char* _UUID) noexcept
{
	this->_uuid_data_1 = 0;
	this->_uuid_data_2 = 0;
	this->_uuid_data_3 = 0;
	for(unsigned char & vItem : this->_uuid_data_4)
	{
		vItem = 0;
	}

	this->formatString(_UUID);
}

// constructor
XUuid::XUuid(const XString& _UUID) noexcept
{
	this->_uuid_data_1 = 0;
	this->_uuid_data_2 = 0;
	this->_uuid_data_3 = 0;
	for(unsigned char & vItem : this->_uuid_data_4)
	{
		vItem = 0;
	}

	this->formatString(_UUID);
}

// constructor
XUuid::XUuid(const XUuid& _Object) noexcept = default;

// constructor
XUuid::XUuid(XUuid&& _Object) noexcept = default;

// destructor
XUuid::~XUuid() noexcept = default;





// operator overload =
XUuid& XUuid::operator = (const XUuid& _Object) noexcept
{
	if(this != &_Object)
	{
		this->_uuid_data_1 = _Object._uuid_data_1;
		this->_uuid_data_2 = _Object._uuid_data_2;
		this->_uuid_data_3 = _Object._uuid_data_3;
		std::memcpy(this->_uuid_data_4, _Object._uuid_data_4, 8);
	}
	return *this;
}

// operator overload =
XUuid& XUuid::operator = (XUuid&& _Object) noexcept
{
	if(this != &_Object)
	{
		this->_uuid_data_1 = _Object._uuid_data_1;
		this->_uuid_data_2 = _Object._uuid_data_2;
		this->_uuid_data_3 = _Object._uuid_data_3;
		std::memcpy(this->_uuid_data_4, _Object._uuid_data_4, 8);
	}
	return *this;
}





// 从字符串格式化
bool XUuid::formatString(const XString& _UUID) noexcept
{
	if(_UUID.size() == 38 && _UUID.startsWith("{") && _UUID.endsWith("}"))
	{
		return XUuid::formatString(_UUID.substr(1, 36));
	}
	else if(_UUID.size() == 36)
	{
		for(XString::pos_type vIndex = 0; vIndex < _UUID.size(); ++vIndex)
		{
			if(vIndex == 8 || vIndex == 13 || vIndex == 18 || vIndex == 23)
			{
				if(_UUID[vIndex] != '-')
				{
					return false;
				}
			}
			else if(!std::isxdigit(_UUID[vIndex]))
			{
				return false;
			}
		}
		x_posix_sscanf(_UUID.data(), "%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
			       &(this->_uuid_data_1), &(this->_uuid_data_2), &(this->_uuid_data_3),
			       this->_uuid_data_4 + 0, this->_uuid_data_4 + 1, this->_uuid_data_4 + 2, this->_uuid_data_4 + 3,
			       this->_uuid_data_4 + 4, this->_uuid_data_4 + 5, this->_uuid_data_4 + 6, this->_uuid_data_4 + 7);
		return true;
	}
	else if(_UUID.size() == 32)
	{
		auto 		vUUID_36 = _UUID;
		vUUID_36.insert(8, '-');
		vUUID_36.insert(13, '-');
		vUUID_36.insert(18, '-');
		vUUID_36.insert(23, '-');
		return XUuid::formatString(vUUID_36);
	}

	return false;
}





// 更换一个新的UUID
void XUuid::update() noexcept
{
#if defined(XANADU_SYSTEM_WINDOWS)
	GUID		vUuid;
	::CoCreateGuid(&vUuid);

	this->_uuid_data_1 = vUuid.Data1;
	this->_uuid_data_2 = vUuid.Data2;
	this->_uuid_data_3 = vUuid.Data3;
	std::memcpy(this->_uuid_data_4, vUuid.Data4, 8);
#else
	std::mt19937	vRandom(std::random_device{}());
	std::uniform_int_distribution<uint16_t>		dist2(0U, 0xFFFFU);
	std::uniform_int_distribution<uint32_t>		dist4(0U, 0xFFFFFFFFU);
	std::uniform_int_distribution<uint64_t>		dist8(0ULL, 0xFFFFFFFFFFFFFFFFULL);

	uint64_t	vData4 = dist8(vRandom);

	this->_uuid_data_1 = dist4(vRandom);
	this->_uuid_data_2 = dist2(vRandom);
	this->_uuid_data_3 = dist2(vRandom);
	std::memcpy(this->_uuid_data_4, &vData4, 8);
#endif
}





// 创建一个UUID
XUuid XUuid::createUuid() noexcept
{
	return {};
}





// 从字符串格式化
XUuid XUuid::fromString(const XString& _UUID) noexcept
{
	return XUuid(_UUID);
}

// 转换为字符串
XString XUuid::toString() const noexcept
{
	return XUuid::toString(WithBraces);
}

// 转换为字符串
XString XUuid::toString(STRING_FORMAT _Format) const noexcept
{
	switch (_Format)
	{
		case WithBraces:
			return XString::format("{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}",
						  this->_uuid_data_1, this->_uuid_data_2, this->_uuid_data_3,
						  this->_uuid_data_4[0], this->_uuid_data_4[1], this->_uuid_data_4[2], this->_uuid_data_4[3],
						  this->_uuid_data_4[4], this->_uuid_data_4[5], this->_uuid_data_4[6], this->_uuid_data_4[7]);
		case WithoutBraces:
			return XString::format("%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
						  this->_uuid_data_1, this->_uuid_data_2, this->_uuid_data_3,
						  this->_uuid_data_4[0], this->_uuid_data_4[1], this->_uuid_data_4[2], this->_uuid_data_4[3],
						  this->_uuid_data_4[4], this->_uuid_data_4[5], this->_uuid_data_4[6], this->_uuid_data_4[7]);
		case HexDigitsOnly:
			return XString::format("%08X%04X%04X%02X%02X%02X%02X%02X%02X%02X%02X",
						  this->_uuid_data_1, this->_uuid_data_2, this->_uuid_data_3,
						  this->_uuid_data_4[0], this->_uuid_data_4[1], this->_uuid_data_4[2], this->_uuid_data_4[3],
						  this->_uuid_data_4[4], this->_uuid_data_4[5], this->_uuid_data_4[6], this->_uuid_data_4[7]);
		default:
			return {};
	}
}
