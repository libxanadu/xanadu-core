#include <xanadu-core/XProcess.h>
#include <xanadu-core/XFileSystem.h>
#include <xanadu-core/XNative.h>
#include <xanadu-core/XSystem.h>
#if defined(XANADU_SYSTEM_WINDOWS)
#include <tlhelp32.h>
#endif
#if defined(XANADU_SYSTEM_DARWIN)
#include <libproc.h>
#endif
#include <source/process/process_common.h>




// 获取子项值
XString RegisterKeyValue(HKEY _Key, const WString& _Guid, const WString& _Name)
{
	auto		vKeyValue = XString();
#if defined(XANADU_SYSTEM_WINDOWS)
	auto		vLocalKey = static_cast<HKEY>(nullptr);
	auto		vResult = RegOpenKeyExW(_Key, _Guid.data(), NULL, KEY_READ, &vLocalKey);
	if(vResult == ERROR_SUCCESS)
	{
		wchar_t		vBuffer[MAX_PATH] = { 0 };
		auto		vLength = DWORD(MAX_PATH);
		auto		vType = DWORD(REG_SZ);
		x_posix_memset(vBuffer, 0, sizeof(wchar_t) * MAX_PATH);
		auto		vQuery = RegQueryValueExW(vLocalKey, _Name.data(), nullptr, &vType, (byte*)vBuffer, &vLength);
		if(vQuery == ERROR_SUCCESS)
		{
			vKeyValue = XString::fromWString(vBuffer);
		}
	}
#endif
	return vKeyValue;
}

XProcess::XProcess() noexcept = default;

XProcess::~XProcess() noexcept = default;



// Kills the process by the specified name
bool XProcess::kill(const XString& _ProcessName) noexcept
{
	if(_ProcessName.empty())
	{
		return false;
	}

	auto		vSync = true;
	XProcess::traverse([&](const XProcessInfo& _ProcessInfo)->bool
	{
		if(_ProcessInfo.getProcessName() == _ProcessName)
		{
			vSync = XProcess::kill(_ProcessInfo.getProcessID());
		}
		return true;
	});
	return vSync;
}

// Kill the process with the specified process ID
bool XProcess::kill(unsigned long long _ProcessID) noexcept
{
	auto		vSync = true;
#if defined(XANADU_SYSTEM_WINDOWS)
	auto		vProcess = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, static_cast<DWORD>(_ProcessID));
	if(vProcess != nullptr)
	{
		vSync = ::TerminateProcess(vProcess, 0);
		::CloseHandle(vProcess);
	}
#else
	vSync = x_posix_kill(_ProcessID, 9) == 0;
#endif
	return vSync;
}



// Gets the current process ID
std::uint64_t XProcess::currentProcessID() noexcept
{
	return static_cast<std::uint64_t>(x_posix_getpid());
}



