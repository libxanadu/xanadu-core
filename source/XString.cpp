#include <xanadu-core/XString.h>
#include <xanadu-core/XBase64.h>



// constructor
XString::XString() noexcept = default;

// constructor
XString::XString(size_type _Length, elem_type _Char) noexcept : _Allocator(_Length, _Char)
{
}

// constructor
XString::XString(const elem_type* _Memory) noexcept : _Allocator(_Memory, x_posix_strlen(_Memory))
{
}

// constructor
XString::XString(const elem_type* _Memory, size_type _Length) noexcept : _Allocator(_Memory, _Length)
{
}

// constructor
XString::XString(const XString& _String) noexcept = default;

// constructor
XString::XString(XString&& _String) noexcept = default;

// destructor
XString::~XString() noexcept = default;





// operator overload =
XString& XString::operator = (const elem_type* _Memory) noexcept
{
	if(this->resize(x_posix_strlen(_Memory)))
	{
		x_posix_memcpy(this->data(), _Memory, this->size());
	}
	return *this;
}

// operator overload =
XString& XString::operator = (const XString& _String) noexcept
{
	if(this != &_String)
	{
		this->_Allocator = _String._Allocator;
	}
	return *this;
}

// operator overload =
XString& XString::operator = (XString&& _String) noexcept
{
	if(this != &_String)
	{
		this->_Allocator = _String._Allocator;
	}
	return *this;
}





// operator overload +=
XString& XString::operator += (elem_type _Char) noexcept
{
	elem_type		vBytes[2] = {_Char, '\0'};
	return this->append(vBytes, 1);
}

// operator overload +=
XString& XString::operator += (const elem_type* _String) noexcept
{
	return this->append(_String, x_posix_strlen(_String));
}

// operator overload +=
XString& XString::operator += (const XString& _String) noexcept
{
	return this->append(_String.data(), _String.size());
}





// operator overload +
XString XString::operator + (elem_type _Char) const noexcept
{
	auto		vTemp = *this;
	vTemp += _Char;
	return vTemp;
}

// operator overload +
XString XString::operator + (const elem_type* _String) const noexcept
{
	auto		vTemp = *this;
	vTemp += _String;
	return vTemp;
}

// operator overload +
XString XString::operator + (const XString& _String) const noexcept
{
	auto		vTemp = *this;
	vTemp += _String;
	return vTemp;
}





// operator overload ==
bool XString::operator == (elem_type _Char) const noexcept
{
	elem_type		vBytes[2] = {_Char, '\0'};
	return this->compare(vBytes, 1, Xs::CaseSensitive) == 0;
}

// operator overload ==
bool XString::operator == (const elem_type* _String) const noexcept
{
	return this->compare(_String, x_posix_strlen(_String), Xs::CaseSensitive) == 0;
}

// operator overload ==
bool XString::operator == (const XString& _String) const noexcept
{
	return this->compare(_String.data(), _String.size(), Xs::CaseSensitive) == 0;
}

// operator overload !=
bool XString::operator != (elem_type _Char) const noexcept
{
	elem_type		vBytes[2] = {_Char, '\0'};
	return this->compare(vBytes, 1, Xs::CaseSensitive) != 0;
}

// operator overload !=
bool XString::operator != (const elem_type* _String) const noexcept
{
	return this->compare(_String, x_posix_strlen(_String), Xs::CaseSensitive) != 0;
}

// operator overload !=
bool XString::operator != (const XString& _String) const noexcept
{
	return this->compare(_String.data(), _String.size(), Xs::CaseSensitive) != 0;
}

// operator overload <
bool XString::operator < (elem_type _Char) const noexcept
{
	elem_type		vBytes[2] = {_Char, '\0'};
	return this->compare(vBytes, 1, Xs::CaseSensitive) < 0;
}

// operator overload <
bool XString::operator < (const elem_type* _String) const noexcept
{
	return this->compare(_String, x_posix_strlen(_String), Xs::CaseSensitive) < 0;
}

// operator overload <
bool XString::operator < (const XString& _String) const noexcept
{
	return this->compare(_String.data(), _String.size(), Xs::CaseSensitive) < 0;
}

// operator overload >
bool XString::operator > (elem_type _Char) const noexcept
{
	elem_type		vBytes[2] = {_Char, '\0'};
	return this->compare(vBytes, 1, Xs::CaseSensitive) > 0;
}

// operator overload >
bool XString::operator > (const elem_type* _String) const noexcept
{
	return this->compare(_String, x_posix_strlen(_String), Xs::CaseSensitive) > 0;
}

// operator overload >
bool XString::operator > (const XString& _String) const noexcept
{
	return this->compare(_String.data(), _String.size(), Xs::CaseSensitive) > 0;
}

// operator overload <=
bool XString::operator <= (elem_type _Char) const noexcept
{
	elem_type		vBytes[2] = {_Char, '\0'};
	return this->compare(vBytes, 1, Xs::CaseSensitive) <= 0;
}

// operator overload <=
bool XString::operator <= (const elem_type* _String) const noexcept
{
	return this->compare(_String, x_posix_strlen(_String), Xs::CaseSensitive) <= 0;
}

// operator overload <=
bool XString::operator <= (const XString& _String) const noexcept
{
	return this->compare(_String.data(), _String.size(), Xs::CaseSensitive) <= 0;
}

// operator overload >=
bool XString::operator >= (elem_type _Char) const noexcept
{
	elem_type		vBytes[2] = {_Char, '\0'};
	return this->compare(vBytes, 1, Xs::CaseSensitive) >= 0;
}

// operator overload >=
bool XString::operator >= (const elem_type* _String) const noexcept
{
	return this->compare(_String, x_posix_strlen(_String), Xs::CaseSensitive) >= 0;
}

// operator overload >=
bool XString::operator >= (const XString& _String) const noexcept
{
	return this->compare(_String.data(), _String.size(), Xs::CaseSensitive) >= 0;
}





// operator overload []
XString::elem_type& XString::operator [] (pos_type _Index)
{
	return this->_Allocator[_Index];
}

// operator overload []
XString::elem_type XString::operator [] (pos_type _Index) const
{
	return this->_Allocator[_Index];
}





// [opt] clear
void XString::clear() noexcept
{
	this->_Allocator.clear();
}

// [opt] resize
bool XString::resize(size_type _Length) noexcept
{
	return this->_Allocator.resize(_Length);
}

// [opt] reverse
bool XString::reverse(size_type _Length) noexcept
{
	return this->_Allocator.reverse(_Length);
}





// [get] exist
bool XString::exist() const noexcept
{
	return this->_Allocator.exist();
}

// [get] empty
bool XString::empty() const noexcept
{
	return this->_Allocator.empty();
}

// [get] data
XString::elem_type* XString::data() noexcept
{
	return static_cast<XString::elem_type*>(this->_Allocator.data());
}

// [get] data
const XString::elem_type* XString::data() const noexcept
{
	return static_cast<const XString::elem_type*>(this->_Allocator.data());
}

