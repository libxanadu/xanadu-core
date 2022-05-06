#include <xanadu-core/library.h>
#if !defined(XANADU_SYSTEM_WINDOWS)
#include <dlfcn.h>
#endif



// constructor
xanadu::library::library() noexcept
{
	this->_library_handle = nullptr;
}

// constructor
xanadu::library::library(const xanadu::string& _DllPath) noexcept
{
	this->_library_handle = nullptr;
	this->open(_DllPath);
}

// destructor
xanadu::library::~library() noexcept
{
	this->close();
}





// operator overload =
xanadu::library& xanadu::library::operator = (const library& _Library) noexcept = default;

// operator overload =
xanadu::library& xanadu::library::operator = (library&& _Library) noexcept = default;





// 打开动态链接库
bool xanadu::library::open() noexcept
{
	return this->open(this->_library_path);
}

// 打开动态链接库
bool xanadu::library::open(const xanadu::string& _DllPath) noexcept
{
	this->_library_path = _DllPath;

	if(_DllPath.empty())
	{
		return false;
	}

	this->close();
	this->_library_handle = xanadu::library::dlopen(_DllPath);
	return this->_library_handle;
}

// 关闭动态链接库
void xanadu::library::close() noexcept
{
	xanadu::library::dlclose(this->_library_handle);
	this->_library_handle = nullptr;
}





// 是否已经打开
bool xanadu::library::is_open() const noexcept
{
	return this->_library_handle;
}

// 动态链接库的路径
const xanadu::string& xanadu::library::dll_path() const noexcept
{
	return this->_library_path;
}





// 在动态链接库中查找函数
xanadu::library::func_address xanadu::library::find(const xanadu::string& _Function) noexcept
{
	return xanadu::library::dlsym(this->_library_handle, _Function);
}





// [static] 打开动态链接库
xanadu::library::library_handle xanadu::library::dlopen(const xanadu::string& _DllPath) noexcept
{
	if(_DllPath == nullptr)
	{
		return nullptr;
	}

#if defined(XANADU_SYSTEM_WINDOWS)
	auto 		vHandle = x_posix_dlopen(_DllPath.data(), 0x0002);
#else
	auto 		vHandle = x_posix_dlopen(_DllPath.data(), RTLD_NOW);
#endif
	return vHandle;
}

// [static] 在动态链接库中查找函数
xanadu::library::func_address xanadu::library::dlsym(library_handle _Handle, const xanadu::string& _Function) noexcept
{
	if(_Handle == nullptr || _Function.empty())
	{
		return nullptr;
	}

	return x_posix_dlsym(_Handle, _Function.data());
}

// [static] 关闭动态链接库
void xanadu::library::dlclose(library_handle _Handle) noexcept
{
	if(_Handle)
	{
		x_posix_dlclose(_Handle);
	}
}
