#include <xanadu-core/bytearray.h>
#include <cstdarg>



// constructor
xanadu::bytearray::bytearray() noexcept = default;

// constructor
xanadu::bytearray::bytearray(size_type _Length, elem_type _Char) noexcept : _Allocator(_Length, _Char)
{
}

// constructor
xanadu::bytearray::bytearray(const elem_type* _Memory) noexcept : _Allocator(_Memory, x_posix_strlen(_Memory))
{
}

// constructor
xanadu::bytearray::bytearray(const elem_type* _Memory, size_type _Length) noexcept : _Allocator(_Memory, _Length)
{
}

// constructor
xanadu::bytearray::bytearray(const raw_type* _Memory, size_type _Length) noexcept : _Allocator(_Memory, _Length)
{
}

// constructor
xanadu::bytearray::bytearray(const xanadu::bytearray& _String) noexcept = default;

// constructor
xanadu::bytearray::bytearray(xanadu::bytearray&& _String) noexcept = default;

// destructor
xanadu::bytearray::~bytearray() noexcept = default;





// operator overload =
xanadu::bytearray& xanadu::bytearray::operator = (const elem_type* _Memory) noexcept
{
	if(this->resize(x_posix_strlen(_Memory)))
	{
		x_posix_memcpy(this->data(), _Memory, this->size());
	}
	return *this;
}

// operator overload =
xanadu::bytearray& xanadu::bytearray::operator = (const xanadu::bytearray& _String) noexcept
{
	if(this != &_String)
	{
		this->_Allocator = _String._Allocator;
	}
	return *this;
}

// operator overload =
xanadu::bytearray& xanadu::bytearray::operator = (xanadu::bytearray&& _String) noexcept
{
	if(this != &_String)
	{
		this->_Allocator = _String._Allocator;
	}
	return *this;
}





// operator overload +=
xanadu::bytearray& xanadu::bytearray::operator += (elem_type _Char) noexcept
{
	elem_type		vBytes[2] = {_Char, '\0'};
	return this->append(vBytes, 1);
}

// operator overload +=
xanadu::bytearray& xanadu::bytearray::operator += (const elem_type* _String) noexcept
{
	return this->append(_String, x_posix_strlen(_String));
}

// operator overload +=
xanadu::bytearray& xanadu::bytearray::operator += (const xanadu::bytearray& _String) noexcept
{
	return this->append(_String.data(), _String.size());
}





// operator overload +
xanadu::bytearray xanadu::bytearray::operator + (elem_type _Char) const noexcept
{
	auto		vTemp = *this;
	vTemp += _Char;
	return vTemp;
}

// operator overload +
xanadu::bytearray xanadu::bytearray::operator + (const elem_type* _String) const noexcept
{
	auto		vTemp = *this;
	vTemp += _String;
	return vTemp;
}

// operator overload +
xanadu::bytearray xanadu::bytearray::operator + (const xanadu::bytearray& _String) const noexcept
{
	auto		vTemp = *this;
	vTemp += _String;
	return vTemp;
}





// operator overload ==
bool xanadu::bytearray::operator == (elem_type _Char) const noexcept
{
	elem_type		vBytes[2] = {_Char, '\0'};
	return this->compare(vBytes, 1) == 0;
}

// operator overload ==
bool xanadu::bytearray::operator == (const elem_type* _String) const noexcept
{
	return this->compare(_String, x_posix_strlen(_String)) == 0;
}

// operator overload ==
bool xanadu::bytearray::operator == (const xanadu::bytearray& _String) const noexcept
{
	return this->compare(_String.data(), _String.size()) == 0;
}

// operator overload !=
bool xanadu::bytearray::operator != (elem_type _Char) const noexcept
{
	elem_type		vBytes[2] = {_Char, '\0'};
	return this->compare(vBytes, 1) != 0;
}

// operator overload !=
bool xanadu::bytearray::operator != (const elem_type* _String) const noexcept
{
	return this->compare(_String, x_posix_strlen(_String)) != 0;
}

// operator overload !=
bool xanadu::bytearray::operator != (const xanadu::bytearray& _String) const noexcept
{
	return this->compare(_String.data(), _String.size()) != 0;
}





// operator overload []
xanadu::bytearray::elem_type& xanadu::bytearray::operator [] (pos_type _Index)
{
	return this->_Allocator[_Index];
}

// operator overload []
xanadu::bytearray::elem_type xanadu::bytearray::operator [] (pos_type _Index) const
{
	return this->_Allocator[_Index];
}





// [opt] clear
void xanadu::bytearray::clear() noexcept
{
	this->_Allocator.clear();
}

// [opt] resize
bool xanadu::bytearray::resize(size_type _Length) noexcept
{
	return this->_Allocator.resize(_Length);
}

// [opt] reverse
bool xanadu::bytearray::reverse(size_type _Length) noexcept
{
	return this->_Allocator.reverse(_Length);
}





// [get] exist
bool xanadu::bytearray::exist() const noexcept
{
	return this->_Allocator.exist();
}

// [get] empty
bool xanadu::bytearray::empty() const noexcept
{
	return this->_Allocator.empty();
}

// [get] data
xanadu::bytearray::elem_type* xanadu::bytearray::data() noexcept
{
	return static_cast<xanadu::bytearray::elem_type*>(this->_Allocator.data());
}

// [get] data
const xanadu::bytearray::elem_type* xanadu::bytearray::data() const noexcept
{
	return static_cast<const xanadu::bytearray::elem_type*>(this->_Allocator.data());
}

