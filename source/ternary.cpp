#include <xanadu-core/ternary.h>


// constructor
xanadu::ternary::ternary() noexcept
{
	this->_value_type = value_null;
}

// constructor
xanadu::ternary::ternary(value_type _Type) noexcept
{
	this->_value_type = _Type;
}

// constructor
xanadu::ternary::ternary(bool _Value) noexcept
{
	this->_value_type = xanadu::ternary::convert(_Value);
}

// constructor
xanadu::ternary::ternary(char _Value) noexcept
{
	this->_value_type = xanadu::ternary::convert(_Value);
}

// constructor
xanadu::ternary::ternary(unsigned char _Value) noexcept
{
	this->_value_type = xanadu::ternary::convert(_Value);
}

// constructor
xanadu::ternary::ternary(short _Value) noexcept
{
	this->_value_type = xanadu::ternary::convert(_Value);
}

// constructor
xanadu::ternary::ternary(unsigned short _Value) noexcept
{
	this->_value_type = xanadu::ternary::convert(_Value);
}

// constructor
xanadu::ternary::ternary(int _Value) noexcept
{
	this->_value_type = xanadu::ternary::convert(_Value);
}

// constructor
xanadu::ternary::ternary(unsigned int _Value) noexcept
{
	this->_value_type = xanadu::ternary::convert(_Value);
}

// constructor
xanadu::ternary::ternary(long _Value) noexcept
{
	this->_value_type = xanadu::ternary::convert(_Value);
}

// constructor
xanadu::ternary::ternary(unsigned long _Value) noexcept
{
	this->_value_type = xanadu::ternary::convert(_Value);
}

// constructor
xanadu::ternary::ternary(long long _Value) noexcept
{
	this->_value_type = xanadu::ternary::convert(_Value);
}

// constructor
xanadu::ternary::ternary(unsigned long long _Value) noexcept
{
	this->_value_type = xanadu::ternary::convert(_Value);
}

// constructor
xanadu::ternary::ternary(const void* _Value) noexcept
{
	this->_value_type = xanadu::ternary::convert(_Value);
}

// constructor
xanadu::ternary::ternary(const xanadu::ternary& _Other) noexcept
{
	this->_value_type = _Other._value_type;
}

// constructor
xanadu::ternary::ternary(xanadu::ternary&& _Other) noexcept
{
	if(this != &_Other)
	{
		this->_value_type = _Other._value_type;
		_Other._value_type = value_null;
	}
}

// Virtual destructor
xanadu::ternary::~ternary() noexcept = default;





// operator overload =
xanadu::ternary& xanadu::ternary::operator = (value_type _Type) noexcept
{
	this->_value_type = _Type;
	return *this;
}

// Operator overload =
xanadu::ternary& xanadu::ternary::operator = (bool _Value) noexcept
{
	this->_value_type = xanadu::ternary::convert(_Value);
	return *this;
}

// Operator overload =
xanadu::ternary& xanadu::ternary::operator = (char _Value) noexcept
{
	this->_value_type = xanadu::ternary::convert(_Value);
	return *this;
}

// Operator overload =
xanadu::ternary& xanadu::ternary::operator = (unsigned char _Value) noexcept
{
	this->_value_type = xanadu::ternary::convert(_Value);
	return *this;
}

// Operator overload =
xanadu::ternary& xanadu::ternary::operator = (short _Value) noexcept
{
	this->_value_type = xanadu::ternary::convert(_Value);
	return *this;
}

// Operator overload =
xanadu::ternary& xanadu::ternary::operator = (unsigned short _Value) noexcept
{
	this->_value_type = xanadu::ternary::convert(_Value);
	return *this;
}

// Operator overload =
xanadu::ternary& xanadu::ternary::operator = (int _Value) noexcept
{
	this->_value_type = xanadu::ternary::convert(_Value);
	return *this;
}

// Operator overload =
xanadu::ternary& xanadu::ternary::operator = (unsigned int _Value) noexcept
{
	this->_value_type = xanadu::ternary::convert(_Value);
	return *this;
}

// Operator overload =
xanadu::ternary& xanadu::ternary::operator = (long _Value) noexcept
{
	this->_value_type = xanadu::ternary::convert(_Value);
	return *this;
}

