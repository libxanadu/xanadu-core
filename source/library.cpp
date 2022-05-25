#include <xanadu-core/library.h>
#if !defined(XANADU_SYSTEM_WINDOWS)
#include <dlfcn.h>
#endif



// constructor
x::library::library() noexcept
{
	this->_library_handle = nullptr;
}

// constructor
x::library::library(const x::string& _DllPath) noexcept
{
	this->_library_handle = nullptr;
	this->open(_DllPath);
}

// destructor
x::library::~library() noexcept
{
	this->close();
}





// operator overload =
x::library& x::library::operator = (const library& _Library) noexcept = default;

// operator overload =
x::library& x::library::operator = (library&& _Library) noexcept = default;





// 打开动态链接库
bool x::library::open() noexcept
{
	return this->open(this->_library_path);
}

// 打开动态链接库
bool x::library::open(const x::string& _DllPath) noexcept
{
	this->_library_path = _DllPath;

	if(_DllPath.empty())
	{
		return false;
	}

	this->close();
	this->_library_handle = x::library::dlopen(_DllPath);
	return this->_library_handle;
}

// 关闭动态链接库
void x::library::close() noexcept
{
	x::library::dlclose(this->_library_handle);
	this->_library_handle = nullptr;
}





// 是否已经打开
bool x::library::is_open() const noexcept
{
	return this->_library_handle;
}

// 动态链接库的路径
const x::string& x::library::dll_path() const noexcept
{
	return this->_library_path;
}





// 在动态链接库中查找函数
x::library::func_address x::library::find(const x::string& _Function) noexcept
{
	return x::library::dlsym(this->_library_handle, _Function);
}





// [static] 打开动态链接库
x::library::library_handle x::library::dlopen(const x::string& _DllPath) noexcept
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
x::library::func_address x::library::dlsym(library_handle _Handle, const x::string& _Function) noexcept
{
	if(_Handle == nullptr || _Function.empty())
	{
		return nullptr;
	}

	return x_posix_dlsym(_Handle, _Function.data());
}

// [static] 关闭动态链接库
void x::library::dlclose(library_handle _Handle) noexcept
{
	if(_Handle)
	{
		x_posix_dlclose(_Handle);
	}
}
