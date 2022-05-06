#include <xanadu-core/string.h> // NOLINT(modernize-deprecated-headers)
#include <cstdarg>



// constructor
xanadu::string::string() noexcept = default;

// constructor
xanadu::string::string(size_type _Length, _Elem _Char) noexcept : _Allocator(_Length, _Char)
{
}

// constructor
xanadu::string::string(const _Elem* _Memory) noexcept : _Allocator(_Memory, x_posix_strlen(_Memory))
{
}

// constructor
xanadu::string::string(const _Elem* _Memory, size_type _Length) noexcept : _Allocator(_Memory, _Length)
{
}

// constructor
xanadu::string::string(const std::string& _StdStr) noexcept : _Allocator(_StdStr.data(), _StdStr.size())
{
}

// constructor
xanadu::string::string(const xanadu::string& _String) noexcept = default;

// constructor
xanadu::string::string(xanadu::string&& _String) noexcept = default;

// destructor
xanadu::string::~string() noexcept = default;





// operator overload =
xanadu::string& xanadu::string::operator = (const _Elem* _Memory) noexcept
{
	if(this->resize(x_posix_strlen(_Memory)))
	{
		x_posix_memcpy(this->data(), _Memory, this->size());
	}
	return *this;
}

// operator overload =
xanadu::string& xanadu::string::operator = (const std::string& _String) noexcept
{
	if(this->resize(_String.size()))
	{
		x_posix_memcpy(this->data(), _String.data(), this->size());
	}
	return *this;
}

// operator overload =
xanadu::string& xanadu::string::operator = (const xanadu::string& _String) noexcept
{
	if(this != &_String)
	{
		this->_Allocator = _String._Allocator;
	}
	return *this;
}

// operator overload =
xanadu::string& xanadu::string::operator = (xanadu::string&& _String) noexcept
{
	if(this != &_String)
	{
		this->_Allocator = _String._Allocator;
	}
	return *this;
}





// operators overload +=
xanadu::string& xanadu::string::operator += (_Elem _Char) noexcept
{
	_Elem		vBytes[2] = {_Char, '\0'};
	return this->append(vBytes, 1);
}

// operators overload +=
xanadu::string& xanadu::string::operator += (const _Elem* _String) noexcept
{
	return this->append(_String, x_posix_strlen(_String));
}

// operators overload +=
xanadu::string& xanadu::string::operator += (const std::string& _String) noexcept
{
	return this->append(_String.data(), _String.size());
}

// operators overload +=
xanadu::string& xanadu::string::operator += (const xanadu::string& _String) noexcept
{
	return this->append(_String.data(), _String.size());
}





// operators overload +
xanadu::string xanadu::string::operator + (_Elem _Char) const noexcept
{
	auto		vTemp = *this;
	vTemp += _Char;
	return vTemp;
}

// operators overload +
xanadu::string xanadu::string::operator + (const _Elem* _String) const noexcept
{
	auto		vTemp = *this;
	vTemp += _String;
	return vTemp;
}

// operators overload +
xanadu::string xanadu::string::operator + (const std::string& _String) const noexcept
{
	auto		vTemp = *this;
	vTemp += _String;
	return vTemp;
}

// operators overload +
xanadu::string xanadu::string::operator + (const xanadu::string& _String) const noexcept
{
	auto		vTemp = *this;
	vTemp += _String;
	return vTemp;
}





// operators overload ==
bool xanadu::string::operator == (_Elem _Char) const noexcept
{
	_Elem		vBytes[2] = {_Char, '\0'};
	return this->compare(vBytes, 1, xanadu::CaseSensitive) == 0;
}

// operators overload ==
bool xanadu::string::operator == (const _Elem* _String) const noexcept
{
	return this->compare(_String, x_posix_strlen(_String), xanadu::CaseSensitive) == 0;
}

// operators overload ==
bool xanadu::string::operator == (const xanadu::string& _String) const noexcept
{
	return this->compare(_String.data(), _String.size(), xanadu::CaseSensitive) == 0;
}

// operators overload !=
bool xanadu::string::operator != (_Elem _Char) const noexcept
{
	_Elem		vBytes[2] = {_Char, '\0'};
	return this->compare(vBytes, 1, xanadu::CaseSensitive) != 0;
}

// operators overload !=
bool xanadu::string::operator != (const _Elem* _String) const noexcept
{
	return this->compare(_String, x_posix_strlen(_String), xanadu::CaseSensitive) != 0;
}

// operators overload !=
bool xanadu::string::operator != (const xanadu::string& _String) const noexcept
{
	return this->compare(_String.data(), _String.size(), xanadu::CaseSensitive) != 0;
}

// operators overload <
bool xanadu::string::operator < (_Elem _Char) const noexcept
{
	_Elem		vBytes[2] = {_Char, '\0'};
	return this->compare(vBytes, 1, xanadu::CaseSensitive) < 0;
}

// operators overload <
bool xanadu::string::operator < (const _Elem* _String) const noexcept
{
	return this->compare(_String, x_posix_strlen(_String), xanadu::CaseSensitive) < 0;
}

// operators overload <
bool xanadu::string::operator < (const xanadu::string& _String) const noexcept
{
	return this->compare(_String.data(), _String.size(), xanadu::CaseSensitive) < 0;
}

// operators overload >
bool xanadu::string::operator > (_Elem _Char) const noexcept
{
	_Elem		vBytes[2] = {_Char, '\0'};
	return this->compare(vBytes, 1, xanadu::CaseSensitive) > 0;
}

// operators overload >
bool xanadu::string::operator > (const _Elem* _String) const noexcept
{
	return this->compare(_String, x_posix_strlen(_String), xanadu::CaseSensitive) > 0;
}

// operators overload >
bool xanadu::string::operator > (const xanadu::string& _String) const noexcept
{
	return this->compare(_String.data(), _String.size(), xanadu::CaseSensitive) > 0;
}

// operators overload <=
bool xanadu::string::operator <= (_Elem _Char) const noexcept
{
	_Elem		vBytes[2] = {_Char, '\0'};
	return this->compare(vBytes, 1, xanadu::CaseSensitive) <= 0;
}

// operators overload <=
bool xanadu::string::operator <= (const _Elem* _String) const noexcept
{
	return this->compare(_String, x_posix_strlen(_String), xanadu::CaseSensitive) <= 0;
}

// operators overload <=
bool xanadu::string::operator <= (const xanadu::string& _String) const noexcept
{
	return this->compare(_String.data(), _String.size(), xanadu::CaseSensitive) <= 0;
}

// operators overload >=
bool xanadu::string::operator >= (_Elem _Char) const noexcept
{
	_Elem		vBytes[2] = {_Char, '\0'};
	return this->compare(vBytes, 1, xanadu::CaseSensitive) >= 0;
}

// operators overload >=
bool xanadu::string::operator >= (const _Elem* _String) const noexcept
{
	return this->compare(_String, x_posix_strlen(_String), xanadu::CaseSensitive) >= 0;
}

// operators overload >=
bool xanadu::string::operator >= (const xanadu::string& _String) const noexcept
{
	return this->compare(_String.data(), _String.size(), xanadu::CaseSensitive) >= 0;
}





// [opt] operator overload []
xanadu::string::_Elem& xanadu::string::operator [] (pos_type _Index)
{
	return this->_Allocator[_Index];
}

// [opt] operator overload []
xanadu::string::_Elem xanadu::string::operator [] (pos_type _Index) const
{
	return this->_Allocator[_Index];
}





// [opt] clear
void xanadu::string::clear() noexcept
{
	this->_Allocator.clear();
}

// [opt] resize
bool xanadu::string::resize(size_type _Length) noexcept
{
	return this->_Allocator.resize(_Length);
}

// [opt] reverse
bool xanadu::string::reverse(size_type _Length) noexcept
{
	return this->_Allocator.reverse(_Length);
}





