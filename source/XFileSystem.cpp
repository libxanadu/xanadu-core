#include <xanadu-core/XFileSystem.h>
#include <xanadu-core/XBase64.h>
#include <xanadu-core/XCoreApplication.h>


// ---------- ---------- ---------- ---------- ---------- ---------- ---------- ---------- ---------- ----------
// XFileSystem::macro
// ---------- ---------- ---------- ---------- ---------- ---------- ---------- ---------- ---------- ----------

#define 			XANADU_FILESYSTEM_REMOVE_SUFFIX				".xrm"


// ---------- ---------- ---------- ---------- ---------- ---------- ---------- ---------- ---------- ----------
// XFileSystem::path
// ---------- ---------- ---------- ---------- ---------- ---------- ---------- ---------- ---------- ----------

// constructor
XFileSystem::path::path() noexcept = default;

// constructor
XFileSystem::path::path(const _Elem* _Path) noexcept
{
	this->_filesystem_path = _Path;
	this->format();
}

// constructor
XFileSystem::path::path(const XString& _Path) noexcept
{
	this->_filesystem_path = _Path;
	this->format();
}

// constructor
XFileSystem::path::path(const XFileSystem::path& _Path) noexcept
{
	this->_filesystem_path = _Path._filesystem_path;
	this->format();
}

// constructor
XFileSystem::path::path(XFileSystem::path&& _Path) noexcept
{
	this->_filesystem_path = _Path._filesystem_path;
	_Path._filesystem_path = nullptr;
	this->format();
}

// destructor
XFileSystem::path::~path() noexcept = default;



// operator overload =
XFileSystem::path& XFileSystem::path::operator = (const _Elem* _Path) noexcept
{
	this->_filesystem_path = _Path;
	this->format();
	return *this;
}

// operator overload =
XFileSystem::path& XFileSystem::path::operator = (const XString& _Path) noexcept
{
	this->_filesystem_path = _Path;
	this->format();
	return *this;
}

// operator overload =
XFileSystem::path& XFileSystem::path::operator = (const XFileSystem::path& _Path) noexcept
{
	this->_filesystem_path = _Path._filesystem_path;
	this->format();
	return *this;
}

// operator overload =
XFileSystem::path& XFileSystem::path::operator = (XFileSystem::path&& _Path) noexcept
{
	this->_filesystem_path = _Path._filesystem_path;
	_Path._filesystem_path = nullptr;
	this->format();
	return *this;
}



// operator overload +=
XFileSystem::path& XFileSystem::path::operator += (const _Elem* _Path) noexcept
{
	this->_filesystem_path += _Path;
	this->format();
	return *this;
}

// operator overload +=
XFileSystem::path& XFileSystem::path::operator += (const XString& _Path) noexcept
{
	this->_filesystem_path += _Path;
	this->format();
	return *this;
}

// operator overload +=
XFileSystem::path& XFileSystem::path::operator += (const XFileSystem::path& _Path) noexcept
{
	this->_filesystem_path += _Path._filesystem_path;
	this->format();
	return *this;
}



// operator overload +
XFileSystem::path XFileSystem::path::operator + (const _Elem* _Path) const noexcept
{
	auto		vTemp = *this;
	vTemp._filesystem_path += _Path;
	vTemp.format();
	return vTemp;
}

// operator overload +
XFileSystem::path XFileSystem::path::operator + (const XString& _Path) const noexcept
{
	auto		vTemp = *this;
	vTemp._filesystem_path += _Path;
	vTemp.format();
	return vTemp;
}

// operator overload +
XFileSystem::path XFileSystem::path::operator + (const XFileSystem::path& _Path) const noexcept
{
	auto		vTemp = *this;
	vTemp._filesystem_path += _Path._filesystem_path;
	vTemp.format();
	return vTemp;
}



// operator overload /=
XFileSystem::path& XFileSystem::path::operator /= (const _Elem* _Path) noexcept
{
	this->_filesystem_path += preferred_separator;
	this->_filesystem_path += _Path;
	this->format();
	return *this;
}

// operator overload /=
XFileSystem::path& XFileSystem::path::operator /= (const XString& _Path) noexcept
{
	this->_filesystem_path += preferred_separator;
	this->_filesystem_path += _Path;
	this->format();
	return *this;
}

// operator overload /=
XFileSystem::path& XFileSystem::path::operator /= (const XFileSystem::path& _Path) noexcept
{
	this->_filesystem_path += preferred_separator;
	this->_filesystem_path += _Path._filesystem_path;
	this->format();
	return *this;
}