// [get] size
XString::size_type XString::size() const noexcept
{
	return this->_Allocator.size();
}

// [get] capacity
XString::size_type XString::capacity() const noexcept
{
	return this->_Allocator.capacity();
}

// [get] surplus
XString::size_type XString::surplus() const noexcept
{
	return this->_Allocator.surplus();
}

// [get] max_size
XString::size_type XString::max_size() const noexcept
{
	return this->_Allocator.max_size();
}






// Truncates the subscript POS of the byte array. If POS goes beyond the end of the array, nothing happens.
void XString::truncate(size_type _Index) noexcept
{
	if (_Index < this->size())
	{
		this->resize(_Index);
	}
}

// Returns a string that has whitespace removed from the start and the end, and that has each sequence of internal whitespace replaced with a single space.
XString XString::simplified() const noexcept
{
	auto		vString = XString();
	auto		vNumber = 0;
	auto		vBegin = true;
	for(auto vIndex = 0ULL; vIndex < this->size(); ++vIndex)
	{
		if(XString::isSpace(this->data()[vIndex]))
		{
			++vNumber;
		}
		else
		{
			if(!vBegin)
			{
				if(vNumber)
				{
					vString.append(' ');
				}
			}
			vString.append(data()[vIndex]);

			vNumber = 0;
			vBegin = false;
		}
	}
	return vString;
}





// 从源中截取部分数据
XString XString::substr(pos_type _Pos) const noexcept
{
	return this->substr(_Pos, XString::npos);
}

// 从源中截取部分数据
XString XString::substr(pos_type _Pos, size_type _Length) const noexcept
{
	if(_Pos < this->size())
	{
		if(_Length == XString::npos)
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

// 从源中截取部分数据
XString XString::left(pos_type _Pos) const noexcept
{
	return this->substr(0, _Pos);
}

// 从源中截取部分数据
XString XString::right(pos_type _Pos) const noexcept
{
	return this->substr(this->size() - _Pos, XString::npos);
}





// [mid] 从源中截取部分数据
XString XString::mid(pos_type _Pos) const noexcept
{
	return this->mid(_Pos, XString::npos);
}

// [mid] 从源中截取部分数据
XString XString::mid(pos_type _Pos, size_type _Size) const noexcept
{
	return this->substr(_Pos, _Size);
}

// [mid] 从源中截取部分数据
XString XString::mid(const elem_type* _Left, const elem_type* _Right) const noexcept
{
	return this->mid(_Left, x_posix_strlen(_Left), _Right, x_posix_strlen(_Right), Xs::CaseSensitive);
}

// [mid] 从源中截取部分数据
XString XString::mid(const elem_type* _Left, const elem_type* _Right, Xs::CaseSensitivity _XCS) const noexcept
{
	return this->mid(_Left, x_posix_strlen(_Left), _Right, x_posix_strlen(_Right), _XCS);
}

// [mid] 从源中截取部分数据
XString XString::mid(const elem_type* _Left, size_type _LengthL, const elem_type* _Right, size_type _LengthR) const noexcept
{
	return this->mid(_Left, _LengthL, _Right, _LengthR, Xs::CaseSensitive);
}

// [mid] 从源中截取部分数据
XString XString::mid(const elem_type* _Left, size_type _LengthL, const elem_type* _Right, size_type _LengthR, Xs::CaseSensitivity _XCS) const noexcept
{
	pos_type 	vPosL = XString::npos;
	pos_type 	vPosR = XString::npos;

	if(_Left == nullptr || _Right == nullptr || _LengthL == 0 || _LengthR == 0)
	{
		return {};
	}

	vPosL = this->find(_Left, _LengthL, 0, _XCS);
	if(XString::npos != vPosL)
	{
		vPosL += _LengthL;
		vPosR = this->find(_Right, _LengthR, vPosL, _XCS);
		if(XString::npos != vPosR)
		{
			return this->substr(vPosL, vPosR - vPosL);
		}
	}
	return {};
}

// [mid] 从源中截取部分数据
XString XString::mid(const elem_type* _Left, const XString& _Right) const noexcept
{
	return this->mid(_Left, x_posix_strlen(_Left), _Right.data(), _Right.size(), Xs::CaseSensitive);
}

// [mid] 从源中截取部分数据
XString XString::mid(const elem_type* _Left, const XString& _Right, Xs::CaseSensitivity _XCS) const noexcept
{
	return this->mid(_Left, x_posix_strlen(_Left), _Right.data(), _Right.size(), _XCS);
}

// [mid] 从源中截取部分数据
XString XString::mid(const XString& _Left, const elem_type* _Right) const noexcept
{
	return this->mid(_Left.data(), _Left.size(), _Right, x_posix_strlen(_Right), Xs::CaseSensitive);
}

// [mid] 从源中截取部分数据
XString XString::mid(const XString& _Left, const elem_type* _Right, Xs::CaseSensitivity _XCS) const noexcept
{
	return this->mid(_Left.data(), _Left.size(), _Right, x_posix_strlen(_Right), _XCS);
}

// [mid] 从源中截取部分数据
XString XString::mid(const XString& _Left, const XString& _Right) const noexcept
{
	return this->mid(_Left.data(), _Left.size(), _Right.data(), _Right.size(), Xs::CaseSensitive);
}

// [mid] 从源中截取部分数据
XString XString::mid(const XString& _Left, const XString& _Right, Xs::CaseSensitivity _XCS) const noexcept
{
	return this->mid(_Left.data(), _Left.size(), _Right.data(), _Right.size(), _XCS);
}





// 检测源数据是否存在指定的前缀
bool XString::startsWith(elem_type _Char) const noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->startsWith(vBytes, 1, Xs::CaseSensitive);
}

// 检测源数据是否存在指定的前缀
bool XString::startsWith(elem_type _Char, Xs::CaseSensitivity _XCS) const noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->startsWith(vBytes, 1, _XCS);
}

// 检测源数据是否存在指定的前缀
bool XString::startsWith(const elem_type* _Memory) const noexcept
{
	return this->startsWith(_Memory, x_posix_strlen(_Memory), Xs::CaseSensitive);
}

// 检测源数据是否存在指定的前缀
bool XString::startsWith(const elem_type* _Memory, Xs::CaseSensitivity _XCS) const noexcept
{
	return this->startsWith(_Memory, x_posix_strlen(_Memory), _XCS);
}

// 检测源数据是否存在指定的前缀
bool XString::startsWith(const elem_type* _Memory, size_type _Length) const noexcept
{
	return this->startsWith(_Memory, _Length, Xs::CaseSensitive);
}

// 检测源数据是否存在指定的前缀
bool XString::startsWith(const elem_type* _Memory, size_type _Length, Xs::CaseSensitivity _XCS) const noexcept
{
	if(this->size() >= _Length)
	{
		return this->left(_Length).compare(_Memory, _Length, _XCS) == 0;
	}
	return false;
}

