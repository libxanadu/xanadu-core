#include <xanadu-core/string.h> // NOLINT(modernize-deprecated-headers)
#include <cstdarg>



// constructor
x::string::string() noexcept = default;

// constructor
x::string::string(size_type _Length, elem_type _Char) noexcept : _Allocator(_Length, _Char)
{
}

// constructor
x::string::string(const elem_type* _Memory) noexcept : _Allocator(_Memory, x_posix_strlen(_Memory))
{
}

// constructor
x::string::string(const elem_type* _Memory, size_type _Length) noexcept : _Allocator(_Memory, _Length)
{
}

// constructor
x::string::string(const std::string& _StdStr) noexcept : _Allocator(_StdStr.data(), _StdStr.size())
{
}

// constructor
x::string::string(const x::string& _String) noexcept = default;

// constructor
x::string::string(x::string&& _String) noexcept = default;

// destructor
x::string::~string() noexcept = default;





// operator overload =
x::string& x::string::operator = (const elem_type* _Memory) noexcept
{
	if(this->resize(x_posix_strlen(_Memory)))
	{
		x_posix_memcpy(this->data(), _Memory, this->size());
	}
	return *this;
}

// operator overload =
x::string& x::string::operator = (const std::string& _String) noexcept
{
	if(this->resize(_String.size()))
	{
		x_posix_memcpy(this->data(), _String.data(), this->size());
	}
	return *this;
}

// operator overload =
x::string& x::string::operator = (const x::string& _String) noexcept
{
	if(this != &_String)
	{
		this->_Allocator = _String._Allocator;
	}
	return *this;
}

// operator overload =
x::string& x::string::operator = (x::string&& _String) noexcept
{
	if(this != &_String)
	{
		this->_Allocator = _String._Allocator;
	}
	return *this;
}





// operator overload +=
x::string& x::string::operator += (elem_type _Char) noexcept
{
	elem_type		vBytes[2] = {_Char, '\0'};
	return this->append(vBytes, 1);
}

// operator overload +=
x::string& x::string::operator += (const elem_type* _String) noexcept
{
	return this->append(_String, x_posix_strlen(_String));
}

// operator overload +=
x::string& x::string::operator += (const std::string& _String) noexcept
{
	return this->append(_String.data(), _String.size());
}

// operator overload +=
x::string& x::string::operator += (const x::string& _String) noexcept
{
	return this->append(_String.data(), _String.size());
}





// operator overload +
x::string x::string::operator + (elem_type _Char) const noexcept
{
	auto		vTemp = *this;
	vTemp += _Char;
	return vTemp;
}

// operator overload +
x::string x::string::operator + (const elem_type* _String) const noexcept
{
	auto		vTemp = *this;
	vTemp += _String;
	return vTemp;
}

// operator overload +
x::string x::string::operator + (const std::string& _String) const noexcept
{
	auto		vTemp = *this;
	vTemp += _String;
	return vTemp;
}

// operator overload +
x::string x::string::operator + (const x::string& _String) const noexcept
{
	auto		vTemp = *this;
	vTemp += _String;
	return vTemp;
}





// operator overload ==
bool x::string::operator == (elem_type _Char) const noexcept
{
	elem_type		vBytes[2] = {_Char, '\0'};
	return this->compare(vBytes, 1, x::CaseSensitive) == 0;
}

// operator overload ==
bool x::string::operator == (const elem_type* _String) const noexcept
{
	return this->compare(_String, x_posix_strlen(_String), x::CaseSensitive) == 0;
}

// operator overload ==
bool x::string::operator == (const x::string& _String) const noexcept
{
	return this->compare(_String.data(), _String.size(), x::CaseSensitive) == 0;
}

// operator overload !=
bool x::string::operator != (elem_type _Char) const noexcept
{
	elem_type		vBytes[2] = {_Char, '\0'};
	return this->compare(vBytes, 1, x::CaseSensitive) != 0;
}

// operator overload !=
bool x::string::operator != (const elem_type* _String) const noexcept
{
	return this->compare(_String, x_posix_strlen(_String), x::CaseSensitive) != 0;
}

// operator overload !=
bool x::string::operator != (const x::string& _String) const noexcept
{
	return this->compare(_String.data(), _String.size(), x::CaseSensitive) != 0;
}

// operator overload <
bool x::string::operator < (elem_type _Char) const noexcept
{
	elem_type		vBytes[2] = {_Char, '\0'};
	return this->compare(vBytes, 1, x::CaseSensitive) < 0;
}

// operator overload <
bool x::string::operator < (const elem_type* _String) const noexcept
{
	return this->compare(_String, x_posix_strlen(_String), x::CaseSensitive) < 0;
}

// operator overload <
bool x::string::operator < (const x::string& _String) const noexcept
{
	return this->compare(_String.data(), _String.size(), x::CaseSensitive) < 0;
}

// operator overload >
bool x::string::operator > (elem_type _Char) const noexcept
{
	elem_type		vBytes[2] = {_Char, '\0'};
	return this->compare(vBytes, 1, x::CaseSensitive) > 0;
}

// operator overload >
bool x::string::operator > (const elem_type* _String) const noexcept
{
	return this->compare(_String, x_posix_strlen(_String), x::CaseSensitive) > 0;
}

// operator overload >
bool x::string::operator > (const x::string& _String) const noexcept
{
	return this->compare(_String.data(), _String.size(), x::CaseSensitive) > 0;
}

// operator overload <=
bool x::string::operator <= (elem_type _Char) const noexcept
{
	elem_type		vBytes[2] = {_Char, '\0'};
	return this->compare(vBytes, 1, x::CaseSensitive) <= 0;
}

// operator overload <=
bool x::string::operator <= (const elem_type* _String) const noexcept
{
	return this->compare(_String, x_posix_strlen(_String), x::CaseSensitive) <= 0;
}

// operator overload <=
bool x::string::operator <= (const x::string& _String) const noexcept
{
	return this->compare(_String.data(), _String.size(), x::CaseSensitive) <= 0;
}

// operator overload >=
bool x::string::operator >= (elem_type _Char) const noexcept
{
	elem_type		vBytes[2] = {_Char, '\0'};
	return this->compare(vBytes, 1, x::CaseSensitive) >= 0;
}

// operator overload >=
bool x::string::operator >= (const elem_type* _String) const noexcept
{
	return this->compare(_String, x_posix_strlen(_String), x::CaseSensitive) >= 0;
}