// operator overload /
XFileSystem::path XFileSystem::path::operator / (const _Elem* _Path) const noexcept
{
	auto		vTemp = *this;
	vTemp._filesystem_path += preferred_separator;
	vTemp._filesystem_path += _Path;
	vTemp.format();
	return vTemp;
}

// operator overload /
XFileSystem::path XFileSystem::path::operator / (const XString& _Path) const noexcept
{
	auto		vTemp = *this;
	vTemp._filesystem_path += preferred_separator;
	vTemp._filesystem_path += _Path;
	vTemp.format();
	return vTemp;
}

// operator overload /
XFileSystem::path XFileSystem::path::operator / (const XFileSystem::path& _Path) const noexcept
{
	auto		vTemp = *this;
	vTemp._filesystem_path += preferred_separator;
	vTemp._filesystem_path += _Path._filesystem_path;
	vTemp.format();
	return vTemp;
}



// operator overload ==
bool XFileSystem::path::operator == (const _Elem* _Path) const noexcept
{
	return this->_filesystem_path == _Path;
}

// operator overload ==
bool XFileSystem::path::operator == (const XString& _Path) const noexcept
{
	return this->_filesystem_path == _Path;
}

// operator overload ==
bool XFileSystem::path::operator == (const XFileSystem::path& _Path) const noexcept
{
	return this->_filesystem_path == _Path._filesystem_path;
}

// operator overload !=
bool XFileSystem::path::operator != (const _Elem* _Path) const noexcept
{
	return this->_filesystem_path != _Path;
}

// operator overload !=
bool XFileSystem::path::operator != (const XString& _Path) const noexcept
{
	return this->_filesystem_path != _Path;
}

// operator overload !=
bool XFileSystem::path::operator != (const XFileSystem::path& _Path) const noexcept
{
	return this->_filesystem_path != _Path._filesystem_path;
}

// operator overload <
bool XFileSystem::path::operator < (const _Elem* _Path) const noexcept
{
	return this->_filesystem_path < _Path;
}

// operator overload <
bool XFileSystem::path::operator < (const XString& _Path) const noexcept
{
	return this->_filesystem_path < _Path;
}

// operator overload <
bool XFileSystem::path::operator < (const XFileSystem::path& _Path) const noexcept
{
	return this->_filesystem_path < _Path._filesystem_path;
}

// operator overload >
bool XFileSystem::path::operator > (const _Elem* _Path) const noexcept
{
	return this->_filesystem_path > _Path;
}

// operator overload >
bool XFileSystem::path::operator > (const XString& _Path) const noexcept
{
	return this->_filesystem_path > _Path;
}

// operator overload >
bool XFileSystem::path::operator > (const XFileSystem::path& _Path) const noexcept
{
	return this->_filesystem_path > _Path._filesystem_path;
}

// operator overload <=
bool XFileSystem::path::operator <= (const _Elem* _Path) const noexcept
{
	return this->_filesystem_path <= _Path;
}

// operator overload <=
bool XFileSystem::path::operator <= (const XString& _Path) const noexcept
{
	return this->_filesystem_path <= _Path;
}

// operator overload <=
bool XFileSystem::path::operator <= (const XFileSystem::path& _Path) const noexcept
{
	return this->_filesystem_path <= _Path._filesystem_path;
}

// operator overload >=
bool XFileSystem::path::operator >= (const _Elem* _Path) const noexcept
{
	return this->_filesystem_path >= _Path;
}

// operator overload >=
bool XFileSystem::path::operator >= (const XString& _Path) const noexcept
{
	return this->_filesystem_path >= _Path;
}

// operator overload >=
bool XFileSystem::path::operator >= (const XFileSystem::path& _Path) const noexcept
{
	return this->_filesystem_path >= _Path._filesystem_path;
}



// appends elements to the path with a directory separator
XFileSystem::path& XFileSystem::path::append(const _Elem* _Path) noexcept
{
	this->_filesystem_path += preferred_separator;
	this->_filesystem_path += _Path;
	this->format();
	return *this;
}

// appends elements to the path with a directory separator
XFileSystem::path& XFileSystem::path::append(const XString& _Path) noexcept
{
	this->_filesystem_path += preferred_separator;
	this->_filesystem_path += _Path;
	this->format();
	return *this;
}

