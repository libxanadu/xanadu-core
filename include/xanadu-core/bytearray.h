#ifndef			_XANADU_CORE_BYTEARRAY_H_
#define			_XANADU_CORE_BYTEARRAY_H_

#include <xanadu-core/allocator.h>


/// namespace xanadu
namespace x
{
	/// class bytearray
	class _XCOREAPI_ bytearray
	{
	public:
		using				elem_type = x::allocator::elem_type;
		using				raw_type = x::allocator::raw_type;
		using				size_type = x::size_type;
		using				pos_type = x::pos_type;

	public:
		static const pos_type		npos = x::allocator::npos;

	private:
		allocator			_Allocator;

	public:
		// constructor
		bytearray() noexcept;

		// constructor
		bytearray(size_type _Length, elem_type _Char) noexcept;

		// constructor
		bytearray(const elem_type* _Memory) noexcept; // NOLINT(google-explicit-constructor)

		// constructor
		bytearray(const elem_type* _Memory, size_type _Length) noexcept;

		// constructor
		bytearray(const raw_type* _Memory, size_type _Length) noexcept;

		// constructor
		bytearray(const x::bytearray& _String) noexcept;

		// constructor
		bytearray(x::bytearray&& _String) noexcept;

		// destructor
		virtual ~bytearray() noexcept;

	public:
		// operator overload =
		bytearray& operator = (const elem_type* _Memory) noexcept;

		// operator overload =
		bytearray& operator = (const x::bytearray& _String) noexcept;

		// operator overload =
		bytearray& operator = (x::bytearray&& _String) noexcept;

	public:
		// operator overload +=
		bytearray& operator += (elem_type _Char) noexcept;

		// operator overload +=
		bytearray& operator += (const elem_type* _String) noexcept;

		// operator overload +=
		bytearray& operator += (const x::bytearray& _String) noexcept;

	public:
		// operator overload +
		bytearray operator + (elem_type _Char) const noexcept;

		// operator overload +
		bytearray operator + (const elem_type* _String) const noexcept;

		// operator overload +
		bytearray operator + (const x::bytearray& _String) const noexcept;

	public:
		// operator overload ==
		bool operator == (elem_type _Char) const noexcept;

		// operator overload ==
		bool operator == (const elem_type* _String) const noexcept;

		// operator overload ==
		bool operator == (const x::bytearray& _String) const noexcept;

		// operator overload !=
		bool operator != (elem_type _Char) const noexcept;

		// operator overload !=
		bool operator != (const elem_type* _String) const noexcept;

		// operator overload !=
		bool operator != (const x::bytearray& _String) const noexcept;

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
		virtual x::bytearray substr(pos_type _Pos) const noexcept final;

		// 从源中截取部分数据
		virtual x::bytearray substr(pos_type _Pos, size_type _Length) const noexcept final;

		// 从源中截取部分数据
		virtual x::bytearray left(pos_type _Pos) const noexcept final;

		// 从源中截取部分数据
		virtual x::bytearray right(pos_type _Pos) const noexcept final;

	public:
		// [mid] 从源中截取部分数据
		virtual x::bytearray mid(pos_type _Pos) const noexcept final;

		// [mid] 从源中截取部分数据
		virtual x::bytearray mid(pos_type _Pos, size_type _Size) const noexcept final;

		// [mid] 从源中截取部分数据
		virtual x::bytearray mid(const elem_type* _Left, const elem_type* _Right) const noexcept final;

		// [mid] 从源中截取部分数据
		virtual x::bytearray mid(const elem_type* _Left, size_type _LengthL, const elem_type* _Right) const noexcept final;

		// [mid] 从源中截取部分数据
		virtual x::bytearray mid(const elem_type* _Left, const elem_type* _Right, size_type _LengthR) const noexcept final;

		// [mid] 从源中截取部分数据
		virtual x::bytearray mid(const elem_type* _Left, size_type _LengthL, const elem_type* _Right, size_type _LengthR) const noexcept final;

		// [mid] 从源中截取部分数据
		virtual x::bytearray mid(const raw_type* _Left, size_type _LengthL, const void* _Right, size_type _LengthR) const noexcept final;

		// [mid] 从源中截取部分数据
		virtual x::bytearray mid(const elem_type* _Left, const x::bytearray& _Right) const noexcept final;

		// [mid] 从源中截取部分数据
		virtual x::bytearray mid(const x::bytearray& _Left, const elem_type* _Right) const noexcept final;

		// [mid] 从源中截取部分数据
		virtual x::bytearray mid(const x::bytearray& _Left, const x::bytearray& _Right) const noexcept final;

	public:
		// 检测源数据是否存在指定的前缀
		virtual bool startsWith(elem_type _Char) const noexcept final;