// [get] size
xanadu::bytearray::size_type xanadu::bytearray::size() const noexcept
{
	return this->_Allocator.size();
}

// [get] capacity
xanadu::bytearray::size_type xanadu::bytearray::capacity() const noexcept
{
	return this->_Allocator.capacity();
}

// [get] surplus
xanadu::bytearray::size_type xanadu::bytearray::surplus() const noexcept
{
	return this->_Allocator.surplus();
}

// [get] max_size
xanadu::bytearray::size_type xanadu::bytearray::max_size() const noexcept
{
	return this->_Allocator.max_size();
}





// 从源中截取部分数据
xanadu::bytearray xanadu::bytearray::substr(pos_type _Pos) const noexcept
{
	return this->substr(_Pos, xanadu::bytearray::npos);
}

// 从源中截取部分数据
xanadu::bytearray xanadu::bytearray::substr(pos_type _Pos, size_type _Length) const noexcept
{
	if(_Pos < this->size())
	{
		if(_Length == xanadu::bytearray::npos)
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
xanadu::bytearray xanadu::bytearray::left(pos_type _Pos) const noexcept
{
	return this->substr(0, _Pos);
}

// 从源中截取部分数据
xanadu::bytearray xanadu::bytearray::right(pos_type _Pos) const noexcept
{
	return this->substr(this->size() - _Pos, xanadu::bytearray::npos);
}





// [mid] 从源中截取部分数据
xanadu::bytearray xanadu::bytearray::mid(pos_type _Pos) const noexcept
{
	return this->mid(_Pos, xanadu::bytearray::npos);
}

// [mid] 从源中截取部分数据
xanadu::bytearray xanadu::bytearray::mid(pos_type _Pos, size_type _Size) const noexcept
{
	return this->substr(_Pos, _Size);
}

// [mid] 从源中截取部分数据
xanadu::bytearray xanadu::bytearray::mid(const elem_type* _Left, const elem_type* _Right) const noexcept
{
	return this->mid(_Left, x_posix_strlen(_Left), _Right, x_posix_strlen(_Right));
}

// [mid] 从源中截取部分数据
xanadu::bytearray xanadu::bytearray::mid(const elem_type* _Left, size_type _LengthL, const elem_type* _Right) const noexcept
{
	return this->mid(_Left, _LengthL, _Right, x_posix_strlen(_Right));
}

// [mid] 从源中截取部分数据
xanadu::bytearray xanadu::bytearray::mid(const elem_type* _Left, const elem_type* _Right, size_type _LengthR) const noexcept
{
	return this->mid(_Left, x_posix_strlen(_Left), _Right, _LengthR);
}

// [mid] 从源中截取部分数据
xanadu::bytearray xanadu::bytearray::mid(const elem_type* _Left, size_type _LengthL, const elem_type* _Right, size_type _LengthR) const noexcept
{
	return this->mid((const raw_type*)_Left, _LengthL, (const raw_type*)_Right, _LengthR);
}

// [mid] 从源中截取部分数据
xanadu::bytearray xanadu::bytearray::mid(const raw_type* _Left, size_type _LengthL, const raw_type* _Right, size_type _LengthR) const noexcept
{
	pos_type 	vPosL = xanadu::bytearray::npos;
	pos_type 	vPosR = xanadu::bytearray::npos;

	if(_Left == nullptr || _Right == nullptr || _LengthL == 0 || _LengthR == 0)
	{
		return {};
	}

	vPosL = this->find(_Left, _LengthL, 0);
	if(xanadu::bytearray::npos != vPosL)
	{
		vPosL += _LengthL;
		vPosR = this->find(_Right, _LengthR, vPosL);
		if(xanadu::bytearray::npos != vPosR)
		{
			return this->substr(vPosL, vPosR - vPosL);
		}
	}
	return {};
}

// [mid] 从源中截取部分数据
xanadu::bytearray xanadu::bytearray::mid(const elem_type* _Left, const xanadu::bytearray& _Right) const noexcept
{
	return this->mid(_Left, x_posix_strlen(_Left), _Right.data(), _Right.size());
}

// [mid] 从源中截取部分数据
xanadu::bytearray xanadu::bytearray::mid(const xanadu::bytearray& _Left, const elem_type* _Right) const noexcept
{
	return this->mid(_Left.data(), _Left.size(), _Right, x_posix_strlen(_Right));
}

// [mid] 从源中截取部分数据
xanadu::bytearray xanadu::bytearray::mid(const xanadu::bytearray& _Left, const xanadu::bytearray& _Right) const noexcept
{
	return this->mid(_Left.data(), _Left.size(), _Right.data(), _Right.size());
}





// 检测源数据是否存在指定的前缀
bool xanadu::bytearray::startsWith(elem_type _Char) const noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->startsWith(vBytes, 1);
}

// 检测源数据是否存在指定的前缀
bool xanadu::bytearray::startsWith(const elem_type* _Memory) const noexcept
{
	return this->startsWith(_Memory, x_posix_strlen(_Memory));
}

// 检测源数据是否存在指定的前缀
bool xanadu::bytearray::startsWith(const elem_type* _Memory, size_type _Length) const noexcept
{
	return this->startsWith((const raw_type*)_Memory, _Length);
}

// 检测源数据是否存在指定的前缀
bool xanadu::bytearray::startsWith(const raw_type* _Memory, size_type _Length) const noexcept
{
	if(this->size() >= _Length)
	{
		return this->left(_Length).compare(_Memory, _Length) == 0;
	}
	return false;
}

// 检测源数据是否存在指定的前缀
bool xanadu::bytearray::startsWith(const xanadu::bytearray& _String) const noexcept
{
	return this->startsWith(_String.data(), _String.size());
}





// 检测源数据是否存在指定的后缀
bool xanadu::bytearray::endsWith(elem_type _Char) const noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->endsWith(vBytes, 1);
}