// operator overload >=
bool x::string::operator >= (const x::string& _String) const noexcept
{
	return this->compare(_String.data(), _String.size(), x::CaseSensitive) >= 0;
}





// operator overload []
x::string::elem_type& x::string::operator [] (pos_type _Index)
{
	return this->_Allocator[_Index];
}

// operator overload []
x::string::elem_type x::string::operator [] (pos_type _Index) const
{
	return this->_Allocator[_Index];
}





// [opt] clear
void x::string::clear() noexcept
{
	this->_Allocator.clear();
}

// [opt] resize
bool x::string::resize(size_type _Length) noexcept
{
	return this->_Allocator.resize(_Length);
}

// [opt] reverse
bool x::string::reverse(size_type _Length) noexcept
{
	return this->_Allocator.reverse(_Length);
}





// [get] exist
bool x::string::exist() const noexcept
{
	return this->_Allocator.exist();
}

// [get] empty
bool x::string::empty() const noexcept
{
	return this->_Allocator.empty();
}

// [get] data
x::string::elem_type* x::string::data() noexcept
{
	return static_cast<x::string::elem_type*>(this->_Allocator.data());
}

// [get] data
const x::string::elem_type* x::string::data() const noexcept
{
	return static_cast<const x::string::elem_type*>(this->_Allocator.data());
}

// [get] size
x::string::size_type x::string::size() const noexcept
{
	return this->_Allocator.size();
}

// [get] capacity
x::string::size_type x::string::capacity() const noexcept
{
	return this->_Allocator.capacity();
}

// [get] surplus
x::string::size_type x::string::surplus() const noexcept
{
	return this->_Allocator.surplus();
}

// [get] max_size
x::string::size_type x::string::max_size() const noexcept
{
	return this->_Allocator.max_size();
}





// 从源中截取部分数据
x::string x::string::substr(pos_type _Pos) const noexcept
{
	return this->substr(_Pos, x::string::npos);
}

// 从源中截取部分数据
x::string x::string::substr(pos_type _Pos, size_type _Length) const noexcept
{
	if(_Pos < this->size())
	{
		if(_Length == x::string::npos)
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
x::string x::string::left(pos_type _Pos) const noexcept
{
	return this->substr(0, _Pos);
}

// 从源中截取部分数据
x::string x::string::right(pos_type _Pos) const noexcept
{
	return this->substr(this->size() - _Pos, x::string::npos);
}





// [mid] 从源中截取部分数据
x::string x::string::mid(pos_type _Pos) const noexcept
{
	return this->mid(_Pos, x::string::npos);
}

// [mid] 从源中截取部分数据
x::string x::string::mid(pos_type _Pos, size_type _Size) const noexcept
{
	return this->substr(_Pos, _Size);
}

// [mid] 从源中截取部分数据
x::string x::string::mid(const elem_type* _Left, const elem_type* _Right) const noexcept
{
	return this->mid(_Left, x_posix_strlen(_Left), _Right, x_posix_strlen(_Right), x::CaseSensitive);
}

// [mid] 从源中截取部分数据
x::string x::string::mid(const elem_type* _Left, const elem_type* _Right, x::CaseSensitivity _XCS) const noexcept
{
	return this->mid(_Left, x_posix_strlen(_Left), _Right, x_posix_strlen(_Right), _XCS);
}

// [mid] 从源中截取部分数据
x::string x::string::mid(const elem_type* _Left, size_type _LengthL, const elem_type* _Right, size_type _LengthR) const noexcept
{
	return this->mid(_Left, _LengthL, _Right, _LengthR, x::CaseSensitive);
}

// [mid] 从源中截取部分数据
x::string x::string::mid(const elem_type* _Left, size_type _LengthL, const elem_type* _Right, size_type _LengthR, x::CaseSensitivity _XCS) const noexcept
{
	pos_type 	vPosL = x::string::npos;
	pos_type 	vPosR = x::string::npos;

	if(_Left == nullptr || _Right == nullptr || _LengthL == 0 || _LengthR == 0)
	{
		return {};
	}

	vPosL = this->find(_Left, _LengthL, 0, _XCS);
	if(x::string::npos != vPosL)
	{
		vPosL += _LengthL;
		vPosR = this->find(_Right, _LengthR, vPosL, _XCS);
		if(x::string::npos != vPosR)
		{
			return this->substr(vPosL, vPosR - vPosL);
		}
	}
	return {};
}

// [mid] 从源中截取部分数据
x::string x::string::mid(const elem_type* _Left, const x::string& _Right) const noexcept
{
	return this->mid(_Left, x_posix_strlen(_Left), _Right.data(), _Right.size(), x::CaseSensitive);
}

// [mid] 从源中截取部分数据
x::string x::string::mid(const elem_type* _Left, const x::string& _Right, x::CaseSensitivity _XCS) const noexcept
{
	return this->mid(_Left, x_posix_strlen(_Left), _Right.data(), _Right.size(), _XCS);
}

// [mid] 从源中截取部分数据
x::string x::string::mid(const x::string& _Left, const elem_type* _Right) const noexcept
{
	return this->mid(_Left.data(), _Left.size(), _Right, x_posix_strlen(_Right), x::CaseSensitive);
}

// [mid] 从源中截取部分数据
x::string x::string::mid(const x::string& _Left, const elem_type* _Right, x::CaseSensitivity _XCS) const noexcept
{
	return this->mid(_Left.data(), _Left.size(), _Right, x_posix_strlen(_Right), _XCS);
}

// [mid] 从源中截取部分数据
x::string x::string::mid(const x::string& _Left, const x::string& _Right) const noexcept
{
	return this->mid(_Left.data(), _Left.size(), _Right.data(), _Right.size(), x::CaseSensitive);
}

// [mid] 从源中截取部分数据
x::string x::string::mid(const x::string& _Left, const x::string& _Right, x::CaseSensitivity _XCS) const noexcept
{
	return this->mid(_Left.data(), _Left.size(), _Right.data(), _Right.size(), _XCS);
}





// 检测源数据是否存在指定的前缀
bool x::string::startsWith(elem_type _Char) const noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->startsWith(vBytes, 1, x::CaseSensitive);
}

// 检测源数据是否存在指定的前缀
bool x::string::startsWith(elem_type _Char, x::CaseSensitivity _XCS) const noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->startsWith(vBytes, 1, _XCS);
}

// 检测源数据是否存在指定的前缀
bool x::string::startsWith(const elem_type* _Memory) const noexcept
{
	return this->startsWith(_Memory, x_posix_strlen(_Memory), x::CaseSensitive);
}

