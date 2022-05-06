#include <xanadu-core/allocator.h>
#include <xanadu-core/exception.h>
#include <cstring>



// static value
const xanadu::allocator::size_type xanadu::allocator::redundancy = 2;
const xanadu::allocator::size_type xanadu::allocator::minimum_capacity = 16;



// constructor
xanadu::allocator::allocator() noexcept
{
	this->_memory_address = nullptr;
	this->_memory_length = 0;
	this->_memory_capacity = 0;

	this->malloc(0);
}

// constructor
xanadu::allocator::allocator(size_type _Length, int _Char) noexcept
{
	this->_memory_address = nullptr;
	this->_memory_length = 0;
	this->_memory_capacity = 0;

	this->malloc(_Length);
	std::memset(this->_memory_address, _Char, this->_memory_length);
}

// constructor
xanadu::allocator::allocator(const void* _Memory, size_type _Length) noexcept
{
	this->_memory_address = nullptr;
	this->_memory_length = 0;
	this->_memory_capacity = 0;

	this->malloc(_Length);
	std::memcpy(this->_memory_address, _Memory, this->_memory_length);
}

// constructor
xanadu::allocator::allocator(const allocator& _Allocator) noexcept
{
	this->_memory_address = nullptr;
	this->_memory_length = 0;
	this->_memory_capacity = 0;

	this->malloc(_Allocator._memory_length);
	std::memcpy(this->_memory_address, _Allocator._memory_address, this->_memory_length);
}

// constructor
xanadu::allocator::allocator(allocator&& _Allocator) noexcept
{
	auto		vCapacity = _Allocator._memory_capacity;
	auto		vLength = _Allocator._memory_length;
	auto		vMemory = _Allocator._memory_address;

	this->_memory_address = nullptr;
	this->_memory_length = 0;
	this->_memory_capacity = 0;
	this->malloc(0);

	_Allocator._memory_address = this->_memory_address;
	_Allocator._memory_length = this->_memory_length;
	_Allocator._memory_capacity = this->_memory_capacity;

	this->_memory_address = vMemory;
	this->_memory_length = vLength;
	this->_memory_capacity = vCapacity;
}

// destructor
xanadu::allocator::~allocator() noexcept
{
	delete this->_memory_address;
}





// operator overload =
xanadu::allocator& xanadu::allocator::operator = (const allocator& _Allocator) noexcept
{
	if(this != &_Allocator)
	{
		this->free();
		if(this->malloc(_Allocator.size()))
		{
			std::memcpy(this->_memory_address, _Allocator._memory_address, this->_memory_length);
		}
	}
	return *this;
}

// operator overload =
xanadu::allocator& xanadu::allocator::operator = (allocator&& _Allocator) noexcept
{
	auto		vCapacity = _Allocator._memory_capacity;
	auto		vLength = _Allocator._memory_length;
	auto		vMemory = _Allocator._memory_address;

	if(this != &_Allocator)
	{
		_Allocator._memory_address = this->_memory_address;
		_Allocator._memory_length = this->_memory_length;
		_Allocator._memory_capacity = this->_memory_capacity;

		this->_memory_address = vMemory;
		this->_memory_length = vLength;
		this->_memory_capacity = vCapacity;
	}
	return *this;
}





// operator overload +
xanadu::allocator xanadu::allocator::operator + (const allocator& _Allocator) noexcept
{
	auto		vTemp = *this;
	vTemp += _Allocator;
	return vTemp;
}





// operator overload +=
xanadu::allocator& xanadu::allocator::operator += (const allocator& _Allocator) noexcept
{
	if(this->resize(this->_memory_length + _Allocator._memory_length))
	{
		std::memcpy(this->_memory_address + this->_memory_length, _Allocator._memory_address, _Allocator._memory_length);
	}
	return *this;
}





// [opt] operator overload []
xanadu::allocator::_Elem& xanadu::allocator::operator [] (pos_type _Index)
{
	if(this->_memory_length <= _Index)
	{
		throw xanadu::exception::range_error();
	}
	return this->_memory_address[_Index];
}

// [opt] operator overload []
xanadu::allocator::_Elem xanadu::allocator::operator [] (pos_type _Index) const
{
	if(this->_memory_length <= _Index)
	{
		throw xanadu::exception::range_error();
	}
	return this->_memory_address[_Index];
}





