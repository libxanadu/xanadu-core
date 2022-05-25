#include <xanadu-core/bytearray.h>
#include <cstdarg>



// constructor
x::bytearray::bytearray() noexcept = default;

// constructor
x::bytearray::bytearray(size_type _Length, elem_type _Char) noexcept : _Allocator(_Length, _Char)
{
}

// constructor
x::bytearray::bytearray(const elem_type* _Memory) noexcept : _Allocator(_Memory, x_posix_strlen(_Memory))
{
}

// constructor
x::bytearray::bytearray(const elem_type* _Memory, size_type _Length) noexcept : _Allocator(_Memory, _Length)
{
}

// constructor
x::bytearray::bytearray(const raw_type* _Memory, size_type _Length) noexcept : _Allocator(_Memory, _Length)
{
}

// constructor
x::bytearray::bytearray(const x::bytearray& _String) noexcept = default;

// constructor
x::bytearray::bytearray(x::bytearray&& _String) noexcept = default;

// destructor
x::bytearray::~bytearray() noexcept = default;





// operator overload =
x::bytearray& x::bytearray::operator = (const elem_type* _Memory) noexcept
{
	if(this->resize(x_posix_strlen(_Memory)))
	{
		x_posix_memcpy(this->data(), _Memory, this->size());
	}
	return *this;
}

// operator overload =
x::bytearray& x::bytearray::operator = (const x::bytearray& _String) noexcept
{
	if(this != &_String)
	{
		this->_Allocator = _String._Allocator;
	}
	return *this;
}

// operator overload =
x::bytearray& x::bytearray::operator = (x::bytearray&& _String) noexcept
{
	if(this != &_String)
	{
		this->_Allocator = _String._Allocator;
	}
	return *this;
}





// operator overload +=
x::bytearray& x::bytearray::operator += (elem_type _Char) noexcept
{
	elem_type		vBytes[2] = {_Char, '\0'};
	return this->append(vBytes, 1);
}

// operator overload +=
x::bytearray& x::bytearray::operator += (const elem_type* _String) noexcept
{
	return this->append(_String, x_posix_strlen(_String));
}

// operator overload +=
x::bytearray& x::bytearray::operator += (const x::bytearray& _String) noexcept
{
	return this->append(_String.data(), _String.size());
}





// operator overload +
x::bytearray x::bytearray::operator + (elem_type _Char) const noexcept
{
	auto		vTemp = *this;
	vTemp += _Char;
	return vTemp;
}

// operator overload +
x::bytearray x::bytearray::operator + (const elem_type* _String) const noexcept
{
	auto		vTemp = *this;
	vTemp += _String;
	return vTemp;
}

// operator overload +
x::bytearray x::bytearray::operator + (const x::bytearray& _String) const noexcept
{
	auto		vTemp = *this;
	vTemp += _String;
	return vTemp;
}





// operator overload ==
bool x::bytearray::operator == (elem_type _Char) const noexcept
{
	elem_type		vBytes[2] = {_Char, '\0'};
	return this->compare(vBytes, 1) == 0;
}

// operator overload ==
bool x::bytearray::operator == (const elem_type* _String) const noexcept
{
	return this->compare(_String, x_posix_strlen(_String)) == 0;
}

// operator overload ==
bool x::bytearray::operator == (const x::bytearray& _String) const noexcept
{
	return this->compare(_String.data(), _String.size()) == 0;
}

// operator overload !=
bool x::bytearray::operator != (elem_type _Char) const noexcept
{
	elem_type		vBytes[2] = {_Char, '\0'};
	return this->compare(vBytes, 1) != 0;
}

// operator overload !=
bool x::bytearray::operator != (const elem_type* _String) const noexcept
{
	return this->compare(_String, x_posix_strlen(_String)) != 0;
}

// operator overload !=
bool x::bytearray::operator != (const x::bytearray& _String) const noexcept
{
	return this->compare(_String.data(), _String.size()) != 0;
}





// operator overload []
x::bytearray::elem_type& x::bytearray::operator [] (pos_type _Index)
{
	return this->_Allocator[_Index];
}

// operator overload []
x::bytearray::elem_type x::bytearray::operator [] (pos_type _Index) const
{
	return this->_Allocator[_Index];
}





// [opt] clear
void x::bytearray::clear() noexcept
{
	this->_Allocator.clear();
}

// [opt] resize
bool x::bytearray::resize(size_type _Length) noexcept
{
	return this->_Allocator.resize(_Length);
}

