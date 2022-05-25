#include <xanadu-core/filesystem/directory.h>


// 打开目录
_XCOREAPI_ x::filesystem::dir_stream x::filesystem::dir_open(const path& _Path) noexcept
{
	XANADU_UNUSED(_Path);

	auto		vStream = new(std::nothrow) x_fs_dir_stream;
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
_XCOREAPI_ bool x::filesystem::dir_read(dir_stream _Stream, file_info& _FileInfo) noexcept
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
_XCOREAPI_ bool x::filesystem::dir_close(dir_stream _Stream) noexcept
{
	auto		vSync = x_posix_closedir(static_cast<DIR*>(_Stream->handle)) == 0;
	delete _Stream;
	return vSync;
}

// 遍历目录
_XCOREAPI_ bool x::filesystem::dir_traverse(const path& _Path, const func_fs_traverse_cb_t& _Function) noexcept
{
	if(_Function == nullptr)
	{
		return false;
	}

	file_info	vFileInfo;
	auto		vStream = x::filesystem::dir_open(_Path);
	if(vStream == nullptr)
	{
		return false;
	}

	while(x::filesystem::dir_read(vStream, vFileInfo))
	{
		if(!_Function(vFileInfo))
		{
			break;
		}
	}

	x::filesystem::dir_close(vStream);
	return true;
}

// 计算目录子项
_XCOREAPI_ x::uint64_t x::filesystem::dir_count(const path& _Path) noexcept
{
	uint64_t	vCount = 0;
	file_info	vFileInfo;
	auto		vStream = x::filesystem::dir_open(_Path);
	if(vStream == nullptr)
	{
		return 0;
	}

	while(x::filesystem::dir_read(vStream, vFileInfo))
	{
		if(vFileInfo.path().filename() == "." || vFileInfo.path().filename() == "..")
		{
			continue;
		}
		++vCount;
	}

	x::filesystem::dir_close(vStream);
	return vCount;
}

