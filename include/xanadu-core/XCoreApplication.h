#ifndef			_XANADU_CORE_CORE_APPLICATION_H_
#define			_XANADU_CORE_CORE_APPLICATION_H_

#include <xanadu-core/header.h>
#include <xanadu-core/XString.h>


///  <summary>
///  Some common operations of application program
///  </summary>
class _XCOREAPI_ XCoreApplication
{
public:
	// constructor
	XCoreApplication() noexcept;

	// destructor
	virtual ~XCoreApplication() noexcept;

public:
	// Gets the path of the current application
	static XString applicationPath() noexcept;

	// Gets the directory of the current application
	static XString applicationDirectory() noexcept;

	// Gets the name of the current application
	static XString applicationName() noexcept;

	// Gets the running directory of the current application
	static XString currentDirectory() noexcept;

	// sets the running directory of the current application
	static XString setCurrentDirectory(const XString& _Directory) noexcept;

public:
	// Gets the cache directory currently in use
	static XString cacheDirectory() noexcept;

	// Get local configuration directory
	static XString configDirectory() noexcept;
};

#endif