// 检测源数据是否存在指定的前缀
bool x::string::startsWith(const elem_type* _Memory, x::CaseSensitivity _XCS) const noexcept
{
	return this->startsWith(_Memory, x_posix_strlen(_Memory), _XCS);
}

// 检测源数据是否存在指定的前缀
bool x::string::startsWith(const elem_type* _Memory, size_type _Length) const noexcept
{
	return this->startsWith(_Memory, _Length, x::CaseSensitive);
}

// 检测源数据是否存在指定的前缀
bool x::string::startsWith(const elem_type* _Memory, size_type _Length, x::CaseSensitivity _XCS) const noexcept
{
	if(this->size() >= _Length)
	{
		return this->left(_Length).compare(_Memory, _Length, _XCS) == 0;
	}
	return false;
}

// 检测源数据是否存在指定的前缀
bool x::string::startsWith(const x::string& _String) const noexcept
{
	return this->startsWith(_String.data(), _String.size(), x::CaseSensitive);
}

// 检测源数据是否存在指定的前缀
bool x::string::startsWith(const x::string& _String, x::CaseSensitivity _XCS) const noexcept
{
	return this->startsWith(_String.data(), _String.size(), _XCS);
}





// 检测源数据是否存在指定的后缀
bool x::string::endsWith(elem_type _Char) const noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->endsWith(vBytes, 1, x::CaseSensitive);
}

// 检测源数据是否存在指定的后缀
bool x::string::endsWith(elem_type _Char, x::CaseSensitivity _XCS) const noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->endsWith(vBytes, 1, _XCS);
}

// 检测源数据是否存在指定的后缀
bool x::string::endsWith(const elem_type* _Memory) const noexcept
{
	return this->endsWith(_Memory, x_posix_strlen(_Memory), x::CaseSensitive);
}

// 检测源数据是否存在指定的后缀
bool x::string::endsWith(const elem_type* _Memory, x::CaseSensitivity _XCS) const noexcept
{
	return this->endsWith(_Memory, x_posix_strlen(_Memory), _XCS);
}

// 检测源数据是否存在指定的后缀
bool x::string::endsWith(const elem_type* _Memory, size_type _Length) const noexcept
{
	return this->endsWith(_Memory, _Length, x::CaseSensitive);
}

// 检测源数据是否存在指定的后缀
bool x::string::endsWith(const elem_type* _Memory, size_type _Length, x::CaseSensitivity _XCS) const noexcept
{
	if(this->size() >= _Length)
	{
		return this->right(_Length).compare(_Memory, _Length, _XCS) == 0;
	}
	return false;
}

// 检测源数据是否存在指定的后缀
bool x::string::endsWith(const x::string& _String) const noexcept
{
	return this->endsWith(_String.data(), _String.size(), x::CaseSensitive);
}

// 检测源数据是否存在指定的后缀
bool x::string::endsWith(const x::string& _String, x::CaseSensitivity _XCS) const noexcept
{
	return this->endsWith(_String.data(), _String.size(), _XCS);
}





// 从指定位置按正序查找数据
x::string::pos_type x::string::find(elem_type _Char) const noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->find(vBytes, 1, 0, x::CaseSensitive);
}

// 从指定位置按正序查找数据
x::string::pos_type x::string::find(elem_type _Char, x::CaseSensitivity _XCS) const noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->find(vBytes, 1, 0, _XCS);
}

// 从指定位置按正序查找数据
x::string::pos_type x::string::find(elem_type _Char, pos_type _Pos) const noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->find(vBytes, 1, _Pos, x::CaseSensitive);
}

// 从指定位置按正序查找数据
x::string::pos_type x::string::find(elem_type _Char, pos_type _Pos, x::CaseSensitivity _XCS) const noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->find(vBytes, 1, _Pos, _XCS);
}

// 从指定位置按正序查找数据
x::string::pos_type x::string::find(const elem_type* _String) const noexcept
{
	return this->find(_String, x_posix_strlen(_String), 0, x::CaseSensitive);
}

// 从指定位置按正序查找数据
x::string::pos_type x::string::find(const elem_type* _String, x::CaseSensitivity _XCS) const noexcept
{
	return this->find(_String, x_posix_strlen(_String), 0, _XCS);
}

// 从指定位置按正序查找数据
x::string::pos_type x::string::find(const elem_type* _String, pos_type _Pos) const noexcept
{
	return this->find(_String, x_posix_strlen(_String), _Pos, x::CaseSensitive);
}

// 从指定位置按正序查找数据
x::string::pos_type x::string::find(const elem_type* _String, pos_type _Pos, x::CaseSensitivity _XCS) const noexcept
{
	return this->find(_String, x_posix_strlen(_String), _Pos, _XCS);
}

// 从指定位置按正序查找数据
x::string::pos_type x::string::find(const elem_type* _String, size_type _Length, pos_type _Pos) const noexcept
{
	return this->find(_String, _Length, _Pos, x::CaseSensitive);
}

// 从指定位置按正序查找数据
x::string::pos_type x::string::find(const elem_type* _String, size_type _Length, pos_type _Pos, x::CaseSensitivity _XCS) const noexcept
{
	auto 		vFind = static_cast<const x::string::elem_type*>(nullptr);

	if(_String == nullptr || _Length == 0 || (this->size() - _Pos) < _Length)
	{
		return x::string::npos;
	}

	if(_XCS == x::CaseInsensitive)
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
	return x::string::npos;
}

// 从指定位置按正序查找数据
x::string::pos_type x::string::find(const x::string& _String) const noexcept
{
	return this->find(_String.data(), _String.size(), 0, x::CaseSensitive);
}

// 从指定位置按正序查找数据
x::string::pos_type x::string::find(const x::string& _String, x::CaseSensitivity _XCS) const noexcept
{
	return this->find(_String.data(), _String.size(), 0, _XCS);
}

// 从指定位置按正序查找数据
x::string::pos_type x::string::find(const x::string& _String, pos_type _Pos) const noexcept
{
	return this->find(_String.data(), _String.size(), _Pos, x::CaseSensitive);
}

// 从指定位置按正序查找数据
x::string::pos_type x::string::find(const x::string& _String, pos_type _Pos, x::CaseSensitivity _XCS) const noexcept
{
	return this->find(_String.data(), _String.size(), _Pos, _XCS);
}