// 检测源数据是否存在指定的前缀
bool XString::startsWith(const XString& _String) const noexcept
{
	return this->startsWith(_String.data(), _String.size(), Xs::CaseSensitive);
}

// 检测源数据是否存在指定的前缀
bool XString::startsWith(const XString& _String, Xs::CaseSensitivity _XCS) const noexcept
{
	return this->startsWith(_String.data(), _String.size(), _XCS);
}





// 检测源数据是否存在指定的后缀
bool XString::endsWith(elem_type _Char) const noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->endsWith(vBytes, 1, Xs::CaseSensitive);
}

// 检测源数据是否存在指定的后缀
bool XString::endsWith(elem_type _Char, Xs::CaseSensitivity _XCS) const noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->endsWith(vBytes, 1, _XCS);
}

// 检测源数据是否存在指定的后缀
bool XString::endsWith(const elem_type* _Memory) const noexcept
{
	return this->endsWith(_Memory, x_posix_strlen(_Memory), Xs::CaseSensitive);
}

// 检测源数据是否存在指定的后缀
bool XString::endsWith(const elem_type* _Memory, Xs::CaseSensitivity _XCS) const noexcept
{
	return this->endsWith(_Memory, x_posix_strlen(_Memory), _XCS);
}

// 检测源数据是否存在指定的后缀
bool XString::endsWith(const elem_type* _Memory, size_type _Length) const noexcept
{
	return this->endsWith(_Memory, _Length, Xs::CaseSensitive);
}

// 检测源数据是否存在指定的后缀
bool XString::endsWith(const elem_type* _Memory, size_type _Length, Xs::CaseSensitivity _XCS) const noexcept
{
	if(this->size() >= _Length)
	{
		return this->right(_Length).compare(_Memory, _Length, _XCS) == 0;
	}
	return false;
}

// 检测源数据是否存在指定的后缀
bool XString::endsWith(const XString& _String) const noexcept
{
	return this->endsWith(_String.data(), _String.size(), Xs::CaseSensitive);
}

// 检测源数据是否存在指定的后缀
bool XString::endsWith(const XString& _String, Xs::CaseSensitivity _XCS) const noexcept
{
	return this->endsWith(_String.data(), _String.size(), _XCS);
}





// 从指定位置按正序查找数据
XString::pos_type XString::find(elem_type _Char) const noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->find(vBytes, 1, 0, Xs::CaseSensitive);
}

// 从指定位置按正序查找数据
XString::pos_type XString::find(elem_type _Char, Xs::CaseSensitivity _XCS) const noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->find(vBytes, 1, 0, _XCS);
}

// 从指定位置按正序查找数据
XString::pos_type XString::find(elem_type _Char, pos_type _Pos) const noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->find(vBytes, 1, _Pos, Xs::CaseSensitive);
}

// 从指定位置按正序查找数据
XString::pos_type XString::find(elem_type _Char, pos_type _Pos, Xs::CaseSensitivity _XCS) const noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->find(vBytes, 1, _Pos, _XCS);
}

// 从指定位置按正序查找数据
XString::pos_type XString::find(const elem_type* _String) const noexcept
{
	return this->find(_String, x_posix_strlen(_String), 0, Xs::CaseSensitive);
}

// 从指定位置按正序查找数据
XString::pos_type XString::find(const elem_type* _String, Xs::CaseSensitivity _XCS) const noexcept
{
	return this->find(_String, x_posix_strlen(_String), 0, _XCS);
}

// 从指定位置按正序查找数据
XString::pos_type XString::find(const elem_type* _String, pos_type _Pos) const noexcept
{
	return this->find(_String, x_posix_strlen(_String), _Pos, Xs::CaseSensitive);
}

// 从指定位置按正序查找数据
XString::pos_type XString::find(const elem_type* _String, pos_type _Pos, Xs::CaseSensitivity _XCS) const noexcept
{
	return this->find(_String, x_posix_strlen(_String), _Pos, _XCS);
}

// 从指定位置按正序查找数据
XString::pos_type XString::find(const elem_type* _String, size_type _Length, pos_type _Pos) const noexcept
{
	return this->find(_String, _Length, _Pos, Xs::CaseSensitive);
}

// 从指定位置按正序查找数据
XString::pos_type XString::find(const elem_type* _String, size_type _Length, pos_type _Pos, Xs::CaseSensitivity _XCS) const noexcept
{
	auto 		vFind = static_cast<const XString::elem_type*>(nullptr);

	if(_String == nullptr || _Length == 0 || (this->size() - _Pos) < _Length)
	{
		return XString::npos;
	}

	if(_XCS == Xs::CaseInsensitive)
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
	return XString::npos;
}

// 从指定位置按正序查找数据
XString::pos_type XString::find(const XString& _String) const noexcept
{
	return this->find(_String.data(), _String.size(), 0, Xs::CaseSensitive);
}

// 从指定位置按正序查找数据
XString::pos_type XString::find(const XString& _String, Xs::CaseSensitivity _XCS) const noexcept
{
	return this->find(_String.data(), _String.size(), 0, _XCS);
}

// 从指定位置按正序查找数据
XString::pos_type XString::find(const XString& _String, pos_type _Pos) const noexcept
{
	return this->find(_String.data(), _String.size(), _Pos, Xs::CaseSensitive);
}

// 从指定位置按正序查找数据
XString::pos_type XString::find(const XString& _String, pos_type _Pos, Xs::CaseSensitivity _XCS) const noexcept
{
	return this->find(_String.data(), _String.size(), _Pos, _XCS);
}





// 从指定位置按倒序查找数据
XString::pos_type XString::rfind(elem_type _Char) const noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->rfind(vBytes, 1, this->size() - 1, Xs::CaseSensitive);
}

// 从指定位置按倒序查找数据
XString::pos_type XString::rfind(elem_type _Char, Xs::CaseSensitivity _XCS) const noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->rfind(vBytes, 1, this->size() - 1, _XCS);
}

// 从指定位置按倒序查找数据
XString::pos_type XString::rfind(elem_type _Char, pos_type _Pos) const noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->rfind(vBytes, 1, _Pos, Xs::CaseSensitive);
}

// 从指定位置按倒序查找数据
XString::pos_type XString::rfind(elem_type _Char, pos_type _Pos, Xs::CaseSensitivity _XCS) const noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->rfind(vBytes, 1, _Pos, _XCS);
}

// 从指定位置按倒序查找数据
XString::pos_type XString::rfind(const elem_type* _String) const noexcept
{
	return  this->rfind(_String, x_posix_strlen(_String), this->size() - 1, Xs::CaseSensitive);
}

// 从指定位置按倒序查找数据
XString::pos_type XString::rfind(const elem_type* _String, Xs::CaseSensitivity _XCS) const noexcept
{
	return  this->rfind(_String, x_posix_strlen(_String), this->size() - 1, _XCS);
}

