#include <xanadu-core/system.h>
#include <xanadu-core/library.h>
#include <xanadu-core/ternary.h>
#include <xanadu-core/shell.h>
#include <xanadu-core/filesystem.h>
#if defined(XANADU_SYSTEM_WINDOWS)
#include <WtsApi32.h>
#include <userenv.h>
#include <Shlobj.h>
#else
#include <sys/utsname.h>
#endif



// 构建一个内核版本
x::system_version::value_type x::system_version::create(x::uint8_t _VersionX, x::uint8_t _VersionY, x::uint8_t _VersionZ) noexcept
{
	x::uint32_t		vX = _VersionX;
	x::uint32_t		vY = _VersionY;
	x::uint32_t		vZ = _VersionZ;
	return (vX << 16) | (vY << 8) | vZ;
}





// constructor
x::system::system() noexcept = default;

// constructor
x::system::system(const x::system& _Other) noexcept = default;

// constructor
x::system::system(x::system&& _Other) noexcept = default;

// destructor
x::system::~system() noexcept = default;





// operator overload =
x::system& x::system::operator = (const x::system& _Other) noexcept = default;

// operator overload =
x::system& x::system::operator = (x::system&& _Other) noexcept = default;





// 本机 /etc/os-release
const std::list<x::string>& x::system::native_os_release() noexcept
{
	static auto	_static_native_os_release = std::list<x::string>();
	if(_static_native_os_release.empty())
	{
		x::shell::sync_run("cat /etc/os-release", [&](const x::shell::output_type& _Output)->void{	_static_native_os_release = _Output.split('\n');	});
	}
	return _static_native_os_release;
}





// 内核名称
x::system::string_type x::system::kernel_name() noexcept
{
	static auto 	_static_system_kernel_name = x::string();
	if(_static_system_kernel_name == nullptr)
	{
#if defined(XANADU_SYSTEM_WINDOWS)
		_static_system_kernel_name = "Microsoft Windows";
#elif defined(XANADU_SYSTEM_LINUX)
		_static_system_kernel_name = "Linux";
#elif defined(XANADU_SYSTEM_DARWIN)
		_static_system_kernel_name = "Darwin";
#else
		_static_system_kernel_name = "Unknown";
#endif
	}
	return _static_system_kernel_name;
}

// 内核版本
x::system::version_type x::system::kernel_version() noexcept
{
	static auto 	_static_system_kernel_version = x::system_version::version_unknown;
	if(_static_system_kernel_version == x::system_version::version_unknown)
	{
		auto		vVersion_1 = static_cast<long>(0);
		auto		vVersion_2 = static_cast<long>(0);
		auto		vVersion_3 = static_cast<long>(0);
#if defined(XANADU_SYSTEM_WINDOWS)
		typedef void(WINAPI* _Function_GetVersionNumbers)(long*, long*, long*);
		auto		vModule = x::library::dlopen("ntdll.dll");
		if(vModule)
		{
			auto		GetVersionNumbers = (_Function_GetVersionNumbers) x::library::dlsym(vModule, "RtlGetNtVersionNumbers");
			if(GetVersionNumbers)
			{
				GetVersionNumbers(&vVersion_1, &vVersion_2, &vVersion_3);
				vVersion_3 = 0;
			}
			x::library::dlclose(vModule);
		}
#elif defined(XANADU_SYSTEM_LINUX) || defined(XANADU_SYSTEM_DARWIN)
		struct utsname	vVersion;
		if(0 == uname(&vVersion))
		{
			x_posix_sscanf(vVersion.release, "%ld.%ld.%ld", &vVersion_1, &vVersion_2, &vVersion_3);
		}
#endif
		_static_system_kernel_version = x::system_version::create((x::uint8_t)vVersion_1, (x::uint8_t)vVersion_2, (x::uint8_t)vVersion_3);
	}
	return _static_system_kernel_version;
}

