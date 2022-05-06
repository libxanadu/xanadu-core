#include <xanadu-core/date_time.h>
#if defined(XANADU_SYSTEM_ANDROID)
#include <sys/time.h>
#else
#include <sys/timeb.h>
#endif


// 月份天数表
static const xanadu::time_regular::value_type		_xanadu_time_regular_month[13] =
	{
		0,
		xanadu::time_regular::day_month_1,
		xanadu::time_regular::day_month_2,
		xanadu::time_regular::day_month_3,
		xanadu::time_regular::day_month_4,
		xanadu::time_regular::day_month_5,
		xanadu::time_regular::day_month_6,
		xanadu::time_regular::day_month_7,
		xanadu::time_regular::day_month_8,
		xanadu::time_regular::day_month_9,
		xanadu::time_regular::day_month_10,
		xanadu::time_regular::day_month_11,
		xanadu::time_regular::day_month_12
	};



// constructor
xanadu::date_time::date_time() noexcept
{
	this->_time_year = xanadu::time_regular::utc_year;
	this->_time_month = xanadu::time_regular::min_month;
	this->_time_day = xanadu::time_regular::min_day;
	this->_time_hour = xanadu::time_regular::min_hour;
	this->_time_minute = xanadu::time_regular::min_minute;
	this->_time_second = xanadu::time_regular::min_second;
	this->_time_millisecond = xanadu::time_regular::min_millisecond;
}

// constructor
xanadu::date_time::date_time(const date_time& _Other) noexcept = default;

// constructor
xanadu::date_time::date_time(date_time&& _Other) noexcept = default;

// destructor
xanadu::date_time::~date_time() noexcept = default;





// operators overload =
xanadu::date_time& xanadu::date_time::operator = (const date_time& _Other) noexcept = default;

// operators overload =
xanadu::date_time& xanadu::date_time::operator = (date_time&& _Other) noexcept = default;





// [get] 当前秒数
xanadu::date_time::value_type xanadu::date_time::current_second() noexcept
{
	return xanadu::date_time::current_second(xanadu::time_zone::UTC);
}

// [get] 当前秒数
xanadu::date_time::value_type xanadu::date_time::current_second(time_zone _TimeZone) noexcept
{
	return xanadu::date_time::current_millisecond(_TimeZone) / xanadu::time_regular::switch_sec;
}

// [get] 当前毫秒数
xanadu::date_time::value_type xanadu::date_time::current_millisecond() noexcept
{
	return xanadu::date_time::current_millisecond(xanadu::time_zone::UTC);
}

// [get] 当前毫秒数
xanadu::date_time::value_type xanadu::date_time::current_millisecond(time_zone _TimeZone) noexcept
{
	XANADU_UNUSED(_TimeZone);
#if defined(XANADU_SYSTEM_ANDROID)
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
#else
	struct timeb		vRawTime{};
	ftime(&vRawTime);
	return vRawTime.time * xanadu::time_regular::switch_sec + vRawTime.millitm;
#endif
}





// 年份是否闰年
bool xanadu::date_time::year_is_leap(value_type _Year) noexcept
{
	return ((_Year % 4) == 0 && (_Year % 100) != 0) || (_Year % 400) == 0;
}





// 修正年份 xanadu::time_regular::min_year - xanadu::time_regular::max_year
xanadu::date_time::value_type xanadu::date_time::revise_year(value_type _Year) noexcept
{
	if(xanadu::time_regular::min_year > _Year)
	{
		_Year = xanadu::time_regular::min_year;
	}
	else if(_Year > xanadu::time_regular::max_year)
	{
		_Year = xanadu::time_regular::max_year;
	}
	return _Year;
}

// 修正月份 xanadu::time_regular::min_month - xanadu::time_regular::max_month
xanadu::date_time::value_type xanadu::date_time::revise_month(value_type _Month) noexcept
{
	if(xanadu::time_regular::min_month > _Month)
	{
		_Month = xanadu::time_regular::min_month;
	}
	else if(_Month > xanadu::time_regular::max_month)
	{
		_Month = xanadu::time_regular::max_month;
	}
	return _Month;
}

// 修正天数 xanadu::time_regular::min_day - xanadu::time_regular::max_day
xanadu::date_time::value_type xanadu::date_time::revise_day(value_type _Day) noexcept
{
	if(xanadu::time_regular::min_day > _Day)
	{
		_Day = xanadu::time_regular::min_day;
	}
	else if(_Day > xanadu::time_regular::max_day)
	{
		_Day = xanadu::time_regular::max_day;
	}
	return _Day;
}

// 修正小时 xanadu::time_regular::min_hour - xanadu::time_regular::max_hour
xanadu::date_time::value_type xanadu::date_time::revise_hour(value_type _Hour) noexcept
{
	if(xanadu::time_regular::min_hour > _Hour)
	{
		_Hour = xanadu::time_regular::min_hour;
	}
	else if(_Hour > xanadu::time_regular::max_hour)
	{
		_Hour = xanadu::time_regular::max_hour;
	}
	return _Hour;
}

// 修正分钟 xanadu::time_regular::min_minute - xanadu::time_regular::max_minute
xanadu::date_time::value_type xanadu::date_time::revise_minute(value_type _Minute) noexcept
{
	if(xanadu::time_regular::min_minute > _Minute)
	{
		_Minute = xanadu::time_regular::min_minute;
	}
	else if(_Minute > xanadu::time_regular::max_minute)
	{
		_Minute = xanadu::time_regular::max_minute;
	}
	return _Minute;
}

