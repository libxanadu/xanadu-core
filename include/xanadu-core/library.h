#ifndef			_XANADU_CORE_LIBRARY_H_
#define			_XANADU_CORE_LIBRARY_H_

#include <xanadu-core/string.h> // NOLINT(modernize-deprecated-headers)


/// namespace xanadu
namespace xanadu
{
	/// class library
	class _XCOREAPI_ library
	{
	public:
		using				library_handle = void*;
		using				func_address = void*;

	public:
		xanadu::string			_library_path;
		library_handle			_library_handle;

	public:
		// constructor
		library() noexcept;

		// constructor
		explicit library(const xanadu::string& _DllPath) noexcept;

		// destructor
		virtual ~library() noexcept;

	private:
		// operator overload =
		library& operator = (const library& _Library) noexcept;

		// operator overload =
		library& operator = (library&& _Library) noexcept;

	public:
		// 打开动态链接库
		virtual bool open() noexcept final;

		// 打开动态链接库
		virtual bool open(const xanadu::string& _DllPath) noexcept final;

		// 关闭动态链接库
		virtual void close() noexcept final;

	public:
		// 是否已经打开
		virtual bool is_open() const noexcept final;

		// 动态链接库的路径
		virtual const xanadu::string& dll_path() const noexcept final;

	public:
		// 在动态链接库中查找函数
		virtual func_address find(const xanadu::string& _Function) noexcept final;

	public:
		// [static] 打开动态链接库
		static library_handle dlopen(const xanadu::string& _DllPath) noexcept;

		// [static] 在动态链接库中查找函数
		static func_address dlsym(library_handle _Handle, const xanadu::string& _Function) noexcept;

		// [static] 关闭动态链接库
		static void dlclose(library_handle _Handle) noexcept;
	};
}

#endif
