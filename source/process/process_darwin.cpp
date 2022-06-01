#include <source/process/process_common.h>



// 从内存中运行进程
int x_process_run_memory_application(const X_PROCESS_RUN_MEMORY_APPLICATION* _Context, const std::function<bool(const XString& _Output)>& _Lambda) noexcept
{
	XANADU_UNUSED(_Context);
	XANADU_UNUSED(_Lambda);

	return -1;
}
