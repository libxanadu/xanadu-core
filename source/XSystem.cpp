#include <xanadu-core/XSystem.h>
#include <xanadu-core/XHash.h>
#include <xanadu-core/XLibrary.h>
#include <xanadu-core/XShell.h>
#include <xanadu-core/XTernary.h>
#if defined(XANADU_SYSTEM_WINDOWS)
#include <WtsApi32.h>
#include <userenv.h>
#else
#include <sys/utsname.h>
#endif


//static system version value
static std::int64_t					_StaticSystemVersion = 0;


//initialize
XSystem::XSystem() noexcept = default;

//release
XSystem::~XSystem() noexcept = default;



// The current version of the operating system
std::int64_t XSystem::SystemVersion() noexcept
{
	if(!_StaticSystemVersion)
	{
#if defined(XANADU_SYSTEM_WINDOWS)
		typedef void(WINAPI* _Function_GetVersionNumbers)(long*, long*, long*);
		auto		vVersion_1 = static_cast<long>(0);
		auto		vVersion_2 = static_cast<long>(0);
		auto		vVersion_3 = static_cast<long>(0);
		auto		vIsServer = isServer();
		auto		vModule = XLibrary::dllOpen("ntdll.dll");
		if(vModule)
		{
			auto		GetVersionNumbers = (_Function_GetVersionNumbers) XLibrary::dllFind(vModule, "RtlGetNtVersionNumbers");
			if(GetVersionNumbers)
			{
				GetVersionNumbers(&vVersion_1, &vVersion_2, &vVersion_3);
				switch(vVersion_1)
				{
					case 10:
						_StaticSystemVersion = vIsServer ? XANADU_OS_VERSION_WINDOWS_2016 : XANADU_OS_VERSION_WINDOWS_10;
						break;
					case 6:
						switch(vVersion_2)
						{
							case 0:
								_StaticSystemVersion = vIsServer ? XANADU_OS_VERSION_WINDOWS_2008 : XANADU_OS_VERSION_WINDOWS_VISTA;
								break;
							case 1:
								_StaticSystemVersion = vIsServer ? XANADU_OS_VERSION_WINDOWS_2008_R2 : XANADU_OS_VERSION_WINDOWS_7;
								break;
							case 2:
								_StaticSystemVersion = vIsServer ? XANADU_OS_VERSION_WINDOWS_2012 : XANADU_OS_VERSION_WINDOWS_8;
								break;
							case 3:
								_StaticSystemVersion = vIsServer ? XANADU_OS_VERSION_WINDOWS_2012_R2 : XANADU_OS_VERSION_WINDOWS_8_1;
								break;
							default:
								break;
						}
						break;
					default:
						_StaticSystemVersion = XANADU_OS_VERSION_UNKNOWN;
						break;
				}
			}
			XLibrary::dllClose(vModule);
		}
#endif
#if defined(XANADU_SYSTEM_LINUX)
		//XANADU_PLATFORM_NOSUPPORT;
#endif
#if defined(XANADU_SYSTEM_DARWIN)
		struct utsname		vVersion;
		if(0 == uname(&vVersion))
		{
			auto	vValue1 = x_posix_atoi(vVersion.release);
			switch(vValue1)
			{
				case 12:
					_StaticSystemVersion = XANADU_OS_VERSION_MACOS_1012;
					break;
				case 13:
					_StaticSystemVersion = XANADU_OS_VERSION_MACOS_1013;
					break;
				case 14:
					_StaticSystemVersion = XANADU_OS_VERSION_MACOS_1014;
					break;
				case 15:
					_StaticSystemVersion = XANADU_OS_VERSION_MACOS_1015;
					break;
				case 16:
					_StaticSystemVersion = XANADU_OS_VERSION_MACOS_1100;
					break;
				default:
					_StaticSystemVersion = XANADU_OS_VERSION_UNKNOWN;
					break;
			}
		}
#endif
	}
	return _StaticSystemVersion;
}