// 修正秒数 xanadu::time_regular::min_second - xanadu::time_regular::max_second
xanadu::date_time::value_type xanadu::date_time::revise_second(value_type _Second) noexcept
{
	if(xanadu::time_regular::min_second > _Second)
	{
		_Second = xanadu::time_regular::min_second;
	}
	else if(_Second > xanadu::time_regular::max_second)
	{
		_Second = xanadu::time_regular::max_second;
	}
	return _Second;
}





// 日期转换为毫秒
xanadu::date_time::value_type xanadu::date_time::data_to_millisecond(value_type _Year) noexcept
{
	value_type	vMillisecond = 0;
	_Year = xanadu::date_time::revise_year(_Year);
	if(_Year >= xanadu::time_regular::utc_year)
	{
		for(value_type vIndex = xanadu::time_regular::utc_year; vIndex <= _Year; ++vIndex)
		{
			vMillisecond += (xanadu::date_time::year_is_leap(vIndex) ? xanadu::time_regular::msec_leap_year : xanadu::time_regular::msec_year);
		}
	}
	else
	{
		for(value_type vIndex = xanadu::time_regular::utc_year; vIndex > _Year; --vIndex)
		{
			vMillisecond -= (xanadu::date_time::year_is_leap(vIndex) ? xanadu::time_regular::msec_leap_year : xanadu::time_regular::msec_year);
		}
	}
	return vMillisecond;
}

// 日期转换为毫秒
xanadu::date_time::value_type xanadu::date_time::data_to_millisecond(value_type _Year, value_type _Month) noexcept
{
	auto 		vFrontMS = xanadu::date_time::data_to_millisecond(_Year);
	_Month = xanadu::date_time::revise_month(_Month);
	for(value_type vIndex = xanadu::time_regular::min_month; vIndex <= _Month; ++vIndex)
	{
		vFrontMS += (_xanadu_time_regular_month[vIndex] * xanadu::time_regular::msec_day);
	}
	if(_Month >= 2 && xanadu::date_time::year_is_leap(_Year))
	{
		vFrontMS += xanadu::time_regular::msec_day;
	}
	return vFrontMS;
}

// 日期转换为毫秒
xanadu::date_time::value_type xanadu::date_time::data_to_millisecond(value_type _Year, value_type _Month, value_type _Day) noexcept
{
	auto 		vFrontMS = xanadu::date_time::data_to_millisecond(_Year, _Month);
	vFrontMS += (xanadu::date_time::revise_day(_Day) * xanadu::time_regular::msec_day);
	return vFrontMS;
}

// 日期转换为毫秒
xanadu::date_time::value_type xanadu::date_time::data_to_millisecond(value_type _Year, value_type _Month, value_type _Day, value_type _Hour) noexcept
{
	auto 		vFrontMS = xanadu::date_time::data_to_millisecond(_Year, _Month, _Day);
	vFrontMS += (xanadu::date_time::revise_hour(_Hour) * xanadu::time_regular::msec_hour);
	return vFrontMS;
}

// 日期转换为毫秒
xanadu::date_time::value_type xanadu::date_time::data_to_millisecond(value_type _Year, value_type _Month, value_type _Day, value_type _Hour, value_type _Minute) noexcept
{
	auto 		vFrontMS = xanadu::date_time::data_to_millisecond(_Year, _Month, _Day, _Hour);
	vFrontMS += (xanadu::date_time::revise_minute(_Minute) * xanadu::time_regular::msec_minute);
	return vFrontMS;
}

// 日期转换为毫秒
xanadu::date_time::value_type xanadu::date_time::data_to_millisecond(value_type _Year, value_type _Month, value_type _Day, value_type _Hour, value_type _Minute, value_type _Second) noexcept
{
	auto 		vFrontMS = xanadu::date_time::data_to_millisecond(_Year, _Month, _Day, _Hour, _Minute);
	vFrontMS += (xanadu::date_time::revise_second(_Second) * xanadu::time_regular::switch_sec);
	return vFrontMS;
}





// 秒转换为日期
xanadu::date_time xanadu::date_time::from_second(value_type _Second) noexcept
{
	xanadu::date_time		vDataTime;

	std::time_t		vSecond = _Second;
	std::tm*		vGM = std::gmtime(&vSecond);

	vDataTime._time_year = vGM->tm_year + 1900;
	vDataTime._time_month = vGM->tm_mon + 1;
	vDataTime._time_day = vGM->tm_mday;
	vDataTime._time_hour = vGM->tm_hour;
	vDataTime._time_minute = vGM->tm_min;
	vDataTime._time_second = vGM->tm_sec;
	vDataTime._time_millisecond = 0;

	return vDataTime;
}

// 毫秒转换为日期
xanadu::date_time xanadu::date_time::from_millisecond(value_type _Millisecond) noexcept
{
	auto 		vDataTime = xanadu::date_time::from_second(_Millisecond / xanadu::time_regular::switch_sec);
	vDataTime._time_millisecond = _Millisecond % xanadu::time_regular::switch_sec;
	return vDataTime;
}





// [get] 年份
xanadu::date_time::value_type xanadu::date_time::year() const noexcept
{
	return this->_time_year;
}

// [get] 月份
xanadu::date_time::value_type xanadu::date_time::month() const noexcept
{
	return this->_time_month;
}

// [get] 天数
xanadu::date_time::value_type xanadu::date_time::day() const noexcept
{
	return this->_time_day;
}

// [get] 小时
xanadu::date_time::value_type xanadu::date_time::hour() const noexcept
{
	return this->_time_hour;
}

// [get] 分钟
xanadu::date_time::value_type xanadu::date_time::minute() const noexcept
{
	return this->_time_minute;
}

// [get] 秒
xanadu::date_time::value_type xanadu::date_time::second() const noexcept
{
	return this->_time_second;
}

// [get] 毫秒
xanadu::date_time::value_type xanadu::date_time::millisecond() const noexcept
{
	return this->_time_millisecond;
}
