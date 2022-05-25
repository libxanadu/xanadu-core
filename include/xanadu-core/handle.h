#ifndef			_XANADU_CORE_HANDLE_H_
#define			_XANADU_CORE_HANDLE_H_

#include <xanadu-core/header.h>
#include <xanadu-core/allocator.h>


/// namespace xanadu
namespace x
{
	/// class handle context
	class handle_context
	{
	private:
		unsigned long long		_ReferenceCount;
		void*				_ActualData;

	public:
		// constructors
		handle_context() noexcept;

		// constructors
		handle_context(void* _Object) noexcept; // NOLINT(google-explicit-constructor)

		// destructor
		virtual ~handle_context() noexcept;

	public:
		// [opt] clone
		virtual handle_context* clone() noexcept final;

		// [opt] release
		virtual void release() noexcept final;

	public:
		// [get] data
		virtual void* data() noexcept final;

		// [get] data
		virtual const void* data() const noexcept final;
	};

	/// class handle
	class _XCOREAPI_ handle
	{
	private:
		handle_context*			_Context;

	public:
		// constructors
		handle() noexcept;

		// constructors
		handle(void* _Object) noexcept; // NOLINT(google-explicit-constructor)

		// constructor
		handle(const handle& _Handle) noexcept;

		// constructor
		handle(handle&& _Handle) noexcept;

		// destructor
		virtual ~handle() noexcept;

	public:
		// operator overload =
		handle& operator = (void* _Object) noexcept;

		// operator overload =
		handle& operator = (const handle& _Handle) noexcept;

		// operator overload =
		handle& operator = (handle&& _Handle) noexcept;

	public:
		// operator overload ==
		bool operator == (const void* _Object) const noexcept;

		// operator overload ==
		bool operator == (const handle& _Handle) const noexcept;

		// operator overload !=
		bool operator != (const void* _Object) const noexcept;

		// operator overload !=
		bool operator != (const handle& _Handle) const noexcept;

	public:
		// [get] exist
		virtual bool exist() const noexcept final;

		// [get] empty
		virtual bool empty() const noexcept final;

		// [get] data
		virtual void* data() noexcept final;

		// [get] data
		virtual const void* data() const noexcept final;

	public:
		// [opt] again
		virtual void again(void* _Object) noexcept final;

		// [opt] clear
		virtual void clear() noexcept final;
	};
}

#endif
