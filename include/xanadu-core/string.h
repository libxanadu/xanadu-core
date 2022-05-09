﻿#ifndef			_XANADU_CORE_STRING_H_
#define			_XANADU_CORE_STRING_H_

#include <xanadu-core/allocator.h>


// String type
using			AString = std::string;		// ASCII
using			WString = std::wstring;		// UNICODE
using			UString = std::string;		// UTF-8
using			LString = std::string;		// Latin1(ISO-8859-1)
#if defined(XANADU_SYSTEM_WINDOWS)
using			NString = AString;
#else
using			NString = UString;
#endif


/// namespace xanadu
namespace xanadu
{
	/// class string
	class _XCOREAPI_ string
	{
	public:
		using elem_type			= char;
		using size_type			= xanadu::size_type;
		using pos_type			= xanadu::pos_type;

	public:
		static const pos_type npos	= xanadu::allocator::npos;

	private:
		allocator			_Allocator;

	public:
		// constructor
		string() noexcept;

		// constructor
		string(size_type _Length, elem_type _Char) noexcept;

		// constructor
		string(const elem_type* _Memory) noexcept; // NOLINT(google-explicit-constructor)

		// constructor
		string(const elem_type* _Memory, size_type _Length) noexcept;

		// constructor
		string(const std::string& _StdStr) noexcept; // NOLINT(google-explicit-constructor)

		// constructor
		string(const xanadu::string& _String) noexcept;

		// constructor
		string(xanadu::string&& _String) noexcept;

		// destructor
		virtual ~string() noexcept;

	public:
		// operator overload =
		string& operator = (const elem_type* _Memory) noexcept;

		// operator overload =
		string& operator = (const std::string& _String) noexcept;

		// operator overload =
		string& operator = (const xanadu::string& _String) noexcept;

		// operator overload =
		string& operator = (xanadu::string&& _String) noexcept;

	public:
		// operator overload +=
		string& operator += (elem_type _Char) noexcept;

		// operator overload +=
		string& operator += (const elem_type* _String) noexcept;

		// operator overload +=
		string& operator += (const std::string& _String) noexcept;

		// operator overload +=
		string& operator += (const xanadu::string& _String) noexcept;

	public:
		// operator overload +
		string operator + (elem_type _Char) const noexcept;

		// operator overload +
		string operator + (const elem_type* _String) const noexcept;

		// operator overload +
		string operator + (const std::string& _String) const noexcept;

		// operator overload +
		string operator + (const xanadu::string& _String) const noexcept;

	public:
		// operator overload ==
		bool operator == (elem_type _Char) const noexcept;

		// operator overload ==
		bool operator == (const elem_type* _String) const noexcept;

		// operator overload ==
		bool operator == (const xanadu::string& _String) const noexcept;

		// operator overload !=
		bool operator != (elem_type _Char) const noexcept;

		// operator overload !=
		bool operator != (const elem_type* _String) const noexcept;

		// operator overload !=
		bool operator != (const xanadu::string& _String) const noexcept;

		// operator overload <
		bool operator < (elem_type _Char) const noexcept;

		// operator overload <
		bool operator < (const elem_type* _String) const noexcept;

		// operator overload <
		bool operator < (const xanadu::string& _String) const noexcept;

		// operator overload >
		bool operator > (elem_type _Char) const noexcept;

		// operator overload >
		bool operator > (const elem_type* _String) const noexcept;

		// operator overload >
		bool operator > (const xanadu::string& _String) const noexcept;

		// operator overload <=
		bool operator <= (elem_type _Char) const noexcept;

		// operator overload <=
		bool operator <= (const elem_type* _String) const noexcept;

		// operator overload <=
		bool operator <= (const xanadu::string& _String) const noexcept;

		// operator overload >=
		bool operator >= (elem_type _Char) const noexcept;

		// operator overload >=
		bool operator >= (const elem_type* _String) const noexcept;

		// operator overload >=
		bool operator >= (const xanadu::string& _String) const noexcept;

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
		virtual xanadu::string substr(pos_type _Pos) const noexcept final;