// 检测源数据是否存在指定的后缀
bool xanadu::bytearray::endsWith(const elem_type* _Memory) const noexcept
{
	return this->endsWith(_Memory, x_posix_strlen(_Memory));
}

// 检测源数据是否存在指定的后缀
bool xanadu::bytearray::endsWith(const elem_type* _Memory, size_type _Length) const noexcept
{
	return this->endsWith((const raw_type*)_Memory, _Length);
}

// 检测源数据是否存在指定的后缀
bool xanadu::bytearray::endsWith(const raw_type* _Memory, size_type _Length) const noexcept
{
	if(this->size() >= _Length)
	{
		return this->right(_Length).compare(_Memory, _Length) == 0;
	}
	return false;
}

// 检测源数据是否存在指定的后缀
bool xanadu::bytearray::endsWith(const xanadu::bytearray& _String) const noexcept
{
	return this->endsWith(_String.data(), _String.size());
}





// 从指定位置按正序查找数据
xanadu::bytearray::pos_type xanadu::bytearray::find(elem_type _Char) const noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->find(vBytes, 1, 0);
}

// 从指定位置按正序查找数据
xanadu::bytearray::pos_type xanadu::bytearray::find(elem_type _Char, pos_type _Pos) const noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->find(vBytes, 1, _Pos);
}

// 从指定位置按正序查找数据
xanadu::bytearray::pos_type xanadu::bytearray::find(const elem_type* _String) const noexcept
{
	return this->find(_String, x_posix_strlen(_String), 0);
}

// 从指定位置按正序查找数据
xanadu::bytearray::pos_type xanadu::bytearray::find(const elem_type* _String, pos_type _Pos) const noexcept
{
	return this->find(_String, x_posix_strlen(_String), _Pos);
}

// 从指定位置按正序查找数据
xanadu::bytearray::pos_type xanadu::bytearray::find(const elem_type* _String, size_type _Length, pos_type _Pos) const noexcept
{
	return this->find((const raw_type*)_String, _Length, _Pos);
}

// 从指定位置按正序查找数据
xanadu::bytearray::pos_type xanadu::bytearray::find(const raw_type* _Memory, size_type _Length, pos_type _Pos) const noexcept
{
	return this->_Allocator.find(_Memory, _Length, _Pos);
}

// 从指定位置按正序查找数据
xanadu::bytearray::pos_type xanadu::bytearray::find(const xanadu::bytearray& _String) const noexcept
{
	return this->find(_String.data(), _String.size(), 0);
}

// 从指定位置按正序查找数据
xanadu::bytearray::pos_type xanadu::bytearray::find(const xanadu::bytearray& _String, pos_type _Pos) const noexcept
{
	return this->find(_String.data(), _String.size(), _Pos);
}





// 从指定位置按倒序查找数据
xanadu::bytearray::pos_type xanadu::bytearray::rfind(elem_type _Char) const noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->rfind(vBytes, 1, this->size() - 1);
}

// 从指定位置按倒序查找数据
xanadu::bytearray::pos_type xanadu::bytearray::rfind(elem_type _Char, pos_type _Pos) const noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->rfind(vBytes, 1, _Pos);
}

// 从指定位置按倒序查找数据
xanadu::bytearray::pos_type xanadu::bytearray::rfind(const elem_type* _String) const noexcept
{
	return  this->rfind(_String, x_posix_strlen(_String), this->size() - 1);
}

// 从指定位置按倒序查找数据
xanadu::bytearray::pos_type xanadu::bytearray::rfind(const elem_type* _String, pos_type _Pos) const noexcept
{
	return  this->rfind(_String, x_posix_strlen(_String), _Pos);
}

// 从指定位置按倒序查找数据
xanadu::bytearray::pos_type xanadu::bytearray::rfind(const elem_type* _String, size_type _Length, pos_type _Pos) const noexcept
{
	return  this->rfind((const raw_type*)_String, _Length, _Pos);
}

// 从指定位置按倒序查找数据
xanadu::bytearray::pos_type xanadu::bytearray::rfind(const raw_type* _Memory, size_type _Length, pos_type _Pos) const noexcept
{
	return this->_Allocator.rfind(_Memory, _Length, _Pos);
}

// 从指定位置按倒序查找数据
xanadu::bytearray::pos_type xanadu::bytearray::rfind(const xanadu::bytearray& _String) const noexcept
{
	return this->rfind(_String.data(), _String.size(), this->size() - 1);
}

// 从指定位置按倒序查找数据
xanadu::bytearray::pos_type xanadu::bytearray::rfind(const xanadu::bytearray& _String, pos_type _Pos) const noexcept
{
	return this->rfind(_String.data(), _String.size(), _Pos);
}





// 检查是否包含指定数据
bool xanadu::bytearray::contains(elem_type _Char) const noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->contains(vBytes, 1);
}

// 检查是否包含指定数据
bool xanadu::bytearray::contains(const elem_type* _String) const noexcept
{
	return this->contains(_String, x_posix_strlen(_String));
}

// 检查是否包含指定数据
bool xanadu::bytearray::contains(const elem_type* _String, size_type _Length) const noexcept
{
	return this->contains((const raw_type*)_String, _Length);
}