// [get] exist
bool xanadu::string::exist() const noexcept
{
	return this->_Allocator.exist();
}

// [get] empty
bool xanadu::string::empty() const noexcept
{
	return this->_Allocator.empty();
}

// [get] data
xanadu::string::_Elem* xanadu::string::data() noexcept
{
	return static_cast<xanadu::string::_Elem*>(this->_Allocator.data());
}

// [get] data
const xanadu::string::_Elem* xanadu::string::data() const noexcept
{
	return static_cast<const xanadu::string::_Elem*>(this->_Allocator.data());
}

// [get] size
xanadu::string::size_type xanadu::string::size() const noexcept
{
	return this->_Allocator.size();
}

// [get] capacity
xanadu::string::size_type xanadu::string::capacity() const noexcept
{
	return this->_Allocator.capacity();
}

// [get] surplus
xanadu::string::size_type xanadu::string::surplus() const noexcept
{
	return this->_Allocator.surplus();
}

// [get] max_size
xanadu::string::size_type xanadu::string::max_size() const noexcept
{
	return this->_Allocator.max_size();
}





// Extracting substrings from strings
xanadu::string xanadu::string::substr(pos_type _Pos) const noexcept
{
	return this->substr(_Pos, xanadu::string::npos);
}

// Extracting substrings from strings
xanadu::string xanadu::string::substr(pos_type _Pos, size_type _Length) const noexcept
{
	if(_Pos < this->size())
	{
		if(_Length == xanadu::string::npos)
		{
			return {this->data() + _Pos, this->size() - _Pos};
		}
		else
		{
			return {this->data() + _Pos, this->size() - _Pos > _Length ? _Length : this->size() - _Pos};
		}
	}
	else
	{
		return {};
	}
}

// Gets the substring to the left of the source string
xanadu::string xanadu::string::left(pos_type _Pos) const noexcept
{
	return this->substr(0, _Pos);
}

// Gets the substring to the right of the source string
xanadu::string xanadu::string::right(pos_type _Pos) const noexcept
{
	return this->substr(this->size() - _Pos, xanadu::string::npos);
}





// [mid] Gets the substring in the middle of the source string
xanadu::string xanadu::string::mid(pos_type _Pos) const noexcept
{
	return this->mid(_Pos, xanadu::string::npos);
}

// [mid] Gets the substring in the middle of the source string
xanadu::string xanadu::string::mid(pos_type _Pos, size_type _Size) const noexcept
{
	return this->substr(_Pos, _Size);
}

// [mid] Gets the substring in the middle of the source string
xanadu::string xanadu::string::mid(const _Elem* _Left, const _Elem* _Right) const noexcept
{
	return this->mid(_Left, x_posix_strlen(_Left), _Right, x_posix_strlen(_Right), xanadu::CaseSensitive);
}

// [mid] Gets the substring in the middle of the source string
xanadu::string xanadu::string::mid(const _Elem* _Left, const _Elem* _Right, xanadu::CaseSensitivity _XCS) const noexcept
{
	return this->mid(_Left, x_posix_strlen(_Left), _Right, x_posix_strlen(_Right), _XCS);
}

// [mid] Gets the substring in the middle of the source string
xanadu::string xanadu::string::mid(const _Elem* _Left, size_type _LengthL, const _Elem* _Right, size_type _LengthR) const noexcept
{
	return this->mid(_Left, _LengthL, _Right, _LengthR, xanadu::CaseSensitive);
}

// [mid] Gets the substring in the middle of the source string
xanadu::string xanadu::string::mid(const _Elem* _Left, size_type _LengthL, const _Elem* _Right, size_type _LengthR, xanadu::CaseSensitivity _XCS) const noexcept
{
	pos_type 	vPosL = xanadu::string::npos;
	pos_type 	vPosR = xanadu::string::npos;

	if(_Left == nullptr || _Right == nullptr || _LengthL == 0 || _LengthR == 0)
	{
		return {};
	}

	vPosL = this->find(_Left, _LengthL, 0, _XCS);
	if(xanadu::string::npos != vPosL)
	{
		vPosL += _LengthL;
		vPosR = this->find(_Right, _LengthR, vPosL, _XCS);
		if(xanadu::string::npos != vPosR)
		{
			return substr(vPosL, vPosR - vPosL);
		}
	}
	return {};
}

// [mid] Gets the substring in the middle of the source string
xanadu::string xanadu::string::mid(const _Elem* _Left, const xanadu::string& _Right) const noexcept
{
	return this->mid(_Left, x_posix_strlen(_Left), _Right.data(), _Right.size(), xanadu::CaseSensitive);
}

// [mid] Gets the substring in the middle of the source string
xanadu::string xanadu::string::mid(const _Elem* _Left, const xanadu::string& _Right, xanadu::CaseSensitivity _XCS) const noexcept
{
	return this->mid(_Left, x_posix_strlen(_Left), _Right.data(), _Right.size(), _XCS);
}

// [mid] Gets the substring in the middle of the source string
xanadu::string xanadu::string::mid(const xanadu::string& _Left, const _Elem* _Right) const noexcept
{
	return this->mid(_Left.data(), _Left.size(), _Right, x_posix_strlen(_Right), xanadu::CaseSensitive);
}

// [mid] Gets the substring in the middle of the source string
xanadu::string xanadu::string::mid(const xanadu::string& _Left, const _Elem* _Right, xanadu::CaseSensitivity _XCS) const noexcept
{
	return this->mid(_Left.data(), _Left.size(), _Right, x_posix_strlen(_Right), _XCS);
}

// [mid] Gets the substring in the middle of the source string
xanadu::string xanadu::string::mid(const xanadu::string& _Left, const xanadu::string& _Right) const noexcept
{
	return this->mid(_Left.data(), _Left.size(), _Right.data(), _Right.size(), xanadu::CaseSensitive);
}

// [mid] Gets the substring in the middle of the source string
xanadu::string xanadu::string::mid(const xanadu::string& _Left, const xanadu::string& _Right, xanadu::CaseSensitivity _XCS) const noexcept
{
	return this->mid(_Left.data(), _Left.size(), _Right.data(), _Right.size(), _XCS);
}





// Detects whether the string starts with the specified prefix
bool xanadu::string::startsWith(_Elem _Char) const noexcept
{
	_Elem		vBytes[2] = { _Char, '\0' };
	return this->startsWith(vBytes, 1, xanadu::CaseSensitive);
}

// Detects whether the string starts with the specified prefix
bool xanadu::string::startsWith(_Elem _Char, xanadu::CaseSensitivity _XCS) const noexcept
{
	_Elem		vBytes[2] = { _Char, '\0' };
	return this->startsWith(vBytes, 1, _XCS);
}

// Detects whether the string starts with the specified prefix
bool xanadu::string::startsWith(const _Elem* _Memory) const noexcept
{
	return this->startsWith(_Memory, x_posix_strlen(_Memory), xanadu::CaseSensitive);
}

// Detects whether the string starts with the specified prefix
bool xanadu::string::startsWith(const _Elem* _Memory, xanadu::CaseSensitivity _XCS) const noexcept
{
	return this->startsWith(_Memory, x_posix_strlen(_Memory), _XCS);
}

// Detects whether the string starts with the specified prefix
bool xanadu::string::startsWith(const _Elem* _Memory, size_type _Length) const noexcept
{
	return this->startsWith(_Memory, _Length, xanadu::CaseSensitive);
}

// Detects whether the string starts with the specified prefix
bool xanadu::string::startsWith(const _Elem* _Memory, size_type _Length, xanadu::CaseSensitivity _XCS) const noexcept
{
	if(this->size() >= _Length)
	{
		return this->left(_Length).compare(_Memory, _Length, _XCS) == 0;
	}
	return false;
}

// Detects whether the string starts with the specified prefix
bool xanadu::string::startsWith(const xanadu::string& _String) const noexcept
{
	return this->startsWith(_String.data(), _String.size(), xanadu::CaseSensitive);
}

