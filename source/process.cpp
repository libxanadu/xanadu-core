#include <xanadu-core/process.h>
#if defined(XANADU_SYSTEM_WINDOWS)
#include <tlhelp32.h>
#include <psapi.h>
#endif
#if defined(XANADU_SYSTEM_LINUX)
#include <xanadu-core/filesystem.h>
#include <sys/wait.h>
#endif
#if defined(XANADU_SYSTEM_DARWIN)
#include <libproc.h>
#endif



// constructor
x::process::process() noexcept
{
	this->_process_id = 0;
}

// constructor
x::process::process(const process& _Other) noexcept = default;

// constructor
x::process::process(process&& _Other) noexcept = default;

// destructor
x::process::~process() noexcept = default;





// operator overload =
x::process& x::process::operator = (const process& _Other) noexcept = default;

// operator overload =
x::process& x::process::operator = (process&& _Other) noexcept = default;





// 遍历所有进程
bool x::process::process_traverse(const std::function<bool(const x::process& _ProcessInfo)>& _Lambda) noexcept
{
	if(_Lambda == nullptr)
	{
		return false;
	}

	auto		vSync = false;

#if defined(XANADU_SYSTEM_WINDOWS)
	auto		vSnapshotHandle = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	auto		vProcessEntry32 = PROCESSENTRY32W();
	vProcessEntry32.dwSize = sizeof(vProcessEntry32);
	if(vSnapshotHandle != INVALID_HANDLE_VALUE)
	{
		vSync = true;
		auto		vMore = ::Process32FirstW(vSnapshotHandle, &vProcessEntry32);
		while(vMore)
		{
			if(!_Lambda(x::process::from_process_id(static_cast<x::process::id_type>(vProcessEntry32.th32ProcessID), x::string::fromWString(vProcessEntry32.szExeFile))))
			{
				break;
			}
			vMore = ::Process32NextW(vSnapshotHandle, &vProcessEntry32);
		};
		::CloseHandle(vSnapshotHandle);
	}
#endif
#if defined(XANADU_SYSTEM_LINUX)
	vSync = x::filesystem::dir_traverse("/proc", [&](const x::filesystem::file_info& _FileInfo)->bool
	{
		if(_FileInfo.path().is_dir())
		{
			if(!_Lambda(x::process::from_process_id(static_cast<x::process::id_type>(_FileInfo.path().filename().toLLong()))))
			{
				return false;
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
					if(!_Lambda(x::process::from_process_id(static_cast<x::process::id_type>(vProcessID))))
					{
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

// 查询所有进程数量
x::uint64_t x::process::process_count() noexcept
{
	x::uint64_t	vNumber = 0;
	x::process::process_traverse([&](const x::process& _ProcessInfo)->bool
	{
		XANADU_UNUSED(_ProcessInfo);
		++vNumber;
		return true;
	});
	return vNumber;
}

// 查询指定名称进程数量
x::uint64_t x::process::process_number(const x::string& _ProcessName) noexcept
{
	if(_ProcessName.empty())
	{
		return 0;
	}

	x::uint64_t	vNumber = 0;
	x::process::process_traverse([&](const x::process& _ProcessInfo)->bool
	{
		if(_ProcessInfo.name() == _ProcessName)
		{
			++vNumber;
		}
		return true;
	});
	return vNumber;
}

// 根据进程ID终止进程
bool x::process::terminate(unsigned long long _ProcessID) noexcept
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

// 根据进程名称终止进程
bool x::process::terminate(const x::string& _ProcessName) noexcept
{
	if(_ProcessName.empty())
	{
		return false;
	}

	auto		vSync = true;
	x::process::process_traverse([&](const x::process& _ProcessInfo)->bool
	{
		if(_ProcessInfo.name() == _ProcessName)
		{
			vSync = x::process::terminate(_ProcessInfo.id());
		}
		return true;
	});
	return vSync;
}





// 当前进程
x::process x::process::current_process() noexcept
{
	return x::process::from_process_id(x::process::current_process_id());
}

// 当前进程ID
x::process::id_type x::process::current_process_id() noexcept
{
	return static_cast<x::process::id_type>(x_posix_getpid());
}





// args 转换为 string
x::string x::process::args_to_string(char** _Args) noexcept
{
	x::string	vString;
	for(int vIndex = 0; _Args[vIndex]; ++vIndex)
	{
		if(vIndex != 0)
		{
			vString.append(' ');
		}
		vString.append(_Args[vIndex]);
	}
	return vString;
}

// string 转换为 args
char** x::process::string_to_args(const x::string& _Args) noexcept
{
	auto		vProgram = std::string(_Args.data());
	auto		vArgs = std::vector<std::string>();
	auto 		vTemp = std::string();
	auto		vQuoteCount = 0;
	auto		vInQuote = false;
	char**		vArgsC = nullptr;

	// handle quoting. tokens can be surrounded by double quotes
	// "hello world". three consecutive double quotes represent
	// the quote character itself.
	for (char vIndex : vProgram)
	{
		if (vIndex == '\"')
		{
			++vQuoteCount;
			if (vQuoteCount == 3)
			{
				// third consecutive quote
				vQuoteCount = 0;
				vTemp += vIndex;
			}
			continue;
		}
		if (vQuoteCount)
		{
			if (vQuoteCount == 1)
			{
				vInQuote = !vInQuote;
			}
			vQuoteCount = 0;
		}
		if (!vInQuote && vIndex == ' ')
		{
			if (!vTemp.empty())
			{
				vArgs.push_back(vTemp);
				vTemp.clear();
			}
		}
		else
		{
			vTemp += vIndex;
		}
	}
	if (!vTemp.empty())
	{
		vArgs.push_back(vTemp);
	}

	vArgsC = (char**) x_posix_malloc(sizeof(char*) * (vArgs.size() + 1));
	for(auto vIndex = 0U; vIndex < vArgs.size(); ++vIndex)
	{
		vArgsC[vIndex] = x_posix_strdup(vArgs[vIndex].data());
	}
	vArgsC[vArgs.size()] = nullptr;
	return vArgsC;
}

// args 释放
void x::process::args_free(char** _Args) noexcept
{
	if(_Args == nullptr)
	{
		return;
	}
	for(auto vIndex = 0; _Args[vIndex]; ++vIndex)
	{
		x_posix_free(_Args[vIndex]);
	}
	x_posix_free(_Args);
}





// 输出所有换行数据
void x::process::read_output_printf_newline(output_type& _Bytes, const callback_type& _Lambda) noexcept
{
	do{
		auto		vFind = _Bytes.find('\n');
		if(vFind == output_type::npos)
		{
			break;
		}
		else
		{
			if(_Lambda)
			{
				_Lambda(_Bytes.left(vFind));
			}
			_Bytes.remove(static_cast<output_type::size_type>(0), vFind + 1);
		}
	}while(true);
}

// 从句柄读取输出
void x::process::read_output_from_descriptor(int _Handle, const callback_type& _Lambda) noexcept
{
	auto		vBuffer = new(std::nothrow) char[XANADU_SIZE_KB];
	auto		vBytes = output_type();
	for(; vBuffer;)
	{
		x_posix_memset(vBuffer, 0, XANADU_SIZE_KB);
		auto		vSync = x_posix_read(_Handle, vBuffer, XANADU_SIZE_KB);
		if(0 < vSync && vSync <= (int)XANADU_SIZE_KB)
		{
			vBytes.append(vBuffer, vSync);
		}
		x::process::read_output_printf_newline(vBytes, _Lambda);
		if(0 == vSync)
		{
			if(0 != x_posix_errno())
			{
				break;
			}
		}
		else if(vSync < 0)
		{
			break;
		}
		if(vSync > (int)XANADU_SIZE_KB)
		{
			break;
		}
	}
	if(_Lambda)
	{
		_Lambda(vBytes);
	}
	delete[] vBuffer;
}

// 从句柄读取输出
void x::process::read_output_from_file(FILE* _Handle, const callback_type& _Lambda) noexcept
{
	auto		vBuffer = new(std::nothrow) char[XANADU_SIZE_KB];
	auto		vBytes = output_type();
	for(; vBuffer;)
	{
		x_posix_memset(vBuffer, 0, XANADU_SIZE_KB);
		auto		vSync = x_posix_fread(vBuffer, 1, XANADU_SIZE_KB, _Handle);
		if(0 < vSync && vSync <= XANADU_SIZE_KB)
		{
			vBytes.append(vBuffer, vSync);
		}
		x::process::read_output_printf_newline(vBytes, _Lambda);
		if(0 == vSync)
		{
			if(0 != x_posix_ferror(_Handle) || 0 != x_posix_feof(_Handle))
			{
				break;
			}
		}
		if(vSync > XANADU_SIZE_KB)
		{
			break;
		}
	}
	if(_Lambda)
	{
		_Lambda(vBytes);
	}
	delete[] vBuffer;
}

// 从句柄读取输出
void x::process::read_output_from_handle(HANDLE _Handle, const callback_type& _Lambda) noexcept
{
#if defined(XANADU_SYSTEM_WINDOWS)
	auto		vBuffer = new(std::nothrow) char[XANADU_SIZE_KB];
	auto		vBytes = output_type();
	auto		vSync = static_cast<DWORD>(0);
	for(; vBuffer;)
	{
		x_posix_memset(vBuffer, 0, XANADU_SIZE_KB);
		auto		vSuccess = (::ReadFile(_Handle, vBuffer, XANADU_SIZE_KB, &vSync, nullptr) == TRUE);
		if(vSuccess && vSync > 0)
		{
			vBytes.append(vBuffer, vSync);
		}
		x::process::read_output_printf_newline(vBytes, _Lambda);
		if(!vSuccess)
		{
			if(ERROR_BROKEN_PIPE == ::GetLastError())
			{
				break;
			}
		}
	}
	if(_Lambda)
	{
		_Lambda(vBytes);
	}
	delete[] vBuffer;
#else
	XANADU_UNUSED(_Handle);
	XANADU_UNUSED(_Lambda);
#endif
}





// 从进程ID构建数据
x::process x::process::from_process_id(id_type _ProcessID) noexcept
{
	x::process	vProcessInfo = x::process::from_process_id(_ProcessID, nullptr);
#if defined(XANADU_SYSTEM_WINDOWS)
	auto		vFind = vProcessInfo._process_path.rfind("/");
	if(vFind != x::string::npos)
	{
		vProcessInfo._process_name = vProcessInfo._process_path.substr(vFind + 1);
	}
#endif
#if defined(XANADU_SYSTEM_LINUX)
	auto		vFind = vProcessInfo._process_path.rfind("/");
	if(vFind != x::string::npos)
	{
		vProcessInfo._process_name = vProcessInfo._process_path.substr(vFind + 1);
	}
#endif
#if defined(XANADU_SYSTEM_DARWIN)
	char		vProcessName[XANADU_PATH_MAX] = { 0 };
	proc_name(_ProcessID, vProcessName, XANADU_PATH_MAX);
	vProcessInfo._process_name = vProcessName;
#endif
	return vProcessInfo;
}

// 从进程ID构建数据
x::process x::process::from_process_id(id_type _ProcessID, const x::string& _ProcessName) noexcept
{
	x::process	vProcessInfo;
	vProcessInfo._process_id = _ProcessID;
	vProcessInfo._process_name = _ProcessName;

#if defined(XANADU_SYSTEM_WINDOWS)

	wchar_t 	vProcessPath[XANADU_PATH_MAX] = {0};
	HMODULE		vModule = nullptr;
	DWORD		dwReturn = 0;
	auto		dwProcessID = static_cast<DWORD>(_ProcessID);
	auto		vProcess = (HMODULE)OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, dwProcessID);
	if(vProcess == nullptr)
	{
		return vProcessInfo;
	}

	// 方法1：GetModuleFileNameEx
	GetModuleFileNameExW(vProcess, nullptr, vProcessPath, XANADU_PATH_MAX);
	if (0 == GetModuleFileNameExW(vProcess, nullptr, vProcessPath, XANADU_PATH_MAX))
	{
		// 方法2：EnumProcessModules --> GetModuleFileNameEx
		if (EnumProcessModules(vProcess, &vModule, sizeof(HMODULE), &dwReturn))
		{
			//dwRet = GetModuleFileName(hMod, szPath, MAX_PATH);
			GetModuleFileNameExW(vProcess, vModule, vProcessPath, XANADU_PATH_MAX);
		}
	}

	::CloseHandle(vProcess);
	vProcessInfo._process_path = x::string::fromWString(vProcessPath).replace("\\", "/");
#endif
#if defined(XANADU_SYSTEM_LINUX)
	auto		vProcessExe = x::string::format("/proc/%llu/exe", _ProcessID);
	char		vProcessPath[XANADU_PATH_MAX] = {0};

	auto		vCount = readlink(vProcessExe.data(), vProcessPath, XANADU_PATH_MAX);
	if(0 <= vCount || vCount <= XANADU_PATH_MAX)
	{
		vProcessInfo._process_path = vProcessPath;
	}
#endif
#if defined(XANADU_SYSTEM_DARWIN)
	char		vProcessPath[XANADU_PATH_MAX] = {0};
	proc_pidpath(_ProcessID, vProcessPath, XANADU_PATH_MAX);
	vProcessInfo._process_path = vProcessPath;
#endif
	return vProcessInfo;
}





// 进程ID
x::process::id_type x::process::id() const noexcept
{
	return this->_process_id;
}

// 进程名称
const x::string& x::process::name() const noexcept
{
	return this->_process_name;
}

// 进程路径
const x::string& x::process::path() const noexcept
{
	return this->_process_path;
}





// 执行 exec 系列函数
int x::process::execds(const x::string& _Application, const x::string& _Directory, const x::string& _Param) noexcept
{
	if(_Application.empty())
	{
		return -1;
	}

	auto		vSync = -1;
	auto		vExecParam = _Application + (_Param.exist() ? " " : "") + _Param;
	auto		vArgs = x::process::string_to_args(vExecParam.data());

	// 我们需要改变工作目录
	if(_Directory.exist())
	{
		x_posix_chdir(_Directory.data());
	}

	// 在这里调用exec系列函数
#if defined(XANADU_SYSTEM_WINDOWS)
	vSync = ::_execv(_Application.data(), vArgs);
#else
	vSync = ::execv(_Application.data(), vArgs);
#endif
	x::process::args_free(vArgs);
	return vSync;
}





// 同步运行
int x::process::sync_run(const x::string& _Application) noexcept
{
	return x::process::async_run(_Application, nullptr, nullptr);
}

// 同步运行
int x::process::sync_run(const x::string& _Application, const x::string& _Directory) noexcept
{
	return x::process::async_run(_Application, _Directory, nullptr);
}

// 同步运行
int x::process::sync_run(const x::string& _Application, const x::string& _Directory, const x::string& _Param) noexcept
{
#if defined(XANADU_SYSTEM_WINDOWS)
	DWORD			vExitCode = STATUS_INVALID_HANDLE;
	SHELLEXECUTEINFOW	vInfoShell = {sizeof(SHELLEXECUTEINFOW) };
	HANDLE			vHandle = nullptr;
	auto			vWApplication = _Application.toWString();
	auto			vWParam = _Param.toWString();
	auto			vWDirectory = _Directory.toWString();
	vInfoShell.fMask = SEE_MASK_NOCLOSEPROCESS | SEE_MASK_FLAG_NO_UI;
	vInfoShell.lpFile = vWApplication.data();
	vInfoShell.lpParameters = vWParam.data();
	vInfoShell.lpDirectory = vWDirectory.data();
	vInfoShell.nShow = SW_HIDE;
	if(ShellExecuteExW(&vInfoShell))
	{
		vHandle = vInfoShell.hProcess;
		if(vHandle)
		{
			WaitForSingleObject(vHandle, INFINITE);
			vExitCode = STILL_ACTIVE;
			GetExitCodeProcess(vHandle, &vExitCode);
			CloseHandle(vHandle);
		}
	}
	else
	{
		// STATUS_INVALID_HANDLE
		vExitCode = GetLastError();
	}
	return (int)vExitCode;
#else
	auto		vSync = fork();
	int 		vStatus = 0;
	if(vSync > 0)
	{
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
	else if(vSync == 0)
	{
		if(-1 == x::process::execds(_Application, _Directory, _Param))
		{
			x_posix_exit(0);
		}
	}
	return -1;
#endif
}





// 同步运行
int x::process::sync_run(const x::string& _Application, const callback_type& _Lambda) noexcept
{
	return x::process::sync_run(_Application, nullptr, nullptr, _Lambda);
}

// 同步运行
int x::process::sync_run(const x::string& _Application, const x::string& _Directory, const callback_type& _Lambda) noexcept
{
	return x::process::sync_run(_Application, _Directory, nullptr, _Lambda);
}

// 同步运行
int x::process::sync_run(const x::string& _Application, const x::string& _Directory, const x::string& _Param, const callback_type& _Lambda) noexcept
{
	if(_Lambda == nullptr)
	{
		return x::process::sync_run(_Application, _Directory, _Param);
	}

#if defined(XANADU_SYSTEM_WINDOWS)
	auto			vApplicationW = _Application.toWString();
	auto			vDirectoryW = _Directory.toWString();
	auto			vParamW = _Param.toWString();
	SECURITY_ATTRIBUTES	sa;
	HANDLE			vRHandle = nullptr;
	HANDLE			vWHandle = nullptr;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = nullptr;
	sa.bInheritHandle = TRUE;

	// 创建匿名管道
	if (::CreatePipe(&vRHandle, &vWHandle, &sa, 0))
	{
		STARTUPINFOW		si;
		PROCESS_INFORMATION	pi;
		x_posix_memset(&si, 0, sizeof(STARTUPINFOW));
		si.cb = sizeof(STARTUPINFO);
		::GetStartupInfoW(&si);
		si.hStdError = vWHandle;
		si.hStdOutput = vWHandle;
		si.wShowWindow = SW_HIDE;
		si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;

		// 创建子进程
		if (::CreateProcessW(vApplicationW.data(), vParamW.data(), nullptr, nullptr, TRUE, NULL, nullptr, nullptr, &si, &pi))
		{
			::CloseHandle(vWHandle);
			x::process::read_output_from_handle(vRHandle, _Lambda);
			::CloseHandle(vRHandle);

			// 等待进程结束
			::WaitForSingleObject(pi.hProcess, INFINITE);
			auto		vExitCode = static_cast<DWORD>(STILL_ACTIVE);
			::GetExitCodeProcess(pi.hProcess, &vExitCode);
			// ::CloseHandle(pi.hProcess);
			return (int)vExitCode;
		}
	}
	return (int)GetLastError();
#else
	auto		vExecParam = _Application + (_Param.exist() ? " " : "") + _Param;
	auto		vHandle = x_posix_popen(vExecParam.data(), "r");
	if(vHandle)
	{
		x::process::read_output_from_file(vHandle, _Lambda);
		return x_posix_pclose(vHandle);
	}
#endif
	return -1;
}





// 异步运行
int x::process::async_run(const x::string& _Application) noexcept
{
	return x::process::async_run(_Application, nullptr, nullptr);
}

// 异步运行
int x::process::async_run(const x::string& _Application, const x::string& _Directory) noexcept
{
	return x::process::async_run(_Application, _Directory, nullptr);
}

// 异步运行
int x::process::async_run(const x::string& _Application, const x::string& _Directory, const x::string& _Param) noexcept
{
#if defined(XANADU_SYSTEM_WINDOWS)
	DWORD			vExitCode = STATUS_INVALID_HANDLE;
	SHELLEXECUTEINFOW	vInfoShell = {sizeof(SHELLEXECUTEINFOW) };
	auto		vWApplication = _Application.toWString();
	auto		vWParam = _Param.toWString();
	auto		vWDirectory = _Directory.toWString();
	vInfoShell.fMask = SEE_MASK_NOCLOSEPROCESS | SEE_MASK_FLAG_NO_UI;
	vInfoShell.lpFile = vWApplication.data();
	vInfoShell.lpParameters = vWParam.data();
	vInfoShell.lpDirectory = vWDirectory.data();
	vInfoShell.nShow = SW_HIDE;
	if(ShellExecuteExW(&vInfoShell))
	{
		vExitCode = 0;
	}
	else
	{
		// STATUS_INVALID_HANDLE
		vExitCode = GetLastError();
	}
	return (int)vExitCode;
#else
	auto		vSync = fork();
	if(vSync > 0)
	{
		return 0;
	}
	else if(vSync == 0)
	{
		if(-1 == x::process::execds(_Application, _Directory, _Param))
		{
			x_posix_exit(0);
		}
	}
	return -1;
#endif
}
