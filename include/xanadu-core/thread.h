#ifndef			_XANADU_CORE_THREAD_H_
#define			_XANADU_CORE_THREAD_H_

#include <xanadu-core/header.h>


/// namespace xanadu
namespace x
{
	/// class thread
	class _XCOREAPI_ thread
	{
	public:
		using id_type			= x::uint64_t;

	public:
		// constructor
		thread() noexcept;

		// constructor
		thread(const thread& _Other) noexcept;

		// constructor
		thread(thread&& _Other) noexcept;

		// destructor
		virtual ~thread() noexcept;

	public:
		// operator overload =
		thread& operator = (const thread& _Other) noexcept;

		// operator overload =
		thread& operator = (thread&& _Other) noexcept;

	public:
		// 当前线程ID
		static id_type current_thread_id() noexcept;

	public:
		// 线程休眠 : sleep
		static unsigned int sleep(unsigned int _Seconds) noexcept;

		// 线程休眠 : msleep
		static unsigned int msleep(unsigned int _Milliseconds) noexcept;

		// 线程休眠 : usleep
		static unsigned int usleep(unsigned int _Microseconds) noexcept;
	};
}


#endif
