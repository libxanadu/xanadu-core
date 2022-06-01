#include <xanadu-core/XDateTime.h>


// constructors
XDateTime::XDateTime() noexcept
{
	this->_info_datetime = XTime::currentTime();
}

// constructors
XDateTime::XDateTime(const XDateTime& _Info) noexcept
{
	this->_info_datetime = _Info._info_datetime;
}

// destructor
XDateTime::~XDateTime() noexcept = default;



// override operator =
XDateTime& XDateTime::operator = (const XDateTime& _Other) = default;



// currentDateTime
XDateTime XDateTime::currentDateTime(const XTimeZone& _TimeZone) noexcept
{
	XANADU_UNUSED(_TimeZone);

	auto		vDateTime = XDateTime();
	vDateTime._info_datetime = XTime::currentTime();
	return vDateTime;
}

// currentMillisecond
std::int64_t XDateTime::currentMillisecond(const XTimeZone& _TimeZone) noexcept
{
	XANADU_UNUSED(_TimeZone);

	return XTime::currentTime().millisecond();
}

// currentSecond
std::int64_t XDateTime::currentSecond(const XTimeZone& _TimeZone) noexcept
{
	XANADU_UNUSED(_TimeZone);

	return XTime::currentTime().second();
}

// fromMillisecond
XDateTime XDateTime::fromMillisecond(std::int64_t _Millisecond, const XTimeZone& _TimeZone) noexcept
{
	XANADU_UNUSED(_TimeZone);

	auto		vDateTime = XDateTime();
	vDateTime._info_datetime = XTime::fromMillisecond(_Millisecond);
	return vDateTime;
}

// fromSecond
XDateTime XDateTime::fromSecond(std::int64_t _Second, const XTimeZone& _TimeZone) noexcept
{
	return XDateTime::fromMillisecond(_Second * 1000, _TimeZone);
}



// currentDateTimeUtc
XDateTime XDateTime::currentDateTimeUtc() noexcept
{
	return XDateTime::currentDateTime(XTimeZone::UTC);
}

// currentMillisecondSinceUtc
std::int64_t XDateTime::currentMillisecondSinceUtc() noexcept
{
	return XDateTime::currentMillisecond(XTimeZone::UTC);
}

// currentSecondSinceUtc
std::int64_t XDateTime::currentSecondSinceUtc() noexcept
{
	return XDateTime::currentSecond(XTimeZone::UTC);
}

// fromMillisecondSinceUtc
XDateTime XDateTime::fromMillisecondSinceUtc(std::int64_t _Millisecond) noexcept
{
	return XDateTime::fromMillisecond(_Millisecond, XTimeZone::UTC);
}

// fromSecondSinceUtc
XDateTime XDateTime::fromSecondSinceUtc(std::int64_t _Second) noexcept
{
	return XDateTime::fromSecond(_Second, XTimeZone::UTC);;
}



// Second To String (1970-01-01 08:00:00)
XString XDateTime::secondToString(std::int64_t _Second) noexcept
{
	auto		vValueSecond = static_cast<time_t>(_Second);
	auto		vTM = localtime(&vValueSecond);
	return XString::format("%04d-%02d-%02d %02d:%02d:%02d", vTM->tm_year + 1900, vTM->tm_mon + 1, vTM->tm_mday, vTM->tm_hour, vTM->tm_min, vTM->tm_sec);
}

// Millisecond To String (1970-01-01 08:00:00.000)
XString XDateTime::millisecondToString(std::int64_t _Millisecond) noexcept
{
	return XDateTime::secondToString(_Millisecond / 1000) + "." + XString::number(_Millisecond % 1000);
}

// Current To String (1970-01-01 08:00:00.000)
XString XDateTime::currentMillisecondToString() noexcept
{
#if defined(XANADU_SYSTEM_WINDOWS)
	SYSTEMTIME		vSystemTime;
	GetSystemTime(&vSystemTime);
	return XString::format("%04d-%02d-%02dT%02d:%02d:%02d.%03dZ", vSystemTime.wYear, vSystemTime.wMonth, vSystemTime.wDay, vSystemTime.wHour, vSystemTime.wMinute, vSystemTime.wSecond, vSystemTime.wMilliseconds);
#else
	struct timespec		vTime;
	clock_gettime(CLOCK_REALTIME, &vTime);
	struct tm		vNowTime;
	localtime_r(&vTime.tv_sec, &vNowTime);
	return XString::format("%04d-%02d-%02dT%02d:%02d:%02d.%06dZ", vNowTime.tm_year + 1900, vNowTime.tm_mon + 1, vNowTime.tm_mday, vNowTime.tm_hour, vNowTime.tm_min, vNowTime.tm_sec, vTime.tv_nsec / 1000);
#endif
}
