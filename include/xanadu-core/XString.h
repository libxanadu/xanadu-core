#ifndef			_XANADU_CORE_STRING_H_
#define			_XANADU_CORE_STRING_H_

#include <xanadu-core/header.h>
#include <xanadu-core/XAllocator.h>
#include <xanadu-core/XByteArray.h>


// String type definition
typedef			char							XChar;
typedef			std::string						AString;		// ASCII
typedef			std::wstring						WString;		// UNICODE
typedef			std::string						UString;		// UTF-8
typedef			std::string						LString;		// Latin1(ISO-8859-1)
#if defined(XANADU_SYSTEM_WINDOWS)
typedef			AString							NString;		// Native string (ASCII)
#else
typedef			UString							NString;		// Native string (UTF-8)
#endif


/// class XString
class _XCOREAPI_ XString
{
public:
	using elem_type			= char;
	using size_type			= XAllocator::size_type;
	using pos_type			= XAllocator::pos_type;

public:
	static const pos_type		npos	= XAllocator::npos;

private:
	XAllocator			_Allocator;

public:
	// constructor
	XString() noexcept;

	// constructor
	XString(size_type _Length, elem_type _Char) noexcept;

	// constructor
	XString(const elem_type* _Memory) noexcept; // NOLINT(google-explicit-constructor)

	// constructor
	XString(const elem_type* _Memory, size_type _Length) noexcept;

	// constructor
	XString(const XString& _String) noexcept;

	// constructor
	XString(XString&& _String) noexcept;

	// destructor
	virtual ~XString() noexcept;

public:
	// operator overload =
	XString& operator = (const elem_type* _Memory) noexcept;

	// operator overload =
	XString& operator = (const XString& _String) noexcept;

	// operator overload =
	XString& operator = (XString&& _String) noexcept;

public:
	// operator overload +=
	XString& operator += (elem_type _Char) noexcept;

	// operator overload +=
	XString& operator += (const elem_type* _String) noexcept;

	// operator overload +=
	XString& operator += (const XString& _String) noexcept;

public:
	// operator overload +
	XString operator + (elem_type _Char) const noexcept;

	// operator overload +
	XString operator + (const elem_type* _String) const noexcept;

	// operator overload +
	XString operator + (const XString& _String) const noexcept;

public:
	// operator overload ==
	bool operator == (elem_type _Char) const noexcept;

	// operator overload ==
	bool operator == (const elem_type* _String) const noexcept;

	// operator overload ==
	bool operator == (const XString& _String) const noexcept;

	// operator overload !=
	bool operator != (elem_type _Char) const noexcept;

	// operator overload !=
	bool operator != (const elem_type* _String) const noexcept;

	// operator overload !=
	bool operator != (const XString& _String) const noexcept;

	// operator overload <
	bool operator < (elem_type _Char) const noexcept;

	// operator overload <
	bool operator < (const elem_type* _String) const noexcept;

	// operator overload <
	bool operator < (const XString& _String) const noexcept;

	// operator overload >
	bool operator > (elem_type _Char) const noexcept;

	// operator overload >
	bool operator > (const elem_type* _String) const noexcept;

	// operator overload >
	bool operator > (const XString& _String) const noexcept;

	// operator overload <=
	bool operator <= (elem_type _Char) const noexcept;

	// operator overload <=
	bool operator <= (const elem_type* _String) const noexcept;

	// operator overload <=
	bool operator <= (const XString& _String) const noexcept;

	// operator overload >=
	bool operator >= (elem_type _Char) const noexcept;

	// operator overload >=
	bool operator >= (const elem_type* _String) const noexcept;

	// operator overload >=
	bool operator >= (const XString& _String) const noexcept;

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
	// Truncates the subscript POS of the byte array. If POS goes beyond the end of the array, nothing happens.
	virtual void truncate(size_type _Index) noexcept final;

	// Returns a string that has whitespace removed from the start and the end, and that has each sequence of internal whitespace replaced with a single space.
	virtual XString simplified() const noexcept final;

public:
	// 从源中截取部分数据
	virtual XString substr(pos_type _Pos) const noexcept final;

	// 从源中截取部分数据
	virtual XString substr(pos_type _Pos, size_type _Length) const noexcept final;

