#ifndef			_XANADU_CORE_BYTE_ARRAY_H_
#define			_XANADU_CORE_BYTE_ARRAY_H_

#include <xanadu-core/header.h>
#include <xanadu-core/XAllocator.h>


/// class XByteArray
class _XCOREAPI_ XByteArray
{
public:
	using				elem_type = XAllocator::elem_type;
	using				size_type = XAllocator::size_type;
	using				pos_type = XAllocator::pos_type;

public:
	static const pos_type		npos = XAllocator::npos;

private:
	XAllocator			_Allocator;

public:
	// constructor
	XByteArray() noexcept;

	// constructor
	XByteArray(size_type _Length, elem_type _Char) noexcept;

	// constructor
	XByteArray(const elem_type* _Memory) noexcept; // NOLINT(google-explicit-constructor)

	// constructor
	XByteArray(const elem_type* _Memory, size_type _Length) noexcept;

	// constructor
	XByteArray(const void* _Memory, size_type _Length) noexcept;

	// constructor
	XByteArray(const XByteArray& _Bytes) noexcept;

	// constructor
	XByteArray(XByteArray&& _Bytes) noexcept;

	// destructor
	virtual ~XByteArray() noexcept;

public:
	// operator overload =
	XByteArray& operator = (const elem_type* _Memory) noexcept;

	// operator overload =
	XByteArray& operator = (const XByteArray& _Bytes) noexcept;

	// operator overload =
	XByteArray& operator = (XByteArray&& _Bytes) noexcept;

public:
	// operator overload +=
	XByteArray& operator += (elem_type _Char) noexcept;

	// operator overload +=
	XByteArray& operator += (const elem_type* _Bytes) noexcept;

	// operator overload +=
	XByteArray& operator += (const XByteArray& _Bytes) noexcept;

public:
	// operator overload +
	XByteArray operator + (elem_type _Char) const noexcept;

	// operator overload +
	XByteArray operator + (const elem_type* _Bytes) const noexcept;

	// operator overload +
	XByteArray operator + (const XByteArray& _Bytes) const noexcept;

public:
	// operator overload ==
	bool operator == (elem_type _Char) const noexcept;

	// operator overload ==
	bool operator == (const elem_type* _Bytes) const noexcept;

	// operator overload ==
	bool operator == (const XByteArray& _Bytes) const noexcept;

	// operator overload !=
	bool operator != (elem_type _Char) const noexcept;

	// operator overload !=
	bool operator != (const elem_type* _Bytes) const noexcept;

	// operator overload !=
	bool operator != (const XByteArray& _Bytes) const noexcept;

public:
	// operator overload []
	elem_type& operator [] (pos_type _Index);

	// operator overload []
	elem_type operator [] (pos_type _Index) const;

public:
	// [opt] clear
	virtual void clear() noexcept final;

	// [opt] resize
	virtual bool resize(size_type _Length) noexcept final;

	// [opt] reverse
	virtual bool reverse(size_type _Length) noexcept final;

public:
	// [get] exist
	virtual bool exist() const noexcept final;

	// [get] empty
	virtual bool empty() const noexcept final;

	// [get] data
	virtual elem_type* data() noexcept final;

	// [get] data
	virtual const elem_type* data() const noexcept final;

	// [get] size
	virtual size_type size() const noexcept final;

	// [get] capacity
	virtual size_type capacity() const noexcept final;

	// [get] surplus
	virtual size_type surplus() const noexcept final;

	// [get] max_size
	virtual size_type max_size() const noexcept final;

public:
	// 从源中截取部分数据
	virtual XByteArray substr(pos_type _Pos) const noexcept final;

	// 从源中截取部分数据
	virtual XByteArray substr(pos_type _Pos, size_type _Length) const noexcept final;

	// 从源中截取部分数据
	virtual XByteArray left(pos_type _Pos) const noexcept final;

	// 从源中截取部分数据
	virtual XByteArray right(pos_type _Pos) const noexcept final;

public:
	// [mid] 从源中截取部分数据
	virtual XByteArray mid(pos_type _Pos) const noexcept final;