// [opt] reverse
bool x::bytearray::reverse(size_type _Length) noexcept
{
	return this->_Allocator.reverse(_Length);
}





// [get] exist
bool x::bytearray::exist() const noexcept
{
	return this->_Allocator.exist();
}

// [get] empty
bool x::bytearray::empty() const noexcept
{
	return this->_Allocator.empty();
}

// [get] data
x::bytearray::elem_type* x::bytearray::data() noexcept
{
	return static_cast<x::bytearray::elem_type*>(this->_Allocator.data());
}

// [get] data
const x::bytearray::elem_type* x::bytearray::data() const noexcept
{
	return static_cast<const x::bytearray::elem_type*>(this->_Allocator.data());
}

// [get] size
x::bytearray::size_type x::bytearray::size() const noexcept
{
	return this->_Allocator.size();
}

// [get] capacity
x::bytearray::size_type x::bytearray::capacity() const noexcept
{
	return this->_Allocator.capacity();
}

// [get] surplus
x::bytearray::size_type x::bytearray::surplus() const noexcept
{
	return this->_Allocator.surplus();
}

// [get] max_size
x::bytearray::size_type x::bytearray::max_size() const noexcept
{
	return this->_Allocator.max_size();
}





// 从源中截取部分数据
x::bytearray x::bytearray::substr(pos_type _Pos) const noexcept
{
	return this->substr(_Pos, x::bytearray::npos);
}

// 从源中截取部分数据
x::bytearray x::bytearray::substr(pos_type _Pos, size_type _Length) const noexcept
{
	if(_Pos < this->size())
	{
		if(_Length == x::bytearray::npos)
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
x::bytearray x::bytearray::left(pos_type _Pos) const noexcept
{
	return this->substr(0, _Pos);
}

// 从源中截取部分数据
x::bytearray x::bytearray::right(pos_type _Pos) const noexcept
{
	return this->substr(this->size() - _Pos, x::bytearray::npos);
}





// [mid] 从源中截取部分数据
x::bytearray x::bytearray::mid(pos_type _Pos) const noexcept
{
	return this->mid(_Pos, x::bytearray::npos);
}

// [mid] 从源中截取部分数据
x::bytearray x::bytearray::mid(pos_type _Pos, size_type _Size) const noexcept
{
	return this->substr(_Pos, _Size);
}

// [mid] 从源中截取部分数据
x::bytearray x::bytearray::mid(const elem_type* _Left, const elem_type* _Right) const noexcept
{
	return this->mid(_Left, x_posix_strlen(_Left), _Right, x_posix_strlen(_Right));
}

// [mid] 从源中截取部分数据
x::bytearray x::bytearray::mid(const elem_type* _Left, size_type _LengthL, const elem_type* _Right) const noexcept
{
	return this->mid(_Left, _LengthL, _Right, x_posix_strlen(_Right));
}

// [mid] 从源中截取部分数据
x::bytearray x::bytearray::mid(const elem_type* _Left, const elem_type* _Right, size_type _LengthR) const noexcept
{
	return this->mid(_Left, x_posix_strlen(_Left), _Right, _LengthR);
}

// [mid] 从源中截取部分数据
x::bytearray x::bytearray::mid(const elem_type* _Left, size_type _LengthL, const elem_type* _Right, size_type _LengthR) const noexcept
{
	return this->mid((const raw_type*)_Left, _LengthL, (const raw_type*)_Right, _LengthR);
}

// [mid] 从源中截取部分数据
x::bytearray x::bytearray::mid(const raw_type* _Left, size_type _LengthL, const raw_type* _Right, size_type _LengthR) const noexcept
{
	pos_type 	vPosL = x::bytearray::npos;
	pos_type 	vPosR = x::bytearray::npos;

	if(_Left == nullptr || _Right == nullptr || _LengthL == 0 || _LengthR == 0)
	{
		return {};
	}

	vPosL = this->find(_Left, _LengthL, 0);
	if(x::bytearray::npos != vPosL)
	{
		vPosL += _LengthL;
		vPosR = this->find(_Right, _LengthR, vPosL);
		if(x::bytearray::npos != vPosR)
		{
			return this->substr(vPosL, vPosR - vPosL);
		}
	}
	return {};
}

// [mid] 从源中截取部分数据
x::bytearray x::bytearray::mid(const elem_type* _Left, const x::bytearray& _Right) const noexcept
{
	return this->mid(_Left, x_posix_strlen(_Left), _Right.data(), _Right.size());
}

// [mid] 从源中截取部分数据
x::bytearray x::bytearray::mid(const x::bytearray& _Left, const elem_type* _Right) const noexcept
{
	return this->mid(_Left.data(), _Left.size(), _Right, x_posix_strlen(_Right));
}

// [mid] 从源中截取部分数据
x::bytearray x::bytearray::mid(const x::bytearray& _Left, const x::bytearray& _Right) const noexcept
{
	return this->mid(_Left.data(), _Left.size(), _Right.data(), _Right.size());
}





// 检测源数据是否存在指定的前缀
bool x::bytearray::startsWith(elem_type _Char) const noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->startsWith(vBytes, 1);
}

// 检测源数据是否存在指定的前缀
bool x::bytearray::startsWith(const elem_type* _Memory) const noexcept
{
	return this->startsWith(_Memory, x_posix_strlen(_Memory));
}

// 检测源数据是否存在指定的前缀
bool x::bytearray::startsWith(const elem_type* _Memory, size_type _Length) const noexcept
{
	return this->startsWith((const raw_type*)_Memory, _Length);
}

// 检测源数据是否存在指定的前缀
bool x::bytearray::startsWith(const raw_type* _Memory, size_type _Length) const noexcept
{
	if(this->size() >= _Length)
	{
		return this->left(_Length).compare(_Memory, _Length) == 0;
	}
	return false;
}

// 检测源数据是否存在指定的前缀
bool x::bytearray::startsWith(const x::bytearray& _String) const noexcept
{
	return this->startsWith(_String.data(), _String.size());
}





// 检测源数据是否存在指定的后缀
bool x::bytearray::endsWith(elem_type _Char) const noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->endsWith(vBytes, 1);
}