	// 从源中截取部分数据
	virtual XString left(pos_type _Pos) const noexcept final;

	// 从源中截取部分数据
	virtual XString right(pos_type _Pos) const noexcept final;

public:
	// [mid] 从源中截取部分数据
	virtual XString mid(pos_type _Pos) const noexcept final;

	// [mid] 从源中截取部分数据
	virtual XString mid(pos_type _Pos, size_type _Size) const noexcept final;

	// [mid] 从源中截取部分数据
	virtual XString mid(const elem_type* _Left, const elem_type* _Right) const noexcept final;

	// [mid] 从源中截取部分数据
	virtual XString mid(const elem_type* _Left, const elem_type* _Right, Xs::CaseSensitivity _XCS) const noexcept final;

	// [mid] 从源中截取部分数据
	virtual XString mid(const elem_type* _Left, size_type _LengthL, const elem_type* _Right, size_type _LengthR) const noexcept final;

	// [mid] 从源中截取部分数据
	virtual XString mid(const elem_type* _Left, size_type _LengthL, const elem_type* _Right, size_type _LengthR, Xs::CaseSensitivity _XCS) const noexcept final;

	// [mid] 从源中截取部分数据
	virtual XString mid(const elem_type* _Left, const XString& _Right) const noexcept final;

	// [mid] 从源中截取部分数据
	virtual XString mid(const elem_type* _Left, const XString& _Right, Xs::CaseSensitivity _XCS) const noexcept final;

	// [mid] 从源中截取部分数据
	virtual XString mid(const XString& _Left, const elem_type* _Right) const noexcept final;

	// [mid] 从源中截取部分数据
	virtual XString mid(const XString& _Left, const elem_type* _Right, Xs::CaseSensitivity _XCS) const noexcept final;

	// [mid] 从源中截取部分数据
	virtual XString mid(const XString& _Left, const XString& _Right) const noexcept final;

	// [mid] 从源中截取部分数据
	virtual XString mid(const XString& _Left, const XString& _Right, Xs::CaseSensitivity _XCS) const noexcept final;

public:
	// 检测源数据是否存在指定的前缀
	virtual bool startsWith(elem_type _Char) const noexcept final;

	// 检测源数据是否存在指定的前缀
	virtual bool startsWith(elem_type _Char, Xs::CaseSensitivity _XCS) const noexcept final;

	// 检测源数据是否存在指定的前缀
	virtual bool startsWith(const elem_type* _Memory) const noexcept final;

	// 检测源数据是否存在指定的前缀
	virtual bool startsWith(const elem_type* _Memory, Xs::CaseSensitivity _XCS) const noexcept final;

	// 检测源数据是否存在指定的前缀
	virtual bool startsWith(const elem_type* _Memory, size_type _Length) const noexcept final;

	// 检测源数据是否存在指定的前缀
	virtual bool startsWith(const elem_type* _Memory, size_type _Length, Xs::CaseSensitivity _XCS) const noexcept final;

	// 检测源数据是否存在指定的前缀
	virtual bool startsWith(const XString& _String) const noexcept final;

	// 检测源数据是否存在指定的前缀
	virtual bool startsWith(const XString& _String, Xs::CaseSensitivity _XCS) const noexcept final;

public:
	// 检测源数据是否存在指定的后缀
	virtual bool endsWith(elem_type _Char) const noexcept final;

	// 检测源数据是否存在指定的后缀
	virtual bool endsWith(elem_type _Char, Xs::CaseSensitivity _XCS) const noexcept final;

	// 检测源数据是否存在指定的后缀
	virtual bool endsWith(const elem_type* _Memory) const noexcept final;

	// 检测源数据是否存在指定的后缀
	virtual bool endsWith(const elem_type* _Memory, Xs::CaseSensitivity) const noexcept final;

	// 检测源数据是否存在指定的后缀
	virtual bool endsWith(const elem_type* _Memory, size_type _Length) const noexcept final;

	// 检测源数据是否存在指定的后缀
	virtual bool endsWith(const elem_type* _Memory, size_type _Length, Xs::CaseSensitivity) const noexcept final;