		// 从源中截取部分数据
		virtual xanadu::string substr(pos_type _Pos, size_type _Length) const noexcept final;

		// 从源中截取部分数据
		virtual xanadu::string left(pos_type _Pos) const noexcept final;

		// 从源中截取部分数据
		virtual xanadu::string right(pos_type _Pos) const noexcept final;

	public:
		// [mid] 从源中截取部分数据
		virtual xanadu::string mid(pos_type _Pos) const noexcept final;

		// [mid] 从源中截取部分数据
		virtual xanadu::string mid(pos_type _Pos, size_type _Size) const noexcept final;

		// [mid] 从源中截取部分数据
		virtual xanadu::string mid(const elem_type* _Left, const elem_type* _Right) const noexcept final;

		// [mid] 从源中截取部分数据
		virtual xanadu::string mid(const elem_type* _Left, const elem_type* _Right, xanadu::CaseSensitivity _XCS) const noexcept final;

		// [mid] 从源中截取部分数据
		virtual xanadu::string mid(const elem_type* _Left, size_type _LengthL, const elem_type* _Right, size_type _LengthR) const noexcept final;

		// [mid] 从源中截取部分数据
		virtual xanadu::string mid(const elem_type* _Left, size_type _LengthL, const elem_type* _Right, size_type _LengthR, xanadu::CaseSensitivity _XCS) const noexcept final;

		// [mid] 从源中截取部分数据
		virtual xanadu::string mid(const elem_type* _Left, const xanadu::string& _Right) const noexcept final;

		// [mid] 从源中截取部分数据
		virtual xanadu::string mid(const elem_type* _Left, const xanadu::string& _Right, xanadu::CaseSensitivity _XCS) const noexcept final;

		// [mid] 从源中截取部分数据
		virtual xanadu::string mid(const xanadu::string& _Left, const elem_type* _Right) const noexcept final;

		// [mid] 从源中截取部分数据
		virtual xanadu::string mid(const xanadu::string& _Left, const elem_type* _Right, xanadu::CaseSensitivity _XCS) const noexcept final;

		// [mid] 从源中截取部分数据
		virtual xanadu::string mid(const xanadu::string& _Left, const xanadu::string& _Right) const noexcept final;

		// [mid] 从源中截取部分数据
		virtual xanadu::string mid(const xanadu::string& _Left, const xanadu::string& _Right, xanadu::CaseSensitivity _XCS) const noexcept final;

	public:
		// 检测源数据是否存在指定的前缀
		virtual bool startsWith(elem_type _Char) const noexcept final;

		// 检测源数据是否存在指定的前缀
		virtual bool startsWith(elem_type _Char, xanadu::CaseSensitivity _XCS) const noexcept final;

		// 检测源数据是否存在指定的前缀
		virtual bool startsWith(const elem_type* _Memory) const noexcept final;

		// 检测源数据是否存在指定的前缀
		virtual bool startsWith(const elem_type* _Memory, xanadu::CaseSensitivity _XCS) const noexcept final;

		// 检测源数据是否存在指定的前缀
		virtual bool startsWith(const elem_type* _Memory, size_type _Length) const noexcept final;

		// 检测源数据是否存在指定的前缀
		virtual bool startsWith(const elem_type* _Memory, size_type _Length, xanadu::CaseSensitivity _XCS) const noexcept final;

		// 检测源数据是否存在指定的前缀
		virtual bool startsWith(const xanadu::string& _String) const noexcept final;

		// 检测源数据是否存在指定的前缀
		virtual bool startsWith(const xanadu::string& _String, xanadu::CaseSensitivity _XCS) const noexcept final;

	public:
		// 检测源数据是否存在指定的后缀
		virtual bool endsWith(elem_type _Char) const noexcept final;

		// 检测源数据是否存在指定的后缀
		virtual bool endsWith(elem_type _Char, xanadu::CaseSensitivity _XCS) const noexcept final;

		// 检测源数据是否存在指定的后缀
		virtual bool endsWith(const elem_type* _Memory) const noexcept final;

