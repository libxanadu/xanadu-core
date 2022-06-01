#include <xanadu-core/XBase64.h>

// Check for Base64 characters
bool XanaduByteArrayIsBase64(unsigned char _Char)
{
	return (isalnum(_Char) || (_Char == '+') || (_Char == '/'));
}


// constructor
XBase64::XBase64() noexcept = default;

// destructor
XBase64::~XBase64() noexcept = default;





// Encode the memory of the specified length as Base64
XByteArray XBase64::encode(const void* _Memory, size_t _Length) noexcept
{
	if(nullptr == _Memory || 0 == _Length)
	{
		return {};
	}

	const char	vAlphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	auto		vByteArray = static_cast<const unsigned char*>(_Memory);
	auto		vPadchar = static_cast<const char>('=');
	auto		vPadLength = static_cast<int>(0);
	auto		vIndex = static_cast<size_t>(0);
	auto		vEncode = XByteArray((_Length + 2) / 3 * 4, '\0');
	char*		vBuffer = vEncode.data();
	while(vIndex < _Length)
	{
		// encode 3 bytes at a time
		auto		vChunk = static_cast<int>(0);
		vChunk |= int((unsigned char)(vByteArray[vIndex++])) << 16;
		if(vIndex == _Length)
		{
			vPadLength = 2;
		}
		else
		{
			vChunk |= int((unsigned char)(vByteArray[vIndex++])) << 8;
			if(vIndex == _Length)
			{
				vPadLength = 1;
			}
			else
			{
				vChunk |= int((unsigned char)(vByteArray[vIndex++]));
			}
		}

		auto		vValue1 = (vChunk & 0x00FC0000) >> 18;
		auto		vValue2 = (vChunk & 0x0003F000) >> 12;
		auto		vValue3 = (vChunk & 0x00000FC0) >> 6;
		auto		vValue4 = (vChunk & 0x0000003F);
		*vBuffer++ = vAlphabet[vValue1];
		*vBuffer++ = vAlphabet[vValue2];

		if(vPadLength > 1)
		{
			*vBuffer++ = vPadchar;
		}
		else
		{
			*vBuffer++ = vAlphabet[vValue3];
		}
		if(vPadLength > 0)
		{
			*vBuffer++ = vPadchar;
		}
		else
		{
			*vBuffer++ = vAlphabet[vValue4];
		}
	}
	vEncode.truncate(vBuffer - vEncode.data());
	return vEncode;
}

// Encode a byte array as Base64
XByteArray XBase64::encode(const XByteArray& _Bytes) noexcept
{
	return XBase64::encode(_Bytes.data(), _Bytes.size());
}





// Decode a segment of Base64 memory
XByteArray XBase64::decode(const void* _Memory, size_t _Length) noexcept
{
	if(nullptr == _Memory || 0 == _Length || (_Length % 4))
	{
		return {};
	}

	auto		vBase64 = static_cast<const unsigned char*>(_Memory);
	auto		vBuffer = static_cast<unsigned int>(0);
	auto		vBits = static_cast<int>(0);
	auto		vOffset = static_cast<int>(0);
	auto		vBytes = XByteArray((_Length * 3) / 4, '\0');

	for(size_t vIndex = 0; vIndex < _Length; ++vIndex)
	{
		auto		vChar = static_cast<int>(vBase64[vIndex]);
		auto		vValue = static_cast<int>(0);

		if(vChar >= 'A' && vChar <= 'Z')
		{
			vValue = vChar - 'A';
		}
		else if(vChar >= 'a' && vChar <= 'z')
		{
			vValue = vChar - 'a' + 26;
		}
		else if(vChar >= '0' && vChar <= '9')
		{
			vValue = vChar - '0' + 52;
		}
		else if(vChar == '+')
		{
			vValue = 62;
		}
		else if(vChar == '/')
		{
			vValue = 63;
		}
		else
		{
			vValue = -1;
		}

		if(vValue != -1)
		{
			vBuffer = (vBuffer << 6) | vValue;
			vBits += 6;
			if(vBits >= 8)
			{
				vBits -= 8;
				vBytes[vOffset++] = (char)(vBuffer >> vBits);
				vBuffer &= (1 << vBits) - 1;
			}
		}
	}

	vBytes.truncate(vOffset);
	return vBytes;
}

// Decode a byte array of Base64
XByteArray XBase64::decode(const XByteArray& _Bytes) noexcept
{
	return XBase64::decode(_Bytes.data(), _Bytes.size());
}