	// 检测源数据是否存在指定的后缀
	virtual bool endsWith(const XString& _String) const noexcept final;

	// 检测源数据是否存在指定的后缀
	virtual bool endsWith(const XString& _String, Xs::CaseSensitivity _XCS) const noexcept final;

public:
	// 从指定位置按正序查找数据
	virtual pos_type find(elem_type _Char) const noexcept final;

	// 从指定位置按正序查找数据
	virtual pos_type find(elem_type _Char, Xs::CaseSensitivity _XCS) const noexcept final;

	// 从指定位置按正序查找数据
	virtual pos_type find(elem_type _Char, pos_type _Pos) const noexcept final;

	// 从指定位置按正序查找数据
	virtual pos_type find(elem_type _Char, pos_type _Pos, Xs::CaseSensitivity _XCS) const noexcept final;

	// 从指定位置按正序查找数据
	virtual pos_type find(const elem_type* _String) const noexcept final;

	// 从指定位置按正序查找数据
	virtual pos_type find(const elem_type* _String, Xs::CaseSensitivity _XCS) const noexcept final;

	// 从指定位置按正序查找数据
	virtual pos_type find(const elem_type* _String, pos_type _Pos) const noexcept final;

	// 从指定位置按正序查找数据
	virtual pos_type find(const elem_type* _String, pos_type _Pos, Xs::CaseSensitivity _XCS) const noexcept final;

	// 从指定位置按正序查找数据
	virtual pos_type find(const elem_type* _String, size_type _Length, pos_type _Pos) const noexcept final;

	// 从指定位置按正序查找数据
	virtual pos_type find(const elem_type* _String, size_type _Length, pos_type _Pos, Xs::CaseSensitivity _XCS) const noexcept final;

	// 从指定位置按正序查找数据
	virtual pos_type find(const XString& _String) const noexcept final;

	// 从指定位置按正序查找数据
	virtual pos_type find(const XString& _String, Xs::CaseSensitivity _XCS) const noexcept final;

	// 从指定位置按正序查找数据
	virtual pos_type find(const XString& _String, pos_type _Pos) const noexcept final;

	// 从指定位置按正序查找数据
	virtual pos_type find(const XString& _String, pos_type _Pos, Xs::CaseSensitivity _XCS) const noexcept final;

public:
	// 从指定位置按倒序查找数据
	virtual pos_type rfind(elem_type _Char) const noexcept final;

	// 从指定位置按倒序查找数据
	virtual pos_type rfind(elem_type _Char, Xs::CaseSensitivity _XCS) const noexcept final;

	// 从指定位置按倒序查找数据
	virtual pos_type rfind(elem_type _Char, pos_type _Pos) const noexcept final;

	// 从指定位置按倒序查找数据
	virtual pos_type rfind(elem_type _Char, pos_type _Pos, Xs::CaseSensitivity _XCS) const noexcept final;

	// 从指定位置按倒序查找数据
	virtual pos_type rfind(const elem_type* _String) const noexcept final;

	// 从指定位置按倒序查找数据
	virtual pos_type rfind(const elem_type* _String, Xs::CaseSensitivity _XCS) const noexcept final;

	// 从指定位置按倒序查找数据
	virtual pos_type rfind(const elem_type* _String, pos_type _Pos) const noexcept final;

	// 从指定位置按倒序查找数据
	virtual pos_type rfind(const elem_type* _String, pos_type _Pos, Xs::CaseSensitivity _XCS) const noexcept final;

	// 从指定位置按倒序查找数据
	virtual pos_type rfind(const elem_type* _String, size_type _Length, pos_type _Pos) const noexcept final;

	// 从指定位置按倒序查找数据
	virtual pos_type rfind(const elem_type* _String, size_type _Length, pos_type _Pos, Xs::CaseSensitivity _XCS) const noexcept final;

	// 从指定位置按倒序查找数据
	virtual pos_type rfind(const XString& _String) const noexcept final;

	// 从指定位置按倒序查找数据
	virtual pos_type rfind(const XString& _String, Xs::CaseSensitivity _XCS) const noexcept final;

	// 从指定位置按倒序查找数据
	virtual pos_type rfind(const XString& _String, pos_type _Pos) const noexcept final;

