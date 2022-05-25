#include <xanadu-core/error.h>
#include <xanadu-core/string.h> // NOLINT(modernize-deprecated-headers)



// 扩展数据
static std::map<x::error::value_type, x::string>		_static_error_expend_array; // NOLINT(cert-err58-cpp)



// constructors
x::error::error() noexcept
{
	this->_error_code = EE_UNKNOWN_ERROR;
}

// constructors
x::error::error(value_type _Error) noexcept
{
	this->_error_code = _Error;
}

// constructor
x::error::error(const error& _Error) noexcept = default;

// constructor
x::error::error(error&& _Error) noexcept = default;

// destructor
x::error::~error() noexcept = default;





// operator overload =
x::error& x::error::operator = (value_type _Error) noexcept
{
	this->_error_code = _Error;
	return *this;
}

// operator overload =
x::error& x::error::operator = (const error& _Error) noexcept = default;

// operator overload =
x::error& x::error::operator = (error&& _Error) noexcept = default;





// operator overload ==
bool x::error::operator == (value_type _Error) const noexcept
{
	return this->_error_code == _Error;
}

// operator overload ==
bool x::error::operator == (const error& _Error) const noexcept
{
	return this->_error_code == _Error._error_code;
}





// operator overload !=
bool x::error::operator != (value_type _Error) const noexcept
{
	return this->_error_code != _Error;
}

// operator overload !=
bool x::error::operator != (const error& _Error) const noexcept
{
	return this->_error_code != _Error._error_code;
}





// operator overload bool
x::error::operator bool () const noexcept
{
	return this->_error_code == EE_SUCCESS;
}





// [get] success
bool x::error::success() const noexcept
{
	return this->_error_code == EE_SUCCESS;
}

// [get] failure
bool x::error::failure() const noexcept
{
	return this->_error_code != EE_SUCCESS;
}

// [get] explain
const x::error::elem_type* x::error::explain() const noexcept
{
	auto		vIterator = _static_error_expend_array.find(this->_error_code);
	if(vIterator != _static_error_expend_array.end())
	{
		return vIterator->second.data();
	}

	switch (this->_error_code)
	{
		case EE_SUCCESS:			return "SUCCESS";
		default:				return "UNKNOWN_ERROR";
	}
}





// 添加扩展数据
void x::error::add_expand(value_type _Code, const elem_type* _Explain) noexcept
{
	auto		vIterator = _static_error_expend_array.find(_Code);
	if(vIterator == _static_error_expend_array.end())
	{
		_static_error_expend_array.insert(std::map<x::error::value_type, x::string>::value_type(_Code, string(_Explain)));
	}
	else
	{
		vIterator->second = _Explain;
	}
}
