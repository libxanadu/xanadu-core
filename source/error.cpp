#include <xanadu-core/error.h>
#include <xanadu-core/string.h> // NOLINT(modernize-deprecated-headers)



// 扩展数据
static std::map<xanadu::error::value_type, xanadu::string>		_static_error_expend_array; // NOLINT(cert-err58-cpp)



// constructors
xanadu::error::error() noexcept
{
	this->_error_code = EE_UNKNOWN_ERROR;
}

// constructors
xanadu::error::error(value_type _Error) noexcept
{
	this->_error_code = _Error;
}

// constructor
xanadu::error::error(const error& _Error) noexcept = default;

// constructor
xanadu::error::error(error&& _Error) noexcept = default;

// destructor
xanadu::error::~error() noexcept = default;





// operator overload =
xanadu::error& xanadu::error::operator = (value_type _Error) noexcept
{
	this->_error_code = _Error;
	return *this;
}

// operator overload =
xanadu::error& xanadu::error::operator = (const error& _Error) noexcept = default;

// operator overload =
xanadu::error& xanadu::error::operator = (error&& _Error) noexcept = default;





// operator overload ==
bool xanadu::error::operator == (value_type _Error) const noexcept
{
	return this->_error_code == _Error;
}

// operator overload ==
bool xanadu::error::operator == (const error& _Error) const noexcept
{
	return this->_error_code == _Error._error_code;
}





// operator overload !=
bool xanadu::error::operator != (value_type _Error) const noexcept
{
	return this->_error_code != _Error;
}

// operator overload !=
bool xanadu::error::operator != (const error& _Error) const noexcept
{
	return this->_error_code != _Error._error_code;
}





// operator overload bool
xanadu::error::operator bool () const noexcept
{
	return this->_error_code == EE_SUCCESS;
}





// [get] success
bool xanadu::error::success() const noexcept
{
	return this->_error_code == EE_SUCCESS;
}

// [get] failure
bool xanadu::error::failure() const noexcept
{
	return this->_error_code != EE_SUCCESS;
}

// [get] explain
const xanadu::error::_Elem* xanadu::error::explain() const noexcept
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
void xanadu::error::add_expand(value_type _Code, const _Elem* _Explain) noexcept
{
	auto		vIterator = _static_error_expend_array.find(_Code);
	if(vIterator == _static_error_expend_array.end())
	{
		_static_error_expend_array.insert(std::map<xanadu::error::value_type, xanadu::string>::value_type(_Code, string(_Explain)));
	}
	else
	{
		vIterator->second = _Explain;
	}
}
