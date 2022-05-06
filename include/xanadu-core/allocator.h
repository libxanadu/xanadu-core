#ifndef			_XANADU_CORE_ALLOCATOR_H_
#define			_XANADU_CORE_ALLOCATOR_H_

#include <xanadu-core/header.h>


/// namespace xanadu
namespace xanadu
{
	/// class allocator
	class _XCOREAPI_ allocator
	{
	public:
		using				_Elem = char;
		using				size_type = xanadu::size_type;
		using				pos_type = xanadu::pos_type;

	public:
		static const pos_type		npos = static_cast<pos_type>(-1);

	private:
		static const size_type		redundancy;
		static const size_type		minimum_capacity;

	private:
		_Elem*				_memory_address;
		size_type			_memory_length;
		size_type			_memory_capacity;

	public:
		// constructor
		allocator() noexcept;

		// constructor
		allocator(size_type _Length, int _Char) noexcept;

		// constructor
		allocator(const void* _Memory, size_type _Length) noexcept;

		// constructor
		allocator(const allocator& _Allocator) noexcept;

		// constructor
		allocator(allocator&& _Allocator) noexcept;

		// destructor
		virtual ~allocator() noexcept;

	public:
		// operator overload =
		allocator& operator = (const allocator& _Allocator) noexcept;

		// operator overload =
		allocator& operator = (allocator&& _Allocator) noexcept;

	public:
		// operator overload +
		allocator operator + (const allocator& _Allocator) noexcept;

	public:
		// operator overload +=
		allocator& operator += (const allocator& _Allocator) noexcept;
		
	public:
		// [opt] operator overload []
		_Elem& operator [] (pos_type _Index);

		// [opt] operator overload []
		_Elem operator [] (pos_type _Index) const;

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
		virtual bool prepend(const allocator& _Allocator) noexcept final;

	public:
		// [opt] append
		virtual bool append(const void* _Memory, size_type _Length) noexcept final;

		// [opt] append
		virtual bool append(const allocator& _Allocator) noexcept final;

	public:
		// [opt] insert
		virtual bool insert(pos_type _Pos, const void* _Memory, size_type _Length) noexcept final;

		// [opt] append
		virtual bool insert(pos_type _Pos, const allocator& _Allocator) noexcept final;

	public:
		// [opt] remove
		virtual bool remove(pos_type _Pos, size_type _Length) noexcept final;

	public:
		// [opt] replace
		virtual bool replace(size_type _Pos, size_type _Length, const _Elem* _After, size_type _LengthA) noexcept final;

		// [opt] replace
		virtual bool replace(size_type _Pos, size_type _Length, const allocator& _After) noexcept final;

	public:
		// [opt] compare
		virtual int compare(const void* _Memory, size_type _Length) const noexcept final;

		// [opt] compare
		virtual int compare(const allocator& _Allocator) const noexcept final;
	};
}

#endif