// appends elements to the path with a directory separator
XFileSystem::path& XFileSystem::path::append(const XFileSystem::path& _Path) noexcept
{
	this->_filesystem_path += preferred_separator;
	this->_filesystem_path += _Path._filesystem_path;
	this->format();
	return *this;
}



// concatenates two paths without introducing a directory separator
XFileSystem::path& XFileSystem::path::concat(const _Elem* _Path) noexcept
{
	this->_filesystem_path += _Path;
	this->format();
	return *this;
}

// concatenates two paths without introducing a directory separator
XFileSystem::path& XFileSystem::path::concat(const XString& _Path) noexcept
{
	this->_filesystem_path += _Path;
	this->format();
	return *this;
}

// concatenates two paths without introducing a directory separator
XFileSystem::path& XFileSystem::path::concat(const XFileSystem::path& _Path) noexcept
{
	this->_filesystem_path += _Path._filesystem_path;
	this->format();
	return *this;
}



// string
XString& XFileSystem::path::data() noexcept
{
	return this->_filesystem_path;
}

// string
const XString& XFileSystem::path::data() const noexcept
{
	return this->_filesystem_path;
}

// checks if the path is exist
bool XFileSystem::path::exist() const noexcept
{
	return this->_filesystem_path.exist();
}

// checks if the path is empty
bool XFileSystem::path::empty() const noexcept
{
	return this->_filesystem_path.empty();
}

// clear
void XFileSystem::path::clear() noexcept
{
	this->_filesystem_path.clear();
}



// format
void XFileSystem::path::format() noexcept
{
	for(auto vIndex = 0U; vIndex < this->_filesystem_path.size(); ++vIndex)
	{
		if(this->_filesystem_path[vIndex] == '\\')
		{
			this->_filesystem_path[vIndex] = '/';
		}
	}
	this->_filesystem_path.replace("//", '/');
	while(this->_filesystem_path.size() > 1 && this->_filesystem_path[this->_filesystem_path.size() - 1] == '/')
	{
		this->_filesystem_path.remove(this->_filesystem_path.size() - 1, 1);
	}
}

// format
XFileSystem::path XFileSystem::path::format(const XFileSystem::path& _Path) noexcept
{
	auto		vFormatPath = _Path;
	vFormatPath.format();
	return vFormatPath;
}



// returns the filepath path component
XString XFileSystem::path::filePath() const noexcept
{
	return this->_filesystem_path;
}

// returns the directory path component
XString XFileSystem::path::directory() const noexcept
{
	auto		vPos = this->_filesystem_path.rfind("/");
	if(vPos == XString::npos)
	{
		return this->_filesystem_path;
	}
	else
	{
		auto		vDirectory = this->_filesystem_path.left(vPos);
		return vDirectory;
	}
}

// returns the filename path component
XString XFileSystem::path::fileName() const noexcept
{
	auto		vPos = this->_filesystem_path.rfind("/");
	if(vPos == XString::npos)
	{
		return this->_filesystem_path;
	}
	else
	{
		auto		vFileName = this->_filesystem_path.right(this->_filesystem_path.size() - vPos - 1);
		return vFileName;
	}
}

// returns the stem path component
XString XFileSystem::path::stem() const noexcept
{
	auto		vFileName = this->fileName();
	auto		vPos = vFileName.rfind(".");
	if(vPos == XString::npos)
	{
		return vFileName;
	}
	else
	{
		return vFileName.left(vPos);
	}
}

// returns the file extension path component
XString XFileSystem::path::extension() const noexcept
{
	return this->suffix();
}

// returns the file extension path component
XString XFileSystem::path::suffix() const noexcept
{
	auto		vFileName = this->fileName();
	auto		vPos = vFileName.rfind(".");
	if(vPos == XString::npos)
	{
		return {};
	}
	else
	{
		return vFileName.right(vFileName.size() - vPos);
	}
}

// Convert to native delimiter
XString XFileSystem::path::native() const noexcept
{
	auto		vNativePath = XString(this->_filesystem_path.size(), '\0');
	for(auto vIndex = 0U; vIndex < this->_filesystem_path.size(); ++vIndex)
	{
		if(this->_filesystem_path[vIndex] == '/')
		{
			vNativePath[vIndex] =  '\\';
		}
		else
		{
			vNativePath[vIndex] = this->_filesystem_path[vIndex];
		}
	}
	return vNativePath;
}

