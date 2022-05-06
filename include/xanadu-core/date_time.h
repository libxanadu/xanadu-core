#ifndef			_XANADU_CORE_TIME_ZONE_H_
#define			_XANADU_CORE_TIME_ZONE_H_

#include <xanadu-core/header.h>


/// namespace xanadu
namespace xanadu
{
	/// enum time_zone
	typedef enum class time_zone
	{
		A0000 = 0,			// +00:00
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
		S0000 = 0,			// -00:00
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

		UTC = A0000,			// 协调世界时
		GMT = A0000,			// 格林威治标准时间
		NOR = A0100,			// 挪威标准时间
		IST = A0200,			// 以色列标准时间
		CST = A0800,			// 中国北京时间
		KST = A0900,			// 韩国标准时间
		NZT = A1200,			// 新西兰时间
		PST = S0800,			// 太平洋标准时间
		HST = S1000,			// 夏威夷标准时间
		IDLE = S1200			// 国际日期变更线，西边
	}time_zone;

	/// enum time_month
	typedef enum class time_month
	{
		January				= 1,
		February			= 2,
		March				= 3,
		April				= 4,
		May				= 5,
		June				= 6,
		July				= 7,
		August				= 8,
		September			= 9,
		October				= 10,
		November			= 11,
		December			= 12,

		Jan				= January,
		Feb				= February,
		Mar				= March,
		Apr				= April,
		// May				= May,
		Jun				= June,
		Jul				= July,
		Aug				= August,
		Sept				= September,
		Oct				= October,
		Nov				= November,
		Dec				= December
	}time_month;

	/// class time_regular
	class _XCOREAPI_ time_regular
	{
	public:
		using				value_type = xanadu::int64_t;

	public:
		static const value_type		switch_sec = 1000;			// 秒数转换

	public:
		static const value_type		utc_year = 1970;			// 协调世界时起始年份

	public:
		static const value_type		sec_minute = 60;			// 一分的秒数
		static const value_type		sec_hour = 3600;			// 一小时的秒数
		static const value_type		sec_day = 86400;			// 一天的秒数
		static const value_type		sec_year = 31536000;			// 一年的秒数
		static const value_type		sec_leap_year = 31622400;		// 一闰年的秒数

	public:
		static const value_type		msec_minute = 60000;			// 一分的毫秒数
		static const value_type		msec_hour = 3600000;			// 一小时的毫秒数
		static const value_type		msec_day = 86400000;			// 一天的毫秒数
		static const value_type		msec_year = 31536000000;		// 一年的毫秒数
		static const value_type		msec_leap_year = 31622400000;		// 一闰年的毫秒数

	public:
		static const value_type		usec_minute = 60000000;			// 一分的微秒数
		static const value_type		usec_hour = 3600000000;			// 一小时的微秒数
		static const value_type		usec_day = 86400000000;			// 一天的微秒数
		static const value_type		usec_year = 31536000000000;		// 一年的微秒数
		static const value_type		usec_leap_year = 31622400000000;	// 一闰年的微秒数

	public:
		static const value_type		nsec_minute = 60000000000;		// 一分的纳秒数
		static const value_type		nsec_hour = 3600000000000;		// 一小时的纳秒数
		static const value_type		nsec_day = 86400000000000;		// 一天的纳秒数
		static const value_type		nsec_year = 31536000000000000;		// 一年的纳秒数
		static const value_type		nsec_leap_year = 31622400000000000;	// 一闰年的纳秒数

	public:
		static const value_type 	day_month_1 = 31;			// 一月份的天数
		static const value_type		day_month_2 = 28;			// 二月份的天数
		static const value_type		day_month_3 = 31;			// 三月份的天数
		static const value_type		day_month_4 = 30;			// 四月份的天数
		static const value_type		day_month_5 = 31;			// 五月份的天数
		static const value_type		day_month_6 = 30;			// 六月份的天数
		static const value_type		day_month_7 = 31;			// 七月份的天数
		static const value_type		day_month_8 = 31;			// 八月份的天数
		static const value_type		day_month_9 = 30;			// 九月份的天数
		static const value_type		day_month_10 = 31;			// 十月份的天数
		static const value_type		day_month_11 = 30;			// 十一月份的天数
		static const value_type		day_month_12 = 31;			// 十二月份的天数
		static const value_type		day_month_leap = 29;			// 闰二月份的天数

		static const value_type		day_month_January = day_month_1;	// 一月份的天数
		static const value_type		day_month_February = day_month_2;	// 二月份的天数
		static const value_type		day_month_March = day_month_3;		// 三月份的天数
		static const value_type		day_month_April = day_month_4;		// 四月份的天数
		static const value_type		day_month_May = day_month_5;		// 五月份的天数
		static const value_type		day_month_June = day_month_6;		// 六月份的天数
		static const value_type		day_month_July = day_month_7;		// 七月份的天数
		static const value_type		day_month_August = day_month_8;		// 八月份的天数
		static const value_type		day_month_September = day_month_9;	// 九月份的天数
		static const value_type		day_month_October = day_month_10;	// 十月份的天数
		static const value_type		day_month_November = day_month_11;	// 十一月份的天数
		static const value_type		day_month_December = day_month_12;	// 十二月份的天数