// 检测源数据是否存在指定的后缀
bool x::bytearray::endsWith(const elem_type* _Memory) const noexcept
{
	return this->endsWith(_Memory, x_posix_strlen(_Memory));
}

// 检测源数据是否存在指定的后缀
bool x::bytearray::endsWith(const elem_type* _Memory, size_type _Length) const noexcept
{
	return this->endsWith((const raw_type*)_Memory, _Length);
}

// 检测源数据是否存在指定的后缀
bool x::bytearray::endsWith(const raw_type* _Memory, size_type _Length) const noexcept
{
	if(this->size() >= _Length)
	{
		return this->right(_Length).compare(_Memory, _Length) == 0;
	}
	return false;
}

// 检测源数据是否存在指定的后缀
bool x::bytearray::endsWith(const x::bytearray& _String) const noexcept
{
	return this->endsWith(_String.data(), _String.size());
}





// 从指定位置按正序查找数据
x::bytearray::pos_type x::bytearray::find(elem_type _Char) const noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->find(vBytes, 1, 0);
}

// 从指定位置按正序查找数据
x::bytearray::pos_type x::bytearray::find(elem_type _Char, pos_type _Pos) const noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->find(vBytes, 1, _Pos);
}

// 从指定位置按正序查找数据
x::bytearray::pos_type x::bytearray::find(const elem_type* _String) const noexcept
{
	return this->find(_String, x_posix_strlen(_String), 0);
}

// 从指定位置按正序查找数据
x::bytearray::pos_type x::bytearray::find(const elem_type* _String, pos_type _Pos) const noexcept
{
	return this->find(_String, x_posix_strlen(_String), _Pos);
}

// 从指定位置按正序查找数据
x::bytearray::pos_type x::bytearray::find(const elem_type* _String, size_type _Length, pos_type _Pos) const noexcept
{
	return this->find((const raw_type*)_String, _Length, _Pos);
}

// 从指定位置按正序查找数据
x::bytearray::pos_type x::bytearray::find(const raw_type* _Memory, size_type _Length, pos_type _Pos) const noexcept
{
	return this->_Allocator.find(_Memory, _Length, _Pos);
}

// 从指定位置按正序查找数据
x::bytearray::pos_type x::bytearray::find(const x::bytearray& _String) const noexcept
{
	return this->find(_String.data(), _String.size(), 0);
}

// 从指定位置按正序查找数据
x::bytearray::pos_type x::bytearray::find(const x::bytearray& _String, pos_type _Pos) const noexcept
{
	return this->find(_String.data(), _String.size(), _Pos);
}





// 从指定位置按倒序查找数据
x::bytearray::pos_type x::bytearray::rfind(elem_type _Char) const noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->rfind(vBytes, 1, this->size() - 1);
}

// 从指定位置按倒序查找数据
x::bytearray::pos_type x::bytearray::rfind(elem_type _Char, pos_type _Pos) const noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->rfind(vBytes, 1, _Pos);
}

