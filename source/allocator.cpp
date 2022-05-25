#include <xanadu-core/allocator.h>
#include <xanadu-core/exception.h>
#include <cstring>



// static value
const x::allocator::size_type x::allocator::redundancy = 2;
const x::allocator::size_type x::allocator::minimum_capacity = 16;



// constructor
x::allocator::allocator() noexcept
{
	this->_memory_address = nullptr;
	this->_memory_length = 0;
	this->_memory_capacity = 0;

	this->malloc(0);
}

// constructor
x::allocator::allocator(size_type _Length, int _Char) noexcept
{
	this->_memory_address = nullptr;
	this->_memory_length = 0;
	this->_memory_capacity = 0;

	this->malloc(_Length);
	std::memset(this->_memory_address, _Char, this->_memory_length);
}

// constructor
x::allocator::allocator(const raw_type* _Memory, size_type _Length) noexcept
{
	this->_memory_address = nullptr;
	this->_memory_length = 0;
	this->_memory_capacity = 0;

	this->malloc(_Length);
	std::memcpy(this->_memory_address, _Memory, this->_memory_length);
}

// constructor
x::allocator::allocator(const allocator& _Allocator) noexcept
{
	this->_memory_address = nullptr;
	this->_memory_length = 0;
	this->_memory_capacity = 0;

	this->malloc(_Allocator._memory_length);
	std::memcpy(this->_memory_address, _Allocator._memory_address, this->_memory_length);
}

// constructor
x::allocator::allocator(allocator&& _Allocator) noexcept
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
x::allocator::~allocator() noexcept
{
	delete this->_memory_address;
}





// operator overload =
x::allocator& x::allocator::operator = (const allocator& _Allocator) noexcept
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
x::allocator& x::allocator::operator = (allocator&& _Allocator) noexcept
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
x::allocator x::allocator::operator + (const allocator& _Allocator) noexcept
{
	auto		vTemp = *this;
	vTemp += _Allocator;
	return vTemp;
}





// operator overload +=
x::allocator& x::allocator::operator += (const allocator& _Allocator) noexcept
{
	if(this->resize(this->_memory_length + _Allocator._memory_length))
	{
		std::memcpy(this->_memory_address + this->_memory_length, _Allocator._memory_address, _Allocator._memory_length);
	}
	return *this;
}





// operator overload []
x::allocator::elem_type& x::allocator::operator [] (pos_type _Index)
{
	if(this->_memory_length <= _Index)
	{
		throw x::exception::range_error();
	}
	return this->_memory_address[_Index];
}

// operator overload []
x::allocator::elem_type x::allocator::operator [] (pos_type _Index) const
{
	if(this->_memory_length <= _Index)
	{
		throw x::exception::range_error();
	}
	return this->_memory_address[_Index];
}





// [opt] capacity from length
x::allocator::size_type x::allocator::capacity_from_length(size_type _Length) noexcept
{
	x::allocator::size_type	vCapacity = x::allocator::minimum_capacity;
	while((_Length + x::allocator::redundancy) >= vCapacity)
	{
		vCapacity <<= 1;
	};
	return vCapacity;
}





// [opt] malloc
bool x::allocator::malloc(size_type _Length) noexcept
{
	auto		vCapacity = x::allocator::capacity_from_length(_Length);
	auto		vMemory = new(std::nothrow) x::allocator::elem_type [vCapacity];

	if(vMemory == nullptr)
	{
		return false;
	}
	std::memset(vMemory, 0, vCapacity);

	delete this->_memory_address;
	this->_memory_address = vMemory;
	this->_memory_length = _Length;
	this->_memory_capacity = vCapacity - x::allocator::redundancy;

	return true;
}

// [opt] clear
void x::allocator::clear() noexcept
{
	std::memset(this->_memory_address, 0, this->_memory_length);
	this->_memory_length = 0;
}

