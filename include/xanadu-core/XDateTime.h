#ifndef			_XANADU_CORE_DATETIME_H_
#define			_XANADU_CORE_DATETIME_H_

#include <xanadu-core/header.h>
#include <xanadu-core/XTime.h>
#include <xanadu-core/XTimeZone.h>

// 日期时间操作
class _XCOREAPI_ XDateTime
{
private:
	XTime						_info_datetime;

public:
	// constructors
	XDateTime() noexcept;

	// constructors
	XDateTime(const XDateTime& _Info) noexcept;

	// destructor
	virtual ~XDateTime() noexcept;

public:
	// override operator =
	XDateTime& operator = (const XDateTime& _Other);

public:
	// currentDateTime
	static XDateTime currentDateTime(const XTimeZone& _TimeZone = XTimeZone::UTC) noexcept;

	// currentMillisecond
	static std::int64_t currentMillisecond(const XTimeZone& _TimeZone = XTimeZone::UTC) noexcept;

	// currentSecond
	static std::int64_t currentSecond(const XTimeZone& _TimeZone = XTimeZone::UTC) noexcept;

	// fromMillisecond
	static XDateTime fromMillisecond(std::int64_t _Millisecond, const XTimeZone& _TimeZone = XTimeZone::UTC) noexcept;

	// fromSecond
	static XDateTime fromSecond(std::int64_t _Second, const XTimeZone& _TimeZone = XTimeZone::UTC) noexcept;

public:
	// currentDateTimeUtc
	static XDateTime currentDateTimeUtc() noexcept;

	// currentMillisecondSinceUtc
	static std::int64_t currentMillisecondSinceUtc() noexcept;

	// currentSecondSinceUtc
	static std::int64_t currentSecondSinceUtc() noexcept;

	// fromMillisecondSinceUtc
	static XDateTime fromMillisecondSinceUtc(std::int64_t _Millisecond) noexcept;

	// fromSecondSinceUtc
	static XDateTime fromSecondSinceUtc(std::int64_t _Second) noexcept;

public:
	// Second To String (1970-01-01 08:00:00)
	static XString secondToString(std::int64_t _Second) noexcept;

	// Millisecond To String (1970-01-01 08:00:00.000)
	static XString millisecondToString(std::int64_t _Millisecond) noexcept;

	// Current To String (1970-01-01 08:00:00.000)
	static XString currentMillisecondToString() noexcept;
};

#endif