// checks whether the given path refers to a directory
bool XFileSystem::path::isDirectory() const noexcept
{
	return XFileSystem::directory::exist(*this);
}

// checks whether the given path refers to a file
bool XFileSystem::path::isFile() const noexcept
{
	return XFileSystem::file::exist(*this);
}




// checks whether path refers to existing file system object
bool XFileSystem::path::exist(const XFileSystem::path& _Path) noexcept
{
#if defined(XANADU_SYSTEM_WINDOWS)
	return 0 == x_posix_waccess(_Path.filePath().toWString().data(), F_OK);
#else
	return 0 == x_posix_access(_Path.filePath().data(), F_OK);
#endif
}

// checks whether the given path refers to a directory
bool XFileSystem::path::isDirectory(const XFileSystem::path& _Path) noexcept
{
	return XFileSystem::directory::exist(_Path);
}

// checks whether the given path refers to a file
bool XFileSystem::path::isFile(const XFileSystem::path& _Path) noexcept
{
	return XFileSystem::file::exist(_Path);
}

// returns the size of a path
unsigned long long XFileSystem::path::size(const XFileSystem::path& _Path) noexcept
{
	if(XFileSystem::path::isDirectory(_Path))
	{
		return XFileSystem::directory::size(_Path);
	}
	else
	{
		return XFileSystem::file::size(_Path);
	}
}

// 后缀匹配
bool XFileSystem::path::suffixMatch(const XFileSystem::path& _Path, const XString& _Suffix) noexcept
{
	auto		vFileSuffix = _Path.suffix();
	return vFileSuffix.compare(_Suffix, Xs::CaseInsensitive) == 0;
}

// 修复	\/:*?"<>|
XFileSystem::path XFileSystem::path::repair(const XFileSystem::path& _Path) noexcept
{
	auto		vFilePath = _Path.filePath();
	auto		vPos = vFilePath.rfind('/');
	for(auto vIndex = vPos; vIndex < vFilePath.size(); ++vIndex)
	{
		switch(vFilePath[vIndex])
		{
			//\/:*?"<>|
			case L':':
			case L'*':
			case L'?':
			case L'\"':
			case L'<':
			case L'>':
			case L'|':
				vFilePath[vIndex] = L'_';
				break;
			default:
				break;
		}
	}
	return vFilePath;
}

// 修复空格
XFileSystem::path XFileSystem::path::spaceRepair(const XFileSystem::path& _Path) noexcept
{
	auto		vFilePath = _Path.filePath();
	if(vFilePath.contains(" "))
	{
		return XString("\"") + vFilePath + XString("\"");
	}
	return _Path;
}

// Check whether the name meets the specification
bool XFileSystem::path::isCorrect(const XString& _FileName) noexcept
{
	auto		vFilePath = XCoreApplication::cacheDirectory() + "/" + _FileName;
	auto		vHandle = XFileSystem::file::open(vFilePath, "wb");
	if(vHandle)
	{
		XFileSystem::file::close(vHandle);
		XFileSystem::file::remove(vFilePath);
		return true;
	}
	return false;
}



// remove
bool XFileSystem::path::remove(const XFileSystem::path& _Path, const std::function<bool(const XFileSystem::path& _Path)>& _Lambda) noexcept
{
	if(XFileSystem::path::isDirectory(_Path))
	{
		return XFileSystem::directory::remove(_Path, _Lambda);
	}
	else
	{
		return XFileSystem::file::remove(_Path);
	}
}



// ---------- ---------- ---------- ---------- ---------- ---------- ---------- ---------- ---------- ----------
// XFileSystem::file
// ---------- ---------- ---------- ---------- ---------- ---------- ---------- ---------- ---------- ----------

// constructor
XFileSystem::file::file() noexcept = default;

// destructor
XFileSystem::file::~file() noexcept = default;



// [opt] open
HANDLE XFileSystem::file::open(const XFileSystem::path& _Path, const char* _Flags) noexcept
{
	auto		vFilePath = XFileSystem::path::format(_Path).filePath();
#if defined(XANADU_SYSTEM_WINDOWS)
	auto		vFlags = XString(_Flags).toWString();
	auto		vHandle = x_posix_wfopen(vFilePath.toWString().data(), vFlags.data());
#else
	auto		vHandle = x_posix_fopen(vFilePath.data(), _Flags);
#endif
	return (HANDLE)vHandle;
}

