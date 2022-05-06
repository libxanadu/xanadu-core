#ifndef			_XANADU_CORE_ERROR_H_
#define			_XANADU_CORE_ERROR_H_

#include <xanadu-core/header.h>


/// namespace xanadu
namespace xanadu
{
	/// class error
	class _XCOREAPI_ error
	{
	public:
		typedef enum value_type : xanadu::size_type
		{
			EE_SUCCESS				= 0x00000000,		// 成功

			EE_ACCESS_DENIED			= 0x00000100,		// 拒绝访问
			EE_INVALID_HANDLE			= 0x00000101,		// 无效句柄
			EE_INVALID_ARG				= 0x00000102,		// 无效参数

			EE_MEMORY_INSUFFICIENT			= 0x00000200,		// 内存不足
			EE_MEMORY_INVALID			= 0x00000201,		// 内存无效
			EE_MEMORY_TOO_SHORT			= 0x00000202,		// 内存太短
			EE_MEMORY_TOO_LONG			= 0x00000203,		// 内存太长

			EE_FILE_NOT_FOUND			= 0x00000300,		// 文件未找到
			EE_FILE_IS_EMPTY			= 0x00000301,		// 文件为空
			EE_FILE_TOO_SHORT			= 0x00000302,		// 文件太短
			EE_FILE_TOO_LONG			= 0x00000303,		// 文件太长
			EE_FILE_CANNOT_OPEN			= 0x00000303,		// 文件无法打开
			EE_FILE_CANNOT_READ			= 0x00000303,		// 文件无法读取
			EE_FILE_CANNOT_WRITE			= 0x00000303,		// 文件无法写入
			EE_FILE_CANNOT_CLOSE			= 0x00000303,		// 文件无法关闭

			EE_UNKNOWN_ERROR			= 0x0000FFFE,		// 未知错误
			EE_EXPAND_MARK				= 0x0000FFFF		// 错误扩展起始点
		}value_type;

	public:
		using				_Elem = char;

	private:
		value_type			_error_code;

	public:
		// constructors
		error() noexcept;

		// constructors
		error(value_type _Error) noexcept; // NOLINT(google-explicit-constructor)

		// constructor
		error(const error& _Error) noexcept;

		// constructor
		error(error&& _Error) noexcept;

		// destructor
		virtual ~error() noexcept;

	public:
		// operator overload =
		error& operator = (value_type _Error) noexcept;

		// operator overload =
		error& operator = (const error& _Error) noexcept;

		// operator overload =
		error& operator = (error&& _Error) noexcept;

	public:
		// operator overload ==
		bool operator == (value_type _Error) const noexcept;

		// operator overload ==
		bool operator == (const error& _Error) const noexcept;

	public:
		// operator overload !=
		bool operator != (value_type _Error) const noexcept;

		// operator overload !=
		bool operator != (const error& _Error) const noexcept;

	public:
		// operator overload bool
		explicit operator bool () const noexcept;

	public:
		// [get] success
		virtual bool success() const noexcept final;

		// [get] failure
		virtual bool failure() const noexcept final;

		// [get] explain
		virtual const _Elem* explain() const noexcept final;

	public:
		// 添加扩展数据
		static void add_expand(value_type _Code, const _Elem* _Explain) noexcept;
	};
}


#endif
