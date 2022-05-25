#include <xanadu-core/thread.h>



// constructor
x::thread::thread() noexcept = default;

// constructor
x::thread::thread(const thread& _Other) noexcept = default;

// constructor
x::thread::thread(thread&& _Other) noexcept = default;

// destructor
x::thread::~thread() noexcept = default;





// operator overload =
x::thread& x::thread::operator = (const thread& _Other) noexcept = default;

// operator overload =
x::thread& x::thread::operator = (thread&& _Other) noexcept = default;





// 当前线程ID
x::thread::id_type x::thread::current_thread_id() noexcept
{
	return (x::thread::id_type)x_posix_gettid();
}





// 线程休眠 : sleep
unsigned int x::thread::sleep(unsigned int _Seconds) noexcept
{
	return x_posix_sleep(_Seconds);
}

// 线程休眠 : msleep
unsigned int x::thread::msleep(unsigned int _Milliseconds) noexcept
{
	return x_posix_msleep(_Milliseconds);
}

// 线程休眠 : usleep
unsigned int x::thread::usleep(unsigned int _Microseconds) noexcept
{
	return x_posix_usleep(_Microseconds);
}