// [opt] capacity from length
xanadu::allocator::size_type xanadu::allocator::capacity_from_length(size_type _Length) noexcept
{
	xanadu::allocator::size_type	vCapacity = xanadu::allocator::minimum_capacity;
	while((_Length + xanadu::allocator::redundancy) >= vCapacity)
	{
		vCapacity <<= 1;
	};
	return vCapacity;
}





// [opt] malloc
bool xanadu::allocator::malloc(size_type _Length) noexcept
{
	auto		vCapacity = xanadu::allocator::capacity_from_length(_Length);
	auto		vMemory = new(std::nothrow) xanadu::allocator::_Elem [vCapacity];

	if(vMemory == nullptr)
	{
		return false;
	}
	std::memset(vMemory, 0, vCapacity);

	delete this->_memory_address;
	this->_memory_address = vMemory;
	this->_memory_length = _Length;
	this->_memory_capacity = vCapacity - xanadu::allocator::redundancy;

	return true;
}

// [opt] clear
void xanadu::allocator::clear() noexcept
{
	std::memset(this->_memory_address, 0, this->_memory_length);
	this->_memory_length = 0;
}

// [opt] resize
bool xanadu::allocator::resize(size_type _Length) noexcept
{
	auto		vCapacity = xanadu::allocator::capacity_from_length(_Length);
	auto		vMemory = static_cast<xanadu::allocator::_Elem*>(nullptr);

	if(_Length > this->_memory_length)
	{
		if(_Length > this->_memory_capacity)
		{
			vMemory = new(std::nothrow) xanadu::allocator::_Elem [vCapacity];
			if(vMemory == nullptr)
			{
				return false;
			}
			std::memcpy(vMemory, this->_memory_address, this->_memory_length);
			std::memset(vMemory + this->_memory_length, 0, vCapacity - this->_memory_length);

			delete this->_memory_address;
			this->_memory_address = vMemory;
			this->_memory_length = _Length;
			this->_memory_capacity = vCapacity - xanadu::allocator::redundancy;
		}
		else
		{
			this->_memory_length = _Length;
		}
	}
	else if(_Length < this->_memory_length)
	{
		std::memset(this->_memory_address + _Length, 0, this->_memory_length - _Length);
		this->_memory_length = _Length;
	}
	return true;
}

// [opt] reverse
bool xanadu::allocator::reverse(size_type _Length) noexcept
{
	auto		vCapacity = xanadu::allocator::capacity_from_length(_Length);
	auto		vMemory = static_cast<xanadu::allocator::_Elem*>(nullptr);

	if(_Length > this->_memory_capacity)
	{
		vMemory = new(std::nothrow) xanadu::allocator::_Elem [vCapacity];
		if(vMemory == nullptr)
		{
			return false;
		}
		std::memcpy(vMemory, this->_memory_address, this->_memory_length);
		std::memset(vMemory + this->_memory_length, 0, vCapacity - this->_memory_length);

		delete this->_memory_address;
		this->_memory_address = vMemory;
		this->_memory_capacity = vCapacity - xanadu::allocator::redundancy;
	}
	return true;
}

// [opt] free
void xanadu::allocator::free() noexcept
{
	delete this->_memory_address;
	this->_memory_address = nullptr;
	this->_memory_length = 0;
	this->_memory_capacity = 0;
}





// [get] exist
bool xanadu::allocator::exist() const noexcept
{
	return this->_memory_length != 0;
}

// [get] empty
bool xanadu::allocator::empty() const noexcept
{
	return this->_memory_length == 0;
}

// [get] data
void* xanadu::allocator::data() noexcept
{
	return this->_memory_address;
}

// [get] data
const void* xanadu::allocator::data() const noexcept
{
	return this->_memory_address;
}

// [get] size
xanadu::allocator::size_type xanadu::allocator::size() const noexcept
{
	return this->_memory_length;
}

// [get] capacity
xanadu::allocator::size_type xanadu::allocator::capacity() const noexcept
{
	return this->_memory_capacity;
}

// [get] surplus
xanadu::allocator::size_type xanadu::allocator::surplus() const noexcept
{
	return this->_memory_capacity - this->_memory_length;
}

// [get] max_size
xanadu::allocator::size_type xanadu::allocator::max_size() const noexcept
{
	return static_cast<size_type>(-2);
}





// [opt] prepend
bool xanadu::allocator::prepend(const void* _Memory, size_type _Length) noexcept
{
	return this->insert(0, _Memory, _Length);
}

