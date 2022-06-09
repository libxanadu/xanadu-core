#include <xanadu-core/XByteArray.h>
#include <cstdarg>



// constructor
XByteArray::XByteArray() noexcept = default;

// constructor
XByteArray::XByteArray(size_type _Length, elem_type _Char) noexcept : _Allocator(_Length, _Char)
{
}

// constructor
XByteArray::XByteArray(const elem_type* _Memory) noexcept : _Allocator(_Memory, x_posix_strlen(_Memory))
{
}

// constructor
XByteArray::XByteArray(const elem_type* _Memory, size_type _Length) noexcept : _Allocator(_Memory, _Length)
{
}

// constructor
XByteArray::XByteArray(const void* _Memory, size_type _Length) noexcept : _Allocator(_Memory, _Length)
{
}

// constructor
XByteArray::XByteArray(const XByteArray& _Bytes) noexcept = default;

// constructor
XByteArray::XByteArray(XByteArray&& _Bytes) noexcept = default;

// destructor
XByteArray::~XByteArray() noexcept = default;





// operator overload =
XByteArray& XByteArray::operator = (const elem_type* _Memory) noexcept
{
	if(this->resize(x_posix_strlen(_Memory)))
	{
		x_posix_memcpy(this->data(), _Memory, this->size());
	}
	return *this;
}

// operator overload =
XByteArray& XByteArray::operator = (const XByteArray& _Bytes) noexcept
{
	if(this != &_Bytes)
	{
		this->_Allocator = _Bytes._Allocator;
	}
	return *this;
}

// operator overload =
XByteArray& XByteArray::operator = (XByteArray&& _Bytes) noexcept
{
	if(this != &_Bytes)
	{
		this->_Allocator = _Bytes._Allocator;
	}
	return *this;
}





// operator overload +=
XByteArray& XByteArray::operator += (elem_type _Char) noexcept
{
	elem_type		vBytes[2] = {_Char, '\0'};
	return this->append(vBytes, 1);
}

// operator overload +=
XByteArray& XByteArray::operator += (const elem_type* _Bytes) noexcept
{
	return this->append(_Bytes, x_posix_strlen(_Bytes));
}

// operator overload +=
XByteArray& XByteArray::operator += (const XByteArray& _Bytes) noexcept
{
	return this->append(_Bytes.data(), _Bytes.size());
}





// operator overload +
XByteArray XByteArray::operator + (elem_type _Char) const noexcept
{
	auto		vTemp = *this;
	vTemp += _Char;
	return vTemp;
}

// operator overload +
XByteArray XByteArray::operator + (const elem_type* _Bytes) const noexcept
{
	auto		vTemp = *this;
	vTemp += _Bytes;
	return vTemp;
}

// operator overload +
XByteArray XByteArray::operator + (const XByteArray& _Bytes) const noexcept
{
	auto		vTemp = *this;
	vTemp += _Bytes;
	return vTemp;
}





// operator overload ==
bool XByteArray::operator == (elem_type _Char) const noexcept
{
	elem_type		vBytes[2] = {_Char, '\0'};
	return this->compare(vBytes, 1) == 0;
}

// operator overload ==
bool XByteArray::operator == (const elem_type* _Bytes) const noexcept
{
	return this->compare(_Bytes, x_posix_strlen(_Bytes)) == 0;
}

// operator overload ==
bool XByteArray::operator == (const XByteArray& _Bytes) const noexcept
{
	return this->compare(_Bytes.data(), _Bytes.size()) == 0;
}

// operator overload !=
bool XByteArray::operator != (elem_type _Char) const noexcept
{
	elem_type		vBytes[2] = {_Char, '\0'};
	return this->compare(vBytes, 1) != 0;
}

// operator overload !=
bool XByteArray::operator != (const elem_type* _Bytes) const noexcept
{
	return this->compare(_Bytes, x_posix_strlen(_Bytes)) != 0;
}

// operator overload !=
bool XByteArray::operator != (const XByteArray& _Bytes) const noexcept
{
	return this->compare(_Bytes.data(), _Bytes.size()) != 0;
}





// operator overload []
XByteArray::elem_type& XByteArray::operator [] (pos_type _Index)
{
	return this->_Allocator[_Index];
}

// operator overload []
XByteArray::elem_type XByteArray::operator [] (pos_type _Index) const
{
	return this->_Allocator[_Index];
}





// [opt] clear
void XByteArray::clear() noexcept
{
	this->_Allocator.clear();
}

// [opt] resize
bool XByteArray::resize(size_type _Length) noexcept
{
	return this->_Allocator.resize(_Length);
}

