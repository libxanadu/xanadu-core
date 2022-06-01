#include <xanadu-core/XCoreApplication.h>
#include <xanadu-core/XFileSystem.h>
#include <xanadu-core/XSystem.h>
#if defined(XANADU_SYSTEM_DARWIN)
#include <mach-o/dyld.h>
#endif


// constructor
XCoreApplication::XCoreApplication() noexcept = default;

// destructor
XCoreApplication::~XCoreApplication() noexcept = default;



// Gets the path of the current application
XString XCoreApplication::applicationPath() noexcept
{
	static auto		vApplicationPath = XString();
	if(vApplicationPath.empty())
	{
#if defined(XANADU_SYSTEM_WINDOWS)
		wchar_t		vDirectory[XANADU_PATH_MAX] = { 0 };
		::GetModuleFileNameW(::GetModuleHandleW(nullptr), vDirectory, XANADU_PATH_MAX);
		vApplicationPath = XFileSystem::path::format(XString::fromWString(vDirectory)).filePath();
#else
#if defined(XANADU_SYSTEM_DARWIN)
		char		vDirectory[XANADU_PATH_MAX];
		uint32_t	vLength = XANADU_PATH_MAX;
		if(_NSGetExecutablePath(vDirectory, &vLength) != 0)
		{
			vDirectory[0] = '\0';
		}
		else
		{
			char*		vAbsolutePath = realpath(vDirectory, NULL);
			if(vAbsolutePath)
			{
				strncpy(vDirectory, vAbsolutePath, vLength);
				free(vAbsolutePath);
			}
		}
		vApplicationPath = XString::fromUString(vDirectory);
#else
		char		vDirectory[XANADU_PATH_MAX] = { 0 };
		auto		vCount = readlink("/proc/self/exe", vDirectory, XANADU_PATH_MAX);
		if(0 <= vCount || vCount <= XANADU_PATH_MAX)
		{
			vApplicationPath = XString::fromUString(vDirectory);
		}
#endif
#endif
	}
	return vApplicationPath;
}

// Gets the directory of the current application
XString XCoreApplication::applicationDirectory() noexcept
{
	auto		vApplicationPath = XCoreApplication::applicationPath();
	auto		vFind = vApplicationPath.rfind('/');
	if(vFind != XString::npos)
	{
		return vApplicationPath.left(vFind);
	}
	return "";
}

// Gets the name of the current application
XString XCoreApplication::applicationName() noexcept
{
	auto		vApplicationPath = XCoreApplication::applicationPath();
	auto		vFind = vApplicationPath.rfind('/');
	if(vFind != XString::npos)
	{
		return vApplicationPath.substr(vFind + 1);
	}
	return "";
}

// Gets the running directory of the current application
XString XCoreApplication::currentDirectory() noexcept
{
	char		vDirectory[XANADU_PATH_MAX] = { 0 };
	x_posix_getcwd(vDirectory, XANADU_PATH_MAX);
	auto		vDirectoryPath = XFileSystem::path::format(XString::fromUString(vDirectory));
	return vDirectoryPath.filePath();
}

// sets the running directory of the current application
XString XCoreApplication::setCurrentDirectory(const XString& _Directory) noexcept
{
	auto		vDirectory = XCoreApplication::currentDirectory();
	auto		vNewDirectory = XFileSystem::path::format(_Directory).filePath();
	x_posix_chdir(vNewDirectory.toUString().data());
	return vDirectory;
}



// Gets the cache directory currently in use
XString XCoreApplication::cacheDirectory() noexcept
{
	static auto	vCacheDirectory = XString();
	if(vCacheDirectory.empty())
	{
#if defined(XANADU_SYSTEM_WINDOWS)
		wchar_t		vLongDirectory[XANADU_PATH_MAX] = { 0 };
		wchar_t		vTempDirectory[XANADU_PATH_MAX] = { 0 };
		if(::GetTempPathW(XANADU_PATH_MAX, vTempDirectory))
		{
			::GetLongPathNameW(vTempDirectory, vLongDirectory, XANADU_PATH_MAX);
		}
		auto		vDirectoryPrefix = XFileSystem::path::format(XString::fromWString(vLongDirectory)).filePath();
#else
		auto		vDirectoryPrefix = XString("/tmp");
#endif
		XFileSystem::directory::create(vDirectoryPrefix);
		vCacheDirectory = vDirectoryPrefix;
	}
	return vCacheDirectory;
}

// Get local configuration directory
XString XCoreApplication::configDirectory() noexcept
{
	static auto	vConfigDirectory = XString();
	if(vConfigDirectory.empty())
	{
		auto		vDirectoryPrefix = XString();
#if defined(XANADU_SYSTEM_WINDOWS)
		wchar_t		vLocalDirectory[XANADU_PATH_MAX] = { 0 };
		if(::SHGetSpecialFolderPathW(GetDesktopWindow(), vLocalDirectory, CSIDL_LOCAL_APPDATA, FALSE))
		{
			vDirectoryPrefix = XFileSystem::path::format(XString::fromWString(vLocalDirectory)).filePath();
		}
		else
		{
			vDirectoryPrefix = XSystem::userHome() + "/AppData/Local";
		}
#else
		vDirectoryPrefix = XSystem::userHome() + "/.config";
#endif
		XFileSystem::directory::create(vDirectoryPrefix);
		vConfigDirectory = vDirectoryPrefix;
	}
	return vConfigDirectory;
}