// Detects whether the string starts with the specified prefix
bool xanadu::string::startsWith(const xanadu::string& _String, xanadu::CaseSensitivity _XCS) const noexcept
{
	return this->startsWith(_String.data(), _String.size(), _XCS);
}





// Detects whether the string ends with the specified suffix
bool xanadu::string::endsWith(_Elem _Char) const noexcept
{
	_Elem		vBytes[2] = { _Char, '\0' };
	return this->endsWith(vBytes, 1, xanadu::CaseSensitive);
}

// Detects whether the string ends with the specified suffix
bool xanadu::string::endsWith(_Elem _Char, xanadu::CaseSensitivity _XCS) const noexcept
{
	_Elem		vBytes[2] = { _Char, '\0' };
	return this->endsWith(vBytes, 1, _XCS);
}

// Detects whether the string ends with the specified suffix
bool xanadu::string::endsWith(const _Elem* _Memory) const noexcept
{
	return this->endsWith(_Memory, x_posix_strlen(_Memory), xanadu::CaseSensitive);
}

// Detects whether the string ends with the specified suffix
bool xanadu::string::endsWith(const _Elem* _Memory, xanadu::CaseSensitivity _XCS) const noexcept
{
	return this->endsWith(_Memory, x_posix_strlen(_Memory), _XCS);
}

// Detects whether the string ends with the specified suffix
bool xanadu::string::endsWith(const _Elem* _Memory, size_type _Length) const noexcept
{
	return this->endsWith(_Memory, _Length, xanadu::CaseSensitive);
}

// Detects whether the string ends with the specified suffix
bool xanadu::string::endsWith(const _Elem* _Memory, size_type _Length, xanadu::CaseSensitivity _XCS) const noexcept
{
	if(this->size() >= _Length)
	{
		return this->right(_Length).compare(_Memory, _Length, _XCS) == 0;
	}
	return false;
}

// Detects whether the string ends with the specified suffix
bool xanadu::string::endsWith(const xanadu::string& _String) const noexcept
{
	return this->endsWith(_String.data(), _String.size(), xanadu::CaseSensitive);
}

// Detects whether the string ends with the specified suffix
bool xanadu::string::endsWith(const xanadu::string& _String, xanadu::CaseSensitivity _XCS) const noexcept
{
	return this->endsWith(_String.data(), _String.size(), _XCS);
}





// Find in positive order from the specified location
xanadu::string::pos_type xanadu::string::find(_Elem _Char) const noexcept
{
	_Elem		vBytes[2] = { _Char, '\0' };
	return this->find(vBytes, 1, 0, xanadu::CaseSensitive);
}

// Find in positive order from the specified location
xanadu::string::pos_type xanadu::string::find(_Elem _Char, xanadu::CaseSensitivity _XCS) const noexcept
{
	_Elem		vBytes[2] = { _Char, '\0' };
	return this->find(vBytes, 1, 0, _XCS);
}

// Find in positive order from the specified location
xanadu::string::pos_type xanadu::string::find(_Elem _Char, pos_type _Pos) const noexcept
{
	_Elem		vBytes[2] = { _Char, '\0' };
	return this->find(vBytes, 1, _Pos, xanadu::CaseSensitive);
}

// Find in positive order from the specified location
xanadu::string::pos_type xanadu::string::find(_Elem _Char, pos_type _Pos, xanadu::CaseSensitivity _XCS) const noexcept
{
	_Elem		vBytes[2] = { _Char, '\0' };
	return this->find(vBytes, 1, _Pos, _XCS);
}

// Find in positive order from the specified location
xanadu::string::pos_type xanadu::string::find(const _Elem* _String) const noexcept
{
	return this->find(_String, x_posix_strlen(_String), 0, xanadu::CaseSensitive);
}

// Find in positive order from the specified location
xanadu::string::pos_type xanadu::string::find(const _Elem* _String, xanadu::CaseSensitivity _XCS) const noexcept
{
	return this->find(_String, x_posix_strlen(_String), 0, _XCS);
}

// Find in positive order from the specified location
xanadu::string::pos_type xanadu::string::find(const _Elem* _String, pos_type _Pos) const noexcept
{
	return this->find(_String, x_posix_strlen(_String), _Pos, xanadu::CaseSensitive);
}

// Find in positive order from the specified location
xanadu::string::pos_type xanadu::string::find(const _Elem* _String, pos_type _Pos, xanadu::CaseSensitivity _XCS) const noexcept
{
	return this->find(_String, x_posix_strlen(_String), _Pos, _XCS);
}

// Find in positive order from the specified location
xanadu::string::pos_type xanadu::string::find(const _Elem* _String, size_type _Length, pos_type _Pos) const noexcept
{
	return this->find(_String, _Length, _Pos, xanadu::CaseSensitive);
}

// Find in positive order from the specified location
xanadu::string::pos_type xanadu::string::find(const _Elem* _String, size_type _Length, pos_type _Pos, xanadu::CaseSensitivity _XCS) const noexcept
{
	auto 		vFind = static_cast<const xanadu::string::_Elem*>(nullptr);

	if(_String == nullptr || _Length == 0 || (this->size() - _Pos) < _Length)
	{
		return xanadu::string::npos;
	}

	if(_XCS == xanadu::CaseInsensitive)
	{
		vFind = x_posix_stristr(this->data() + _Pos, _String);
	}
	else
	{
		vFind = x_posix_strstr(this->data() + _Pos, _String);
	}

	if(vFind)
	{
		return vFind - this->data();
	}
	return xanadu::string::npos;
}

// Find in positive order from the specified location
xanadu::string::pos_type xanadu::string::find(const xanadu::string& _String) const noexcept
{
	return this->find(_String.data(), _String.size(), 0, xanadu::CaseSensitive);
}

// Find in positive order from the specified location
xanadu::string::pos_type xanadu::string::find(const xanadu::string& _String, xanadu::CaseSensitivity _XCS) const noexcept
{
	return this->find(_String.data(), _String.size(), 0, _XCS);
}

// Find in positive order from the specified location
xanadu::string::pos_type xanadu::string::find(const xanadu::string& _String, pos_type _Pos) const noexcept
{
	return this->find(_String.data(), _String.size(), _Pos, xanadu::CaseSensitive);
}

// Find in positive order from the specified location
xanadu::string::pos_type xanadu::string::find(const xanadu::string& _String, pos_type _Pos, xanadu::CaseSensitivity _XCS) const noexcept
{
	return this->find(_String.data(), _String.size(), _Pos, _XCS);
}





// Search in reverse order from the specified location
xanadu::string::pos_type xanadu::string::rfind(_Elem _Char) const noexcept
{
	_Elem		vBytes[2] = { _Char, '\0' };
	return this->rfind(vBytes, 1, this->size() - 1, xanadu::CaseSensitive);
}

// Search in reverse order from the specified location
xanadu::string::pos_type xanadu::string::rfind(_Elem _Char, xanadu::CaseSensitivity _XCS) const noexcept
{
	_Elem		vBytes[2] = { _Char, '\0' };
	return this->rfind(vBytes, 1, this->size() - 1, _XCS);
}

// Search in reverse order from the specified location
xanadu::string::pos_type xanadu::string::rfind(_Elem _Char, pos_type _Pos) const noexcept
{
	_Elem		vBytes[2] = { _Char, '\0' };
	return this->rfind(vBytes, 1, _Pos, xanadu::CaseSensitive);
}

// Search in reverse order from the specified location
xanadu::string::pos_type xanadu::string::rfind(_Elem _Char, pos_type _Pos, xanadu::CaseSensitivity _XCS) const noexcept
{
	_Elem		vBytes[2] = { _Char, '\0' };
	return this->rfind(vBytes, 1, _Pos, _XCS);
}

