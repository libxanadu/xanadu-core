#ifndef			_XANADU_CORE_ALLOCATOR_H_
#define			_XANADU_CORE_ALLOCATOR_H_

#include <xanadu-core/header.h>


/// class XAllocator
class _XCOREAPI_ XAllocator
{
public:
	using				elem_type = char;
	using				size_type = x_size_t;
	using				pos_type = x_pos_type;

public:
	static const pos_type		npos = static_cast<pos_type>(-1);

private:
	static const size_type		redundancy;
	static const size_type		minimum_capacity;

private:
	elem_type*			_memory_address;
	size_type			_memory_length;
	size_type			_memory_capacity;

public:
	// constructor
	XAllocator() noexcept;

	// constructor
	XAllocator(size_type _Length, int _Char) noexcept;

	// constructor
	XAllocator(const void* _Memory, size_type _Length) noexcept;

	// constructor
	XAllocator(const XAllocator& _Allocator) noexcept;

	// constructor
	XAllocator(XAllocator&& _Allocator) noexcept;

	// destructor
	virtual ~XAllocator() noexcept;

public:
	// operator overload =
	XAllocator& operator = (const XAllocator& _Allocator) noexcept;

	// operator overload =
	XAllocator& operator = (XAllocator&& _Allocator) noexcept;

public:
	// operator overload +
	XAllocator operator + (const XAllocator& _Allocator) noexcept;

public:
	// operator overload +=
	XAllocator& operator += (const XAllocator& _Allocator) noexcept;

public:
	// operator overload []
	elem_type& operator [] (pos_type _Index);

	// operator overload []
	elem_type operator [] (pos_type _Index) const;

public:
	// [opt] capacity from length
	static size_type capacity_from_length(size_type _Length) noexcept;

public:
	// [opt] malloc
	virtual bool malloc(size_type _Length) noexcept final;

	// [opt] clear
	virtual void clear() noexcept final;

	// [opt] resize
	virtual bool resize(size_type _Length) noexcept final;

	// [opt] reverse
	virtual bool reverse(size_type _Length) noexcept final;

	// [opt] free
	virtual void free() noexcept final;

public:
	// [get] exist
	virtual bool exist() const noexcept final;

	// [get] empty
	virtual bool empty() const noexcept final;

	// [get] data
	virtual void* data() noexcept final;

	// [get] data
	virtual const void* data() const noexcept final;

	// [get] size
	virtual size_type size() const noexcept final;

	// [get] capacity
	virtual size_type capacity() const noexcept final;

	// [get] surplus
	virtual size_type surplus() const noexcept final;

	// [get] max_size
	virtual size_type max_size() const noexcept final;

public:
	// [opt] prepend
	virtual bool prepend(const void* _Memory, size_type _Length) noexcept final;

	// [opt] prepend
	virtual bool prepend(const XAllocator& _Allocator) noexcept final;

public:
	// [opt] append
	virtual bool append(const void* _Memory, size_type _Length) noexcept final;

	// [opt] append
	virtual bool append(const XAllocator& _Allocator) noexcept final;

public:
	// [opt] insert
	virtual bool insert(pos_type _Pos, const void* _Memory, size_type _Length) noexcept final;

	// [opt] append
	virtual bool insert(pos_type _Pos, const XAllocator& _Allocator) noexcept final;

public:
	// [opt] remove
	virtual bool remove(pos_type _Pos, size_type _Length) noexcept final;

public:
	// [opt] replace
	virtual bool replace(size_type _Pos, size_type _Length, const void* _After, size_type _LengthA) noexcept final;

	// [opt] replace
	virtual bool replace(size_type _Pos, size_type _Length, const XAllocator& _After) noexcept final;

public:
	// [opt] compare
	virtual int compare(const void* _Memory, size_type _Length) const noexcept final;

	// [opt] compare
	virtual int compare(const XAllocator& _Allocator) const noexcept final;

public:
	// [opt] find
	virtual pos_type find(const void* _Memory, size_type _Length, pos_type _Pos) const noexcept final;

	// [opt] find
	virtual pos_type find(const XAllocator& _Allocator, pos_type _Pos) const noexcept final;

public:
	// [opt] rfind
	virtual pos_type rfind(const void* _Memory, size_type _Length, pos_type _Pos) const noexcept final;

	// [opt] rfind
	virtual pos_type rfind(const XAllocator& _Allocator, pos_type _Pos) const noexcept final;
};

#endif