// [opt] prepend
bool xanadu::allocator::prepend(const allocator& _Allocator) noexcept
{
	return this->insert(0, _Allocator);
}





// [opt] append
bool xanadu::allocator::append(const void* _Memory, size_type _Length) noexcept
{
	return this->insert(this->size(), _Memory, _Length);
}

// [opt] append
bool xanadu::allocator::append(const allocator& _Allocator) noexcept
{
	return this->insert(this->size(), _Allocator);
}





// [opt] insert
bool xanadu::allocator::insert(pos_type _Pos, const void* _Memory, size_type _Length) noexcept
{
	if(_Memory == nullptr || _Length == 0)
	{
		return false;
	}

	if(this->surplus() < _Length && !this->reverse(this->_memory_length + _Length))
	{
		return false;
	}

	if(_Pos > this->_memory_length)
	{
		_Pos = this->_memory_length;
	}

	std::memmove(this->_memory_address + _Pos + _Length, this->_memory_address + _Pos, this->_memory_length - _Pos);
	std::memcpy(this->_memory_address + _Pos, _Memory, _Length);
	this->_memory_length += _Length;
	return true;
}

// [opt] append
bool xanadu::allocator::insert(pos_type _Pos, const allocator& _Allocator) noexcept
{
	return this->insert(_Pos, _Allocator.data(), _Allocator.size());
}





// [opt] remove
bool xanadu::allocator::remove(pos_type _Pos, size_type _Length) noexcept
{
	if(_Pos >= this->_memory_length)
	{
		return false;
	}

	if(_Length > (this->_memory_length - _Pos))
	{
		_Length = this->_memory_length - _Pos;
	}

	std::memmove(this->_memory_address + _Pos, this->_memory_address + _Pos + _Length, this->_memory_length - _Length);
	std::memset(this->_memory_address + (this->_memory_length - _Length), 0, _Length);
	this->_memory_length -= _Length;
	return true;
}





// [opt] replace
bool xanadu::allocator::replace(size_type _Pos, size_type _Length, const _Elem* _After, size_type _LengthA) noexcept
{
	size_type 	vDifference = 0;

	if(_Length == _LengthA)
	{
		std::memcpy(this->_memory_address + _Pos, _After, _LengthA);
	}
	else if(_Length > _LengthA)
	{
		vDifference = _Length - _LengthA;
		std::memmove(this->_memory_address + _Pos + _LengthA, this->_memory_address + _Pos + _Length, this->_memory_length - _Pos - _Length);
		std::memset(this->_memory_address + this->_memory_length - vDifference, 0, vDifference);
		std::memcpy(this->_memory_address + _Pos, _After, _LengthA);
		this->_memory_length += _LengthA;
		this->_memory_length -= _Length;
	}
	else
	{
		vDifference = _LengthA - _Length;
		if(this->surplus() < vDifference && !this->reverse(this->_memory_length + vDifference))
		{
			return false;
		}
		std::memmove(this->_memory_address + _Pos + _LengthA, this->_memory_address + _Pos + _Length, this->_memory_length - _Pos - _Length);
		std::memcpy(this->_memory_address + _Pos, _After, _LengthA);
		this->_memory_length += _LengthA;
		this->_memory_length -= _Length;
	}
	return true;
}

// [opt] replace
bool xanadu::allocator::replace(size_type _Pos, size_type _Length, const allocator& _After) noexcept
{
	return this->replace(_Pos, _Length, _After._memory_address, _After._memory_length);
}





// [opt] compare
int xanadu::allocator::compare(const void* _Memory, size_type _Length) const noexcept
{
	int		vCompare = 0;

	if (this->_memory_address == _Memory)
	{
		return 0;
	}
	if (this->_memory_address && _Memory)
	{
		if(this->_memory_length == _Length)
		{
			vCompare = std::memcmp(this->_memory_address, _Memory, _Length);
		}
		else if(this->_memory_length > _Length)
		{
			vCompare = std::memcmp(this->_memory_address, _Memory, _Length);
			if(vCompare == 0)
			{
				vCompare = -1;
			}
		}
		else
		{
			vCompare = std::memcmp(this->_memory_address, _Memory, this->_memory_length);
			if(vCompare == 0)
			{
				vCompare = 1;
			}
		}
		return vCompare;
	}
	else if(this->_memory_address)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

// [opt] compare
int xanadu::allocator::compare(const allocator& _Allocator) const noexcept
{
	return this->compare(_Allocator._memory_address, _Allocator._memory_length);
}
