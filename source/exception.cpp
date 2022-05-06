#include <xanadu-core/exception.h>



// constructor
xanadu::exception::exception() noexcept
{
	this->_memory_address = xanadu::exception::clone_string(nullptr, 0);
}

// constructor
xanadu::exception::exception(const _Elem* _Memory) noexcept
{
	this->_memory_address = xanadu::exception::clone_string(_Memory, x_posix_strlen(_Memory));
}

// constructor
xanadu::exception::exception(const _Elem* _Memory, size_type _Length) noexcept
{
	this->_memory_address = xanadu::exception::clone_string(_Memory, _Length);
}

// constructor
xanadu::exception::exception(const std::string& _Exception) noexcept
{
	this->_memory_address = xanadu::exception::clone_string(_Exception.data(), _Exception.size());
}

// constructor
xanadu::exception::exception(const xanadu::string& _Exception) noexcept
{
	this->_memory_address = xanadu::exception::clone_string(_Exception.data(), _Exception.size());
}

// constructor
xanadu::exception::exception(const exception& _Exception) noexcept
{
	this->_memory_address = xanadu::exception::clone_string(_Exception._memory_address, x_posix_strlen(_Exception._memory_address));
}

// constructor
xanadu::exception::exception(exception&& _Exception) noexcept
{
	this->_memory_address = xanadu::exception::clone_string(_Exception._memory_address, x_posix_strlen(_Exception._memory_address));
}

// destructor
xanadu::exception::~exception() noexcept
{
	delete this->_memory_address;
}





// operator overload =
xanadu::exception& xanadu::exception::operator = (const _Elem* _Memory) noexcept
{
	delete this->_memory_address;
	this->_memory_address = xanadu::exception::clone_string(_Memory, x_posix_strlen(_Memory));
	return *this;
}

// operator overload =
xanadu::exception& xanadu::exception::operator = (const std::string& _Exception) noexcept
{
	delete this->_memory_address;
	this->_memory_address = xanadu::exception::clone_string(_Exception.data(), _Exception.size());
	return *this;
}

// operator overload =
xanadu::exception& xanadu::exception::operator = (const xanadu::string& _Exception) noexcept
{
	delete this->_memory_address;
	this->_memory_address = xanadu::exception::clone_string(_Exception.data(), _Exception.size());
	return *this;
}

// operator overload =
xanadu::exception& xanadu::exception::operator = (const exception& _Exception) noexcept
{
	if(this != &_Exception)
	{
		delete this->_memory_address;
		this->_memory_address = xanadu::exception::clone_string(_Exception._memory_address, x_posix_strlen(_Exception._memory_address));
	}
	return *this;
}

// operator overload =
xanadu::exception& xanadu::exception::operator = (exception&& _Exception) noexcept
{
	if(this != &_Exception)
	{
		delete this->_memory_address;
		this->_memory_address = xanadu::exception::clone_string(_Exception._memory_address, x_posix_strlen(_Exception._memory_address));
	}
	return *this;
}





// [opt] 拷贝字符串
xanadu::exception::_Elem* xanadu::exception::clone_string(const _Elem* _Memory, size_type _Length) noexcept
{
	auto		vAddress = new(std::nothrow) _Elem[_Length + 1];
	if(vAddress)
	{
		x_posix_memset(vAddress, 0, _Length + 1);
		x_posix_memcpy(vAddress, _Memory, _Length);
	}
	return vAddress;
}





// [get] explain
const xanadu::exception::_Elem* xanadu::exception::explain() const noexcept
{
	if(this->_memory_address)
	{
		return this->_memory_address;
	}
	else
	{
		return u8"unknown";
	}
}





// [std] range_error
std::range_error xanadu::exception::range_error() noexcept
{
	return std::range_error("range_error");
}

// [std] range_error
std::range_error xanadu::exception::range_error(const char* _Message) noexcept
{
	return std::range_error(_Message ? _Message : "null");
}

// [std] range_error
std::range_error xanadu::exception::range_error(const std::string& _Message) noexcept
{
	return std::range_error(_Message.empty() ? "null" : _Message);
}

// [std] range_error
std::range_error xanadu::exception::range_error(const xanadu::string& _Message) noexcept
{
	return std::range_error(_Message.empty() ? "null" : _Message.data());
}