// [opt] seek
bool XFileSystem::file::seek(HANDLE _Handle, long _Offset, int _Origin) noexcept
{
	if(_Handle)
	{
		return 0 == x_posix_fseek(static_cast<FILE*>(_Handle), _Offset, _Origin);
	}
	else
	{
		return false;
	}
}

// [opt] offset
long long XFileSystem::file::offset(HANDLE _Handle) noexcept
{
	if(_Handle)
	{
		return x_posix_ftell(static_cast<FILE*>(_Handle));
	}
	return -1;
}

// [opt] eof
bool XFileSystem::file::eof(HANDLE _Handle) noexcept
{
	if(_Handle)
	{
		return x_posix_feof(static_cast<FILE*>(_Handle));
	}
	else
	{
		return false;
	}
}

// [opt] read all
bool XFileSystem::file::read(HANDLE _Handle, void* _Buffer, uint64_t _Length) noexcept
{
	uint64_t 	vAlready = 0;
	size_t 		vSync = 0;

	if(_Handle)
	{
		while(vAlready < _Length)
		{
			vSync = x_posix_fread((char*)(_Buffer) + vAlready, 1, static_cast<size_t>(_Length - vAlready), static_cast<FILE*>(_Handle));
			if(vSync <= 0)
			{
				break;
			}
			vAlready += vSync;
		}
		return vAlready == _Length;
	}
	else
	{
		return false;
	}
}

// [opt] read line
XByteArray XFileSystem::file::readLine(HANDLE _Handle) noexcept
{
	auto		vBytes = XByteArray();
	auto		vBuffer = new(std::nothrow) char[XANADU_SIZE_MB];
	if(vBuffer)
	{
		if(x_posix_fgets(vBuffer, XANADU_SIZE_MB - 2, static_cast<FILE*>(_Handle)))
		{
			vBytes = XByteArray(vBuffer, x_posix_strlen(vBuffer));
		}
		XANADU_DELETE_ARR(vBuffer);
	}
	return vBytes;
}

// [opt] read
uint64_t XFileSystem::file::read(void* _Buffer, uint64_t _Size, uint64_t _Count, HANDLE _Handle) noexcept
{
	if(_Handle)
	{
		return x_posix_fread(_Buffer, static_cast<size_t>(_Size), static_cast<size_t>(_Count), static_cast<FILE*>(_Handle));
	}
	return false;
}

// [opt] write all
bool XFileSystem::file::write(HANDLE _Handle, const void* _Buffer, uint64_t _Length) noexcept
{
	uint64_t 	vAlready = 0;
	size_t 		vSync = 0;

	if(_Handle)
	{
		while(vAlready < _Length)
		{
			vSync = x_posix_fwrite((const char*)(_Buffer) + vAlready, 1, static_cast<size_t>(_Length - vAlready), static_cast<FILE*>(_Handle));
			if(vSync <= 0)
			{
				break;
			}
			vAlready += vSync;
		}
		return vAlready == _Length;
	}
	else
	{
		return false;
	}
}

// [opt] write all
bool XFileSystem::file::write(HANDLE _Handle, const XByteArray& _Buffer) noexcept
{
	if(_Handle && _Buffer.exist())
	{
		return XFileSystem::file::write(_Handle, _Buffer.data(), _Buffer.size());
	}
	return false;
}

// [opt] write
uint64_t XFileSystem::file::write(const void* _Buffer, uint64_t _Size, uint64_t _Count, HANDLE _Handle) noexcept
{
	if(_Handle)
	{
		return x_posix_fwrite(_Buffer, static_cast<size_t>(_Size), static_cast<size_t>(_Count), static_cast<FILE*>(_Handle));
	}
	return 0ULL;
}

// [opt] flush
bool XFileSystem::file::flush(HANDLE _Handle) noexcept
{
	if(_Handle)
	{
		return 0 == x_posix_fflush(static_cast<FILE*>(_Handle));
	}
	return false;
}

// [opt] close
bool XFileSystem::file::close(HANDLE _Handle) noexcept
{
	if(_Handle)
	{
		return 0 == x_posix_fclose(static_cast<FILE*>(_Handle));
	}
	return false;
}



// checks if the path is exist
uint64_t XFileSystem::file::size(const XFileSystem::path& _Path) noexcept
{
	auto		vFilePath = XFileSystem::path::format(_Path).filePath();
	return x_posix_fsize(vFilePath.data());
}