		// 检测源数据是否存在指定的后缀
		virtual bool endsWith(const elem_type* _Memory, xanadu::CaseSensitivity) const noexcept final;

		// 检测源数据是否存在指定的后缀
		virtual bool endsWith(const elem_type* _Memory, size_type _Length) const noexcept final;

		// 检测源数据是否存在指定的后缀
		virtual bool endsWith(const elem_type* _Memory, size_type _Length, xanadu::CaseSensitivity) const noexcept final;

		// 检测源数据是否存在指定的后缀
		virtual bool endsWith(const xanadu::string& _String) const noexcept final;

		// 检测源数据是否存在指定的后缀
		virtual bool endsWith(const xanadu::string& _String, xanadu::CaseSensitivity _XCS) const noexcept final;
		
	public:
		// 从指定位置按正序查找数据
		virtual pos_type find(elem_type _Char) const noexcept final;

		// 从指定位置按正序查找数据
		virtual pos_type find(elem_type _Char, xanadu::CaseSensitivity _XCS) const noexcept final;

		// 从指定位置按正序查找数据
		virtual pos_type find(elem_type _Char, pos_type _Pos) const noexcept final;

		// 从指定位置按正序查找数据
		virtual pos_type find(elem_type _Char, pos_type _Pos, xanadu::CaseSensitivity _XCS) const noexcept final;

		// 从指定位置按正序查找数据
		virtual pos_type find(const elem_type* _String) const noexcept final;

		// 从指定位置按正序查找数据
		virtual pos_type find(const elem_type* _String, xanadu::CaseSensitivity _XCS) const noexcept final;

		// 从指定位置按正序查找数据
		virtual pos_type find(const elem_type* _String, pos_type _Pos) const noexcept final;

		// 从指定位置按正序查找数据
		virtual pos_type find(const elem_type* _String, pos_type _Pos, xanadu::CaseSensitivity _XCS) const noexcept final;

		// 从指定位置按正序查找数据
		virtual pos_type find(const elem_type* _String, size_type _Length, pos_type _Pos) const noexcept final;

		// 从指定位置按正序查找数据
		virtual pos_type find(const elem_type* _String, size_type _Length, pos_type _Pos, xanadu::CaseSensitivity _XCS) const noexcept final;

		// 从指定位置按正序查找数据
		virtual pos_type find(const xanadu::string& _String) const noexcept final;

		// 从指定位置按正序查找数据
		virtual pos_type find(const xanadu::string& _String, xanadu::CaseSensitivity _XCS) const noexcept final;

		// 从指定位置按正序查找数据
		virtual pos_type find(const xanadu::string& _String, pos_type _Pos) const noexcept final;

		// 从指定位置按正序查找数据
		virtual pos_type find(const xanadu::string& _String, pos_type _Pos, xanadu::CaseSensitivity _XCS) const noexcept final;

	public:
		// 从指定位置按倒序查找数据
		virtual pos_type rfind(elem_type _Char) const noexcept final;

		// 从指定位置按倒序查找数据
		virtual pos_type rfind(elem_type _Char, xanadu::CaseSensitivity _XCS) const noexcept final;

		// 从指定位置按倒序查找数据
		virtual pos_type rfind(elem_type _Char, pos_type _Pos) const noexcept final;

		// 从指定位置按倒序查找数据
		virtual pos_type rfind(elem_type _Char, pos_type _Pos, xanadu::CaseSensitivity _XCS) const noexcept final;

		// 从指定位置按倒序查找数据
		virtual pos_type rfind(const elem_type* _String) const noexcept final;

		// 从指定位置按倒序查找数据
		virtual pos_type rfind(const elem_type* _String, xanadu::CaseSensitivity _XCS) const noexcept final;

		// 从指定位置按倒序查找数据
		virtual pos_type rfind(const elem_type* _String, pos_type _Pos) const noexcept final;

		// 从指定位置按倒序查找数据
		virtual pos_type rfind(const elem_type* _String, pos_type _Pos, xanadu::CaseSensitivity _XCS) const noexcept final;