	// [mid] 从源中截取部分数据
	virtual XByteArray mid(pos_type _Pos, size_type _Size) const noexcept final;

	// [mid] 从源中截取部分数据
	virtual XByteArray mid(const elem_type* _Left, const elem_type* _Right) const noexcept final;

	// [mid] 从源中截取部分数据
	virtual XByteArray mid(const elem_type* _Left, size_type _LengthL, const elem_type* _Right) const noexcept final;

	// [mid] 从源中截取部分数据
	virtual XByteArray mid(const elem_type* _Left, const elem_type* _Right, size_type _LengthR) const noexcept final;

	// [mid] 从源中截取部分数据
	virtual XByteArray mid(const elem_type* _Left, size_type _LengthL, const elem_type* _Right, size_type _LengthR) const noexcept final;

	// [mid] 从源中截取部分数据
	virtual XByteArray mid(const void* _Left, size_type _LengthL, const void* _Right, size_type _LengthR) const noexcept final;

	// [mid] 从源中截取部分数据
	virtual XByteArray mid(const elem_type* _Left, const XByteArray& _Right) const noexcept final;

	// [mid] 从源中截取部分数据
	virtual XByteArray mid(const XByteArray& _Left, const elem_type* _Right) const noexcept final;

	// [mid] 从源中截取部分数据
	virtual XByteArray mid(const XByteArray& _Left, const XByteArray& _Right) const noexcept final;

public:
	// 检测源数据是否存在指定的前缀
	virtual bool startsWith(elem_type _Char) const noexcept final;

	// 检测源数据是否存在指定的前缀
	virtual bool startsWith(const elem_type* _Memory) const noexcept final;

	// 检测源数据是否存在指定的前缀
	virtual bool startsWith(const elem_type* _Memory, size_type _Length) const noexcept final;

	// 检测源数据是否存在指定的前缀
	virtual bool startsWith(const void* _Memory, size_type _Length) const noexcept final;

	// 检测源数据是否存在指定的前缀
	virtual bool startsWith(const XByteArray& _Bytes) const noexcept final;

public:
	// 检测源数据是否存在指定的后缀
	virtual bool endsWith(elem_type _Char) const noexcept final;

	// 检测源数据是否存在指定的后缀
	virtual bool endsWith(const elem_type* _Memory) const noexcept final;

	// 检测源数据是否存在指定的后缀
	virtual bool endsWith(const elem_type* _Memory, size_type _Length) const noexcept final;

	// 检测源数据是否存在指定的后缀
	virtual bool endsWith(const void* _Memory, size_type _Length) const noexcept final;

	// 检测源数据是否存在指定的后缀
	virtual bool endsWith(const XByteArray& _Bytes) const noexcept final;

public:
	// 从指定位置按正序查找数据
	virtual pos_type find(elem_type _Char) const noexcept final;

	// 从指定位置按正序查找数据
	virtual pos_type find(elem_type _Char, pos_type _Pos) const noexcept final;

	// 从指定位置按正序查找数据
	virtual pos_type find(const elem_type* _Bytes) const noexcept final;

	// 从指定位置按正序查找数据
	virtual pos_type find(const elem_type* _Bytes, pos_type _Pos) const noexcept final;

	// 从指定位置按正序查找数据
	virtual pos_type find(const elem_type* _Bytes, size_type _Length, pos_type _Pos) const noexcept final;

	// 从指定位置按正序查找数据
	virtual pos_type find(const void* _Memory, size_type _Length, pos_type _Pos) const noexcept final;

	// 从指定位置按正序查找数据
	virtual pos_type find(const XByteArray& _Bytes) const noexcept final;

	// 从指定位置按正序查找数据
	virtual pos_type find(const XByteArray& _Bytes, pos_type _Pos) const noexcept final;

public:
	// 从指定位置按倒序查找数据
	virtual pos_type rfind(elem_type _Char) const noexcept final;