	public:
		static const value_type		min_millisecond = 0;			// 允许的最小毫秒数
		static const value_type		min_second = 0;				// 允许的最小秒数
		static const value_type		min_minute = 0;				// 允许的最小分钟数
		static const value_type		min_hour = 0;				// 允许的最小小时数
		static const value_type		min_day = 1;				// 允许的最小天数
		static const value_type		min_month = 1;				// 允许的最小月数
		static const value_type		min_year = -9999;			// 允许的最小年数

		static const value_type		max_millisecond = 999;			// 允许的最大毫秒数
		static const value_type		max_second = 59;			// 允许的最大秒数
		static const value_type		max_minute = 59;			// 允许的最大分钟数
		static const value_type		max_hour = 23;				// 允许的最大小时数
		static const value_type		max_day = 31;				// 允许的最大天数
		static const value_type		max_month = 12;				// 允许的最大月数
		static const value_type		max_year = 9999;			// 允许的最大年数
	};

	/// class date_time
	class _XCOREAPI_ date_time
	{
	public:
		using				value_type = xanadu::int64_t;

	private:
		value_type			_time_year;
		value_type			_time_month;
		value_type			_time_day;
		value_type			_time_hour;
		value_type			_time_minute;
		value_type			_time_second;
		value_type			_time_millisecond;

	public:
		// constructor
		date_time() noexcept;

		// constructor
		date_time(const date_time& _Other) noexcept;

		// constructor
		date_time(date_time&& _Other) noexcept;

		// destructor
		virtual ~date_time() noexcept;

	public:
		// operators overload =
		date_time& operator = (const date_time& _Other) noexcept;

		// operators overload =
		date_time& operator = (date_time&& _Other) noexcept;

	public:
		// [get] 当前秒数
		static value_type current_second() noexcept;

		// [get] 当前秒数
		static value_type current_second(time_zone _TimeZone) noexcept;

		// [get] 当前毫秒数
		static value_type current_millisecond() noexcept;

		// [get] 当前毫秒数
		static value_type current_millisecond(time_zone _TimeZone) noexcept;

	public:
		// 年份是否闰年
		static bool year_is_leap(value_type _Year) noexcept;

	public:
		// 修正年份 xanadu::time_regular::min_year - xanadu::time_regular::max_year
		static value_type revise_year(value_type _Year) noexcept;

		// 修正月份 xanadu::time_regular::min_month - xanadu::time_regular::max_month
		static value_type revise_month(value_type _Month) noexcept;

		// 修正天数 xanadu::time_regular::min_day - xanadu::time_regular::max_day
		static value_type revise_day(value_type _Day) noexcept;

		// 修正小时 xanadu::time_regular::min_hour - xanadu::time_regular::max_hour
		static value_type revise_hour(value_type _Hour) noexcept;

		// 修正分钟 xanadu::time_regular::min_minute - xanadu::time_regular::max_minute
		static value_type revise_minute(value_type _Minute) noexcept;

		// 修正秒数 xanadu::time_regular::min_second - xanadu::time_regular::max_second
		static value_type revise_second(value_type _Second) noexcept;

	public:
		// 日期转换为毫秒
		static value_type data_to_millisecond(value_type _Year) noexcept;

		// 日期转换为毫秒
		static value_type data_to_millisecond(value_type _Year, value_type _Month) noexcept;

		// 日期转换为毫秒
		static value_type data_to_millisecond(value_type _Year, value_type _Month, value_type _Day) noexcept;

		// 日期转换为毫秒
		static value_type data_to_millisecond(value_type _Year, value_type _Month, value_type _Day, value_type _Hour) noexcept;

		// 日期转换为毫秒
		static value_type data_to_millisecond(value_type _Year, value_type _Month, value_type _Day, value_type _Hour, value_type _Minute) noexcept;

		// 日期转换为毫秒
		static value_type data_to_millisecond(value_type _Year, value_type _Month, value_type _Day, value_type _Hour, value_type _Minute, value_type _Second) noexcept;

	public:
		// 秒转换为日期
		static date_time from_second(value_type _Second) noexcept;

		// 毫秒转换为日期
		static date_time from_millisecond(value_type _Millisecond) noexcept;

	public:
		// [get] 年份
		virtual value_type year() const noexcept final;

		// [get] 月份
		virtual value_type month() const noexcept final;

		// [get] 天数
		virtual value_type day() const noexcept final;

		// [get] 小时
		virtual value_type hour() const noexcept final;

		// [get] 分钟
		virtual value_type minute() const noexcept final;

		// [get] 秒
		virtual value_type second() const noexcept final;

		// [get] 毫秒
		virtual value_type millisecond() const noexcept final;
	};
}

#endif