// 检查是否包含指定数据
bool xanadu::bytearray::contains(const raw_type* _Memory, size_type _Length) const noexcept
{
	auto		vFind = this->find(_Memory, _Length, 0);
	return vFind != xanadu::bytearray::npos;
}

// 检查是否包含指定数据
bool xanadu::bytearray::contains(const xanadu::bytearray& _String) const noexcept
{
	return this->contains(_String.data(), _String.size());
}





// 检查是否与指定数据相同
int xanadu::bytearray::compare(elem_type _Char) const noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->compare(vBytes, 1);
}

// 检查是否与指定数据相同
int xanadu::bytearray::compare(const elem_type* _String) const noexcept
{
	return this->compare(_String, x_posix_strlen(_String));
}

// 检查是否与指定数据相同
int xanadu::bytearray::compare(const elem_type* _String, size_type _Length) const noexcept
{
	return this->compare((const raw_type*)_String, _Length);
}

// 检查是否与指定数据相同
int xanadu::bytearray::compare(const raw_type* _Memory, size_type _Length) const noexcept
{
	return this->_Allocator.compare(_Memory, _Length);
}

// 检查是否与指定数据相同
int xanadu::bytearray::compare(const xanadu::bytearray& _String) const noexcept
{
	return this->compare(_String.data(), _String.size());
}





// 在头部插入数据
xanadu::bytearray& xanadu::bytearray::prepend(elem_type _Char) noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->prepend(vBytes, 1);
}

// 在头部插入数据
xanadu::bytearray& xanadu::bytearray::prepend(const elem_type* _String) noexcept
{
	return this->prepend(_String, x_posix_strlen(_String));
}

// 在头部插入数据
xanadu::bytearray& xanadu::bytearray::prepend(const elem_type* _String, size_type _Size) noexcept
{
	return this->prepend((const raw_type*)_String, _Size);
}

// 在头部插入数据
xanadu::bytearray& xanadu::bytearray::prepend(const raw_type* _Memory, size_type _Size) noexcept
{
	return this->insert(0, _Memory, _Size);
}

// 在头部插入数据
xanadu::bytearray& xanadu::bytearray::prepend(const xanadu::bytearray& _String) noexcept
{
	return this->prepend(_String.data(), _String.size());
}





// 在尾部添加数据
xanadu::bytearray& xanadu::bytearray::append(elem_type _Char) noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->append(vBytes, 1);
}

// 在尾部添加数据
xanadu::bytearray& xanadu::bytearray::append(const elem_type* _String) noexcept
{
	return this->append(_String, x_posix_strlen(_String));
}

// 在尾部添加数据
xanadu::bytearray& xanadu::bytearray::append(const elem_type* _String, size_type _Size) noexcept
{
	return this->append((const raw_type*)_String, _Size);
}

// 在尾部添加数据
xanadu::bytearray& xanadu::bytearray::append(const raw_type* _Memory, size_type _Size) noexcept
{
	return this->insert(this->size(), _Memory, _Size);
}

// 在尾部添加数据
xanadu::bytearray& xanadu::bytearray::append(const xanadu::bytearray& _String) noexcept
{
	return this->append(_String.data(), _String.size());
}





// 在指定下标处插入数据
xanadu::bytearray& xanadu::bytearray::insert(pos_type _Pos, elem_type _Char) noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->insert(_Pos, vBytes, 1);
}

// 在指定下标处插入数据
xanadu::bytearray& xanadu::bytearray::insert(pos_type _Pos, size_type _Count, elem_type _Char) noexcept
{
	auto		vString = xanadu::bytearray(_Count, _Char);
	return this->insert(_Pos, vString.data(), vString.size());
}

// 在指定下标处插入数据
xanadu::bytearray& xanadu::bytearray::insert(pos_type _Pos, const elem_type* _String) noexcept
{
	return this->insert(_Pos, _String, x_posix_strlen(_String));
}

// 在指定下标处插入数据
xanadu::bytearray& xanadu::bytearray::insert(pos_type _Pos, const elem_type* _String, size_type _Length) noexcept
{
	return this->insert(_Pos, (const raw_type*)_String, _Length);
}

// 在指定下标处插入数据
xanadu::bytearray& xanadu::bytearray::insert(pos_type _Pos, const raw_type* _Memory, size_type _Length) noexcept
{
	this->_Allocator.insert(_Pos, _Memory, _Length);
	return *this;
}

// 在指定下标处插入数据
xanadu::bytearray& xanadu::bytearray::insert(pos_type _Pos, const xanadu::bytearray& _String) noexcept
{
	return this->insert(_Pos, _String.data(), _String.size());
}





// 移除下标 pos 处的 length 长度数据
xanadu::bytearray& xanadu::bytearray::remove(pos_type _Pos, size_type _Length) noexcept
{
	this->_Allocator.remove(_Pos, _Length);
	return *this;
}

// 删除与参数相同的数据
xanadu::bytearray& xanadu::bytearray::remove(elem_type _Char) noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->remove(vBytes, 1);
}

// 删除与参数相同的数据
xanadu::bytearray& xanadu::bytearray::remove(const elem_type* _String) noexcept
{
	return this->remove(_String, x_posix_strlen(_String));
}

// 删除与参数相同的数据
xanadu::bytearray& xanadu::bytearray::remove(const elem_type* _String, size_type _Length) noexcept
{
	return this->remove((const raw_type*)_String, _Length);
}

// 删除与参数相同的数据
xanadu::bytearray& xanadu::bytearray::remove(const raw_type* _Memory, size_type _Length) noexcept
{
	auto		vFind = this->find(_Memory, _Length, 0);
	if(vFind != xanadu::bytearray::npos)
	{
		return this->remove(vFind, _Length);
	}
	return *this;
}

