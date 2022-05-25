#include <xanadu-core/filesystem.h>



// constructor
x::filesystem::path::path() noexcept = default;

// constructor
x::filesystem::path::path(const path& _Other) noexcept = default;

// constructor
x::filesystem::path::path(path&& _Other) noexcept = default;

// destructor
x::filesystem::path::~path() noexcept = default;





// constructor
x::filesystem::path::path(const elem_type* _String) noexcept
{
	this->_path_absolute = x::filesystem::path::format_to_common(_String);
}

// constructor
x::filesystem::path::path(const string_type& _String) noexcept
{
	this->_path_absolute = x::filesystem::path::format_to_common(_String);
}

// constructor
x::filesystem::path::path(string_type&& _String) noexcept
{
	this->_path_absolute = x::filesystem::path::format_to_common(_String);
}





// operator overload =
x::filesystem::path& x::filesystem::path::operator = (const path& _Other) noexcept = default;

// operator overload =
x::filesystem::path& x::filesystem::path::operator = (path&& _Other) noexcept = default;





// operator overload =
x::filesystem::path& x::filesystem::path::operator = (const elem_type* _String) noexcept
{
	this->_path_absolute = x::filesystem::path::format_to_common(_String);
	return *this;
}

// operator overload =
x::filesystem::path& x::filesystem::path::operator = (const string_type& _String) noexcept
{
	this->_path_absolute = x::filesystem::path::format_to_common(_String);
	return *this;
}

// operator overload =
x::filesystem::path& x::filesystem::path::operator = (string_type&& _String) noexcept
{
	this->_path_absolute = x::filesystem::path::format_to_common(_String);
	return *this;
}





// operator overload +
x::filesystem::path x::filesystem::path::operator + (const elem_type* _String) const noexcept
{
	auto		vNew = *this;
	vNew += _String;
	return vNew;
}

// operator overload +
x::filesystem::path x::filesystem::path::operator + (const string_type& _String) const noexcept
{
	auto		vNew = *this;
	vNew += _String;
	return vNew;
}

// operator overload +
x::filesystem::path x::filesystem::path::operator + (const path& _Path) const noexcept
{
	auto		vNew = *this;
	vNew += _Path;
	return vNew;
}





// operator overload +=
x::filesystem::path& x::filesystem::path::operator += (const elem_type* _String) noexcept
{
	this->_path_absolute += _String;
	return *this;
}

// operator overload +=
x::filesystem::path& x::filesystem::path::operator += (const string_type& _String) noexcept
{
	this->_path_absolute += _String;
	return *this;
}

// operator overload +=
x::filesystem::path& x::filesystem::path::operator += (const path& _Path) noexcept
{
	this->_path_absolute += _Path._path_absolute;
	return *this;
}





// operator overload /
x::filesystem::path x::filesystem::path::operator / (const elem_type* _String) const noexcept
{
	auto		vNew = *this;
	vNew /= _String;
	return vNew;
}

// operator overload /
x::filesystem::path x::filesystem::path::operator / (const string_type& _String) const noexcept
{
	auto		vNew = *this;
	vNew /= _String;
	return vNew;
}

// operator overload /
x::filesystem::path x::filesystem::path::operator / (const path& _Path) const noexcept
{
	auto		vNew = *this;
	vNew /= _Path;
	return vNew;
}





// operator overload /=
x::filesystem::path& x::filesystem::path::operator /= (const elem_type* _String) noexcept
{
	this->_path_absolute += "/";
	this->_path_absolute += _String;
	return *this;
}

// operator overload /=
x::filesystem::path& x::filesystem::path::operator /= (const string_type& _String) noexcept
{
	this->_path_absolute += "/";
	this->_path_absolute += _String;
	return *this;
}

// operator overload /=
x::filesystem::path& x::filesystem::path::operator /= (const path& _Path) noexcept
{
	this->_path_absolute += "/";
	this->_path_absolute += _Path._path_absolute;
	return *this;
}