// 从指定位置按倒序查找数据
x::string::pos_type x::string::rfind(elem_type _Char) const noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->rfind(vBytes, 1, this->size() - 1, x::CaseSensitive);
}

// 从指定位置按倒序查找数据
x::string::pos_type x::string::rfind(elem_type _Char, x::CaseSensitivity _XCS) const noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->rfind(vBytes, 1, this->size() - 1, _XCS);
}

// 从指定位置按倒序查找数据
x::string::pos_type x::string::rfind(elem_type _Char, pos_type _Pos) const noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->rfind(vBytes, 1, _Pos, x::CaseSensitive);
}

// 从指定位置按倒序查找数据
x::string::pos_type x::string::rfind(elem_type _Char, pos_type _Pos, x::CaseSensitivity _XCS) const noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->rfind(vBytes, 1, _Pos, _XCS);
}

// 从指定位置按倒序查找数据
x::string::pos_type x::string::rfind(const elem_type* _String) const noexcept
{
	return  this->rfind(_String, x_posix_strlen(_String), this->size() - 1, x::CaseSensitive);
}

// 从指定位置按倒序查找数据
x::string::pos_type x::string::rfind(const elem_type* _String, x::CaseSensitivity _XCS) const noexcept
{
	return  this->rfind(_String, x_posix_strlen(_String), this->size() - 1, _XCS);
}

// 从指定位置按倒序查找数据
x::string::pos_type x::string::rfind(const elem_type* _String, pos_type _Pos) const noexcept
{
	return  this->rfind(_String, x_posix_strlen(_String), _Pos, x::CaseSensitive);
}

// 从指定位置按倒序查找数据
x::string::pos_type x::string::rfind(const elem_type* _String, pos_type _Pos, x::CaseSensitivity _XCS) const noexcept
{
	return  this->rfind(_String, x_posix_strlen(_String), _Pos, _XCS);
}

// 从指定位置按倒序查找数据
x::string::pos_type x::string::rfind(const elem_type* _String, size_type _Length, pos_type _Pos) const noexcept
{
	return this->rfind(_String, _Length, _Pos, x::CaseSensitive);
}

// 从指定位置按倒序查找数据
x::string::pos_type x::string::rfind(const elem_type* _String, size_type _Length, pos_type _Pos, x::CaseSensitivity _XCS) const noexcept
{
	auto 		vFind = static_cast<int>(1);

	if(_String == nullptr || _Length == 0 || this->size() < _Length)
	{
		return x::string::npos;
	}

	for(; _Pos != x::string::npos && vFind != 0; --_Pos)
	{
		if(_XCS == x::CaseInsensitive)
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

// 从指定位置按倒序查找数据
x::string::pos_type x::string::rfind(const x::string& _String) const noexcept
{
	return this->rfind(_String.data(), _String.size(), this->size() - 1, x::CaseSensitive);
}

// 从指定位置按倒序查找数据
x::string::pos_type x::string::rfind(const x::string& _String, x::CaseSensitivity _XCS) const noexcept
{
	return this->rfind(_String.data(), _String.size(), this->size() - 1, _XCS);
}

// 从指定位置按倒序查找数据
x::string::pos_type x::string::rfind(const x::string& _String, pos_type _Pos) const noexcept
{
	return this->rfind(_String.data(), _String.size(), _Pos, x::CaseSensitive);
}

// 从指定位置按倒序查找数据
x::string::pos_type x::string::rfind(const x::string& _String, pos_type _Pos, x::CaseSensitivity _XCS) const noexcept
{
	return this->rfind(_String.data(), _String.size(), _Pos, _XCS);
}





// 检查是否包含指定数据
bool x::string::contains(elem_type _Char) const noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->contains(vBytes, 1, x::CaseSensitive);
}

// 检查是否包含指定数据
bool x::string::contains(elem_type _Char, x::CaseSensitivity _XCS) const noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->contains(vBytes, 1, _XCS);
}

// 检查是否包含指定数据
bool x::string::contains(const elem_type* _String) const noexcept
{
	return this->contains(_String, x_posix_strlen(_String), x::CaseSensitive);
}

// 检查是否包含指定数据
bool x::string::contains(const elem_type* _String, x::CaseSensitivity _XCS) const noexcept
{
	return this->contains(_String, x_posix_strlen(_String), _XCS);
}

// 检查是否包含指定数据
bool x::string::contains(const elem_type* _String, size_type _Length) const noexcept
{
	return this->contains(_String, _Length, x::CaseSensitive);
}

// 检查是否包含指定数据
bool x::string::contains(const elem_type* _String, size_type _Length, x::CaseSensitivity _XCS) const noexcept
{
	auto		vFind = this->find(_String, _Length, 0, _XCS);
	return vFind != x::string::npos;
}

// 检查是否包含指定数据
bool x::string::contains(const x::string& _String) const noexcept
{
	return this->contains(_String.data(), _String.size(), x::CaseSensitive);
}

// 检查是否包含指定数据
bool x::string::contains(const x::string& _String, x::CaseSensitivity _XCS) const noexcept
{
	return this->contains(_String.data(), _String.size(), _XCS);
}





// 检查是否与指定数据相同
int x::string::compare(elem_type _Char) const noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->compare(vBytes, 1, x::CaseSensitive);
}

// 检查是否与指定数据相同
int x::string::compare(elem_type _Char, x::CaseSensitivity _XCS) const noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->compare(vBytes, 1, _XCS);
}

// 检查是否与指定数据相同
int x::string::compare(const elem_type* _String) const noexcept
{
	return this->compare(_String, x_posix_strlen(_String), x::CaseSensitive);
}

// 检查是否与指定数据相同
int x::string::compare(const elem_type* _String, x::CaseSensitivity _XCS) const noexcept
{
	return this->compare(_String, x_posix_strlen(_String), _XCS);
}

// 检查是否与指定数据相同
int x::string::compare(const elem_type* _String, size_type _Length) const noexcept
{
	return this->compare(_String, _Length, x::CaseSensitive);
}

// 检查是否与指定数据相同
int x::string::compare(const elem_type* _String, size_type _Length, x::CaseSensitivity _XCS) const noexcept
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
			if(_XCS == x::CaseInsensitive)
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
			if(_XCS == x::CaseInsensitive)
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
			if(_XCS == x::CaseInsensitive)
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
int x::string::compare(const x::string& _String) const noexcept
{
	return this->compare(_String.data(), _String.size(), x::CaseSensitive);
}

