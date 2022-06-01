#include <xanadu-core/XThread.h>



// constructor
XThread::XThread() noexcept = default;

// constructor
XThread::XThread(const XThread& _Other) noexcept = default;

// constructor
XThread::XThread(XThread&& _Other) noexcept = default;

// destructor
XThread::~XThread() noexcept = default;





// operator overload =
XThread& XThread::operator = (const XThread& _Other) noexcept = default;

// operator overload =
XThread& XThread::operator = (XThread&& _Other) noexcept = default;





// 当前线程ID
XThread::id_type XThread::currentThreadId() noexcept
{
	return (XThread::id_type)x_posix_gettid();
}





// 线程休眠 : sleep
unsigned int XThread::sleep(unsigned int _Seconds) noexcept
{
	return x_posix_sleep(_Seconds);
}

// 线程休眠 : msleep
unsigned int XThread::msleep(unsigned int _Milliseconds) noexcept
{
	return x_posix_msleep(_Milliseconds);
}

// 线程休眠 : usleep
unsigned int XThread::usleep(unsigned int _Microseconds) noexcept
{
	return x_posix_usleep(_Microseconds);
}





// Running thread
void XThread::start() noexcept
{
	std::thread	vThread(&XThread::run, this);
	vThread.detach();
}





// Specific execution function of thread
void XThread::run()
{
}
