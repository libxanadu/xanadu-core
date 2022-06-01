#ifndef			_XANADU_CORE_BYTE_TERNARY_H_
#define			_XANADU_CORE_BYTE_TERNARY_H_

#include <xanadu-core/header.h>

/// <summary>
///  A ternary value type
/// The value types are true / false / null(undefined)
/// </summary>
class _XCOREAPI_ XTernary
{
public:
	// value types
	typedef enum value_type
	{
		TernaryNull = 0,		// The value equal to 0 is null
		TernaryTrue = 1,		// All values greater than 0 are true
		TernaryFalse = -1,		// All values less than 0 are false
	}value_type;

private:
	value_type				_ternary_value;

public:
	// constructor
	XTernary() noexcept;

	// constructor
	XTernary(value_type _Type) noexcept; // NOLINT(google-explicit-constructor)

	// constructor
	XTernary(bool _Value) noexcept; // NOLINT(google-explicit-constructor)

	// constructor
	XTernary(char _Value) noexcept; // NOLINT(google-explicit-constructor)

	// constructor
	XTernary(unsigned char _Value) noexcept; // NOLINT(google-explicit-constructor)

	// constructor
	XTernary(short _Value) noexcept; // NOLINT(google-explicit-constructor)

	// constructor
	XTernary(unsigned short _Value) noexcept; // NOLINT(google-explicit-constructor)

	// constructor
	XTernary(int _Value) noexcept; // NOLINT(google-explicit-constructor)

	// constructor
	XTernary(unsigned int _Value) noexcept; // NOLINT(google-explicit-constructor)

	// constructor
	XTernary(long _Value) noexcept; // NOLINT(google-explicit-constructor)

	// constructor
	XTernary(unsigned long _Value) noexcept; // NOLINT(google-explicit-constructor)

	// constructor
	XTernary(long long _Value) noexcept; // NOLINT(google-explicit-constructor)

	// constructor
	XTernary(unsigned long long _Value) noexcept; // NOLINT(google-explicit-constructor)

	// constructor
	XTernary(const void* _Value) noexcept; // NOLINT(google-explicit-constructor)

	// constructor
	XTernary(const XTernary& _Other) noexcept;

	// constructor
	XTernary(XTernary&& _Other) noexcept;

	// destructor
	virtual ~XTernary() noexcept;

public:
	// operator overload =
	XTernary& operator = (value_type _Type) noexcept;

	// operator overload =
	XTernary& operator = (bool _Value) noexcept;

	// operator overload =
	XTernary& operator = (char _Value) noexcept;

	// operator overload =
	XTernary& operator = (unsigned char _Value) noexcept;

	// operator overload =
	XTernary& operator = (short _Value) noexcept;

	// operator overload =
	XTernary& operator = (unsigned short _Value) noexcept;

	// operator overload =
	XTernary& operator = (int _Value) noexcept;

	// operator overload =
	XTernary& operator = (unsigned int _Value) noexcept;

	// operator overload =
	XTernary& operator = (long _Value) noexcept;

	// operator overload =
	XTernary& operator = (unsigned long _Value) noexcept;

	// operator overload =
	XTernary& operator = (long long _Value) noexcept;

	// operator overload =
	XTernary& operator = (unsigned long long _Value) noexcept;

	// operator overload =
	XTernary& operator = (const void* _Value) noexcept;

	// operator overload =
	XTernary& operator = (const XTernary& _Other) noexcept;

	// operator overload =
	XTernary& operator = (XTernary&& _Other) noexcept;

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
	bool operator == (const XTernary& _Other) const noexcept;

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
	bool operator != (const XTernary& _Other) const noexcept;

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
	// swap
	virtual void swap(XTernary& _Other) noexcept final;

public:
	// [get] type
	virtual value_type type() const noexcept final;

public:
	// [get] Is Null
	virtual bool isNull() const noexcept final;

	// [get] Is Null
	virtual bool isEmpty() const noexcept final;

	// [get] Is Ture
	virtual bool isTure() const noexcept final;

	// [get] Is False
	virtual bool isFalse() const noexcept final;
};

#endif