// 检查是否与指定数据相同
int x::string::compare(const x::string& _String, x::CaseSensitivity _XCS) const noexcept
{
	return this->compare(_String.data(), _String.size(), _XCS);
}





// 在头部插入数据
x::string& x::string::prepend(elem_type _Char) noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->prepend(vBytes, 1);
}

// 在头部插入数据
x::string& x::string::prepend(const elem_type* _String) noexcept
{
	return this->prepend(_String, x_posix_strlen(_String));
}

// 在头部插入数据
x::string& x::string::prepend(const elem_type* _String, size_type _Size) noexcept
{
	return this->insert(0, _String, _Size);
}

// 在头部插入数据
x::string& x::string::prepend(const x::string& _String) noexcept
{
	return this->prepend(_String.data(), _String.size());
}





// 在尾部添加数据
x::string& x::string::append(elem_type _Char) noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->append(vBytes, 1);
}

// 在尾部添加数据
x::string& x::string::append(const elem_type* _String) noexcept
{
	return this->append(_String, x_posix_strlen(_String));
}

// 在尾部添加数据
x::string& x::string::append(const elem_type* _String, size_type _Size) noexcept
{
	return this->insert(this->size(), _String, _Size);
}

// 在尾部添加数据
x::string& x::string::append(const x::string& _String) noexcept
{
	return this->append(_String.data(), _String.size());
}





// 在指定下标处插入数据
x::string& x::string::insert(pos_type _Pos, elem_type _Char) noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->insert(_Pos, vBytes, 1);
}

// 在指定下标处插入数据
x::string& x::string::insert(pos_type _Pos, size_type _Count, elem_type _Char) noexcept
{
	auto		vString = x::string(_Count, _Char);
	return this->insert(_Pos, vString.data(), vString.size());
}

// 在指定下标处插入数据
x::string& x::string::insert(pos_type _Pos, const elem_type* _String) noexcept
{
	return this->insert(_Pos, _String, x_posix_strlen(_String));
}

// 在指定下标处插入数据
x::string& x::string::insert(pos_type _Pos, const elem_type* _String, size_type _Length) noexcept
{
	this->_Allocator.insert(_Pos, _String, _Length);
	return *this;
}

// Inserts data from the specified location x::string
x::string& x::string::insert(pos_type _Pos, const x::string& _String) noexcept
{
	return this->insert(_Pos, _String.data(), _String.size());
}





// 移除下标 pos 处的 length 长度数据
x::string& x::string::remove(pos_type _Pos, size_type _Length) noexcept
{
	this->_Allocator.remove(_Pos, _Length);
	return *this;
}

// 删除与参数相同的数据
x::string& x::string::remove(elem_type _Char) noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->remove(vBytes, 1, x::CaseSensitive);
}

// 删除与参数相同的数据
x::string& x::string::remove(elem_type _Char, x::CaseSensitivity _XCS) noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->remove(vBytes, 1, _XCS);
}

// 删除与参数相同的数据
x::string& x::string::remove(const elem_type* _String) noexcept
{
	return this->remove(_String, x_posix_strlen(_String), x::CaseSensitive);
}

// 删除与参数相同的数据
x::string& x::string::remove(const elem_type* _String, x::CaseSensitivity _XCS) noexcept
{
	return this->remove(_String, x_posix_strlen(_String), _XCS);
}

// 删除与参数相同的数据
x::string& x::string::remove(const elem_type* _String, size_type _Length) noexcept
{
	return this->remove(_String, _Length, x::CaseSensitive);
}

// 删除与参数相同的数据
x::string& x::string::remove(const elem_type* _String, size_type _Length, x::CaseSensitivity _XCS) noexcept
{
	auto		vFind = this->find(_String, _Length, 0, _XCS);
	if(vFind != x::string::npos)
	{
		return this->remove(vFind, _Length);
	}
	return *this;
}

// 删除与参数相同的数据
x::string& x::string::remove(const x::string& _String) noexcept
{
	return this->remove(_String.data(), _String.size(), x::CaseSensitive);
}

// 删除与参数相同的数据
x::string& x::string::remove(const x::string& _String, x::CaseSensitivity _XCS) noexcept
{
	return this->remove(_String.data(), _String.size(), _XCS);
}



// 替换数据
x::string& x::string::replace(pos_type _Pos, size_type _Length, elem_type _After) noexcept
{
	elem_type		vAfter[2] = { _After, '\0' };
	return this->replace(_Pos, _Length, vAfter, 1);
}

// 替换数据
x::string& x::string::replace(pos_type _Pos, size_type _Length, const elem_type* _After) noexcept
{
	return this->replace(_Pos, _Length, _After, x_posix_strlen(_After));
}

// 替换数据
x::string& x::string::replace(pos_type _Pos, size_type _Length, const elem_type* _After, size_type _LengthA) noexcept
{
	this->_Allocator.replace(_Pos, _Length, _After, _LengthA);
	return *this;
}

// 替换数据
x::string& x::string::replace(pos_type _Pos, size_type _Length, const x::string& _After) noexcept
{
	return this->replace(_Pos, _Length, _After.data(), _After.size());
}





// 替换数据
x::string& x::string::replace(elem_type _Before, elem_type _After) noexcept
{
	elem_type		vBefore[2] = { _Before, '\0' };
	elem_type		vAfter[2] = { _After, '\0' };
	return this->replace(vBefore, 1, vAfter, 1, x::CaseSensitive);
}

// 替换数据
x::string& x::string::replace(elem_type _Before, elem_type _After, x::CaseSensitivity _XCS) noexcept
{
	elem_type		vBefore[2] = { _Before, '\0' };
	elem_type		vAfter[2] = { _After, '\0' };
	return this->replace(vBefore, 1, vAfter, 1, _XCS);
}

// 替换数据
x::string& x::string::replace(elem_type _Before, const elem_type* _After, size_type _LengthA) noexcept
{
	elem_type		vBefore[2] = { _Before, '\0' };
	return this->replace(vBefore, 1, _After, _LengthA, x::CaseSensitive);
}

// 替换数据
x::string& x::string::replace(elem_type _Before, const elem_type* _After, size_type _LengthA, x::CaseSensitivity _XCS) noexcept
{
	elem_type		vBefore[2] = { _Before, '\0' };
	return this->replace(vBefore, 1, _After, _LengthA, _XCS);
}

