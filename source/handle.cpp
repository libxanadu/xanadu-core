#include <xanadu-core/handle.h>


// constructors
xanadu::handle_context::handle_context() noexcept
{
	this->_ReferenceCount = 1;
	this->_ActualData = nullptr;
}

// constructors
xanadu::handle_context::handle_context(void* _Object) noexcept
{
	this->_ReferenceCount = 1;
	this->_ActualData = _Object;
}

// destructor
xanadu::handle_context::~handle_context() noexcept
{
	this->_ReferenceCount = 0;
	this->_ActualData = nullptr;
}





// [opt] clone
xanadu::handle_context* xanadu::handle_context::clone() noexcept
{
	++this->_ReferenceCount;
	return this;
}

// [opt] release
void xanadu::handle_context::release() noexcept
{
	--this->_ReferenceCount;
	if(this->_ReferenceCount == 0)
	{
		delete this;
	}
}





// [get] data
void* xanadu::handle_context::data() noexcept
{
	return this->_ActualData;
}

// [get] data
const void* xanadu::handle_context::data() const noexcept
{
	return this->_ActualData;
}





// constructors
xanadu::handle::handle() noexcept
{
	this->_Context = new(std::nothrow) xanadu::handle_context();
}

// constructors
xanadu::handle::handle(void* _Object) noexcept
{
	this->_Context = new(std::nothrow) xanadu::handle_context(_Object);
}

// constructor
xanadu::handle::handle(const handle& _Handle) noexcept
{
	this->_Context = _Handle._Context->clone();
}

// constructor
xanadu::handle::handle(handle&& _Handle) noexcept
{
	this->_Context = _Handle._Context->clone();
}

// destructor
xanadu::handle::~handle() noexcept
{
	this->_Context->release();
	this->_Context = nullptr;
}





// operator overload =
xanadu::handle& xanadu::handle::operator = (void* _Object) noexcept
{
	this->_Context->release();
	this->_Context = new(std::nothrow) xanadu::handle_context(_Object);
	return *this;
}

// operator overload =
xanadu::handle& xanadu::handle::operator = (const handle& _Handle) noexcept
{
	if(this != &_Handle)
	{
		this->_Context->release();
		this->_Context = _Handle._Context->clone();
	}
	return *this;
}

// operator overload =
xanadu::handle& xanadu::handle::operator = (handle&& _Handle) noexcept
{
	if(this != &_Handle)
	{
		this->_Context->release();
		this->_Context = _Handle._Context->clone();
	}
	return *this;
}





// operator overload ==
bool xanadu::handle::operator == (const void* _Object) const noexcept
{
	return this->_Context->data() == _Object;
}

// operator overload ==
bool xanadu::handle::operator == (const handle& _Handle) const noexcept
{
	return this->_Context == _Handle._Context;
}

// operator overload !=
bool xanadu::handle::operator != (const void* _Object) const noexcept
{
	return this->_Context->data() != _Object;
}

// operator overload !=
bool xanadu::handle::operator != (const handle& _Handle) const noexcept
{
	return this->_Context != _Handle._Context;
}





// [get] exist
bool xanadu::handle::exist() const noexcept
{
	return this->_Context->data();
}

// [get] empty
bool xanadu::handle::empty() const noexcept
{
	return this->_Context->data() == nullptr;
}

// [get] data
void* xanadu::handle::data() noexcept
{
	return this->_Context->data();
}

// [get] data
const void* xanadu::handle::data() const noexcept
{
	return this->_Context->data();
}





// [opt] again
void xanadu::handle::again(void* _Object) noexcept
{
	this->_Context->release();
	this->_Context = new(std::nothrow) xanadu::handle_context(_Object);
}

// [opt] clear
void xanadu::handle::clear() noexcept
{
	this->_Context->release();
	this->_Context = new(std::nothrow) xanadu::handle_context();
}