// 从指定位置按倒序查找数据
x::bytearray::pos_type x::bytearray::rfind(const elem_type* _String) const noexcept
{
	return  this->rfind(_String, x_posix_strlen(_String), this->size() - 1);
}

// 从指定位置按倒序查找数据
x::bytearray::pos_type x::bytearray::rfind(const elem_type* _String, pos_type _Pos) const noexcept
{
	return  this->rfind(_String, x_posix_strlen(_String), _Pos);
}

// 从指定位置按倒序查找数据
x::bytearray::pos_type x::bytearray::rfind(const elem_type* _String, size_type _Length, pos_type _Pos) const noexcept
{
	return  this->rfind((const raw_type*)_String, _Length, _Pos);
}

// 从指定位置按倒序查找数据
x::bytearray::pos_type x::bytearray::rfind(const raw_type* _Memory, size_type _Length, pos_type _Pos) const noexcept
{
	return this->_Allocator.rfind(_Memory, _Length, _Pos);
}

// 从指定位置按倒序查找数据
x::bytearray::pos_type x::bytearray::rfind(const x::bytearray& _String) const noexcept
{
	return this->rfind(_String.data(), _String.size(), this->size() - 1);
}

// 从指定位置按倒序查找数据
x::bytearray::pos_type x::bytearray::rfind(const x::bytearray& _String, pos_type _Pos) const noexcept
{
	return this->rfind(_String.data(), _String.size(), _Pos);
}





// 检查是否包含指定数据
bool x::bytearray::contains(elem_type _Char) const noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->contains(vBytes, 1);
}

// 检查是否包含指定数据
bool x::bytearray::contains(const elem_type* _String) const noexcept
{
	return this->contains(_String, x_posix_strlen(_String));
}

// 检查是否包含指定数据
bool x::bytearray::contains(const elem_type* _String, size_type _Length) const noexcept
{
	return this->contains((const raw_type*)_String, _Length);
}

// 检查是否包含指定数据
bool x::bytearray::contains(const raw_type* _Memory, size_type _Length) const noexcept
{
	auto		vFind = this->find(_Memory, _Length, 0);
	return vFind != x::bytearray::npos;
}

// 检查是否包含指定数据
bool x::bytearray::contains(const x::bytearray& _String) const noexcept
{
	return this->contains(_String.data(), _String.size());
}





// 检查是否与指定数据相同
int x::bytearray::compare(elem_type _Char) const noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->compare(vBytes, 1);
}

// 检查是否与指定数据相同
int x::bytearray::compare(const elem_type* _String) const noexcept
{
	return this->compare(_String, x_posix_strlen(_String));
}

// 检查是否与指定数据相同
int x::bytearray::compare(const elem_type* _String, size_type _Length) const noexcept
{
	return this->compare((const raw_type*)_String, _Length);
}

// 检查是否与指定数据相同
int x::bytearray::compare(const raw_type* _Memory, size_type _Length) const noexcept
{
	return this->_Allocator.compare(_Memory, _Length);
}

// 检查是否与指定数据相同
int x::bytearray::compare(const x::bytearray& _String) const noexcept
{
	return this->compare(_String.data(), _String.size());
}





// 在头部插入数据
x::bytearray& x::bytearray::prepend(elem_type _Char) noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->prepend(vBytes, 1);
}

// 在头部插入数据
x::bytearray& x::bytearray::prepend(const elem_type* _String) noexcept
{
	return this->prepend(_String, x_posix_strlen(_String));
}

// 在头部插入数据
x::bytearray& x::bytearray::prepend(const elem_type* _String, size_type _Size) noexcept
{
	return this->prepend((const raw_type*)_String, _Size);
}

// 在头部插入数据
x::bytearray& x::bytearray::prepend(const raw_type* _Memory, size_type _Size) noexcept
{
	return this->insert(0, _Memory, _Size);
}

// 在头部插入数据
x::bytearray& x::bytearray::prepend(const x::bytearray& _String) noexcept
{
	return this->prepend(_String.data(), _String.size());
}





// 在尾部添加数据
x::bytearray& x::bytearray::append(elem_type _Char) noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->append(vBytes, 1);
}

// 在尾部添加数据
x::bytearray& x::bytearray::append(const elem_type* _String) noexcept
{
	return this->append(_String, x_posix_strlen(_String));
}

// 在尾部添加数据
x::bytearray& x::bytearray::append(const elem_type* _String, size_type _Size) noexcept
{
	return this->append((const raw_type*)_String, _Size);
}

