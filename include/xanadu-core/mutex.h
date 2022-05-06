#ifndef			_XANADU_CORE_MUTEX_H_
#define			_XANADU_CORE_MUTEX_H_

#include <xanadu-core/header.h>


/// namespace xanadu
namespace xanadu
{
	/// class mutex
	class _XCOREAPI_ mutex
	{
	public:
		typedef enum class mutex_mode
		{
			recursive			= 0,
			non_recursive			= 1
		}mutex_mode;

	public:
		using				mutex_handle = void*;

	public:
		mutex_handle			_mutex_handle;
		mutex_mode			_mutex_mode;

	public:
		// constructor
		mutex() noexcept;

		// constructor
		explicit mutex(mutex_mode _Mode) noexcept;

		// destructor
		virtual ~mutex() noexcept;

	private:
		// operator overload =
		mutex& operator = (const mutex& _Mutex) noexcept;

		// operator overload =
		mutex& operator = (mutex&& _Mutex) noexcept;

	public:
		// 锁的模式
		virtual mutex_mode mode() const noexcept final;

		// 是否成功初始化
		virtual bool is_init() const noexcept final;

	public:
		// 锁定
		virtual void lock() noexcept final;

		// 尝试锁定
		virtual bool trylock() noexcept final;

		// 解锁
		virtual void unlock() noexcept final;

	public:
		// [static] 创建互斥锁
		static mutex_handle mutex_create() noexcept;

		// [static] 创建互斥锁
		static mutex_handle mutex_create(mutex_mode _Mode) noexcept;

		// [static] 锁定互斥锁
		static void mutex_lock(mutex_handle _Handle) noexcept;

		// [static] 尝试锁定互斥锁
		static bool mutex_trylock(mutex_handle _Handle) noexcept;

		// [static] 解锁互斥锁
		static void mutex_unlock(mutex_handle _Handle) noexcept;

		// [static] 销毁互斥锁
		static void mutex_destroy(mutex_handle _Handle) noexcept;
	};
}


/// namespace xanadu
namespace xanadu
{
	/// class mutex
	class _XCOREAPI_ auto_mutex
	{
	private:
		xanadu::mutex&			_mutex_ref;

	public:
		// constructor
		explicit auto_mutex(xanadu::mutex& _Mutex) noexcept;

		// destructor
		virtual ~auto_mutex() noexcept;
	};
}


// 一些方便调用互斥锁的宏
#define				XANADU_MUTEX_AUTO(_Mutex)				xanadu::auto_mutex		_xanadu_auto_mutex(_Mutex)
#define				STD_MUTEX_GUARD(_Mutex)				std::lock_guard<std::mutex>	_xanadu_lock_guard(_Mutex)

#endif
