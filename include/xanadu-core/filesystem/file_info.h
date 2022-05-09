#ifndef			_XANADU_CORE_FILESYSTEM_FILE_INFO_H_
#define			_XANADU_CORE_FILESYSTEM_FILE_INFO_H_

#include <xanadu-core/header.h>
#include <xanadu-core/string.h> // NOLINT(modernize-deprecated-headers)
#include <xanadu-core/filesystem/copy_options.h>
#include <xanadu-core/filesystem/file_status.h>
#include <xanadu-core/filesystem/path.h>


// namespace xanadu::filesystem
namespace xanadu::filesystem
{
	/// class file_info
	class _XCOREAPI_ file_info
	{
	private:
		path				_file_path;

	public:
		// constructor
		file_info() noexcept;

		// constructor
		file_info(const file_info& _Other) noexcept;

		// constructor
		file_info(file_info&& _Other) noexcept;

		// destructor
		virtual ~file_info() noexcept;

	public:
		// constructor
		explicit file_info(const xanadu::filesystem::path& _Path) noexcept;

	public:
		// operator overload =
		file_info& operator = (const file_info& _Other) noexcept;

		// operator overload =
		file_info& operator = (file_info&& _Other) noexcept;

	public:
		// operator overload const path&
		operator const xanadu::filesystem::path& () const noexcept; // NOLINT(google-explicit-constructor)

	public:
		// 路径
		virtual const xanadu::filesystem::path& path() const noexcept final;
	};
}


#endif