// checks if the path is exist
bool XFileSystem::file::exist(const XFileSystem::path& _Path) noexcept
{
	auto		vFilePath = _Path.filePath();
#if defined(XANADU_SYSTEM_WINDOWS)
	if(0 == x_posix_waccess(vFilePath.toWString().data(), F_OK))
	{
		return !XFileSystem::directory::exist(_Path);
	}
#else
	if(0 == x_posix_access(vFilePath.data(), F_OK))
	{
		return !XFileSystem::directory::exist(_Path);
	}
#endif
	return false;
}

// rename
bool XFileSystem::file::rename(const XFileSystem::path& _PathOLD, const XFileSystem::path& _PathNEW) noexcept
{
	XFileSystem::file::remove(_PathNEW);

	auto		vFileOLD = XFileSystem::path::format(_PathOLD).filePath();
	auto		vFileNEW = XFileSystem::path::format(_PathNEW).filePath();
#if defined(XANADU_SYSTEM_WINDOWS)
	auto		vSync = x_posix_wrename(vFileOLD.toWString().data(), vFileNEW.toWString().data());
#else
	auto		vSync = x_posix_rename(vFileOLD.data(), vFileNEW.data());
#endif
	if(0 == vSync)
	{
		return true;
	}
	else
	{
#if defined(XANADU_SYSTEM_WINDOWS)
		if(::MoveFileW(vFileOLD.toWString().data(), vFileNEW.toWString().data()))
		{
			return true;
		}
#endif
		return false;
	}
}

// remove
bool XFileSystem::file::remove(const XFileSystem::path& _Path) noexcept
{
	if (XFileSystem::file::exist(_Path))
	{
		auto		vFilePath = _Path.filePath();
#if defined(XANADU_SYSTEM_WINDOWS)
		auto		vRemove = x_posix_wremove(vFilePath.toWString().data());
#else
		auto		vRemove = x_posix_remove(vFilePath.data());
#endif
		if(0 == vRemove)
		{
			return true;
		}
		else
		{
#if defined(XANADU_SYSTEM_WINDOWS)
			if(::DeleteFileW(vFilePath.toWString().data()))
			{
				return true;
			}
#endif
			auto		vFileXrm = vFilePath + XANADU_FILESYSTEM_REMOVE_SUFFIX;
#if defined(XANADU_SYSTEM_WINDOWS)
			auto		vSync = x_posix_wrename(vFilePath.toWString().data(), vFileXrm.toWString().data());
#else
			auto		vSync = x_posix_rename(vFilePath.data(), vFileXrm.data());
#endif
			return vSync;
		}
	}
	return true;
}

// copy
bool XFileSystem::file::copy(const XFileSystem::path& _Source, const XFileSystem::path& _Target, _FunctionProgress _Lambda) noexcept
{
	auto		vSync = false;
	auto		vBytes = XByteArray(XANADU_SIZE_MB, '\0');
	auto		vFileSize = XFileSystem::file::size(_Source);
	auto		vSyncSize = 0ULL;
	auto		vHandleSource = XFileSystem::file::open(_Source, "rb");
	auto		vHandleTarget = XFileSystem::file::open(_Target, "wb");
	if(vFileSize == 0)
	{
		vSync = true;
	}
	else if(vHandleSource && vHandleTarget && vBytes.size() == XANADU_SIZE_MB)
	{
		while(vFileSize > vSyncSize)
		{
			auto		vReadSize = ((vFileSize - vSyncSize) > XANADU_SIZE_MB) ? XANADU_SIZE_MB : (vFileSize - vSyncSize);
			if(!XFileSystem::file::read(vHandleSource, vBytes.data(), vReadSize))
			{
				break;
			}
			vSyncSize += vReadSize;
			if(!XFileSystem::file::write(vHandleTarget, vBytes.data(), vReadSize))
			{
				break;
			}
			if(_Lambda && !_Lambda(vSyncSize, vFileSize))
			{
				break;
			}
			if(vFileSize == vSyncSize)
			{
				vSync = true;
				break;
			}
		};
	}
#if !defined(XANADU_SYSTEM_WINDOWS)
	// When successful, we need copy permissions
	if(vSync)
	{

	}
#endif
	XFileSystem::file::close(vHandleSource);
	XFileSystem::file::close(vHandleTarget);
#if defined(XANADU_SYSTEM_WINDOWS)
	if(!vSync)
	{
		vSync = CopyFileW(_Source.filePath().toWString().data(), _Target.filePath().toWString().data(), FALSE);
	}
#endif
	return vSync;
}