	// 从指定位置按倒序查找数据
	virtual pos_type rfind(const XString& _String, pos_type _Pos, Xs::CaseSensitivity _XCS) const noexcept final;

public:
	// 检查是否包含指定数据
	virtual bool contains(elem_type _Char) const noexcept final;

	// 检查是否包含指定数据
	virtual bool contains(elem_type _Char, Xs::CaseSensitivity _XCS) const noexcept final;

	// 检查是否包含指定数据
	virtual bool contains(const elem_type* _String) const noexcept final;

	// 检查是否包含指定数据
	virtual bool contains(const elem_type* _String, Xs::CaseSensitivity _XCS) const noexcept final;

	// 检查是否包含指定数据
	virtual bool contains(const elem_type* _String, size_type _Length) const noexcept final;

	// 检查是否包含指定数据
	virtual bool contains(const elem_type* _String, size_type _Length, Xs::CaseSensitivity _XCS) const noexcept final;

	// 检查是否包含指定数据
	virtual bool contains(const XString& _String) const noexcept final;

	// 检查是否包含指定数据
	virtual bool contains(const XString& _String, Xs::CaseSensitivity _XCS) const noexcept final;

public:
	// 检查是否与指定数据相同
	virtual int compare(elem_type _Char) const noexcept final;

	// 检查是否与指定数据相同
	virtual int compare(elem_type _Char, Xs::CaseSensitivity _XCS) const noexcept final;

	// 检查是否与指定数据相同
	virtual int compare(const elem_type* _String) const noexcept final;

	// 检查是否与指定数据相同
	virtual int compare(const elem_type* _String, Xs::CaseSensitivity _XCS) const noexcept final;

	// 检查是否与指定数据相同
	virtual int compare(const elem_type* _String, size_type _Length) const noexcept final;

	// 检查是否与指定数据相同
	virtual int compare(const elem_type* _String, size_type _Length, Xs::CaseSensitivity _XCS) const noexcept final;

	// 检查是否与指定数据相同
	virtual int compare(const XString& _String) const noexcept final;

	// 检查是否与指定数据相同
	virtual int compare(const XString& _String, Xs::CaseSensitivity _XCS) const noexcept final;

public:
	// 在头部插入数据
	virtual XString& prepend(elem_type _Char) noexcept final;

	// 在头部插入数据
	virtual XString& prepend(size_type _Count, elem_type _Char) noexcept final;

	// 在头部插入数据
	virtual XString& prepend(const elem_type* _String) noexcept final;

	// 在头部插入数据
	virtual XString& prepend(const elem_type* _String, size_type _Size) noexcept final;

	// 在头部插入数据
	virtual XString& prepend(const XString& _String) noexcept final;

public:
	// 在尾部添加数据
	virtual XString& append(elem_type _Char) noexcept final;

	// 在尾部添加数据
	virtual XString& append(size_type _Count, elem_type _Char) noexcept final;

	// 在尾部添加数据
	virtual XString& append(const elem_type* _String) noexcept final;

	// 在尾部添加数据
	virtual XString& append(const elem_type* _String, size_type _Size) noexcept final;

	// 在尾部添加数据
	virtual XString& append(const XString& _String) noexcept final;

public:
	// 在指定下标处插入数据
	virtual XString& insert(pos_type _Pos, elem_type _Char) noexcept final;

	// 在指定下标处插入数据
	virtual XString& insert(pos_type _Pos, size_type _Count, elem_type _Char) noexcept final;

	// 在指定下标处插入数据
	virtual XString& insert(pos_type _Pos, const elem_type* _String) noexcept final;

	// 在指定下标处插入数据
	virtual XString& insert(pos_type _Pos, const elem_type* _String, size_type _Length) noexcept final;

	// Inserts data from the specified location XString
	virtual XString& insert(pos_type _Pos, const XString& _String) noexcept final;

public:
	// 移除下标 pos 处的 length 长度数据
	virtual XString& remove(pos_type _Pos, size_type _Length) noexcept final;

	// 删除与参数相同的数据
	virtual XString& remove(elem_type _Char) noexcept final;

