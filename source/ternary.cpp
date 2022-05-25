#include <xanadu-core/ternary.h>


// constructor
x::ternary::ternary() noexcept
{
	this->_value_type = value_null;
}

// constructor
x::ternary::ternary(value_type _Type) noexcept
{
	this->_value_type = _Type;
}

// constructor
x::ternary::ternary(bool _Value) noexcept
{
	this->_value_type = x::ternary::convert(_Value);
}

// constructor
x::ternary::ternary(char _Value) noexcept
{
	this->_value_type = x::ternary::convert(_Value);
}

// constructor
x::ternary::ternary(unsigned char _Value) noexcept
{
	this->_value_type = x::ternary::convert(_Value);
}

// constructor
x::ternary::ternary(short _Value) noexcept
{
	this->_value_type = x::ternary::convert(_Value);
}

// constructor
x::ternary::ternary(unsigned short _Value) noexcept
{
	this->_value_type = x::ternary::convert(_Value);
}

// constructor
x::ternary::ternary(int _Value) noexcept
{
	this->_value_type = x::ternary::convert(_Value);
}

// constructor
x::ternary::ternary(unsigned int _Value) noexcept
{
	this->_value_type = x::ternary::convert(_Value);
}

// constructor
x::ternary::ternary(long _Value) noexcept
{
	this->_value_type = x::ternary::convert(_Value);
}

// constructor
x::ternary::ternary(unsigned long _Value) noexcept
{
	this->_value_type = x::ternary::convert(_Value);
}

// constructor
x::ternary::ternary(long long _Value) noexcept
{
	this->_value_type = x::ternary::convert(_Value);
}

// constructor
x::ternary::ternary(unsigned long long _Value) noexcept
{
	this->_value_type = x::ternary::convert(_Value);
}

// constructor
x::ternary::ternary(const void* _Value) noexcept
{
	this->_value_type = x::ternary::convert(_Value);
}

// constructor
x::ternary::ternary(const x::ternary& _Other) noexcept
{
	this->_value_type = _Other._value_type;
}

// constructor
x::ternary::ternary(x::ternary&& _Other) noexcept
{
	if(this != &_Other)
	{
		this->_value_type = _Other._value_type;
		_Other._value_type = value_null;
	}
}

// Virtual destructor
x::ternary::~ternary() noexcept = default;





// operator overload =
x::ternary& x::ternary::operator = (value_type _Type) noexcept
{
	this->_value_type = _Type;
	return *this;
}

// Operator overload =
x::ternary& x::ternary::operator = (bool _Value) noexcept
{
	this->_value_type = x::ternary::convert(_Value);
	return *this;
}

// Operator overload =
x::ternary& x::ternary::operator = (char _Value) noexcept
{
	this->_value_type = x::ternary::convert(_Value);
	return *this;
}

// Operator overload =
x::ternary& x::ternary::operator = (unsigned char _Value) noexcept
{
	this->_value_type = x::ternary::convert(_Value);
	return *this;
}

// Operator overload =
x::ternary& x::ternary::operator = (short _Value) noexcept
{
	this->_value_type = x::ternary::convert(_Value);
	return *this;
}

// Operator overload =
x::ternary& x::ternary::operator = (unsigned short _Value) noexcept
{
	this->_value_type = x::ternary::convert(_Value);
	return *this;
}

// Operator overload =
x::ternary& x::ternary::operator = (int _Value) noexcept
{
	this->_value_type = x::ternary::convert(_Value);
	return *this;
}

// Operator overload =
x::ternary& x::ternary::operator = (unsigned int _Value) noexcept
{
	this->_value_type = x::ternary::convert(_Value);
	return *this;
}

// Operator overload =
x::ternary& x::ternary::operator = (long _Value) noexcept
{
	this->_value_type = x::ternary::convert(_Value);
	return *this;
}

// Operator overload =
x::ternary& x::ternary::operator = (unsigned long _Value) noexcept
{
	this->_value_type = x::ternary::convert(_Value);
	return *this;
}