// 在尾部添加数据
x::bytearray& x::bytearray::append(const raw_type* _Memory, size_type _Size) noexcept
{
	return this->insert(this->size(), _Memory, _Size);
}

// 在尾部添加数据
x::bytearray& x::bytearray::append(const x::bytearray& _String) noexcept
{
	return this->append(_String.data(), _String.size());
}





// 在指定下标处插入数据
x::bytearray& x::bytearray::insert(pos_type _Pos, elem_type _Char) noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->insert(_Pos, vBytes, 1);
}

// 在指定下标处插入数据
x::bytearray& x::bytearray::insert(pos_type _Pos, size_type _Count, elem_type _Char) noexcept
{
	auto		vString = x::bytearray(_Count, _Char);
	return this->insert(_Pos, vString.data(), vString.size());
}

// 在指定下标处插入数据
x::bytearray& x::bytearray::insert(pos_type _Pos, const elem_type* _String) noexcept
{
	return this->insert(_Pos, _String, x_posix_strlen(_String));
}

// 在指定下标处插入数据
x::bytearray& x::bytearray::insert(pos_type _Pos, const elem_type* _String, size_type _Length) noexcept
{
	return this->insert(_Pos, (const raw_type*)_String, _Length);
}

// 在指定下标处插入数据
x::bytearray& x::bytearray::insert(pos_type _Pos, const raw_type* _Memory, size_type _Length) noexcept
{
	this->_Allocator.insert(_Pos, _Memory, _Length);
	return *this;
}

// 在指定下标处插入数据
x::bytearray& x::bytearray::insert(pos_type _Pos, const x::bytearray& _String) noexcept
{
	return this->insert(_Pos, _String.data(), _String.size());
}





// 移除下标 pos 处的 length 长度数据
x::bytearray& x::bytearray::remove(pos_type _Pos, size_type _Length) noexcept
{
	this->_Allocator.remove(_Pos, _Length);
	return *this;
}

// 删除与参数相同的数据
x::bytearray& x::bytearray::remove(elem_type _Char) noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->remove(vBytes, 1);
}

// 删除与参数相同的数据
x::bytearray& x::bytearray::remove(const elem_type* _String) noexcept
{
	return this->remove(_String, x_posix_strlen(_String));
}

// 删除与参数相同的数据
x::bytearray& x::bytearray::remove(const elem_type* _String, size_type _Length) noexcept
{
	return this->remove((const raw_type*)_String, _Length);
}

// 删除与参数相同的数据
x::bytearray& x::bytearray::remove(const raw_type* _Memory, size_type _Length) noexcept
{
	auto		vFind = this->find(_Memory, _Length, 0);
	if(vFind != x::bytearray::npos)
	{
		return this->remove(vFind, _Length);
	}
	return *this;
}

// 删除与参数相同的数据
x::bytearray& x::bytearray::remove(const x::bytearray& _String) noexcept
{
	return this->remove(_String.data(), _String.size());
}





// 替换数据
x::bytearray& x::bytearray::replace(pos_type _Pos, size_type _Length, elem_type _After) noexcept
{
	elem_type		vAfter[2] = { _After, '\0' };
	return this->replace(_Pos, _Length, vAfter, 1);
}

// 替换数据
x::bytearray& x::bytearray::replace(pos_type _Pos, size_type _Length, const elem_type* _After) noexcept
{
	return this->replace(_Pos, _Length, _After, x_posix_strlen(_After));
}

// 替换数据
x::bytearray& x::bytearray::replace(pos_type _Pos, size_type _Length, const elem_type* _After, size_type _LengthA) noexcept
{
	return this->replace(_Pos, _Length, (const raw_type*)_After, _LengthA);
}

// 替换数据
x::bytearray& x::bytearray::replace(pos_type _Pos, size_type _Length, const raw_type* _After, size_type _LengthA) noexcept
{
	this->_Allocator.replace(_Pos, _Length, _After, _LengthA);
	return *this;
}

// 替换数据
x::bytearray& x::bytearray::replace(pos_type _Pos, size_type _Length, const x::bytearray& _After) noexcept
{
	return this->replace(_Pos, _Length, _After.data(), _After.size());
}





// 替换数据
x::bytearray& x::bytearray::replace(elem_type _Before, elem_type _After) noexcept
{
	elem_type		vBefore[2] = { _Before, '\0' };
	elem_type		vAfter[2] = { _After, '\0' };
	return this->replace(vBefore, 1, vAfter, 1);
}

