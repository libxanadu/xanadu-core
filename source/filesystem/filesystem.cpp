#include <xanadu-core/filesystem.h>



// 检查路径是否存在
_XCOREAPI_ bool x::filesystem::path_is_exist(const path& _Path) noexcept
{
	auto		vFilePath = _Path.filepath();
#if defined(XANADU_SYSTEM_WINDOWS)
	return 0 == x_posix_waccess(vFilePath.toWString().data(), F_OK);
#else
	return 0 == x_posix_access(vFilePath.data(), F_OK);
#endif
}

// 检查路径是否为文件
_XCOREAPI_ bool x::filesystem::path_is_file(const path& _Path) noexcept
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
_XCOREAPI_ bool x::filesystem::path_is_dir(const path& _Path) noexcept
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
_XCOREAPI_ x::filesystem::file_status x::filesystem::status(const path& _Path) noexcept
{
	auto		vFileStatus = x::filesystem::file_status();
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
_XCOREAPI_ x::uint64_t x::filesystem::file_size(const path& _Path) noexcept
{
	auto		vStatus = x::filesystem::status(_Path);
	return vStatus.size();
}

// 查询链接状态
_XCOREAPI_ x::filesystem::file_status x::filesystem::symlink_status(const path& _Path) noexcept
{
	return x::filesystem::status(_Path);
}

// 检查路径是否存在
_XCOREAPI_ bool x::filesystem::exists(const path& _Target) noexcept
{
	return x::filesystem::exists(x::filesystem::status(_Target));
}

// 检查路径是否存在
_XCOREAPI_ bool x::filesystem::exists(const file_status& _Status) noexcept
{
	if(_Status.type() == file_type::none || _Status.type() == file_type::not_found)
	{
		return false;
	}
	return true;
}

// 文件或目录是否为空
_XCOREAPI_ bool x::filesystem::is_empty(const path& _Path) noexcept
{
	auto		vStatus = x::filesystem::status(_Path);
	if(vStatus.type() == file_type::none || vStatus.type() == file_type::not_found)
	{
		return false;
	}

	if(x::filesystem::is_directory(vStatus))
	{
		return x::filesystem::dir_count(_Path) == 0;
	}
	else
	{
		return vStatus.size() == 0;
	}
}

// 重新设定文件大小
_XCOREAPI_ bool x::filesystem::resize_file(const path& _Target, x::uint64_t _New_size) noexcept
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
_XCOREAPI_ bool x::filesystem::is_block_file(const path& _Path) noexcept
{
	return x::filesystem::is_block_file(status(_Path));
}

// is_block_file
_XCOREAPI_ bool x::filesystem::is_block_file(const file_status& _Status) noexcept
{
	return _Status.type() == file_type::block;
}

// is_character_file
_XCOREAPI_ bool x::filesystem::is_character_file(const path& _Path) noexcept
{
	return x::filesystem::is_character_file(status(_Path));
}

// is_character_file
_XCOREAPI_ bool x::filesystem::is_character_file(const file_status& _Status) noexcept
{
	return _Status.type() == file_type::character;
}

// is_directory
_XCOREAPI_ bool x::filesystem::is_directory(const path& _Path) noexcept
{
	return x::filesystem::is_directory(status(_Path));
}

// is_directory
_XCOREAPI_ bool x::filesystem::is_directory(const file_status& _Status) noexcept
{
	return _Status.type() == file_type::directory;
}

// is_fifo
_XCOREAPI_ bool x::filesystem::is_fifo(const path& _Path) noexcept
{
	return x::filesystem::is_fifo(status(_Path));
}

// is_fifo
_XCOREAPI_ bool x::filesystem::is_fifo(const file_status& _Status) noexcept
{
	return _Status.type() == file_type::fifo;
}

// is_other
_XCOREAPI_ bool x::filesystem::is_other(const path& _Path) noexcept
{
	return x::filesystem::is_other(status(_Path));
}

// is_other
_XCOREAPI_ bool x::filesystem::is_other(const file_status& _Status) noexcept
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
_XCOREAPI_ bool x::filesystem::is_regular_file(const path& _Path) noexcept
{
	return x::filesystem::is_regular_file(status(_Path));
}

// is_regular_file
_XCOREAPI_ bool x::filesystem::is_regular_file(const file_status& _Status) noexcept
{
	return _Status.type() == file_type::regular;
}

// is_socket
_XCOREAPI_ bool x::filesystem::is_socket(const path& _Path) noexcept
{
	return x::filesystem::is_socket(status(_Path));
}

// is_socket
_XCOREAPI_ bool x::filesystem::is_socket(const file_status& _Status) noexcept
{
	return _Status.type() == file_type::socket;
}

// is_symlink
_XCOREAPI_ bool x::filesystem::is_symlink(const path& _Path) noexcept
{
	return x::filesystem::is_symlink(status(_Path));
}

// is_symlink
_XCOREAPI_ bool x::filesystem::is_symlink(const file_status& _Status) noexcept
{
	return _Status.type() == file_type::symlink;
}





// 创建目录
_XCOREAPI_ bool x::filesystem::create_directory(const path& _Path) noexcept
{
	return x::filesystem::create_directory(_Path, 0755);
}

// 递归创建目录
_XCOREAPI_ bool x::filesystem::create_directories(const path& _Path) noexcept
{
	return x::filesystem::create_directories(_Path, 0755);
}

// 创建目录
_XCOREAPI_ bool x::filesystem::create_directory(const path& _Path, int _Mode) noexcept
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
_XCOREAPI_ bool x::filesystem::create_directories(const path& _Path, int _Mode) noexcept
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
_XCOREAPI_ bool x::filesystem::permissions(const path& _Target, perms _Perms) noexcept
{
	return x::filesystem::permissions(_Target, _Perms, perm_options::replace);
}

// 设置权限
_XCOREAPI_ bool x::filesystem::permissions(const path& _Target, perms _Perms, perm_options _Options) noexcept
{
	XANADU_UNUSED(_Target);
	XANADU_UNUSED(_Perms);
	XANADU_UNUSED(_Options);

	return true;
}

// 移除路径
_XCOREAPI_ bool x::filesystem::remove(const path& _Target) noexcept
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
_XCOREAPI_ bool x::filesystem::rename(const path& _Old_p, const path& _New_p) noexcept
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
_XCOREAPI_ bool x::filesystem::copy_file(const path& _From, const path& _To) noexcept
{
	return x::filesystem::copy_file(_From, _To, copy_options::overwrite_existing);
}

// 复制文件
_XCOREAPI_ bool x::filesystem::copy_file(const path& _From, const path& _To, copy_options _Options) noexcept
{
	auto			vStatusRead = status(_From);
	x::uint64_t 		vSizeRead = vStatusRead.size();
	x::uint64_t 		vSyncSize = 0;
	unsigned char*		vSyncBytes = nullptr;
	x::uint64_t 		vSyncAlready = 0;
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

	vHandleRead = x::filesystem::fopen(_From, "rb");
	vHandleWrite = x::filesystem::fopen(_To, "wb");
	vSyncBytes = new(std::nothrow) unsigned char[XANADU_SIZE_MB];

	if(vHandleRead && vHandleWrite && vSyncBytes)
	{
		while(vSyncAlready < vSizeRead)
		{
			vSyncSize = x::filesystem::fread(vSyncBytes, 1, XANADU_SIZE_MB, vHandleRead);
			if(vSyncSize == 0)
			{
				break;
			}

			if(!x::filesystem::fwrite(vHandleWrite, vSyncBytes, vSyncSize))
			{
				break;
			}
			vSyncAlready += vSyncSize;
		}
	}

	delete[] vSyncBytes;
	x::filesystem::fclose(vHandleRead);
	x::filesystem::fclose(vHandleWrite);
	return vSyncAlready == vSizeRead;
}

// 复制
_XCOREAPI_ bool x::filesystem::copy(const path& _From, const path& _To) noexcept
{
	return x::filesystem::copy(_From, _To, copy_options::overwrite_existing);
}

// 复制
_XCOREAPI_ bool x::filesystem::copy(const path& _From, const path& _To, copy_options _Options) noexcept
{
	XANADU_UNUSED(_Options);

	auto		vStatus = x::filesystem::status(_From);
	if(x::filesystem::exists(vStatus))
	{
		if(x::filesystem::is_directory(vStatus))
		{
			auto		vSyncStatus = false;
			auto		vFileInfo = x::filesystem::file_info();
			auto		vStream = x::filesystem::dir_open(_From);
			if(vStream)
			{
				vSyncStatus = true;
				x::filesystem::create_directories(_To);
				while(vSyncStatus && x::filesystem::dir_read(vStream, vFileInfo))
				{
					const auto& 	vFormPath = vFileInfo.path();
					auto		vToPath = _To / vFormPath.filename();
					vSyncStatus = x::filesystem::copy(vFormPath, vToPath, _Options);
				}
				x::filesystem::dir_close(vStream);
			}
			return vSyncStatus;
		}
		else
		{
			x::filesystem::create_directories(_To.parent_dir());
			return x::filesystem::copy_file(_From, _To, _Options);
		}
	}
	return false;
}