// [opt] reverse
bool XByteArray::reverse(size_type _Length) noexcept
{
	return this->_Allocator.reverse(_Length);
}





// [get] exist
bool XByteArray::exist() const noexcept
{
	return this->_Allocator.exist();
}

// [get] empty
bool XByteArray::empty() const noexcept
{
	return this->_Allocator.empty();
}

// [get] data
XByteArray::elem_type* XByteArray::data() noexcept
{
	return static_cast<XByteArray::elem_type*>(this->_Allocator.data());
}

// [get] data
const XByteArray::elem_type* XByteArray::data() const noexcept
{
	return static_cast<const XByteArray::elem_type*>(this->_Allocator.data());
}

// [get] size
XByteArray::size_type XByteArray::size() const noexcept
{
	return this->_Allocator.size();
}

// [get] capacity
XByteArray::size_type XByteArray::capacity() const noexcept
{
	return this->_Allocator.capacity();
}

// [get] surplus
XByteArray::size_type XByteArray::surplus() const noexcept
{
	return this->_Allocator.surplus();
}

// [get] max_size
XByteArray::size_type XByteArray::max_size() const noexcept
{
	return this->_Allocator.max_size();
}





// 从源中截取部分数据
XByteArray XByteArray::substr(pos_type _Pos) const noexcept
{
	return this->substr(_Pos, XByteArray::npos);
}

// 从源中截取部分数据
XByteArray XByteArray::substr(pos_type _Pos, size_type _Length) const noexcept
{
	if(_Pos < this->size())
	{
		if(_Length == XByteArray::npos)
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
XByteArray XByteArray::left(pos_type _Pos) const noexcept
{
	return this->substr(0, _Pos);
}

// 从源中截取部分数据
XByteArray XByteArray::right(pos_type _Pos) const noexcept
{
	return this->substr(this->size() - _Pos, XByteArray::npos);
}





// [mid] 从源中截取部分数据
XByteArray XByteArray::mid(pos_type _Pos) const noexcept
{
	return this->mid(_Pos, XByteArray::npos);
}

// [mid] 从源中截取部分数据
XByteArray XByteArray::mid(pos_type _Pos, size_type _Size) const noexcept
{
	return this->substr(_Pos, _Size);
}

// [mid] 从源中截取部分数据
XByteArray XByteArray::mid(const elem_type* _Left, const elem_type* _Right) const noexcept
{
	return this->mid(_Left, x_posix_strlen(_Left), _Right, x_posix_strlen(_Right));
}

// [mid] 从源中截取部分数据
XByteArray XByteArray::mid(const elem_type* _Left, size_type _LengthL, const elem_type* _Right) const noexcept
{
	return this->mid(_Left, _LengthL, _Right, x_posix_strlen(_Right));
}

// [mid] 从源中截取部分数据
XByteArray XByteArray::mid(const elem_type* _Left, const elem_type* _Right, size_type _LengthR) const noexcept
{
	return this->mid(_Left, x_posix_strlen(_Left), _Right, _LengthR);
}

// [mid] 从源中截取部分数据
XByteArray XByteArray::mid(const elem_type* _Left, size_type _LengthL, const elem_type* _Right, size_type _LengthR) const noexcept
{
	return this->mid((const void*)_Left, _LengthL, (const void*)_Right, _LengthR);
}

// [mid] 从源中截取部分数据
XByteArray XByteArray::mid(const void* _Left, size_type _LengthL, const void* _Right, size_type _LengthR) const noexcept
{
	pos_type 	vPosL = 0;
	pos_type 	vPosR = 0;

	if(_Left == nullptr || _Right == nullptr || _LengthL == 0 || _LengthR == 0)
	{
		return {};
	}

	vPosL = this->find(_Left, _LengthL, 0);
	if(XByteArray::npos != vPosL)
	{
		vPosL += _LengthL;
		vPosR = this->find(_Right, _LengthR, vPosL);
		if(XByteArray::npos != vPosR)
		{
			return this->substr(vPosL, vPosR - vPosL);
		}
	}
	return {};
}

// [mid] 从源中截取部分数据
XByteArray XByteArray::mid(const elem_type* _Left, const XByteArray& _Right) const noexcept
{
	return this->mid(_Left, x_posix_strlen(_Left), _Right.data(), _Right.size());
}

// [mid] 从源中截取部分数据
XByteArray XByteArray::mid(const XByteArray& _Left, const elem_type* _Right) const noexcept
{
	return this->mid(_Left.data(), _Left.size(), _Right, x_posix_strlen(_Right));
}

// [mid] 从源中截取部分数据
XByteArray XByteArray::mid(const XByteArray& _Left, const XByteArray& _Right) const noexcept
{
	return this->mid(_Left.data(), _Left.size(), _Right.data(), _Right.size());
}





// 检测源数据是否存在指定的前缀
bool XByteArray::startsWith(elem_type _Char) const noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->startsWith(vBytes, 1);
}

// 检测源数据是否存在指定的前缀
bool XByteArray::startsWith(const elem_type* _Memory) const noexcept
{
	return this->startsWith(_Memory, x_posix_strlen(_Memory));
}

// 检测源数据是否存在指定的前缀
bool XByteArray::startsWith(const elem_type* _Memory, size_type _Length) const noexcept
{
	return this->startsWith((const void*)_Memory, _Length);
}

// 检测源数据是否存在指定的前缀
bool XByteArray::startsWith(const void* _Memory, size_type _Length) const noexcept
{
	if(this->size() >= _Length)
	{
		return this->left(_Length).compare(_Memory, _Length) == 0;
	}
	return false;
}

// 检测源数据是否存在指定的前缀
bool XByteArray::startsWith(const XByteArray& _Bytes) const noexcept
{
	return this->startsWith(_Bytes.data(), _Bytes.size());
}





// 检测源数据是否存在指定的后缀
bool XByteArray::endsWith(elem_type _Char) const noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->endsWith(vBytes, 1);
}

