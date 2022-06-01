#include <xanadu-core/XTimeZone.h>



XTimeZone::XTimeZone() noexcept
{
}

XTimeZone::XTimeZone(ENUM_TIME_ZONE _TimeZone) noexcept
{
	this->_info_time_zone = _TimeZone;
}

XTimeZone::XTimeZone(const XTimeZone& _Other) noexcept
{
	this->_info_time_zone = _Other._info_time_zone;
}

XTimeZone::~XTimeZone() noexcept
{
}






XTimeZone& XTimeZone::operator = (ENUM_TIME_ZONE _TimeZone) noexcept
{
	this->_info_time_zone = _TimeZone;
	return *this;
}

XTimeZone& XTimeZone::operator = (const XTimeZone& _Other) noexcept
{
	this->_info_time_zone = _Other._info_time_zone;
	return *this;
}





XTimeZone::ENUM_TIME_ZONE XTimeZone::timeZone() const noexcept
{
	return this->_info_time_zone;
}





std::int64_t XTimeZone::toMillisecond() const noexcept
{
	return this->toSecond() * 1000;
}

std::int64_t XTimeZone::toSecond() const noexcept
{
	auto		vHour = this->_info_time_zone / 100;
	auto		vMinute = this->_info_time_zone % 100;

	if(vHour == 0)
	{
		if(vMinute == 0)
		{
			return 0;
		}
		else if(vMinute > 0)
		{
			return vMinute * XANADU_TIME_MINUTE;
		}
		else
		{
			return -(vMinute * XANADU_TIME_MINUTE);
		}
	}
	else if(vHour > 0)
	{
		return (vHour * XANADU_TIME_HOUR) + (vMinute * XANADU_TIME_MINUTE);
	}
	else
	{
		return -((vHour * XANADU_TIME_HOUR) + (vMinute * XANADU_TIME_MINUTE));
	}
}





std::int64_t XTimeZone::toMillisecond(ENUM_TIME_ZONE _TimeZone) noexcept
{
	return XTimeZone(_TimeZone).toMillisecond();
}

std::int64_t XTimeZone::toSecond(ENUM_TIME_ZONE _TimeZone) noexcept
{
	return XTimeZone(_TimeZone).toSecond();
}
