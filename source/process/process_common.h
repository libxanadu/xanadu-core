#ifndef			_XANADU_CORE_RUN_MEMORY_APP_H_
#define			_XANADU_CORE_RUN_MEMORY_APP_H_

#include <xanadu-core/xanadu.h>


// 结构
typedef struct X_PROCESS_RUN_MEMORY_APPLICATION
{
	const unsigned char*		AppMemory;
	uint64_t			AppLength;
	const char*			RunParameter;
	const char*			RunDirectory;
	const char*			HostApp;
}X_PROCESS_RUN_MEMORY_APPLICATION;


// 从句柄读取输出
void x_process_read_output_from_handle(HANDLE _Handle, const std::function<bool(const XString& _Output)>& _Lambda) noexcept;

// 从句柄读取输出
void x_process_read_output_from_file(FILE* _Handle, const std::function<bool(const XString& _Output)>& _Lambda) noexcept;

// 从句柄读取输出
void x_process_read_output_from_descriptor(int _Handle, const std::function<bool(const XString& _Output)>& _Lambda) noexcept;



// 进程参数转换
char** x_process_param_string_to_argv(const char* _Argv) noexcept;

// 进程参数转换
char* x_process_param_argv_to_string(char** _Argv) noexcept;

// 进程参数释放
void x_process_param_free(char** _Argv) noexcept;



// 从内存中运行进程
int x_process_run_memory_application(const X_PROCESS_RUN_MEMORY_APPLICATION* _Context, const std::function<bool(const XString& _Output)>& _Lambda) noexcept;



#endif