		// 从指定位置按倒序查找数据
		virtual pos_type rfind(const elem_type* _String, size_type _Length, pos_type _Pos) const noexcept final;

		// 从指定位置按倒序查找数据
		virtual pos_type rfind(const elem_type* _String, size_type _Length, pos_type _Pos, xanadu::CaseSensitivity _XCS) const noexcept final;

		// 从指定位置按倒序查找数据
		virtual pos_type rfind(const xanadu::string& _String) const noexcept final;

		// 从指定位置按倒序查找数据
		virtual pos_type rfind(const xanadu::string& _String, xanadu::CaseSensitivity _XCS) const noexcept final;

		// 从指定位置按倒序查找数据
		virtual pos_type rfind(const xanadu::string& _String, pos_type _Pos) const noexcept final;

		// 从指定位置按倒序查找数据
		virtual pos_type rfind(const xanadu::string& _String, pos_type _Pos, xanadu::CaseSensitivity _XCS) const noexcept final;

	public:
		// 检查是否包含指定数据
		virtual bool contains(elem_type _Char) const noexcept final;

		// 检查是否包含指定数据
		virtual bool contains(elem_type _Char, xanadu::CaseSensitivity _XCS) const noexcept final;

		// 检查是否包含指定数据
		virtual bool contains(const elem_type* _String) const noexcept final;

		// 检查是否包含指定数据
		virtual bool contains(const elem_type* _String, xanadu::CaseSensitivity _XCS) const noexcept final;

		// 检查是否包含指定数据
		virtual bool contains(const elem_type* _String, size_type _Length) const noexcept final;

		// 检查是否包含指定数据
		virtual bool contains(const elem_type* _String, size_type _Length, xanadu::CaseSensitivity _XCS) const noexcept final;

		// 检查是否包含指定数据
		virtual bool contains(const xanadu::string& _String) const noexcept final;

		// 检查是否包含指定数据
		virtual bool contains(const xanadu::string& _String, xanadu::CaseSensitivity _XCS) const noexcept final;

	public:
		// 检查是否与指定数据相同
		virtual int compare(elem_type _Char) const noexcept final;

		// 检查是否与指定数据相同
		virtual int compare(elem_type _Char, xanadu::CaseSensitivity _XCS) const noexcept final;

		// 检查是否与指定数据相同
		virtual int compare(const elem_type* _String) const noexcept final;

		// 检查是否与指定数据相同
		virtual int compare(const elem_type* _String, xanadu::CaseSensitivity _XCS) const noexcept final;

		// 检查是否与指定数据相同
		virtual int compare(const elem_type* _String, size_type _Length) const noexcept final;

		// 检查是否与指定数据相同
		virtual int compare(const elem_type* _String, size_type _Length, xanadu::CaseSensitivity _XCS) const noexcept final;

		// 检查是否与指定数据相同
		virtual int compare(const xanadu::string& _String) const noexcept final;

		// 检查是否与指定数据相同
		virtual int compare(const xanadu::string& _String, xanadu::CaseSensitivity _XCS) const noexcept final;

	public:
		// 在头部插入数据
		virtual xanadu::string& prepend(elem_type _Char) noexcept final;

		// 在头部插入数据
		virtual xanadu::string& prepend(const elem_type* _String) noexcept final;

		// 在头部插入数据
		virtual xanadu::string& prepend(const elem_type* _String, size_type _Size) noexcept final;

		// 在头部插入数据
		virtual xanadu::string& prepend(const xanadu::string& _String) noexcept final;

	public:
		// 在尾部添加数据
		virtual xanadu::string& append(elem_type _Char) noexcept final;

		// 在尾部添加数据
		virtual xanadu::string& append(const elem_type* _String) noexcept final;

		// 在尾部添加数据
		virtual xanadu::string& append(const elem_type* _String, size_type _Size) noexcept final;

		// 在尾部添加数据
		virtual xanadu::string& append(const xanadu::string& _String) noexcept final;

	public:
		// 在指定下标处插入数据
		virtual xanadu::string& insert(pos_type _Pos, elem_type _Char) noexcept final;