// The name of the user who is now logged in
XString XSystem::currentUser() noexcept
{
	static XString 		vStaticCurrentUser = nullptr;
	if(vStaticCurrentUser.empty())
	{
#if defined(XANADU_SYSTEM_WINDOWS)
		auto		vUserProfileDirectory = XString();
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
						vUserProfileDirectory = XString::fromWString(vBuffer);
						vUserProfileDirectory.replace("\\", "/");
						auto		vFind = vUserProfileDirectory.rfind('/');
						if(vFind != XString::npos)
						{
							vStaticCurrentUser = vUserProfileDirectory.substr(vFind + 1);
						}
					}
					delete[] vBuffer;
				}
			}
			::CloseHandle(vToken);
		}

		if(vStaticCurrentUser.empty())
		{
			LPWSTR		vInfoBuffer = nullptr;
			DWORD		vInfoLength = 0;
			auto		vQuery = WTSQuerySessionInformationW(WTS_CURRENT_SERVER_HANDLE, WTS_CURRENT_SESSION, WTSUserName, &vInfoBuffer, &vInfoLength);
			if (vQuery && vInfoBuffer && vInfoLength)
			{
				vStaticCurrentUser = XString::fromWString(WString(vInfoBuffer, vInfoLength));
			}
			else
			{
				wchar_t		vUserName[XANADU_SIZE_KB] = { 0 };
				DWORD		vUserLength = XANADU_SIZE_KB - 1;
				GetUserNameW(vUserName, &vUserLength);
				vStaticCurrentUser = XString::fromWString(vUserName);
			}
			if(vInfoBuffer)
			{
				WTSFreeMemory(vInfoBuffer);
			}
		}
#else
		vStaticCurrentUser = XString::fromUString(getenv("USER"));
#endif
	}
	return vStaticCurrentUser;
}

// Computer name
XString XSystem::hostName() noexcept
{
#if defined(XANADU_SYSTEM_WINDOWS)
	wchar_t		vHostName[XANADU_PATH_MAX] = { 0 };
	DWORD		vLength = XANADU_PATH_MAX;
	GetComputerNameW(vHostName, &vLength);
	return XString::fromWString(vHostName);
#else
	char		vHostName[XANADU_PATH_MAX] = { 0 };
	gethostname(vHostName, XANADU_PATH_MAX);
	return XString::fromUString(vHostName);
#endif
}

// Gets the directory for the current user
XString XSystem::userHome() noexcept
{
#if defined(XANADU_SYSTEM_WINDOWS)
	return XString::fromWString(L"C:/Users/") + XSystem::currentUser();
#endif
#if defined(XANADU_SYSTEM_LINUX)
	return XString("/home/") + XSystem::currentUser();
#endif
#if defined(XANADU_SYSTEM_DARWIN)
	return XString("/Users/") + XSystem::currentUser();
#endif
}

// Whether the operating system is 32-bit
bool XSystem::is_32bit() noexcept
{
	return !XSystem::is_64bit();
}

// Whether the operating system is 64-bit
bool XSystem::is_64bit() noexcept
{
	static XTernary		vValue64Bit = nullptr;
	if(vValue64Bit == nullptr)
	{
#if defined(XANADU_SYSTEM_WINDOWS)
		SYSTEM_INFO	vSystemInfo;
		GetNativeSystemInfo(&vSystemInfo);
		switch(vSystemInfo.wProcessorArchitecture)
		{
			case PROCESSOR_ARCHITECTURE_AMD64:
			case PROCESSOR_ARCHITECTURE_IA64:
			case PROCESSOR_ARCHITECTURE_ALPHA64:
				vValue64Bit = true;
				break;
			default:
				vValue64Bit = false;
				break;
		}
#else
		vValue64Bit = true;
#endif
	}
	return vValue64Bit == true;
}

// Whether the operating system is a server version
bool XSystem::isServer() noexcept
{
	static XTernary		vValueServer = nullptr;
	if(vValueServer == nullptr)
	{
#if defined(XANADU_SYSTEM_WINDOWS)
		typedef BOOL(WINAPI* _Function_IsWindowsServer)();
		auto		vHandle = XLibrary::dllOpen("Kernel32.dll");
		if(vHandle)
		{
			auto		vIsWindowsServer = (_Function_IsWindowsServer) XLibrary::dllFind(vHandle, "IsWindowsServer");
			if(vIsWindowsServer)
			{
				vValueServer = vIsWindowsServer() != 0;
			}
			XLibrary::dllClose(vHandle);
		}
#else
		vValueServer = false;
#endif
	}
	return vValueServer == true;
}

// Whether the operating system is a desktop version
bool XSystem::isDesktop() noexcept
{
	return !XSystem::isServer();
}

