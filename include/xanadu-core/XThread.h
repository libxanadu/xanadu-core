#ifndef			_XANADU_CORE_THREAD_H_
#define			_XANADU_CORE_THREAD_H_

#include <xanadu-core/header.h>


/// class XThread
class _XCOREAPI_ XThread
{
public:
	using id_type			= x_ullong_t;

public:
	// constructor
	XThread() noexcept;

private:
	// constructor
	XThread(const XThread& _Other) noexcept;

	// constructor
	XThread(XThread&& _Other) noexcept;

public:
	// destructor
	virtual ~XThread() noexcept;

private:
	// operator overload =
	XThread& operator = (const XThread& _Other) noexcept;

	// operator overload =
	XThread& operator = (XThread&& _Other) noexcept;

public:
	// 当前线程ID
	static id_type currentThreadId() noexcept;

public:
	// 线程休眠 : sleep
	static unsigned int sleep(unsigned int _Seconds) noexcept;

	// 线程休眠 : msleep
	static unsigned int msleep(unsigned int _Milliseconds) noexcept;

	// 线程休眠 : usleep
	static unsigned int usleep(unsigned int _Microseconds) noexcept;

public:
	// Running thread
	virtual void start() noexcept final;

public:
	// Specific execution function of thread
	virtual void run();
};


#endif
