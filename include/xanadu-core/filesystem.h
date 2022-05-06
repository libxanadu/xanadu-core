#ifndef			_XANADU_CORE_FILESYSTEM_H_
#define			_XANADU_CORE_FILESYSTEM_H_

#include <xanadu-core/header.h>
#include <xanadu-core/string.h> // NOLINT(modernize-deprecated-headers)
#include <xanadu-core/filesystem/copy_options.h>
#include <xanadu-core/filesystem/file_status.h>
#include <xanadu-core/filesystem/file_info.h>
#include <xanadu-core/filesystem/path.h>


// namespace xanadu::filesystem
namespace xanadu::filesystem
{
	/// class file
	class _XCOREAPI_ file
	{
	public:
		// constructor
		file() noexcept;

		// constructor
		file(const file& _Other) noexcept;

		// constructor
		file(file&& _Other) noexcept;

		// destructor
		virtual ~file() noexcept;

	public:
		// operators overload =
		file& operator = (const file& _Other) noexcept;

		// operators overload =
		file& operator = (file&& _Other) noexcept;
	};

	/// class directory
	class _XCOREAPI_ directory
	{
	public:
		// constructor
		directory() noexcept;

		// constructor
		directory(const directory& _Other) noexcept;

		// constructor
		directory(directory&& _Other) noexcept;

		// destructor
		virtual ~directory() noexcept;

	public:
		// operators overload =
		directory& operator = (const directory& _Other) noexcept;

		// operators overload =
		directory& operator = (directory&& _Other) noexcept;
	};
}


// namespace xanadu::filesystem
namespace xanadu::filesystem
{
	typedef struct _xanadu_fs_dir_stream
	{
		void*			handle;
		xanadu::string		directory;
	}xanadu_fs_dir_stream;

	using		string_type = xanadu::string;
	using 		bytes_type = xanadu::string;
	using 		file_stream = void*;
	using 		dir_stream = xanadu_fs_dir_stream*;

	using		func_fs_file_cb_t = std::function<bool(xanadu::uint64_t _Progress, xanadu::uint64_t _Total)>;
	using 		func_fs_remove_cb_t = std::function<bool(const path& _Path)>;
	using 		func_fs_copy_cb_t = std::function<bool(const path& _Source, const path& _Target)>;
	using 		func_fs_traverse_cb_t = std::function<bool(const file_info& _FileInfo)>;
}


// namespace xanadu::filesystem
namespace xanadu::filesystem
{
	// 检查路径是否存在
	_XCOREAPI_ bool path_is_exist(const path& _Path) noexcept;

	// 检查路径是否为文件
	_XCOREAPI_ bool path_is_file(const path& _Path) noexcept;

	// 检查路径是否为目录
	_XCOREAPI_ bool path_is_dir(const path& _Path) noexcept;
}


// namespace xanadu::filesystem
namespace xanadu::filesystem
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
	_XCOREAPI_ xanadu::uint64_t file_size(const path& _Path) noexcept;

	// 重新设定文件大小
	_XCOREAPI_ bool resize_file(const path& _Target, xanadu::uint64_t _New_size) noexcept;

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


// namespace xanadu::filesystem
namespace xanadu::filesystem
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


// namespace xanadu::filesystem
namespace xanadu::filesystem
{
	// 打开文件
	_XCOREAPI_ file_stream fopen(const path& _Path, const char* _Flags) noexcept;

	// 设置文件指针位置
	_XCOREAPI_ xanadu::int64_t fseek(file_stream _Stream, xanadu::int64_t _Offset, int _Origin) noexcept;

	// 当前文件指针位置
	_XCOREAPI_ xanadu::int64_t ftell(file_stream _Stream) noexcept;

	// 是否已经到文件尾
	_XCOREAPI_ bool feof(file_stream _Stream) noexcept;

	// 读取所有数据
	_XCOREAPI_ bool fread(file_stream _Stream, void* _Buffer, uint64_t _Length) noexcept;

	// 读取一行数据
	_XCOREAPI_ bytes_type fread_line(file_stream _Stream) noexcept;

	// 读取指定长度的数据
	_XCOREAPI_ uint64_t fread(void* _Buffer, uint64_t _Size, uint64_t _Count, file_stream _Stream) noexcept;

	// 写入所有数据
	_XCOREAPI_ bool fwrite(file_stream _Stream, const void* _Buffer, uint64_t _Length) noexcept;

	// 写入所有数据
	_XCOREAPI_ bool fwrite(file_stream _Stream, const bytes_type& _Buffer) noexcept;

	// 写入指定长度的数据
	_XCOREAPI_ uint64_t fwrite(const void* _Buffer, uint64_t _Size, uint64_t _Count, file_stream _Stream) noexcept;

	// 刷新缓冲区
	_XCOREAPI_ bool fflush(file_stream _Stream) noexcept;

	// 关闭文件
	_XCOREAPI_ bool fclose(file_stream _Stream) noexcept;
}


// namespace xanadu::filesystem
namespace xanadu::filesystem
{
	// 打开目录
	_XCOREAPI_ dir_stream dir_open(const path& _Path) noexcept;

	// 读取目录子项
	_XCOREAPI_ bool dir_read(dir_stream _Stream, file_info& _FileInfo) noexcept;

	// 关闭目录
	_XCOREAPI_ bool dir_close(dir_stream _Stream) noexcept;

	// 遍历目录
	_XCOREAPI_ bool dir_traverse(const path& _Path, const func_fs_traverse_cb_t& _Function) noexcept;

	// 计算目录子项
	_XCOREAPI_ uint64_t dir_count(const path& _Path) noexcept;
}

#endif