		// 在指定下标处插入数据
		virtual xanadu::string& insert(pos_type _Pos, size_type _Count, elem_type _Char) noexcept final;

		// 在指定下标处插入数据
		virtual xanadu::string& insert(pos_type _Pos, const elem_type* _String) noexcept final;

		// 在指定下标处插入数据
		virtual xanadu::string& insert(pos_type _Pos, const elem_type* _String, size_type _Length) noexcept final;

		// Inserts data from the specified location xanadu::string
		virtual xanadu::string& insert(pos_type _Pos, const xanadu::string& _String) noexcept final;

	public:
		// 移除下标 pos 处的 length 长度数据
		virtual xanadu::string& remove(pos_type _Pos, size_type _Length) noexcept final;

		// 删除与参数相同的数据
		virtual xanadu::string& remove(elem_type _Char) noexcept final;

		// 删除与参数相同的数据
		virtual xanadu::string& remove(elem_type _Char, xanadu::CaseSensitivity _XCS) noexcept final;

		// 删除与参数相同的数据
		virtual xanadu::string& remove(const elem_type* _String) noexcept final;

		// 删除与参数相同的数据
		virtual xanadu::string& remove(const elem_type* _String, xanadu::CaseSensitivity _XCS) noexcept final;

		// 删除与参数相同的数据
		virtual xanadu::string& remove(const elem_type* _String, size_type _Length) noexcept final;

		// 删除与参数相同的数据
		virtual xanadu::string& remove(const elem_type* _String, size_type _Length, xanadu::CaseSensitivity _XCS) noexcept final;

		// 删除与参数相同的数据
		virtual xanadu::string& remove(const xanadu::string& _String) noexcept final;

		// 删除与参数相同的数据
		virtual xanadu::string& remove(const xanadu::string& _String, xanadu::CaseSensitivity _XCS) noexcept final;

	public:
		// 替换数据
		virtual xanadu::string& replace(pos_type _Pos, size_type _Length, elem_type _After) noexcept final;

		// 替换数据
		virtual xanadu::string& replace(pos_type _Pos, size_type _Length, const elem_type* _After) noexcept final;

		// 替换数据
		virtual xanadu::string& replace(pos_type _Pos, size_type _Length, const elem_type* _After, size_type _LengthA) noexcept final;

		// 替换数据
		virtual xanadu::string& replace(pos_type _Pos, size_type _Length, const xanadu::string& _After) noexcept final;

	public:
		// 替换数据
		virtual xanadu::string& replace(elem_type _Before, elem_type _After) noexcept final;

		// 替换数据
		virtual xanadu::string& replace(elem_type _Before, elem_type _After, xanadu::CaseSensitivity _XCS) noexcept final;

		// 替换数据
		virtual xanadu::string& replace(elem_type _Before, const elem_type* _After, size_type _LengthA) noexcept final;

		// 替换数据
		virtual xanadu::string& replace(elem_type _Before, const elem_type* _After, size_type _LengthA, xanadu::CaseSensitivity _XCS) noexcept final;

		// 替换数据
		virtual xanadu::string& replace(elem_type _Before, const xanadu::string& _After) noexcept final;

		// 替换数据
		virtual xanadu::string& replace(elem_type _Before, const xanadu::string& _After, xanadu::CaseSensitivity _XCS) noexcept final;

	public:
		// 替换数据
		virtual xanadu::string& replace(const elem_type* _Before, elem_type _After) noexcept final;

		// 替换数据
		virtual xanadu::string& replace(const elem_type* _Before, elem_type _After, xanadu::CaseSensitivity _XCS) noexcept final;

		// 替换数据
		virtual xanadu::string& replace(const elem_type* _Before, const elem_type* _After, size_type _LengthA) noexcept final;

		// 替换数据
		virtual xanadu::string& replace(const elem_type* _Before, const elem_type* _After, size_type _LengthA, xanadu::CaseSensitivity _XCS) noexcept final;

		// 替换数据
		virtual xanadu::string& replace(const elem_type* _Before, const xanadu::string& _After) noexcept final;

