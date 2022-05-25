#include <xanadu-core/mutex.h>



// constructor
x::mutex::mutex() noexcept
{
	this->_mutex_mode = mutex_mode::non_recursive;
	this->_mutex_handle = x::mutex::mutex_create(this->_mutex_mode);
}

// constructor
x::mutex::mutex(mutex_mode _Mode) noexcept
{
	this->_mutex_mode = _Mode;
	this->_mutex_handle = x::mutex::mutex_create(this->_mutex_mode);
}

// destructor
x::mutex::~mutex() noexcept
{
	x::mutex::mutex_destroy(this->_mutex_handle);
	this->_mutex_handle = nullptr;
}





// operator overload =
x::mutex& x::mutex::operator = (const mutex& _Mutex) noexcept = default;

// operator overload =
x::mutex& x::mutex::operator = (mutex&& _Mutex) noexcept = default;





// 锁的模式
x::mutex::mutex_mode x::mutex::mode() const noexcept
{
	return this->_mutex_mode;
}

// 是否成功初始化
bool x::mutex::is_init() const noexcept
{
	return this->_mutex_handle;
}





// 锁定
void x::mutex::lock() noexcept
{
	x::mutex::mutex_lock(this->_mutex_handle);
}

// 尝试锁定
bool x::mutex::trylock() noexcept
{
	return x::mutex::mutex_trylock(this->_mutex_handle);
}

// 解锁
void x::mutex::unlock() noexcept
{
	x::mutex::mutex_unlock(this->_mutex_handle);
}





// [static] 创建互斥锁
x::mutex::mutex_handle x::mutex::mutex_create() noexcept
{
	return x::mutex::mutex_create(x::mutex::mutex_mode::non_recursive);
}

// [static] 创建互斥锁
x::mutex::mutex_handle x::mutex::mutex_create(mutex_mode _Mode) noexcept
{
#if defined(XANADU_SYSTEM_WINDOWS)
	XANADU_UNUSED(_Mode);

	auto		vHandle = new(std::nothrow) CRITICAL_SECTION;
	InitializeCriticalSection(vHandle);
#else
	auto		vHandle = new(std::nothrow) pthread_mutex_t;
	switch(_Mode)
	{
		case x::mutex::mutex_mode::recursive:
			{
				pthread_mutexattr_t	vAttr;
				pthread_mutexattr_init(&vAttr);
				pthread_mutexattr_settype(&vAttr, PTHREAD_MUTEX_RECURSIVE);
				pthread_mutex_init(vHandle, &vAttr);
			}
			break;
		default:
			pthread_mutex_init(vHandle, nullptr);
			break;
	}
#endif
	return static_cast<x::mutex::mutex_handle>(vHandle);
}

// [static] 锁定互斥锁
void x::mutex::mutex_lock(mutex_handle _Handle) noexcept
{
	if(_Handle == nullptr)
	{
		return;
	}

#if defined(XANADU_SYSTEM_WINDOWS)
	EnterCriticalSection(static_cast<CRITICAL_SECTION*>(_Handle));
#else
	pthread_mutex_lock(static_cast<pthread_mutex_t*>(_Handle));
#endif
}

// [static] 尝试锁定互斥锁
bool x::mutex::mutex_trylock(mutex_handle _Handle) noexcept
{
	if(_Handle == nullptr)
	{
		return false;
	}

#if defined(XANADU_SYSTEM_WINDOWS)
	return TryEnterCriticalSection(static_cast<CRITICAL_SECTION*>(_Handle));
#else
	return pthread_mutex_trylock(static_cast<pthread_mutex_t*>(_Handle)) == 0;
#endif
}

// [static] 解锁互斥锁
void x::mutex::mutex_unlock(mutex_handle _Handle) noexcept
{
	if(_Handle == nullptr)
	{
		return;
	}

#if defined(XANADU_SYSTEM_WINDOWS)
	LeaveCriticalSection(static_cast<CRITICAL_SECTION*>(_Handle));
#else
	pthread_mutex_unlock(static_cast<pthread_mutex_t*>(_Handle));
#endif
}

// [static] 销毁互斥锁
void x::mutex::mutex_destroy(mutex_handle _Handle) noexcept
{
	if(_Handle == nullptr)
	{
		return;
	}

#if defined(XANADU_SYSTEM_WINDOWS)
	auto		vMutex = static_cast<CRITICAL_SECTION*>(_Handle);
	DeleteCriticalSection(vMutex);
#else
	auto		vMutex = static_cast<pthread_mutex_t*>(_Handle);
	pthread_mutex_destroy(vMutex);
#endif
	delete vMutex;
}





// constructor
x::auto_mutex::auto_mutex(x::mutex& _Mutex) noexcept : _mutex_ref(_Mutex)
{
	this->_mutex_ref.lock();
}

// destructor
x::auto_mutex::~auto_mutex() noexcept
{
	this->_mutex_ref.unlock();
}
