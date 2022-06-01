#ifndef			_XANADU_CORE_VARIANT_H_
#define			_XANADU_CORE_VARIANT_H_

#include <xanadu-core/header.h>
#include <xanadu-core/XByteArray.h>
#include <xanadu-core/XString.h>

// Xanadu Class Variant
class _XCOREAPI_ XVariant
{
public:
	typedef enum value_type
	{
		VariantInvalid				= 0,
		VariantBoolean				= 1,
		VariantChar				= 2,
		VariantUChar				= 3,
		VariantShort				= 4,
		VariantUShort				= 5,
		VariantInteger				= 6,
		VariantUInteger				= 7,
		VariantLong				= 8,
		VariantULong				= 9,
		VariantLLong				= 10,
		VariantULLong				= 11,
		VariantFloat				= 12,
		VariantDouble				= 13,
		VariantString				= 14,
		VariantByteArray			= 15
	}value_type;

private:
	typedef union data_type
	{
		bool					_VBool;
		x_llong_t				_VInt64S;
		x_ullong_t				_VInt64U;
		x_double_t 				_VDouble;
		void*					_VObject;
		x_llong_t				_VNull;
	}data_type;

	data_type					_variant_data;
	value_type					_variant_type;

public:
	// constructor
	XVariant() noexcept;

	// constructor
	XVariant(value_type _Type) noexcept;

	// constructor
	XVariant(bool _Value) noexcept;

	// constructor
	XVariant(x_char_t _Value) noexcept;

	// constructor
	XVariant(x_uchar_t _Value) noexcept;

	// constructor
	XVariant(x_short_t _Value) noexcept;

	// constructor
	XVariant(x_ushort_t _Value) noexcept;

	// constructor
	XVariant(x_int_t _Value) noexcept;

	// constructor
	XVariant(x_uint_t _Value) noexcept;

	// constructor
	XVariant(x_long_t _Value) noexcept;

	// constructor
	XVariant(x_ulong_t _Value) noexcept;

	// constructor
	XVariant(x_llong_t _Value) noexcept;

	// constructor
	XVariant(x_ullong_t _Value) noexcept;

	// constructor
	XVariant(x_float_t _Value) noexcept;

	// constructor
	XVariant(x_double_t _Value) noexcept;

	// constructor
	XVariant(const char* _Value) noexcept;

	// constructor
	XVariant(const XString& _Value) noexcept;

	// constructor
	XVariant(const XByteArray& _Value) noexcept;

	// constructor
	XVariant(const XVariant& _Other) noexcept;

	// constructor
	XVariant(XVariant&& _Other) noexcept;

	// destructor
	virtual ~XVariant() noexcept;

public:
	// operator overload =
	XVariant& operator = (bool _Value) noexcept;

	// operator overload =
	XVariant& operator = (x_char_t _Value) noexcept;

	// operator overload =
	XVariant& operator = (x_uchar_t _Value) noexcept;

	// operator overload =
	XVariant& operator = (x_short_t _Value) noexcept;

	// operator overload =
	XVariant& operator = (x_ushort_t _Value) noexcept;

	// operator overload =
	XVariant& operator = (x_int_t _Value) noexcept;

	// operator overload =
	XVariant& operator = (x_uint_t _Value) noexcept;

	// operator overload =
	XVariant& operator = (x_long_t _Value) noexcept;

	// operator overload =
	XVariant& operator = (x_ulong_t _Value) noexcept;

	// operator overload =
	XVariant& operator = (x_llong_t _Value) noexcept;

	// operator overload =
	XVariant& operator = (x_ullong_t _Value) noexcept;

	// operator overload =
	XVariant& operator = (x_float_t _Value) noexcept;

	// operator overload =
	XVariant& operator = (x_double_t _Value) noexcept;

	// operator overload =
	XVariant& operator = (const char* _Value) noexcept;

	// operator overload =
	XVariant& operator = (const XString& _Value) noexcept;

	// operator overload =
	XVariant& operator = (const XByteArray& _Value) noexcept;

	// operator overload =
	XVariant& operator = (const XVariant& _Other) noexcept;

	// operator overload =
	XVariant& operator = (XVariant&& _Other) noexcept;

private:
	// Data copy
	virtual void _copy(const XVariant& _Other) noexcept final;

public:
	// Get the current type
	virtual value_type type() const noexcept final;

	// Clear current content
	virtual void clear() noexcept final;

public:
	// Convert to bool
	virtual bool toBool() const noexcept final;

	// Convert to x_char_t
	virtual x_char_t toChar() const noexcept final;

	// Convert to x_uchar_t
	virtual x_uchar_t toUChar() const noexcept final;

	// Convert to x_short_t
	virtual x_short_t toShort() const noexcept final;

	// Convert to x_ushort_t
	virtual x_ushort_t toUShort() const noexcept final;

	// Convert to x_int_t
	virtual x_int_t toInt() const noexcept final;

	// Convert to x_uint_t
	virtual x_uint_t toUInt() const noexcept final;

	// Convert to x_long_t
	virtual x_long_t toLong() const noexcept final;

	// Convert to x_ulong_t
	virtual x_ulong_t toULong() const noexcept final;

	// Convert to x_llong_t
	virtual x_llong_t toLLong() const noexcept final;

	// Convert to x_ullong_t
	virtual x_ullong_t toULLong() const noexcept final;

	// Convert to x_float_t
	virtual x_float_t toFloat() const noexcept final;

	// Convert to x_double_t
	virtual x_double_t toDouble() const noexcept final;

	// Convert to XString
	virtual XString toString() const noexcept final;

	// Convert to XByteArray
	virtual XByteArray toBytes() const noexcept final;
};

#endif