// 硬件体系类型
x::system::machine_type x::system::kernel_machine() noexcept
{
	static auto 	_static_system_machine = x::system_machine::machine_unknown;
	if(_static_system_machine == x::system_machine::machine_unknown)
	{
#if defined(XANADU_SYSTEM_WINDOWS)
		SYSTEM_INFO	vSystemInfo;
		GetNativeSystemInfo(&vSystemInfo);
		switch(vSystemInfo.wProcessorArchitecture)
		{
			case PROCESSOR_ARCHITECTURE_ARM:
				_static_system_machine = x::system_machine::machine_arm;
				break;
			case PROCESSOR_ARCHITECTURE_ARM64:
			case PROCESSOR_ARCHITECTURE_IA32_ON_ARM64:
				_static_system_machine = x::system_machine::machine_aarch64;
				break;
			case PROCESSOR_ARCHITECTURE_MIPS:
				_static_system_machine = x::system_machine::machine_mips;
				break;
			case PROCESSOR_ARCHITECTURE_AMD64:
			case PROCESSOR_ARCHITECTURE_IA64:
			case PROCESSOR_ARCHITECTURE_ALPHA64:
			case PROCESSOR_ARCHITECTURE_ARM32_ON_WIN64:
				_static_system_machine = x::system_machine::machine_amd64;
				break;
			case PROCESSOR_ARCHITECTURE_INTEL:
				_static_system_machine = x::system_machine::machine_i386;
				break;
			default:
				break;
		}
#elif defined(XANADU_SYSTEM_LINUX) || defined(XANADU_SYSTEM_DARWIN)
		struct utsname	vVersion;
		if(0 == uname(&vVersion))
		{
			if(x_posix_stricmp(vVersion.machine, "x86_64") == 0 || x_posix_stricmp(vVersion.machine, "amd64") == 0)
			{
				_static_system_machine = x::system_machine::machine_amd64;
			}
			else if(x_posix_stricmp(vVersion.machine, "i386") == 0 || x_posix_stricmp(vVersion.machine, "i486") == 0 || x_posix_stricmp(vVersion.machine, "i586") == 0 || x_posix_stricmp(vVersion.machine, "i686") == 0)
			{
				_static_system_machine = x::system_machine::machine_i386;
			}
			else if(x_posix_stricmp(vVersion.machine, "arm64") == 0 || x_posix_stricmp(vVersion.machine, "aarch64") == 0)
			{
				_static_system_machine = x::system_machine::machine_aarch64;
			}
			else if(x_posix_stricmp(vVersion.machine, "arm") == 0)
			{
				_static_system_machine = x::system_machine::machine_arm;
			}
			else if(x_posix_stricmp(vVersion.machine, "mips_x64") == 0 || x_posix_stricmp(vVersion.machine, "mips_64") == 0)
			{
				_static_system_machine = x::system_machine::machine_mips_64;
			}
			else if(x_posix_stricmp(vVersion.machine, "mips") == 0)
			{
				_static_system_machine = x::system_machine::machine_mips;
			}
		}
#endif
	}
	return _static_system_machine;
}





// 系统位数
x::system::osbit_type x::system::os_bit() noexcept
{
	static auto 	_static_system_os_bit = x::system_osbit::bit_unknown;
	if(_static_system_os_bit == x::system_osbit::bit_unknown)
	{
		auto		vMachine = x::system::kernel_machine();
		switch (vMachine)
		{
			case x::system_machine::machine_arm:
			case x::system_machine::machine_i386:
			case x::system_machine::machine_mips:
				_static_system_os_bit = x::system_osbit::bit_32;
				break;
			case x::system_machine::machine_aarch64:
			case x::system_machine::machine_amd64:
			case x::system_machine::machine_mips_64:
				_static_system_os_bit = x::system_osbit::bit_64;
				break;
			default:
				break;
		}
	}
	return _static_system_os_bit;
}