// Search in reverse order from the specified location
xanadu::string::pos_type xanadu::string::rfind(const _Elem* _String) const noexcept
{
	return  this->rfind(_String, x_posix_strlen(_String), this->size() - 1, xanadu::CaseSensitive);
}

// Search in reverse order from the specified location
xanadu::string::pos_type xanadu::string::rfind(const _Elem* _String, xanadu::CaseSensitivity _XCS) const noexcept
{
	return  this->rfind(_String, x_posix_strlen(_String), this->size() - 1, _XCS);
}

// Search in reverse order from the specified location
xanadu::string::pos_type xanadu::string::rfind(const _Elem* _String, pos_type _Pos) const noexcept
{
	return  this->rfind(_String, x_posix_strlen(_String), _Pos, xanadu::CaseSensitive);
}

// Search in reverse order from the specified location
xanadu::string::pos_type xanadu::string::rfind(const _Elem* _String, pos_type _Pos, xanadu::CaseSensitivity _XCS) const noexcept
{
	return  this->rfind(_String, x_posix_strlen(_String), _Pos, _XCS);
}

// Search in reverse order from the specified location
xanadu::string::pos_type xanadu::string::rfind(const _Elem* _String, size_type _Length, pos_type _Pos) const noexcept
{
	return this->rfind(_String, _Length, _Pos, xanadu::CaseSensitive);
}

// Search in reverse order from the specified location
xanadu::string::pos_type xanadu::string::rfind(const _Elem* _String, size_type _Length, pos_type _Pos, xanadu::CaseSensitivity _XCS) const noexcept
{
	auto 		vFind = static_cast<int>(1);

	if(_String == nullptr || _Length == 0 || this->size() < _Length)
	{
		return xanadu::string::npos;
	}

	for(; _Pos != xanadu::string::npos && vFind != 0; --_Pos)
	{
		if(_XCS == xanadu::CaseInsensitive)
		{
			vFind = x_posix_strnicmp(this->data() + _Pos, _String, _Length);
		}
		else
		{
			vFind = x_posix_strncmp(this->data() + _Pos, _String, _Length);
		}
	}
	return _Pos;
}

// Search in reverse order from the specified location
xanadu::string::pos_type xanadu::string::rfind(const xanadu::string& _String) const noexcept
{
	return this->rfind(_String.data(), _String.size(), this->size() - 1, xanadu::CaseSensitive);
}

// Search in reverse order from the specified location
xanadu::string::pos_type xanadu::string::rfind(const xanadu::string& _String, xanadu::CaseSensitivity _XCS) const noexcept
{
	return this->rfind(_String.data(), _String.size(), this->size() - 1, _XCS);
}

// Search in reverse order from the specified location
xanadu::string::pos_type xanadu::string::rfind(const xanadu::string& _String, pos_type _Pos) const noexcept
{
	return this->rfind(_String.data(), _String.size(), _Pos, xanadu::CaseSensitive);
}

// Search in reverse order from the specified location
xanadu::string::pos_type xanadu::string::rfind(const xanadu::string& _String, pos_type _Pos, xanadu::CaseSensitivity _XCS) const noexcept
{
	return this->rfind(_String.data(), _String.size(), _Pos, _XCS);
}





// Check whether the specified content is included
bool xanadu::string::contains(_Elem _Char) const noexcept
{
	_Elem		vBytes[2] = { _Char, '\0' };
	return this->contains(vBytes, 1, xanadu::CaseSensitive);
}

// Check whether the specified content is included
bool xanadu::string::contains(_Elem _Char, xanadu::CaseSensitivity _XCS) const noexcept
{
	_Elem		vBytes[2] = { _Char, '\0' };
	return this->contains(vBytes, 1, _XCS);
}

// Check whether the specified content is included
bool xanadu::string::contains(const _Elem* _String) const noexcept
{
	return this->contains(_String, x_posix_strlen(_String), xanadu::CaseSensitive);
}

// Check whether the specified content is included
bool xanadu::string::contains(const _Elem* _String, xanadu::CaseSensitivity _XCS) const noexcept
{
	return this->contains(_String, x_posix_strlen(_String), _XCS);
}

// Check whether the specified content is included
bool xanadu::string::contains(const _Elem* _String, size_type _Length) const noexcept
{
	return this->contains(_String, _Length, xanadu::CaseSensitive);
}

// Check whether the specified content is included
bool xanadu::string::contains(const _Elem* _String, size_type _Length, xanadu::CaseSensitivity _XCS) const noexcept
{
	auto		vFind = this->find(_String, _Length, 0, _XCS);
	return vFind != xanadu::string::npos;
}

// Check whether the specified content is included
bool xanadu::string::contains(const xanadu::string& _String) const noexcept
{
	return this->contains(_String.data(), _String.size(), xanadu::CaseSensitive);
}

// Check whether the specified content is included
bool xanadu::string::contains(const xanadu::string& _String, xanadu::CaseSensitivity _XCS) const noexcept
{
	return this->contains(_String.data(), _String.size(), _XCS);
}





// Check that they are the same
int xanadu::string::compare(_Elem _Char) const noexcept
{
	_Elem		vBytes[2] = { _Char, '\0' };
	return this->compare(vBytes, 1, xanadu::CaseSensitive);
}

// Check that they are the same
int xanadu::string::compare(_Elem _Char, xanadu::CaseSensitivity _XCS) const noexcept
{
	_Elem		vBytes[2] = { _Char, '\0' };
	return this->compare(vBytes, 1, _XCS);
}

// Check that they are the same
int xanadu::string::compare(const _Elem* _String) const noexcept
{
	return this->compare(_String, x_posix_strlen(_String), xanadu::CaseSensitive);
}

// Check that they are the same
int xanadu::string::compare(const _Elem* _String, xanadu::CaseSensitivity _XCS) const noexcept
{
	return this->compare(_String, x_posix_strlen(_String), _XCS);
}

// Check that they are the same
int xanadu::string::compare(const _Elem* _String, size_type _Length) const noexcept
{
	return this->compare(_String, _Length, xanadu::CaseSensitive);
}