// 检测源数据是否存在指定的后缀
bool XByteArray::endsWith(const elem_type* _Memory) const noexcept
{
	return this->endsWith(_Memory, x_posix_strlen(_Memory));
}

// 检测源数据是否存在指定的后缀
bool XByteArray::endsWith(const elem_type* _Memory, size_type _Length) const noexcept
{
	return this->endsWith((const void*)_Memory, _Length);
}

// 检测源数据是否存在指定的后缀
bool XByteArray::endsWith(const void* _Memory, size_type _Length) const noexcept
{
	if(this->size() >= _Length)
	{
		return this->right(_Length).compare(_Memory, _Length) == 0;
	}
	return false;
}

// 检测源数据是否存在指定的后缀
bool XByteArray::endsWith(const XByteArray& _Bytes) const noexcept
{
	return this->endsWith(_Bytes.data(), _Bytes.size());
}





// 从指定位置按正序查找数据
XByteArray::pos_type XByteArray::find(elem_type _Char) const noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->find(vBytes, 1, 0);
}

// 从指定位置按正序查找数据
XByteArray::pos_type XByteArray::find(elem_type _Char, pos_type _Pos) const noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->find(vBytes, 1, _Pos);
}

// 从指定位置按正序查找数据
XByteArray::pos_type XByteArray::find(const elem_type* _Bytes) const noexcept
{
	return this->find(_Bytes, x_posix_strlen(_Bytes), 0);
}

// 从指定位置按正序查找数据
XByteArray::pos_type XByteArray::find(const elem_type* _Bytes, pos_type _Pos) const noexcept
{
	return this->find(_Bytes, x_posix_strlen(_Bytes), _Pos);
}

// 从指定位置按正序查找数据
XByteArray::pos_type XByteArray::find(const elem_type* _Bytes, size_type _Length, pos_type _Pos) const noexcept
{
	return this->find((const void*)_Bytes, _Length, _Pos);
}

// 从指定位置按正序查找数据
XByteArray::pos_type XByteArray::find(const void* _Memory, size_type _Length, pos_type _Pos) const noexcept
{
	return this->_Allocator.find(_Memory, _Length, _Pos);
}

// 从指定位置按正序查找数据
XByteArray::pos_type XByteArray::find(const XByteArray& _Bytes) const noexcept
{
	return this->find(_Bytes.data(), _Bytes.size(), 0);
}

// 从指定位置按正序查找数据
XByteArray::pos_type XByteArray::find(const XByteArray& _Bytes, pos_type _Pos) const noexcept
{
	return this->find(_Bytes.data(), _Bytes.size(), _Pos);
}





// 从指定位置按倒序查找数据
XByteArray::pos_type XByteArray::rfind(elem_type _Char) const noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->rfind(vBytes, 1, this->size() - 1);
}

// 从指定位置按倒序查找数据
XByteArray::pos_type XByteArray::rfind(elem_type _Char, pos_type _Pos) const noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->rfind(vBytes, 1, _Pos);
}

