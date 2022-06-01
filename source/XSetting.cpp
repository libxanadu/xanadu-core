#include <xanadu-core/XSetting.h>


#define 			XANADU_SETTING_LINE_FEED			"\r\n"

enum ENUM_XANADU_SETTING_LINE_TYPE
{
	EXSETTING_LINE_TYPE_SECTION = 0,
	EXSETTING_LINE_TYPE_KEY,
	EXSETTING_LINE_TYPE_NULL,
	EXSETTING_LINE_TYPE_EXPLAIN,
};

class XSettingPrivate
{
public:
	XSettingPrivate*			_Prve;
	XSettingPrivate*			_Next;
	ENUM_XANADU_SETTING_LINE_TYPE		_Type;
	XByteArray				_Text;
	XByteArray				_Line;
};


XSetting::XSetting() noexcept
{
	this->_Info = nullptr;
}

// Overload _copy
XSetting::XSetting(const XSetting& _Setting) noexcept
{
	this->_copy(_Setting);
}

XSetting::~XSetting() noexcept
{
	this->_clear();
}

// Overload Operator =
XSetting& XSetting::operator = (const XSetting& _Setting) noexcept
{
	this->_copy(_Setting);
	return *this;
}






void XSetting::_clear() noexcept
{
	while (this->_Info)
	{
		auto		vNode = this->_Info;
		this->_Info = this->_Info->_Next;
		XANADU_DELETE_PTR(vNode);
	};
}

void XSetting::_copy(const XSetting& _Setting) noexcept
{
	this->_clear();
	for(auto vNode = _Setting._Info; vNode; vNode = vNode->_Next)
	{
		auto		vNodeCopy = new(std::nothrow) XSettingPrivate();
		if(vNodeCopy)
		{
			vNodeCopy->_Type = vNode->_Type;
			vNodeCopy->_Text = vNode->_Text;
			vNodeCopy->_Line = vNode->_Line;
			this->_append(vNodeCopy);
		}
	}
}

XSettingPrivate* XSetting::_format(const XByteArray& _Bytes) const noexcept
{
	auto		vNode = new(std::nothrow) XSettingPrivate();
	if(vNode)
	{
		if (_Bytes.empty())
		{
			vNode->_Type = EXSETTING_LINE_TYPE_NULL;
		}
		else
		{
			switch (_Bytes[0])
			{
				case '[':
					vNode->_Type = EXSETTING_LINE_TYPE_SECTION;
					break;
				case ';':
				case '#':
					vNode->_Type = EXSETTING_LINE_TYPE_EXPLAIN;
					break;
				case '\r':
				case '\n':
					vNode->_Type = EXSETTING_LINE_TYPE_NULL;
					break;
				default:
					vNode->_Type = EXSETTING_LINE_TYPE_KEY;
					break;
			}
		}
		vNode->_Text = _Bytes;
		if(_Bytes.endsWith("\r\n"))
		{
			vNode->_Text = _Bytes.left(_Bytes.size() - 2);
			vNode->_Line = "\r\n";
		}
		else if(_Bytes.endsWith("\n"))
		{
			vNode->_Text = _Bytes.left(_Bytes.size() - 1);
			vNode->_Line = "\n";
		}
		else if(_Bytes.endsWith("\r"))
		{
			vNode->_Text = _Bytes.left(_Bytes.size() - 1);
			vNode->_Line = "\r";
		}
		else
		{
			vNode->_Text = _Bytes;
			vNode->_Line = "\r\n";
		}
		vNode->_Prve = nullptr;
		vNode->_Next = nullptr;
	}
	return vNode;
}

void XSetting::_append(XSettingPrivate* _Node) noexcept
{
	if(this->_Info)
	{
		auto		vNode = this->_Info;
		while(vNode->_Next)
		{
			vNode = vNode->_Next;
		};
		vNode->_Next = _Node;
		_Node->_Prve = vNode;
	}
	else
	{
		this->_Info = _Node;
	}
}