// 替换数据
x::bytearray& x::bytearray::replace(elem_type _Before, const elem_type* _After) noexcept
{
	elem_type		vBefore[2] = { _Before, '\0' };
	return this->replace(vBefore, 1, _After, x_posix_strlen(_After));
}

// 替换数据
x::bytearray& x::bytearray::replace(elem_type _Before, const elem_type* _After, size_type _LengthA) noexcept
{
	elem_type		vBefore[2] = { _Before, '\0' };
	return this->replace(vBefore, 1, _After, _LengthA);
}

// 替换数据
x::bytearray& x::bytearray::replace(elem_type _Before, const raw_type* _After, size_type _LengthA) noexcept
{
	elem_type		vBefore[2] = { _Before, '\0' };
	return this->replace(vBefore, 1, _After, _LengthA);
}

// 替换数据
x::bytearray& x::bytearray::replace(elem_type _Before, const x::bytearray& _After) noexcept
{
	elem_type		vBefore[2] = { _Before, '\0' };
	return this->replace(vBefore, 1, _After.data(), _After.size());
}





// 替换数据
x::bytearray& x::bytearray::replace(const elem_type* _Before, elem_type _After) noexcept
{
	elem_type		vAfter[2] = { _After, '\0' };
	return this->replace(_Before, x_posix_strlen(_Before), vAfter, 1);
}

// 替换数据
x::bytearray& x::bytearray::replace(const elem_type* _Before, const elem_type* _After) noexcept
{
	return this->replace(_Before, x_posix_strlen(_Before), _After, x_posix_strlen(_After));
}

// 替换数据
x::bytearray& x::bytearray::replace(const elem_type* _Before, const elem_type* _After, size_type _LengthA) noexcept
{
	return this->replace(_Before, x_posix_strlen(_Before), _After, _LengthA);
}

// 替换数据
x::bytearray& x::bytearray::replace(const elem_type* _Before, const raw_type* _After, size_type _LengthA) noexcept
{
	return this->replace(_Before, x_posix_strlen(_Before), _After, _LengthA);
}

// 替换数据
x::bytearray& x::bytearray::replace(const elem_type* _Before, const x::bytearray& _After) noexcept
{
	return this->replace(_Before, x_posix_strlen(_Before), _After.data(), _After.size());
}





// 替换数据
x::bytearray& x::bytearray::replace(const elem_type* _Before, size_type _LengthB, elem_type _After) noexcept
{
	elem_type		vAfter[2] = { _After, '\0' };
	return this->replace(_Before, _LengthB, vAfter, 1);
}

// 替换数据
x::bytearray& x::bytearray::replace(const elem_type* _Before, size_type _LengthB, const elem_type* _After) noexcept
{
	return this->replace(_Before, _LengthB, _After, x_posix_strlen(_After));
}

// 替换数据
x::bytearray& x::bytearray::replace(const elem_type* _Before, size_type _LengthB, const elem_type* _After, size_type _LengthA) noexcept
{
	return this->replace(_Before, _LengthB, (const raw_type*)_After, _LengthA);
}

// 替换数据
x::bytearray& x::bytearray::replace(const elem_type* _Before, size_type _LengthB, const raw_type* _After, size_type _LengthA) noexcept
{
	return this->replace((const raw_type*)_Before, _LengthB, _After, _LengthA);
}

// 替换数据
x::bytearray& x::bytearray::replace(const elem_type* _Before, size_type _LengthB, const x::bytearray& _After) noexcept
{
	return this->replace(_Before, _LengthB, _After.data(), _After.size());
}





// 替换数据
x::bytearray& x::bytearray::replace(const raw_type* _Before, size_type _LengthB, elem_type _After) noexcept
{
	elem_type		vAfter[2] = { _After, '\0' };
	return this->replace(_Before, _LengthB, vAfter, 1);
}

// 替换数据
x::bytearray& x::bytearray::replace(const raw_type* _Before, size_type _LengthB, const elem_type* _After) noexcept
{
	return this->replace(_Before, _LengthB, _After, x_posix_strlen(_After));
}

// 替换数据
x::bytearray& x::bytearray::replace(const raw_type* _Before, size_type _LengthB, const elem_type* _After, size_type _LengthA) noexcept
{
	return this->replace(_Before, _LengthB, (const raw_type*)_After, _LengthA);
}

// 替换数据
x::bytearray& x::bytearray::replace(const raw_type* _Before, size_type _LengthB, const raw_type* _After, size_type _LengthA) noexcept
{
	pos_type	vPos = x::bytearray::npos;
	do
	{
		vPos = this->find(_Before, _LengthB, vPos);
		if(x::bytearray::npos != vPos)
		{
			this->replace(vPos, _LengthB, _After, _LengthA);
			vPos += _LengthA;
		}
	} while(x::bytearray::npos != vPos);
	return *this;
}