		// 检测源数据是否存在指定的前缀
		virtual bool startsWith(const elem_type* _Memory) const noexcept final;

		// 检测源数据是否存在指定的前缀
		virtual bool startsWith(const elem_type* _Memory, size_type _Length) const noexcept final;

		// 检测源数据是否存在指定的前缀
		virtual bool startsWith(const raw_type* _Memory, size_type _Length) const noexcept final;

		// 检测源数据是否存在指定的前缀
		virtual bool startsWith(const x::bytearray& _String) const noexcept final;

	public:
		// 检测源数据是否存在指定的后缀
		virtual bool endsWith(elem_type _Char) const noexcept final;

		// 检测源数据是否存在指定的后缀
		virtual bool endsWith(const elem_type* _Memory) const noexcept final;

		// 检测源数据是否存在指定的后缀
		virtual bool endsWith(const elem_type* _Memory, size_type _Length) const noexcept final;

		// 检测源数据是否存在指定的后缀
		virtual bool endsWith(const raw_type* _Memory, size_type _Length) const noexcept final;

		// 检测源数据是否存在指定的后缀
		virtual bool endsWith(const x::bytearray& _String) const noexcept final;

	public:
		// 从指定位置按正序查找数据
		virtual pos_type find(elem_type _Char) const noexcept final;

		// 从指定位置按正序查找数据
		virtual pos_type find(elem_type _Char, pos_type _Pos) const noexcept final;

		// 从指定位置按正序查找数据
		virtual pos_type find(const elem_type* _String) const noexcept final;

		// 从指定位置按正序查找数据
		virtual pos_type find(const elem_type* _String, pos_type _Pos) const noexcept final;

		// 从指定位置按正序查找数据
		virtual pos_type find(const elem_type* _String, size_type _Length, pos_type _Pos) const noexcept final;

		// 从指定位置按正序查找数据
		virtual pos_type find(const raw_type* _Memory, size_type _Length, pos_type _Pos) const noexcept final;

		// 从指定位置按正序查找数据
		virtual pos_type find(const x::bytearray& _String) const noexcept final;

		// 从指定位置按正序查找数据
		virtual pos_type find(const x::bytearray& _String, pos_type _Pos) const noexcept final;

	public:
		// 从指定位置按倒序查找数据
		virtual pos_type rfind(elem_type _Char) const noexcept final;

		// 从指定位置按倒序查找数据
		virtual pos_type rfind(elem_type _Char, pos_type _Pos) const noexcept final;

		// 从指定位置按倒序查找数据
		virtual pos_type rfind(const elem_type* _String) const noexcept final;

		// 从指定位置按倒序查找数据
		virtual pos_type rfind(const elem_type* _String, pos_type _Pos) const noexcept final;

		// 从指定位置按倒序查找数据
		virtual pos_type rfind(const elem_type* _String, size_type _Length, pos_type _Pos) const noexcept final;

		// 从指定位置按倒序查找数据
		virtual pos_type rfind(const raw_type* _Memory, size_type _Length, pos_type _Pos) const noexcept final;

		// 从指定位置按倒序查找数据
		virtual pos_type rfind(const x::bytearray& _String) const noexcept final;

		// 从指定位置按倒序查找数据
		virtual pos_type rfind(const x::bytearray& _String, pos_type _Pos) const noexcept final;

	public:
		// 检查是否包含指定数据
		virtual bool contains(elem_type _Char) const noexcept final;

		// 检查是否包含指定数据
		virtual bool contains(const elem_type* _String) const noexcept final;

		// 检查是否包含指定数据
		virtual bool contains(const elem_type* _String, size_type _Length) const noexcept final;

		// 检查是否包含指定数据
		virtual bool contains(const raw_type* _Memory, size_type _Length) const noexcept final;

		// 检查是否包含指定数据
		virtual bool contains(const x::bytearray& _String) const noexcept final;

	public:
		// 检查是否与指定数据相同
		virtual int compare(elem_type _Char) const noexcept final;

		// 检查是否与指定数据相同
		virtual int compare(const elem_type* _String) const noexcept final;

		// 检查是否与指定数据相同
		virtual int compare(const elem_type* _String, size_type _Length) const noexcept final;

		// 检查是否与指定数据相同
		virtual int compare(const raw_type* _Memory, size_type _Length) const noexcept final;

		// 检查是否与指定数据相同
		virtual int compare(const x::bytearray& _String) const noexcept final;

	public:
		// 在头部插入数据
		virtual x::bytearray& prepend(elem_type _Char) noexcept final;

		// 在头部插入数据
		virtual x::bytearray& prepend(const elem_type* _String) noexcept final;

		// 在头部插入数据
		virtual x::bytearray& prepend(const elem_type* _String, size_type _Size) noexcept final;

