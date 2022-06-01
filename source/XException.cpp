#include <xanadu-core/XException.h>



// constructor
XException::XException() noexcept = default;

// constructor
XException::XException(const char* _Explain) noexcept
{
	this->_explain = _Explain;
}

// constructor
XException::XException(const XString& _Explain) noexcept
{
	this->_explain = _Explain;
}

// constructor
XException::XException(const XException& _Exception) noexcept = default;

// destructor
XException::~XException() noexcept = default;





// operator overloading =
XException& XException::operator = (const char* _Explain) noexcept
{
	this->_explain = _Explain;
	return *this;
}

// operator overloading =
XException& XException::operator = (const XString& _Explain) noexcept
{
	this->_explain = _Explain;
	return *this;
}

// operator overloading =
XException& XException::operator = (const XException& _Exception) noexcept = default;





// Get exception description
const char* XException::what() const noexcept
{
	return this->_explain.data();
}






// [std] range_error
std::range_error XException::range_error() noexcept
{
	return std::range_error("range_error");
}

// [std] range_error
std::range_error XException::range_error(const char* _Message) noexcept
{
	return std::range_error(_Message ? _Message : "null");
}

// [std] range_error
std::range_error XException::range_error(const std::string& _Message) noexcept
{
	return std::range_error(_Message.empty() ? "null" : _Message);
}

// [std] range_error
std::range_error XException::range_error(const XString& _Message) noexcept
{
	return std::range_error(_Message.empty() ? "null" : _Message.data());
}
