#ifndef			_XANADU_CORE_PROCESS_H_
#define			_XANADU_CORE_PROCESS_H_

#include <xanadu-core/header.h>
#include <xanadu-core/string.h> // NOLINT(modernize-deprecated-headers)


/// namespace xanadu
namespace x
{
	/// class process
	class _XCOREAPI_ process
	{
	public:
		using				output_type = x::string;
		using				callback_type = std::function<void(const output_type& _Output)>;
		using				id_type = x::uint64_t;

	private:
		id_type				_process_id;
		x::string			_process_name;
		x::string			_process_path;

	public:
		// constructor
		process() noexcept;

		// constructor
		process(const process& _Other) noexcept;

		// constructor
		process(process&& _Other) noexcept;

		// destructor
		virtual ~process() noexcept;

	public:
		// operator overload =
		process& operator = (const process& _Other) noexcept;

		// operator overload =
		process& operator = (process&& _Other) noexcept;

	public:
		// 遍历所有进程
		static bool process_traverse(const std::function<bool(const x::process& _ProcessInfo)>& _Lambda) noexcept;

		// 查询所有进程数量
		static x::uint64_t process_count() noexcept;

		// 查询指定名称进程数量
		static x::uint64_t process_number(const x::string& _ProcessName) noexcept;

		// 根据进程ID终止进程
		static bool terminate(unsigned long long _ProcessID) noexcept;

		// 根据进程名称终止进程
		static bool terminate(const x::string& _ProcessName) noexcept;

	public:
		// 当前进程
		static x::process current_process() noexcept;

		// 当前进程ID
		static id_type current_process_id() noexcept;

	public:
		// args 转换为 string
		static x::string args_to_string(char** _Args) noexcept;

		// string 转换为 args
		static char** string_to_args(const x::string& _Args) noexcept;

		// args 释放
		static void args_free(char** _Args) noexcept;

	public:
		// 输出所有已换行的数据
		static void read_output_printf_newline(output_type& _Bytes, const callback_type& _Lambda) noexcept;

		// 从句柄读取输出
		static void read_output_from_descriptor(int _Handle, const callback_type& _Lambda) noexcept;

		// 从句柄读取输出
		static void read_output_from_file(FILE* _Handle, const callback_type& _Lambda) noexcept;

		// 从句柄读取输出
		static void read_output_from_handle(HANDLE _Handle, const callback_type& _Lambda) noexcept;

	public:
		// 从进程ID构建数据
		static process from_process_id(id_type _ProcessID) noexcept;

		// 从进程ID构建数据
		static process from_process_id(id_type _ProcessID, const x::string& _ProcessName) noexcept;

	public:
		// 进程ID
		virtual id_type id() const noexcept final;

		// 进程名称
		virtual const x::string& name() const noexcept final;

		// 进程路径
		virtual const x::string& path() const noexcept final;

	public:
		// 执行 exec 系列函数
		static int execds(const x::string& _Application, const x::string& _Directory, const x::string& _Param) noexcept;

	public:
		// 同步运行
		static int sync_run(const x::string& _Application) noexcept;

		// 同步运行
		static int sync_run(const x::string& _Application, const x::string& _Directory) noexcept;

		// 同步运行
		static int sync_run(const x::string& _Application, const x::string& _Directory, const x::string& _Param) noexcept;

	public:
		// 同步运行并接收结果
		static int sync_run(const x::string& _Application, const callback_type& _Lambda) noexcept;

		// 同步运行并接收结果
		static int sync_run(const x::string& _Application, const x::string& _Directory, const callback_type& _Lambda) noexcept;

		// 同步运行并接收结果
		static int sync_run(const x::string& _Application, const x::string& _Directory, const x::string& _Param, const callback_type& _Lambda) noexcept;

	public:
		// 异步运行
		static int async_run(const x::string& _Application) noexcept;

		// 异步运行
		static int async_run(const x::string& _Application, const x::string& _Directory) noexcept;

		// 异步运行
		static int async_run(const x::string& _Application, const x::string& _Directory, const x::string& _Param) noexcept;
	};
}

#endif