// 系统名称
const x::system::string_type& x::system::os_name() noexcept
{
	static auto 	_static_system_os_name = x::string();
	if(_static_system_os_name == nullptr)
	{
#if defined(XANADU_SYSTEM_WINDOWS)
		auto		vKernelVersion = x::system::kernel_version();
		auto		vIsDesktop = x::system::os_is_desktop();
		switch(vKernelVersion)
		{
			case x::system_version::nt_5_0:
				_static_system_os_name = "2000";
				break;
			case x::system_version::nt_5_1:
				_static_system_os_name = "XP";
				break;
			case x::system_version::nt_5_2:
				_static_system_os_name = "Server 2003 R2";
				break;
			case x::system_version::nt_6_0:
				_static_system_os_name = vIsDesktop ? "Vista" : "Server 2008";
				break;
			case x::system_version::nt_6_1:
				_static_system_os_name = vIsDesktop ? "7" : "Server 2008 R2";
				break;
			case x::system_version::nt_6_2:
				_static_system_os_name = vIsDesktop ? "8" : "Server 2012";
				break;
			case x::system_version::nt_6_3:
				_static_system_os_name = vIsDesktop ? "8.1" : "Server 2012 R2";
				break;
			case x::system_version::nt_6_4:
			case x::system_version::nt_10_0:
				_static_system_os_name = vIsDesktop ? "10" : "Server 2016";
				break;
			default:
				break;
		}
#elif defined(XANADU_SYSTEM_LINUX)
		auto		vOSRelease = x::system::native_os_release();
		for(const auto & vIterator : vOSRelease)
		{
			if(vIterator.startsWith("NAME="))
			{
				auto		vName = vIterator.substr(x_posix_strlen("NAME="));
				vName.remove("\"");
				_static_system_os_name = vName;
				break;
			}
		}
#elif defined(XANADU_SYSTEM_DARWIN)
		_static_system_os_name = "OSX";
#endif
		if(_static_system_os_name.empty())
		{
			_static_system_os_name = "Unknown";
		}
	}
	return _static_system_os_name;
}

// 系统版本
const x::system::string_type& x::system::os_version_str() noexcept
{
	static auto 	_static_system_os_version_str = x::system::string_type();
	if(_static_system_os_version_str == nullptr)
	{
#if defined(XANADU_SYSTEM_WINDOWS)
		auto		vKernelVersion = x::system::kernel_version();
		switch (vKernelVersion)
		{
			case x::system_version::nt_5_0:
				_static_system_os_version_str = "NT 5.0";
				break;
			case x::system_version::nt_5_1:
				_static_system_os_version_str = "NT 5.1";
				break;
			case x::system_version::nt_5_2:
				_static_system_os_version_str = "NT 5.2";
				break;
			case x::system_version::nt_6_0:
				_static_system_os_version_str = "NT 6.0";
				break;
			case x::system_version::nt_6_1:
				_static_system_os_version_str = "NT 6.1";
				break;
			case x::system_version::nt_6_2:
				_static_system_os_version_str = "NT 6.2";
				break;
			case x::system_version::nt_6_3:
				_static_system_os_version_str = "NT 6.3";
				break;
			case x::system_version::nt_6_4:
				_static_system_os_version_str = "NT 6.4";
				break;
			case x::system_version::nt_10_0:
				_static_system_os_version_str = "NT 10.0";
				break;
			default:
				_static_system_os_version_str = x::string::format("NT %d.%d", (vKernelVersion & 0x00FF0000) >> 16, (vKernelVersion & 0x0000FF00) >> 8);
				break;
		}
#elif defined(XANADU_SYSTEM_LINUX)
		auto		vOSRelease = x::system::native_os_release();
		for(const auto & vIterator : vOSRelease)
		{
			if(vIterator.startsWith("VERSION_ID="))
			{
				auto		vVersionID = vIterator.substr(x_posix_strlen("VERSION_ID=")).remove("\"");
				_static_system_os_version_str = vVersionID;
				break;
			}
		}
#elif defined(XANADU_SYSTEM_DARWIN)
		auto		vVersionStr = x::string();
		x::shell::sync_run("sw_vers | awk \'NR==2 {print $2}\'", [&](const x::shell::output_type& _Output)->void{	vVersionStr = _Output;	});
		_static_system_os_version_str = vVersionStr;
#endif
	}
	return _static_system_os_version_str;
}