	// 从指定位置按倒序查找数据
	virtual pos_type rfind(elem_type _Char, pos_type _Pos) const noexcept final;

	// 从指定位置按倒序查找数据
	virtual pos_type rfind(const elem_type* _Bytes) const noexcept final;

	// 从指定位置按倒序查找数据
	virtual pos_type rfind(const elem_type* _Bytes, pos_type _Pos) const noexcept final;

	// 从指定位置按倒序查找数据
	virtual pos_type rfind(const elem_type* _Bytes, size_type _Length, pos_type _Pos) const noexcept final;

	// 从指定位置按倒序查找数据
	virtual pos_type rfind(const void* _Memory, size_type _Length, pos_type _Pos) const noexcept final;

	// 从指定位置按倒序查找数据
	virtual pos_type rfind(const XByteArray& _Bytes) const noexcept final;

	// 从指定位置按倒序查找数据
	virtual pos_type rfind(const XByteArray& _Bytes, pos_type _Pos) const noexcept final;

public:
	// 检查是否包含指定数据
	virtual bool contains(elem_type _Char) const noexcept final;

	// 检查是否包含指定数据
	virtual bool contains(const elem_type* _Bytes) const noexcept final;

	// 检查是否包含指定数据
	virtual bool contains(const elem_type* _Bytes, size_type _Length) const noexcept final;

	// 检查是否包含指定数据
	virtual bool contains(const void* _Memory, size_type _Length) const noexcept final;

	// 检查是否包含指定数据
	virtual bool contains(const XByteArray& _Bytes) const noexcept final;

public:
	// 检查是否与指定数据相同
	virtual int compare(elem_type _Char) const noexcept final;

	// 检查是否与指定数据相同
	virtual int compare(const elem_type* _Bytes) const noexcept final;

	// 检查是否与指定数据相同
	virtual int compare(const elem_type* _Bytes, size_type _Length) const noexcept final;

	// 检查是否与指定数据相同
	virtual int compare(const void* _Memory, size_type _Length) const noexcept final;

	// 检查是否与指定数据相同
	virtual int compare(const XByteArray& _Bytes) const noexcept final;

public:
	// 在头部插入数据
	virtual XByteArray& prepend(elem_type _Char) noexcept final;

	// 在头部插入数据
	virtual XByteArray& prepend(const elem_type* _Bytes) noexcept final;

	// 在头部插入数据
	virtual XByteArray& prepend(const elem_type* _Bytes, size_type _Size) noexcept final;

	// 在头部插入数据
	virtual XByteArray& prepend(const void* _Memory, size_type _Size) noexcept final;

	// 在头部插入数据
	virtual XByteArray& prepend(const XByteArray& _Bytes) noexcept final;

public:
	// 在尾部添加数据
	virtual XByteArray& append(elem_type _Char) noexcept final;

	// 在尾部添加数据
	virtual XByteArray& append(const elem_type* _Bytes) noexcept final;

	// 在尾部添加数据
	virtual XByteArray& append(const elem_type* _Bytes, size_type _Size) noexcept final;

	// 在尾部添加数据
	virtual XByteArray& append(const void* _Memory, size_type _Size) noexcept final;

	// 在尾部添加数据
	virtual XByteArray& append(const XByteArray& _Bytes) noexcept final;

public:
	// 在指定下标处插入数据
	virtual XByteArray& insert(pos_type _Pos, elem_type _Char) noexcept final;

	// 在指定下标处插入数据
	virtual XByteArray& insert(pos_type _Pos, size_type _Count, elem_type _Char) noexcept final;

	// 在指定下标处插入数据
	virtual XByteArray& insert(pos_type _Pos, const elem_type* _Bytes) noexcept final;

	// 在指定下标处插入数据
	virtual XByteArray& insert(pos_type _Pos, const elem_type* _Bytes, size_type _Length) noexcept final;

	// 在指定下标处插入数据
	virtual XByteArray& insert(pos_type _Pos, const void* _Memory, size_type _Length) noexcept final;

