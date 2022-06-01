#ifndef			_XANADU_CORE_LIBRARY_H_
#define			_XANADU_CORE_LIBRARY_H_

#include <xanadu-core/header.h>
#include <xanadu-core/XString.h>

///  <summary>
///  Implementation of a dynamic loading external library
///  </summary>
class _XCOREAPI_ XLibrary
{
public:
	using				handle_type = void*;
	using				func_type = void*;

private:
	// Handle to dynamic link library
	handle_type			_dll_handle;

	// Full path of dynamic link library
	XString				_dll_path;

public:
	// constructor
	XLibrary() noexcept;

	// constructor
	explicit XLibrary(const XString& _DllPath) noexcept;

	// destructor
	virtual ~XLibrary() noexcept;

public:
	// Open dynamic link library
	virtual bool open() noexcept final;

	// Open dynamic link library
	virtual bool open(const XString& _DllPath) noexcept final;

	// Find functions in dynamic link libraries
	virtual func_type find(const char* _FuncName) noexcept final;

	// Find functions in dynamic link libraries
	virtual func_type find(const XString& _FuncName) noexcept final;

	// Release dynamic link library
	virtual void close() noexcept final;

public:
	// Current open dynamic link library path
	virtual const XString& path() const noexcept final;

	// Whether the dynamic link library has been opened
	virtual bool isOpen() const noexcept final;

public:
	// Open dynamic link library
	static HANDLE dllOpen(const XString& _Dynamic) noexcept;

	// Find functions in dynamic link libraries
	static void* dllFind(HANDLE _Handle, const char* _FuncName) noexcept;

	// Find functions in dynamic link libraries
	static void* dllFind(HANDLE _Handle, const XString& _FuncName) noexcept;

	// Release dynamic link library
	static int dllClose(HANDLE _Handle) noexcept;
};

#endif