// 系统版本
x::system::version_type x::system::os_version() noexcept
{
	static auto 	_static_system_os_version = x::system_version::version_unknown;
	if(_static_system_os_version == x::system_version::version_unknown)
	{
#if defined(XANADU_SYSTEM_WINDOWS)
		_static_system_os_version = x::system::kernel_version();
#elif defined(XANADU_SYSTEM_LINUX) || defined(XANADU_SYSTEM_DARWIN)
		auto		vVersion_1 = static_cast<int>(0);
		auto		vVersion_2 = static_cast<int>(0);
		auto		vVersion_3 = static_cast<int>(0);
		auto		vVersionStr = x::system::os_version_str();
		if(x_posix_sscanf(vVersionStr.data(), "%d.%d.%d", &vVersion_1, &vVersion_2, &vVersion_3) == 3)
		{
			_static_system_os_version = (vVersion_1 << 16) | (vVersion_2 << 8) | vVersion_3;
		}
		else if(x_posix_sscanf(vVersionStr.data(), "%d.%d", &vVersion_1, &vVersion_2) == 2)
		{
			_static_system_os_version = (vVersion_1 << 16) | (vVersion_2 << 8);
		}
		else if(x_posix_sscanf(vVersionStr.data(), "%d", &vVersion_1) == 1)
		{
			_static_system_os_version = vVersion_1 << 16;
		}
#endif
	}
	return _static_system_os_version;
}

// 系统编译版本
const x::system::string_type& x::system::os_build_version() noexcept
{
	static auto 	_static_system_os_build_version = x::system::string_type();
	if(_static_system_os_build_version == nullptr)
	{
#if defined(XANADU_SYSTEM_WINDOWS)
		auto		vModule = x::library::dlopen("ntdll.dll");
		if(vModule)
		{
			auto		vValue1 = static_cast<long>(0);
			auto		vValue2 = static_cast<long>(0);
			auto		vValue3 = static_cast<long>(0);
			typedef void(WINAPI* LP_GetVersionNumbers)(long*, long*, long*);
			auto		GetVersionNumbers = (LP_GetVersionNumbers)x::library::dlsym(vModule, "RtlGetNtVersionNumbers");
			if(GetVersionNumbers)
			{
				GetVersionNumbers(&vValue1, &vValue2, &vValue3);
				_static_system_os_build_version = x::system::string_type::format("%d", vValue3);

			}
			x::library::dlclose(vModule);
		}
#elif defined(XANADU_SYSTEM_LINUX)
		auto		vOSRelease = x::system::native_os_release();
		for(const auto & vIterator : vOSRelease)
		{
			if(vIterator.startsWith("VERSION_ID="))
			{
				auto		vVersionID = vIterator.substr(x_posix_strlen("VERSION_ID=")).remove("\"");
				_static_system_os_build_version = vVersionID;
				break;
			}
		}
#elif defined(XANADU_SYSTEM_DARWIN)
		auto		vBytesOSRelease = x::string();
		x::shell::sync_run("sw_vers | awk \'NR==2 {print $2}\'", [&](const x::shell::output_type& _Output)->void{	vBytesOSRelease = _Output;	});
		if(vBytesOSRelease.exist())
		{
			_static_system_os_build_version = vBytesOSRelease;
		}
#endif
		if(_static_system_os_build_version.empty())
		{
			_static_system_os_build_version = "Unknown";
		}
	}
	return _static_system_os_build_version;
}

// 系统是否为服务器版本
bool x::system::os_is_server() noexcept
{
	static auto	_static_system_os_is_server = x::ternary(nullptr);
	if(_static_system_os_is_server == nullptr)
	{
#if defined(XANADU_SYSTEM_WINDOWS)
		typedef BOOL(WINAPI* _Function_IsWindowsServer)();
		auto		vHandle = x::library::dlopen("Kernel32.dll");
		if(vHandle)
		{
			auto		vIsWindowsServer = (_Function_IsWindowsServer) x::library::dlsym(vHandle, "IsWindowsServer");
			if(vIsWindowsServer)
			{
				_static_system_os_is_server = vIsWindowsServer() != 0;
			}
			x::library::dlclose(vHandle);
		}
#else
		_static_system_os_is_server = false;
#endif
	}
	return _static_system_os_is_server == true;
}