// Traverses the list of currently running processes
bool XProcess::traverse(const std::function<bool(const XProcessInfo& _Info)>& _Lambda) noexcept
{
	XANADU_CHECK_RETURN(_Lambda, false);

	auto		vSync = false;

#if defined(XANADU_SYSTEM_WINDOWS)
	auto		vProcessEntry32 = PROCESSENTRY32W();
	vProcessEntry32.dwSize = sizeof(vProcessEntry32);
	auto		vSnapshotHandle = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if(vSnapshotHandle != INVALID_HANDLE_VALUE)
	{
		vSync = true;
		auto		vMore = ::Process32FirstW(vSnapshotHandle, &vProcessEntry32);
		while(vMore)
		{
			if(!_Lambda(XProcessInfo(static_cast<std::uint64_t>(vProcessEntry32.th32ProcessID), XString::fromWString(vProcessEntry32.szExeFile))))
			{
				// If the caller cancels the operation, then we should jump out of the loop
				break;
			}
			vMore = ::Process32NextW(vSnapshotHandle, &vProcessEntry32);
		};
		::CloseHandle(vSnapshotHandle);
	}
#endif
#if defined(XANADU_SYSTEM_LINUX)
	vSync = XFileSystem::directory::traverse("/proc", [&](const XFileSystem::path& _Path)->bool
	{
		if(XFileSystem::path::isDirectory(_Path))
		{
			auto		vExepath = XString::format("/proc/%ls/exe", _Path.fileName().data());
			auto		vApplication = vExepath.toUString();
			char		vDirectory[XANADU_PATH_MAX] = { 0 };
			auto		vCount = readlink(vApplication.data(), vDirectory, XANADU_PATH_MAX);
			if(0 <= vCount || vCount <= XANADU_PATH_MAX)
			{
				if(x_posix_strlen(vDirectory))
				{
					auto		vName = x_posix_strrchr(vDirectory, '/') + 1;
					if(vName && x_posix_strlen(vName))
					{
						if(false == _Lambda(XProcessInfo(static_cast<std::uint64_t>(_Path.fileName().toLLong()), XString::fromUString(vName))))
						{
							// If the caller cancels the operation, then we should jump out of the loop
							return false;
						}
					}
				}
			}
		}
		return true;
	});
#endif
#if defined(XANADU_SYSTEM_DARWIN)
	auto		vProcessNumber = proc_listpids(PROC_ALL_PIDS, 0, NULL, 0) * 2;
	if(vProcessNumber)
	{
		auto	vProcessArray = (pid_t*)x_posix_malloc(sizeof(pid_t) * vProcessNumber);
		if(vProcessArray)
		{
			vProcessNumber = proc_listpids(PROC_ALL_PIDS, 0, vProcessArray, sizeof(pid_t) * vProcessNumber);
			if(vProcessNumber)
			{
				vSync = true;
				for(auto vIndex = 0; vIndex < vProcessNumber; ++vIndex)
				{
					pid_t           vProcessID = vProcessArray[vIndex];
					if(vProcessID == 0)
					{
						continue;
					}
					char			vProcessNAME[1024] = { 0 };
					//char			vProcessPATH[2048] = { 0 };
					//struct proc_bsdinfo     vProcessINFO;
					proc_name(vProcessID, vProcessNAME, 1024);
					//proc_pidpath(vProcessID, vProcessPATH, 2048);
					//proc_pidinfo(vProcessID, PROC_PIDTBSDINFO, 0, &vProcessINFO, PROC_PIDTBSDINFO_SIZE);
					if(false == _Lambda(XProcessInfo(static_cast<std::uint64_t>(vProcessID), XString::fromUString(vProcessNAME))))
					{
						// If the caller cancels the operation, then we should jump out of the loop
						break;
					}
				}
			}
			x_posix_free(vProcessArray);
		}
	}
#endif
	return vSync;
}



// Does the specified process name exist
bool XProcess::isExist(const XString& _ProcessName) noexcept
{
	if(_ProcessName.empty())
	{
		return false;
	}

	if(XProcess::number(_ProcessName) > 0)
	{
		return true;
	}
	return false;
}

// How many instances of the specified process name
std::uint64_t XProcess::number(const XString& _ProcessName) noexcept
{
	if(_ProcessName.empty())
	{
		return 0;
	}

	auto		vNumber = 0;
	XProcess::traverse([&](const XProcessInfo& _ProcessInfo)->bool
	{
		if(_ProcessInfo.getProcessName() == _ProcessName)
		{
			++vNumber;
		}
		return true;
	});
	return vNumber;
}

