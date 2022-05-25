#include <xanadu-core/handle.h>


// constructors
x::handle_context::handle_context() noexcept
{
	this->_ReferenceCount = 1;
	this->_ActualData = nullptr;
}

// constructors
x::handle_context::handle_context(void* _Object) noexcept
{
	this->_ReferenceCount = 1;
	this->_ActualData = _Object;
}

// destructor
x::handle_context::~handle_context() noexcept
{
	this->_ReferenceCount = 0;
	this->_ActualData = nullptr;
}





// [opt] clone
x::handle_context* x::handle_context::clone() noexcept
{
	++this->_ReferenceCount;
	return this;
}

// [opt] release
void x::handle_context::release() noexcept
{
	--this->_ReferenceCount;
	if(this->_ReferenceCount == 0)
	{
		delete this;
	}
}





// [get] data
void* x::handle_context::data() noexcept
{
	return this->_ActualData;
}

// [get] data
const void* x::handle_context::data() const noexcept
{
	return this->_ActualData;
}





// constructors
x::handle::handle() noexcept
{
	this->_Context = new(std::nothrow) x::handle_context();
}

// constructors
x::handle::handle(void* _Object) noexcept
{
	this->_Context = new(std::nothrow) x::handle_context(_Object);
}

// constructor
x::handle::handle(const handle& _Handle) noexcept
{
	this->_Context = _Handle._Context->clone();
}

// constructor
x::handle::handle(handle&& _Handle) noexcept
{
	this->_Context = _Handle._Context->clone();
}

// destructor
x::handle::~handle() noexcept
{
	this->_Context->release();
	this->_Context = nullptr;
}





// operator overload =
x::handle& x::handle::operator = (void* _Object) noexcept
{
	this->_Context->release();
	this->_Context = new(std::nothrow) x::handle_context(_Object);
	return *this;
}

// operator overload =
x::handle& x::handle::operator = (const handle& _Handle) noexcept
{
	if(this != &_Handle)
	{
		this->_Context->release();
		this->_Context = _Handle._Context->clone();
	}
	return *this;
}

// operator overload =
x::handle& x::handle::operator = (handle&& _Handle) noexcept
{
	if(this != &_Handle)
	{
		this->_Context->release();
		this->_Context = _Handle._Context->clone();
	}
	return *this;
}





// operator overload ==
bool x::handle::operator == (const void* _Object) const noexcept
{
	return this->_Context->data() == _Object;
}

// operator overload ==
bool x::handle::operator == (const handle& _Handle) const noexcept
{
	return this->_Context == _Handle._Context;
}

// operator overload !=
bool x::handle::operator != (const void* _Object) const noexcept
{
	return this->_Context->data() != _Object;
}

// operator overload !=
bool x::handle::operator != (const handle& _Handle) const noexcept
{
	return this->_Context != _Handle._Context;
}





// [get] exist
bool x::handle::exist() const noexcept
{
	return this->_Context->data();
}

// [get] empty
bool x::handle::empty() const noexcept
{
	return this->_Context->data() == nullptr;
}

// [get] data
void* x::handle::data() noexcept
{
	return this->_Context->data();
}

// [get] data
const void* x::handle::data() const noexcept
{
	return this->_Context->data();
}





// [opt] again
void x::handle::again(void* _Object) noexcept
{
	this->_Context->release();
	this->_Context = new(std::nothrow) x::handle_context(_Object);
}

// [opt] clear
void x::handle::clear() noexcept
{
	this->_Context->release();
	this->_Context = new(std::nothrow) x::handle_context();
}