// 删除与参数相同的数据
xanadu::bytearray& xanadu::bytearray::remove(const xanadu::bytearray& _String) noexcept
{
	return this->remove(_String.data(), _String.size());
}





// 替换数据
xanadu::bytearray& xanadu::bytearray::replace(pos_type _Pos, size_type _Length, elem_type _After) noexcept
{
	elem_type		vAfter[2] = { _After, '\0' };
	return this->replace(_Pos, _Length, vAfter, 1);
}

// 替换数据
xanadu::bytearray& xanadu::bytearray::replace(pos_type _Pos, size_type _Length, const elem_type* _After) noexcept
{
	return this->replace(_Pos, _Length, _After, x_posix_strlen(_After));
}

// 替换数据
xanadu::bytearray& xanadu::bytearray::replace(pos_type _Pos, size_type _Length, const elem_type* _After, size_type _LengthA) noexcept
{
	return this->replace(_Pos, _Length, (const raw_type*)_After, _LengthA);
}

// 替换数据
xanadu::bytearray& xanadu::bytearray::replace(pos_type _Pos, size_type _Length, const raw_type* _After, size_type _LengthA) noexcept
{
	this->_Allocator.replace(_Pos, _Length, _After, _LengthA);
	return *this;
}

// 替换数据
xanadu::bytearray& xanadu::bytearray::replace(pos_type _Pos, size_type _Length, const xanadu::bytearray& _After) noexcept
{
	return this->replace(_Pos, _Length, _After.data(), _After.size());
}





// 替换数据
xanadu::bytearray& xanadu::bytearray::replace(elem_type _Before, elem_type _After) noexcept
{
	elem_type		vBefore[2] = { _Before, '\0' };
	elem_type		vAfter[2] = { _After, '\0' };
	return this->replace(vBefore, 1, vAfter, 1);
}

// 替换数据
xanadu::bytearray& xanadu::bytearray::replace(elem_type _Before, const elem_type* _After) noexcept
{
	elem_type		vBefore[2] = { _Before, '\0' };
	return this->replace(vBefore, 1, _After, x_posix_strlen(_After));
}

// 替换数据
xanadu::bytearray& xanadu::bytearray::replace(elem_type _Before, const elem_type* _After, size_type _LengthA) noexcept
{
	elem_type		vBefore[2] = { _Before, '\0' };
	return this->replace(vBefore, 1, _After, _LengthA);
}

// 替换数据
xanadu::bytearray& xanadu::bytearray::replace(elem_type _Before, const raw_type* _After, size_type _LengthA) noexcept
{
	elem_type		vBefore[2] = { _Before, '\0' };
	return this->replace(vBefore, 1, _After, _LengthA);
}

// 替换数据
xanadu::bytearray& xanadu::bytearray::replace(elem_type _Before, const xanadu::bytearray& _After) noexcept
{
	elem_type		vBefore[2] = { _Before, '\0' };
	return this->replace(vBefore, 1, _After.data(), _After.size());
}





// 替换数据
xanadu::bytearray& xanadu::bytearray::replace(const elem_type* _Before, elem_type _After) noexcept
{
	elem_type		vAfter[2] = { _After, '\0' };
	return this->replace(_Before, x_posix_strlen(_Before), vAfter, 1);
}

// 替换数据
xanadu::bytearray& xanadu::bytearray::replace(const elem_type* _Before, const elem_type* _After) noexcept
{
	return this->replace(_Before, x_posix_strlen(_Before), _After, x_posix_strlen(_After));
}

// 替换数据
xanadu::bytearray& xanadu::bytearray::replace(const elem_type* _Before, const elem_type* _After, size_type _LengthA) noexcept
{
	return this->replace(_Before, x_posix_strlen(_Before), _After, _LengthA);
}

// 替换数据
xanadu::bytearray& xanadu::bytearray::replace(const elem_type* _Before, const raw_type* _After, size_type _LengthA) noexcept
{
	return this->replace(_Before, x_posix_strlen(_Before), _After, _LengthA);
}

// 替换数据
xanadu::bytearray& xanadu::bytearray::replace(const elem_type* _Before, const xanadu::bytearray& _After) noexcept
{
	return this->replace(_Before, x_posix_strlen(_Before), _After.data(), _After.size());
}





// 替换数据
xanadu::bytearray& xanadu::bytearray::replace(const elem_type* _Before, size_type _LengthB, elem_type _After) noexcept
{
	elem_type		vAfter[2] = { _After, '\0' };
	return this->replace(_Before, _LengthB, vAfter, 1);
}

// 替换数据
xanadu::bytearray& xanadu::bytearray::replace(const elem_type* _Before, size_type _LengthB, const elem_type* _After) noexcept
{
	return this->replace(_Before, _LengthB, _After, x_posix_strlen(_After));
}

// 替换数据
xanadu::bytearray& xanadu::bytearray::replace(const elem_type* _Before, size_type _LengthB, const elem_type* _After, size_type _LengthA) noexcept
{
	return this->replace(_Before, _LengthB, (const raw_type*)_After, _LengthA);
}

// 替换数据
xanadu::bytearray& xanadu::bytearray::replace(const elem_type* _Before, size_type _LengthB, const raw_type* _After, size_type _LengthA) noexcept
{
	return this->replace((const raw_type*)_Before, _LengthB, _After, _LengthA);
}