// operator overload string_type
x::filesystem::path::operator string_type() const noexcept
{
	return this->_path_absolute;
}





// 格式化至通用路径
x::filesystem::path::string_type x::filesystem::path::format_to_common(const string_type& _String) noexcept
{
	auto		vCommon = _String;
	for(auto vIndex = 0U; vIndex < vCommon.size(); ++vIndex)
	{
		if(vCommon[vIndex] == '\\')
		{
			vCommon[vIndex] = x::filesystem::path::path_separator;
		}
	}
	vCommon.replace("//", x::filesystem::path::path_separator);
	while(vCommon.size() > 1 && vCommon[vCommon.size() - 1] == x::filesystem::path::path_separator)
	{
		vCommon.remove(vCommon.size() - 1, 1);
	}
	return vCommon;
}

// 格式化至本机路径
x::filesystem::path::string_type x::filesystem::path::format_to_native(const string_type& _String) noexcept
{
	auto		vCommon = x::filesystem::path::format_to_common(_String);
#if defined(XANADU_SYSTEM_WINDOWS)
	vCommon.replace(x::filesystem::path::path_separator, '\\');
#endif
	return vCommon;
}

// 转换至绝对路径
x::filesystem::path::string_type x::filesystem::path::convert_to_absolute(const string_type& _String) noexcept
{
	return x::filesystem::path::format_to_common(_String);
}

// 检查名称是否符合规范
bool x::filesystem::path::check_is_correct(const path& _Path) noexcept
{
	return _Path.is_exist();
}





// 本机路径
x::filesystem::path::string_type x::filesystem::path::native_path() const noexcept
{
	return x::filesystem::path::format_to_native(this->_path_absolute);
}

// 文件路径
x::filesystem::path::string_type x::filesystem::path::filepath() const noexcept
{
	return this->_path_absolute;
}

// 父目录
x::filesystem::path::string_type x::filesystem::path::parent_dir() const noexcept
{
	auto		vPos = this->_path_absolute.rfind("/");
	if(vPos == string_type::npos)
	{
		return this->_path_absolute;
	}
	else
	{
		auto		vDirectory = this->_path_absolute.left(vPos);
		return vDirectory;
	}
}

// 文件名称
x::filesystem::path::string_type x::filesystem::path::filename() const noexcept
{
	auto		vPos = this->_path_absolute.rfind("/");
	if(vPos == string_type::npos)
	{
		return this->_path_absolute;
	}
	else
	{
		auto		vFileName = this->_path_absolute.right(this->_path_absolute.size() - vPos - 1);
		return vFileName;
	}
}

// 去除后缀名的文件名称
x::filesystem::path::string_type x::filesystem::path::stem() const noexcept
{
	auto		vFileName = this->filename();
	auto		vPos = vFileName.rfind(".");
	if(vPos == string_type::npos)
	{
		return vFileName;
	}
	else
	{
		return vFileName.left(vPos);
	}
}

// 后缀名
x::filesystem::path::string_type x::filesystem::path::extension() const noexcept
{
	return this->suffix();
}

// 后缀名
x::filesystem::path::string_type x::filesystem::path::suffix() const noexcept
{
	auto		vFileName = this->filename();
	auto		vPos = vFileName.rfind(".");
	if(vPos == string_type::npos)
	{
		return {};
	}
	else
	{
		return vFileName.right(vFileName.size() - vPos);
	}
}





// 判断是否存在
bool x::filesystem::path::is_exist() const noexcept
{
	return x::filesystem::exists(*this);
}

// 判断是否为目录
bool x::filesystem::path::is_dir() const noexcept
{
	return x::filesystem::is_directory(*this);
}

// 判断是否为文件
bool x::filesystem::path::is_file() const noexcept
{
	return !x::filesystem::is_directory(*this);
}