// move
bool XFileSystem::file::move(const XFileSystem::path& _Source, const XFileSystem::path& _Target, _FunctionProgress _Lambda) noexcept
{
	if(XFileSystem::file::rename(_Source, _Target))
	{
		return true;
	}
	else
	{
		if(XFileSystem::file::copy(_Source, _Target, _Lambda))
		{
			XFileSystem::file::remove(_Source);
			return true;
		}
	}
	return false;
}



// [opt] to bytes
XByteArray XFileSystem::file::toBytes(const XFileSystem::path& _Path) noexcept
{
	auto		vSize = XFileSystem::file::size(_Path);
	auto		vBytes = XByteArray(static_cast<std::size_t>(vSize), '\0');
	auto		vHandle = XFileSystem::file::open(_Path, "rb");
	if(vHandle && vSize > 0 && vBytes.size() == vSize)
	{
		XFileSystem::file::read(vHandle, vBytes.data(), vSize);
	}
	XFileSystem::file::close(vHandle);
	return vBytes;
}

// [opt] from bytes
bool XFileSystem::file::fromBytes(const XFileSystem::path& _Path, const void* _Bytes, std::size_t _Length) noexcept
{
	auto		vSync = false;
	auto		vHandle = XFileSystem::file::open(_Path, "wb");
	if(vHandle)
	{
		if(_Bytes && _Length > 0)
		{
			vSync = XFileSystem::file::write(vHandle, _Bytes, _Length);
		}
		else
		{
			vSync = true;
		}
		XFileSystem::file::close(vHandle);
	}
	return vSync;
}

// [opt] from bytes
bool XFileSystem::file::fromBytes(const XFileSystem::path& _Path, const XByteArray& _Bytes) noexcept
{
	return XFileSystem::file::fromBytes(_Path, _Bytes.data(), _Bytes.size());
}

// [opt] to bytes
XByteArray XFileSystem::file::toBase64(const XFileSystem::path& _Path) noexcept
{
	return XFileSystem::file::toBytes(_Path).toBase64();
}

// [opt] from base64
bool XFileSystem::file::fromBase64(const XFileSystem::path& _Path, const void* _Base64, std::size_t _Length) noexcept
{
	return XFileSystem::file::fromBytes(_Path, XBase64::decode(_Base64, _Length));
}

// [opt] from base64
bool XFileSystem::file::fromBase64(const XFileSystem::path& _Path, const XByteArray& _Base64) noexcept
{
	return XFileSystem::file::fromBase64(_Path, _Base64.data(), _Base64.size());
}




// ---------- ---------- ---------- ---------- ---------- ---------- ---------- ---------- ---------- ----------
// XFileSystem::directory
// ---------- ---------- ---------- ---------- ---------- ---------- ---------- ---------- ---------- ----------

// constructor
XFileSystem::directory::directory() noexcept = default;

// destructor
XFileSystem::directory::~directory() noexcept = default;



// returns the size of a directory
uint64_t XFileSystem::directory::size(const XFileSystem::path& _Directory) noexcept
{
	auto		vDirectorySize = 0ULL;
	XFileSystem::directory::traverse(_Directory, [&](const XFileSystem::path& _Path)->bool
	{
		vDirectorySize += XFileSystem::path::size(_Path);
		return true;
	});
	return vDirectorySize;
}

