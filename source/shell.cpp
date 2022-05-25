#include <xanadu-core/shell.h>
#include <xanadu-core/process.h>



// constructor
x::shell::shell() noexcept = default;

// destructor
x::shell::~shell() noexcept = default;





// operator overload =
x::shell& x::shell::operator = (const shell& _Other) noexcept = default;

// operator overload =
x::shell& x::shell::operator = (shell&& _Other) noexcept = default;





// 执行本机system命令
int x::shell::system(const x::string& _Command) noexcept
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
int x::shell::sync_run(const x::string& _Shell) noexcept
{
	if(_Shell.empty())
	{
		return -1;
	}

#if defined(XANADU_SYSTEM_WINDOWS)
	return static_cast<int>(x::process::sync_run("cmd.exe", nullptr, _Shell));
#else
#if defined(XANADU_SYSTEM_ARM)
	return static_cast<int>(x::process::sync_run("/bin/sh", nullptr, x::string("-c ") + _Shell));
#else
	return static_cast<int>(x::process::sync_run("/bin/bash", nullptr, x::string("-c ") + _Shell));
#endif
#endif
}

// 同步运行并接收结果
int x::shell::sync_run(const x::string& _Shell, const callback_type& _Lambda) noexcept
{
	if(_Lambda == nullptr)
	{
		return x::shell::sync_run(_Shell);
	}

	auto		vArgs = x::process::string_to_args(_Shell.data());
	auto		vApplication = x::string(vArgs[0]);
	auto		vParam = x::process::args_to_string(vArgs[0] ? (vArgs + 1) : nullptr);
	x::process::args_free(vArgs);

	return x::process::sync_run(vApplication, nullptr, vParam, _Lambda);
}

// 异步运行
int x::shell::async_run(const x::string& _Shell) noexcept
{
	if(_Shell.empty())
	{
		return -1;
	}

#if defined(XANADU_SYSTEM_WINDOWS)
	return static_cast<int>(x::process::async_run("cmd.exe", nullptr, _Shell));
#else
	#if defined(XANADU_SYSTEM_ARM)
	return static_cast<int>(x::process::async_run("/bin/sh", nullptr, x::string("-c ") + _Shell));
#else
	return static_cast<int>(x::process::async_run("/bin/bash", nullptr, x::string("-c ") + _Shell));
#endif
#endif
}
