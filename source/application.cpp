#include <xanadu-core/application.h>
#include <xanadu-core/filesystem.h>
#include <xanadu-core/system.h>
#if defined(XANADU_SYSTEM_WINDOWS)
#include <Shlobj.h>
#endif
#if defined(XANADU_SYSTEM_DARWIN)
#include <mach-o/dyld.h>
#endif



// constructor
xanadu::application::application() noexcept = default;

// constructor
xanadu::application::application(int _Argc, char* _Argv[]) noexcept
{
	XANADU_UNUSED(_Argc);
	XANADU_UNUSED(_Argv);
}

// constructor
xanadu::application::application(const application& _Other) noexcept = default;

// constructor
xanadu::application::application(application&& _Other) noexcept = default;

// destructor
xanadu::application::~application() noexcept = default;





// operator overload =
xanadu::application& xanadu::application::operator = (const application& _Other) noexcept = default;

// operator overload =
xanadu::application& xanadu::application::operator = (application&& _Other) noexcept = default;





// 当前应用程序路径
const xanadu::application::string_type& xanadu::application::application_path() noexcept
{
	static auto	_static_application_path = string_type();
	if(_static_application_path == nullptr)
	{
#if defined(XANADU_SYSTEM_WINDOWS)
		wchar_t		vDirectory[XANADU_PATH_MAX] = { 0 };
		::GetModuleFileNameW(::GetModuleHandleW(nullptr), vDirectory, XANADU_PATH_MAX);
		_static_application_path = xanadu::filesystem::path::format_to_common(xanadu::string::fromWString(vDirectory));
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
		_static_application_path = xanadu::string::fromUString(vDirectory);
#else
		char		vDirectory[XANADU_PATH_MAX] = { 0 };
		auto		vCount = readlink("/proc/self/exe", vDirectory, XANADU_PATH_MAX);
		if(0 <= vCount || vCount <= XANADU_PATH_MAX)
		{
			_static_application_path = xanadu::string::fromUString(vDirectory);
		}
#endif
#endif
	}
	return _static_application_path;
}

// 当前应用程序目录
const xanadu::application::string_type& xanadu::application::application_directory() noexcept
{
	static auto	_static_application_directory = string_type();
	if(_static_application_directory == nullptr)
	{
		auto		vApplicationPath = xanadu::application::application_path();
		auto		vFind = vApplicationPath.rfind('/');
		if(vFind != string_type::npos)
		{
			_static_application_directory = vApplicationPath.left(vFind);
		}
	}
	return _static_application_directory;
}

// 当前应用程序名称
const xanadu::application::string_type& xanadu::application::application_name() noexcept
{
	static auto	_static_application_name = string_type();
	if(_static_application_name == nullptr)
	{
		auto		vApplicationPath = xanadu::application::application_path();
		auto		vFind = vApplicationPath.rfind('/');
		if(vFind != string_type::npos)
		{
			_static_application_name = vApplicationPath.substr(vFind + 1);
		}
	}
	return _static_application_name;
}

// 当前运行目录
xanadu::application::string_type xanadu::application::current_directory() noexcept
{
	char		vDirectory[XANADU_PATH_MAX] = { 0 };
	x_posix_getcwd(vDirectory, XANADU_PATH_MAX);
	auto		vDirectoryPath = xanadu::filesystem::path::format_to_common(string_type::fromUString(vDirectory));
	return vDirectoryPath;
}

// 修改当前运行目录
xanadu::application::string_type xanadu::application::set_current_directory(const string_type& _Directory) noexcept
{
	auto		vDirectory = xanadu::application::current_directory();
	auto		vNewDirectory = xanadu::filesystem::path::format_to_common(_Directory);
	x_posix_chdir(vNewDirectory.toUString().data());
	return vDirectory;
}





