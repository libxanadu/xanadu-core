#ifndef			_XANADU_CORE_APPLICATION_H_
#define			_XANADU_CORE_APPLICATION_H_

#include <xanadu-core/header.h>
#include <xanadu-core/string.h> // NOLINT(modernize-deprecated-headers)


/// namespace xanadu
namespace xanadu
{
	/// class application
	class _XCOREAPI_ application
	{
	public:
		using				string_type = xanadu::string;

	public:
		// constructor
		application() noexcept;

		// constructor
		application(int _Argc, char* _Argv[]) noexcept;

		// constructor
		application(const application& _Other) noexcept;

		// constructor
		application(application&& _Other) noexcept;

		// destructor
		virtual ~application() noexcept;

	public:
		// operators overload =
		application& operator = (const application& _Other) noexcept;

		// operators overload =
		application& operator = (application&& _Other) noexcept;

	public:
		// 当前应用程序路径
		static const string_type& application_path() noexcept;

		// 当前应用程序目录
		static const string_type& application_directory() noexcept;

		// 当前应用程序名称
		static const string_type& application_name() noexcept;

		// 当前运行目录
		static string_type current_directory() noexcept;

		// 修改当前运行目录
		static string_type set_current_directory(const string_type& _Directory) noexcept;

	public:
		// 应用程序无后缀名称
		static const string_type& application_stem_name() noexcept;

		// 应用程序本地目录
		static const string_type& application_local_directory() noexcept;

		// 应用程序远程目录
		static const string_type& application_remote_directory() noexcept;

		// 应用程序缓存目录
		static const string_type& application_temp_directory() noexcept;

	public:
		// xanadu名称
		static const string_type& com_xanadu_name() noexcept;

		// xanadu本地目录
		static const string_type& xanadu_local_directory() noexcept;

		// xanadu远程目录
		static const string_type& xanadu_remote_directory() noexcept;

		// xanadu缓存目录
		static const string_type& xanadu_temp_directory() noexcept;
	};
}

#endif