// [opt] resize
bool x::allocator::resize(size_type _Length) noexcept
{
	auto		vCapacity = x::allocator::capacity_from_length(_Length);
	auto		vMemory = static_cast<x::allocator::elem_type*>(nullptr);

	if(_Length > this->_memory_length)
	{
		if(_Length > this->_memory_capacity)
		{
			vMemory = new(std::nothrow) x::allocator::elem_type [vCapacity];
			if(vMemory == nullptr)
			{
				return false;
			}
			std::memcpy(vMemory, this->_memory_address, this->_memory_length);
			std::memset(vMemory + this->_memory_length, 0, vCapacity - this->_memory_length);

			delete this->_memory_address;
			this->_memory_address = vMemory;
			this->_memory_length = _Length;
			this->_memory_capacity = vCapacity - x::allocator::redundancy;
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
bool x::allocator::reverse(size_type _Length) noexcept
{
	auto		vCapacity = x::allocator::capacity_from_length(_Length);
	auto		vMemory = static_cast<x::allocator::elem_type*>(nullptr);

	if(_Length > this->_memory_capacity)
	{
		vMemory = new(std::nothrow) x::allocator::elem_type [vCapacity];
		if(vMemory == nullptr)
		{
			return false;
		}
		std::memcpy(vMemory, this->_memory_address, this->_memory_length);
		std::memset(vMemory + this->_memory_length, 0, vCapacity - this->_memory_length);

		delete this->_memory_address;
		this->_memory_address = vMemory;
		this->_memory_capacity = vCapacity - x::allocator::redundancy;
	}
	return true;
}

// [opt] free
void x::allocator::free() noexcept
{
	delete this->_memory_address;
	this->_memory_address = nullptr;
	this->_memory_length = 0;
	this->_memory_capacity = 0;
}





// [get] exist
bool x::allocator::exist() const noexcept
{
	return this->_memory_length != 0;
}

// [get] empty
bool x::allocator::empty() const noexcept
{
	return this->_memory_length == 0;
}

// [get] data
x::allocator::raw_type* x::allocator::data() noexcept
{
	return this->_memory_address;
}

// [get] data
const x::allocator::raw_type* x::allocator::data() const noexcept
{
	return this->_memory_address;
}

// [get] size
x::allocator::size_type x::allocator::size() const noexcept
{
	return this->_memory_length;
}

// [get] capacity
x::allocator::size_type x::allocator::capacity() const noexcept
{
	return this->_memory_capacity;
}

// [get] surplus
x::allocator::size_type x::allocator::surplus() const noexcept
{
	return this->_memory_capacity - this->_memory_length;
}

// [get] max_size
x::allocator::size_type x::allocator::max_size() const noexcept
{
	return static_cast<size_type>(-2);
}





// [opt] prepend
bool x::allocator::prepend(const raw_type* _Memory, size_type _Length) noexcept
{
	return this->insert(0, _Memory, _Length);
}

// [opt] prepend
bool x::allocator::prepend(const allocator& _Allocator) noexcept
{
	return this->insert(0, _Allocator);
}





// [opt] append
bool x::allocator::append(const raw_type* _Memory, size_type _Length) noexcept
{
	return this->insert(this->size(), _Memory, _Length);
}

// [opt] append
bool x::allocator::append(const allocator& _Allocator) noexcept
{
	return this->insert(this->size(), _Allocator);
}





// [opt] insert
bool x::allocator::insert(pos_type _Pos, const raw_type* _Memory, size_type _Length) noexcept
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
bool x::allocator::insert(pos_type _Pos, const allocator& _Allocator) noexcept
{
	return this->insert(_Pos, _Allocator.data(), _Allocator.size());
}





// [opt] remove
bool x::allocator::remove(pos_type _Pos, size_type _Length) noexcept
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
bool x::allocator::replace(size_type _Pos, size_type _Length, const raw_type* _After, size_type _LengthA) noexcept
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
bool x::allocator::replace(size_type _Pos, size_type _Length, const allocator& _After) noexcept
{
	return this->replace(_Pos, _Length, _After._memory_address, _After._memory_length);
}





// [opt] compare
int x::allocator::compare(const raw_type* _Memory, size_type _Length) const noexcept
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
int x::allocator::compare(const allocator& _Allocator) const noexcept
{
	return this->compare(_Allocator._memory_address, _Allocator._memory_length);
}




// [opt] find
x::allocator::pos_type x::allocator::find(const raw_type* _Memory, size_type _Length, pos_type _Pos) const noexcept
{
	if(this->_memory_address == _Memory)
	{
		return 0;
	}
	if(this->_memory_length == 0 || _Memory == nullptr || _Length == 0 || _Pos > this->_memory_length  || (this->_memory_length - _Pos) < _Length)
	{
		return x::allocator::npos;
	}

	auto		vCount = this->_memory_length - _Pos - _Length;

	for(x::allocator::pos_type vPos = _Pos; vPos <= vCount; ++vPos)
	{
		if(0 == std::memcmp(this->_memory_address + vPos, _Memory, _Length))
		{
			return vPos;
		}
	}

	return x::allocator::npos;
}

// [opt] find
x::allocator::pos_type x::allocator::find(const allocator& _Allocator, pos_type _Pos) const noexcept
{
	return this->find(_Allocator._memory_address, _Allocator._memory_length, _Pos);
}




// [opt] rfind
x::allocator::pos_type x::allocator::rfind(const raw_type* _Memory, size_type _Length, pos_type _Pos) const noexcept
{
	if(this->_memory_address == _Memory)
	{
		return 0;
	}
	if(this->_memory_length == 0 || _Memory == nullptr || _Length == 0 || _Pos > this->_memory_length  || (this->_memory_length - _Pos) < _Length)
	{
		return x::allocator::npos;
	}

	for(; _Pos >= 0; --_Pos)
	{
		if(0 == std::memcmp(this->_memory_address + _Pos, _Memory, _Length))
		{
			return _Pos;
		}
		if(_Pos == 0)
		{
			break;
		}
	}

	return x::allocator::npos;
}

// [opt] rfind
x::allocator::pos_type x::allocator::rfind(const allocator& _Allocator, pos_type _Pos) const noexcept
{
	return this->rfind(_Allocator._memory_address, _Allocator._memory_length, _Pos);
}