// Operator overload =
xanadu::ternary& xanadu::ternary::operator = (unsigned long _Value) noexcept
{
	this->_value_type = xanadu::ternary::convert(_Value);
	return *this;
}

// Operator overload =
xanadu::ternary& xanadu::ternary::operator = (long long _Value) noexcept
{
	this->_value_type = xanadu::ternary::convert(_Value);
	return *this;
}

// Operator overload =
xanadu::ternary& xanadu::ternary::operator = (unsigned long long _Value) noexcept
{
	this->_value_type = xanadu::ternary::convert(_Value);
	return *this;
}

// Operator overload =
xanadu::ternary& xanadu::ternary::operator = (const void* _Value) noexcept
{
	this->_value_type = xanadu::ternary::convert(_Value);
	return *this;
}

// Operator overload =
xanadu::ternary& xanadu::ternary::operator = (const xanadu::ternary& _Other) noexcept
{
	if(this == &_Other)
	{
		return *this;
	}

	this->_value_type = _Other._value_type;
	return *this;
}

// Operator overload =
xanadu::ternary& xanadu::ternary::operator = (xanadu::ternary&& _Other) noexcept
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
bool xanadu::ternary::operator == (value_type _Type) const noexcept
{
	return this->_value_type == _Type;
}

// operator overload ==
bool xanadu::ternary::operator == (bool _Value) const noexcept
{
	return this->_value_type == xanadu::ternary::convert(_Value);
}

// operator overload ==
bool xanadu::ternary::operator == (char _Value) const noexcept
{
	return this->_value_type == xanadu::ternary::convert(_Value);
}

// operator overload ==
bool xanadu::ternary::operator == (unsigned char _Value) const noexcept
{
	return this->_value_type == xanadu::ternary::convert(_Value);
}

// operator overload ==
bool xanadu::ternary::operator == (short _Value) const noexcept
{
	return this->_value_type == xanadu::ternary::convert(_Value);
}

// operator overload ==
bool xanadu::ternary::operator == (unsigned short _Value) const noexcept
{
	return this->_value_type == xanadu::ternary::convert(_Value);
}

// operator overload ==
bool xanadu::ternary::operator == (int _Value) const noexcept
{
	return this->_value_type == xanadu::ternary::convert(_Value);
}

// operator overload ==
bool xanadu::ternary::operator == (unsigned int _Value) const noexcept
{
	return this->_value_type == xanadu::ternary::convert(_Value);
}

// operator overload ==
bool xanadu::ternary::operator == (long _Value) const noexcept
{
	return this->_value_type == xanadu::ternary::convert(_Value);
}

// operator overload ==
bool xanadu::ternary::operator == (unsigned long _Value) const noexcept
{
	return this->_value_type == xanadu::ternary::convert(_Value);
}

// operator overload ==
bool xanadu::ternary::operator == (long long _Value) const noexcept
{
	return this->_value_type == xanadu::ternary::convert(_Value);
}

// operator overload ==
bool xanadu::ternary::operator == (unsigned long long _Value) const noexcept
{
	return this->_value_type == xanadu::ternary::convert(_Value);
}

// operator overload ==
bool xanadu::ternary::operator == (const void* _Value) const noexcept
{
	return this->_value_type == xanadu::ternary::convert(_Value);
}

// operator overload ==
bool xanadu::ternary::operator == (const xanadu::ternary& _Other) const noexcept
{
	return this->_value_type == _Other._value_type;
}



// operator overload !=
bool xanadu::ternary::operator != (value_type _Type) const noexcept
{
	return this->_value_type != _Type;
}

// operator overload !=
bool xanadu::ternary::operator != (bool _Value) const noexcept
{
	return this->_value_type != xanadu::ternary::convert(_Value);
}

// operator overload !=
bool xanadu::ternary::operator != (char _Value) const noexcept
{
	return this->_value_type != xanadu::ternary::convert(_Value);
}

// operator overload !=
bool xanadu::ternary::operator != (unsigned char _Value) const noexcept
{
	return this->_value_type != xanadu::ternary::convert(_Value);
}

// operator overload !=
bool xanadu::ternary::operator != (short _Value) const noexcept
{
	return this->_value_type != xanadu::ternary::convert(_Value);
}