// 替换数据
xanadu::bytearray& xanadu::bytearray::replace(const elem_type* _Before, size_type _LengthB, const xanadu::bytearray& _After) noexcept
{
	return this->replace(_Before, _LengthB, _After.data(), _After.size());
}





// 替换数据
xanadu::bytearray& xanadu::bytearray::replace(const raw_type* _Before, size_type _LengthB, elem_type _After) noexcept
{
	elem_type		vAfter[2] = { _After, '\0' };
	return this->replace(_Before, _LengthB, vAfter, 1);
}

// 替换数据
xanadu::bytearray& xanadu::bytearray::replace(const raw_type* _Before, size_type _LengthB, const elem_type* _After) noexcept
{
	return this->replace(_Before, _LengthB, _After, x_posix_strlen(_After));
}

// 替换数据
xanadu::bytearray& xanadu::bytearray::replace(const raw_type* _Before, size_type _LengthB, const elem_type* _After, size_type _LengthA) noexcept
{
	return this->replace(_Before, _LengthB, (const raw_type*)_After, _LengthA);
}

// 替换数据
xanadu::bytearray& xanadu::bytearray::replace(const raw_type* _Before, size_type _LengthB, const raw_type* _After, size_type _LengthA) noexcept
{
	pos_type	vPos = xanadu::bytearray::npos;
	do
	{
		vPos = this->find(_Before, _LengthB, vPos);
		if(xanadu::bytearray::npos != vPos)
		{
			this->replace(vPos, _LengthB, _After, _LengthA);
			vPos += _LengthA;
		}
	} while(xanadu::bytearray::npos != vPos);
	return *this;
}

// 替换数据
xanadu::bytearray& xanadu::bytearray::replace(const raw_type* _Before, size_type _LengthB, const xanadu::bytearray& _After) noexcept
{
	return this->replace(_Before, _LengthB, _After.data(), _After.size());
}





// 替换数据
xanadu::bytearray& xanadu::bytearray::replace(const xanadu::bytearray& _Before, elem_type _After) noexcept
{
	elem_type		vAfter[2] = { _After, '\0' };
	return this->replace(_Before.data(), _Before.size(), vAfter, 1);
}

// 替换数据
xanadu::bytearray& xanadu::bytearray::replace(const xanadu::bytearray& _Before, const elem_type* _After) noexcept
{
	return this->replace(_Before.data(), _Before.size(), _After, x_posix_strlen(_After));
}

// 替换数据
xanadu::bytearray& xanadu::bytearray::replace(const xanadu::bytearray& _Before, const elem_type* _After, size_type _LengthA) noexcept
{
	return this->replace(_Before.data(), _Before.size(), (const raw_type*)_After, _LengthA);
}

// 替换数据
xanadu::bytearray& xanadu::bytearray::replace(const xanadu::bytearray& _Before, const raw_type* _After, size_type _LengthA) noexcept
{
	return this->replace(_Before.data(), _Before.size(), _After, _LengthA);
}

// 替换数据
xanadu::bytearray& xanadu::bytearray::replace(const xanadu::bytearray& _Before, const xanadu::bytearray& _After) noexcept
{
	return this->replace(_Before.data(), _Before.size(), _After.data(), _After.size());
}





// 按指定数据拆分字符串
std::list<xanadu::bytearray> xanadu::bytearray::split(elem_type _Char) const noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->split(vBytes, 1);
}

// 按指定数据拆分字符串
std::list<xanadu::bytearray> xanadu::bytearray::split(const elem_type* _Memory) const noexcept
{
	return this->split({_Memory, x_posix_strlen(_Memory)});
}

// 按指定数据拆分字符串
std::list<xanadu::bytearray> xanadu::bytearray::split(const elem_type* _Memory, size_type _Size) const noexcept
{
	return this->split({_Memory, _Size});
}

// 按指定数据拆分字符串
std::list<xanadu::bytearray> xanadu::bytearray::split(const raw_type* _Memory, size_type _Size) const noexcept
{
	return this->split({_Memory, _Size});
}

// 按指定数据拆分字符串
std::list<xanadu::bytearray> xanadu::bytearray::split(const xanadu::bytearray& _String) const noexcept
{
	auto		vHeaderArray = std::list<xanadu::bytearray>();
	auto		vLast = static_cast<size_type>(0U);
	auto		vSplitIndex = this->find(_String, vLast);
	while(vSplitIndex != xanadu::bytearray::npos && _String.exist())
	{
		vHeaderArray.push_back(this->mid(vLast, vSplitIndex - vLast));
		vLast = vSplitIndex + 2;
		vSplitIndex = this->find(_String, vLast);
	}
	vHeaderArray.push_back(this->mid(vLast));

	return vHeaderArray;
}





// 判断一个字符是否为空白字符
bool xanadu::bytearray::isSpace(elem_type _Char) noexcept
{
	// 如果宽字符是空白字符，则为真，否则假。
	return isspace(_Char);
}

