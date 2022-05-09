#include <xanadu-core/filesystem/file_info.h>



// constructor
xanadu::filesystem::file_info::file_info() noexcept = default;

// constructor
xanadu::filesystem::file_info::file_info(const file_info& _Other) noexcept = default;

// constructor
xanadu::filesystem::file_info::file_info(file_info&& _Other) noexcept = default;

// destructor
xanadu::filesystem::file_info::~file_info() noexcept = default;





// constructor
xanadu::filesystem::file_info::file_info(const xanadu::filesystem::path& _Path) noexcept
{
	this->_file_path = _Path;
}





// operator overload =
xanadu::filesystem::file_info& xanadu::filesystem::file_info::operator = (const file_info& _Other) noexcept = default;

// operator overload =
xanadu::filesystem::file_info& xanadu::filesystem::file_info::operator = (file_info&& _Other) noexcept = default;





// operator overload const path&
xanadu::filesystem::file_info::operator const xanadu::filesystem::path& () const noexcept
{
	return this->_file_path;
}





// 路径
const xanadu::filesystem::path& xanadu::filesystem::file_info::path() const noexcept
{
	return this->_file_path;
}