// 运行并等待进程
std::uint64_t XProcess::execute(const XString& _Application, const XString& _Param, const XString& _Directory, bool _Wait, bool _UI) noexcept
{
#if defined(XANADU_SYSTEM_WINDOWS)
	DWORD			vExitCode = STATUS_INVALID_HANDLE;
	SHELLEXECUTEINFOW	vInfoShell = {sizeof(SHELLEXECUTEINFOW) };
	if (_UI)
	{
		vInfoShell.fMask = SEE_MASK_NOCLOSEPROCESS;
	}
	else
	{
		vInfoShell.fMask = SEE_MASK_NOCLOSEPROCESS | SEE_MASK_FLAG_NO_UI;
	}
	auto		vWApplication = _Application.toWString();
	auto		vWParam = _Param.toWString();
	auto		vWDirectory = _Directory.toWString();
	vInfoShell.lpFile = vWApplication.data();
	vInfoShell.lpParameters = vWParam.data();
	vInfoShell.lpDirectory = vWDirectory.data();
	vInfoShell.nShow = _UI ? SW_SHOW : SW_HIDE;
	if(ShellExecuteExW(&vInfoShell))
	{
		auto	vHandle = vInfoShell.hProcess;
		if(vHandle)
		{
			if(_Wait)
			{
				WaitForSingleObject(vHandle, INFINITE);
				vExitCode = STILL_ACTIVE;
				GetExitCodeProcess(vHandle, &vExitCode);
				CloseHandle(vHandle);
			}
			else
			{
				vExitCode = 0;
			}
		}
	}
	else
	{
		// STATUS_INVALID_HANDLE
		vExitCode = GetLastError();
	}
	return vExitCode;
#else
	auto		vSync = fork();
	if(vSync > 0)
	{
		if(_Wait)
		{
			int 	vStatus = 0;
			::waitpid(vSync, &vStatus, 0);
			if(WIFEXITED(vStatus))
			{
				return WEXITSTATUS(vStatus);
			}
			else
			{
				return WTERMSIG(vStatus);
			}
		}
		return 0;
	}
	else if(vSync == 0)
	{
		auto		vNApplication = _Application.toNString();
		auto		vNDirectory = _Directory.toNString();
		auto		vNParam = _Param.toNString();
		if(-1 == XProcess::execds(vNApplication.data(), vNDirectory.data(), vNParam.data()))
		{
			x_posix_exit(0);
		}
	}
	return -1;
#endif
}

// Loads and executes new child processes.
int XProcess::execds(const char* _Application, const char* _Directory, const char* _Param) noexcept
{
	auto		vSync = -1;
	auto		vExecParam = std::string(_Application ? _Application : "") + " " + std::string(_Param ? _Param : "");
	auto		vArgs = x_process_param_string_to_argv(vExecParam.data());

	// 我们需要改变工作目录
	x_posix_chdir(_Directory);

	// 在这里调用exec系列函数
#if defined(XANADU_SYSTEM_WINDOWS)
	vSync = ::_execv(_Application, vArgs);
#else
	vSync = ::execv(_Application, vArgs);
#endif

	x_process_param_free(vArgs);
	return vSync;
}

// 在内存中运行进程
int XProcess::run_memory_app(const XProcessRunMemoryInfo& _MemoryInfo, const std::function<bool(const XString& _Output)>& _Lambda) noexcept
{
	auto		vRunStatus = 0;
	auto		vContext = new(std::nothrow) X_PROCESS_RUN_MEMORY_APPLICATION();
	if(vContext == nullptr)
	{
		return -1;
	}
	x_posix_memset(vContext, 0, sizeof(X_PROCESS_RUN_MEMORY_APPLICATION));

	vContext->AppMemory = (unsigned char*)_MemoryInfo._memberMemoryApp.data();
	vContext->AppLength = _MemoryInfo._memberMemoryApp.size();
	vContext->RunParameter = _MemoryInfo._memberParam.data();
	vContext->RunDirectory = _MemoryInfo._memberDirectory.data();
	vContext->HostApp = _MemoryInfo._memberHostApp.data();

	vRunStatus = x_process_run_memory_application(vContext, _Lambda);

	x_posix_free(vContext);

	return vRunStatus;
}