// 从指定位置按倒序查找数据
XByteArray::pos_type XByteArray::rfind(const elem_type* _Bytes) const noexcept
{
	return  this->rfind(_Bytes, x_posix_strlen(_Bytes), this->size() - 1);
}

// 从指定位置按倒序查找数据
XByteArray::pos_type XByteArray::rfind(const elem_type* _Bytes, pos_type _Pos) const noexcept
{
	return  this->rfind(_Bytes, x_posix_strlen(_Bytes), _Pos);
}

// 从指定位置按倒序查找数据
XByteArray::pos_type XByteArray::rfind(const elem_type* _Bytes, size_type _Length, pos_type _Pos) const noexcept
{
	return  this->rfind((const void*)_Bytes, _Length, _Pos);
}

// 从指定位置按倒序查找数据
XByteArray::pos_type XByteArray::rfind(const void* _Memory, size_type _Length, pos_type _Pos) const noexcept
{
	return this->_Allocator.rfind(_Memory, _Length, _Pos);
}

// 从指定位置按倒序查找数据
XByteArray::pos_type XByteArray::rfind(const XByteArray& _Bytes) const noexcept
{
	return this->rfind(_Bytes.data(), _Bytes.size(), this->size() - 1);
}

// 从指定位置按倒序查找数据
XByteArray::pos_type XByteArray::rfind(const XByteArray& _Bytes, pos_type _Pos) const noexcept
{
	return this->rfind(_Bytes.data(), _Bytes.size(), _Pos);
}





// 检查是否包含指定数据
bool XByteArray::contains(elem_type _Char) const noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->contains(vBytes, 1);
}

// 检查是否包含指定数据
bool XByteArray::contains(const elem_type* _Bytes) const noexcept
{
	return this->contains(_Bytes, x_posix_strlen(_Bytes));
}

// 检查是否包含指定数据
bool XByteArray::contains(const elem_type* _Bytes, size_type _Length) const noexcept
{
	return this->contains((const void*)_Bytes, _Length);
}

// 检查是否包含指定数据
bool XByteArray::contains(const void* _Memory, size_type _Length) const noexcept
{
	auto		vFind = this->find(_Memory, _Length, 0);
	return vFind != XByteArray::npos;
}

// 检查是否包含指定数据
bool XByteArray::contains(const XByteArray& _Bytes) const noexcept
{
	return this->contains(_Bytes.data(), _Bytes.size());
}





// 检查是否与指定数据相同
int XByteArray::compare(elem_type _Char) const noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->compare(vBytes, 1);
}

// 检查是否与指定数据相同
int XByteArray::compare(const elem_type* _Bytes) const noexcept
{
	return this->compare(_Bytes, x_posix_strlen(_Bytes));
}

// 检查是否与指定数据相同
int XByteArray::compare(const elem_type* _Bytes, size_type _Length) const noexcept
{
	return this->compare((const void*)_Bytes, _Length);
}

// 检查是否与指定数据相同
int XByteArray::compare(const void* _Memory, size_type _Length) const noexcept
{
	return this->_Allocator.compare(_Memory, _Length);
}

// 检查是否与指定数据相同
int XByteArray::compare(const XByteArray& _Bytes) const noexcept
{
	return this->compare(_Bytes.data(), _Bytes.size());
}





// 在头部插入数据
XByteArray& XByteArray::prepend(elem_type _Char) noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->prepend(vBytes, 1);
}

// 在头部插入数据
XByteArray& XByteArray::prepend(const elem_type* _Bytes) noexcept
{
	return this->prepend(_Bytes, x_posix_strlen(_Bytes));
}

// 在头部插入数据
XByteArray& XByteArray::prepend(const elem_type* _Bytes, size_type _Size) noexcept
{
	return this->prepend((const void*)_Bytes, _Size);
}

// 在头部插入数据
XByteArray& XByteArray::prepend(const void* _Memory, size_type _Size) noexcept
{
	return this->insert(0, _Memory, _Size);
}

// 在头部插入数据
XByteArray& XByteArray::prepend(const XByteArray& _Bytes) noexcept
{
	return this->prepend(_Bytes.data(), _Bytes.size());
}





// 在尾部添加数据
XByteArray& XByteArray::append(elem_type _Char) noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->append(vBytes, 1);
}

// 在尾部添加数据
XByteArray& XByteArray::append(const elem_type* _Bytes) noexcept
{
	return this->append(_Bytes, x_posix_strlen(_Bytes));
}

// 在尾部添加数据
XByteArray& XByteArray::append(const elem_type* _Bytes, size_type _Size) noexcept
{
	return this->append((const void*)_Bytes, _Size);
}

