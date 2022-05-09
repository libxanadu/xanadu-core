#ifndef			_XANADU_CORE_SYSTEM_H_
#define			_XANADU_CORE_SYSTEM_H_

#include <xanadu-core/header.h>
#include <xanadu-core/string.h> // NOLINT(modernize-deprecated-headers)


/// namespace xanadu
namespace xanadu
{
	/// class system_version
	class _XCOREAPI_ system_version
	{
	public:
		using value_type				= xanadu::uint64_t;
		using version_type				= xanadu::uint64_t;

	public:
		static const value_type version_unknown		= 0x00000000;		// 未知版本

	public:
		static const value_type nt_5_0			= 0x00050000;		// Windows NT 5.0
		static const value_type nt_5_1			= 0x00050100;		// Windows NT 5.1
		static const value_type nt_5_2			= 0x00050200;		// Windows NT 5.2
		static const value_type nt_6_0			= 0x00060000;		// Windows NT 6.0
		static const value_type nt_6_1			= 0x00060100;		// Windows NT 6.1
		static const value_type nt_6_2			= 0x00060200;		// Windows NT 6.2
		static const value_type nt_6_3			= 0x00060300;		// Windows NT 6.3
		static const value_type nt_6_4			= 0x00060400;		// Windows NT 6.4
		static const value_type nt_10_0			= 0x00100000;		// Windows NT 10.0

	public:
		static const value_type linux_2_2_2		= 0x00020202;		// Linux
		static const value_type linux_3_3_3		= 0x00030303;		// Linux
		static const value_type linux_4_4_4		= 0x00040404;		// Linux
		static const value_type linux_5_5_5		= 0x00050505;		// Linux
		static const value_type linux_6_6_6		= 0x00060606;		// Linux

	public:
		static const value_type darwin_16_7_0		= 0x00160700;		// Darwin 16.7.0
		static const value_type darwin_21_1_0		= 0x00210100;		// Darwin 21.1.0

	public:
		static const value_type windows_2000		= nt_5_0;		// Windows 2000
		static const value_type windows_xp		= nt_5_1;		// Windows XP
		static const value_type windows_2003		= nt_5_2;		// Windows 2003
		static const value_type windows_vista		= nt_6_0;		// Windows Vista
		static const value_type windows_7		= nt_6_1;		// Windows 7
		static const value_type windows_8		= nt_6_2;		// Windows 8
		static const value_type windows_8_1		= nt_6_3;		// Windows 8.1
		static const value_type windows_10		= nt_10_0;		// Windows 10

	public:
		// 构建一个内核版本
		static value_type create(xanadu::uint8_t _VersionX, xanadu::uint8_t _VersionY, xanadu::uint8_t _VersionZ) noexcept;
	};

	/// class system_machine
	class _XCOREAPI_ system_machine
	{
	public:
		using value_type				= xanadu::uint64_t;

	public:
		static const value_type machine_unknown		= 0x00000000;		// 未知架构
		static const value_type machine_arm		= 0x00000132;		// ARM
		static const value_type machine_aarch64		= 0x00000164;		// AARCH64
		static const value_type machine_i386		= 0x00000232;		// X86
		static const value_type machine_amd64		= 0x00000264;		// X64
		static const value_type machine_mips		= 0x00000332;		// mips
		static const value_type machine_mips_64		= 0x00000364;		// mips_64
	};

	/// class system_osbit
	class _XCOREAPI_ system_osbit
	{
	public:
		using value_type				= xanadu::uint8_t;

	public:
		static const value_type bit_unknown		= 0x00000000;		// 未知位数
		static const value_type bit_8			= 0x00000008;		// 8位
		static const value_type bit_16			= 0x00000016;		// 16位
		static const value_type bit_32			= 0x00000032;		// 32位
		static const value_type bit_64			= 0x00000064;		// 64位
	};

	/// class system
	class _XCOREAPI_ system
	{
	public:
		using version_type				= xanadu::system_version::version_type;
		using machine_type				= xanadu::system_machine::value_type;
		using string_type				= xanadu::string;
		using osbit_type				= xanadu::system_osbit::value_type;

	public:
		// constructor
		system() noexcept;

		// constructor
		system(const system& _Other) noexcept;

		// constructor
		system(system&& _Other) noexcept;

		// destructor
		virtual ~system() noexcept;

	public:
		// operator overload =
		system& operator = (const system& _Other) noexcept;

		// operator overload =
		system& operator = (system&& _Other) noexcept;

	private:
		// 本机 /etc/os-release
		static const std::list<xanadu::string>& native_os_release() noexcept;

	public:
		// 内核名称
		static string_type kernel_name() noexcept;

		// 内核版本
		static version_type kernel_version() noexcept;

		// 硬件体系类型
		static machine_type kernel_machine() noexcept;

	public:
		// 系统位数
		static osbit_type os_bit() noexcept;

		// 系统名称
		static const string_type& os_name() noexcept;

		// 系统版本
		static const string_type& os_version_str() noexcept;

		// 系统版本
		static version_type os_version() noexcept;

		// 系统编译版本
		static const string_type& os_build_version() noexcept;

		// 系统是否为服务器版本
		static bool os_is_server() noexcept;

		// 系统是否为桌面版本
		static bool os_is_desktop() noexcept;

		// 系统字符串标识
		static const string_type& os_native_explain() noexcept;

	public:
		// 计算机名称
		static const string_type& computer_name() noexcept;

	public:
		// 当前登录的帐号名称
		static const string_type& current_user_name() noexcept;

		// 当前登录帐号的主目录
		static const string_type& current_user_home() noexcept;

	public:
		// 本地数据目录
		static const string_type& local_data_directory() noexcept;

		// 远程数据目录
		static const string_type& remote_data_directory() noexcept;

		// 缓存目录
		static const string_type& temp_directory() noexcept;
	};
}

#endif
