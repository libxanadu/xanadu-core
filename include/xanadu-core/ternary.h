#ifndef			_XANADU_CORE_TERNARY_H_
#define			_XANADU_CORE_TERNARY_H_

#include <xanadu-core/header.h>


/// namespace xanadu
namespace xanadu
{
	/// class ternary
	class _XCOREAPI_ ternary
	{
	public:
		// value types
		typedef enum value_type
		{
			// == 0 则为空
			value_null			= 0,

			// > 0 则为真
			value_true			= 1,

			// < 0 则为假
			value_false			= -1
		}value_type;

	private:
		value_type			_value_type;

	public:
		// constructor
		ternary() noexcept;

		// constructor
		ternary(value_type _Type) noexcept; // NOLINT(google-explicit-constructor)

		// constructor
		ternary(bool _Value) noexcept; // NOLINT(google-explicit-constructor)

		// constructor
		ternary(char _Value) noexcept; // NOLINT(google-explicit-constructor)

		// constructor
		ternary(unsigned char _Value) noexcept; // NOLINT(google-explicit-constructor)

		// constructor
		ternary(short _Value) noexcept; // NOLINT(google-explicit-constructor)

		// constructor
		ternary(unsigned short _Value) noexcept; // NOLINT(google-explicit-constructor)

		// constructor
		ternary(int _Value) noexcept; // NOLINT(google-explicit-constructor)

		// constructor
		ternary(unsigned int _Value) noexcept; // NOLINT(google-explicit-constructor)

		// constructor
		ternary(long _Value) noexcept; // NOLINT(google-explicit-constructor)

		// constructor
		ternary(unsigned long _Value) noexcept; // NOLINT(google-explicit-constructor)

		// constructor
		ternary(long long _Value) noexcept; // NOLINT(google-explicit-constructor)

		// constructor
		ternary(unsigned long long _Value) noexcept; // NOLINT(google-explicit-constructor)

		// constructor
		ternary(const void* _Value) noexcept; // NOLINT(google-explicit-constructor)

		// constructor
		ternary(const ternary& _Other) noexcept;

		// constructor
		ternary(ternary&& _Other) noexcept;

		// destructor
		virtual ~ternary() noexcept;

	public:
		// operator overload =
		ternary& operator = (value_type _Type) noexcept;

		// operator overload =
		ternary& operator = (bool _Value) noexcept;

		// operator overload =
		ternary& operator = (char _Value) noexcept;

		// operator overload =
		ternary& operator = (unsigned char _Value) noexcept;

		// operator overload =
		ternary& operator = (short _Value) noexcept;

		// operator overload =
		ternary& operator = (unsigned short _Value) noexcept;

		// operator overload =
		ternary& operator = (int _Value) noexcept;

		// operator overload =
		ternary& operator = (unsigned int _Value) noexcept;

		// operator overload =
		ternary& operator = (long _Value) noexcept;

		// operator overload =
		ternary& operator = (unsigned long _Value) noexcept;

		// operator overload =
		ternary& operator = (long long _Value) noexcept;

		// operator overload =
		ternary& operator = (unsigned long long _Value) noexcept;

		// operator overload =
		ternary& operator = (const void* _Value) noexcept;

		// operator overload =
		ternary& operator = (const ternary& _Other) noexcept;

		// operator overload =
		ternary& operator = (ternary&& _Other) noexcept;

	public:
		// operator overload ==
		bool operator == (value_type _Type) const noexcept;

		// operator overload ==
		bool operator == (bool _Value) const noexcept;

		// operator overload ==
		bool operator == (char _Value) const noexcept;

		// operator overload ==
		bool operator == (unsigned char _Value) const noexcept;

		// operator overload ==
		bool operator == (short _Value) const noexcept;

		// operator overload ==
		bool operator == (unsigned short _Value) const noexcept;

		// operator overload ==
		bool operator == (int _Value) const noexcept;

		// operator overload ==
		bool operator == (unsigned int _Value) const noexcept;

		// operator overload ==
		bool operator == (long _Value) const noexcept;

		// operator overload ==
		bool operator == (unsigned long _Value) const noexcept;

		// operator overload ==
		bool operator == (long long _Value) const noexcept;

		// operator overload ==
		bool operator == (unsigned long long _Value) const noexcept;

		// operator overload ==
		bool operator == (const void* _Value) const noexcept;

		// operator overload ==
		bool operator == (const ternary& _Other) const noexcept;

	public:
		// operator overload !=
		bool operator != (value_type _Type) const noexcept;

		// operator overload !=
		bool operator != (bool _Value) const noexcept;

		// operator overload !=
		bool operator != (char _Value) const noexcept;

		// operator overload !=
		bool operator != (unsigned char _Value) const noexcept;

		// operator overload !=
		bool operator != (short _Value) const noexcept;

		// operator overload !=
		bool operator != (unsigned short _Value) const noexcept;

		// operator overload !=
		bool operator != (int _Value) const noexcept;

		// operator overload !=
		bool operator != (unsigned int _Value) const noexcept;

		// operator overload !=
		bool operator != (long _Value) const noexcept;

		// operator overload !=
		bool operator != (unsigned long _Value) const noexcept;

		// operator overload !=
		bool operator != (long long _Value) const noexcept;

		// operator overload !=
		bool operator != (unsigned long long _Value) const noexcept;

		// operator overload !=
		bool operator != (const void* _Value) const noexcept;

		// operator overload !=
		bool operator != (const ternary& _Other) const noexcept;

	public:
		// [opt] convert parameter to ternary type
		static value_type convert(bool _Value) noexcept;

		// [opt] convert parameter to ternary type
		static value_type convert(char _Value) noexcept;

		// [opt] convert parameter to ternary type
		static value_type convert(unsigned char _Value) noexcept;

		// [opt] convert parameter to ternary type
		static value_type convert(short _Value) noexcept;

		// [opt] convert parameter to ternary type
		static value_type convert(unsigned short _Value) noexcept;

		// [opt] convert parameter to ternary type
		static value_type convert(int _Value) noexcept;

		// [opt] convert parameter to ternary type
		static value_type convert(unsigned int _Value) noexcept;

		// [opt] convert parameter to ternary type
		static value_type convert(long _Value) noexcept;

		// [opt] convert parameter to ternary type
		static value_type convert(unsigned long _Value) noexcept;

		// [opt] convert parameter to ternary type
		static value_type convert(long long _Value) noexcept;

		// [opt] convert parameter to ternary type
		static value_type convert(unsigned long long _Value) noexcept;

		// [opt] convert parameter to ternary type
		static value_type convert(const void* _Value) noexcept;

	public:
		// [get] type
		virtual value_type type() const noexcept final;

	public:
		// [get] 是否为空
		virtual bool is_null() const noexcept final;

		// [get] 是否为真
		virtual bool is_ture() const noexcept final;

		// [get] 是否为假
		virtual bool is_false() const noexcept final;
	};
}

#endif
