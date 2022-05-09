#include <xanadu-core/filesystem/file_status.h>



// constructor
xanadu::filesystem::file_status::file_status() noexcept
{
	this->_file_size = 0;
	this->_file_type = file_type::unknown;
	this->_file_perms = perms_type::none;
	this->_create_time = 0;
	this->_modify_time = 0;
	this->_access_time = 0;
}

// constructor
xanadu::filesystem::file_status::file_status(const file_type& _FileType, const perms_type& _FilePerms) noexcept
{
	this->_file_size = 0;
	this->_file_type = _FileType;
	this->_file_perms = _FilePerms;
	this->_create_time = 0;
	this->_modify_time = 0;
	this->_access_time = 0;
}

// constructor
xanadu::filesystem::file_status::file_status(size_type _FileSize, const file_type& _FileType, const perms_type& _FilePerms, time_type _CreateTime, time_type _ModifyTime, time_type _AccessTime) noexcept
{
	this->_file_size = _FileSize;
	this->_file_type = _FileType;
	this->_file_perms = _FilePerms;
	this->_create_time = _CreateTime;
	this->_modify_time = _ModifyTime;
	this->_access_time = _AccessTime;
}

// constructor
xanadu::filesystem::file_status::file_status(const file_status& _Other) noexcept = default;

// constructor
xanadu::filesystem::file_status::file_status(file_status&& _Other) noexcept = default;

// destructor
xanadu::filesystem::file_status::~file_status() noexcept = default;





// operator overload =
xanadu::filesystem::file_status& xanadu::filesystem::file_status::operator = (const file_status& _Other) noexcept = default;

// operator overload =
xanadu::filesystem::file_status& xanadu::filesystem::file_status::operator = (file_status&& _Other) noexcept = default;





// 文件大小
void xanadu::filesystem::file_status::size(size_type _FileSize) noexcept
{
	this->_file_size = _FileSize;
}

// 文件属性
void xanadu::filesystem::file_status::type(file_type _FileType) noexcept
{
	this->_file_type = _FileType;
}

// 文件权限
void xanadu::filesystem::file_status::perms(perms_type _FilePerms) noexcept
{
	this->_file_perms = _FilePerms;
}

// 文件创建时间
void xanadu::filesystem::file_status::create_time(time_type _CreateTime) noexcept
{
	this->_create_time = _CreateTime;
}

// 文件修改时间
void xanadu::filesystem::file_status::modify_time(time_type _ModifyTime) noexcept
{
	this->_modify_time = _ModifyTime;
}

// 文件访问时间
void xanadu::filesystem::file_status::access_time(time_type _AccessTime) noexcept
{
	this->_access_time = _AccessTime;
}





// 文件大小
xanadu::filesystem::file_status::size_type xanadu::filesystem::file_status::size() const noexcept
{
	return this->_file_size;
}

// 文件属性
xanadu::filesystem::file_type xanadu::filesystem::file_status::type() const noexcept
{
	return this->_file_type;
}

// 文件权限
xanadu::filesystem::file_status::perms_type xanadu::filesystem::file_status::perms() const noexcept
{
	return this->_file_perms;
}

// 文件创建时间
xanadu::filesystem::file_status::time_type xanadu::filesystem::file_status::create_time() const noexcept
{
	return this->_create_time;
}

// 文件修改时间
xanadu::filesystem::file_status::time_type xanadu::filesystem::file_status::modify_time() const noexcept
{
	return this->_modify_time;
}

// 文件访问时间
xanadu::filesystem::file_status::time_type xanadu::filesystem::file_status::access_time() const noexcept
{
	return this->_access_time;
}