// 替换数据
x::string& x::string::replace(elem_type _Before, const x::string& _After) noexcept
{
	elem_type		vBefore[2] = { _Before, '\0' };
	return this->replace(vBefore, 1, _After.data(), _After.size(), x::CaseSensitive);
}

// 替换数据
x::string& x::string::replace(elem_type _Before, const x::string& _After, x::CaseSensitivity _XCS) noexcept
{
	elem_type		vBefore[2] = { _Before, '\0' };
	return this->replace(vBefore, 1, _After.data(), _After.size(), _XCS);
}





// 替换数据
x::string& x::string::replace(const elem_type* _Before, elem_type _After) noexcept
{
	elem_type		vAfter[2] = { _After, '\0' };
	return this->replace(_Before, x_posix_strlen(_Before), vAfter, 1, x::CaseSensitive);
}

// 替换数据
x::string& x::string::replace(const elem_type* _Before, elem_type _After, x::CaseSensitivity _XCS) noexcept
{
	elem_type		vAfter[2] = { _After, '\0' };
	return this->replace(_Before, x_posix_strlen(_Before), vAfter, 1, _XCS);
}

// 替换数据
x::string& x::string::replace(const elem_type* _Before, const elem_type* _After, size_type _LengthA) noexcept
{
	return this->replace(_Before, x_posix_strlen(_Before), _After, _LengthA, x::CaseSensitive);
}

// 替换数据
x::string& x::string::replace(const elem_type* _Before, const elem_type* _After, size_type _LengthA, x::CaseSensitivity _XCS) noexcept
{
	return this->replace(_Before, x_posix_strlen(_Before), _After, _LengthA, _XCS);
}

// 替换数据
x::string& x::string::replace(const elem_type* _Before, const x::string& _After) noexcept
{
	return this->replace(_Before, x_posix_strlen(_Before), _After.data(), _After.size(), x::CaseSensitive);
}

// 替换数据
x::string& x::string::replace(const elem_type* _Before, const x::string& _After, x::CaseSensitivity _XCS) noexcept
{
	return this->replace(_Before, x_posix_strlen(_Before), _After.data(), _After.size(), _XCS);
}





// 替换数据
x::string& x::string::replace(const elem_type* _Before, size_type _LengthB, elem_type _After) noexcept
{
	elem_type		vAfter[2] = { _After, '\0' };
	return this->replace(_Before, _LengthB, vAfter, 1, x::CaseSensitive);
}

// 替换数据
x::string& x::string::replace(const elem_type* _Before, size_type _LengthB, elem_type _After, x::CaseSensitivity _XCS) noexcept
{
	elem_type		vAfter[2] = { _After, '\0' };
	return this->replace(_Before, _LengthB, vAfter, 1, _XCS);
}

// 替换数据
x::string& x::string::replace(const elem_type* _Before, size_type _LengthB, const elem_type* _After, size_type _LengthA) noexcept
{
	return this->replace(_Before, _LengthB, _After, _LengthA, x::CaseSensitive);
}

// 替换数据
x::string& x::string::replace(const elem_type* _Before, size_type _LengthB, const elem_type* _After, size_type _LengthA, x::CaseSensitivity _XCS) noexcept
{
	pos_type	vPos = x::string::npos;
	do
	{
		vPos = this->find(_Before, _LengthB, vPos, _XCS);
		if(x::string::npos != vPos)
		{
			this->replace(vPos, _LengthB, _After, _LengthA);
			vPos += _LengthA;
		}
	} while(x::string::npos != vPos);
	return *this;
}

// 替换数据
x::string& x::string::replace(const elem_type* _Before, size_type _LengthB, const x::string& _After) noexcept
{
	return this->replace(_Before, _LengthB, _After.data(), _After.size(), x::CaseSensitive);
}

// 替换数据
x::string& x::string::replace(const elem_type* _Before, size_type _LengthB, const x::string& _After, x::CaseSensitivity _XCS) noexcept
{
	return this->replace(_Before, _LengthB, _After.data(), _After.size(), _XCS);
}





// 替换数据
x::string& x::string::replace(const x::string& _Before, elem_type _After) noexcept
{
	elem_type		vAfter[2] = { _After, '\0' };
	return this->replace(_Before.data(), _Before.size(), vAfter, 1, x::CaseSensitive);
}

// 替换数据
x::string& x::string::replace(const x::string& _Before, elem_type _After, x::CaseSensitivity _XCS) noexcept
{
	elem_type		vAfter[2] = { _After, '\0' };
	return this->replace(_Before.data(), _Before.size(), vAfter, 1, _XCS);
}

// 替换数据
x::string& x::string::replace(const x::string& _Before, const elem_type* _After, size_type _LengthA) noexcept
{
	return this->replace(_Before.data(), _Before.size(), _After, _LengthA, x::CaseSensitive);
}

// 替换数据
x::string& x::string::replace(const x::string& _Before, const elem_type* _After, size_type _LengthA, x::CaseSensitivity _XCS) noexcept
{
	return this->replace(_Before.data(), _Before.size(), _After, _LengthA, _XCS);
}

// 替换数据
x::string& x::string::replace(const x::string& _Before, const x::string& _After) noexcept
{
	return this->replace(_Before.data(), _Before.size(), _After.data(), _After.size(), x::CaseSensitive);
}

// 替换数据
x::string& x::string::replace(const x::string& _Before, const x::string& _After, x::CaseSensitivity _XCS) noexcept
{
	return this->replace(_Before.data(), _Before.size(), _After.data(), _After.size(), _XCS);
}





// 按指定数据拆分字符串
std::list<x::string> x::string::split(elem_type _Char) const noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->split(vBytes, 1);
}

// 按指定数据拆分字符串
std::list<x::string> x::string::split(const elem_type* _Memory) const noexcept
{
	return this->split({_Memory, x_posix_strlen(_Memory)});
}

// 按指定数据拆分字符串
std::list<x::string> x::string::split(const elem_type* _Memory, size_type _Size) const noexcept
{
	return this->split({_Memory, _Size});
}

// 按指定数据拆分字符串
std::list<x::string> x::string::split(const x::string& _String) const noexcept
{
	auto		vHeaderArray = std::list<x::string>();
	auto		vLast = static_cast<size_type>(0U);
	auto		vSplitIndex = this->find(_String, vLast);
	while(vSplitIndex != x::string::npos && _String.exist())
	{
		vHeaderArray.push_back(this->mid(vLast, vSplitIndex - vLast));
		vLast = vSplitIndex + 2;
		vSplitIndex = this->find(_String, vLast);
	}
	vHeaderArray.push_back(this->mid(vLast));

	return vHeaderArray;
}





