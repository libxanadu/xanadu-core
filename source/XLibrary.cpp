#include <xanadu-core/XLibrary.h>



// constructor
XLibrary::XLibrary() noexcept
{
	this->_dll_handle = nullptr;
}

// constructor
XLibrary::XLibrary(const XString& _DllPath) noexcept
{
	this->_dll_handle = nullptr;
	this->_dll_path = _DllPath;
}

// destructor
XLibrary::~XLibrary() noexcept
{
	if(this->_dll_handle)
	{
		this->close();
	}
}





// Open dynamic link library
bool XLibrary::open() noexcept
{
	if(this->_dll_path.empty())
	{
		return false;
	}

#if defined(XANADU_SYSTEM_WINDOWS)
	this->_dll_handle = x_posix_dlopen(this->_dll_path.data(), 0x0002);
#else
	this->_dll_handle = x_posix_dlopen(this->_dll_path.data(), RTLD_NOW);
#endif
	return this->_dll_handle;
}

// Open dynamic link library
bool XLibrary::open(const XString& _DllPath) noexcept
{
	this->_dll_path = _DllPath;
	return this->open();
}

// Find functions in dynamic link libraries
XLibrary::func_type XLibrary::find(const char* _FuncName) noexcept
{
	if(this->_dll_handle == nullptr || _FuncName == nullptr)
	{
		return nullptr;
	}
	return (func_type)x_posix_dlsym(this->_dll_handle, _FuncName);
}

// Find functions in dynamic link libraries
XLibrary::func_type XLibrary::find(const XString& _FuncName) noexcept
{
	return this->find(_FuncName.data());
}

// Release dynamic link library
void XLibrary::close() noexcept
{
	if(this->_dll_handle)
	{
		x_posix_dlclose(this->_dll_handle);
	}
}





// Current open dynamic link library path
const XString& XLibrary::path() const noexcept
{
	return this->_dll_path;
}

// Whether the dynamic link library has been opened
bool XLibrary::isOpen() const noexcept
{
	return this->_dll_handle;
}





// Open dynamic link library
HANDLE XLibrary::dllOpen(const XString& _Dynamic) noexcept
{
#if defined(XANADU_SYSTEM_WINDOWS)
	return (HANDLE)x_posix_dlopen(_Dynamic.toUString().data(), 0x0002);
#else
	return (HANDLE)x_posix_dlopen(_Dynamic.toUString().data(), RTLD_NOW);
#endif
}

// Find functions in dynamic link libraries
void* XLibrary::dllFind(HANDLE _Handle, const char* _FuncName) noexcept
{
	if(_Handle == nullptr || _FuncName == nullptr)
	{
		return nullptr;
	}
	return x_posix_dlsym(_Handle, _FuncName);
}

// Find functions in dynamic link libraries
void* XLibrary::dllFind(HANDLE _Handle, const XString& _FuncName) noexcept
{
	if(_Handle == nullptr || _FuncName.empty())
	{
		return nullptr;
	}
	return XLibrary::dllFind(_Handle, _FuncName.data());
}

// Release dynamic link library
int XLibrary::dllClose(HANDLE _Handle) noexcept
{
	if(_Handle == nullptr)
	{
		return -1;
	}
	return x_posix_dlclose(_Handle);
}
