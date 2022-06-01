#include <xanadu-core/XProcessInfo.h>
#include <xanadu-core/XProcess.h>

// 进程信息私有块
class XProcessInfoPrivate
{
public:
	std::uint64_t				_ProcessID;
	XString				_ProcessName;

public:
	XProcessInfoPrivate()
	{
		this->_ProcessID = 0ULL;
	};

	static void copy(XProcessInfoPrivate* _Target, const XProcessInfoPrivate* _Source)
	{
		_Target->_ProcessID = _Source->_ProcessID;
		_Target->_ProcessName = _Source->_ProcessName;
	};
};

XProcessInfo::XProcessInfo() noexcept
{
	this->_private_info = new(std::nothrow) XProcessInfoPrivate();
}

XProcessInfo::XProcessInfo(std::uint64_t _ProcessID) noexcept
{
	this->_private_info = new(std::nothrow) XProcessInfoPrivate();
	this->_private_info->_ProcessID = _ProcessID;
}

XProcessInfo::XProcessInfo(std::uint64_t _ProcessID, const XString& _ProcessName) noexcept
{
	this->_private_info = new(std::nothrow) XProcessInfoPrivate();
	this->_private_info->_ProcessID = _ProcessID;
	this->_private_info->_ProcessName = _ProcessName;
}

XProcessInfo::XProcessInfo(const XProcessInfo& _Other) noexcept
{
	this->_private_info = new(std::nothrow) XProcessInfoPrivate();
	XProcessInfoPrivate::copy(this->_private_info, _Other._private_info);
}

XProcessInfo::~XProcessInfo() noexcept
{
	XANADU_DELETE_PTR(this->_private_info);
}




XProcessInfo& XProcessInfo::operator = (const XProcessInfo& _Other) noexcept
{
	XProcessInfoPrivate::copy(this->_private_info, _Other._private_info);
	return *this;
}



// 获取进程ID
std::uint64_t XProcessInfo::getProcessID() const noexcept
{
	return this->_private_info->_ProcessID;
}

// 获取进程名称
XString XProcessInfo::getProcessName() const noexcept
{
	return this->_private_info->_ProcessName;
}

// 结束进程
bool XProcessInfo::terminate() const noexcept
{
	return XProcess::kill(this->getProcessID());
}