// 格式化字符串 (char* [%s]) (wchar_t* [%ls])
xanadu::bytearray xanadu::bytearray::format(const char* _Format, ...) noexcept
{
	auto		vString = xanadu::bytearray();
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
xanadu::bytearray xanadu::bytearray::toUpper() const noexcept
{
	auto		vStrUpper = *this;
	for(pos_type vIndex = 0; vIndex < vStrUpper.size(); ++vIndex)
	{
		vStrUpper[vIndex] = (elem_type)std::toupper(vStrUpper[vIndex]);
	}
	return vStrUpper;
}

// [conv] 转换至小写
xanadu::bytearray xanadu::bytearray::toLower() const noexcept
{
	auto		vStrUpper = *this;
	for(pos_type vIndex = 0; vIndex < vStrUpper.size(); ++vIndex)
	{
		vStrUpper[vIndex] = (elem_type)std::tolower(vStrUpper[vIndex]);
	}
	return vStrUpper;
}





// [conv] 转换至HEX
xanadu::bytearray xanadu::bytearray::toHex() const noexcept
{
	auto		vTarget = xanadu::bytearray(this->size() * 2, '0');
	for (auto vIndex = 0U; vIndex < this->size(); ++vIndex)
	{
		x_posix_sprintf(vTarget.data() + (vIndex * 2), "%02X", (std::uint8_t)this->data()[vIndex]);
	}
	return vTarget;
}

// [conv] 从HEX转换
xanadu::bytearray xanadu::bytearray::fromHex(const elem_type* _String) noexcept
{
	return xanadu::bytearray::fromHex({_String, x_posix_strlen(_String)});
}

// [conv] 从HEX转换
xanadu::bytearray xanadu::bytearray::fromHex(const elem_type* _String, size_type _Size) noexcept
{
	return xanadu::bytearray::fromHex({_String, _Size});
}

// [conv] 从HEX转换
xanadu::bytearray xanadu::bytearray::fromHex(const xanadu::bytearray& _Hex) noexcept
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
	auto		vTarget = xanadu::bytearray(vLength, '\0');

	for (auto vIndex = 0U; vIndex < vLength; ++vIndex)
	{
		auto		vHexLeft = vFunctionHexToChar(vBuffer[vIndex * 2 + 0]);
		auto		vHexRight = vFunctionHexToChar(vBuffer[vIndex * 2 + 1]);
		vTarget[vIndex] = static_cast<char>(vHexLeft * 16 + vHexRight);
	}
	return vTarget;
}





// [convert] convert to char
char xanadu::bytearray::toChar(bool* _Ok, int _Base) const noexcept
{
	return static_cast<char>(this->toLLong(_Ok, _Base));
}

// [convert] convert to unsigned char
unsigned char xanadu::bytearray::toUChar(bool* _Ok, int _Base) const noexcept
{
	return static_cast<unsigned char>(this->toULLong(_Ok, _Base));
}

// [convert] convert to short
short xanadu::bytearray::toShort(bool* _Ok, int _Base) const noexcept
{
	return static_cast<short>(this->toLLong(_Ok, _Base));
}

// [convert] convert to short
unsigned short xanadu::bytearray::toUShort(bool* _Ok, int _Base) const noexcept
{
	return static_cast<unsigned short>(this->toULLong(_Ok, _Base));
}

// [convert] convert to int
int xanadu::bytearray::toInt(bool* _Ok, int _Base) const noexcept
{
	return static_cast<int>(this->toLLong(_Ok, _Base));
}

// [convert] convert to unsigned int
unsigned int xanadu::bytearray::toUInt(bool* _Ok, int _Base) const noexcept
{
	return static_cast<unsigned int>(this->toULLong(_Ok, _Base));
}

// [convert] convert to long
long xanadu::bytearray::toLong(bool* _Ok, int _Base) const noexcept
{
	return static_cast<long>(this->toLLong(_Ok, _Base));
}

// [convert] convert to unsigned long
unsigned long xanadu::bytearray::toULong(bool* _Ok, int _Base) const noexcept
{
	return static_cast<unsigned long>(this->toULLong(_Ok, _Base));
}

// [convert] convert to long long
long long xanadu::bytearray::toLLong(bool* _Ok, int _Base) const noexcept
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
unsigned long long xanadu::bytearray::toULLong(bool* _Ok, int _Base) const noexcept
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
float xanadu::bytearray::toFloat(bool* _Ok) const noexcept
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
double xanadu::bytearray::toDouble(bool* _Ok) const noexcept
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
xanadu::bytearray& xanadu::bytearray::setNumber(char _Value, int _Base) noexcept
{
	this->setNumber(static_cast<long long>(_Value), _Base);
	return *this;
}

// [convert] convert from number
xanadu::bytearray& xanadu::bytearray::setNumber(unsigned char _Value, int _Base) noexcept
{
	this->setNumber(static_cast<unsigned long long>(_Value), _Base);
	return *this;
}

// [convert] convert from number
xanadu::bytearray& xanadu::bytearray::setNumber(short _Value, int _Base) noexcept
{
	this->setNumber(static_cast<long long>(_Value), _Base);
	return *this;
}

// [convert] convert from number
xanadu::bytearray& xanadu::bytearray::setNumber(unsigned short _Value, int _Base) noexcept
{
	this->setNumber(static_cast<unsigned long long>(_Value), _Base);
	return *this;
}

// [convert] convert from number
xanadu::bytearray& xanadu::bytearray::setNumber(int _Value, int _Base) noexcept
{
	this->setNumber(static_cast<long long>(_Value), _Base);
	return *this;
}

// [convert] convert from number
xanadu::bytearray& xanadu::bytearray::setNumber(unsigned int _Value, int _Base) noexcept
{
	this->setNumber(static_cast<unsigned long long>(_Value), _Base);
	return *this;
}

// [convert] convert from number
xanadu::bytearray& xanadu::bytearray::setNumber(long _Value, int _Base) noexcept
{
	this->setNumber(static_cast<long long>(_Value), _Base);
	return *this;
}

// [convert] convert from number
xanadu::bytearray& xanadu::bytearray::setNumber(unsigned long _Value, int _Base) noexcept
{
	this->setNumber(static_cast<unsigned long long>(_Value), _Base);
	return *this;
}

