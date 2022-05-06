#include <xanadu-core/filesystem.h>



// 检查路径是否存在
_XCOREAPI_ bool xanadu::filesystem::path_is_exist(const path& _Path) noexcept
{
	auto		vFilePath = _Path.filepath();
#if defined(XANADU_SYSTEM_WINDOWS)
	return 0 == x_posix_waccess(vFilePath.toWString().data(), F_OK);
#else
	return 0 == x_posix_access(vFilePath.data(), F_OK);
#endif
}

// 检查路径是否为文件
_XCOREAPI_ bool xanadu::filesystem::path_is_file(const path& _Path) noexcept
{
	auto		vFilePath = _Path.filepath();
#if defined(XANADU_SYSTEM_WINDOWS)
	auto		vAttrib = ::GetFileAttributesW(vFilePath.toWString().data());
	if(INVALID_FILE_ATTRIBUTES != vAttrib && !(vAttrib & FILE_ATTRIBUTE_DIRECTORY))
	{
		return true;
	}
#else
	x_file_stat_t	vFileStatus{};
	if(0 == x_filesystem_stat(vFilePath.data(), &vFileStatus))
	{
		return !(S_ISDIR(vFileStatus.st_mode));
	}
#endif
	return false;
}

// 检查路径是否为目录
_XCOREAPI_ bool xanadu::filesystem::path_is_dir(const path& _Path) noexcept
{
	auto		vFilePath = _Path.filepath();
#if defined(XANADU_SYSTEM_WINDOWS)
	auto		vAttrib = ::GetFileAttributesW(vFilePath.toWString().data());
	if(INVALID_FILE_ATTRIBUTES != vAttrib && vAttrib & FILE_ATTRIBUTE_DIRECTORY)
	{
		return true;
	}
#else
	x_file_stat_t	vFileStatus{};
	if(0 == x_filesystem_stat(vFilePath.data(), &vFileStatus))
	{
		return S_ISDIR(vFileStatus.st_mode);
	}
#endif
	return false;
}





// 查询文件状态
_XCOREAPI_ xanadu::filesystem::file_status xanadu::filesystem::status(const path& _Path) noexcept
{
	auto		vFileStatus = xanadu::filesystem::file_status();
	auto 		vFileStat = x_file_stat_t();
	auto 		vSync = x_filesystem_stat(_Path.filepath().data(), &vFileStat);
	if(vSync != 0)
	{
		return {file_type::not_found, perms::unknown};
	}

	auto 		vFileType = file_type::none;

	// 检查类型
	if(S_ISBLK(vFileStat.st_mode))
	{
		vFileType = file_type::block;
	}
	else if(S_ISCHR(vFileStat.st_mode))
	{
		vFileType = file_type::character;
	}
	else if(S_ISDIR(vFileStat.st_mode))
	{
		vFileType = file_type::directory;
	}
	else if(S_ISFIFO(vFileStat.st_mode))
	{
		vFileType = file_type::fifo;
	}
	else if(S_ISREG(vFileStat.st_mode))
	{
		vFileType = file_type::regular;
	}
#if !defined(XANADU_SYSTEM_WINDOWS)
	else if(S_ISSOCK(vFileStat.st_mode))
	{
		vFileType = file_type::socket;
	}
#endif
	else if(S_ISLNK(vFileStat.st_mode))
	{
		vFileType = file_type::symlink;
	}

	return {static_cast<size_type>(vFileStat.st_size), vFileType, perms(vFileStat.st_mode), vFileStat.st_ctime, vFileStat.st_mtime, vFileStat.st_atime};
}

// 查询文件大小
_XCOREAPI_ xanadu::uint64_t xanadu::filesystem::file_size(const path& _Path) noexcept
{
	auto		vStatus = xanadu::filesystem::status(_Path);
	return vStatus.size();
}