// 从指定位置按倒序查找数据
XString::pos_type XString::rfind(const elem_type* _String, pos_type _Pos) const noexcept
{
	return  this->rfind(_String, x_posix_strlen(_String), _Pos, Xs::CaseSensitive);
}

// 从指定位置按倒序查找数据
XString::pos_type XString::rfind(const elem_type* _String, pos_type _Pos, Xs::CaseSensitivity _XCS) const noexcept
{
	return  this->rfind(_String, x_posix_strlen(_String), _Pos, _XCS);
}

// 从指定位置按倒序查找数据
XString::pos_type XString::rfind(const elem_type* _String, size_type _Length, pos_type _Pos) const noexcept
{
	return this->rfind(_String, _Length, _Pos, Xs::CaseSensitive);
}

// 从指定位置按倒序查找数据
XString::pos_type XString::rfind(const elem_type* _String, size_type _Length, pos_type _Pos, Xs::CaseSensitivity _XCS) const noexcept
{
	auto 		vFind = static_cast<int>(1);

	if(_String == nullptr || _Length == 0 || this->size() < _Length)
	{
		return XString::npos;
	}

	for(; _Pos != XString::npos; --_Pos)
	{
		if(_XCS == Xs::CaseInsensitive)
		{
			vFind = x_posix_strnicmp(this->data() + _Pos, _String, _Length);
		}
		else
		{
			vFind = x_posix_strncmp(this->data() + _Pos, _String, _Length);
		}
		if(vFind == 0)
		{
			break;
		}
	}
	return _Pos;
}

// 从指定位置按倒序查找数据
XString::pos_type XString::rfind(const XString& _String) const noexcept
{
	return this->rfind(_String.data(), _String.size(), this->size() - 1, Xs::CaseSensitive);
}

// 从指定位置按倒序查找数据
XString::pos_type XString::rfind(const XString& _String, Xs::CaseSensitivity _XCS) const noexcept
{
	return this->rfind(_String.data(), _String.size(), this->size() - 1, _XCS);
}

// 从指定位置按倒序查找数据
XString::pos_type XString::rfind(const XString& _String, pos_type _Pos) const noexcept
{
	return this->rfind(_String.data(), _String.size(), _Pos, Xs::CaseSensitive);
}

// 从指定位置按倒序查找数据
XString::pos_type XString::rfind(const XString& _String, pos_type _Pos, Xs::CaseSensitivity _XCS) const noexcept
{
	return this->rfind(_String.data(), _String.size(), _Pos, _XCS);
}





// 检查是否包含指定数据
bool XString::contains(elem_type _Char) const noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->contains(vBytes, 1, Xs::CaseSensitive);
}

// 检查是否包含指定数据
bool XString::contains(elem_type _Char, Xs::CaseSensitivity _XCS) const noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->contains(vBytes, 1, _XCS);
}

// 检查是否包含指定数据
bool XString::contains(const elem_type* _String) const noexcept
{
	return this->contains(_String, x_posix_strlen(_String), Xs::CaseSensitive);
}

// 检查是否包含指定数据
bool XString::contains(const elem_type* _String, Xs::CaseSensitivity _XCS) const noexcept
{
	return this->contains(_String, x_posix_strlen(_String), _XCS);
}

// 检查是否包含指定数据
bool XString::contains(const elem_type* _String, size_type _Length) const noexcept
{
	return this->contains(_String, _Length, Xs::CaseSensitive);
}

// 检查是否包含指定数据
bool XString::contains(const elem_type* _String, size_type _Length, Xs::CaseSensitivity _XCS) const noexcept
{
	auto		vFind = this->find(_String, _Length, 0, _XCS);
	return vFind != XString::npos;
}

// 检查是否包含指定数据
bool XString::contains(const XString& _String) const noexcept
{
	return this->contains(_String.data(), _String.size(), Xs::CaseSensitive);
}

// 检查是否包含指定数据
bool XString::contains(const XString& _String, Xs::CaseSensitivity _XCS) const noexcept
{
	return this->contains(_String.data(), _String.size(), _XCS);
}





// 检查是否与指定数据相同
int XString::compare(elem_type _Char) const noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->compare(vBytes, 1, Xs::CaseSensitive);
}

// 检查是否与指定数据相同
int XString::compare(elem_type _Char, Xs::CaseSensitivity _XCS) const noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->compare(vBytes, 1, _XCS);
}

// 检查是否与指定数据相同
int XString::compare(const elem_type* _String) const noexcept
{
	return this->compare(_String, x_posix_strlen(_String), Xs::CaseSensitive);
}

// 检查是否与指定数据相同
int XString::compare(const elem_type* _String, Xs::CaseSensitivity _XCS) const noexcept
{
	return this->compare(_String, x_posix_strlen(_String), _XCS);
}

// 检查是否与指定数据相同
int XString::compare(const elem_type* _String, size_type _Length) const noexcept
{
	return this->compare(_String, _Length, Xs::CaseSensitive);
}

// 检查是否与指定数据相同
int XString::compare(const elem_type* _String, size_type _Length, Xs::CaseSensitivity _XCS) const noexcept
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
			if(_XCS == Xs::CaseInsensitive)
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
			if(_XCS == Xs::CaseInsensitive)
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
			if(_XCS == Xs::CaseInsensitive)
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

// 检查是否与指定数据相同
int XString::compare(const XString& _String) const noexcept
{
	return this->compare(_String.data(), _String.size(), Xs::CaseSensitive);
}

// 检查是否与指定数据相同
int XString::compare(const XString& _String, Xs::CaseSensitivity _XCS) const noexcept
{
	return this->compare(_String.data(), _String.size(), _XCS);
}





// 在头部插入数据
XString& XString::prepend(elem_type _Char) noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->prepend(vBytes, 1);
}

// 在头部插入数据
XString& XString::prepend(size_type _Count, elem_type _Char) noexcept
{
	return this->prepend({_Count, _Char});
}

// 在头部插入数据
XString& XString::prepend(const elem_type* _String) noexcept
{
	return this->prepend(_String, x_posix_strlen(_String));
}

// 在头部插入数据
XString& XString::prepend(const elem_type* _String, size_type _Size) noexcept
{
	return this->insert(0, _String, _Size);
}

// 在头部插入数据
XString& XString::prepend(const XString& _String) noexcept
{
	return this->prepend(_String.data(), _String.size());
}





// 在尾部添加数据
XString& XString::append(elem_type _Char) noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->append(vBytes, 1);
}

// 在尾部添加数据
XString& XString::append(size_type _Count, elem_type _Char) noexcept
{
	return this->append({_Count, _Char});
}

// 在尾部添加数据
XString& XString::append(const elem_type* _String) noexcept
{
	return this->append(_String, x_posix_strlen(_String));
}

// 在尾部添加数据
XString& XString::append(const elem_type* _String, size_type _Size) noexcept
{
	return this->insert(this->size(), _String, _Size);
}

// 在尾部添加数据
XString& XString::append(const XString& _String) noexcept
{
	return this->append(_String.data(), _String.size());
}