		// 替换数据
		virtual xanadu::string& replace(const elem_type* _Before, const xanadu::string& _After, xanadu::CaseSensitivity _XCS) noexcept final;

	public:
		// 替换数据
		virtual xanadu::string& replace(const elem_type* _Before, size_type _LengthB, elem_type _After) noexcept final;

		// 替换数据
		virtual xanadu::string& replace(const elem_type* _Before, size_type _LengthB, elem_type _After, xanadu::CaseSensitivity _XCS) noexcept final;

		// 替换数据
		virtual xanadu::string& replace(const elem_type* _Before, size_type _LengthB, const elem_type* _After, size_type _LengthA) noexcept final;

		// 替换数据
		virtual xanadu::string& replace(const elem_type* _Before, size_type _LengthB, const elem_type* _After, size_type _LengthA, xanadu::CaseSensitivity _XCS) noexcept final;

		// 替换数据
		virtual xanadu::string& replace(const elem_type* _Before, size_type _LengthB, const xanadu::string& _After) noexcept final;

		// 替换数据
		virtual xanadu::string& replace(const elem_type* _Before, size_type _LengthB, const xanadu::string& _After, xanadu::CaseSensitivity _XCS) noexcept final;

	public:
		// 替换数据
		virtual xanadu::string& replace(const xanadu::string& _Before, elem_type _After) noexcept final;

		// 替换数据
		virtual xanadu::string& replace(const xanadu::string& _Before, elem_type _After, xanadu::CaseSensitivity _XCS) noexcept final;

		// 替换数据
		virtual xanadu::string& replace(const xanadu::string& _Before, const elem_type* _After, size_type _LengthA) noexcept final;

		// 替换数据
		virtual xanadu::string& replace(const xanadu::string& _Before, const elem_type* _After, size_type _LengthA, xanadu::CaseSensitivity _XCS) noexcept final;

		// 替换数据
		virtual xanadu::string& replace(const xanadu::string& _Before, const xanadu::string& _After) noexcept final;

		// 替换数据
		virtual xanadu::string& replace(const xanadu::string& _Before, const xanadu::string& _After, xanadu::CaseSensitivity _XCS) noexcept final;

	public:
		// 按指定数据拆分字符串
		virtual std::list<xanadu::string> split(elem_type _Char) const noexcept final;

		// 按指定数据拆分字符串
		virtual std::list<xanadu::string> split(const elem_type* _Memory) const noexcept final;

		// 按指定数据拆分字符串
		virtual std::list<xanadu::string> split(const elem_type* _Memory, size_type _Size) const noexcept final;

		// 按指定数据拆分字符串
		virtual std::list<xanadu::string> split(const xanadu::string& _String) const noexcept final;

	public:
		// 判断一个字符是否为空白字符
		static bool isSpace(elem_type _Char) noexcept;

		// 格式化字符串 (char* [%s]) (wchar_t* [%ls])
		static xanadu::string format(const char* _Format, ...) noexcept;

	public:
		// [conv] 转换至大写
		xanadu::string toUpper() const noexcept;

		// [conv] 转换至小写
		xanadu::string toLower() const noexcept;

	public:
		// [conv] 转换至AString
		virtual AString toAString() const noexcept final;

		// [conv] 从AString转换
		static xanadu::string fromAString(const char* _AString) noexcept;

		// [conv] 从AString转换
		static xanadu::string fromAString(const AString& _AString) noexcept;

	public:
		// [conv] 转换至WString
		virtual WString toWString() const noexcept final;

		// [conv] 从WString转换
		static xanadu::string fromWString(const wchar_t* _WString) noexcept;

		// [conv] 从WString转换
		static xanadu::string fromWString(const WString& _WString) noexcept;

	public:
		// [conv] 转换至UString
		virtual UString toUString() const noexcept final;

		// [conv] 从UString转换
		static xanadu::string fromUString(const char* _UString) noexcept;

		// [conv] 从UString转换
		static xanadu::string fromUString(const UString& _UString) noexcept;

	public:
		// [conv] 转换至NString (Windows: ASCII / 其它: UTF-8)
		virtual NString toNString() const noexcept final;

