#ifndef			_XANADU_CORE_SHELL_H_
#define			_XANADU_CORE_SHELL_H_

#include <xanadu-core/header.h>
#include <xanadu-core/string.h> // NOLINT(modernize-deprecated-headers)


/// namespace xanadu
namespace x
{
	/// class shell
	class _XCOREAPI_ shell
	{
	public:
		using				output_type = x::string;
		using				callback_type = std::function<void(const output_type& _Output)>;

	public:
		// constructor
		shell() noexcept;

		// destructor
		virtual ~shell() noexcept;

	public:
		// operator overload =
		shell& operator = (const shell& _Other) noexcept;

		// operator overload =
		shell& operator = (shell&& _Other) noexcept;

	public:
		// 执行本机system命令
		static int system(const x::string& _Command) noexcept;

	public:
		// 同步运行
		static int sync_run(const x::string& _Shell) noexcept;

		// 同步运行并接收结果
		static int sync_run(const x::string& _Shell, const callback_type& _Lambda) noexcept;

		// 异步运行
		static int async_run(const x::string& _Shell) noexcept;
	};
}

#endif