// 判断一个字符是否为空白字符
bool x::string::isSpace(elem_type _Char) noexcept
{
	// 如果宽字符是空白字符，则为真，否则假。
	return isspace(_Char);
}

// 格式化字符串 (char* [%s]) (wchar_t* [%ls])
x::string x::string::format(const char* _Format, ...) noexcept
{
	auto		vString = x::string();
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
x::string x::string::toUpper() const noexcept
{
	auto		vStrUpper = *this;
	for(pos_type vIndex = 0; vIndex < vStrUpper.size(); ++vIndex)
	{
		vStrUpper[vIndex] = (elem_type)std::toupper(vStrUpper[vIndex]);
	}
	return vStrUpper;
}

// [conv] 转换至小写
x::string x::string::toLower() const noexcept
{
	auto		vStrUpper = *this;
	for(pos_type vIndex = 0; vIndex < vStrUpper.size(); ++vIndex)
	{
		vStrUpper[vIndex] = (elem_type)std::tolower(vStrUpper[vIndex]);
	}
	return vStrUpper;
}





// [conv] 转换至AString
AString x::string::toAString() const noexcept
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
x::string x::string::fromAString(const char* _AString) noexcept
{
	return x::string::fromAString({_AString, x_posix_strlen(_AString)});
}

// [conv] 从AString转换
x::string x::string::fromAString(const AString& _AString) noexcept
{
	auto		vString = WString();
	auto		vChangeStr = x_posix_stratow(_AString.data());
	if(vChangeStr)
	{
		vString = vChangeStr;
		x_posix_free(vChangeStr);
	}
	return x::string::fromWString(vString);
}





// [conv] 转换至WString
WString x::string::toWString() const noexcept
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
x::string x::string::fromWString(const wchar_t* _WString) noexcept
{
	return x::string::fromWString({_WString, x_posix_wcslen(_WString)});
}

// [conv] 从WString转换
x::string x::string::fromWString(const WString& _WString) noexcept
{
	auto		vString = x::string();
	auto		vChangeStr = x_posix_strwtou(_WString.data());
	if(vChangeStr)
	{
		vString = vChangeStr;
		x_posix_free(vChangeStr);
	}
	return vString;
}





// [conv] 转换至UString
UString x::string::toUString() const noexcept
{
	return {this->data(), this->size()};
}

// [conv] 从UString转换
x::string x::string::fromUString(const char* _UString) noexcept
{
	return x::string::fromUString({_UString, x_posix_strlen(_UString)});
}

// [conv] 从UString转换
x::string x::string::fromUString(const UString& _UString) noexcept
{
	return {_UString.data(), _UString.size()};
}





// [conv] 转换至NString (Windows: ASCII / 其它: UTF-8)
NString x::string::toNString() const noexcept
{
#if defined(XANADU_SYSTEM_WINDOWS)
	return this->toAString();
#else
	return this->toUString();
#endif
}

// [conv] 从NString转换 (Windows: ASCII / 其它: UTF-8)
x::string x::string::fromNString(const char* _NString) noexcept
{
	return x::string::fromNString({_NString, x_posix_strlen(_NString)});
}

// [conv] 从NString转换 (Windows: ASCII / 其它: UTF-8)
x::string x::string::fromNString(const UString& _NString) noexcept
{
#if defined(XANADU_SYSTEM_WINDOWS)
	return x::string::fromAString(_NString);
#else
	return x::string::fromUString(_NString);
#endif
}





// [conv] 转换至HEX
x::string x::string::toHex() const noexcept
{
	auto		vTarget = x::string(this->size() * 2, '0');
	for (auto vIndex = 0U; vIndex < this->size(); ++vIndex)
	{
		x_posix_sprintf(vTarget.data() + (vIndex * 2), "%02X", (std::uint8_t)this->data()[vIndex]);
	}
	return vTarget;
}

// [conv] 从HEX转换
x::string x::string::fromHex(const elem_type* _String) noexcept
{
	return x::string::fromHex({_String, x_posix_strlen(_String)});
}

// [conv] 从HEX转换
x::string x::string::fromHex(const elem_type* _String, size_type _Size) noexcept
{
	return x::string::fromHex({_String, _Size});
}

// [conv] 从HEX转换
x::string x::string::fromHex(const x::string& _Hex) noexcept
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
	auto		vTarget = x::string(vLength, '\0');

	for (auto vIndex = 0U; vIndex < vLength; ++vIndex)
	{
		auto		vHexLeft = vFunctionHexToChar(vBuffer[vIndex * 2 + 0]);
		auto		vHexRight = vFunctionHexToChar(vBuffer[vIndex * 2 + 1]);
		vTarget[vIndex] = static_cast<char>(vHexLeft * 16 + vHexRight);
	}
	return vTarget;
}





// [convert] convert to char
char x::string::toChar(bool* _Ok, int _Base) const noexcept
{
	return static_cast<char>(this->toLLong(_Ok, _Base));
}

// [convert] convert to unsigned char
unsigned char x::string::toUChar(bool* _Ok, int _Base) const noexcept
{
	return static_cast<unsigned char>(this->toULLong(_Ok, _Base));
}

// [convert] convert to short
short x::string::toShort(bool* _Ok, int _Base) const noexcept
{
	return static_cast<short>(this->toLLong(_Ok, _Base));
}

// [convert] convert to short
unsigned short x::string::toUShort(bool* _Ok, int _Base) const noexcept
{
	return static_cast<unsigned short>(this->toULLong(_Ok, _Base));
}

// [convert] convert to int
int x::string::toInt(bool* _Ok, int _Base) const noexcept
{
	return static_cast<int>(this->toLLong(_Ok, _Base));
}

// [convert] convert to unsigned int
unsigned int x::string::toUInt(bool* _Ok, int _Base) const noexcept
{
	return static_cast<unsigned int>(this->toULLong(_Ok, _Base));
}

// [convert] convert to long
long x::string::toLong(bool* _Ok, int _Base) const noexcept
{
	return static_cast<long>(this->toLLong(_Ok, _Base));
}

// [convert] convert to unsigned long
unsigned long x::string::toULong(bool* _Ok, int _Base) const noexcept
{
	return static_cast<unsigned long>(this->toULLong(_Ok, _Base));
}