// 枚举卸载列表
bool XProcess::program(std::function<void(const XANADU_CORE_PROCESS_UNINSTALL* _Info)> _Lambda) noexcept
{
	auto		vResult = false;
#if defined(XANADU_SYSTEM_WINDOWS)
	XANADU_CHECK_RETURN(_Lambda, vResult);
	auto		FunctionEnumItem = [&](HKEY _Key, bool _X86)
	{
		LONG		vResult = 0;
		DWORD		vIndex = 0;
		do
		{
			wchar_t		vBuffer[MAX_PATH] = { 0 };
			DWORD		vLength = MAX_PATH;
			x_posix_memset(vBuffer, 0, sizeof(wchar_t) * MAX_PATH);
			vResult = RegEnumKeyExW(_Key, vIndex, vBuffer, &vLength, nullptr, nullptr, nullptr, nullptr);
			if(vResult == ERROR_SUCCESS)
			{
				auto	vInfo = new(std::nothrow) XANADU_CORE_PROCESS_UNINSTALL();
				if(vInfo)
				{
					vInfo->_IsX86 = _X86;
					vInfo->_IsX64 = !_X86;
					vInfo->_Label = XString::fromWString(vBuffer);
					vInfo->_Location = RegisterKeyValue(_Key, vBuffer, L"InstallLocation");
					vInfo->_Name = RegisterKeyValue(_Key, vBuffer, L"DisplayName");
					vInfo->_Uninstall = RegisterKeyValue(_Key, vBuffer, L"UninstallString");
					vInfo->_Version = RegisterKeyValue(_Key, vBuffer, L"DisplayVersion");
					_Lambda(vInfo);
					XANADU_DELETE_PTR(vInfo);
				}
			}
			++vIndex;
		} while(vResult != ERROR_NO_MORE_ITEMS);
	};

	//获取32位
	{
		HKEY		vKey = nullptr;
		LONG		vRegedit = RegOpenKeyExA(HKEY_LOCAL_MACHINE, R"(SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall)", NULL, KEY_READ, &vKey);
		if(ERROR_SUCCESS == vRegedit)
		{
			FunctionEnumItem(vKey, true);
			RegCloseKey(vKey);
			vResult = true;
		}
	}
	//获取64位
	if(XSystem::is_64bit())
	{
		HKEY		vKey = nullptr;
		LONG		vRegedit = RegOpenKeyExA(HKEY_LOCAL_MACHINE, R"(SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall)", NULL, KEY_READ | KEY_WOW64_64KEY, &vKey);
		if(ERROR_SUCCESS == vRegedit)
		{
			FunctionEnumItem(vKey, false);
			RegCloseKey(vKey);
			vResult = true;
		}
	}
#endif
#if defined(XANADU_SYSTEM_LINUX)
#endif
#if defined(XANADU_SYSTEM_DARWIN)
	/*
	XFileSystem::DirectoryList("/Applications", [&](const XFileInfo& _Info)->bool
	{
		if(_Info.isDir())
		{
			auto	vUninstall = Dynamic::plist_from_file(_Info.filePath() + "/Contents/Info.plist");
			if(vUninstall)
			{
				auto	vInfo = new(std::nothrow) XANADU_CORE_PROCESS_UNINSTALL();
				if(vInfo)
				{
					vInfo->_IsX86 = false;
					vInfo->_IsX64 = true;
					vInfo->_Label = Dynamic::plist_node_get_string(Dynamic::plist_dict_get_item(vUninstall, "CFBundleExecutable"));
					vInfo->_Location = L"";
					vInfo->_Name = Dynamic::plist_node_get_string(Dynamic::plist_dict_get_item(vUninstall, "CFBundleDisplayName"));
					vInfo->_Uninstall = L"";
					vInfo->_Version = Dynamic::plist_node_get_string(Dynamic::plist_dict_get_item(vUninstall, "CFBundleShortVersionString"));
					_Lambda(vInfo);
					XANADU_DELETE_PTR(vInfo);
				}
				Dynamic::plist_free(vUninstall);
			}
		}
		return true;
	});
	*/
#endif
	return vResult;
}