	// 删除与参数相同的数据
	virtual XString& remove(elem_type _Char, Xs::CaseSensitivity _XCS) noexcept final;

	// 删除与参数相同的数据
	virtual XString& remove(const elem_type* _String) noexcept final;

	// 删除与参数相同的数据
	virtual XString& remove(const elem_type* _String, Xs::CaseSensitivity _XCS) noexcept final;

	// 删除与参数相同的数据
	virtual XString& remove(const elem_type* _String, size_type _Length) noexcept final;

	// 删除与参数相同的数据
	virtual XString& remove(const elem_type* _String, size_type _Length, Xs::CaseSensitivity _XCS) noexcept final;

	// 删除与参数相同的数据
	virtual XString& remove(const XString& _String) noexcept final;

	// 删除与参数相同的数据
	virtual XString& remove(const XString& _String, Xs::CaseSensitivity _XCS) noexcept final;

public:
	// 替换数据
	virtual XString& replace(pos_type _Pos, size_type _Length, elem_type _After) noexcept final;

	// 替换数据
	virtual XString& replace(pos_type _Pos, size_type _Length, const elem_type* _After) noexcept final;

	// 替换数据
	virtual XString& replace(pos_type _Pos, size_type _Length, const elem_type* _After, size_type _LengthA) noexcept final;

	// 替换数据
	virtual XString& replace(pos_type _Pos, size_type _Length, const XString& _After) noexcept final;

public:
	// 替换数据
	virtual XString& replace(elem_type _Before, elem_type _After) noexcept final;

	// 替换数据
	virtual XString& replace(elem_type _Before, elem_type _After, Xs::CaseSensitivity _XCS) noexcept final;

	// 替换数据
	virtual XString& replace(elem_type _Before, const elem_type* _After, size_type _LengthA) noexcept final;

	// 替换数据
	virtual XString& replace(elem_type _Before, const elem_type* _After, size_type _LengthA, Xs::CaseSensitivity _XCS) noexcept final;

	// 替换数据
	virtual XString& replace(elem_type _Before, const XString& _After) noexcept final;

	// 替换数据
	virtual XString& replace(elem_type _Before, const XString& _After, Xs::CaseSensitivity _XCS) noexcept final;

public:
	// 替换数据
	virtual XString& replace(const elem_type* _Before, elem_type _After) noexcept final;

	// 替换数据
	virtual XString& replace(const elem_type* _Before, elem_type _After, Xs::CaseSensitivity _XCS) noexcept final;

	// 替换数据
	virtual XString& replace(const elem_type* _Before, const elem_type* _After, size_type _LengthA) noexcept final;

	// 替换数据
	virtual XString& replace(const elem_type* _Before, const elem_type* _After, size_type _LengthA, Xs::CaseSensitivity _XCS) noexcept final;

	// 替换数据
	virtual XString& replace(const elem_type* _Before, const XString& _After) noexcept final;

	// 替换数据
	virtual XString& replace(const elem_type* _Before, const XString& _After, Xs::CaseSensitivity _XCS) noexcept final;

public:
	// 替换数据
	virtual XString& replace(const elem_type* _Before, size_type _LengthB, elem_type _After) noexcept final;

	// 替换数据
	virtual XString& replace(const elem_type* _Before, size_type _LengthB, elem_type _After, Xs::CaseSensitivity _XCS) noexcept final;

	// 替换数据
	virtual XString& replace(const elem_type* _Before, size_type _LengthB, const elem_type* _After, size_type _LengthA) noexcept final;

	// 替换数据
	virtual XString& replace(const elem_type* _Before, size_type _LengthB, const elem_type* _After, size_type _LengthA, Xs::CaseSensitivity _XCS) noexcept final;

	// 替换数据
	virtual XString& replace(const elem_type* _Before, size_type _LengthB, const XString& _After) noexcept final;

	// 替换数据
	virtual XString& replace(const elem_type* _Before, size_type _LengthB, const XString& _After, Xs::CaseSensitivity _XCS) noexcept final;

public:
	// 替换数据
	virtual XString& replace(const XString& _Before, elem_type _After) noexcept final;

	// 替换数据
	virtual XString& replace(const XString& _Before, elem_type _After, Xs::CaseSensitivity _XCS) noexcept final;