// 在指定下标处插入数据
XString& XString::insert(pos_type _Pos, elem_type _Char) noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->insert(_Pos, vBytes, 1);
}

// 在指定下标处插入数据
XString& XString::insert(pos_type _Pos, size_type _Count, elem_type _Char) noexcept
{
	auto		vString = XString(_Count, _Char);
	return this->insert(_Pos, vString.data(), vString.size());
}

// 在指定下标处插入数据
XString& XString::insert(pos_type _Pos, const elem_type* _String) noexcept
{
	return this->insert(_Pos, _String, x_posix_strlen(_String));
}

// 在指定下标处插入数据
XString& XString::insert(pos_type _Pos, const elem_type* _String, size_type _Length) noexcept
{
	this->_Allocator.insert(_Pos, _String, _Length);
	return *this;
}

// Inserts data from the specified location XString
XString& XString::insert(pos_type _Pos, const XString& _String) noexcept
{
	return this->insert(_Pos, _String.data(), _String.size());
}





// 移除下标 pos 处的 length 长度数据
XString& XString::remove(pos_type _Pos, size_type _Length) noexcept
{
	this->_Allocator.remove(_Pos, _Length);
	return *this;
}

// 删除与参数相同的数据
XString& XString::remove(elem_type _Char) noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->remove(vBytes, 1, Xs::CaseSensitive);
}

// 删除与参数相同的数据
XString& XString::remove(elem_type _Char, Xs::CaseSensitivity _XCS) noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->remove(vBytes, 1, _XCS);
}

// 删除与参数相同的数据
XString& XString::remove(const elem_type* _String) noexcept
{
	return this->remove(_String, x_posix_strlen(_String), Xs::CaseSensitive);
}

// 删除与参数相同的数据
XString& XString::remove(const elem_type* _String, Xs::CaseSensitivity _XCS) noexcept
{
	return this->remove(_String, x_posix_strlen(_String), _XCS);
}

// 删除与参数相同的数据
XString& XString::remove(const elem_type* _String, size_type _Length) noexcept
{
	return this->remove(_String, _Length, Xs::CaseSensitive);
}

// 删除与参数相同的数据
XString& XString::remove(const elem_type* _String, size_type _Length, Xs::CaseSensitivity _XCS) noexcept
{
	auto		vFind = this->find(_String, _Length, 0, _XCS);
	if(vFind != XString::npos)
	{
		return this->remove(vFind, _Length);
	}
	return *this;
}

// 删除与参数相同的数据
XString& XString::remove(const XString& _String) noexcept
{
	return this->remove(_String.data(), _String.size(), Xs::CaseSensitive);
}

// 删除与参数相同的数据
XString& XString::remove(const XString& _String, Xs::CaseSensitivity _XCS) noexcept
{
	return this->remove(_String.data(), _String.size(), _XCS);
}





// 替换数据
XString& XString::replace(pos_type _Pos, size_type _Length, elem_type _After) noexcept
{
	elem_type		vAfter[2] = { _After, '\0' };
	return this->replace(_Pos, _Length, vAfter, 1);
}

// 替换数据
XString& XString::replace(pos_type _Pos, size_type _Length, const elem_type* _After) noexcept
{
	return this->replace(_Pos, _Length, _After, x_posix_strlen(_After));
}

// 替换数据
XString& XString::replace(pos_type _Pos, size_type _Length, const elem_type* _After, size_type _LengthA) noexcept
{
	this->_Allocator.replace(_Pos, _Length, _After, _LengthA);
	return *this;
}

// 替换数据
XString& XString::replace(pos_type _Pos, size_type _Length, const XString& _After) noexcept
{
	return this->replace(_Pos, _Length, _After.data(), _After.size());
}





// 替换数据
XString& XString::replace(elem_type _Before, elem_type _After) noexcept
{
	elem_type		vBefore[2] = { _Before, '\0' };
	elem_type		vAfter[2] = { _After, '\0' };
	return this->replace(vBefore, 1, vAfter, 1, Xs::CaseSensitive);
}

// 替换数据
XString& XString::replace(elem_type _Before, elem_type _After, Xs::CaseSensitivity _XCS) noexcept
{
	elem_type		vBefore[2] = { _Before, '\0' };
	elem_type		vAfter[2] = { _After, '\0' };
	return this->replace(vBefore, 1, vAfter, 1, _XCS);
}

// 替换数据
XString& XString::replace(elem_type _Before, const elem_type* _After, size_type _LengthA) noexcept
{
	elem_type		vBefore[2] = { _Before, '\0' };
	return this->replace(vBefore, 1, _After, _LengthA, Xs::CaseSensitive);
}

// 替换数据
XString& XString::replace(elem_type _Before, const elem_type* _After, size_type _LengthA, Xs::CaseSensitivity _XCS) noexcept
{
	elem_type		vBefore[2] = { _Before, '\0' };
	return this->replace(vBefore, 1, _After, _LengthA, _XCS);
}

// 替换数据
XString& XString::replace(elem_type _Before, const XString& _After) noexcept
{
	elem_type		vBefore[2] = { _Before, '\0' };
	return this->replace(vBefore, 1, _After.data(), _After.size(), Xs::CaseSensitive);
}

// 替换数据
XString& XString::replace(elem_type _Before, const XString& _After, Xs::CaseSensitivity _XCS) noexcept
{
	elem_type		vBefore[2] = { _Before, '\0' };
	return this->replace(vBefore, 1, _After.data(), _After.size(), _XCS);
}





// 替换数据
XString& XString::replace(const elem_type* _Before, elem_type _After) noexcept
{
	elem_type		vAfter[2] = { _After, '\0' };
	return this->replace(_Before, x_posix_strlen(_Before), vAfter, 1, Xs::CaseSensitive);
}

// 替换数据
XString& XString::replace(const elem_type* _Before, elem_type _After, Xs::CaseSensitivity _XCS) noexcept
{
	elem_type		vAfter[2] = { _After, '\0' };
	return this->replace(_Before, x_posix_strlen(_Before), vAfter, 1, _XCS);
}

// 替换数据
XString& XString::replace(const elem_type* _Before, const elem_type* _After, size_type _LengthA) noexcept
{
	return this->replace(_Before, x_posix_strlen(_Before), _After, _LengthA, Xs::CaseSensitive);
}

// 替换数据
XString& XString::replace(const elem_type* _Before, const elem_type* _After, size_type _LengthA, Xs::CaseSensitivity _XCS) noexcept
{
	return this->replace(_Before, x_posix_strlen(_Before), _After, _LengthA, _XCS);
}

// 替换数据
XString& XString::replace(const elem_type* _Before, const XString& _After) noexcept
{
	return this->replace(_Before, x_posix_strlen(_Before), _After.data(), _After.size(), Xs::CaseSensitive);
}

