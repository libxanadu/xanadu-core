#include <source/process/process_common.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <linux/memfd.h>



// 从内存中运行进程
int x_process_run_memory_application(const X_PROCESS_RUN_MEMORY_APPLICATION* _Context, const std::function<bool(const XString& _Output)>& _Lambda) noexcept
{
	XANADU_UNUSED(_Context);
	XANADU_UNUSED(_Lambda);

	auto		AppMemory = _Context->AppMemory;
	auto		AppLength = _Context->AppLength;
	auto		RunParameter = x_process_param_string_to_argv(_Context->RunParameter);
	auto		RunDirectory = _Context->RunDirectory;
	char		HostPath[256] = "\0";
	int		HostHandle = 0;
	pid_t		AppProcessID = x_posix_getpid();
	pid_t		AppChild = 0;
	int		AppSync[2] = {0};
	int		vAppStatus = -1;
	char		RMA_NAME[128] = {0};

	// 使用系统调用创建内存句柄
	x_posix_sprintf(RMA_NAME, "rma-%lld", (long long)x_time_system_millisecond());
	HostHandle = syscall(SYS_memfd_create, RMA_NAME, MFD_CLOEXEC);
	// x_posix_write(HostHandle, AppMemory, AppLength);
	uint64_t 	vAlready = 0;
	size_t 		vSync = 0;

	while(vAlready < AppLength)
	{
		vSync = x_posix_write(HostHandle, AppMemory + vAlready, AppLength - vAlready);
		if(vSync <= 0)
		{
			break;
		}
		vAlready += vSync;
	}
	if(vAlready != AppLength)
	{
		XLOG_DEBUG("CORE", u8"memory write error");
		return -1;
	}

	x_posix_sprintf(HostPath,"/proc/%d/fd/%d", AppProcessID, HostHandle);

	// 设置环境变量
	auto		vLoadDirectory = XString(x_posix_getenv("LD_LIBRARY_PATH"));
	vLoadDirectory += ":";
	vLoadDirectory += RunDirectory;
	x_posix_setenv("LD_LIBRARY_PATH", vLoadDirectory.data(), 1);

	auto		vRunParam0 = RunParameter[0];
	RunParameter[0] = HostPath;
	auto		vRunShell = x_process_param_argv_to_string(RunParameter);
	RunParameter[0] = vRunParam0;

	auto		vHandle = x_posix_popen(vRunShell, "r");
	if(vHandle)
	{
		x_process_read_output_from_file(vHandle, _Lambda);
		vAppStatus = x_posix_pclose(vHandle);
		x_posix_close(HostHandle);
		return vAppStatus;
	}

	pipe(AppSync);

	AppChild = fork();
	if (AppChild == 0)
	{
		x_posix_close(AppSync[0]);
		x_posix_close(1);
		x_posix_close(2);
		x_posix_dup2(AppSync[1], 1);
		x_posix_dup2(AppSync[1], 2);

		x_posix_chdir(RunDirectory);
		execve(HostPath, RunParameter, nullptr);
		return 0;
	}
	else if (AppChild == -1)
	{
		x_posix_close(HostHandle);
		return -1;
	}
	else
	{
		x_posix_close(AppSync[1]);
		x_process_read_output_from_descriptor(AppSync[0], _Lambda);
		x_posix_close(AppSync[0]);
		waitpid(AppChild, &vAppStatus, 0);
		x_posix_close(HostHandle);
		return vAppStatus;
	}
}
