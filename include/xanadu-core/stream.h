#ifndef			_XANADU_CORE_STREAM_H_
#define			_XANADU_CORE_STREAM_H_

#include <xanadu-core/header.h>


/// namespace xanadu
namespace x
{
	/// class stream
	class _XCOREAPI_ stream
	{
	public:
		// constructor
		stream() noexcept;

		// constructor
		stream(const stream& _Other) noexcept;

		// constructor
		stream(stream&& _Other) noexcept;

		// destructor
		virtual ~stream() noexcept;

	public:
		// operator overload =
		stream& operator = (const stream& _Other) noexcept;

		// operator overload =
		stream& operator = (stream&& _Other) noexcept;
	};
}

#endif