// 替换数据
XString& XString::replace(const elem_type* _Before, const XString& _After, Xs::CaseSensitivity _XCS) noexcept
{
	return this->replace(_Before, x_posix_strlen(_Before), _After.data(), _After.size(), _XCS);
}





// 替换数据
XString& XString::replace(const elem_type* _Before, size_type _LengthB, elem_type _After) noexcept
{
	elem_type		vAfter[2] = { _After, '\0' };
	return this->replace(_Before, _LengthB, vAfter, 1, Xs::CaseSensitive);
}

// 替换数据
XString& XString::replace(const elem_type* _Before, size_type _LengthB, elem_type _After, Xs::CaseSensitivity _XCS) noexcept
{
	elem_type		vAfter[2] = { _After, '\0' };
	return this->replace(_Before, _LengthB, vAfter, 1, _XCS);
}

// 替换数据
XString& XString::replace(const elem_type* _Before, size_type _LengthB, const elem_type* _After, size_type _LengthA) noexcept
{
	return this->replace(_Before, _LengthB, _After, _LengthA, Xs::CaseSensitive);
}

// 替换数据
XString& XString::replace(const elem_type* _Before, size_type _LengthB, const elem_type* _After, size_type _LengthA, Xs::CaseSensitivity _XCS) noexcept
{
	pos_type	vPos = XString::npos;
	do
	{
		vPos = this->find(_Before, _LengthB, vPos, _XCS);
		if(XString::npos != vPos)
		{
			this->replace(vPos, _LengthB, _After, _LengthA);
			vPos += _LengthA;
		}
	} while(XString::npos != vPos);
	return *this;
}

// 替换数据
XString& XString::replace(const elem_type* _Before, size_type _LengthB, const XString& _After) noexcept
{
	return this->replace(_Before, _LengthB, _After.data(), _After.size(), Xs::CaseSensitive);
}

// 替换数据
XString& XString::replace(const elem_type* _Before, size_type _LengthB, const XString& _After, Xs::CaseSensitivity _XCS) noexcept
{
	return this->replace(_Before, _LengthB, _After.data(), _After.size(), _XCS);
}





// 替换数据
XString& XString::replace(const XString& _Before, elem_type _After) noexcept
{
	elem_type		vAfter[2] = { _After, '\0' };
	return this->replace(_Before.data(), _Before.size(), vAfter, 1, Xs::CaseSensitive);
}

// 替换数据
XString& XString::replace(const XString& _Before, elem_type _After, Xs::CaseSensitivity _XCS) noexcept
{
	elem_type		vAfter[2] = { _After, '\0' };
	return this->replace(_Before.data(), _Before.size(), vAfter, 1, _XCS);
}

// 替换数据
XString& XString::replace(const XString& _Before, const elem_type* _After, size_type _LengthA) noexcept
{
	return this->replace(_Before.data(), _Before.size(), _After, _LengthA, Xs::CaseSensitive);
}

// 替换数据
XString& XString::replace(const XString& _Before, const elem_type* _After, size_type _LengthA, Xs::CaseSensitivity _XCS) noexcept
{
	return this->replace(_Before.data(), _Before.size(), _After, _LengthA, _XCS);
}

// 替换数据
XString& XString::replace(const XString& _Before, const XString& _After) noexcept
{
	return this->replace(_Before.data(), _Before.size(), _After.data(), _After.size(), Xs::CaseSensitive);
}

// 替换数据
XString& XString::replace(const XString& _Before, const XString& _After, Xs::CaseSensitivity _XCS) noexcept
{
	return this->replace(_Before.data(), _Before.size(), _After.data(), _After.size(), _XCS);
}





// 按指定数据拆分字符串
std::list<XString> XString::split(elem_type _Char) const noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->split(vBytes, 1);
}

// 按指定数据拆分字符串
std::list<XString> XString::split(const elem_type* _Memory) const noexcept
{
	return this->split({_Memory, x_posix_strlen(_Memory)});
}

// 按指定数据拆分字符串
std::list<XString> XString::split(const elem_type* _Memory, size_type _Size) const noexcept
{
	return this->split({_Memory, _Size});
}

// 按指定数据拆分字符串
std::list<XString> XString::split(const XString& _String) const noexcept
{
	auto		vHeaderArray = std::list<XString>();
	auto		vLast = static_cast<size_type>(0U);
	auto		vSplitIndex = this->find(_String, vLast);
	while(vSplitIndex != XString::npos && _String.exist())
	{
		vHeaderArray.push_back(this->mid(vLast, vSplitIndex - vLast));
		vLast = vSplitIndex + 2;
		vSplitIndex = this->find(_String, vLast);
	}
	vHeaderArray.push_back(this->mid(vLast));

	return vHeaderArray;
}





// Determine whether a character is a blank character, Same as iswspace.
bool XString::isSpace(elem_type _Char) noexcept
{
	// Non-zero value if the wide character is a whitespace character, zero otherwise.
	return std::isspace(_Char);
}