	// 在指定下标处插入数据
	virtual XByteArray& insert(pos_type _Pos, const XByteArray& _Bytes) noexcept final;

public:
	// 移除下标 pos 处的 length 长度数据
	virtual XByteArray& remove(pos_type _Pos, size_type _Length) noexcept final;

	// 删除与参数相同的数据
	virtual XByteArray& remove(elem_type _Char) noexcept final;

	// 删除与参数相同的数据
	virtual XByteArray& remove(const elem_type* _Bytes) noexcept final;

	// 删除与参数相同的数据
	virtual XByteArray& remove(const elem_type* _Bytes, size_type _Length) noexcept final;

	// 删除与参数相同的数据
	virtual XByteArray& remove(const void* _Memory, size_type _Length) noexcept final;

	// 删除与参数相同的数据
	virtual XByteArray& remove(const XByteArray& _Bytes) noexcept final;

public:
	// 替换数据
	virtual XByteArray& replace(pos_type _Pos, size_type _Length, elem_type _After) noexcept final;

	// 替换数据
	virtual XByteArray& replace(pos_type _Pos, size_type _Length, const elem_type* _After) noexcept final;

	// 替换数据
	virtual XByteArray& replace(pos_type _Pos, size_type _Length, const elem_type* _After, size_type _LengthA) noexcept final;

	// 替换数据
	virtual XByteArray& replace(pos_type _Pos, size_type _Length, const void* _After, size_type _LengthA) noexcept final;

	// 替换数据
	virtual XByteArray& replace(pos_type _Pos, size_type _Length, const XByteArray& _After) noexcept final;

public:
	// 替换数据
	virtual XByteArray& replace(elem_type _Before, elem_type _After) noexcept final;

	// 替换数据
	virtual XByteArray& replace(elem_type _Before, const elem_type* _After) noexcept final;

	// 替换数据
	virtual XByteArray& replace(elem_type _Before, const elem_type* _After, size_type _LengthA) noexcept final;

	// 替换数据
	virtual XByteArray& replace(elem_type _Before, const void* _After, size_type _LengthA) noexcept final;

	// 替换数据
	virtual XByteArray& replace(elem_type _Before, const XByteArray& _After) noexcept final;

public:
	// 替换数据
	virtual XByteArray& replace(const elem_type* _Before, elem_type _After) noexcept final;

	// 替换数据
	virtual XByteArray& replace(const elem_type* _Before, const elem_type* _After) noexcept final;

	// 替换数据
	virtual XByteArray& replace(const elem_type* _Before, const elem_type* _After, size_type _LengthA) noexcept final;

	// 替换数据
	virtual XByteArray& replace(const elem_type* _Before, const void* _After, size_type _LengthA) noexcept final;

	// 替换数据
	virtual XByteArray& replace(const elem_type* _Before, const XByteArray& _After) noexcept final;

public:
	// 替换数据
	virtual XByteArray& replace(const elem_type* _Before, size_type _LengthB, elem_type _After) noexcept final;

	// 替换数据
	virtual XByteArray& replace(const elem_type* _Before, size_type _LengthB, const elem_type* _After) noexcept final;

	// 替换数据
	virtual XByteArray& replace(const elem_type* _Before, size_type _LengthB, const elem_type* _After, size_type _LengthA) noexcept final;

	// 替换数据
	virtual XByteArray& replace(const elem_type* _Before, size_type _LengthB, const void* _After, size_type _LengthA) noexcept final;

	// 替换数据
	virtual XByteArray& replace(const elem_type* _Before, size_type _LengthB, const XByteArray& _After) noexcept final;

public:
	// 替换数据
	virtual XByteArray& replace(const void* _Before, size_type _LengthB, elem_type _After) noexcept final;

	// 替换数据
	virtual XByteArray& replace(const void* _Before, size_type _LengthB, const elem_type* _After) noexcept final;