// 替换数据
x::bytearray& x::bytearray::replace(const raw_type* _Before, size_type _LengthB, const x::bytearray& _After) noexcept
{
	return this->replace(_Before, _LengthB, _After.data(), _After.size());
}





// 替换数据
x::bytearray& x::bytearray::replace(const x::bytearray& _Before, elem_type _After) noexcept
{
	elem_type		vAfter[2] = { _After, '\0' };
	return this->replace(_Before.data(), _Before.size(), vAfter, 1);
}

// 替换数据
x::bytearray& x::bytearray::replace(const x::bytearray& _Before, const elem_type* _After) noexcept
{
	return this->replace(_Before.data(), _Before.size(), _After, x_posix_strlen(_After));
}

// 替换数据
x::bytearray& x::bytearray::replace(const x::bytearray& _Before, const elem_type* _After, size_type _LengthA) noexcept
{
	return this->replace(_Before.data(), _Before.size(), (const raw_type*)_After, _LengthA);
}

// 替换数据
x::bytearray& x::bytearray::replace(const x::bytearray& _Before, const raw_type* _After, size_type _LengthA) noexcept
{
	return this->replace(_Before.data(), _Before.size(), _After, _LengthA);
}

// 替换数据
x::bytearray& x::bytearray::replace(const x::bytearray& _Before, const x::bytearray& _After) noexcept
{
	return this->replace(_Before.data(), _Before.size(), _After.data(), _After.size());
}





// 按指定数据拆分字符串
std::list<x::bytearray> x::bytearray::split(elem_type _Char) const noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->split(vBytes, 1);
}

// 按指定数据拆分字符串
std::list<x::bytearray> x::bytearray::split(const elem_type* _Memory) const noexcept
{
	return this->split({_Memory, x_posix_strlen(_Memory)});
}

// 按指定数据拆分字符串
std::list<x::bytearray> x::bytearray::split(const elem_type* _Memory, size_type _Size) const noexcept
{
	return this->split({_Memory, _Size});
}

// 按指定数据拆分字符串
std::list<x::bytearray> x::bytearray::split(const raw_type* _Memory, size_type _Size) const noexcept
{
	return this->split({_Memory, _Size});
}

// 按指定数据拆分字符串
std::list<x::bytearray> x::bytearray::split(const x::bytearray& _String) const noexcept
{
	auto		vHeaderArray = std::list<x::bytearray>();
	auto		vLast = static_cast<size_type>(0U);
	auto		vSplitIndex = this->find(_String, vLast);
	while(vSplitIndex != x::bytearray::npos && _String.exist())
	{
		vHeaderArray.push_back(this->mid(vLast, vSplitIndex - vLast));
		vLast = vSplitIndex + 2;
		vSplitIndex = this->find(_String, vLast);
	}
	vHeaderArray.push_back(this->mid(vLast));

	return vHeaderArray;
}





// 判断一个字符是否为空白字符
bool x::bytearray::isSpace(elem_type _Char) noexcept
{
	// 如果宽字符是空白字符，则为真，否则假。
	return isspace(_Char);
}

// 格式化字符串 (char* [%s]) (wchar_t* [%ls])
x::bytearray x::bytearray::format(const char* _Format, ...) noexcept
{
	auto		vString = x::bytearray();
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
x::bytearray x::bytearray::toUpper() const noexcept
{
	auto		vStrUpper = *this;
	for(pos_type vIndex = 0; vIndex < vStrUpper.size(); ++vIndex)
	{
		vStrUpper[vIndex] = (elem_type)std::toupper(vStrUpper[vIndex]);
	}
	return vStrUpper;
}

// [conv] 转换至小写
x::bytearray x::bytearray::toLower() const noexcept
{
	auto		vStrUpper = *this;
	for(pos_type vIndex = 0; vIndex < vStrUpper.size(); ++vIndex)
	{
		vStrUpper[vIndex] = (elem_type)std::tolower(vStrUpper[vIndex]);
	}
	return vStrUpper;
}





// [conv] 转换至HEX
x::bytearray x::bytearray::toHex() const noexcept
{
	auto		vTarget = x::bytearray(this->size() * 2, '0');
	for (auto vIndex = 0U; vIndex < this->size(); ++vIndex)
	{
		x_posix_sprintf(vTarget.data() + (vIndex * 2), "%02X", (std::uint8_t)this->data()[vIndex]);
	}
	return vTarget;
}

// [conv] 从HEX转换
x::bytearray x::bytearray::fromHex(const elem_type* _Hex) noexcept
{
	return x::bytearray::fromHex(_Hex, x_posix_strlen(_Hex));
}

// [conv] 从HEX转换
x::bytearray x::bytearray::fromHex(const elem_type* _Hex, size_type _Size) noexcept
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
	auto		vTarget = x::bytearray(vLength, '\0');

	for (auto vIndex = 0U; vIndex < vLength; ++vIndex)
	{
		auto		vHexLeft = vFunctionHexToChar(vBuffer[vIndex * 2 + 0]);
		auto		vHexRight = vFunctionHexToChar(vBuffer[vIndex * 2 + 1]);
		vTarget[vIndex] = static_cast<char>(vHexLeft * 16 + vHexRight);
	}
	return vTarget;
}