// 在尾部添加数据
XByteArray& XByteArray::append(const void* _Memory, size_type _Size) noexcept
{
	return this->insert(this->size(), _Memory, _Size);
}

// 在尾部添加数据
XByteArray& XByteArray::append(const XByteArray& _Bytes) noexcept
{
	return this->append(_Bytes.data(), _Bytes.size());
}





// 在指定下标处插入数据
XByteArray& XByteArray::insert(pos_type _Pos, elem_type _Char) noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->insert(_Pos, vBytes, 1);
}

// 在指定下标处插入数据
XByteArray& XByteArray::insert(pos_type _Pos, size_type _Count, elem_type _Char) noexcept
{
	auto		vString = XByteArray(_Count, _Char);
	return this->insert(_Pos, vString.data(), vString.size());
}

// 在指定下标处插入数据
XByteArray& XByteArray::insert(pos_type _Pos, const elem_type* _Bytes) noexcept
{
	return this->insert(_Pos, _Bytes, x_posix_strlen(_Bytes));
}

// 在指定下标处插入数据
XByteArray& XByteArray::insert(pos_type _Pos, const elem_type* _Bytes, size_type _Length) noexcept
{
	return this->insert(_Pos, (const void*)_Bytes, _Length);
}

// 在指定下标处插入数据
XByteArray& XByteArray::insert(pos_type _Pos, const void* _Memory, size_type _Length) noexcept
{
	this->_Allocator.insert(_Pos, _Memory, _Length);
	return *this;
}

// 在指定下标处插入数据
XByteArray& XByteArray::insert(pos_type _Pos, const XByteArray& _Bytes) noexcept
{
	return this->insert(_Pos, _Bytes.data(), _Bytes.size());
}





// 移除下标 pos 处的 length 长度数据
XByteArray& XByteArray::remove(pos_type _Pos, size_type _Length) noexcept
{
	this->_Allocator.remove(_Pos, _Length);
	return *this;
}

// 删除与参数相同的数据
XByteArray& XByteArray::remove(elem_type _Char) noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->remove(vBytes, 1);
}

// 删除与参数相同的数据
XByteArray& XByteArray::remove(const elem_type* _Bytes) noexcept
{
	return this->remove(_Bytes, x_posix_strlen(_Bytes));
}

// 删除与参数相同的数据
XByteArray& XByteArray::remove(const elem_type* _Bytes, size_type _Length) noexcept
{
	return this->remove((const void*)_Bytes, _Length);
}

// 删除与参数相同的数据
XByteArray& XByteArray::remove(const void* _Memory, size_type _Length) noexcept
{
	auto		vFind = this->find(_Memory, _Length, 0);
	if(vFind != XByteArray::npos)
	{
		return this->remove(vFind, _Length);
	}
	return *this;
}

// 删除与参数相同的数据
XByteArray& XByteArray::remove(const XByteArray& _Bytes) noexcept
{
	return this->remove(_Bytes.data(), _Bytes.size());
}





// 替换数据
XByteArray& XByteArray::replace(pos_type _Pos, size_type _Length, elem_type _After) noexcept
{
	elem_type		vAfter[2] = { _After, '\0' };
	return this->replace(_Pos, _Length, vAfter, 1);
}

// 替换数据
XByteArray& XByteArray::replace(pos_type _Pos, size_type _Length, const elem_type* _After) noexcept
{
	return this->replace(_Pos, _Length, _After, x_posix_strlen(_After));
}

// 替换数据
XByteArray& XByteArray::replace(pos_type _Pos, size_type _Length, const elem_type* _After, size_type _LengthA) noexcept
{
	return this->replace(_Pos, _Length, (const void*)_After, _LengthA);
}

// 替换数据
XByteArray& XByteArray::replace(pos_type _Pos, size_type _Length, const void* _After, size_type _LengthA) noexcept
{
	this->_Allocator.replace(_Pos, _Length, _After, _LengthA);
	return *this;
}

// 替换数据
XByteArray& XByteArray::replace(pos_type _Pos, size_type _Length, const XByteArray& _After) noexcept
{
	return this->replace(_Pos, _Length, _After.data(), _After.size());
}





// 替换数据
XByteArray& XByteArray::replace(elem_type _Before, elem_type _After) noexcept
{
	elem_type		vBefore[2] = { _Before, '\0' };
	elem_type		vAfter[2] = { _After, '\0' };
	return this->replace(vBefore, 1, vAfter, 1);
}