	// 替换数据
	virtual XString& replace(const XString& _Before, const elem_type* _After, size_type _LengthA) noexcept final;

	// 替换数据
	virtual XString& replace(const XString& _Before, const elem_type* _After, size_type _LengthA, Xs::CaseSensitivity _XCS) noexcept final;

	// 替换数据
	virtual XString& replace(const XString& _Before, const XString& _After) noexcept final;

	// 替换数据
	virtual XString& replace(const XString& _Before, const XString& _After, Xs::CaseSensitivity _XCS) noexcept final;

public:
	// 按指定数据拆分字符串
	virtual std::list<XString> split(elem_type _Char) const noexcept final;

	// 按指定数据拆分字符串
	virtual std::list<XString> split(const elem_type* _Memory) const noexcept final;

	// 按指定数据拆分字符串
	virtual std::list<XString> split(const elem_type* _Memory, size_type _Size) const noexcept final;

	// 按指定数据拆分字符串
	virtual std::list<XString> split(const XString& _String) const noexcept final;

public:
	// 判断一个字符是否为空白字符
	static bool isSpace(elem_type _Char) noexcept;

	// 格式化字符串 (char* [%s]) (wchar_t* [%ls])
	static XString format(const char* _Format, ...) noexcept;

public:
	// [conv] 转换至大写
	XString toUpper() const noexcept;

	// [conv] 转换至小写
	XString toLower() const noexcept;

public:
	// [conv] convert to base64
	virtual XString toBase64() const noexcept final;

	// [conv] convert from base64
	virtual XString fromBase64(const elem_type* _String, size_type _Size) noexcept final;

	// [conv] convert from base64
	virtual XString fromBase64(const XString& _Base64) noexcept final;

public:
	// [conv] 转换至AString
	virtual AString toAString() const noexcept final;

	// [conv] 从AString转换
	static XString fromAString(const char* _AString) noexcept;

	// [conv] 从AString转换
	static XString fromAString(const AString& _AString) noexcept;

public:
	// [conv] 转换至WString
	virtual WString toWString() const noexcept final;

	// [conv] 从WString转换
	static XString fromWString(const wchar_t* _WString) noexcept;

	// [conv] 从WString转换
	static XString fromWString(const WString& _WString) noexcept;

public:
	// [conv] 转换至UString
	virtual UString toUString() const noexcept final;

	// [conv] 从UString转换
	static XString fromUString(const char* _UString) noexcept;

	// [conv] 从UString转换
	static XString fromUString(const UString& _UString) noexcept;

public:
	// [conv] 转换至NString (Windows: ASCII / 其它: UTF-8)
	virtual NString toNString() const noexcept final;

	// [conv] 从NString转换 (Windows: ASCII / 其它: UTF-8)
	static XString fromNString(const char* _NString) noexcept;

	// [conv] 从NString转换 (Windows: ASCII / 其它: UTF-8)
	static XString fromNString(const NString& _NString) noexcept;

public:
	// [conv] 转换至HEX
	virtual XString toHex() const noexcept final;

	// [conv] 从HEX转换
	static XString fromHex(const elem_type* _Hex) noexcept;

	// [conv] 从HEX转换
	static XString fromHex(const elem_type* _Hex, size_type _Size) noexcept;

	// [conv] 从HEX转换
	static XString fromHex(const XString& _Hex) noexcept;

public:
	// [conv] convert to UTF-8 encoded byte array
	virtual XByteArray toBytes() const noexcept final;

	// [conv] convert from byte array
	static XString fromBytes(const XByteArray& _Bytes) noexcept;

public:
	// [conv] convert to UTF-8 encoded url
	virtual XString toUrl() const noexcept final;

	// [conv] convert from UTF-8 encoded url
	static XString fromUrl(const XString& _URL) noexcept;

public:
	// [convert] convert to char
	char toChar(bool* _Ok = nullptr, int _Base = 10) const noexcept;

	// [convert] convert to unsigned char
	unsigned char toUChar(bool* _Ok = nullptr, int _Base = 10) const noexcept;

	// [convert] convert to short
	short toShort(bool* _Ok = nullptr, int _Base = 10) const noexcept;