// Native system String
XString XSystem::nativeString() noexcept
{
	static XString			_StaticNativeString;
	if (_StaticNativeString.empty())
	{
#if defined(XANADU_SYSTEM_WINDOWS)
		auto		vSystemString = XString("Microsoft Windows ");
#endif
#if defined(XANADU_SYSTEM_LINUX)
		auto		vSystemString = XString("Linux ");
#endif
#if defined(XANADU_SYSTEM_DARWIN)
		auto		vSystemString = XString("Mac OS ");
#endif
		//拼接系统版本
		switch(XSystem::SystemVersion())
		{
#if defined(XANADU_SYSTEM_WINDOWS)
			case XANADU_OS_VERSION_WINDOWS_VISTA:
				vSystemString += "Vista";
				break;
			case XANADU_OS_VERSION_WINDOWS_2008:
				vSystemString += "Server 2008";
				break;
			case XANADU_OS_VERSION_WINDOWS_7:
				vSystemString += "7";
				break;
			case XANADU_OS_VERSION_WINDOWS_2008_R2:
				vSystemString += "Server 2008 R2";
				break;
			case XANADU_OS_VERSION_WINDOWS_8:
				vSystemString += "8";
				break;
			case XANADU_OS_VERSION_WINDOWS_2012:
				vSystemString += "Server 2012";
				break;
			case XANADU_OS_VERSION_WINDOWS_8_1:
				vSystemString += "8.1";
				break;
			case XANADU_OS_VERSION_WINDOWS_2012_R2:
				vSystemString += "Server 2012 R2";
				break;
			case XANADU_OS_VERSION_WINDOWS_10:
				vSystemString += "10";
				break;
			case XANADU_OS_VERSION_WINDOWS_2016:
				vSystemString += "Server 2016";
				break;
#endif
#if defined(XANADU_SYSTEM_LINUX)
			case XANADU_OS_VERSION_LINUX_1404:
				vSystemString += "Linux 14.04";
				break;
			case XANADU_OS_VERSION_LINUX_1410:
				vSystemString += "Linux 14.10";
				break;
			case XANADU_OS_VERSION_LINUX_1504:
				vSystemString += "Linux 15.04";
				break;
			case XANADU_OS_VERSION_LINUX_1510:
				vSystemString += "Linux 15.10";
				break;
			case XANADU_OS_VERSION_LINUX_1604:
				vSystemString += "Linux 16.04";
				break;
			case XANADU_OS_VERSION_LINUX_1610:
				vSystemString += "Linux 16.10";
				break;
			case XANADU_OS_VERSION_LINUX_1704:
				vSystemString += "Linux 17.04";
				break;
			case XANADU_OS_VERSION_LINUX_1710:
				vSystemString += "Linux 17.10";
				break;
			case XANADU_OS_VERSION_LINUX_1804:
				vSystemString += "Linux 18.04";
				break;
			case XANADU_OS_VERSION_LINUX_1810:
				vSystemString += "Linux 18.10";
				break;
			case XANADU_OS_VERSION_LINUX_1904:
				vSystemString += "Linux 19.04";
				break;
			case XANADU_OS_VERSION_LINUX_1910:
				vSystemString += "Linux 19.10";
				break;
			case XANADU_OS_VERSION_LINUX_2004:
				vSystemString += "Linux 2004";
				break;
			case XANADU_OS_VERSION_LINUX_2010:
				vSystemString += "Linux 2010";
				break;
			case XANADU_OS_VERSION_LINUX_2104:
				vSystemString += "Linux 2104";
				break;
			case XANADU_OS_VERSION_LINUX_2110:
				vSystemString += "Linux 2110";
				break;
#endif
#if defined(XANADU_SYSTEM_DARWIN)
			case XANADU_OS_VERSION_MACOS_1012:
				vSystemString += "10.12 Sierra";
				break;
			case XANADU_OS_VERSION_MACOS_1013:
				vSystemString += "10.13 High Sierra";
				break;
			case XANADU_OS_VERSION_MACOS_1014:
				vSystemString += "10.14 Mojave";
				break;
			case XANADU_OS_VERSION_MACOS_1015:
				vSystemString += "10.15 Catalina";
				break;
			case XANADU_OS_VERSION_MACOS_1100:
				vSystemString += "11.00 Big Sur";
				break;
			case XANADU_OS_VERSION_MACOS_1101:
				vSystemString += "11.01 Big Sur";
				break;
#endif
			default:
				vSystemString += "Unknown";
				break;
		}
		//拼接编译版本
		vSystemString += " (build ";
		vSystemString += XSystem::buildVersion();
		vSystemString += ")";

		//拼接系统位数
		if(XSystem::is_64bit())
		{
			vSystemString += ",64-Bit";
		}
		else
		{
			vSystemString += ",32-Bit";
		}
		_StaticNativeString = vSystemString;
	}
	return _StaticNativeString;
}

