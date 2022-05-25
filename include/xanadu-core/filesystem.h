#ifndef			_XANADU_CORE_FILESYSTEM_H_
#define			_XANADU_CORE_FILESYSTEM_H_

#include <xanadu-core/header.h>
#include <xanadu-core/string.h> // NOLINT(modernize-deprecated-headers)
#include <xanadu-core/filesystem/file.h>
#include <xanadu-core/filesystem/directory.h>


// namespace x::filesystem
namespace x::filesystem
{
	// 检查路径是否存在
	_XCOREAPI_ bool path_is_exist(const path& _Path) noexcept;

	// 检查路径是否为文件
	_XCOREAPI_ bool path_is_file(const path& _Path) noexcept;

	// 检查路径是否为目录
	_XCOREAPI_ bool path_is_dir(const path& _Path) noexcept;
}


// namespace x::filesystem
namespace x::filesystem
{
	// 查询文件状态
	_XCOREAPI_ file_status status(const path& _Path) noexcept;

	// 查询链接状态
	_XCOREAPI_ file_status symlink_status(const path& _Path) noexcept;

	// 检查路径是否存在
	_XCOREAPI_ bool exists(const path& _Target) noexcept;

	// 检查路径是否存在
	_XCOREAPI_ bool exists(const file_status& _Status) noexcept;

	// 文件或目录是否为空
	_XCOREAPI_ bool is_empty(const path& _Path) noexcept;

	// 查询文件大小
	_XCOREAPI_ x::uint64_t file_size(const path& _Path) noexcept;

	// 重新设定文件大小
	_XCOREAPI_ bool resize_file(const path& _Target, x::uint64_t _New_size) noexcept;

	// is_block_file
	_XCOREAPI_ bool is_block_file(const path& _Path) noexcept;

	// is_block_file
	_XCOREAPI_ bool is_block_file(const file_status& _Status) noexcept;

	// is_character_file
	_XCOREAPI_ bool is_character_file(const path& _Path) noexcept;

	// is_character_file
	_XCOREAPI_ bool is_character_file(const file_status& _Status) noexcept;

	// is_directory
	_XCOREAPI_ bool is_directory(const path& _Path) noexcept;

	// is_directory
	_XCOREAPI_ bool is_directory(const file_status& _Status) noexcept;

	// is_fifo
	_XCOREAPI_ bool is_fifo(const path& _Path) noexcept;

	// is_fifo
	_XCOREAPI_ bool is_fifo(const file_status& _Status) noexcept;

	// is_other
	_XCOREAPI_ bool is_other(const path& _Path) noexcept;

	// is_other
	_XCOREAPI_ bool is_other(const file_status& _Status) noexcept;

	// is_regular_file
	_XCOREAPI_ bool is_regular_file(const path& _Path) noexcept;

	// is_regular_file
	_XCOREAPI_ bool is_regular_file(const file_status& _Status) noexcept;

	// is_socket
	_XCOREAPI_ bool is_socket(const path& _Path) noexcept;

	// is_socket
	_XCOREAPI_ bool is_socket(const file_status& _Status) noexcept;

	// is_symlink
	_XCOREAPI_ bool is_symlink(const path& _Path) noexcept;

	// is_symlink
	_XCOREAPI_ bool is_symlink(const file_status& _Status) noexcept;
}


// namespace x::filesystem
namespace x::filesystem
{
	// 创建目录
	_XCOREAPI_ bool create_directory(const path& _Path) noexcept;

	// 递归创建目录
	_XCOREAPI_ bool create_directories(const path& _Path) noexcept;

	// 创建目录
	_XCOREAPI_ bool create_directory(const path& _Path, int _Mode) noexcept;

	// 递归创建目录
	_XCOREAPI_ bool create_directories(const path& _Path, int _Mode) noexcept;

	// 设置权限
	_XCOREAPI_ bool permissions(const path& _Target, perms _Perms) noexcept;

	// 设置权限
	_XCOREAPI_ bool permissions(const path& _Target, perms _Perms, perm_options _Options) noexcept;

	// 移除路径
	_XCOREAPI_ bool remove(const path& _Target) noexcept;

	// 重命名路径
	_XCOREAPI_ bool rename(const path& _Old_p, const path& _New_p) noexcept;

	// 复制文件
	_XCOREAPI_ bool copy_file(const path& _From, const path& _To) noexcept;

	// 复制文件
	_XCOREAPI_ bool copy_file(const path& _From, const path& _To, copy_options _Options) noexcept;

	// 复制
	_XCOREAPI_ bool copy(const path& _From, const path& _To) noexcept;

	// 复制
	_XCOREAPI_ bool copy(const path& _From, const path& _To, copy_options _Options) noexcept;
}


#endif
