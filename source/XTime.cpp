#include <xanadu-core/XTime.h>


typedef struct _XANADU_TIME_HIGH_PRECISION
{
#if defined(XANADU_SYSTEM_WINDOWS)
	// 开始时间
	LARGE_INTEGER		vBeginTime;

	// 结束时间
	LARGE_INTEGER		vEndTime;

	// CPU时间
	LARGE_INTEGER		vCpuTime;
#else
	// 开始时间
	timeval			vBeginTime;

	// 结束时间
	timeval			vEndTime;
#endif
}XANADU_TIME_HIGH_PRECISION;


std::int64_t currentMillisecondUTC()
{
#if defined(XANADU_SYSTEM_ANDROID)
	/*
	struct timeval	tv{};
	gettimeofday(&tv);
	std::int64_t	vMillisecond = tv.tv_sec;
	vMillisecond *= 1000;
	vMillisecond += tv.tv_usec / 1000;
	return vMillisecond;
	*/
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
#else
	struct timeb		vRawTime{};
	ftime(&vRawTime);
	return vRawTime.time * 1000LL + vRawTime.millitm;
#endif
};


// constructors
XTime::XTime() noexcept
{
	this->_time_millisecond = currentMillisecondUTC();
}

// constructors
XTime::XTime(std::uint32_t _Hour, std::uint32_t _Minute, std::uint32_t _Second, std::uint32_t _Millisecond) noexcept
{
	this->_time_millisecond = _Hour * 3600LL * 1000LL;
	this->_time_millisecond += _Minute * 60LL * 1000LL;
	this->_time_millisecond += _Second * 1000LL;
	this->_time_millisecond += _Millisecond;
}

// constructors
XTime::XTime(const XTime& _Info) noexcept = default;

// destructor
XTime::~XTime() noexcept = default;



// override operator =
XTime& XTime::operator = (const XTime& _Other) noexcept = default;



// Gets the total number of seconds
std::int64_t XTime::second() const noexcept
{
	return this->millisecond() / 1000LL;
}

// Gets the total number of millisecond
std::int64_t XTime::millisecond() const noexcept
{
	return this->_time_millisecond;
}





// Get the current time
XTime XTime::currentTime() noexcept
{
	return XTime::fromMillisecond(currentMillisecondUTC());
}

// Sets the time to the specified number of milliseconds
XTime XTime::fromMillisecond(std::int64_t _Millisecond) noexcept
{
	auto		vTime = XTime();
	vTime._time_millisecond = _Millisecond;
	return vTime;
}





// 高精度计时开始
HANDLE XTime::HighPrecisionStart() noexcept
{
	auto		vHandle = new(std::nothrow) XANADU_TIME_HIGH_PRECISION();
	if (vHandle)
	{
		x_posix_memset(vHandle, 0, sizeof(XANADU_TIME_HIGH_PRECISION));
#if defined(XANADU_SYSTEM_WINDOWS)
		QueryPerformanceFrequency(&vHandle->vCpuTime);
		QueryPerformanceCounter(&vHandle->vBeginTime);
#else
		gettimeofday(&vHandle->vBeginTime, NULL);
#endif
	}
	return vHandle;
}

// 高精度计时结束
std::int64_t XTime::HighPrecisionStop(HANDLE _Handle) noexcept
{
	auto		vDifference = static_cast<std::int64_t>(0);
	auto		vHandle = static_cast<XANADU_TIME_HIGH_PRECISION*>(_Handle);
	if (vHandle)
	{
#if defined(XANADU_SYSTEM_WINDOWS)
		QueryPerformanceCounter(&vHandle->vEndTime);

		double		dbCpuTime = (double)vHandle->vCpuTime.QuadPart;
		std::int64_t		nTemp = vHandle->vEndTime.QuadPart - vHandle->vBeginTime.QuadPart;

		double		dbDifference = (double)nTemp;
		dbDifference *= 1000.0f;
		double		dbMillisecond = dbDifference / dbCpuTime;

		vDifference = (std::int64_t)dbMillisecond;
#else
		gettimeofday(&vHandle->vEndTime, NULL);
		std::int64_t		nDelayedSecond = vHandle->vEndTime.tv_sec - vHandle->vBeginTime.tv_sec;
		nDelayedSecond *= 1000000;
		std::int64_t		nDelayedMillisecond = vHandle->vEndTime.tv_usec - vHandle->vBeginTime.tv_usec;
		vDifference += nDelayedSecond + nDelayedMillisecond;
#endif
		XANADU_DELETE_PTR(vHandle);
	}
	return vDifference;
}

