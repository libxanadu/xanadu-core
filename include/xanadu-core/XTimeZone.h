#ifndef			_XANADU_CORE_TIME_ZONE_H_
#define			_XANADU_CORE_TIME_ZONE_H_

#include <xanadu-core/header.h>
#include <xanadu-core/XTime.h>


// 时区
class _XCOREAPI_ XTimeZone
{
public:
	// http://www.loglogo.com/front/countryCode/
	enum ENUM_TIME_ZONE
	{
		UTC = 0,			// 默认为UTC >> 0:00
		A0000 = UTC,			// +00:00
		A0100 = 100,			// +01:00
		A0200 = 200,			// +02:00
		A0300 = 300,			// +03:00
		A0400 = 400,			// +04:00
		A0500 = 500,			// +05:00
		A0600 = 600,			// +06:00
		A0700 = 700,			// +07:00
		A0800 = 800,			// +08:00
		A0900 = 900,			// +09:00
		A1000 = 1000,			// +10:00
		A1100 = 1100,			// +11:00
		A1200 = 1200,			// +12:00
		S0000 = UTC,			// -00:00
		S0100 = -100,			// -01:00
		S0200 = -200,			// -02:00
		S0300 = -300,			// -03:00
		S0400 = -400,			// -04:00
		S0500 = -500,			// -05:00
		S0600 = -600,			// -06:00
		S0700 = -700,			// -07:00
		S0800 = -800,			// -08:00
		S0900 = -900,			// -09:00
		S1000 = -1000,			// -10:00
		S1100 = -1100,			// -11:00
		S1200 = -1200,			// -12:00
		CN = A0800,			// 中国，中华人民共和国
		HK = A0800,			// 中国，香港特别行政区
	};

private:
	ENUM_TIME_ZONE					_info_time_zone;

public:
	XTimeZone() noexcept;

	XTimeZone(ENUM_TIME_ZONE _TimeZone) noexcept;

	XTimeZone(const XTimeZone& _Other) noexcept;

	virtual ~XTimeZone() noexcept;

public:
	virtual XTimeZone& operator = (ENUM_TIME_ZONE _TimeZone) noexcept;

	virtual XTimeZone& operator = (const XTimeZone& _Other) noexcept;

public:
	virtual ENUM_TIME_ZONE timeZone() const noexcept;

public:
	virtual std::int64_t toMillisecond() const noexcept;

	virtual std::int64_t toSecond() const noexcept;

public:
	static std::int64_t toMillisecond(ENUM_TIME_ZONE _TimeZone) noexcept;

	static std::int64_t toSecond(ENUM_TIME_ZONE _TimeZone) noexcept;
};

#endif