// 替换数据
XByteArray& XByteArray::replace(elem_type _Before, const elem_type* _After) noexcept
{
	elem_type		vBefore[2] = { _Before, '\0' };
	return this->replace(vBefore, 1, _After, x_posix_strlen(_After));
}

// 替换数据
XByteArray& XByteArray::replace(elem_type _Before, const elem_type* _After, size_type _LengthA) noexcept
{
	elem_type		vBefore[2] = { _Before, '\0' };
	return this->replace(vBefore, 1, _After, _LengthA);
}

// 替换数据
XByteArray& XByteArray::replace(elem_type _Before, const void* _After, size_type _LengthA) noexcept
{
	elem_type		vBefore[2] = { _Before, '\0' };
	return this->replace(vBefore, 1, _After, _LengthA);
}

// 替换数据
XByteArray& XByteArray::replace(elem_type _Before, const XByteArray& _After) noexcept
{
	elem_type		vBefore[2] = { _Before, '\0' };
	return this->replace(vBefore, 1, _After.data(), _After.size());
}





// 替换数据
XByteArray& XByteArray::replace(const elem_type* _Before, elem_type _After) noexcept
{
	elem_type		vAfter[2] = { _After, '\0' };
	return this->replace(_Before, x_posix_strlen(_Before), vAfter, 1);
}

// 替换数据
XByteArray& XByteArray::replace(const elem_type* _Before, const elem_type* _After) noexcept
{
	return this->replace(_Before, x_posix_strlen(_Before), _After, x_posix_strlen(_After));
}

// 替换数据
XByteArray& XByteArray::replace(const elem_type* _Before, const elem_type* _After, size_type _LengthA) noexcept
{
	return this->replace(_Before, x_posix_strlen(_Before), _After, _LengthA);
}

// 替换数据
XByteArray& XByteArray::replace(const elem_type* _Before, const void* _After, size_type _LengthA) noexcept
{
	return this->replace(_Before, x_posix_strlen(_Before), _After, _LengthA);
}

// 替换数据
XByteArray& XByteArray::replace(const elem_type* _Before, const XByteArray& _After) noexcept
{
	return this->replace(_Before, x_posix_strlen(_Before), _After.data(), _After.size());
}





// 替换数据
XByteArray& XByteArray::replace(const elem_type* _Before, size_type _LengthB, elem_type _After) noexcept
{
	elem_type		vAfter[2] = { _After, '\0' };
	return this->replace(_Before, _LengthB, vAfter, 1);
}

// 替换数据
XByteArray& XByteArray::replace(const elem_type* _Before, size_type _LengthB, const elem_type* _After) noexcept
{
	return this->replace(_Before, _LengthB, _After, x_posix_strlen(_After));
}

// 替换数据
XByteArray& XByteArray::replace(const elem_type* _Before, size_type _LengthB, const elem_type* _After, size_type _LengthA) noexcept
{
	return this->replace(_Before, _LengthB, (const void*)_After, _LengthA);
}

// 替换数据
XByteArray& XByteArray::replace(const elem_type* _Before, size_type _LengthB, const void* _After, size_type _LengthA) noexcept
{
	return this->replace((const void*)_Before, _LengthB, _After, _LengthA);
}

// 替换数据
XByteArray& XByteArray::replace(const elem_type* _Before, size_type _LengthB, const XByteArray& _After) noexcept
{
	return this->replace(_Before, _LengthB, _After.data(), _After.size());
}





// 替换数据
XByteArray& XByteArray::replace(const void* _Before, size_type _LengthB, elem_type _After) noexcept
{
	elem_type		vAfter[2] = { _After, '\0' };
	return this->replace(_Before, _LengthB, vAfter, 1);
}

// 替换数据
XByteArray& XByteArray::replace(const void* _Before, size_type _LengthB, const elem_type* _After) noexcept
{
	return this->replace(_Before, _LengthB, _After, x_posix_strlen(_After));
}

// 替换数据
XByteArray& XByteArray::replace(const void* _Before, size_type _LengthB, const elem_type* _After, size_type _LengthA) noexcept
{
	return this->replace(_Before, _LengthB, (const void*)_After, _LengthA);
}

// 替换数据
XByteArray& XByteArray::replace(const void* _Before, size_type _LengthB, const void* _After, size_type _LengthA) noexcept
{
	pos_type	vPos = 0;
	do
	{
		vPos = this->find(_Before, _LengthB, vPos);
		if(XByteArray::npos != vPos)
		{
			this->replace(vPos, _LengthB, _After, _LengthA);
			vPos += _LengthA;
		}
	} while(XByteArray::npos != vPos);
	return *this;
}