// Check that they are the same
int xanadu::string::compare(const _Elem* _String, size_type _Length, xanadu::CaseSensitivity _XCS) const noexcept
{
	int		vCompare = 0;

	if (this->data() == _String)
	{
		return 0;
	}
	if (this->data() && _String)
	{
		if(this->size() == _Length)
		{
			if(_XCS == xanadu::CaseInsensitive)
			{
				vCompare = x_posix_strnicmp(this->data(), _String, _Length);
			}
			else
			{
				vCompare = x_posix_strncmp(this->data(), _String, _Length);
			}
		}
		else if(this->size() > _Length)
		{
			if(_XCS == xanadu::CaseInsensitive)
			{
				vCompare = x_posix_strnicmp(this->data(), _String, _Length);
			}
			else
			{
				vCompare = x_posix_strncmp(this->data(), _String, _Length);
			}
			if(vCompare == 0)
			{
				vCompare = -1;
			}
		}
		else
		{
			if(_XCS == xanadu::CaseInsensitive)
			{
				vCompare = x_posix_strnicmp(this->data(), _String, this->size());
			}
			else
			{
				vCompare = x_posix_strncmp(this->data(), _String, this->size());
			}
			if(vCompare == 0)
			{
				vCompare = 1;
			}
		}
		return vCompare;
	}
	else if(this->data())
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

// Check that they are the same
int xanadu::string::compare(const xanadu::string& _String) const noexcept
{
	return this->compare(_String.data(), _String.size(), xanadu::CaseSensitive);
}

// Check that they are the same
int xanadu::string::compare(const xanadu::string& _String, xanadu::CaseSensitivity _XCS) const noexcept
{
	return this->compare(_String.data(), _String.size(), _XCS);
}





// Add at the begin
xanadu::string& xanadu::string::prepend(_Elem _Char) noexcept
{
	_Elem		vBytes[2] = { _Char, '\0' };
	return this->prepend(vBytes, 1);
}

// Add at the begin
xanadu::string& xanadu::string::prepend(const _Elem* _String) noexcept
{
	return this->prepend(_String, x_posix_strlen(_String));
}

// Add at the begin
xanadu::string& xanadu::string::prepend(const _Elem* _String, size_type _Size) noexcept
{
	return this->insert(0, _String, _Size);
}

// Add at the begin
xanadu::string& xanadu::string::prepend(const xanadu::string& _String) noexcept
{
	return this->prepend(_String.data(), _String.size());
}





// Add at the end
xanadu::string& xanadu::string::append(_Elem _Char) noexcept
{
	_Elem		vBytes[2] = { _Char, '\0' };
	return this->append(vBytes, 1);
}

// Add at the end
xanadu::string& xanadu::string::append(const _Elem* _String) noexcept
{
	return this->append(_String, x_posix_strlen(_String));
}

// Add at the end
xanadu::string& xanadu::string::append(const _Elem* _String, size_type _Size) noexcept
{
	return this->insert(this->size(), _String, _Size);
}

// Add at the end
xanadu::string& xanadu::string::append(const xanadu::string& _String) noexcept
{
	return this->append(_String.data(), _String.size());
}





// Inserts data from the specified location _Elem
xanadu::string& xanadu::string::insert(pos_type _Pos, _Elem _Char) noexcept
{
	_Elem		vBytes[2] = { _Char, '\0' };
	return this->insert(_Pos, vBytes, 1);
}

// Inserts data from the specified location _Elem
xanadu::string& xanadu::string::insert(pos_type _Pos, size_type _Count, _Elem _Char) noexcept
{
	auto		vString = xanadu::string(_Count, _Char);
	return this->insert(_Pos, vString.data(), vString.size());
}

// Inserts data from the specified location const _Elem*
xanadu::string& xanadu::string::insert(pos_type _Pos, const _Elem* _String) noexcept
{
	return this->insert(_Pos, _String, x_posix_strlen(_String));
}

// Inserts data from the specified location const _Elem*
xanadu::string& xanadu::string::insert(pos_type _Pos, const _Elem* _String, size_type _Length) noexcept
{
	this->_Allocator.insert(_Pos, _String, _Length);
	return *this;
}

// Inserts data from the specified location xanadu::string
xanadu::string& xanadu::string::insert(pos_type _Pos, const xanadu::string& _String) noexcept
{
	return this->insert(_Pos, _String.data(), _String.size());
}





// Removes the specified length of data from the specified location
xanadu::string& xanadu::string::remove(pos_type _Pos, size_type _Length) noexcept
{
	this->_Allocator.remove(_Pos, _Length);
	return *this;
}

// Delete the same data as the parameter
xanadu::string& xanadu::string::remove(_Elem _Char) noexcept
{
	_Elem		vBytes[2] = { _Char, '\0' };
	return this->remove(vBytes, 1, xanadu::CaseSensitive);
}

// Delete the same data as the parameter
xanadu::string& xanadu::string::remove(_Elem _Char, xanadu::CaseSensitivity _XCS) noexcept
{
	_Elem		vBytes[2] = { _Char, '\0' };
	return this->remove(vBytes, 1, _XCS);
}

// Delete the same data as the parameter
xanadu::string& xanadu::string::remove(const _Elem* _String) noexcept
{
	return this->remove(_String, x_posix_strlen(_String), xanadu::CaseSensitive);
}

// Delete the same data as the parameter
xanadu::string& xanadu::string::remove(const _Elem* _String, xanadu::CaseSensitivity _XCS) noexcept
{
	return this->remove(_String, x_posix_strlen(_String), _XCS);
}

// Delete the same data as the parameter
xanadu::string& xanadu::string::remove(const _Elem* _String, size_type _Length) noexcept
{
	return this->remove(_String, _Length, xanadu::CaseSensitive);
}

// Delete the same data as the parameter
xanadu::string& xanadu::string::remove(const _Elem* _String, size_type _Length, xanadu::CaseSensitivity _XCS) noexcept
{
	auto		vFind = this->find(_String, _Length, _XCS);
	if(vFind != xanadu::string::npos)
	{
		return this->remove(vFind, _Length);
	}
	return *this;
}

// Delete the same data as the parameter
xanadu::string& xanadu::string::remove(const xanadu::string& _String) noexcept
{
	return this->remove(_String.data(), _String.size(), xanadu::CaseSensitive);
}

// Delete the same data as the parameter
xanadu::string& xanadu::string::remove(const xanadu::string& _String, xanadu::CaseSensitivity _XCS) noexcept
{
	return this->remove(_String.data(), _String.size(), _XCS);
}



// Replace the specified data
xanadu::string& xanadu::string::replace(pos_type _Pos, size_type _Length, _Elem _After) noexcept
{
	_Elem		vAfter[2] = { _After, '\0' };
	return this->replace(_Pos, _Length, vAfter, 1);
}

// Replace the specified data
xanadu::string& xanadu::string::replace(pos_type _Pos, size_type _Length, const _Elem* _After) noexcept
{
	return this->replace(_Pos, _Length, _After, x_posix_strlen(_After));
}

// Replace the specified data
xanadu::string& xanadu::string::replace(pos_type _Pos, size_type _Length, const _Elem* _After, size_type _LengthA) noexcept
{
	this->_Allocator.replace(_Pos, _Length, _After, _LengthA);
	return *this;
}

// Replace the specified data
xanadu::string& xanadu::string::replace(pos_type _Pos, size_type _Length, const xanadu::string& _After) noexcept
{
	return this->replace(_Pos, _Length, _After.data(), _After.size());
}





// Replace the specified data
xanadu::string& xanadu::string::replace(_Elem _Before, _Elem _After) noexcept
{
	_Elem		vBefore[2] = { _Before, '\0' };
	_Elem		vAfter[2] = { _After, '\0' };
	return this->replace(vBefore, 1, vAfter, 1, xanadu::CaseSensitive);
}

// Replace the specified data
xanadu::string& xanadu::string::replace(_Elem _Before, _Elem _After, xanadu::CaseSensitivity _XCS) noexcept
{
	_Elem		vBefore[2] = { _Before, '\0' };
	_Elem		vAfter[2] = { _After, '\0' };
	return this->replace(vBefore, 1, vAfter, 1, _XCS);
}

// Replace the specified data
xanadu::string& xanadu::string::replace(_Elem _Before, const _Elem* _After, size_type _LengthA) noexcept
{
	_Elem		vBefore[2] = { _Before, '\0' };
	return this->replace(vBefore, 1, _After, _LengthA, xanadu::CaseSensitive);
}

// Replace the specified data
xanadu::string& xanadu::string::replace(_Elem _Before, const _Elem* _After, size_type _LengthA, xanadu::CaseSensitivity _XCS) noexcept
{
	_Elem		vBefore[2] = { _Before, '\0' };
	return this->replace(vBefore, 1, _After, _LengthA, _XCS);
}

// Replace the specified data
xanadu::string& xanadu::string::replace(_Elem _Before, const xanadu::string& _After) noexcept
{
	_Elem		vBefore[2] = { _Before, '\0' };
	return this->replace(vBefore, 1, _After.data(), _After.size(), xanadu::CaseSensitive);
}

// Replace the specified data
xanadu::string& xanadu::string::replace(_Elem _Before, const xanadu::string& _After, xanadu::CaseSensitivity _XCS) noexcept
{
	_Elem		vBefore[2] = { _Before, '\0' };
	return this->replace(vBefore, 1, _After.data(), _After.size(), _XCS);
}





// Replace the specified data
xanadu::string& xanadu::string::replace(const _Elem* _Before, _Elem _After) noexcept
{
	_Elem		vAfter[2] = { _After, '\0' };
	return this->replace(_Before, x_posix_strlen(_Before), vAfter, 1, xanadu::CaseSensitive);
}

// Replace the specified data
xanadu::string& xanadu::string::replace(const _Elem* _Before, _Elem _After, xanadu::CaseSensitivity _XCS) noexcept
{
	_Elem		vAfter[2] = { _After, '\0' };
	return this->replace(_Before, x_posix_strlen(_Before), vAfter, 1, _XCS);
}

// Replace the specified data
xanadu::string& xanadu::string::replace(const _Elem* _Before, const _Elem* _After, size_type _LengthA) noexcept
{
	return this->replace(_Before, x_posix_strlen(_Before), _After, _LengthA, xanadu::CaseSensitive);
}

// Replace the specified data
xanadu::string& xanadu::string::replace(const _Elem* _Before, const _Elem* _After, size_type _LengthA, xanadu::CaseSensitivity _XCS) noexcept
{
	return this->replace(_Before, x_posix_strlen(_Before), _After, _LengthA, _XCS);
}

// Replace the specified data
xanadu::string& xanadu::string::replace(const _Elem* _Before, const xanadu::string& _After) noexcept
{
	return this->replace(_Before, x_posix_strlen(_Before), _After.data(), _After.size(), xanadu::CaseSensitive);
}

// Replace the specified data
xanadu::string& xanadu::string::replace(const _Elem* _Before, const xanadu::string& _After, xanadu::CaseSensitivity _XCS) noexcept
{
	return this->replace(_Before, x_posix_strlen(_Before), _After.data(), _After.size(), _XCS);
}





// Replace the specified data
xanadu::string& xanadu::string::replace(const _Elem* _Before, size_type _LengthB, _Elem _After) noexcept
{
	_Elem		vAfter[2] = { _After, '\0' };
	return this->replace(_Before, _LengthB, vAfter, 1, xanadu::CaseSensitive);
}

// Replace the specified data
xanadu::string& xanadu::string::replace(const _Elem* _Before, size_type _LengthB, _Elem _After, xanadu::CaseSensitivity _XCS) noexcept
{
	_Elem		vAfter[2] = { _After, '\0' };
	return this->replace(_Before, _LengthB, vAfter, 1, _XCS);
}

// Replace the specified data
xanadu::string& xanadu::string::replace(const _Elem* _Before, size_type _LengthB, const _Elem* _After, size_type _LengthA) noexcept
{
	return this->replace(_Before, _LengthB, _After, _LengthA, xanadu::CaseSensitive);
}

// Replace the specified data
xanadu::string& xanadu::string::replace(const _Elem* _Before, size_type _LengthB, const _Elem* _After, size_type _LengthA, xanadu::CaseSensitivity _XCS) noexcept
{
	pos_type	vPos = xanadu::string::npos;
	do
	{
		vPos = this->find(_Before, _LengthB, vPos, _XCS);
		if(xanadu::string::npos != vPos)
		{
			this->replace(vPos, _LengthB, _After, _LengthA);
			vPos += _LengthA;
		}
	} while(xanadu::string::npos != vPos);
	return *this;
}

// Replace the specified data
xanadu::string& xanadu::string::replace(const _Elem* _Before, size_type _LengthB, const xanadu::string& _After) noexcept
{
	return this->replace(_Before, _LengthB, _After.data(), _After.size(), xanadu::CaseSensitive);
}

// Replace the specified data
xanadu::string& xanadu::string::replace(const _Elem* _Before, size_type _LengthB, const xanadu::string& _After, xanadu::CaseSensitivity _XCS) noexcept
{
	return this->replace(_Before, _LengthB, _After.data(), _After.size(), _XCS);
}





// Replace the specified data
xanadu::string& xanadu::string::replace(const xanadu::string& _Before, _Elem _After) noexcept
{
	_Elem		vAfter[2] = { _After, '\0' };
	return this->replace(_Before.data(), _Before.size(), vAfter, 1, xanadu::CaseSensitive);
}

// Replace the specified data
xanadu::string& xanadu::string::replace(const xanadu::string& _Before, _Elem _After, xanadu::CaseSensitivity _XCS) noexcept
{
	_Elem		vAfter[2] = { _After, '\0' };
	return this->replace(_Before.data(), _Before.size(), vAfter, 1, _XCS);
}

// Replace the specified data
xanadu::string& xanadu::string::replace(const xanadu::string& _Before, const _Elem* _After, size_type _LengthA) noexcept
{
	return this->replace(_Before.data(), _Before.size(), _After, _LengthA, xanadu::CaseSensitive);
}

// Replace the specified data
xanadu::string& xanadu::string::replace(const xanadu::string& _Before, const _Elem* _After, size_type _LengthA, xanadu::CaseSensitivity _XCS) noexcept
{
	return this->replace(_Before.data(), _Before.size(), _After, _LengthA, _XCS);
}

// Replace the specified data
xanadu::string& xanadu::string::replace(const xanadu::string& _Before, const xanadu::string& _After) noexcept
{
	return this->replace(_Before.data(), _Before.size(), _After.data(), _After.size(), xanadu::CaseSensitive);
}

// Replace the specified data
xanadu::string& xanadu::string::replace(const xanadu::string& _Before, const xanadu::string& _After, xanadu::CaseSensitivity _XCS) noexcept
{
	return this->replace(_Before.data(), _Before.size(), _After.data(), _After.size(), _XCS);
}





// 按指定数据拆分字符串
std::list<xanadu::string> xanadu::string::split(_Elem _Char) const noexcept
{
	_Elem		vBytes[2] = { _Char, '\0' };
	return this->split(vBytes, 1);
}

// 按指定数据拆分字符串
std::list<xanadu::string> xanadu::string::split(const _Elem* _Memory) const noexcept
{
	return this->split({_Memory, x_posix_strlen(_Memory)});
}

// 按指定数据拆分字符串
std::list<xanadu::string> xanadu::string::split(const _Elem* _Memory, size_type _Size) const noexcept
{
	return this->split({_Memory, _Size});
}

// 按指定数据拆分字符串
std::list<xanadu::string> xanadu::string::split(const xanadu::string& _String) const noexcept
{
	auto		vHeaderArray = std::list<xanadu::string>();
	auto		vLast = static_cast<size_type>(0U);
	auto		vSplitIndex = this->find(_String, vLast);
	while(vSplitIndex != xanadu::string::npos && _String.exist())
	{
		vHeaderArray.push_back(this->mid(vLast, vSplitIndex - vLast));
		vLast = vSplitIndex + 2;
		vSplitIndex = this->find(_String, vLast);
	}
	vHeaderArray.push_back(this->mid(vLast));

	return vHeaderArray;
}





// 判断一个字符是否为空白字符
bool xanadu::string::isSpace(_Elem _Char) noexcept
{
	// 如果宽字符是空白字符，则为真，否则假。
	return isspace(_Char);
}

// 格式化字符串 (char* [%s]) (wchar_t* [%ls])
xanadu::string xanadu::string::format(const char* _Format, ...) noexcept
{
	auto		vString = xanadu::string();
	va_list		vArgs1;
	va_list		vArgs2;

	va_start(vArgs1, _Format);
	va_copy(vArgs2, vArgs1);
	auto		vSize = std::vsnprintf(nullptr, 0, _Format, vArgs1);
	if(vSize > 0)
	{
		vString.resize(vSize + XANADU_STDIO_VSNPRINTF_EXTRA);
		std::vsnprintf(vString.data(), vString.size(), _Format, vArgs2);
		vString.remove(vSize, XANADU_STDIO_VSNPRINTF_EXTRA);
	}
	va_end(vArgs1);
	va_end(vArgs2);
	return vString;
}





// [conv] 转换至大写
xanadu::string xanadu::string::toUpper() const noexcept
{
	auto		vStrUpper = *this;
	for(pos_type vIndex = 0; vIndex < vStrUpper.size(); ++vIndex)
	{
		vStrUpper[vIndex] = (_Elem)std::toupper(vStrUpper[vIndex]);
	}
	return vStrUpper;
}

// [conv] 转换至小写
xanadu::string xanadu::string::toLower() const noexcept
{
	auto		vStrUpper = *this;
	for(pos_type vIndex = 0; vIndex < vStrUpper.size(); ++vIndex)
	{
		vStrUpper[vIndex] = (_Elem)std::tolower(vStrUpper[vIndex]);
	}
	return vStrUpper;
}





// [conv] 转换至AString
AString xanadu::string::toAString() const noexcept
{
	auto		vWString = this->toWString();
	auto		vAString = AString();
	auto		vChangeStr = x_posix_strwtoa(vWString.data());
	if(vChangeStr)
	{
		vAString = vChangeStr;
		x_posix_free(vChangeStr);
	}
	return vAString;
}

// [conv] 从AString转换
xanadu::string xanadu::string::fromAString(const char* _AString) noexcept
{
	return xanadu::string::fromAString({_AString, x_posix_strlen(_AString)});
}

// [conv] 从AString转换
xanadu::string xanadu::string::fromAString(const AString& _AString) noexcept
{
	auto		vString = WString();
	auto		vChangeStr = x_posix_stratow(_AString.data());
	if(vChangeStr)
	{
		vString = vChangeStr;
		x_posix_free(vChangeStr);
	}
	return xanadu::string::fromWString(vString);
}





// [conv] 转换至WString
WString xanadu::string::toWString() const noexcept
{
	auto		vWString = WString();
	auto		vChangeStr = x_posix_strutow(this->data());
	if(vChangeStr)
	{
		vWString = vChangeStr;
		x_posix_free(vChangeStr);
	}
	return vWString;
}

// [conv] 从WString转换
xanadu::string xanadu::string::fromWString(const wchar_t* _WString) noexcept
{
	return xanadu::string::fromWString({_WString, x_posix_wcslen(_WString)});
}

// [conv] 从WString转换
xanadu::string xanadu::string::fromWString(const WString& _WString) noexcept
{
	auto		vString = xanadu::string();
	auto		vChangeStr = x_posix_strwtou(_WString.data());
	if(vChangeStr)
	{
		vString = vChangeStr;
		x_posix_free(vChangeStr);
	}
	return vString;
}





// [conv] 转换至UString
UString xanadu::string::toUString() const noexcept
{
	return {this->data(), this->size()};
}

// [conv] 从UString转换
xanadu::string xanadu::string::fromUString(const char* _UString) noexcept
{
	return xanadu::string::fromUString({_UString, x_posix_strlen(_UString)});
}

// [conv] 从UString转换
xanadu::string xanadu::string::fromUString(const UString& _UString) noexcept
{
	return {_UString.data(), _UString.size()};
}





// [conv] 转换至NString (Windows: ASCII / 其它: UTF-8)
NString xanadu::string::toNString() const noexcept
{
#if defined(XANADU_SYSTEM_WINDOWS)
	return this->toAString();
#else
	return this->toUString();
#endif
}

// [conv] 从NString转换 (Windows: ASCII / 其它: UTF-8)
xanadu::string xanadu::string::fromNString(const char* _NString) noexcept
{
	return xanadu::string::fromNString({_NString, x_posix_strlen(_NString)});
}

// [conv] 从NString转换 (Windows: ASCII / 其它: UTF-8)
xanadu::string xanadu::string::fromNString(const UString& _NString) noexcept
{
#if defined(XANADU_SYSTEM_WINDOWS)
	return xanadu::string::fromAString(_NString);
#else
	return xanadu::string::fromUString(_NString);
#endif
}





// [conv] 转换至HEX
xanadu::string xanadu::string::toHex() const noexcept
{
	auto		vTarget = xanadu::string(this->size() * 2, '0');
	for (auto vIndex = 0U; vIndex < this->size(); ++vIndex)
	{
		x_posix_sprintf(vTarget.data() + (vIndex * 2), "%02X", (std::uint8_t)this->data()[vIndex]);
	}
	return vTarget;
}

// [conv] 从HEX转换
xanadu::string xanadu::string::fromHex(const _Elem* _String) noexcept
{
	return xanadu::string::fromHex({_String, x_posix_strlen(_String)});
}

// [conv] 从HEX转换
xanadu::string xanadu::string::fromHex(const _Elem* _String, size_type _Size) noexcept
{
	return xanadu::string::fromHex({_String, _Size});
}

// [conv] 从HEX转换
xanadu::string xanadu::string::fromHex(const xanadu::string& _Hex) noexcept
{
	if (_Hex.empty())
	{
		return {};
	}

	auto		vFunctionHexToChar = [](char _Char)
	{
		if ((_Char >= 'A') && (_Char <= 'Z'))
		{
			return _Char - 'A' + 10;
		}
		else if ((_Char >= 'a') && (_Char <= 'z'))
		{
			return _Char - 'a' + 10;
		}
		else if ((_Char >= '0') && (_Char <= '9'))
		{
			return _Char - '0';
		}
		return 0;
	};
	auto		vBuffer = _Hex.data();
	auto		vLength = _Hex.size() / 2;
	auto		vTarget = xanadu::string(vLength, '\0');

	for (auto vIndex = 0U; vIndex < vLength; ++vIndex)
	{
		auto		vHexLeft = vFunctionHexToChar(vBuffer[vIndex * 2 + 0]);
		auto		vHexRight = vFunctionHexToChar(vBuffer[vIndex * 2 + 1]);
		vTarget[vIndex] = static_cast<char>(vHexLeft * 16 + vHexRight);
	}
	return vTarget;
}





// [convert] convert to char
char xanadu::string::toChar(bool* _Ok, int _Base) const noexcept
{
	return static_cast<char>(this->toLLong(_Ok, _Base));
}

// [convert] convert to unsigned char
unsigned char xanadu::string::toUChar(bool* _Ok, int _Base) const noexcept
{
	return static_cast<unsigned char>(this->toULLong(_Ok, _Base));
}

// [convert] convert to short
short xanadu::string::toShort(bool* _Ok, int _Base) const noexcept
{
	return static_cast<short>(this->toLLong(_Ok, _Base));
}

// [convert] convert to short
unsigned short xanadu::string::toUShort(bool* _Ok, int _Base) const noexcept
{
	return static_cast<unsigned short>(this->toULLong(_Ok, _Base));
}

// [convert] convert to int
int xanadu::string::toInt(bool* _Ok, int _Base) const noexcept
{
	return static_cast<int>(this->toLLong(_Ok, _Base));
}

// [convert] convert to unsigned int
unsigned int xanadu::string::toUInt(bool* _Ok, int _Base) const noexcept
{
	return static_cast<unsigned int>(this->toULLong(_Ok, _Base));
}

// [convert] convert to long
long xanadu::string::toLong(bool* _Ok, int _Base) const noexcept
{
	return static_cast<long>(this->toLLong(_Ok, _Base));
}

// [convert] convert to unsigned long
unsigned long xanadu::string::toULong(bool* _Ok, int _Base) const noexcept
{
	return static_cast<unsigned long>(this->toULLong(_Ok, _Base));
}

// [convert] convert to long long
long long xanadu::string::toLLong(bool* _Ok, int _Base) const noexcept
{
	auto		vEnd = static_cast<_Elem*>(nullptr);
	auto		vValue = std::strtoll(this->data(), &vEnd, _Base);

	if(_Ok)
	{
		if(vEnd && vEnd[0] == '\0')
		{
			*_Ok = true;
		}
		else
		{
			*_Ok = false;
		}
	}

	return vValue;
}

// [convert] convert to unsigned long long
unsigned long long xanadu::string::toULLong(bool* _Ok, int _Base) const noexcept
{
	auto		vEnd = static_cast<_Elem*>(nullptr);
	auto		vValue = std::strtoull(this->data(), &vEnd, _Base);

	if(_Ok)
	{
		if(vEnd && vEnd[0] == '\0')
		{
			*_Ok = true;
		}
		else
		{
			*_Ok = false;
		}
	}

	return vValue;
}

// [convert] convert to float
float xanadu::string::toFloat(bool* _Ok) const noexcept
{
	auto		vEnd = static_cast<_Elem*>(nullptr);
	auto		vValue = std::strtof(this->data(), &vEnd);

	if(_Ok)
	{
		if(vEnd && vEnd[0] == '\0')
		{
			*_Ok = true;
		}
		else
		{
			*_Ok = false;
		}
	}

	return vValue;
}

// [convert] convert to double
double xanadu::string::toDouble(bool* _Ok) const noexcept
{
	auto		vEnd = static_cast<_Elem*>(nullptr);
	auto		vValue = std::strtod(this->data(), &vEnd);

	if(_Ok)
	{
		if(vEnd && vEnd[0] == '\0')
		{
			*_Ok = true;
		}
		else
		{
			*_Ok = false;
		}
	}

	return vValue;
}





// [convert] convert from number
xanadu::string& xanadu::string::setNumber(char _Value, int _Base) noexcept
{
	this->setNumber(static_cast<long long>(_Value), _Base);
	return *this;
}

// [convert] convert from number
xanadu::string& xanadu::string::setNumber(unsigned char _Value, int _Base) noexcept
{
	this->setNumber(static_cast<unsigned long long>(_Value), _Base);
	return *this;
}

// [convert] convert from number
xanadu::string& xanadu::string::setNumber(short _Value, int _Base) noexcept
{
	this->setNumber(static_cast<long long>(_Value), _Base);
	return *this;
}

// [convert] convert from number
xanadu::string& xanadu::string::setNumber(unsigned short _Value, int _Base) noexcept
{
	this->setNumber(static_cast<unsigned long long>(_Value), _Base);
	return *this;
}

// [convert] convert from number
xanadu::string& xanadu::string::setNumber(int _Value, int _Base) noexcept
{
	this->setNumber(static_cast<long long>(_Value), _Base);
	return *this;
}

// [convert] convert from number
xanadu::string& xanadu::string::setNumber(unsigned int _Value, int _Base) noexcept
{
	this->setNumber(static_cast<unsigned long long>(_Value), _Base);
	return *this;
}

// [convert] convert from number
xanadu::string& xanadu::string::setNumber(long _Value, int _Base) noexcept
{
	this->setNumber(static_cast<long long>(_Value), _Base);
	return *this;
}

// [convert] convert from number
xanadu::string& xanadu::string::setNumber(unsigned long _Value, int _Base) noexcept
{
	this->setNumber(static_cast<unsigned long long>(_Value), _Base);
	return *this;
}

// [convert] convert from number
xanadu::string& xanadu::string::setNumber(long long _Value, int _Base) noexcept
{
	if(2 <= _Base && _Base <= 36)
	{
		*this = std::to_string(_Value).data();
	}
	return *this;
}

// [convert] convert from number
xanadu::string& xanadu::string::setNumber(unsigned long long _Value, int _Base) noexcept
{
	if(2 <= _Base && _Base <= 36)
	{
		*this = std::to_string(_Value).data();
	}
	return *this;
}

// [convert] convert from number
xanadu::string& xanadu::string::setNumber(float _Value, char _Format, int _Prec) noexcept
{
	XANADU_UNUSED(_Format);
	XANADU_UNUSED(_Prec);

	*this = std::to_string(_Value).data();
	return *this;
}

// [convert] convert from number
xanadu::string& xanadu::string::setNumber(double _Value, char _Format, int _Prec) noexcept
{
	XANADU_UNUSED(_Format);
	XANADU_UNUSED(_Prec);

	*this = std::to_string(_Value).data();
	return *this;
}





// [convert] convert from number
xanadu::string xanadu::string::number(char _Value, int _Base) noexcept
{
	auto		vValue = xanadu::string();
	vValue.setNumber(_Value, _Base);
	return vValue;
}

// [convert] convert from number
xanadu::string xanadu::string::number(unsigned char _Value, int _Base) noexcept
{
	auto		vValue = xanadu::string();
	vValue.setNumber(_Value, _Base);
	return vValue;
}

// [convert] convert from number
xanadu::string xanadu::string::number(short _Value, int _Base) noexcept
{
	auto		vValue = xanadu::string();
	vValue.setNumber(_Value, _Base);
	return vValue;
}

// [convert] convert from number
xanadu::string xanadu::string::number(unsigned short _Value, int _Base) noexcept
{
	auto		vValue = xanadu::string();
	vValue.setNumber(_Value, _Base);
	return vValue;
}

// [convert] convert from number
xanadu::string xanadu::string::number(int _Value, int _Base) noexcept
{
	auto		vValue = xanadu::string();
	vValue.setNumber(_Value, _Base);
	return vValue;
}

// [convert] convert from number
xanadu::string xanadu::string::number(unsigned int _Value, int _Base) noexcept
{
	auto		vValue = xanadu::string();
	vValue.setNumber(_Value, _Base);
	return vValue;
}

// [convert] convert from number
xanadu::string xanadu::string::number(long _Value, int _Base) noexcept
{
	auto		vValue = xanadu::string();
	vValue.setNumber(_Value, _Base);
	return vValue;
}

// [convert] convert from number
xanadu::string xanadu::string::number(unsigned long _Value, int _Base) noexcept
{
	auto		vValue = xanadu::string();
	vValue.setNumber(_Value, _Base);
	return vValue;
}

// [convert] convert from number
xanadu::string xanadu::string::number(long long _Value, int _Base) noexcept
{
	auto		vValue = xanadu::string();
	vValue.setNumber(_Value, _Base);
	return vValue;
}

// [convert] convert from number
xanadu::string xanadu::string::number(unsigned long long _Value, int _Base) noexcept
{
	auto		vValue = xanadu::string();
	vValue.setNumber(_Value, _Base);
	return vValue;
}

// [convert] convert from number
xanadu::string xanadu::string::number(float _Value, char _Format, int _Prec) noexcept
{
	auto		vValue = xanadu::string();
	vValue.setNumber(_Value, _Format, _Prec);
	return vValue;
}

// [convert] convert from number
xanadu::string xanadu::string::number(double _Value, char _Format, int _Prec) noexcept
{
	auto		vValue = xanadu::string();
	vValue.setNumber(_Value, _Format, _Prec);
	return vValue;
}





// Standard enhancement function : stream <<
_XCOREAPI_ std::ostream& operator<< (std::ostream& _OStream, const xanadu::string& _String) noexcept
{
	for(auto vIndex = 0U; vIndex < _String.size(); ++vIndex)
	{
		_OStream << _String[vIndex];
	}
	return _OStream;
}

// Standard enhancement function : stream >>
_XCOREAPI_ std::istream& operator>> (std::istream& _IStream, xanadu::string& _String) noexcept
{
	_String.clear();
	do
	{
		auto		vChar = static_cast<xanadu::string::_Elem>(_IStream.get());
		if(vChar == '\n' || vChar == ' ')
		{
			break;
		}
		_String.append(vChar);
	} while(true);
	return _IStream;
}

// Standard enhancement function : getline
_XCOREAPI_ std::istream& getline(std::istream& _IStream, xanadu::string& _String, char _Delim) noexcept
{
	_String.clear();
	do
	{
		auto		vChar = static_cast<xanadu::string::_Elem>(_IStream.get());
		if(vChar == _Delim)
		{
			break;
		}
		_String.append(vChar);
	} while(true);
	return _IStream;
}

// Standard enhancement function : getline
_XCOREAPI_ std::istream& getline(std::istream& _IStream, xanadu::string& _String) noexcept
{
	return getline(_IStream, _String, '\n');
}