// checks if the directory is exist
bool XFileSystem::directory::exist(const XFileSystem::path& _Directory) noexcept
{
	auto		vFilePath = _Directory.filePath();
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

// 目录:创建
bool XFileSystem::directory::create(const XFileSystem::path& _Directory, int _Mode) noexcept
{
	auto		vFilePath = XFileSystem::path::format(_Directory).filePath();
#if defined(XANADU_SYSTEM_WINDOWS)
	auto		vSync = x_posix_wmkdir_r(vFilePath.toWString().data(), _Mode);
#else
	auto		vSync = x_posix_mkdir_r(vFilePath.data(), _Mode);
#endif
	return 0 == vSync;
}

// traverse
bool XFileSystem::directory::traverse(const XFileSystem::path& _Directory, _Function1 _Lambda) noexcept
{
#if defined(XANADU_SYSTEM_WINDOWS)
	auto			vDirectoryPath = _Directory.filePath();
	auto			vDirectory = vDirectoryPath.toWString() + L"/*.*";
	struct _wfinddata64_t	vFileInfo{};
	auto			vHandle = _wfindfirst64(vDirectory.data(), &vFileInfo);
	if(vHandle == -1L)
	{
		return false;
	}
	else
	{
		do
		{
			if(x_posix_wcscmp(vFileInfo.name, L".") == 0 || x_posix_wcscmp(vFileInfo.name, L"..") == 0)
			{
			}
			else
			{
				auto		vFullPath = vDirectoryPath + L'/' + XString::fromWString(vFileInfo.name);
				if(_Lambda && !_Lambda(vFullPath))
				{
					break;
				}
			}
		}while(_wfindnext64(vHandle, &vFileInfo) == 0);
		_findclose(vHandle);
		return true;
	}
#else
	auto		vDirectory = _Directory.filePath();
	auto 		vHandle = ::opendir(vDirectory.data());
	auto		vDirEntry = static_cast<struct dirent*>(nullptr);
	if (vHandle)
	{
		vDirEntry = ::readdir(vHandle);
		while(vDirEntry)
		{
			if(x_posix_strcmp(vDirEntry->d_name, ".") == 0 || x_posix_strcmp(vDirEntry->d_name, ".") == 0)
			{
			}
			else
			{
				auto		vFullPath = vDirectory + '/' + vDirEntry->d_name;
				if(_Lambda && !_Lambda(vFullPath))
				{
					break;
				}
			}
			vDirEntry = ::readdir(vHandle);
		}
		::closedir(vHandle);
		return true;
	}
	return false;
#endif
}

// remove
bool XFileSystem::directory::remove(const XFileSystem::path& _Directory, _Function1 _Lambda) noexcept
{
	auto		vSync = true;
	auto		vTraverse = XFileSystem::directory::traverse(_Directory, [&](const XFileSystem::path& _Path)->bool
	{
		vSync = XFileSystem::path::remove(_Path, _Lambda);
		return vSync;
	});
	if (XFileSystem::directory::exist(_Directory))
	{
		auto		vDirectoryPath = _Directory.filePath();
#if defined(XANADU_SYSTEM_WINDOWS)
		auto		vRemove = x_posix_wrmdir(vDirectoryPath.toWString().data());
#else
		auto		vRemove = x_posix_rmdir(vDirectoryPath.data());
#endif
		vSync = (0 == vRemove);
	}
	return vSync && vTraverse;
}

// copy
bool XFileSystem::directory::copy(const XFileSystem::path& _Source, const XFileSystem::path& _Target, _Function2 _Lambda) noexcept
{
	auto		vSync = true;
	XFileSystem::directory::create(_Target);
	auto		vTraverse = XFileSystem::directory::traverse(_Source, [&](const XFileSystem::path& _Path)->bool
	{
		auto		vTargetFull = _Target / _Path.fileName();
		if(XFileSystem::path::isDirectory(_Path))
		{
			XFileSystem::directory::create(vTargetFull);
			vSync = XFileSystem::directory::copy(_Path, vTargetFull, _Lambda);
		}
		else
		{
			vSync = XFileSystem::file::copy(_Path, vTargetFull, nullptr);
		}
		return vSync;
	});
	return vSync && vTraverse;
}

// move
bool XFileSystem::directory::move(const XFileSystem::path& _Source, const XFileSystem::path& _Target, _Function2 _Lambda) noexcept
{
	auto		vSync = true;
	XFileSystem::directory::create(_Target);
	auto		vTraverse = XFileSystem::directory::traverse(_Source, [&](const XFileSystem::path& _Path)->bool
	{
		auto		vTargetFull = _Target / _Path.fileName();
		if(XFileSystem::path::isDirectory(_Path))
		{
			XFileSystem::directory::create(vTargetFull);
			vSync = XFileSystem::directory::move(_Path, vTargetFull, _Lambda);
		}
		else
		{
			vSync = XFileSystem::file::move(_Path, vTargetFull, nullptr);
		}
		return vSync;
	});
	if(vSync && vTraverse)
	{
		auto		vSourceDirectory = _Source.filePath();
#if defined(XANADU_SYSTEM_WINDOWS)
		auto		vRemove = x_posix_wrmdir(vSourceDirectory.toWString().data());
#else
		auto		vRemove = x_posix_rmdir(vSourceDirectory.data());
#endif
		vSync = (0 == vRemove);
	}
	return vSync && vTraverse;
}
