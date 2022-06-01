#include <xanadu-core/XShell.h>
#include <xanadu-core/XProcess.h>
#include <source/process/process_common.h>


XShell::XShell() noexcept = default;

XShell::~XShell() noexcept = default;



// Async run shell
int XShell::run(const XString& _Shell) noexcept
{
	XANADU_CHECK_RETURN(_Shell.exist(), -1);

#if defined(XANADU_SYSTEM_WINDOWS)
	return static_cast<int>(XProcess::execute("cmd.exe", _Shell));
#else
#if defined(XANADU_SYSTEM_ARM)
	return static_cast<int>(XProcess::execute("/bin/sh", XString("-c ") + _Shell));
#else
	return static_cast<int>(XProcess::execute("/bin/bash", XString("-c ") + _Shell));
#endif
#endif
}

// Sync run shell
int XShell::run(const XString& _Shell, const std::function<bool(const XString& _Output)>& _Lambda) noexcept
{
	XANADU_CHECK_RETURN(_Shell.exist(), -1);

#if defined(XANADU_SYSTEM_WINDOWS)
	auto			vShell = _Shell.toWString();
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

		wchar_t 	vApplication[XANADU_PATH_MAX] = {0};
		auto		vCommandLine = new(std::nothrow) wchar_t[static_cast<size_t>(vShell.size()) + 100];
		if(vCommandLine)
		{
			x_posix_wmemset(vCommandLine, 0, static_cast<size_t>(vShell.size()) + 100);
			auto		vPos = XString::npos;
			if(vShell[0] == L'\"')
			{
				vPos = vShell.find(L'\"', 1U);
				if(vPos != XString::npos)
				{
					vPos += 1;
				}
			}
			else
			{
				vPos = vShell.find(L' ');
			}
			if(vPos == XString::npos)
			{
				vPos = 0;
				x_posix_wmemcpy(vApplication, vShell.data(), vPos);
			}
			else
			{
				x_posix_wmemcpy(vApplication, vShell.data(), vPos);
				vPos += 1;
			}
			x_posix_wmemcpy(vCommandLine, vShell.data() + vPos, static_cast<size_t>(vShell.size() - vPos));

			// 修复 CreateProcess GetLastError = 123 的错误
			if(vApplication[0] == L'\"' && vApplication[x_posix_wcslen(vApplication) - 1] == L'\"')
			{
				vApplication[x_posix_wcslen(vApplication) - 1] = L'\0';
				x_posix_wmemmove(vApplication, vApplication + 1, x_posix_wcslen(vApplication) - 1);
				vApplication[x_posix_wcslen(vApplication) - 1] = L'\0';
			}
			// 创建子进程
			if (::CreateProcessW(vApplication, vCommandLine, nullptr, nullptr, TRUE, NULL, nullptr, nullptr, &si, &pi))
			{
				::CloseHandle(vWHandle);
				x_process_read_output_from_handle(vRHandle, _Lambda);
				::CloseHandle(vRHandle);

				// 等待进程结束
				::WaitForSingleObject(pi.hProcess, INFINITE);
				auto		vExitCode = static_cast<DWORD>(STILL_ACTIVE);
				::GetExitCodeProcess(pi.hProcess, &vExitCode);
				// ::CloseHandle(pi.hProcess);
				XANADU_DELETE_ARR(vCommandLine);
				return (int)vExitCode;
			}
			else
			{
				XANADU_DELETE_ARR(vCommandLine);
				return (int)GetLastError();
			}

		}
	}
#else
	auto		vHandle = x_posix_popen(_Shell.toNString().data(), "r");
	if(vHandle)
	{
		x_process_read_output_from_file(vHandle, _Lambda);
		return x_posix_pclose(vHandle);
	}
#endif
	return -1;
}

// Native system
int XShell::system(const XString& _Command) noexcept
{
	XANADU_CHECK_RETURN(_Command.exist(), -1);
#if defined(XANADU_SYSTEM_WINDOWS)
	return x_posix_wsystem(_Command.toWString().data());
#else
	return x_posix_system(_Command.toUString().data());
#endif
}