		// 在头部插入数据
		virtual x::bytearray& prepend(const raw_type* _Memory, size_type _Size) noexcept final;

		// 在头部插入数据
		virtual x::bytearray& prepend(const x::bytearray& _String) noexcept final;

	public:
		// 在尾部添加数据
		virtual x::bytearray& append(elem_type _Char) noexcept final;

		// 在尾部添加数据
		virtual x::bytearray& append(const elem_type* _String) noexcept final;

		// 在尾部添加数据
		virtual x::bytearray& append(const elem_type* _String, size_type _Size) noexcept final;

		// 在尾部添加数据
		virtual x::bytearray& append(const raw_type* _Memory, size_type _Size) noexcept final;

		// 在尾部添加数据
		virtual x::bytearray& append(const x::bytearray& _String) noexcept final;

	public:
		// 在指定下标处插入数据
		virtual x::bytearray& insert(pos_type _Pos, elem_type _Char) noexcept final;

		// 在指定下标处插入数据
		virtual x::bytearray& insert(pos_type _Pos, size_type _Count, elem_type _Char) noexcept final;

		// 在指定下标处插入数据
		virtual x::bytearray& insert(pos_type _Pos, const elem_type* _String) noexcept final;

		// 在指定下标处插入数据
		virtual x::bytearray& insert(pos_type _Pos, const elem_type* _String, size_type _Length) noexcept final;

		// 在指定下标处插入数据
		virtual x::bytearray& insert(pos_type _Pos, const raw_type* _Memory, size_type _Length) noexcept final;

		// 在指定下标处插入数据
		virtual x::bytearray& insert(pos_type _Pos, const x::bytearray& _String) noexcept final;

	public:
		// 移除下标 pos 处的 length 长度数据
		virtual x::bytearray& remove(pos_type _Pos, size_type _Length) noexcept final;

		// 删除与参数相同的数据
		virtual x::bytearray& remove(elem_type _Char) noexcept final;

		// 删除与参数相同的数据
		virtual x::bytearray& remove(const elem_type* _String) noexcept final;

		// 删除与参数相同的数据
		virtual x::bytearray& remove(const elem_type* _String, size_type _Length) noexcept final;

		// 删除与参数相同的数据
		virtual x::bytearray& remove(const raw_type* _Memory, size_type _Length) noexcept final;

		// 删除与参数相同的数据
		virtual x::bytearray& remove(const x::bytearray& _String) noexcept final;

	public:
		// 替换数据
		virtual x::bytearray& replace(pos_type _Pos, size_type _Length, elem_type _After) noexcept final;

		// 替换数据
		virtual x::bytearray& replace(pos_type _Pos, size_type _Length, const elem_type* _After) noexcept final;

		// 替换数据
		virtual x::bytearray& replace(pos_type _Pos, size_type _Length, const elem_type* _After, size_type _LengthA) noexcept final;

		// 替换数据
		virtual x::bytearray& replace(pos_type _Pos, size_type _Length, const raw_type* _After, size_type _LengthA) noexcept final;

		// 替换数据
		virtual x::bytearray& replace(pos_type _Pos, size_type _Length, const x::bytearray& _After) noexcept final;

	public:
		// 替换数据
		virtual x::bytearray& replace(elem_type _Before, elem_type _After) noexcept final;

		// 替换数据
		virtual x::bytearray& replace(elem_type _Before, const elem_type* _After) noexcept final;

		// 替换数据
		virtual x::bytearray& replace(elem_type _Before, const elem_type* _After, size_type _LengthA) noexcept final;

		// 替换数据
		virtual x::bytearray& replace(elem_type _Before, const raw_type* _After, size_type _LengthA) noexcept final;

		// 替换数据
		virtual x::bytearray& replace(elem_type _Before, const x::bytearray& _After) noexcept final;

	public:
		// 替换数据
		virtual x::bytearray& replace(const elem_type* _Before, elem_type _After) noexcept final;

		// 替换数据
		virtual x::bytearray& replace(const elem_type* _Before, const elem_type* _After) noexcept final;

		// 替换数据
		virtual x::bytearray& replace(const elem_type* _Before, const elem_type* _After, size_type _LengthA) noexcept final;

		// 替换数据
		virtual x::bytearray& replace(const elem_type* _Before, const raw_type* _After, size_type _LengthA) noexcept final;

		// 替换数据
		virtual x::bytearray& replace(const elem_type* _Before, const x::bytearray& _After) noexcept final;

	public:
		// 替换数据
		virtual x::bytearray& replace(const elem_type* _Before, size_type _LengthB, elem_type _After) noexcept final;

		// 替换数据
		virtual x::bytearray& replace(const elem_type* _Before, size_type _LengthB, const elem_type* _After) noexcept final;