// [conv] 从HEX转换
x::bytearray x::bytearray::fromHex(const raw_type* _Hex, size_type _Size) noexcept
{
	return x::bytearray::fromHex((const elem_type*)_Hex, _Size);
}

// [conv] 从HEX转换
x::bytearray x::bytearray::fromHex(const x::bytearray& _Hex) noexcept
{
	return x::bytearray::fromHex(_Hex.data(), _Hex.size());
}





// [conv] 转换至Base64
x::bytearray x::bytearray::toBase64() const noexcept
{
	uint8_t*	vEncodeBytes = nullptr;
	size_t 		vEncodeSize = 0;
	auto		vSync = x_base64_encode((const uint8_t*)this->data(), this->size(), &vEncodeBytes, &vEncodeSize);
	if(vSync && vEncodeBytes && vEncodeSize)
	{
		bytearray	vBase64(vEncodeBytes, vEncodeSize);
		x_posix_free(vEncodeBytes);
		return vBase64;
	}
	return {};
}

// [conv] 从Base64转换
x::bytearray x::bytearray::fromBase64(const elem_type* _Base64) noexcept
{
	return x::bytearray::fromBase64(_Base64, x_posix_strlen(_Base64));
}

// [conv] 从Base64转换
x::bytearray x::bytearray::fromBase64(const elem_type* _Base64, size_type _Size) noexcept
{
	uint8_t*	vDecodeBytes = nullptr;
	size_t 		vDecodeSize = 0;
	auto		vSync = x_base64_decode((const uint8_t*)_Base64, _Size, &vDecodeBytes, &vDecodeSize);
	if(vSync && vDecodeBytes && vDecodeSize)
	{
		bytearray	vDecode(vDecodeBytes, vDecodeSize);
		x_posix_free(vDecodeBytes);
		return vDecode;
	}
	return {};
}

// [conv] 从Base64转换
x::bytearray x::bytearray::fromBase64(const raw_type* _Base64, size_type _Size) noexcept
{
	return x::bytearray::fromBase64((const elem_type*)_Base64, _Size);
}

// [conv] 从Base64转换
x::bytearray x::bytearray::fromBase64(const x::bytearray& _Base64) noexcept
{
	return x::bytearray::fromBase64(_Base64.data(), _Base64.size());
}





// Standard enhancement function : stream <<
_XCOREAPI_ std::ostream& operator<< (std::ostream& _OStream, const x::bytearray& _String) noexcept
{
	for(auto vIndex = 0U; vIndex < _String.size(); ++vIndex)
	{
		_OStream << _String[vIndex];
	}
	return _OStream;
}

// Standard enhancement function : stream >>
_XCOREAPI_ std::istream& operator>> (std::istream& _IStream, x::bytearray& _String) noexcept
{
	_String.clear();
	do
	{
		auto		vChar = static_cast<x::bytearray::elem_type>(_IStream.get());
		if(vChar == '\n' || vChar == ' ')
		{
			break;
		}
		_String.append(vChar);
	} while(true);
	return _IStream;
}

// Standard enhancement function : getline
_XCOREAPI_ std::istream& getline(std::istream& _IStream, x::bytearray& _String, char _Delim) noexcept
{
	_String.clear();
	do
	{
		auto		vChar = static_cast<x::bytearray::elem_type>(_IStream.get());
		if(vChar == _Delim)
		{
			break;
		}
		_String.append(vChar);
	} while(true);
	return _IStream;
}

// Standard enhancement function : getline
_XCOREAPI_ std::istream& getline(std::istream& _IStream, x::bytearray& _String) noexcept
{
	return getline(_IStream, _String, '\n');
}