// 查询链接状态
_XCOREAPI_ xanadu::filesystem::file_status xanadu::filesystem::symlink_status(const path& _Path) noexcept
{
	return xanadu::filesystem::status(_Path);
}

// 检查路径是否存在
_XCOREAPI_ bool xanadu::filesystem::exists(const path& _Target) noexcept
{
	return xanadu::filesystem::exists(xanadu::filesystem::status(_Target));
}

// 检查路径是否存在
_XCOREAPI_ bool xanadu::filesystem::exists(const file_status& _Status) noexcept
{
	if(_Status.type() == file_type::none || _Status.type() == file_type::not_found)
	{
		return false;
	}
	return true;
}

// 文件或目录是否为空
_XCOREAPI_ bool xanadu::filesystem::is_empty(const path& _Path) noexcept
{
	auto		vStatus = xanadu::filesystem::status(_Path);
	if(vStatus.type() == file_type::none || vStatus.type() == file_type::not_found)
	{
		return false;
	}

	if(xanadu::filesystem::is_directory(vStatus))
	{
		return xanadu::filesystem::dir_count(_Path) == 0;
	}
	else
	{
		return vStatus.size() == 0;
	}
}

// 重新设定文件大小
_XCOREAPI_ bool xanadu::filesystem::resize_file(const path& _Target, xanadu::uint64_t _New_size) noexcept
{
	auto		vFilePath = _Target.filepath();
#if defined(XANADU_SYSTEM_WINDOWS)
	auto		vHandle = CreateFileW(vFilePath.toWString().data(), GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	LARGE_INTEGER	vSize;
	vSize.QuadPart = (long long)_New_size;
	return vHandle != INVALID_HANDLE_VALUE && ::SetFilePointerEx(vHandle, vSize, nullptr, FILE_BEGIN) && ::SetEndOfFile(vHandle)  && ::CloseHandle(vHandle);
#else
	return ::truncate(vFilePath.data(), _New_size) == 0;
#endif
}

// is_block_file
_XCOREAPI_ bool xanadu::filesystem::is_block_file(const path& _Path) noexcept
{
	return xanadu::filesystem::is_block_file(status(_Path));
}

// is_block_file
_XCOREAPI_ bool xanadu::filesystem::is_block_file(const file_status& _Status) noexcept
{
	return _Status.type() == file_type::block;
}

// is_character_file
_XCOREAPI_ bool xanadu::filesystem::is_character_file(const path& _Path) noexcept
{
	return xanadu::filesystem::is_character_file(status(_Path));
}

// is_character_file
_XCOREAPI_ bool xanadu::filesystem::is_character_file(const file_status& _Status) noexcept
{
	return _Status.type() == file_type::character;
}

// is_directory
_XCOREAPI_ bool xanadu::filesystem::is_directory(const path& _Path) noexcept
{
	return xanadu::filesystem::is_directory(status(_Path));
}

// is_directory
_XCOREAPI_ bool xanadu::filesystem::is_directory(const file_status& _Status) noexcept
{
	return _Status.type() == file_type::directory;
}

// is_fifo
_XCOREAPI_ bool xanadu::filesystem::is_fifo(const path& _Path) noexcept
{
	return xanadu::filesystem::is_fifo(status(_Path));
}

// is_fifo
_XCOREAPI_ bool xanadu::filesystem::is_fifo(const file_status& _Status) noexcept
{
	return _Status.type() == file_type::fifo;
}

// is_other
_XCOREAPI_ bool xanadu::filesystem::is_other(const path& _Path) noexcept
{
	return xanadu::filesystem::is_other(status(_Path));
}

// is_other
_XCOREAPI_ bool xanadu::filesystem::is_other(const file_status& _Status) noexcept
{
	switch (_Status.type())
	{
		case file_type::none:
		case file_type::not_found:
		case file_type::regular:
		case file_type::directory:
		case file_type::symlink:
			return false;
		case file_type::block:
		case file_type::character:
		case file_type::fifo:
		case file_type::socket:
		case file_type::unknown:
		case file_type::junction:
		default:
			return true;
	}
}

// is_regular_file
_XCOREAPI_ bool xanadu::filesystem::is_regular_file(const path& _Path) noexcept
{
	return xanadu::filesystem::is_regular_file(status(_Path));
}

// is_regular_file
_XCOREAPI_ bool xanadu::filesystem::is_regular_file(const file_status& _Status) noexcept
{
	return _Status.type() == file_type::regular;
}

// is_socket
_XCOREAPI_ bool xanadu::filesystem::is_socket(const path& _Path) noexcept
{
	return xanadu::filesystem::is_socket(status(_Path));
}

// is_socket
_XCOREAPI_ bool xanadu::filesystem::is_socket(const file_status& _Status) noexcept
{
	return _Status.type() == file_type::socket;
}

// is_symlink
_XCOREAPI_ bool xanadu::filesystem::is_symlink(const path& _Path) noexcept
{
	return xanadu::filesystem::is_symlink(status(_Path));
}

// is_symlink
_XCOREAPI_ bool xanadu::filesystem::is_symlink(const file_status& _Status) noexcept
{
	return _Status.type() == file_type::symlink;
}





// 创建目录
_XCOREAPI_ bool xanadu::filesystem::create_directory(const path& _Path) noexcept
{
	return xanadu::filesystem::create_directory(_Path, 0755);
}

// 递归创建目录
_XCOREAPI_ bool xanadu::filesystem::create_directories(const path& _Path) noexcept
{
	return xanadu::filesystem::create_directories(_Path, 0755);
}

// 创建目录
_XCOREAPI_ bool xanadu::filesystem::create_directory(const path& _Path, int _Mode) noexcept
{
	auto		vFilePath = _Path.filepath();
#if defined(XANADU_SYSTEM_WINDOWS)
	auto		vSync = x_posix_wmkdir(vFilePath.toWString().data(), _Mode);
#else
	auto		vSync = x_posix_mkdir(vFilePath.data(), _Mode);
#endif
	return 0 == vSync;
}

// 递归创建目录
_XCOREAPI_ bool xanadu::filesystem::create_directories(const path& _Path, int _Mode) noexcept
{
	auto		vFilePath = _Path.filepath();
#if defined(XANADU_SYSTEM_WINDOWS)
	auto		vSync = x_posix_wmkdir_r(vFilePath.toWString().data(), _Mode);
#else
	auto		vSync = x_posix_mkdir_r(vFilePath.data(), _Mode);
#endif
	return 0 == vSync;
}

// 设置权限
_XCOREAPI_ bool xanadu::filesystem::permissions(const path& _Target, perms _Perms) noexcept
{
	return xanadu::filesystem::permissions(_Target, _Perms, perm_options::replace);
}

// 设置权限
_XCOREAPI_ bool xanadu::filesystem::permissions(const path& _Target, perms _Perms, perm_options _Options) noexcept
{
	XANADU_UNUSED(_Target);
	XANADU_UNUSED(_Perms);
	XANADU_UNUSED(_Options);

	return true;
}

// 移除路径
_XCOREAPI_ bool xanadu::filesystem::remove(const path& _Target) noexcept
{
	auto		vFilePath = _Target.filepath();
#if defined(XANADU_SYSTEM_WINDOWS)
	auto		vSync = x_posix_wremove(vFilePath.toWString().data());
#else
	auto		vSync = x_posix_remove(vFilePath.data());
#endif
	return 0 == vSync;
}

// 重命名路径
_XCOREAPI_ bool xanadu::filesystem::rename(const path& _Old_p, const path& _New_p) noexcept
{
	auto		vOLD = _Old_p.filepath();
	auto		vNEW = _New_p.filepath();
#if defined(XANADU_SYSTEM_WINDOWS)
	auto		vSync = x_posix_wrename(vOLD.toWString().data(), vNEW.toWString().data());
#else
	auto		vSync = x_posix_rename(vOLD.data(), vNEW.data());
#endif
	return 0 == vSync;
}

// 复制文件
_XCOREAPI_ bool xanadu::filesystem::copy_file(const path& _From, const path& _To) noexcept
{
	return xanadu::filesystem::copy_file(_From, _To, copy_options::overwrite_existing);
}

// 复制文件
_XCOREAPI_ bool xanadu::filesystem::copy_file(const path& _From, const path& _To, copy_options _Options) noexcept
{
	auto			vStatusRead = status(_From);
	xanadu::uint64_t 		vSizeRead = vStatusRead.size();
	xanadu::uint64_t 		vSyncSize = 0;
	unsigned char*		vSyncBytes = nullptr;
	xanadu::uint64_t 		vSyncAlready = 0;
	file_stream		vHandleRead = nullptr;
	file_stream		vHandleWrite = nullptr;

	if((_Options & copy_options::_Existing_mask) == copy_options::overwrite_existing)
	{
		if(!exists(_To))
		{
			return true;
		}
		remove(_To);
	}
	else if((_Options & copy_options::_Existing_mask) == copy_options::update_existing)
	{
		if(vSizeRead == file_size(_To))
		{
			return true;
		}
		remove(_To);
	}

	vHandleRead = xanadu::filesystem::fopen(_From, "rb");
	vHandleWrite = xanadu::filesystem::fopen(_To, "wb");
	vSyncBytes = new(std::nothrow) unsigned char[XANADU_SIZE_MB];

	if(vHandleRead && vHandleWrite && vSyncBytes)
	{
		while(vSyncAlready < vSizeRead)
		{
			vSyncSize = xanadu::filesystem::fread(vSyncBytes, 1, XANADU_SIZE_MB, vHandleRead);
			if(vSyncSize == 0)
			{
				break;
			}

			if(!xanadu::filesystem::fwrite(vHandleWrite, vSyncBytes, vSyncSize))
			{
				break;
			}
			vSyncAlready += vSyncSize;
		}
	}

	delete[] vSyncBytes;
	xanadu::filesystem::fclose(vHandleRead);
	xanadu::filesystem::fclose(vHandleWrite);
	return vSyncAlready == vSizeRead;
}

// 复制
_XCOREAPI_ bool xanadu::filesystem::copy(const path& _From, const path& _To) noexcept
{
	return xanadu::filesystem::copy(_From, _To, copy_options::overwrite_existing);
}

// 复制
_XCOREAPI_ bool xanadu::filesystem::copy(const path& _From, const path& _To, copy_options _Options) noexcept
{
	XANADU_UNUSED(_Options);

	auto		vStatus = xanadu::filesystem::status(_From);
	if(xanadu::filesystem::exists(vStatus))
	{
		if(xanadu::filesystem::is_directory(vStatus))
		{
			auto		vSyncStatus = false;
			auto		vFileInfo = xanadu::filesystem::file_info();
			auto		vStream = xanadu::filesystem::dir_open(_From);
			if(vStream)
			{
				vSyncStatus = true;
				xanadu::filesystem::create_directories(_To);
				while(vSyncStatus && xanadu::filesystem::dir_read(vStream, vFileInfo))
				{
					const auto& 	vFormPath = vFileInfo.path();
					auto		vToPath = _To / vFormPath.filename();
					vSyncStatus = xanadu::filesystem::copy(vFormPath, vToPath, _Options);
				}
				xanadu::filesystem::dir_close(vStream);
			}
			return vSyncStatus;
		}
		else
		{
			xanadu::filesystem::create_directories(_To.parent_dir());
			return xanadu::filesystem::copy_file(_From, _To, _Options);
		}
	}
	return false;
}





// 打开文件
_XCOREAPI_ xanadu::filesystem::file_stream xanadu::filesystem::fopen(const path& _Path, const char* _Flags) noexcept
{
	auto		vFilePath = _Path.filepath();
#if defined(XANADU_SYSTEM_WINDOWS)
	auto		vFlags = xanadu::filesystem::string_type (_Flags).toWString();
	auto		vHandle = x_posix_wfopen(vFilePath.toWString().data(), vFlags.data());
#else
	auto		vHandle = x_posix_fopen(vFilePath.data(), _Flags);
#endif
	return (file_stream)vHandle;
}

// 设置文件指针位置
_XCOREAPI_ xanadu::int64_t xanadu::filesystem::fseek(file_stream _Stream, xanadu::int64_t _Offset, int _Origin) noexcept
{
	if(_Stream == nullptr)
	{
		return -1;
	}
	return x_posix_fseek(static_cast<FILE*>(_Stream), (long)_Offset, _Origin);
}

// 当前文件指针位置
_XCOREAPI_ xanadu::int64_t xanadu::filesystem::ftell(file_stream _Stream) noexcept
{
	if(_Stream == nullptr)
	{
		return -1;
	}
	return x_posix_ftell(static_cast<FILE*>(_Stream));
}

// 是否已经到文件尾
_XCOREAPI_ bool xanadu::filesystem::feof(file_stream _Stream) noexcept
{
	if(_Stream == nullptr)
	{
		return true;
	}
	return x_posix_feof(static_cast<FILE*>(_Stream));
}

// 读取所有数据
_XCOREAPI_ bool xanadu::filesystem::fread(file_stream _Stream, void* _Buffer, uint64_t _Length) noexcept
{
	uint64_t 	vAlready = 0;
	uint64_t 	vSync = 0;

	if(_Stream == nullptr)
	{
		return false;
	}

	while(vAlready < _Length)
	{
		vSync = xanadu::filesystem::fread((char*)(_Buffer) + vAlready, 1, _Length - vAlready, _Stream);
		if(vSync <= 0)
		{
			break;
		}
		vAlready += vSync;
	}
	return vAlready == _Length;
}

// 读取一行数据
_XCOREAPI_ xanadu::filesystem::bytes_type xanadu::filesystem::fread_line(file_stream _Stream) noexcept
{
	auto		vBytes = xanadu::filesystem::bytes_type();
	auto		vBuffer = new(std::nothrow) char[XANADU_SIZE_MB];
	if(vBuffer)
	{
		if(x_posix_fgets(vBuffer, XANADU_SIZE_MB - 2, static_cast<FILE*>(_Stream)))
		{
			vBytes = xanadu::filesystem::bytes_type(vBuffer, x_posix_strlen(vBuffer));
		}
		delete[] vBuffer;
	}
	return vBytes;
}

// 读取指定长度的数据
_XCOREAPI_ xanadu::uint64_t xanadu::filesystem::fread(void* _Buffer, uint64_t _Size, uint64_t _Count, file_stream _Stream) noexcept
{
	if(_Stream == nullptr || _Buffer == nullptr)
	{
		return 0;
	}
	return x_posix_fread(_Buffer, static_cast<std::size_t>(_Size), static_cast<std::size_t>(_Count), static_cast<FILE*>(_Stream));
}

// 写入所有数据
_XCOREAPI_ bool xanadu::filesystem::fwrite(file_stream _Stream, const void* _Buffer, uint64_t _Length) noexcept
{
	uint64_t 	vAlready = 0;
	uint64_t 	vSync = 0;

	if(_Stream == nullptr)
	{
		return false;
	}

	while(vAlready < _Length)
	{
		vSync = xanadu::filesystem::fwrite((const char*)(_Buffer) + vAlready, 1, _Length - vAlready, _Stream);
		if(vSync <= 0)
		{
			break;
		}
		vAlready += vSync;
	}
	return vAlready == _Length;
}

// 写入所有数据
_XCOREAPI_ bool xanadu::filesystem::fwrite(file_stream _Stream, const bytes_type& _Buffer) noexcept
{
	return xanadu::filesystem::fwrite(_Stream, _Buffer.data(), _Buffer.size());
}

// 写入指定长度的数据
_XCOREAPI_ xanadu::uint64_t xanadu::filesystem::fwrite(const void* _Buffer, uint64_t _Size, uint64_t _Count, file_stream _Stream) noexcept
{
	if(_Stream == nullptr || _Buffer == nullptr)
	{
		return 0;
	}
	return x_posix_fwrite(_Buffer, static_cast<size_t>(_Size), static_cast<size_t>(_Count), static_cast<FILE*>(_Stream));
}

// 刷新缓冲区
_XCOREAPI_ bool xanadu::filesystem::fflush(file_stream _Stream) noexcept
{
	if(_Stream == nullptr)
	{
		return false;
	}
	return 0 == x_posix_fflush(static_cast<FILE*>(_Stream));
}

// 关闭文件
_XCOREAPI_ bool xanadu::filesystem::fclose(file_stream _Stream) noexcept
{
	if(_Stream == nullptr)
	{
		return false;
	}
	return 0 == x_posix_fclose(static_cast<FILE*>(_Stream));
}





// 打开目录
_XCOREAPI_ xanadu::filesystem::dir_stream xanadu::filesystem::dir_open(const path& _Path) noexcept
{
	XANADU_UNUSED(_Path);

	auto		vStream = new(std::nothrow) xanadu_fs_dir_stream;
	auto		vFilePath = _Path.filepath();
	auto		vHandle = x_posix_opendir(vFilePath.data());
	if(vHandle == nullptr)
	{
		delete vStream;
		return nullptr;
	}
	vStream->handle = vHandle;
	vStream->directory = _Path;
	return vStream;
}

// 读取目录子项
_XCOREAPI_ bool xanadu::filesystem::dir_read(dir_stream _Stream, file_info& _FileInfo) noexcept
{
	auto		vDIR = static_cast<DIR*>(_Stream->handle);
	auto		vDirent = x_posix_readdir(vDIR);
	if(vDirent == nullptr)
	{
		return false;
	}

	_FileInfo = file_info(path(_Stream->directory) /= vDirent->d_name);
	return true;
}

// 关闭目录
_XCOREAPI_ bool xanadu::filesystem::dir_close(dir_stream _Stream) noexcept
{
	auto		vSync = x_posix_closedir(static_cast<DIR*>(_Stream->handle)) == 0;
	delete _Stream;
	return vSync;
}

// 遍历目录
_XCOREAPI_ bool xanadu::filesystem::dir_traverse(const path& _Path, const func_fs_traverse_cb_t& _Function) noexcept
{
	if(_Function == nullptr)
	{
		return false;
	}

	file_info	vFileInfo;
	auto		vStream = xanadu::filesystem::dir_open(_Path);
	if(vStream == nullptr)
	{
		return false;
	}

	while(xanadu::filesystem::dir_read(vStream, vFileInfo))
	{
		if(!_Function(vFileInfo))
		{
			break;
		}
	}

	xanadu::filesystem::dir_close(vStream);
	return true;
}

// 计算目录子项
_XCOREAPI_ xanadu::uint64_t xanadu::filesystem::dir_count(const path& _Path) noexcept
{
	uint64_t	vCount = 0;
	file_info	vFileInfo;
	auto		vStream = xanadu::filesystem::dir_open(_Path);
	if(vStream == nullptr)
	{
		return 0;
	}

	while(xanadu::filesystem::dir_read(vStream, vFileInfo))
	{
		if(vFileInfo.path().filename() == "." || vFileInfo.path().filename() == "..")
		{
			continue;
		}
		++vCount;
	}

	xanadu::filesystem::dir_close(vStream);
	return vCount;
}