		// 替换数据
		virtual x::bytearray& replace(const elem_type* _Before, size_type _LengthB, const elem_type* _After, size_type _LengthA) noexcept final;

		// 替换数据
		virtual x::bytearray& replace(const elem_type* _Before, size_type _LengthB, const raw_type* _After, size_type _LengthA) noexcept final;

		// 替换数据
		virtual x::bytearray& replace(const elem_type* _Before, size_type _LengthB, const x::bytearray& _After) noexcept final;

	public:
		// 替换数据
		virtual x::bytearray& replace(const raw_type* _Before, size_type _LengthB, elem_type _After) noexcept final;

		// 替换数据
		virtual x::bytearray& replace(const raw_type* _Before, size_type _LengthB, const elem_type* _After) noexcept final;

		// 替换数据
		virtual x::bytearray& replace(const raw_type* _Before, size_type _LengthB, const elem_type* _After, size_type _LengthA) noexcept final;

		// 替换数据
		virtual x::bytearray& replace(const raw_type* _Before, size_type _LengthB, const raw_type* _After, size_type _LengthA) noexcept final;

		// 替换数据
		virtual x::bytearray& replace(const raw_type* _Before, size_type _LengthB, const x::bytearray& _After) noexcept final;

	public:
		// 替换数据
		virtual x::bytearray& replace(const x::bytearray& _Before, elem_type _After) noexcept final;

		// 替换数据
		virtual x::bytearray& replace(const x::bytearray& _Before, const elem_type* _After) noexcept final;

		// 替换数据
		virtual x::bytearray& replace(const x::bytearray& _Before, const elem_type* _After, size_type _LengthA) noexcept final;

		// 替换数据
		virtual x::bytearray& replace(const x::bytearray& _Before, const raw_type* _After, size_type _LengthA) noexcept final;

		// 替换数据
		virtual x::bytearray& replace(const x::bytearray& _Before, const x::bytearray& _After) noexcept final;

	public:
		// 按指定数据拆分字符串
		virtual std::list<x::bytearray> split(elem_type _Char) const noexcept final;

		// 按指定数据拆分字符串
		virtual std::list<x::bytearray> split(const elem_type* _Memory) const noexcept final;

		// 按指定数据拆分字符串
		virtual std::list<x::bytearray> split(const elem_type* _Memory, size_type _Size) const noexcept final;

		// 按指定数据拆分字符串
		virtual std::list<x::bytearray> split(const raw_type* _Memory, size_type _Size) const noexcept final;

		// 按指定数据拆分字符串
		virtual std::list<x::bytearray> split(const x::bytearray& _String) const noexcept final;

	public:
		// 判断一个字符是否为空白字符
		static bool isSpace(elem_type _Char) noexcept;

		// 格式化字符串 (char* [%s]) (wchar_t* [%ls])
		static x::bytearray format(const char* _Format, ...) noexcept;

	public:
		// [conv] 转换至大写
		x::bytearray toUpper() const noexcept;

		// [conv] 转换至小写
		x::bytearray toLower() const noexcept;

	public:
		// [conv] 转换至HEX
		virtual x::bytearray toHex() const noexcept final;

		// [conv] 从HEX转换
		static x::bytearray fromHex(const elem_type* _Hex) noexcept;

		// [conv] 从HEX转换
		static x::bytearray fromHex(const elem_type* _Hex, size_type _Size) noexcept;

		// [conv] 从HEX转换
		static x::bytearray fromHex(const raw_type* _Hex, size_type _Size) noexcept;

		// [conv] 从HEX转换
		static x::bytearray fromHex(const x::bytearray& _Hex) noexcept;

	public:
		// [conv] 转换至Base64
		virtual x::bytearray toBase64() const noexcept final;

		// [conv] 从Base64转换
		static x::bytearray fromBase64(const elem_type* _Base64) noexcept;

		// [conv] 从Base64转换
		static x::bytearray fromBase64(const elem_type* _Base64, size_type _Size) noexcept;

		// [conv] 从Base64转换
		static x::bytearray fromBase64(const raw_type* _Base64, size_type _Size) noexcept;

		// [conv] 从Base64转换
		static x::bytearray fromBase64(const x::bytearray& _Base64) noexcept;
	};
}



// Standard enhancement function : stream <<
_XCOREAPI_ std::ostream& operator << (std::ostream& _OStream, const x::bytearray& _String) noexcept;

// Standard enhancement function : stream >>
_XCOREAPI_ std::istream& operator >> (std::istream& _IStream, x::bytearray& _String) noexcept;

// Standard enhancement function : getline
_XCOREAPI_ std::istream& getline(std::istream& _IStream, x::bytearray& _String, char _Delim) noexcept;

// Standard enhancement function : getline
_XCOREAPI_ std::istream& getline(std::istream& _IStream, x::bytearray& _String) noexcept;



#endif