// 系统是否为桌面版本
bool x::system::os_is_desktop() noexcept
{
	return !x::system::os_is_server();
}

// 系统字符串标识
const x::system::string_type& x::system::os_native_explain() noexcept
{
	static auto 	_static_os_native_explain = x::system::string_type();
	if(_static_os_native_explain == nullptr)
	{
		auto		vKernel_Name = x::system::kernel_name();
		auto		vOS_Name = x::system::os_name();
		auto		vOS_Version = x::system::os_version_str();

		auto		vSystemNativeExplain = vKernel_Name + " " + vOS_Name;

		// 拼接系统版本
		vSystemNativeExplain += " ";
		vSystemNativeExplain += vOS_Version;

		// 拼接编译版本
		vSystemNativeExplain += " (build ";
		vSystemNativeExplain += x::system::os_build_version();
		vSystemNativeExplain += ")";

		//拼接系统位数
		if(x::system::os_bit() == x::system_osbit::bit_64)
		{
			vSystemNativeExplain += ",64-Bit";
		}
		else
		{
			vSystemNativeExplain += ",32-Bit";
		}
	}
	return _static_os_native_explain;
}





// 计算机名称
const x::system::string_type& x::system::computer_name() noexcept
{
	static x::system::string_type 	_static_system_host_name;
#if defined(XANADU_SYSTEM_WINDOWS)
	wchar_t		vHostName[XANADU_PATH_MAX] = { 0 };
	DWORD		vLength = XANADU_PATH_MAX;
	GetComputerNameW(vHostName, &vLength);
	_static_system_host_name = x::system::string_type::fromWString(vHostName);
#else
	char		vHostName[XANADU_PATH_MAX] = { 0 };
	gethostname(vHostName, XANADU_PATH_MAX);
	_static_system_host_name = x::system::string_type::fromUString(vHostName);
#endif
	return _static_system_host_name;
}





// 当前登录的帐号名称
const x::system::string_type& x::system::current_user_name() noexcept
{
	static x::system::string_type 	_static_system_current_user_name = nullptr;
	if(_static_system_current_user_name.empty())
	{
#if defined(XANADU_SYSTEM_WINDOWS)
		auto		vUserProfileDirectory = x::system::string_type();
		auto		vProcess = ::GetCurrentProcess();
		HANDLE		vToken = nullptr;
		auto		vSync = ::OpenProcessToken(vProcess, TOKEN_QUERY, &vToken);
		if (vSync)
		{
			DWORD		vLength = 0;
			// First call, to determine size of the strings (with '\0').
			vSync = ::GetUserProfileDirectoryW(vToken, nullptr, &vLength);
			if (!vSync && vLength != 0)
			{
				auto		vBuffer = new(std::nothrow) wchar_t[vLength];
				if(vBuffer)
				{
					vSync = ::GetUserProfileDirectoryW(vToken, vBuffer, &vLength);
					if (vSync)
					{
						vUserProfileDirectory = x::system::string_type::fromWString(vBuffer);
						vUserProfileDirectory.replace("\\", "/");
						auto		vFind = vUserProfileDirectory.rfind('/');
						if(vFind != x::system::string_type::npos)
						{
							_static_system_current_user_name = vUserProfileDirectory.substr(vFind + 1);
						}
					}
					delete[] vBuffer;
				}
			}
			::CloseHandle(vToken);
		}

		if(_static_system_current_user_name.empty())
		{
			LPWSTR		vInfoBuffer = nullptr;
			DWORD		vInfoLength = 0;
			auto		vQuery = WTSQuerySessionInformationW(WTS_CURRENT_SERVER_HANDLE, WTS_CURRENT_SESSION, WTSUserName, &vInfoBuffer, &vInfoLength);
			if (vQuery && vInfoBuffer && vInfoLength)
			{
				_static_system_current_user_name = x::system::string_type::fromWString(WString(vInfoBuffer, vInfoLength));
			}
			else
			{
				wchar_t		vUserName[XANADU_SIZE_KB] = { 0 };
				DWORD		vUserLength = XANADU_SIZE_KB - 1;
				GetUserNameW(vUserName, &vUserLength);
				_static_system_current_user_name = x::system::string_type::fromWString(vUserName);
			}
			if(vInfoBuffer)
			{
				WTSFreeMemory(vInfoBuffer);
			}
		}
#else
		_static_system_current_user_name = x::system::string_type::fromUString(getenv("USER"));
#endif
	}
	return _static_system_current_user_name;
}

