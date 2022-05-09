#include <xanadu-core/thread.h>



// constructor
xanadu::thread::thread() noexcept = default;

// constructor
xanadu::thread::thread(const thread& _Other) noexcept = default;

// constructor
xanadu::thread::thread(thread&& _Other) noexcept = default;

// destructor
xanadu::thread::~thread() noexcept = default;





// operator overload =
xanadu::thread& xanadu::thread::operator = (const thread& _Other) noexcept = default;

// operator overload =
xanadu::thread& xanadu::thread::operator = (thread&& _Other) noexcept = default;





// 当前线程ID
xanadu::thread::id_type xanadu::thread::current_thread_id() noexcept
{
	return (xanadu::thread::id_type)x_posix_gettid();
}





// 线程休眠 : sleep
unsigned int xanadu::thread::sleep(unsigned int _Seconds) noexcept
{
	return x_posix_sleep(_Seconds);
}

// 线程休眠 : msleep
unsigned int xanadu::thread::msleep(unsigned int _Milliseconds) noexcept
{
	return x_posix_msleep(_Milliseconds);
}

// 线程休眠 : usleep
unsigned int xanadu::thread::usleep(unsigned int _Microseconds) noexcept
{
	return x_posix_usleep(_Microseconds);
}
