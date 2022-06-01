#ifndef			_XANADU_CORE_TIME_H_
#define			_XANADU_CORE_TIME_H_

#include <xanadu-core/header.h>
#include <xanadu-core/XString.h>
#include <xanadu-core/XTimeZone.h>

#define				XANADU_TIME_MINUTE				(60)				// 一分的秒数
#define				XANADU_TIME_HOUR				(3600)				// 一小时的秒数(XANADU_TIME_MINUTE * 60)
#define				XANADU_TIME_DAY					(86400)				// 一天的秒数(XANADU_TIME_HOUR * 24)
#define				XANADU_TIME_YEAR				(31536000)			// 一年的秒数(XANADU_TIME_DAY * 365)

// 时间操作
class _XCOREAPI_ XTime
{
private:
	// time : init is current
	std::int64_t					_time_millisecond;

public:
	// constructors
	XTime() noexcept;

	// constructors
	XTime(std::uint32_t _Hour, std::uint32_t _Minute, std::uint32_t _Second = 0U, std::uint32_t _Millisecond = 0U) noexcept;

	// constructors
	XTime(const XTime& _Info) noexcept;

	// destructor
	virtual ~XTime() noexcept;

public:
	// override operator =
	XTime& operator = (const XTime& _Other) noexcept;

public:
	// Gets the total number of seconds
	virtual std::int64_t second() const noexcept;

	// Gets the total number of millisecond
	virtual std::int64_t millisecond() const noexcept;

public:
	// Get the current time
	static XTime currentTime() noexcept;

	// Sets the time to the specified number of milliseconds
	static XTime fromMillisecond(std::int64_t _Millisecond) noexcept;

public:
	// 高精度计时开始
	static HANDLE HighPrecisionStart() noexcept;

	// 高精度计时结束
	static std::int64_t HighPrecisionStop(HANDLE _Handle) noexcept;
};

#endif