// [convert] convert from number
xanadu::bytearray& xanadu::bytearray::setNumber(long long _Value, int _Base) noexcept
{
	if(2 <= _Base && _Base <= 36)
	{
		*this = std::to_string(_Value).data();
	}
	return *this;
}

// [convert] convert from number
xanadu::bytearray& xanadu::bytearray::setNumber(unsigned long long _Value, int _Base) noexcept
{
	if(2 <= _Base && _Base <= 36)
	{
		*this = std::to_string(_Value).data();
	}
	return *this;
}

// [convert] convert from number
xanadu::bytearray& xanadu::bytearray::setNumber(float _Value, char _Format, int _Prec) noexcept
{
	XANADU_UNUSED(_Format);
	XANADU_UNUSED(_Prec);

	*this = std::to_string(_Value).data();
	return *this;
}

// [convert] convert from number
xanadu::bytearray& xanadu::bytearray::setNumber(double _Value, char _Format, int _Prec) noexcept
{
	XANADU_UNUSED(_Format);
	XANADU_UNUSED(_Prec);

	*this = std::to_string(_Value).data();
	return *this;
}





// [convert] convert from number
xanadu::bytearray xanadu::bytearray::number(char _Value, int _Base) noexcept
{
	auto		vValue = xanadu::bytearray();
	vValue.setNumber(_Value, _Base);
	return vValue;
}

// [convert] convert from number
xanadu::bytearray xanadu::bytearray::number(unsigned char _Value, int _Base) noexcept
{
	auto		vValue = xanadu::bytearray();
	vValue.setNumber(_Value, _Base);
	return vValue;
}

// [convert] convert from number
xanadu::bytearray xanadu::bytearray::number(short _Value, int _Base) noexcept
{
	auto		vValue = xanadu::bytearray();
	vValue.setNumber(_Value, _Base);
	return vValue;
}

// [convert] convert from number
xanadu::bytearray xanadu::bytearray::number(unsigned short _Value, int _Base) noexcept
{
	auto		vValue = xanadu::bytearray();
	vValue.setNumber(_Value, _Base);
	return vValue;
}

// [convert] convert from number
xanadu::bytearray xanadu::bytearray::number(int _Value, int _Base) noexcept
{
	auto		vValue = xanadu::bytearray();
	vValue.setNumber(_Value, _Base);
	return vValue;
}

// [convert] convert from number
xanadu::bytearray xanadu::bytearray::number(unsigned int _Value, int _Base) noexcept
{
	auto		vValue = xanadu::bytearray();
	vValue.setNumber(_Value, _Base);
	return vValue;
}

// [convert] convert from number
xanadu::bytearray xanadu::bytearray::number(long _Value, int _Base) noexcept
{
	auto		vValue = xanadu::bytearray();
	vValue.setNumber(_Value, _Base);
	return vValue;
}

// [convert] convert from number
xanadu::bytearray xanadu::bytearray::number(unsigned long _Value, int _Base) noexcept
{
	auto		vValue = xanadu::bytearray();
	vValue.setNumber(_Value, _Base);
	return vValue;
}

// [convert] convert from number
xanadu::bytearray xanadu::bytearray::number(long long _Value, int _Base) noexcept
{
	auto		vValue = xanadu::bytearray();
	vValue.setNumber(_Value, _Base);
	return vValue;
}

// [convert] convert from number
xanadu::bytearray xanadu::bytearray::number(unsigned long long _Value, int _Base) noexcept
{
	auto		vValue = xanadu::bytearray();
	vValue.setNumber(_Value, _Base);
	return vValue;
}

// [convert] convert from number
xanadu::bytearray xanadu::bytearray::number(float _Value, char _Format, int _Prec) noexcept
{
	auto		vValue = xanadu::bytearray();
	vValue.setNumber(_Value, _Format, _Prec);
	return vValue;
}

// [convert] convert from number
xanadu::bytearray xanadu::bytearray::number(double _Value, char _Format, int _Prec) noexcept
{
	auto		vValue = xanadu::bytearray();
	vValue.setNumber(_Value, _Format, _Prec);
	return vValue;
}





// Standard enhancement function : stream <<
_XCOREAPI_ std::ostream& operator<< (std::ostream& _OStream, const xanadu::bytearray& _String) noexcept
{
	for(auto vIndex = 0U; vIndex < _String.size(); ++vIndex)
	{
		_OStream << _String[vIndex];
	}
	return _OStream;
}

// Standard enhancement function : stream >>
_XCOREAPI_ std::istream& operator>> (std::istream& _IStream, xanadu::bytearray& _String) noexcept
{
	_String.clear();
	do
	{
		auto		vChar = static_cast<xanadu::bytearray::elem_type>(_IStream.get());
		if(vChar == '\n' || vChar == ' ')
		{
			break;
		}
		_String.append(vChar);
	} while(true);
	return _IStream;
}

// Standard enhancement function : getline
_XCOREAPI_ std::istream& getline(std::istream& _IStream, xanadu::bytearray& _String, char _Delim) noexcept
{
	_String.clear();
	do
	{
		auto		vChar = static_cast<xanadu::bytearray::elem_type>(_IStream.get());
		if(vChar == _Delim)
		{
			break;
		}
		_String.append(vChar);
	} while(true);
	return _IStream;
}

// Standard enhancement function : getline
_XCOREAPI_ std::istream& getline(std::istream& _IStream, xanadu::bytearray& _String) noexcept
{
	return getline(_IStream, _String, '\n');
}
