#ifndef			_XANADU_CORE_FS_PATH_H_
#define			_XANADU_CORE_FS_PATH_H_

#include <xanadu-core/header.h>
#include <xanadu-core/string.h> // NOLINT(modernize-deprecated-headers)
#include <xanadu-core/filesystem/file_status.h>


// namespace xanadu::filesystem
namespace xanadu::filesystem
{
	/// class path
	class _XCOREAPI_ path
	{
	public:
		using				_Elem = xanadu::string::_Elem;
		using				value_type = _Elem;
		using				string_type = xanadu::string;

	public:
		static const value_type		path_separator = '/';

	private:
		string_type			_path_absolute;

	public:
		// constructor
		path() noexcept;

		// constructor
		path(const path& _Other) noexcept;

		// constructor
		path(path&& _Other) noexcept;

		// destructor
		virtual ~path() noexcept;

	public:
		// constructor
		path(const _Elem* _String) noexcept; // NOLINT(google-explicit-constructor)

		// constructor
		path(const string_type& _String) noexcept; // NOLINT(google-explicit-constructor)

		// constructor
		path(string_type&& _String) noexcept; // NOLINT(google-explicit-constructor)

	public:
		// operators overload =
		path& operator = (const path& _Other) noexcept;

		// operators overload =
		path& operator = (path&& _Other) noexcept;

	public:
		// operators overload =
		path& operator = (const _Elem* _String) noexcept;

		// operators overload =
		path& operator = (const string_type& _String) noexcept;

		// operators overload =
		path& operator = (string_type&& _String) noexcept;

	public:
		// operators overload +
		path operator + (const _Elem* _String) const noexcept;

		// operators overload +
		path operator + (const string_type& _String) const noexcept;

		// operators overload +
		path operator + (const path& _Path) const noexcept;

	public:
		// operators overload +=
		path& operator += (const _Elem* _String) noexcept;

		// operators overload +=
		path& operator += (const string_type& _String) noexcept;

		// operators overload +=
		path& operator += (const path& _Path) noexcept;

	public:
		// operators overload +=
		path operator / (const _Elem* _String) const noexcept;

		// operators overload /
		path operator / (const string_type& _String) const noexcept;

		// operators overload /
		path operator / (const path& _Path) const noexcept;

	public:
		// operators overload /=
		path& operator /= (const _Elem* _String) noexcept;

		// operators overload /=
		path& operator /= (const string_type& _String) noexcept;

		// operators overload /=
		path& operator /= (const path& _Path) noexcept;

	public:
		// operators overload string_type
		operator string_type() const noexcept; // NOLINT(google-explicit-constructor)

	public:
		// 格式化至通用路径
		static string_type format_to_common(const string_type& _String) noexcept;

		// 格式化至本机路径
		static string_type format_to_native(const string_type& _String) noexcept;

		// 转换至绝对路径
		static string_type convert_to_absolute(const string_type& _String) noexcept;

		// 检查名称是否符合规范
		static bool check_is_correct(const path& _Path) noexcept;

	public:
		// 本机路径
		virtual string_type native_path() const noexcept final;

		// 文件路径
		virtual string_type filepath() const noexcept final;

		// 父目录
		virtual string_type parent_dir() const noexcept final;

		// 文件名称
		virtual string_type filename() const noexcept final;

		// 去除后缀名的文件名称
		virtual string_type stem() const noexcept final;

		// 后缀名
		virtual string_type extension() const noexcept final;

		// 后缀名
		virtual string_type suffix() const noexcept final;

	public:
		// 判断是否存在
		virtual bool is_exist() const noexcept final;

		// 判断是否为目录
		virtual bool is_dir() const noexcept final;

		// 判断是否为文件
		virtual bool is_file() const noexcept final;
	};
}


#endif