// Format string (char* [%s]) (wchar_t* [%ls])
XString XString::format(const char* _Format, ...) noexcept
{
	auto		vString = XString();
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
XString XString::toUpper() const noexcept
{
	auto		vStrUpper = *this;
	for(pos_type vIndex = 0; vIndex < vStrUpper.size(); ++vIndex)
	{
		vStrUpper[vIndex] = (elem_type)std::toupper(vStrUpper[vIndex]);
	}
	return vStrUpper;
}

// [conv] 转换至小写
XString XString::toLower() const noexcept
{
	auto		vStrUpper = *this;
	for(pos_type vIndex = 0; vIndex < vStrUpper.size(); ++vIndex)
	{
		vStrUpper[vIndex] = (elem_type)std::tolower(vStrUpper[vIndex]);
	}
	return vStrUpper;
}





// [conv] convert to base64
XString XString::toBase64() const noexcept
{
	auto		vBytes = XBase64::encode(this->data(), this->size());
	return {vBytes.data(), vBytes.size()};
}

// [conv] convert from base64
XString XString::fromBase64(const elem_type* _String, size_type _Size) noexcept
{
	auto		vBytes = XBase64::decode(_String, _Size);
	return {vBytes.data(), vBytes.size()};
}

// [conv] convert from base64
XString XString::fromBase64(const XString& _Base64) noexcept
{
	return XString::fromBase64(_Base64.data(), _Base64.size());
}





// [conv] 转换至AString
AString XString::toAString() const noexcept
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
XString XString::fromAString(const char* _AString) noexcept
{
	return XString({_AString, x_posix_strlen(_AString)});
}

// [conv] 从AString转换
XString XString::fromAString(const AString& _AString) noexcept
{
	auto		vString = WString();
	auto		vChangeStr = x_posix_stratow(_AString.data());
	if(vChangeStr)
	{
		vString = vChangeStr;
		x_posix_free(vChangeStr);
	}
	return XString::fromWString(vString);
}





// [conv] 转换至WString
WString XString::toWString() const noexcept
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
XString XString::fromWString(const wchar_t* _WString) noexcept
{
	return XString::fromWString({_WString, x_posix_wcslen(_WString)});
}

// [conv] 从WString转换
XString XString::fromWString(const WString& _WString) noexcept
{
	auto		vString = XString();
	auto		vChangeStr = x_posix_strwtou(_WString.data());
	if(vChangeStr)
	{
		vString = vChangeStr;
		x_posix_free(vChangeStr);
	}
	return vString;
}





// [conv] 转换至UString
UString XString::toUString() const noexcept
{
	return {this->data(), this->size()};
}

// [conv] 从UString转换
XString XString::fromUString(const char* _UString) noexcept
{
	return XString({_UString, x_posix_strlen(_UString)});
}

// [conv] 从UString转换
XString XString::fromUString(const UString& _UString) noexcept
{
	return {_UString.data(), _UString.size()};
}





// [conv] 转换至NString (Windows: ASCII / 其它: UTF-8)
NString XString::toNString() const noexcept
{
#if defined(XANADU_SYSTEM_WINDOWS)
	return this->toAString();
#else
	return this->toUString();
#endif
}

// [conv] 从NString转换 (Windows: ASCII / 其它: UTF-8)
XString XString::fromNString(const char* _NString) noexcept
{
	return XString({_NString, x_posix_strlen(_NString)});
}

// [conv] 从NString转换 (Windows: ASCII / 其它: UTF-8)
XString XString::fromNString(const NString& _NString) noexcept
{
#if defined(XANADU_SYSTEM_WINDOWS)
	return XString::fromAString(_NString);
#else
	return XString::fromUString(_NString);
#endif
}





// [conv] 转换至HEX
XString XString::toHex() const noexcept
{
	auto		vTarget = XString(this->size() * 2, '0');
	for (auto vIndex = 0U; vIndex < this->size(); ++vIndex)
	{
		x_posix_sprintf(vTarget.data() + (vIndex * 2), "%02X", (std::uint8_t)this->data()[vIndex]);
	}
	return vTarget;
}

// [conv] 从HEX转换
XString XString::fromHex(const elem_type* _Hex) noexcept
{
	return XString::fromHex(_Hex, x_posix_strlen(_Hex));
}

// [conv] 从HEX转换
XString XString::fromHex(const elem_type* _Hex, size_type _Size) noexcept
{
	if (_Hex == nullptr || _Size == 0)
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
	auto		vBuffer = _Hex;
	auto		vLength = _Size / 2;
	auto		vTarget = XString(vLength, '\0');

	for (auto vIndex = 0U; vIndex < vLength; ++vIndex)
	{
		auto		vHexLeft = vFunctionHexToChar(vBuffer[vIndex * 2 + 0]);
		auto		vHexRight = vFunctionHexToChar(vBuffer[vIndex * 2 + 1]);
		vTarget[vIndex] = static_cast<char>(vHexLeft * 16 + vHexRight);
	}
	return vTarget;
}

// [conv] 从HEX转换
XString XString::fromHex(const XString& _Hex) noexcept
{
	return XString::fromHex(_Hex.data(), _Hex.size());
}








// [conv] convert to UTF-8 encoded byte array
XByteArray XString::toBytes() const noexcept
{
	return {this->data(), this->size()};
}

// [conv] convert from byte array
XString XString::fromBytes(const XByteArray& _Bytes) noexcept
{
	return {_Bytes.data(), _Bytes.size()};
}





// [conv] convert to UTF-8 encoded url
XString XString::toUrl() const noexcept
{
	auto		vDecode = toUString();
	auto		vEncode = XString();
	for(char vChar : vDecode)
	{
		if(((vChar >= 'A') && (vChar <= 'Z')) || ((vChar >= 'a') && (vChar <= 'z')) || ((vChar >= '0') && (vChar <= '9')))
		{
			vEncode.append(1, vChar);
		}
		else if(vChar == ' ')
		{
			vEncode.append("%20");
		}
		else if(vChar == '.' || vChar == '-' || vChar == '_' || vChar == '*' || vChar == ':' || vChar == '/' || vChar == ',')
		{
			vEncode.append(1, vChar);
		}
		else if(vChar == '&' || vChar == '?' || vChar == '=')
		{
			vEncode.append(1, vChar);
		}
		else
		{
			char	_Buffer[16] = { 0 };
			sprintf(_Buffer, "%%%02X", (unsigned char)vChar);
			vEncode.append(_Buffer);
		}
	}
	return vEncode;
}

// [conv] convert from UTF-8 encoded url
XString XString::fromUrl(const XString& _URL) noexcept
{
	auto		vEncode = _URL.toUString();
	auto		vDecode = XString();

	auto		Function_Hex2Num = [](char _Char)->int
	{
		if(_Char >= '0' && _Char <= '9')
		{
			return _Char - '0';
		}
		if(_Char >= 'a' && _Char <= 'z')
		{
			return _Char - 'a' + 10;
		}
		if(_Char >= 'A' && _Char <= 'Z')
		{
			return _Char - 'A' + 10;
		}
		return '0';
	};

	for(auto vIterator = vEncode.begin(); vIterator != vEncode.end(); ++vIterator)
	{
		auto	_Char = (*vIterator);
		switch(_Char)
		{
			case '%':
				if((vIterator + 2) != vEncode.end())
				{
					auto	_Char1 = Function_Hex2Num(*(vIterator + 1));
					auto	_Char2 = Function_Hex2Num(*(vIterator + 2));
					if((_Char1 != '0') && (_Char2 != '0'))
					{
						vDecode.append(1, (char)((_Char1 << 4) | _Char2));
					}
					vIterator += 2;
				}
				break;
			default:
				vDecode.append(1, _Char);
				break;
		}
	}
	return vDecode;
}





// [convert] convert to char
char XString::toChar(bool* _Ok, int _Base) const noexcept
{
	return static_cast<char>(this->toLLong(_Ok, _Base));
}

// [convert] convert to unsigned char
unsigned char XString::toUChar(bool* _Ok, int _Base) const noexcept
{
	return static_cast<unsigned char>(this->toULLong(_Ok, _Base));
}

// [convert] convert to short
short XString::toShort(bool* _Ok, int _Base) const noexcept
{
	return static_cast<short>(this->toLLong(_Ok, _Base));
}

// [convert] convert to short
unsigned short XString::toUShort(bool* _Ok, int _Base) const noexcept
{
	return static_cast<unsigned short>(this->toULLong(_Ok, _Base));
}

// [convert] convert to int
int XString::toInt(bool* _Ok, int _Base) const noexcept
{
	return static_cast<int>(this->toLLong(_Ok, _Base));
}

// [convert] convert to unsigned int
unsigned int XString::toUInt(bool* _Ok, int _Base) const noexcept
{
	return static_cast<unsigned int>(this->toULLong(_Ok, _Base));
}

// [convert] convert to long
long XString::toLong(bool* _Ok, int _Base) const noexcept
{
	return static_cast<long>(this->toLLong(_Ok, _Base));
}

// [convert] convert to unsigned long
unsigned long XString::toULong(bool* _Ok, int _Base) const noexcept
{
	return static_cast<unsigned long>(this->toULLong(_Ok, _Base));
}

// [convert] convert to long long
long long XString::toLLong(bool* _Ok, int _Base) const noexcept
{
	auto		vEnd = static_cast<elem_type*>(nullptr);
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
unsigned long long XString::toULLong(bool* _Ok, int _Base) const noexcept
{
	auto		vEnd = static_cast<elem_type*>(nullptr);
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
float XString::toFloat(bool* _Ok) const noexcept
{
	auto		vEnd = static_cast<elem_type*>(nullptr);
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
double XString::toDouble(bool* _Ok) const noexcept
{
	auto		vEnd = static_cast<elem_type*>(nullptr);
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
XString& XString::setNumber(char _Value, int _Base) noexcept
{
	this->setNumber(static_cast<long long>(_Value), _Base);
	return *this;
}

// [convert] convert from number
XString& XString::setNumber(unsigned char _Value, int _Base) noexcept
{
	this->setNumber(static_cast<unsigned long long>(_Value), _Base);
	return *this;
}

// [convert] convert from number
XString& XString::setNumber(short _Value, int _Base) noexcept
{
	this->setNumber(static_cast<long long>(_Value), _Base);
	return *this;
}

// [convert] convert from number
XString& XString::setNumber(unsigned short _Value, int _Base) noexcept
{
	this->setNumber(static_cast<unsigned long long>(_Value), _Base);
	return *this;
}

// [convert] convert from number
XString& XString::setNumber(int _Value, int _Base) noexcept
{
	this->setNumber(static_cast<long long>(_Value), _Base);
	return *this;
}

// [convert] convert from number
XString& XString::setNumber(unsigned int _Value, int _Base) noexcept
{
	this->setNumber(static_cast<unsigned long long>(_Value), _Base);
	return *this;
}

// [convert] convert from number
XString& XString::setNumber(long _Value, int _Base) noexcept
{
	this->setNumber(static_cast<long long>(_Value), _Base);
	return *this;
}

// [convert] convert from number
XString& XString::setNumber(unsigned long _Value, int _Base) noexcept
{
	this->setNumber(static_cast<unsigned long long>(_Value), _Base);
	return *this;
}

// [convert] convert from number
XString& XString::setNumber(long long _Value, int _Base) noexcept
{
	if(2 <= _Base && _Base <= 36)
	{
		*this = std::to_string(_Value).data();
	}
	return *this;
}

// [convert] convert from number
XString& XString::setNumber(unsigned long long _Value, int _Base) noexcept
{
	if(2 <= _Base && _Base <= 36)
	{
		*this = std::to_string(_Value).data();
	}
	return *this;
}

// [convert] convert from number
XString& XString::setNumber(float _Value, char _Format, int _Prec) noexcept
{
	XANADU_UNUSED(_Format);
	XANADU_UNUSED(_Prec);

	*this = std::to_string(_Value).data();
	return *this;
}

// [convert] convert from number
XString& XString::setNumber(double _Value, char _Format, int _Prec) noexcept
{
	XANADU_UNUSED(_Format);
	XANADU_UNUSED(_Prec);

	*this = std::to_string(_Value).data();
	return *this;
}





// [convert] convert from number
XString XString::number(char _Value, int _Base) noexcept
{
	auto		vValue = XString();
	vValue.setNumber(_Value, _Base);
	return vValue;
}

// [convert] convert from number
XString XString::number(unsigned char _Value, int _Base) noexcept
{
	auto		vValue = XString();
	vValue.setNumber(_Value, _Base);
	return vValue;
}

// [convert] convert from number
XString XString::number(short _Value, int _Base) noexcept
{
	auto		vValue = XString();
	vValue.setNumber(_Value, _Base);
	return vValue;
}

// [convert] convert from number
XString XString::number(unsigned short _Value, int _Base) noexcept
{
	auto		vValue = XString();
	vValue.setNumber(_Value, _Base);
	return vValue;
}

// [convert] convert from number
XString XString::number(int _Value, int _Base) noexcept
{
	auto		vValue = XString();
	vValue.setNumber(_Value, _Base);
	return vValue;
}

// [convert] convert from number
XString XString::number(unsigned int _Value, int _Base) noexcept
{
	auto		vValue = XString();
	vValue.setNumber(_Value, _Base);
	return vValue;
}

// [convert] convert from number
XString XString::number(long _Value, int _Base) noexcept
{
	auto		vValue = XString();
	vValue.setNumber(_Value, _Base);
	return vValue;
}

// [convert] convert from number
XString XString::number(unsigned long _Value, int _Base) noexcept
{
	auto		vValue = XString();
	vValue.setNumber(_Value, _Base);
	return vValue;
}

// [convert] convert from number
XString XString::number(long long _Value, int _Base) noexcept
{
	auto		vValue = XString();
	vValue.setNumber(_Value, _Base);
	return vValue;
}

// [convert] convert from number
XString XString::number(unsigned long long _Value, int _Base) noexcept
{
	auto		vValue = XString();
	vValue.setNumber(_Value, _Base);
	return vValue;
}

// [convert] convert from number
XString XString::number(float _Value, char _Format, int _Prec) noexcept
{
	auto		vValue = XString();
	vValue.setNumber(_Value, _Format, _Prec);
	return vValue;
}

// [convert] convert from number
XString XString::number(double _Value, char _Format, int _Prec) noexcept
{
	auto		vValue = XString();
	vValue.setNumber(_Value, _Format, _Prec);
	return vValue;
}





// Standard enhancement function : stream <<
_XCOREAPI_ std::ostream& operator<< (std::ostream& _OStream, const XString& _String) noexcept
{
	for(auto vIndex = 0U; vIndex < _String.size(); ++vIndex)
	{
		_OStream << _String[vIndex];
	}
	return _OStream;
}

// Standard enhancement function : stream >>
_XCOREAPI_ std::istream& operator>> (std::istream& _IStream, XString& _String) noexcept
{
	_String.clear();
	do
	{
		auto		vChar = static_cast<XString::elem_type>(_IStream.get());
		if(vChar == '\n' || vChar == ' ')
		{
			break;
		}
		_String.append(vChar);
	} while(true);
	return _IStream;
}

// Standard enhancement function : getline
_XCOREAPI_ std::istream& getline(std::istream& _IStream, XString& _String, char _Delim) noexcept
{
	_String.clear();
	do
	{
		auto		vChar = static_cast<XString::elem_type>(_IStream.get());
		if(vChar == _Delim)
		{
			break;
		}
		_String.append(vChar);
	} while(true);
	return _IStream;
}

// Standard enhancement function : getline
_XCOREAPI_ std::istream& getline(std::istream& _IStream, XString& _String) noexcept
{
	return getline(_IStream, _String, '\n');
}
