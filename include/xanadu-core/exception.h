#ifndef			_XANADU_CORE_EXCEPTION_H_
#define			_XANADU_CORE_EXCEPTION_H_

#include <xanadu-core/header.h>
#include <xanadu-core/string.h> // NOLINT(modernize-deprecated-headers)


/// namespace xanadu
namespace xanadu
{
	/// class exception
	class _XCOREAPI_ exception
	{
	public:
		using				elem_type = char;
		using				size_type = xanadu::size_type;

	private:
		elem_type*				_memory_address;

	public:
		// constructor
		exception() noexcept;

		// constructor
		exception(const elem_type* _Memory) noexcept; // NOLINT(google-explicit-constructor)

		// constructor
		exception(const elem_type* _Memory, size_type _Length) noexcept;

		// constructor
		exception(const std::string& _Exception) noexcept; // NOLINT(google-explicit-constructor)

		// constructor
		exception(const xanadu::string& _Exception) noexcept; // NOLINT(google-explicit-constructor)

		// constructor
		exception(const exception& _Exception) noexcept;

		// constructor
		exception(exception&& _Exception) noexcept;

		// destructor
		virtual ~exception() noexcept;

	public:
		// operator overload =
		exception& operator = (const elem_type* _Exception) noexcept;

		// operator overload =
		exception& operator = (const std::string& _Exception) noexcept;

		// operator overload =
		exception& operator = (const xanadu::string& _Exception) noexcept;

		// operator overload =
		exception& operator = (const exception& _Exception) noexcept;

		// operator overload =
		exception& operator = (exception&& _Exception) noexcept;

	private:
		// [opt] 拷贝字符串
		static elem_type* clone_string(const elem_type* _Memory, size_type _Length) noexcept;

	public:
		// [get] explain
		virtual const elem_type* explain() const noexcept final;

	public:
		// [std] range_error
		static std::range_error range_error() noexcept;

		// [std] range_error
		static std::range_error range_error(const char* _Message) noexcept;

		// [std] range_error
		static std::range_error range_error(const std::string& _Message) noexcept;

		// [std] range_error
		static std::range_error range_error(const xanadu::string& _Message) noexcept;
	};
}

#endif
