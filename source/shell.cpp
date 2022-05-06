#include <xanadu-core/shell.h>
#include <xanadu-core/process.h>



// constructor
xanadu::shell::shell() noexcept = default;

// destructor
xanadu::shell::~shell() noexcept = default;





// operators overload =
xanadu::shell& xanadu::shell::operator = (const shell& _Other) noexcept = default;

// operators overload =
xanadu::shell& xanadu::shell::operator = (shell&& _Other) noexcept = default;





// 执行本机system命令
int xanadu::shell::system(const xanadu::string& _Command) noexcept
{
	if(_Command.empty())
	{
		return -1;
	}

#if defined(XANADU_SYSTEM_WINDOWS)
	return x_posix_wsystem(_Command.toWString().data());
#else
	return x_posix_system(_Command.toUString().data());
#endif
}





// 同步运行
int xanadu::shell::sync_run(const xanadu::string& _Shell) noexcept
{
	if(_Shell.empty())
	{
		return -1;
	}

#if defined(XANADU_SYSTEM_WINDOWS)
	return static_cast<int>(xanadu::process::sync_run("cmd.exe", nullptr, _Shell));
#else
#if defined(XANADU_SYSTEM_ARM)
	return static_cast<int>(xanadu::process::sync_run("/bin/sh", nullptr, xanadu::string("-c ") + _Shell));
#else
	return static_cast<int>(xanadu::process::sync_run("/bin/bash", nullptr, xanadu::string("-c ") + _Shell));
#endif
#endif
}

// 同步运行并接收结果
int xanadu::shell::sync_run(const xanadu::string& _Shell, const callback_type& _Lambda) noexcept
{
	if(_Lambda == nullptr)
	{
		return xanadu::shell::sync_run(_Shell);
	}

	auto		vArgs = xanadu::process::string_to_args(_Shell.data());
	auto		vApplication = xanadu::string(vArgs[0]);
	auto		vParam = xanadu::process::args_to_string(vArgs[0] ? (vArgs + 1) : nullptr);
	xanadu::process::args_free(vArgs);

	return xanadu::process::sync_run(vApplication, nullptr, vParam, _Lambda);
}

// 异步运行
int xanadu::shell::async_run(const xanadu::string& _Shell) noexcept
{
	if(_Shell.empty())
	{
		return -1;
	}

#if defined(XANADU_SYSTEM_WINDOWS)
	return static_cast<int>(xanadu::process::async_run("cmd.exe", nullptr, _Shell));
#else
	#if defined(XANADU_SYSTEM_ARM)
	return static_cast<int>(xanadu::process::async_run("/bin/sh", nullptr, xanadu::string("-c ") + _Shell));
#else
	return static_cast<int>(xanadu::process::async_run("/bin/bash", nullptr, xanadu::string("-c ") + _Shell));
#endif
#endif
}
