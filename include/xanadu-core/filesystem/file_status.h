#ifndef			_XANADU_CORE_FS_FILE_STATUS_H_
#define			_XANADU_CORE_FS_FILE_STATUS_H_

#include <xanadu-core/header.h>
#include <xanadu-core/string.h> // NOLINT(modernize-deprecated-headers)
#include <xanadu-core/filesystem/perms.h>
#include <xanadu-core/filesystem/file_type.h>


// namespace xanadu::filesystem
namespace xanadu::filesystem
{
	/// class file_status
	class _XCOREAPI_ file_status
	{
	public:
		using				size_type = xanadu::uint64_t;
		using				time_type = xanadu::int64_t;
		using				perms_type = xanadu::filesystem::perms;

	private:
		size_type			_file_size;
		file_type			_file_type;
		perms_type			_file_perms;
		time_type			_create_time;
		time_type			_modify_time;
		time_type			_access_time;

	public:
		// constructor
		file_status() noexcept;

		// constructor
		file_status(const file_type& _FileType, const perms_type& _FilePerms) noexcept;

		// constructor
		file_status(size_type _FileSize, const file_type& _FileType, const perms_type& _FilePerms, time_type _CreateTime, time_type _ModifyTime, time_type _AccessTime) noexcept;

		// constructor
		file_status(const file_status& _Other) noexcept;

		// constructor
		file_status(file_status&& _Other) noexcept;

		// destructor
		virtual ~file_status() noexcept;

	public:
		// operator overload =
		file_status& operator = (const file_status& _Other) noexcept;

		// operator overload =
		file_status& operator = (file_status&& _Other) noexcept;

	public:
		// 文件大小
		virtual void size(size_type _FileSize) noexcept final;

		// 文件属性
		virtual void type(file_type _FileType) noexcept final;

		// 文件权限
		virtual void perms(perms_type _FilePerms) noexcept final;

		// 文件创建时间
		virtual void create_time(time_type _CreateTime) noexcept final;

		// 文件修改时间
		virtual void modify_time(time_type _ModifyTime) noexcept final;

		// 文件访问时间
		virtual void access_time(time_type _AccessTime) noexcept final;

	public:
		// 文件大小
		virtual size_type size() const noexcept final;

		// 文件属性
		virtual file_type type() const noexcept final;

		// 文件权限
		virtual perms_type perms() const noexcept final;

		// 文件创建时间
		virtual time_type create_time() const noexcept final;

		// 文件修改时间
		virtual time_type modify_time() const noexcept final;

		// 文件访问时间
		virtual time_type access_time() const noexcept final;
	};
}


#endif