	// [convert] convert to unsigned short
	unsigned short toUShort(bool* _Ok = nullptr, int _Base = 10) const noexcept;

	// [convert] convert to int
	int toInt(bool* _Ok = nullptr, int _Base = 10) const noexcept;

	// [convert] convert to unsigned int
	unsigned int toUInt(bool* _Ok = nullptr, int _Base = 10) const noexcept;

	// [convert] convert to long
	long toLong(bool* _Ok = nullptr, int _Base = 10) const noexcept;

	// [convert] convert to unsigned long
	unsigned long toULong(bool* _Ok = nullptr, int _Base = 10) const noexcept;

	// [convert] convert to long long
	long long toLLong(bool* _Ok = nullptr, int _Base = 10) const noexcept;

	// [convert] convert to unsigned long long
	unsigned long long toULLong(bool* _Ok = nullptr, int _Base = 10) const noexcept;

	// [convert] convert to float
	float toFloat(bool* _Ok = nullptr) const noexcept;

	// [convert] convert to double
	double toDouble(bool* _Ok = nullptr) const noexcept;

public:
	// [convert] convert from number
	XString& setNumber(char _Value, int _Base = 10) noexcept;

	// [convert] convert from number
	XString& setNumber(unsigned char _Value, int _Base = 10) noexcept;

	// [convert] convert from number
	XString& setNumber(short _Value, int _Base = 10) noexcept;

	// [convert] convert from number
	XString& setNumber(unsigned short _Value, int _Base = 10) noexcept;

	// [convert] convert from number
	XString& setNumber(int _Value, int _Base = 10) noexcept;

	// [convert] convert from number
	XString& setNumber(unsigned int _Value, int _Base = 10) noexcept;

	// [convert] convert from number
	XString& setNumber(long _Value, int _Base = 10) noexcept;

	// [convert] convert from number
	XString& setNumber(unsigned long _Value, int _Base = 10) noexcept;

	// [convert] convert from number
	XString& setNumber(long long _Value, int _Base = 10) noexcept;

	// [convert] convert from number
	XString& setNumber(unsigned long long _Value, int _Base = 10) noexcept;

	// [convert] convert from number
	XString& setNumber(float _Value, char _Format, int _Prec) noexcept;

	// [convert] convert from number
	XString& setNumber(double _Value, char _Format, int _Prec) noexcept;

public:
	// [convert] convert from number
	static XString number(char _Value, int _Base = 10) noexcept;

	// [convert] convert from number
	static XString number(unsigned char _Value, int _Base = 10) noexcept;

	// [convert] convert from number
	static XString number(short _Value, int _Base = 10) noexcept;

	// [convert] convert from number
	static XString number(unsigned short _Value, int _Base = 10) noexcept;

	// [convert] convert from number
	static XString number(int _Value, int _Base = 10) noexcept;

	// [convert] convert from number
	static XString number(unsigned int _Value, int _Base = 10) noexcept;

	// [convert] convert from number
	static XString number(long _Value, int _Base = 10) noexcept;

	// [convert] convert from number
	static XString number(unsigned long _Value, int _Base = 10) noexcept;

	// [convert] convert from number
	static XString number(long long _Value, int _Base = 10) noexcept;

	// [convert] convert from number
	static XString number(unsigned long long _Value, int _Base = 10) noexcept;

	// [convert] convert from number
	static XString number(float _Value, char _Format = 'g', int _Prec = 6) noexcept;

	// [convert] convert from number
	static XString number(double _Value, char _Format = 'g', int _Prec = 6) noexcept;
};


// Standard enhancement function : stream <<
_XCOREAPI_ std::ostream& operator << (std::ostream& _OStream, const XString& _String) noexcept;

// Standard enhancement function : stream >>
_XCOREAPI_ std::istream& operator >> (std::istream& _IStream, XString& _String) noexcept;

// Standard enhancement function : getline
_XCOREAPI_ std::istream& getline(std::istream& _IStream, XString& _String, char _Delim) noexcept;

// Standard enhancement function : getline
_XCOREAPI_ std::istream& getline(std::istream& _IStream, XString& _String) noexcept;

#endif
