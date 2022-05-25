#include <xanadu-core/filesystem/file.h>



// 打开文件
_XCOREAPI_ x::filesystem::file_stream x::filesystem::fopen(const path& _Path, const char* _Flags) noexcept
{
	auto		vFilePath = _Path.filepath();
#if defined(XANADU_SYSTEM_WINDOWS)
	auto		vFlags = x::filesystem::string_type (_Flags).toWString();
	auto		vHandle = x_posix_wfopen(vFilePath.toWString().data(), vFlags.data());
#else
	auto		vHandle = x_posix_fopen(vFilePath.data(), _Flags);
#endif
	return (file_stream)vHandle;
}

// 设置文件指针位置
_XCOREAPI_ x::int64_t x::filesystem::fseek(file_stream _Stream, x::int64_t _Offset, int _Origin) noexcept
{
	if(_Stream == nullptr)
	{
		return -1;
	}
	return x_posix_fseek(static_cast<FILE*>(_Stream), (long)_Offset, _Origin);
}

// 当前文件指针位置
_XCOREAPI_ x::int64_t x::filesystem::ftell(file_stream _Stream) noexcept
{
	if(_Stream == nullptr)
	{
		return -1;
	}
	return x_posix_ftell(static_cast<FILE*>(_Stream));
}

// 是否已经到文件尾
_XCOREAPI_ bool x::filesystem::feof(file_stream _Stream) noexcept
{
	if(_Stream == nullptr)
	{
		return true;
	}
	return x_posix_feof(static_cast<FILE*>(_Stream));
}

// 读取所有数据
_XCOREAPI_ bool x::filesystem::fread(file_stream _Stream, void* _Buffer, uint64_t _Length) noexcept
{
	uint64_t 	vAlready = 0;
	uint64_t 	vSync = 0;

	if(_Stream == nullptr)
	{
		return false;
	}

	while(vAlready < _Length)
	{
		vSync = x::filesystem::fread((char*)(_Buffer) + vAlready, 1, _Length - vAlready, _Stream);
		if(vSync <= 0)
		{
			break;
		}
		vAlready += vSync;
	}
	return vAlready == _Length;
}

// 读取一行数据
_XCOREAPI_ x::filesystem::bytes_type x::filesystem::fread_line(file_stream _Stream) noexcept
{
	auto		vBytes = x::filesystem::bytes_type();
	auto		vBuffer = new(std::nothrow) char[XANADU_SIZE_MB];
	if(vBuffer)
	{
		if(x_posix_fgets(vBuffer, XANADU_SIZE_MB - 2, static_cast<FILE*>(_Stream)))
		{
			vBytes = x::filesystem::bytes_type(vBuffer, x_posix_strlen(vBuffer));
		}
		delete[] vBuffer;
	}
	return vBytes;
}

// 读取指定长度的数据
_XCOREAPI_ x::uint64_t x::filesystem::fread(void* _Buffer, uint64_t _Size, uint64_t _Count, file_stream _Stream) noexcept
{
	if(_Stream == nullptr || _Buffer == nullptr)
	{
		return 0;
	}
	return x_posix_fread(_Buffer, static_cast<std::size_t>(_Size), static_cast<std::size_t>(_Count), static_cast<FILE*>(_Stream));
}

// 写入所有数据
_XCOREAPI_ bool x::filesystem::fwrite(file_stream _Stream, const void* _Buffer, uint64_t _Length) noexcept
{
	uint64_t 	vAlready = 0;
	uint64_t 	vSync = 0;

	if(_Stream == nullptr)
	{
		return false;
	}

	while(vAlready < _Length)
	{
		vSync = x::filesystem::fwrite((const char*)(_Buffer) + vAlready, 1, _Length - vAlready, _Stream);
		if(vSync <= 0)
		{
			break;
		}
		vAlready += vSync;
	}
	return vAlready == _Length;
}

// 写入所有数据
_XCOREAPI_ bool x::filesystem::fwrite(file_stream _Stream, const bytes_type& _Buffer) noexcept
{
	return x::filesystem::fwrite(_Stream, _Buffer.data(), _Buffer.size());
}

// 写入指定长度的数据
_XCOREAPI_ x::uint64_t x::filesystem::fwrite(const void* _Buffer, uint64_t _Size, uint64_t _Count, file_stream _Stream) noexcept
{
	if(_Stream == nullptr || _Buffer == nullptr)
	{
		return 0;
	}
	return x_posix_fwrite(_Buffer, static_cast<size_t>(_Size), static_cast<size_t>(_Count), static_cast<FILE*>(_Stream));
}

// 刷新缓冲区
_XCOREAPI_ bool x::filesystem::fflush(file_stream _Stream) noexcept
{
	if(_Stream == nullptr)
	{
		return false;
	}
	return 0 == x_posix_fflush(static_cast<FILE*>(_Stream));
}

// 关闭文件
_XCOREAPI_ bool x::filesystem::fclose(file_stream _Stream) noexcept
{
	if(_Stream == nullptr)
	{
		return false;
	}
	return 0 == x_posix_fclose(static_cast<FILE*>(_Stream));
}
