#ifndef			_XANADU_CORE_STRING_H_
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
		using _Elem			= char;
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
		string(size_type _Length, _Elem _Char) noexcept;

		// constructor
		string(const _Elem* _Memory) noexcept; // NOLINT(google-explicit-constructor)

		// constructor
		string(const _Elem* _Memory, size_type _Length) noexcept;

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
		string& operator = (const _Elem* _Memory) noexcept;

		// operator overload =
		string& operator = (const std::string& _String) noexcept;

		// operator overload =
		string& operator = (const xanadu::string& _String) noexcept;

		// operator overload =
		string& operator = (xanadu::string&& _String) noexcept;

	public:
		// operator overload +=
		string& operator += (_Elem _Char) noexcept;

		// operator overload +=
		string& operator += (const _Elem* _String) noexcept;

		// operator overload +=
		string& operator += (const std::string& _String) noexcept;

		// operator overload +=
		string& operator += (const xanadu::string& _String) noexcept;

	public:
		// operator overload +
		string operator + (_Elem _Char) const noexcept;

		// operator overload +
		string operator + (const _Elem* _String) const noexcept;

		// operator overload +
		string operator + (const std::string& _String) const noexcept;

		// operator overload +
		string operator + (const xanadu::string& _String) const noexcept;

	public:
		// operator overload ==
		bool operator == (_Elem _Char) const noexcept;

		// operator overload ==
		bool operator == (const _Elem* _String) const noexcept;

		// operator overload ==
		bool operator == (const xanadu::string& _String) const noexcept;

		// operator overload !=
		bool operator != (_Elem _Char) const noexcept;

		// operator overload !=
		bool operator != (const _Elem* _String) const noexcept;

		// operator overload !=
		bool operator != (const xanadu::string& _String) const noexcept;

		// operator overload <
		bool operator < (_Elem _Char) const noexcept;

		// operator overload <
		bool operator < (const _Elem* _String) const noexcept;

		// operator overload <
		bool operator < (const xanadu::string& _String) const noexcept;

		// operator overload >
		bool operator > (_Elem _Char) const noexcept;

		// operator overload >
		bool operator > (const _Elem* _String) const noexcept;

		// operator overload >
		bool operator > (const xanadu::string& _String) const noexcept;

		// operator overload <=
		bool operator <= (_Elem _Char) const noexcept;

		// operator overload <=
		bool operator <= (const _Elem* _String) const noexcept;

		// operator overload <=
		bool operator <= (const xanadu::string& _String) const noexcept;

		// operator overload >=
		bool operator >= (_Elem _Char) const noexcept;

		// operator overload >=
		bool operator >= (const _Elem* _String) const noexcept;

		// operator overload >=
		bool operator >= (const xanadu::string& _String) const noexcept;

	public:
		// [opt] operator overload []
		_Elem& operator [] (pos_type _Index);

		// [opt] operator overload []
		_Elem operator [] (pos_type _Index) const;

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
		virtual _Elem* data() noexcept final;

		// [get] data
		virtual const _Elem* data() const noexcept final;

		// [get] size
		virtual size_type size() const noexcept final;

		// [get] capacity
		virtual size_type capacity() const noexcept final;

		// [get] surplus
		virtual size_type surplus() const noexcept final;

		// [get] max_size
		virtual size_type max_size() const noexcept final;

	public:
		// Extracting substrings from strings
		virtual xanadu::string substr(pos_type _Pos) const noexcept final;

		// Extracting substrings from strings
		virtual xanadu::string substr(pos_type _Pos, size_type _Length) const noexcept final;

		// Gets the substring to the left of the source string
		virtual xanadu::string left(pos_type _Pos) const noexcept final;

		// Gets the substring to the right of the source string
		virtual xanadu::string right(pos_type _Pos) const noexcept final;

	public:
		// [mid] Gets the substring in the middle of the source string
		virtual xanadu::string mid(pos_type _Pos) const noexcept final;

		// [mid] Gets the substring in the middle of the source string
		virtual xanadu::string mid(pos_type _Pos, size_type _Size) const noexcept final;

		// [mid] Gets the substring in the middle of the source string
		virtual xanadu::string mid(const _Elem* _Left, const _Elem* _Right) const noexcept final;

		// [mid] Gets the substring in the middle of the source string
		virtual xanadu::string mid(const _Elem* _Left, const _Elem* _Right, xanadu::CaseSensitivity _XCS) const noexcept final;

		// [mid] Gets the substring in the middle of the source string
		virtual xanadu::string mid(const _Elem* _Left, size_type _LengthL, const _Elem* _Right, size_type _LengthR) const noexcept final;

		// [mid] Gets the substring in the middle of the source string
		virtual xanadu::string mid(const _Elem* _Left, size_type _LengthL, const _Elem* _Right, size_type _LengthR, xanadu::CaseSensitivity _XCS) const noexcept final;

		// [mid] Gets the substring in the middle of the source string
		virtual xanadu::string mid(const _Elem* _Left, const xanadu::string& _Right) const noexcept final;

		// [mid] Gets the substring in the middle of the source string
		virtual xanadu::string mid(const _Elem* _Left, const xanadu::string& _Right, xanadu::CaseSensitivity _XCS) const noexcept final;

		// [mid] Gets the substring in the middle of the source string
		virtual xanadu::string mid(const xanadu::string& _Left, const _Elem* _Right) const noexcept final;

		// [mid] Gets the substring in the middle of the source string
		virtual xanadu::string mid(const xanadu::string& _Left, const _Elem* _Right, xanadu::CaseSensitivity _XCS) const noexcept final;

		// [mid] Gets the substring in the middle of the source string
		virtual xanadu::string mid(const xanadu::string& _Left, const xanadu::string& _Right) const noexcept final;

		// [mid] Gets the substring in the middle of the source string
		virtual xanadu::string mid(const xanadu::string& _Left, const xanadu::string& _Right, xanadu::CaseSensitivity _XCS) const noexcept final;

	public:
		// Detects whether the string starts with the specified prefix
		virtual bool startsWith(_Elem _Char) const noexcept final;

		// Detects whether the string starts with the specified prefix
		virtual bool startsWith(_Elem _Char, xanadu::CaseSensitivity _XCS) const noexcept final;

		// Detects whether the string starts with the specified prefix
		virtual bool startsWith(const _Elem* _Memory) const noexcept final;

		// Detects whether the string starts with the specified prefix
		virtual bool startsWith(const _Elem* _Memory, xanadu::CaseSensitivity _XCS) const noexcept final;

		// Detects whether the string starts with the specified prefix
		virtual bool startsWith(const _Elem* _Memory, size_type _Length) const noexcept final;

		// Detects whether the string starts with the specified prefix
		virtual bool startsWith(const _Elem* _Memory, size_type _Length, xanadu::CaseSensitivity _XCS) const noexcept final;

		// Detects whether the string starts with the specified prefix
		virtual bool startsWith(const xanadu::string& _String) const noexcept final;

		// Detects whether the string starts with the specified prefix
		virtual bool startsWith(const xanadu::string& _String, xanadu::CaseSensitivity _XCS) const noexcept final;

	public:
		// Detects whether the string ends with the specified suffix
		virtual bool endsWith(_Elem _Char) const noexcept final;

		// Detects whether the string ends with the specified suffix
		virtual bool endsWith(_Elem _Char, xanadu::CaseSensitivity _XCS) const noexcept final;

		// Detects whether the string ends with the specified suffix
		virtual bool endsWith(const _Elem* _Memory) const noexcept final;

		// Detects whether the string ends with the specified suffix
		virtual bool endsWith(const _Elem* _Memory, xanadu::CaseSensitivity) const noexcept final;

		// Detects whether the string ends with the specified suffix
		virtual bool endsWith(const _Elem* _Memory, size_type _Length) const noexcept final;

		// Detects whether the string ends with the specified suffix
		virtual bool endsWith(const _Elem* _Memory, size_type _Length, xanadu::CaseSensitivity) const noexcept final;

		// Detects whether the string ends with the specified suffix
		virtual bool endsWith(const xanadu::string& _String) const noexcept final;

		// Detects whether the string ends with the specified suffix
		virtual bool endsWith(const xanadu::string& _String, xanadu::CaseSensitivity _XCS) const noexcept final;
		
	public:
		// Find in positive order from the specified location
		virtual pos_type find(_Elem _Char) const noexcept final;

		// Find in positive order from the specified location
		virtual pos_type find(_Elem _Char, xanadu::CaseSensitivity _XCS) const noexcept final;

		// Find in positive order from the specified location
		virtual pos_type find(_Elem _Char, pos_type _Pos) const noexcept final;

		// Find in positive order from the specified location
		virtual pos_type find(_Elem _Char, pos_type _Pos, xanadu::CaseSensitivity _XCS) const noexcept final;

		// Find in positive order from the specified location
		virtual pos_type find(const _Elem* _String) const noexcept final;

		// Find in positive order from the specified location
		virtual pos_type find(const _Elem* _String, xanadu::CaseSensitivity _XCS) const noexcept final;

		// Find in positive order from the specified location
		virtual pos_type find(const _Elem* _String, pos_type _Pos) const noexcept final;

		// Find in positive order from the specified location
		virtual pos_type find(const _Elem* _String, pos_type _Pos, xanadu::CaseSensitivity _XCS) const noexcept final;

		// Find in positive order from the specified location
		virtual pos_type find(const _Elem* _String, size_type _Length, pos_type _Pos) const noexcept final;

		// Find in positive order from the specified location
		virtual pos_type find(const _Elem* _String, size_type _Length, pos_type _Pos, xanadu::CaseSensitivity _XCS) const noexcept final;

		// Find in positive order from the specified location
		virtual pos_type find(const xanadu::string& _String) const noexcept final;

		// Find in positive order from the specified location
		virtual pos_type find(const xanadu::string& _String, xanadu::CaseSensitivity _XCS) const noexcept final;

		// Find in positive order from the specified location
		virtual pos_type find(const xanadu::string& _String, pos_type _Pos) const noexcept final;

		// Find in positive order from the specified location
		virtual pos_type find(const xanadu::string& _String, pos_type _Pos, xanadu::CaseSensitivity _XCS) const noexcept final;

	public:
		// Search in reverse order from the specified location
		virtual pos_type rfind(_Elem _Char) const noexcept final;

		// Search in reverse order from the specified location
		virtual pos_type rfind(_Elem _Char, xanadu::CaseSensitivity _XCS) const noexcept final;

		// Search in reverse order from the specified location
		virtual pos_type rfind(_Elem _Char, pos_type _Pos) const noexcept final;

		// Search in reverse order from the specified location
		virtual pos_type rfind(_Elem _Char, pos_type _Pos, xanadu::CaseSensitivity _XCS) const noexcept final;

		// Search in reverse order from the specified location
		virtual pos_type rfind(const _Elem* _String) const noexcept final;

		// Search in reverse order from the specified location
		virtual pos_type rfind(const _Elem* _String, xanadu::CaseSensitivity _XCS) const noexcept final;

		// Search in reverse order from the specified location
		virtual pos_type rfind(const _Elem* _String, pos_type _Pos) const noexcept final;

		// Search in reverse order from the specified location
		virtual pos_type rfind(const _Elem* _String, pos_type _Pos, xanadu::CaseSensitivity _XCS) const noexcept final;

		// Search in reverse order from the specified location
		virtual pos_type rfind(const _Elem* _String, size_type _Length, pos_type _Pos) const noexcept final;

		// Search in reverse order from the specified location
		virtual pos_type rfind(const _Elem* _String, size_type _Length, pos_type _Pos, xanadu::CaseSensitivity _XCS) const noexcept final;

		// Search in reverse order from the specified location
		virtual pos_type rfind(const xanadu::string& _String) const noexcept final;

		// Search in reverse order from the specified location
		virtual pos_type rfind(const xanadu::string& _String, xanadu::CaseSensitivity _XCS) const noexcept final;

		// Search in reverse order from the specified location
		virtual pos_type rfind(const xanadu::string& _String, pos_type _Pos) const noexcept final;

		// Search in reverse order from the specified location
		virtual pos_type rfind(const xanadu::string& _String, pos_type _Pos, xanadu::CaseSensitivity _XCS) const noexcept final;

	public:
		// Check whether the specified content is included
		virtual bool contains(_Elem _Char) const noexcept final;

		// Check whether the specified content is included
		virtual bool contains(_Elem _Char, xanadu::CaseSensitivity _XCS) const noexcept final;

		// Check whether the specified content is included
		virtual bool contains(const _Elem* _String) const noexcept final;

		// Check whether the specified content is included
		virtual bool contains(const _Elem* _String, xanadu::CaseSensitivity _XCS) const noexcept final;

		// Check whether the specified content is included
		virtual bool contains(const _Elem* _String, size_type _Length) const noexcept final;

		// Check whether the specified content is included
		virtual bool contains(const _Elem* _String, size_type _Length, xanadu::CaseSensitivity _XCS) const noexcept final;

		// Check whether the specified content is included
		virtual bool contains(const xanadu::string& _String) const noexcept final;

		// Check whether the specified content is included
		virtual bool contains(const xanadu::string& _String, xanadu::CaseSensitivity _XCS) const noexcept final;

	public:
		// Check that they are the same
		virtual int compare(_Elem _Char) const noexcept final;

		// Check that they are the same
		virtual int compare(_Elem _Char, xanadu::CaseSensitivity _XCS) const noexcept final;

		// Check that they are the same
		virtual int compare(const _Elem* _String) const noexcept final;

		// Check that they are the same
		virtual int compare(const _Elem* _String, xanadu::CaseSensitivity _XCS) const noexcept final;

		// Check that they are the same
		virtual int compare(const _Elem* _String, size_type _Length) const noexcept final;

		// Check that they are the same
		virtual int compare(const _Elem* _String, size_type _Length, xanadu::CaseSensitivity _XCS) const noexcept final;

		// Check that they are the same
		virtual int compare(const xanadu::string& _String) const noexcept final;

		// Check that they are the same
		virtual int compare(const xanadu::string& _String, xanadu::CaseSensitivity _XCS) const noexcept final;

	public:
		// Add at the begin
		virtual xanadu::string& prepend(_Elem _Char) noexcept final;

		// Add at the begin
		virtual xanadu::string& prepend(const _Elem* _String) noexcept final;

		// Add at the begin
		virtual xanadu::string& prepend(const _Elem* _String, size_type _Size) noexcept final;

		// Add at the begin
		virtual xanadu::string& prepend(const xanadu::string& _String) noexcept final;

	public:
		// Add at the end
		virtual xanadu::string& append(_Elem _Char) noexcept final;

		// Add at the end
		virtual xanadu::string& append(const _Elem* _String) noexcept final;

		// Add at the end
		virtual xanadu::string& append(const _Elem* _String, size_type _Size) noexcept final;

		// Add at the end
		virtual xanadu::string& append(const xanadu::string& _String) noexcept final;

	public:
		// Inserts data from the specified location _Elem
		virtual xanadu::string& insert(pos_type _Pos, _Elem _Char) noexcept final;

		// Inserts data from the specified location _Elem
		virtual xanadu::string& insert(pos_type _Pos, size_type _Count, _Elem _Char) noexcept final;

		// Inserts data from the specified location const _Elem*
		virtual xanadu::string& insert(pos_type _Pos, const _Elem* _String) noexcept final;

		// Inserts data from the specified location const _Elem*
		virtual xanadu::string& insert(pos_type _Pos, const _Elem* _String, size_type _Length) noexcept final;

		// Inserts data from the specified location xanadu::string
		virtual xanadu::string& insert(pos_type _Pos, const xanadu::string& _String) noexcept final;

	public:
		// Removes the specified length of data from the specified location
		virtual xanadu::string& remove(pos_type _Pos, size_type _Length) noexcept final;

		// Delete the same data as the parameter
		virtual xanadu::string& remove(_Elem _Char) noexcept final;

		// Delete the same data as the parameter
		virtual xanadu::string& remove(_Elem _Char, xanadu::CaseSensitivity _XCS) noexcept final;

		// Delete the same data as the parameter
		virtual xanadu::string& remove(const _Elem* _String) noexcept final;

		// Delete the same data as the parameter
		virtual xanadu::string& remove(const _Elem* _String, xanadu::CaseSensitivity _XCS) noexcept final;

		// Delete the same data as the parameter
		virtual xanadu::string& remove(const _Elem* _String, size_type _Length) noexcept final;

		// Delete the same data as the parameter
		virtual xanadu::string& remove(const _Elem* _String, size_type _Length, xanadu::CaseSensitivity _XCS) noexcept final;

		// Delete the same data as the parameter
		virtual xanadu::string& remove(const xanadu::string& _String) noexcept final;

		// Delete the same data as the parameter
		virtual xanadu::string& remove(const xanadu::string& _String, xanadu::CaseSensitivity _XCS) noexcept final;

	public:
		// Replace the specified data
		virtual xanadu::string& replace(pos_type _Pos, size_type _Length, _Elem _After) noexcept final;

		// Replace the specified data
		virtual xanadu::string& replace(pos_type _Pos, size_type _Length, const _Elem* _After) noexcept final;

		// Replace the specified data
		virtual xanadu::string& replace(pos_type _Pos, size_type _Length, const _Elem* _After, size_type _LengthA) noexcept final;

		// Replace the specified data
		virtual xanadu::string& replace(pos_type _Pos, size_type _Length, const xanadu::string& _After) noexcept final;

	public:
		// Replace the specified data
		virtual xanadu::string& replace(_Elem _Before, _Elem _After) noexcept final;

		// Replace the specified data
		virtual xanadu::string& replace(_Elem _Before, _Elem _After, xanadu::CaseSensitivity _XCS) noexcept final;

		// Replace the specified data
		virtual xanadu::string& replace(_Elem _Before, const _Elem* _After, size_type _LengthA) noexcept final;

		// Replace the specified data
		virtual xanadu::string& replace(_Elem _Before, const _Elem* _After, size_type _LengthA, xanadu::CaseSensitivity _XCS) noexcept final;

		// Replace the specified data
		virtual xanadu::string& replace(_Elem _Before, const xanadu::string& _After) noexcept final;

		// Replace the specified data
		virtual xanadu::string& replace(_Elem _Before, const xanadu::string& _After, xanadu::CaseSensitivity _XCS) noexcept final;

	public:
		// Replace the specified data
		virtual xanadu::string& replace(const _Elem* _Before, _Elem _After) noexcept final;

		// Replace the specified data
		virtual xanadu::string& replace(const _Elem* _Before, _Elem _After, xanadu::CaseSensitivity _XCS) noexcept final;

		// Replace the specified data
		virtual xanadu::string& replace(const _Elem* _Before, const _Elem* _After, size_type _LengthA) noexcept final;

		// Replace the specified data
		virtual xanadu::string& replace(const _Elem* _Before, const _Elem* _After, size_type _LengthA, xanadu::CaseSensitivity _XCS) noexcept final;

		// Replace the specified data
		virtual xanadu::string& replace(const _Elem* _Before, const xanadu::string& _After) noexcept final;

		// Replace the specified data
		virtual xanadu::string& replace(const _Elem* _Before, const xanadu::string& _After, xanadu::CaseSensitivity _XCS) noexcept final;

	public:
		// Replace the specified data
		virtual xanadu::string& replace(const _Elem* _Before, size_type _LengthB, _Elem _After) noexcept final;

		// Replace the specified data
		virtual xanadu::string& replace(const _Elem* _Before, size_type _LengthB, _Elem _After, xanadu::CaseSensitivity _XCS) noexcept final;

		// Replace the specified data
		virtual xanadu::string& replace(const _Elem* _Before, size_type _LengthB, const _Elem* _After, size_type _LengthA) noexcept final;

		// Replace the specified data
		virtual xanadu::string& replace(const _Elem* _Before, size_type _LengthB, const _Elem* _After, size_type _LengthA, xanadu::CaseSensitivity _XCS) noexcept final;

		// Replace the specified data
		virtual xanadu::string& replace(const _Elem* _Before, size_type _LengthB, const xanadu::string& _After) noexcept final;

		// Replace the specified data
		virtual xanadu::string& replace(const _Elem* _Before, size_type _LengthB, const xanadu::string& _After, xanadu::CaseSensitivity _XCS) noexcept final;

	public:
		// Replace the specified data
		virtual xanadu::string& replace(const xanadu::string& _Before, _Elem _After) noexcept final;

		// Replace the specified data
		virtual xanadu::string& replace(const xanadu::string& _Before, _Elem _After, xanadu::CaseSensitivity _XCS) noexcept final;

		// Replace the specified data
		virtual xanadu::string& replace(const xanadu::string& _Before, const _Elem* _After, size_type _LengthA) noexcept final;

		// Replace the specified data
		virtual xanadu::string& replace(const xanadu::string& _Before, const _Elem* _After, size_type _LengthA, xanadu::CaseSensitivity _XCS) noexcept final;

		// Replace the specified data
		virtual xanadu::string& replace(const xanadu::string& _Before, const xanadu::string& _After) noexcept final;

		// Replace the specified data
		virtual xanadu::string& replace(const xanadu::string& _Before, const xanadu::string& _After, xanadu::CaseSensitivity _XCS) noexcept final;

	public:
		// 按指定数据拆分字符串
		virtual std::list<xanadu::string> split(_Elem _Char) const noexcept final;

		// 按指定数据拆分字符串
		virtual std::list<xanadu::string> split(const _Elem* _Memory) const noexcept final;

		// 按指定数据拆分字符串
		virtual std::list<xanadu::string> split(const _Elem* _Memory, size_type _Size) const noexcept final;

		// 按指定数据拆分字符串
		virtual std::list<xanadu::string> split(const xanadu::string& _String) const noexcept final;

	public:
		// 判断一个字符是否为空白字符
		static bool isSpace(_Elem _Char) noexcept;

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
		static xanadu::string fromHex(const _Elem* _String) noexcept;

		// [conv] 从HEX转换
		static xanadu::string fromHex(const _Elem* _String, size_type _Size) noexcept;

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
