#include <xanadu-core/filesystem/file_info.h>



// constructor
x::filesystem::file_info::file_info() noexcept = default;

// constructor
x::filesystem::file_info::file_info(const file_info& _Other) noexcept = default;

// constructor
x::filesystem::file_info::file_info(file_info&& _Other) noexcept = default;

// destructor
x::filesystem::file_info::~file_info() noexcept = default;





// constructor
x::filesystem::file_info::file_info(const x::filesystem::path& _Path) noexcept
{
	this->_file_path = _Path;
}





// operator overload =
x::filesystem::file_info& x::filesystem::file_info::operator = (const file_info& _Other) noexcept = default;

// operator overload =
x::filesystem::file_info& x::filesystem::file_info::operator = (file_info&& _Other) noexcept = default;





// operator overload const path&
x::filesystem::file_info::operator const x::filesystem::path& () const noexcept
{
	return this->_file_path;
}





// 路径
const x::filesystem::path& x::filesystem::file_info::path() const noexcept
{
	return this->_file_path;
}