// [convert] convert to long long
long long x::string::toLLong(bool* _Ok, int _Base) const noexcept
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
unsigned long long x::string::toULLong(bool* _Ok, int _Base) const noexcept
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
float x::string::toFloat(bool* _Ok) const noexcept
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
double x::string::toDouble(bool* _Ok) const noexcept
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
x::string& x::string::setNumber(char _Value, int _Base) noexcept
{
	this->setNumber(static_cast<long long>(_Value), _Base);
	return *this;
}

// [convert] convert from number
x::string& x::string::setNumber(unsigned char _Value, int _Base) noexcept
{
	this->setNumber(static_cast<unsigned long long>(_Value), _Base);
	return *this;
}

// [convert] convert from number
x::string& x::string::setNumber(short _Value, int _Base) noexcept
{
	this->setNumber(static_cast<long long>(_Value), _Base);
	return *this;
}

// [convert] convert from number
x::string& x::string::setNumber(unsigned short _Value, int _Base) noexcept
{
	this->setNumber(static_cast<unsigned long long>(_Value), _Base);
	return *this;
}

// [convert] convert from number
x::string& x::string::setNumber(int _Value, int _Base) noexcept
{
	this->setNumber(static_cast<long long>(_Value), _Base);
	return *this;
}

// [convert] convert from number
x::string& x::string::setNumber(unsigned int _Value, int _Base) noexcept
{
	this->setNumber(static_cast<unsigned long long>(_Value), _Base);
	return *this;
}

// [convert] convert from number
x::string& x::string::setNumber(long _Value, int _Base) noexcept
{
	this->setNumber(static_cast<long long>(_Value), _Base);
	return *this;
}

// [convert] convert from number
x::string& x::string::setNumber(unsigned long _Value, int _Base) noexcept
{
	this->setNumber(static_cast<unsigned long long>(_Value), _Base);
	return *this;
}

// [convert] convert from number
x::string& x::string::setNumber(long long _Value, int _Base) noexcept
{
	if(2 <= _Base && _Base <= 36)
	{
		*this = std::to_string(_Value).data();
	}
	return *this;
}

// [convert] convert from number
x::string& x::string::setNumber(unsigned long long _Value, int _Base) noexcept
{
	if(2 <= _Base && _Base <= 36)
	{
		*this = std::to_string(_Value).data();
	}
	return *this;
}

// [convert] convert from number
x::string& x::string::setNumber(float _Value, char _Format, int _Prec) noexcept
{
	XANADU_UNUSED(_Format);
	XANADU_UNUSED(_Prec);

	*this = std::to_string(_Value).data();
	return *this;
}

// [convert] convert from number
x::string& x::string::setNumber(double _Value, char _Format, int _Prec) noexcept
{
	XANADU_UNUSED(_Format);
	XANADU_UNUSED(_Prec);

	*this = std::to_string(_Value).data();
	return *this;
}





// [convert] convert from number
x::string x::string::number(char _Value, int _Base) noexcept
{
	auto		vValue = x::string();
	vValue.setNumber(_Value, _Base);
	return vValue;
}

// [convert] convert from number
x::string x::string::number(unsigned char _Value, int _Base) noexcept
{
	auto		vValue = x::string();
	vValue.setNumber(_Value, _Base);
	return vValue;
}

// [convert] convert from number
x::string x::string::number(short _Value, int _Base) noexcept
{
	auto		vValue = x::string();
	vValue.setNumber(_Value, _Base);
	return vValue;
}

// [convert] convert from number
x::string x::string::number(unsigned short _Value, int _Base) noexcept
{
	auto		vValue = x::string();
	vValue.setNumber(_Value, _Base);
	return vValue;
}

// [convert] convert from number
x::string x::string::number(int _Value, int _Base) noexcept
{
	auto		vValue = x::string();
	vValue.setNumber(_Value, _Base);
	return vValue;
}

// [convert] convert from number
x::string x::string::number(unsigned int _Value, int _Base) noexcept
{
	auto		vValue = x::string();
	vValue.setNumber(_Value, _Base);
	return vValue;
}

// [convert] convert from number
x::string x::string::number(long _Value, int _Base) noexcept
{
	auto		vValue = x::string();
	vValue.setNumber(_Value, _Base);
	return vValue;
}

// [convert] convert from number
x::string x::string::number(unsigned long _Value, int _Base) noexcept
{
	auto		vValue = x::string();
	vValue.setNumber(_Value, _Base);
	return vValue;
}

// [convert] convert from number
x::string x::string::number(long long _Value, int _Base) noexcept
{
	auto		vValue = x::string();
	vValue.setNumber(_Value, _Base);
	return vValue;
}

// [convert] convert from number
x::string x::string::number(unsigned long long _Value, int _Base) noexcept
{
	auto		vValue = x::string();
	vValue.setNumber(_Value, _Base);
	return vValue;
}

// [convert] convert from number
x::string x::string::number(float _Value, char _Format, int _Prec) noexcept
{
	auto		vValue = x::string();
	vValue.setNumber(_Value, _Format, _Prec);
	return vValue;
}

// [convert] convert from number
x::string x::string::number(double _Value, char _Format, int _Prec) noexcept
{
	auto		vValue = x::string();
	vValue.setNumber(_Value, _Format, _Prec);
	return vValue;
}





// Standard enhancement function : stream <<
_XCOREAPI_ std::ostream& operator<< (std::ostream& _OStream, const x::string& _String) noexcept
{
	for(auto vIndex = 0U; vIndex < _String.size(); ++vIndex)
	{
		_OStream << _String[vIndex];
	}
	return _OStream;
}

// Standard enhancement function : stream >>
_XCOREAPI_ std::istream& operator>> (std::istream& _IStream, x::string& _String) noexcept
{
	_String.clear();
	do
	{
		auto		vChar = static_cast<x::string::elem_type>(_IStream.get());
		if(vChar == '\n' || vChar == ' ')
		{
			break;
		}
		_String.append(vChar);
	} while(true);
	return _IStream;
}

// Standard enhancement function : getline
_XCOREAPI_ std::istream& getline(std::istream& _IStream, x::string& _String, char _Delim) noexcept
{
	_String.clear();
	do
	{
		auto		vChar = static_cast<x::string::elem_type>(_IStream.get());
		if(vChar == _Delim)
		{
			break;
		}
		_String.append(vChar);
	} while(true);
	return _IStream;
}

// Standard enhancement function : getline
_XCOREAPI_ std::istream& getline(std::istream& _IStream, x::string& _String) noexcept
{
	return getline(_IStream, _String, '\n');
}