// Operator overload =
x::ternary& x::ternary::operator = (long long _Value) noexcept
{
	this->_value_type = x::ternary::convert(_Value);
	return *this;
}

// Operator overload =
x::ternary& x::ternary::operator = (unsigned long long _Value) noexcept
{
	this->_value_type = x::ternary::convert(_Value);
	return *this;
}

// Operator overload =
x::ternary& x::ternary::operator = (const void* _Value) noexcept
{
	this->_value_type = x::ternary::convert(_Value);
	return *this;
}

// Operator overload =
x::ternary& x::ternary::operator = (const x::ternary& _Other) noexcept
{
	if(this == &_Other)
	{
		return *this;
	}

	this->_value_type = _Other._value_type;
	return *this;
}

// Operator overload =
x::ternary& x::ternary::operator = (x::ternary&& _Other) noexcept
{
	if(this == &_Other)
	{
		return *this;
	}

	this->_value_type = _Other._value_type;
	_Other._value_type = value_null;
	return *this;
}




// operator overload ==
bool x::ternary::operator == (value_type _Type) const noexcept
{
	return this->_value_type == _Type;
}

// operator overload ==
bool x::ternary::operator == (bool _Value) const noexcept
{
	return this->_value_type == x::ternary::convert(_Value);
}

// operator overload ==
bool x::ternary::operator == (char _Value) const noexcept
{
	return this->_value_type == x::ternary::convert(_Value);
}

// operator overload ==
bool x::ternary::operator == (unsigned char _Value) const noexcept
{
	return this->_value_type == x::ternary::convert(_Value);
}

// operator overload ==
bool x::ternary::operator == (short _Value) const noexcept
{
	return this->_value_type == x::ternary::convert(_Value);
}

// operator overload ==
bool x::ternary::operator == (unsigned short _Value) const noexcept
{
	return this->_value_type == x::ternary::convert(_Value);
}

// operator overload ==
bool x::ternary::operator == (int _Value) const noexcept
{
	return this->_value_type == x::ternary::convert(_Value);
}

// operator overload ==
bool x::ternary::operator == (unsigned int _Value) const noexcept
{
	return this->_value_type == x::ternary::convert(_Value);
}

// operator overload ==
bool x::ternary::operator == (long _Value) const noexcept
{
	return this->_value_type == x::ternary::convert(_Value);
}

// operator overload ==
bool x::ternary::operator == (unsigned long _Value) const noexcept
{
	return this->_value_type == x::ternary::convert(_Value);
}

// operator overload ==
bool x::ternary::operator == (long long _Value) const noexcept
{
	return this->_value_type == x::ternary::convert(_Value);
}

// operator overload ==
bool x::ternary::operator == (unsigned long long _Value) const noexcept
{
	return this->_value_type == x::ternary::convert(_Value);
}

// operator overload ==
bool x::ternary::operator == (const void* _Value) const noexcept
{
	return this->_value_type == x::ternary::convert(_Value);
}

// operator overload ==
bool x::ternary::operator == (const x::ternary& _Other) const noexcept
{
	return this->_value_type == _Other._value_type;
}



// operator overload !=
bool x::ternary::operator != (value_type _Type) const noexcept
{
	return this->_value_type != _Type;
}

// operator overload !=
bool x::ternary::operator != (bool _Value) const noexcept
{
	return this->_value_type != x::ternary::convert(_Value);
}

// operator overload !=
bool x::ternary::operator != (char _Value) const noexcept
{
	return this->_value_type != x::ternary::convert(_Value);
}

// operator overload !=
bool x::ternary::operator != (unsigned char _Value) const noexcept
{
	return this->_value_type != x::ternary::convert(_Value);
}

// operator overload !=
bool x::ternary::operator != (short _Value) const noexcept
{
	return this->_value_type != x::ternary::convert(_Value);
}

// operator overload !=
bool x::ternary::operator != (unsigned short _Value) const noexcept
{
	return this->_value_type != x::ternary::convert(_Value);
}

// operator overload !=
bool x::ternary::operator != (int _Value) const noexcept
{
	return this->_value_type != x::ternary::convert(_Value);
}