XSettingPrivate* XSetting::_find(const XString& _Section, const XString& _Key) const noexcept
{
	auto		vSection = _Section.toBytes();
	auto		vKey = _Key.toBytes();

	// 遍历整个列表
	for (auto vNode = this->_Info; vNode; vNode = vNode->_Next)
	{
		if(vNode->_Type == EXSETTING_LINE_TYPE_SECTION && this->_section(vNode) == vSection)
		{
			// 如果当前是 SECTION ，并且和 参数 相同，则查找子项
			for (auto vKeyNode = vNode->_Next; vKeyNode; vKeyNode = vKeyNode->_Next)
			{
				if(vKeyNode->_Type == EXSETTING_LINE_TYPE_SECTION)
				{
					// 当子项为SECTION时，表示已经结束，返回空值
					return nullptr;
				}
				if(vKeyNode->_Type == EXSETTING_LINE_TYPE_KEY)
				{
					if(this->_left(vKeyNode) == vKey)
					{
						return vKeyNode;
					}
				}
			}
			break;
		}
	}
	return nullptr;
}

void XSetting::_remove(XSettingPrivate* _Node) noexcept
{
	if(_Node)
	{
		if(this->_Info == _Node)
		{
			this->_Info = this->_Info->_Next;
		}
		else
		{
			for (auto vNode = this->_Info->_Next; vNode; vNode = vNode->_Next)
			{
				if(vNode == _Node)
				{
					// 移除节点
					if(vNode->_Prve)
					{
						vNode->_Prve->_Next = vNode->_Next;
					}
					if(vNode->_Next)
					{
						vNode->_Next->_Prve = vNode->_Prve;
					}
					break;
				}
			}
		}
		XANADU_DELETE_PTR(_Node);
	}
}

XSettingPrivate* XSetting::_section_end(const XString& _Section) noexcept
{
	auto		vSection = _Section.toBytes();
	auto		vEnd = static_cast<XSettingPrivate*>(nullptr);

	// 遍历整个列表
	for (auto vNode = this->_Info; vNode; vNode = vNode->_Next)
	{
		if(vNode->_Type == EXSETTING_LINE_TYPE_SECTION && this->_section(vNode) == vSection)
		{
			// 如果当前是 SECTION ，并且和 参数 相同，则查找子项
			for (auto vKeyNode = vNode->_Next; vKeyNode; vKeyNode = vKeyNode->_Next)
			{
				if(vKeyNode->_Type == EXSETTING_LINE_TYPE_SECTION)
				{
					// 当子项为SECTION时，表示已经结束
					break;
				}
				if(vKeyNode->_Type == EXSETTING_LINE_TYPE_KEY)
				{
					vEnd = vKeyNode;
				}
			}
			break;
		}
	}
	return vEnd;
}

XByteArray XSetting::_section(const XSettingPrivate* _Node) const noexcept
{
	if(_Node)
	{
		if(_Node->_Type == EXSETTING_LINE_TYPE_SECTION && _Node->_Text.size() >= 3)
		{
			return _Node->_Text.mid(1, _Node->_Text.size() - 2);
		}
	}
	return {};
}

XByteArray XSetting::_left(const XSettingPrivate* _Node) const noexcept
{
	if(_Node)
	{
		if(_Node->_Type == EXSETTING_LINE_TYPE_KEY && _Node->_Text.find('=') != XByteArray::npos)
		{
			return _Node->_Text.left(_Node->_Text.find('='));
		}
	}
	return {};
}

XByteArray XSetting::_right(const XSettingPrivate* _Node) const noexcept
{
	if(_Node)
	{
		if(_Node->_Type == EXSETTING_LINE_TYPE_KEY && _Node->_Text.find('=') != XByteArray::npos)
		{
			return _Node->_Text.mid(_Node->_Text.find('=') + 1);
		}
	}
	return {};
}