// 应用程序无后缀名称
const xanadu::application::string_type& xanadu::application::application_stem_name() noexcept
{
	static auto	_static_application_application_stem_name = string_type();
	if(_static_application_application_stem_name == nullptr)
	{
		auto		vApplicationName = xanadu::application::application_name();
		if(vApplicationName.endsWith(".exe", xanadu::CaseInsensitive) ||
		   vApplicationName.endsWith(".com", xanadu::CaseInsensitive) ||
		   vApplicationName.endsWith(".run", xanadu::CaseInsensitive))
		{
			vApplicationName.remove(vApplicationName.size() - 1 - 4, 4);
		}
		_static_application_application_stem_name = vApplicationName;
	}
	return _static_application_application_stem_name;
}

// 应用程序本地目录
const xanadu::application::string_type& xanadu::application::application_local_directory() noexcept
{
	static auto	_static_application_local_directory = string_type();
	if(_static_application_local_directory == nullptr)
	{
		_static_application_local_directory = xanadu::system::local_data_directory() + "/" + xanadu::application::application_stem_name().toLower();
		xanadu::filesystem::create_directory(_static_application_local_directory, 0777);
	}
	return _static_application_local_directory;
}

// 应用程序远程目录
const xanadu::application::string_type& xanadu::application::application_remote_directory() noexcept
{
	static auto	_static_application_remote_directory = string_type();
	if(_static_application_remote_directory == nullptr)
	{
		_static_application_remote_directory = xanadu::system::remote_data_directory() + "/" + xanadu::application::application_stem_name().toLower();
		xanadu::filesystem::create_directory(_static_application_remote_directory, 0777);
	}
	return _static_application_remote_directory;
}

// 应用程序缓存目录
const xanadu::application::string_type& xanadu::application::application_temp_directory() noexcept
{
	static auto	_static_application_temp_directory = string_type();
	if(_static_application_temp_directory == nullptr)
	{
		_static_application_temp_directory = xanadu::system::temp_directory() + "/" + xanadu::application::application_stem_name().toLower();
		xanadu::filesystem::create_directory(_static_application_temp_directory, 0777);
	}
	return _static_application_temp_directory;
}





// xanadu名称
const xanadu::application::string_type& xanadu::application::com_xanadu_name() noexcept
{
	static auto	_static_application_com_xanadu_name = string_type();
	if(_static_application_com_xanadu_name == nullptr)
	{
		auto		vApplicationName = xanadu::application::application_stem_name().toLower();
		vApplicationName.insert(0, "com.xanadu.");

		_static_application_com_xanadu_name = vApplicationName;
	}
	return _static_application_com_xanadu_name;
}

// xanadu本地目录
const xanadu::application::string_type& xanadu::application::xanadu_local_directory() noexcept
{
	static auto	_static_application_xanadu_local_directory = string_type();
	if(_static_application_xanadu_local_directory == nullptr)
	{
		_static_application_xanadu_local_directory = xanadu::system::local_data_directory() + "/" + xanadu::application::com_xanadu_name();
		xanadu::filesystem::create_directory(_static_application_xanadu_local_directory, 0777);
	}
	return _static_application_xanadu_local_directory;
}

// xanadu远程目录
const xanadu::application::string_type& xanadu::application::xanadu_remote_directory() noexcept
{
	static auto	_static_application_xanadu_remote_directory = string_type();
	if(_static_application_xanadu_remote_directory == nullptr)
	{
		_static_application_xanadu_remote_directory = xanadu::system::remote_data_directory() + "/" + xanadu::application::com_xanadu_name();
		xanadu::filesystem::create_directory(_static_application_xanadu_remote_directory, 0777);
	}
	return _static_application_xanadu_remote_directory;
}

// xanadu缓存目录
const xanadu::application::string_type& xanadu::application::xanadu_temp_directory() noexcept
{
	static auto	_static_application_xanadu_temp_directory = string_type();
	if(_static_application_xanadu_temp_directory == nullptr)
	{
		_static_application_xanadu_temp_directory = xanadu::system::temp_directory() + "/" + xanadu::application::com_xanadu_name();
		xanadu::filesystem::create_directory(_static_application_xanadu_temp_directory, 0777);
	}
	return _static_application_xanadu_temp_directory;
}