// operator overload !=
bool x::ternary::operator != (unsigned int _Value) const noexcept
{
	return this->_value_type != x::ternary::convert(_Value);
}

// operator overload !=
bool x::ternary::operator != (long _Value) const noexcept
{
	return this->_value_type != x::ternary::convert(_Value);
}

// operator overload !=
bool x::ternary::operator != (unsigned long _Value) const noexcept
{
	return this->_value_type != x::ternary::convert(_Value);
}

// operator overload !=
bool x::ternary::operator != (long long _Value) const noexcept
{
	return this->_value_type != x::ternary::convert(_Value);
}

// operator overload !=
bool x::ternary::operator != (unsigned long long _Value) const noexcept
{
	return this->_value_type != x::ternary::convert(_Value);
}

// operator overload !=
bool x::ternary::operator != (const void* _Value) const noexcept
{
	return this->_value_type != x::ternary::convert(_Value);
}

// operator overload !=
bool x::ternary::operator != (const x::ternary& _Other) const noexcept
{
	return this->_value_type != _Other._value_type;
}



// [opt] convert parameter to ternary type
x::ternary::value_type x::ternary::convert(bool _Value) noexcept
{
	return _Value ? value_true : value_false;
}

// [opt] convert parameter to ternary type
x::ternary::value_type x::ternary::convert(char _Value) noexcept
{
	return x::ternary::convert(static_cast<long long>(_Value));
}

// [opt] convert parameter to ternary type
x::ternary::value_type x::ternary::convert(unsigned char _Value) noexcept
{
	return x::ternary::convert(static_cast<unsigned long long>(_Value));
}

// [opt] convert parameter to ternary type
x::ternary::value_type x::ternary::convert(short _Value) noexcept
{
	return x::ternary::convert(static_cast<long long>(_Value));
}

// [opt] convert parameter to ternary type
x::ternary::value_type x::ternary::convert(unsigned short _Value) noexcept
{
	return x::ternary::convert(static_cast<unsigned long long>(_Value));
}

// [opt] convert parameter to ternary type
x::ternary::value_type x::ternary::convert(int _Value) noexcept
{
	return x::ternary::convert(static_cast<long long>(_Value));
}

// [opt] convert parameter to ternary type
x::ternary::value_type x::ternary::convert(unsigned int _Value) noexcept
{
	return x::ternary::convert(static_cast<unsigned long long>(_Value));
}

// [opt] convert parameter to ternary type
x::ternary::value_type x::ternary::convert(long _Value) noexcept
{
	return x::ternary::convert(static_cast<long long>(_Value));
}

// [opt] convert parameter to ternary type
x::ternary::value_type x::ternary::convert(unsigned long _Value) noexcept
{
	return x::ternary::convert(static_cast<unsigned long long>(_Value));
}

// [opt] convert parameter to ternary type
x::ternary::value_type x::ternary::convert(long long _Value) noexcept
{
	if(_Value == 0)
	{
		return value_null;
	}
	else if(_Value > 0)
	{
		return value_true;
	}
	else
	{
		return value_false;
	}
}

// [opt] convert parameter to ternary type
x::ternary::value_type x::ternary::convert(unsigned long long _Value) noexcept
{
	if(_Value == 0)
	{
		return value_null;
	}
	else
	{
		return value_true;
	}
}

// [opt] convert parameter to ternary type
x::ternary::value_type x::ternary::convert(const void* _Value) noexcept
{
	if(_Value == nullptr)
	{
		return value_null;
	}
	else
	{
		return value_true;
	}
}





// [get] type
x::ternary::value_type x::ternary::type() const noexcept
{
	return this->_value_type;
}





// [get] 是否为空
bool x::ternary::is_null() const noexcept
{
	return this->_value_type == value_null;
}

// [get] 是否为真
bool x::ternary::is_ture() const noexcept
{
	return this->_value_type == value_true;
}

// [get] 是否为假
bool x::ternary::is_false() const noexcept
{
	return this->_value_type == value_false;
}