		// [conv] 从NString转换 (Windows: ASCII / 其它: UTF-8)
		static xanadu::string fromNString(const char* _NString) noexcept;

		// [conv] 从NString转换 (Windows: ASCII / 其它: UTF-8)
		static xanadu::string fromNString(const UString& _NString) noexcept;

	public:
		// [conv] 转换至HEX
		virtual xanadu::string toHex() const noexcept final;

		// [conv] 从HEX转换
		static xanadu::string fromHex(const elem_type* _String) noexcept;

		// [conv] 从HEX转换
		static xanadu::string fromHex(const elem_type* _String, size_type _Size) noexcept;

		// [conv] 从HEX转换
		static xanadu::string fromHex(const xanadu::string& _Hex) noexcept;

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
		xanadu::string& setNumber(char _Value, int _Base = 10) noexcept;

		// [convert] convert from number
		xanadu::string& setNumber(unsigned char _Value, int _Base = 10) noexcept;

		// [convert] convert from number
		xanadu::string& setNumber(short _Value, int _Base = 10) noexcept;

		// [convert] convert from number
		xanadu::string& setNumber(unsigned short _Value, int _Base = 10) noexcept;

		// [convert] convert from number
		xanadu::string& setNumber(int _Value, int _Base = 10) noexcept;

		// [convert] convert from number
		xanadu::string& setNumber(unsigned int _Value, int _Base = 10) noexcept;

		// [convert] convert from number
		xanadu::string& setNumber(long _Value, int _Base = 10) noexcept;

		// [convert] convert from number
		xanadu::string& setNumber(unsigned long _Value, int _Base = 10) noexcept;

		// [convert] convert from number
		xanadu::string& setNumber(long long _Value, int _Base = 10) noexcept;

		// [convert] convert from number
		xanadu::string& setNumber(unsigned long long _Value, int _Base = 10) noexcept;

		// [convert] convert from number
		xanadu::string& setNumber(float _Value, char _Format, int _Prec) noexcept;

		// [convert] convert from number
		xanadu::string& setNumber(double _Value, char _Format, int _Prec) noexcept;

	public:
		// [convert] convert from number
		static xanadu::string number(char _Value, int _Base = 10) noexcept;

		// [convert] convert from number
		static xanadu::string number(unsigned char _Value, int _Base = 10) noexcept;

		// [convert] convert from number
		static xanadu::string number(short _Value, int _Base = 10) noexcept;

		// [convert] convert from number
		static xanadu::string number(unsigned short _Value, int _Base = 10) noexcept;

		// [convert] convert from number
		static xanadu::string number(int _Value, int _Base = 10) noexcept;

		// [convert] convert from number
		static xanadu::string number(unsigned int _Value, int _Base = 10) noexcept;

		// [convert] convert from number
		static xanadu::string number(long _Value, int _Base = 10) noexcept;

		// [convert] convert from number
		static xanadu::string number(unsigned long _Value, int _Base = 10) noexcept;

		// [convert] convert from number
		static xanadu::string number(long long _Value, int _Base = 10) noexcept;

		// [convert] convert from number
		static xanadu::string number(unsigned long long _Value, int _Base = 10) noexcept;

		// [convert] convert from number
		static xanadu::string number(float _Value, char _Format = 'g', int _Prec = 6) noexcept;

		// [convert] convert from number
		static xanadu::string number(double _Value, char _Format = 'g', int _Prec = 6) noexcept;
	};
}



// Standard enhancement function : stream <<
_XCOREAPI_ std::ostream& operator << (std::ostream& _OStream, const xanadu::string& _String) noexcept;

// Standard enhancement function : stream >>
_XCOREAPI_ std::istream& operator >> (std::istream& _IStream, xanadu::string& _String) noexcept;

// Standard enhancement function : getline
_XCOREAPI_ std::istream& getline(std::istream& _IStream, xanadu::string& _String, char _Delim) noexcept;

// Standard enhancement function : getline
_XCOREAPI_ std::istream& getline(std::istream& _IStream, xanadu::string& _String) noexcept;



#endif