// 替换数据
XByteArray& XByteArray::replace(const void* _Before, size_type _LengthB, const XByteArray& _After) noexcept
{
	return this->replace(_Before, _LengthB, _After.data(), _After.size());
}





// 替换数据
XByteArray& XByteArray::replace(const XByteArray& _Before, elem_type _After) noexcept
{
	elem_type		vAfter[2] = { _After, '\0' };
	return this->replace(_Before.data(), _Before.size(), vAfter, 1);
}

// 替换数据
XByteArray& XByteArray::replace(const XByteArray& _Before, const elem_type* _After) noexcept
{
	return this->replace(_Before.data(), _Before.size(), _After, x_posix_strlen(_After));
}

// 替换数据
XByteArray& XByteArray::replace(const XByteArray& _Before, const elem_type* _After, size_type _LengthA) noexcept
{
	return this->replace(_Before.data(), _Before.size(), (const void*)_After, _LengthA);
}

// 替换数据
XByteArray& XByteArray::replace(const XByteArray& _Before, const void* _After, size_type _LengthA) noexcept
{
	return this->replace(_Before.data(), _Before.size(), _After, _LengthA);
}

// 替换数据
XByteArray& XByteArray::replace(const XByteArray& _Before, const XByteArray& _After) noexcept
{
	return this->replace(_Before.data(), _Before.size(), _After.data(), _After.size());
}





// 从指定位置截断
void XByteArray::truncate(pos_type _Pos) noexcept
{
	if(_Pos < this->size())
	{
		this->resize(_Pos);
	}
}





// 按指定数据拆分字符串
std::list<XByteArray> XByteArray::split(elem_type _Char) const noexcept
{
	elem_type		vBytes[2] = { _Char, '\0' };
	return this->split(vBytes, 1);
}

// 按指定数据拆分字符串
std::list<XByteArray> XByteArray::split(const elem_type* _Memory) const noexcept
{
	return this->split({_Memory, x_posix_strlen(_Memory)});
}

// 按指定数据拆分字符串
std::list<XByteArray> XByteArray::split(const elem_type* _Memory, size_type _Size) const noexcept
{
	return this->split({_Memory, _Size});
}

// 按指定数据拆分字符串
std::list<XByteArray> XByteArray::split(const void* _Memory, size_type _Size) const noexcept
{
	return this->split({_Memory, _Size});
}

// 按指定数据拆分字符串
std::list<XByteArray> XByteArray::split(const XByteArray& _Bytes) const noexcept
{
	auto		vHeaderArray = std::list<XByteArray>();
	auto		vLast = static_cast<size_type>(0U);
	auto		vSplitIndex = this->find(_Bytes, vLast);
	while(vSplitIndex != XByteArray::npos && _Bytes.exist())
	{
		vHeaderArray.push_back(this->mid(vLast, vSplitIndex - vLast));
		vLast = vSplitIndex + 2;
		vSplitIndex = this->find(_Bytes, vLast);
	}
	vHeaderArray.push_back(this->mid(vLast));

	return vHeaderArray;
}





// 判断一个字符是否为空白字符
bool XByteArray::isSpace(elem_type _Char) noexcept
{
	// 如果宽字符是空白字符，则为真，否则假。
	return isspace(_Char);
}

// 格式化字符串 (char* [%s]) (wchar_t* [%ls])
XByteArray XByteArray::format(const char* _Format, ...) noexcept
{
	auto		vString = XByteArray();
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
XByteArray XByteArray::toUpper() const noexcept
{
	auto		vStrUpper = *this;
	for(pos_type vIndex = 0; vIndex < vStrUpper.size(); ++vIndex)
	{
		vStrUpper[vIndex] = (elem_type)std::toupper(vStrUpper[vIndex]);
	}
	return vStrUpper;
}

// [conv] 转换至小写
XByteArray XByteArray::toLower() const noexcept
{
	auto		vStrUpper = *this;
	for(pos_type vIndex = 0; vIndex < vStrUpper.size(); ++vIndex)
	{
		vStrUpper[vIndex] = (elem_type)std::tolower(vStrUpper[vIndex]);
	}
	return vStrUpper;
}





// [conv] 转换至HEX
XByteArray XByteArray::toHex() const noexcept
{
	auto		vTarget = XByteArray(this->size() * 2, '0');
	for (auto vIndex = 0U; vIndex < this->size(); ++vIndex)
	{
		x_posix_sprintf(vTarget.data() + (vIndex * 2), "%02X", (std::uint8_t)this->data()[vIndex]);
	}
	return vTarget;
}

// [conv] 从HEX转换
XByteArray XByteArray::fromHex(const elem_type* _Hex) noexcept
{
	return XByteArray::fromHex(_Hex, x_posix_strlen(_Hex));
}

// [conv] 从HEX转换
XByteArray XByteArray::fromHex(const elem_type* _Hex, size_type _Size) noexcept
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
	auto		vTarget = XByteArray(vLength, '\0');

	for (auto vIndex = 0U; vIndex < vLength; ++vIndex)
	{
		auto		vHexLeft = vFunctionHexToChar(vBuffer[vIndex * 2 + 0]);
		auto		vHexRight = vFunctionHexToChar(vBuffer[vIndex * 2 + 1]);
		vTarget[vIndex] = static_cast<char>(vHexLeft * 16 + vHexRight);
	}
	return vTarget;
}