// Native Build Version
XString XSystem::buildVersion() noexcept
{
#if defined(XANADU_SYSTEM_WINDOWS)
	auto		vBuildVersion = XString();
	auto		vModule = XLibrary::dllOpen("ntdll.dll");
	if(vModule)
	{
		auto		vValue1 = static_cast<long>(0);
		auto		vValue2 = static_cast<long>(0);
		auto		vValue3 = static_cast<long>(0);
		typedef void(WINAPI* LP_GetVersionNumbers)(long*, long*, long*);
		auto		GetVersionNumbers = (LP_GetVersionNumbers)XLibrary::dllFind(vModule, "RtlGetNtVersionNumbers");
		if(GetVersionNumbers)
		{
			GetVersionNumbers(&vValue1, &vValue2, &vValue3);
			vBuildVersion = XString::format("%d", vValue3);

		}
		XLibrary::dllClose(vModule);
	}
	return vBuildVersion;
#endif
#if defined(XANADU_SYSTEM_LINUX)
	return XString("Unknown");
#endif
#if defined(XANADU_SYSTEM_DARWIN)
	return XString("Unknown");
#endif
}

// The CPUID of the current computer
XString XSystem::cpuID() noexcept
{
	static char			_StaticCpuID[XANADU_PATH_MAX] = { 0 };
	if(0 == x_posix_strlen(_StaticCpuID))
	{
		unsigned long		vValue1 = 0;
		unsigned long		vValue2 = 0;

#if defined(XANADU_SYSTEM_WINDOWS)
		__asm {
			mov eax, 01h;
			xor edx, edx;
			cpuid;
			mov vValue1, edx;
			mov vValue2, eax;
		}
#endif
		std::sprintf(_StaticCpuID, "%08lX%08lX", vValue1, vValue2);
	}
	return {_StaticCpuID};
}

// The hard disk ID of the current computer
XString XSystem::diskID() noexcept
{
	static char				_StaticDiskID[XANADU_PATH_MAX] = { 0 };
	if(0 == x_posix_strlen(_StaticDiskID))
	{
#if defined(XANADU_SYSTEM_WINDOWS)
		auto		vHandle = ::CreateFileA(R"(\\.\PhysicalDrive0)", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, nullptr, OPEN_EXISTING, 0, nullptr);
		if(!vHandle)
		{
			vHandle = ::CreateFileA(R"(\\.\Scsi0)", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, nullptr, OPEN_EXISTING, 0, nullptr);
		}
		if(vHandle)
		{
			DWORD			dwBytesReturned = 0;
			GETVERSIONINPARAMS	gVersionParsams;
			x_posix_memset(&gVersionParsams, 0, sizeof(GETVERSIONINPARAMS));

			if(DeviceIoControl(vHandle, SMART_GET_VERSION, nullptr, 0, &gVersionParsams, sizeof(GETVERSIONINPARAMS), &dwBytesReturned, nullptr))
			{
				if(dwBytesReturned != 0 && gVersionParsams.bIDEDeviceMap > 0)
				{
					SENDCMDINPARAMS		scip;
					x_posix_memset(&scip, 0, sizeof(SENDCMDINPARAMS));
					scip.cBufferSize = IDENTIFY_BUFFER_SIZE;
					scip.irDriveRegs.bSectorCountReg = 1;
					scip.irDriveRegs.bSectorNumberReg = 1;
					scip.irDriveRegs.bDriveHeadReg = 0xA0;
					scip.irDriveRegs.bCommandReg = 0xEC;

					BYTE btBuffer[1024] = { 0 };

					if(DeviceIoControl(vHandle, SMART_RCV_DRIVE_DATA, &scip, sizeof(SENDCMDINPARAMS), btBuffer, 1024, &dwBytesReturned, nullptr))
					{
						//序列号的开始位置,具体请参考SENDCMDOUTPARAMS与IDSECTOR结构
						auto		vSerialPos = 0x24;
						auto		vLocalPos = 0;
						while(btBuffer[vSerialPos] < 128)
						{
							_StaticDiskID[vLocalPos++] = btBuffer[vSerialPos++];
						}
					}
				}
			}
			::CloseHandle(vHandle);
		}
#endif
#if defined(XANADU_SYSTEM_LINUX)
#endif
#if defined(XANADU_SYSTEM_DARWIN)
		//system_profiler SPSerialATADataType | grep Serial
		XShell::run("system_profiler SPSerialATADataType | grep Serial", [&](const XString& _Output)->bool
		{
			auto		vSPSerialATADataType = _Output;
			vSPSerialATADataType.remove("Serial number:");
			vSPSerialATADataType.remove("Serial Number:");
			vSPSerialATADataType = vSPSerialATADataType.simplified();
			if(vSPSerialATADataType.exist())
			{
				x_posix_strcpy(_StaticDiskID, vSPSerialATADataType.data());
			}
			return true;
		});
#endif
	}
	return XString(_StaticDiskID);
}