///加载
bool XSetting::load(const XString& _File) noexcept
{
	this->_clear();

#if defined(XANADU_SYSTEM_WINDOWS)
	auto		vHandle = x_posix_wfopen(_File.toWString().data(), L"rb");
#else
	auto		vHandle = x_posix_fopen(_File.data(), "rb");
#endif
	if(vHandle)
	{
		auto		vBuffer = new(std::nothrow) char[XANADU_SIZE_MB];
		if(vBuffer)
		{
			while(0 == x_posix_feof(vHandle))
			{
				x_posix_memset(vBuffer, 0, XANADU_SIZE_MB);
				x_posix_fgets(vBuffer, XANADU_SIZE_MB - 1, vHandle);

				// 添加一行数据
				auto		vNode = this->_format(XByteArray(vBuffer));
				this->_append(vNode);

			};
			XANADU_DELETE_ARR(vBuffer);
		}
		return true;
	}
	return false;
}

// 保存
bool XSetting::save(const XString& _File) const noexcept
{
#if defined(XANADU_SYSTEM_WINDOWS)
	auto		vHandle = x_posix_wfopen(_File.toWString().data(), L"wb");
#else
	auto		vHandle = x_posix_fopen(_File.data(), "wb");
#endif
	if(vHandle)
	{
		for (auto vNode = this->_Info; vNode; vNode = vNode->_Next)
		{
			auto		vText = vNode->_Text + vNode->_Line;
			x_posix_fwrite(vText.data(), 1, vText.size(), vHandle);
		}
		x_posix_fclose(vHandle);
		return true;
	}
	return false;
}





// 增
bool XSetting::append(const XString& _Section, const XString& _Key, const XVariant& _Value) noexcept
{
	return this->modify(_Section, _Key, _Value);
}

// 删
bool XSetting::remove(const XString& _Section, const XString& _Key) noexcept
{
	auto		vNode = this->_find(_Section, _Key);
	if(vNode)
	{
		this->_remove(vNode);
		return true;
	}
	return false;
}

// 改
bool XSetting::modify(const XString& _Section, const XString& _Key, const XVariant& _Value) noexcept
{
	auto		vNode = this->_find(_Section, _Key);
	if(vNode)
	{
		vNode->_Text = _Key.toBytes() + "=" + _Value.toBytes();
		return true;
	}
	else
	{
		vNode = this->_format(_Key.toBytes() + "=" + _Value.toBytes());
		if(vNode)
		{
			auto		vEnd = this->_section_end(_Section);
			if(vEnd)
			{
				// 当查找到存在的 Section 结尾时，把当前节点添加到结尾后
				if(vEnd->_Next)
				{
					vEnd->_Next->_Prve = vNode;
					vNode->_Next = vEnd->_Next;
					vEnd->_Next = vNode;
				}
				vNode->_Prve = vEnd;
			}
			else
			{
				// 当没有同名Section存在时，创建一个Section与Key
				auto		vNodeSection = this->_format(XByteArray("[") + _Section.toBytes() + XByteArray("]"));
				auto		vNodeKey = this->_format(_Key.toBytes() + "=" + _Value.toBytes());
				if(vNodeSection == vNodeKey)
				{
					this->_append(vNodeSection);
					this->_append(vNodeKey);
				}
			}
			return true;
		}
	}
	return false;
}

// 查
XVariant XSetting::select(const XString& _Section, const XString& _Key, const XVariant& _Default) const noexcept
{
	auto		vNode = this->_find(_Section, _Key);
	if(vNode)
	{
		return XVariant(this->_right(vNode));
	}
	return _Default;
}





// 写入
bool XSetting::write(const XString& _File, const XString& _Section, const XString& _Key, const XVariant& _Value) noexcept
{
	auto		vSync = false;
	auto		vSetting = XSetting();
	if(vSetting.load(_File))
	{
		vSync = vSetting.modify(_Section, _Key, _Value);
		if(vSync)
		{
			vSetting.save(_File);
		}
	}
	return vSync;
}

// 读取
XVariant XSetting::read(const XString& _File, const XString& _Section, const XString& _Key, const XVariant& _Default) noexcept
{
	auto		vSync = _Default;
	auto		vSetting = XSetting();
	if(vSetting.load(_File))
	{
		vSync = vSetting.select(_Section, _Key);
	}
	return vSync;
}