// [conv] 从HEX转换
XByteArray XByteArray::fromHex(const void* _Hex, size_type _Size) noexcept
{
	return XByteArray::fromHex((const elem_type*)_Hex, _Size);
}

// [conv] 从HEX转换
XByteArray XByteArray::fromHex(const XByteArray& _Hex) noexcept
{
	return XByteArray::fromHex(_Hex.data(), _Hex.size());
}





// [conv] 转换至Base64
XByteArray XByteArray::toBase64() const noexcept
{
	uint8_t*	vEncodeBytes = nullptr;
	size_t 		vEncodeSize = 0;
	auto		vSync = x_base64_encode((const uint8_t*)this->data(), this->size(), &vEncodeBytes, &vEncodeSize);
	if(vSync && vEncodeBytes && vEncodeSize)
	{
		XByteArray	vBase64(vEncodeBytes, vEncodeSize);
		x_posix_free(vEncodeBytes);
		return vBase64;
	}
	return {};
}

// [conv] 从Base64转换
XByteArray XByteArray::fromBase64(const elem_type* _Base64) noexcept
{
	return XByteArray::fromBase64(_Base64, x_posix_strlen(_Base64));
}

// [conv] 从Base64转换
XByteArray XByteArray::fromBase64(const elem_type* _Base64, size_type _Size) noexcept
{
	uint8_t*	vDecodeBytes = nullptr;
	size_t 		vDecodeSize = 0;
	auto		vSync = x_base64_decode((const uint8_t*)_Base64, _Size, &vDecodeBytes, &vDecodeSize);
	if(vSync && vDecodeBytes && vDecodeSize)
	{
		XByteArray	vDecode(vDecodeBytes, vDecodeSize);
		x_posix_free(vDecodeBytes);
		return vDecode;
	}
	return {};
}

// [conv] 从Base64转换
XByteArray XByteArray::fromBase64(const void* _Base64, size_type _Size) noexcept
{
	return XByteArray::fromBase64((const elem_type*)_Base64, _Size);
}

// [conv] 从Base64转换
XByteArray XByteArray::fromBase64(const XByteArray& _Base64) noexcept
{
	return XByteArray::fromBase64(_Base64.data(), _Base64.size());
}





// Standard enhancement function : stream <<
_XCOREAPI_ std::ostream& operator<< (std::ostream& _OStream, const XByteArray& _Bytes) noexcept
{
	for(auto vIndex = 0U; vIndex < _Bytes.size(); ++vIndex)
	{
		_OStream << _Bytes[vIndex];
	}
	return _OStream;
}

// Standard enhancement function : stream >>
_XCOREAPI_ std::istream& operator>> (std::istream& _IStream, XByteArray& _Bytes) noexcept
{
	_Bytes.clear();
	do
	{
		auto		vChar = static_cast<XByteArray::elem_type>(_IStream.get());
		if(vChar == '\n' || vChar == ' ')
		{
			break;
		}
		_Bytes.append(vChar);
	} while(true);
	return _IStream;
}

// Standard enhancement function : getline
_XCOREAPI_ std::istream& getline(std::istream& _IStream, XByteArray& _Bytes, char _Delim) noexcept
{
	_Bytes.clear();
	do
	{
		auto		vChar = static_cast<XByteArray::elem_type>(_IStream.get());
		if(vChar == _Delim)
		{
			break;
		}
		_Bytes.append(vChar);
	} while(true);
	return _IStream;
}

// Standard enhancement function : getline
_XCOREAPI_ std::istream& getline(std::istream& _IStream, XByteArray& _Bytes) noexcept
{
	return getline(_IStream, _Bytes, '\n');
}