// A string unique to the current computer
XString XSystem::onlyString() noexcept
{
	static XString			_StaticOnlyString;
	if(_StaticOnlyString.empty())
	{
#if defined(XANADU_SYSTEM_WINDOWS)
		auto		vTempOnlyString = XSystem::nativeString() + "_CPU[" + XSystem::cpuID() + "]_DISK[" + XSystem::diskID() + "]_MachineGuid[";
		// 获取MachineGuid(重装系统后改变)
		HKEY		vKey = nullptr;
		LSTATUS		vResult = ERROR_SUCCESS;
		if(XSystem::is_64bit())
		{
			vResult = RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Cryptography", NULL, KEY_READ | KEY_WOW64_64KEY, &vKey);
		}
		else
		{
			vResult = RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Cryptography", NULL, KEY_READ, &vKey);
		}
		if(ERROR_SUCCESS == vResult)
		{
			wchar_t		vBuffer[MAX_PATH] = { 0 };
			DWORD		vLength = MAX_PATH;
			DWORD		vType = REG_SZ;
			x_posix_memset(vBuffer, 0, sizeof(wchar_t) * MAX_PATH);
			LSTATUS		vQuery = RegQueryValueExW(vKey, L"MachineGuid", nullptr, &vType, (byte*)vBuffer, &vLength);
			if(vQuery == ERROR_SUCCESS)
			{
				vTempOnlyString += XString::fromWString(vBuffer);
			}
			RegCloseKey(vKey);
		}
		vTempOnlyString += "]";
#endif
#if defined(XANADU_SYSTEM_LINUX)
		auto		vTempOnlyString = XSystem::nativeString() + XSystem::diskID() + "]_MachineGuid[";
		vTempOnlyString += XString::number(static_cast<std::int64_t>(x_posix_gethostid()));
		vTempOnlyString += "]";
#endif
#if defined(XANADU_SYSTEM_DARWIN)
		auto		vTempOnlyString = XSystem::nativeString() + XSystem::diskID() + "]_MachineGuid[";
		vTempOnlyString += XString::number(static_cast<std::int64_t>(gethostid()));
		// 获取macOS计算机序列号
		XShell::run("ioreg -rd1 -c IOPlatformExpertDevice | awk \'/IOPlatformSerialNumber/ { print $3; }\'", [&](const XString& _Output)->bool
		{
			auto		vIOPlatformSerialNumber = _Output;
			vIOPlatformSerialNumber.remove("\"");
			vIOPlatformSerialNumber = vIOPlatformSerialNumber.simplified();
			vTempOnlyString += "-";
			vTempOnlyString += vIOPlatformSerialNumber;
			return true;
		});
		// Get Hardware UUID in Mac OS X
		XShell::run("system_profiler SPHardwareDataType | awk \'/UUID/ { print $3; }\'", [&](const XString& _Output)->bool
		{
			vTempOnlyString += "-";
			vTempOnlyString += _Output;
			return true;
		});
		vTempOnlyString += "]";
#endif
		_StaticOnlyString = XString::fromBytes(XHash::hash(vTempOnlyString.toBytes(), XHash::MD5).toHex().toUpper());
	}
	return _StaticOnlyString;
}