// 当前登录帐号的主目录
const x::system::string_type& x::system::current_user_home() noexcept
{
	static x::system::string_type 	_static_system_current_user_home = nullptr;
#if defined(XANADU_SYSTEM_WINDOWS)
	_static_system_current_user_home = x::system::string_type::fromWString(L"C:/Users/") + x::system::current_user_name();
#endif
#if defined(XANADU_SYSTEM_LINUX)
	_static_system_current_user_home = x::system::string_type("/home/") + x::system::current_user_name();
#endif
#if defined(XANADU_SYSTEM_DARWIN)
	_static_system_current_user_home = x::system::string_type("/Users/") + x::system::current_user_name();
#endif
	return _static_system_current_user_home;
}





// 本地数据目录
const x::system::string_type& x::system::local_data_directory() noexcept
{
	static auto 	_static_system_local_data_directory = x::system::string_type();
	if(_static_system_local_data_directory == nullptr)
	{
#if defined(XANADU_SYSTEM_WINDOWS)
		wchar_t		vLocalDirectory[X_FILESYSTEM_MAX_PATH] = { 0 };
		if(SHGetSpecialFolderPathW(GetDesktopWindow(), vLocalDirectory, CSIDL_APPDATA, FALSE))
		{
			_static_system_local_data_directory = x::filesystem::path::format_to_common(string_type::fromWString(vLocalDirectory) + "/Local");
		}
		else
		{
			_static_system_local_data_directory = x::system::current_user_home() + "/AppData/Local";
		}
#else
		_static_system_local_data_directory = x::system::current_user_home() + "/.config";
#endif
		x::filesystem::create_directory(_static_system_local_data_directory, 0777);
	}
	return _static_system_local_data_directory;
}

// 远程数据目录
const x::system::string_type& x::system::remote_data_directory() noexcept
{
	static auto 	_static_system_remote_data_directory = x::system::string_type();
	if(_static_system_remote_data_directory == nullptr)
	{
#if defined(XANADU_SYSTEM_WINDOWS)
		wchar_t		vLocalDirectory[X_FILESYSTEM_MAX_PATH] = { 0 };
		if(SHGetSpecialFolderPathW(GetDesktopWindow(), vLocalDirectory, CSIDL_APPDATA, FALSE))
		{
			_static_system_remote_data_directory = x::filesystem::path::format_to_common(string_type::fromWString(vLocalDirectory) + "/Roaming");
		}
		else
		{
			_static_system_remote_data_directory = x::system::current_user_home() + "/AppData/Roaming";
		}
#else
		_static_system_remote_data_directory = x::system::current_user_home() + "/.remote";
#endif
		x::filesystem::create_directory(_static_system_remote_data_directory, 0777);
	}
	return _static_system_remote_data_directory;
}

// 缓存目录
const x::system::string_type& x::system::temp_directory() noexcept
{
	static auto 	_static_system_temp_directory = x::system::string_type();
	if(_static_system_temp_directory == nullptr)
	{
#if defined(XANADU_SYSTEM_WINDOWS)
		wchar_t 	vLongDirectory[XANADU_PATH_MAX] = { 0 };
		wchar_t		vTempDirectory[XANADU_PATH_MAX] = { 0 };
		if(GetTempPathW(XANADU_PATH_MAX, vTempDirectory))
		{
			GetLongPathNameW(vTempDirectory, vLongDirectory, XANADU_PATH_MAX);
			_static_system_temp_directory = x::filesystem::path::format_to_common(string_type::fromWString(vLongDirectory));
		}
#else
		_static_system_temp_directory = "/tmp";
#endif
		x::filesystem::create_directory(_static_system_temp_directory, 0777);
	}
	return _static_system_temp_directory;
}