// operator overload !=
bool xanadu::ternary::operator != (unsigned short _Value) const noexcept
{
	return this->_value_type != xanadu::ternary::convert(_Value);
}

// operator overload !=
bool xanadu::ternary::operator != (int _Value) const noexcept
{
	return this->_value_type != xanadu::ternary::convert(_Value);
}

// operator overload !=
bool xanadu::ternary::operator != (unsigned int _Value) const noexcept
{
	return this->_value_type != xanadu::ternary::convert(_Value);
}

// operator overload !=
bool xanadu::ternary::operator != (long _Value) const noexcept
{
	return this->_value_type != xanadu::ternary::convert(_Value);
}

// operator overload !=
bool xanadu::ternary::operator != (unsigned long _Value) const noexcept
{
	return this->_value_type != xanadu::ternary::convert(_Value);
}

// operator overload !=
bool xanadu::ternary::operator != (long long _Value) const noexcept
{
	return this->_value_type != xanadu::ternary::convert(_Value);
}

// operator overload !=
bool xanadu::ternary::operator != (unsigned long long _Value) const noexcept
{
	return this->_value_type != xanadu::ternary::convert(_Value);
}

// operator overload !=
bool xanadu::ternary::operator != (const void* _Value) const noexcept
{
	return this->_value_type != xanadu::ternary::convert(_Value);
}

// operator overload !=
bool xanadu::ternary::operator != (const xanadu::ternary& _Other) const noexcept
{
	return this->_value_type != _Other._value_type;
}



// [opt] convert parameter to ternary type
xanadu::ternary::value_type xanadu::ternary::convert(bool _Value) noexcept
{
	return _Value ? value_true : value_false;
}

// [opt] convert parameter to ternary type
xanadu::ternary::value_type xanadu::ternary::convert(char _Value) noexcept
{
	return xanadu::ternary::convert(static_cast<long long>(_Value));
}

// [opt] convert parameter to ternary type
xanadu::ternary::value_type xanadu::ternary::convert(unsigned char _Value) noexcept
{
	return xanadu::ternary::convert(static_cast<unsigned long long>(_Value));
}

// [opt] convert parameter to ternary type
xanadu::ternary::value_type xanadu::ternary::convert(short _Value) noexcept
{
	return xanadu::ternary::convert(static_cast<long long>(_Value));
}

// [opt] convert parameter to ternary type
xanadu::ternary::value_type xanadu::ternary::convert(unsigned short _Value) noexcept
{
	return xanadu::ternary::convert(static_cast<unsigned long long>(_Value));
}

// [opt] convert parameter to ternary type
xanadu::ternary::value_type xanadu::ternary::convert(int _Value) noexcept
{
	return xanadu::ternary::convert(static_cast<long long>(_Value));
}

// [opt] convert parameter to ternary type
xanadu::ternary::value_type xanadu::ternary::convert(unsigned int _Value) noexcept
{
	return xanadu::ternary::convert(static_cast<unsigned long long>(_Value));
}

// [opt] convert parameter to ternary type
xanadu::ternary::value_type xanadu::ternary::convert(long _Value) noexcept
{
	return xanadu::ternary::convert(static_cast<long long>(_Value));
}

// [opt] convert parameter to ternary type
xanadu::ternary::value_type xanadu::ternary::convert(unsigned long _Value) noexcept
{
	return xanadu::ternary::convert(static_cast<unsigned long long>(_Value));
}

// [opt] convert parameter to ternary type
xanadu::ternary::value_type xanadu::ternary::convert(long long _Value) noexcept
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
xanadu::ternary::value_type xanadu::ternary::convert(unsigned long long _Value) noexcept
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
xanadu::ternary::value_type xanadu::ternary::convert(const void* _Value) noexcept
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
xanadu::ternary::value_type xanadu::ternary::type() const noexcept
{
	return this->_value_type;
}





// [get] 是否为空
bool xanadu::ternary::is_null() const noexcept
{
	return this->_value_type == value_null;
}

// [get] 是否为真
bool xanadu::ternary::is_ture() const noexcept
{
	return this->_value_type == value_true;
}

// [get] 是否为假
bool xanadu::ternary::is_false() const noexcept
{
	return this->_value_type == value_false;
}