	// 替换数据
	virtual XByteArray& replace(const void* _Before, size_type _LengthB, const elem_type* _After, size_type _LengthA) noexcept final;

	// 替换数据
	virtual XByteArray& replace(const void* _Before, size_type _LengthB, const void* _After, size_type _LengthA) noexcept final;

	// 替换数据
	virtual XByteArray& replace(const void* _Before, size_type _LengthB, const XByteArray& _After) noexcept final;

public:
	// 替换数据
	virtual XByteArray& replace(const XByteArray& _Before, elem_type _After) noexcept final;

	// 替换数据
	virtual XByteArray& replace(const XByteArray& _Before, const elem_type* _After) noexcept final;

	// 替换数据
	virtual XByteArray& replace(const XByteArray& _Before, const elem_type* _After, size_type _LengthA) noexcept final;

	// 替换数据
	virtual XByteArray& replace(const XByteArray& _Before, const void* _After, size_type _LengthA) noexcept final;

	// 替换数据
	virtual XByteArray& replace(const XByteArray& _Before, const XByteArray& _After) noexcept final;

public:
	// 从指定位置截断
	virtual void truncate(pos_type _Pos) noexcept final;

public:
	// 按指定数据拆分字符串
	virtual std::list<XByteArray> split(elem_type _Char) const noexcept final;

	// 按指定数据拆分字符串
	virtual std::list<XByteArray> split(const elem_type* _Memory) const noexcept final;

	// 按指定数据拆分字符串
	virtual std::list<XByteArray> split(const elem_type* _Memory, size_type _Size) const noexcept final;

	// 按指定数据拆分字符串
	virtual std::list<XByteArray> split(const void* _Memory, size_type _Size) const noexcept final;

	// 按指定数据拆分字符串
	virtual std::list<XByteArray> split(const XByteArray& _Bytes) const noexcept final;

public:
	// 判断一个字符是否为空白字符
	static bool isSpace(elem_type _Char) noexcept;

	// 格式化字符串 (char* [%s]) (wchar_t* [%ls])
	static XByteArray format(const char* _Format, ...) noexcept;

public:
	// [conv] 转换至大写
	XByteArray toUpper() const noexcept;

	// [conv] 转换至小写
	XByteArray toLower() const noexcept;

public:
	// [conv] 转换至HEX
	virtual XByteArray toHex() const noexcept final;

	// [conv] 从HEX转换
	static XByteArray fromHex(const elem_type* _Hex) noexcept;

	// [conv] 从HEX转换
	static XByteArray fromHex(const elem_type* _Hex, size_type _Size) noexcept;

	// [conv] 从HEX转换
	static XByteArray fromHex(const void* _Hex, size_type _Size) noexcept;

	// [conv] 从HEX转换
	static XByteArray fromHex(const XByteArray& _Hex) noexcept;

public:
	// [conv] 转换至Base64
	virtual XByteArray toBase64() const noexcept final;

	// [conv] 从Base64转换
	static XByteArray fromBase64(const elem_type* _Base64) noexcept;

	// [conv] 从Base64转换
	static XByteArray fromBase64(const elem_type* _Base64, size_type _Size) noexcept;

	// [conv] 从Base64转换
	static XByteArray fromBase64(const void* _Base64, size_type _Size) noexcept;

	// [conv] 从Base64转换
	static XByteArray fromBase64(const XByteArray& _Base64) noexcept;
};



// Standard enhancement function : stream <<
_XCOREAPI_ std::ostream& operator << (std::ostream& _OStream, const XByteArray& _Bytes) noexcept;

// Standard enhancement function : stream >>
_XCOREAPI_ std::istream& operator >> (std::istream& _IStream, XByteArray& _String) noexcept;

// Standard enhancement function : getline
_XCOREAPI_ std::istream& getline(std::istream& _IStream, XByteArray& _String, char _Delim) noexcept;

// Standard enhancement function : getline
_XCOREAPI_ std::istream& getline(std::istream& _IStream, XByteArray& _String) noexcept;

#endif
