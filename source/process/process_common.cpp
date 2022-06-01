#include <source/process/process_common.h>



// 输出所有换行数据
static void x_process_read_output_printf_newline(XByteArray& _Bytes, const std::function<bool(const XString& _Output)>& _Lambda) noexcept
{
	do{
		auto		vFind = _Bytes.find('\n');
		if(vFind == XByteArray::npos)
		{
			break;
		}
		else
		{
			if(_Lambda)
			{
				_Lambda(XString::fromBytes(_Bytes.left(vFind)));
			}
			_Bytes.remove(static_cast<XByteArray::size_type>(0U), vFind + 1);
		}
	}while(true);
}

// 从句柄读取输出
void x_process_read_output_from_handle(HANDLE _Handle, const std::function<bool(const XString& _Output)>& _Lambda) noexcept
{
#if defined(XANADU_SYSTEM_WINDOWS)
	auto		vBuffer = new(std::nothrow) char[XANADU_SIZE_KB];
	auto		vBytes = XByteArray();
	auto		vSync = static_cast<DWORD>(0);
	for(; vBuffer;)
	{
		x_posix_memset(vBuffer, 0, XANADU_SIZE_KB);
		auto		vSuccess = (::ReadFile(_Handle, vBuffer, XANADU_SIZE_KB, &vSync, nullptr) == TRUE);
		if(vSuccess && vSync > 0)
		{
			vBytes.append(vBuffer, vSync);
		}
		x_process_read_output_printf_newline(vBytes, _Lambda);
		if(!vSuccess)
		{
			if(ERROR_BROKEN_PIPE == ::GetLastError())
			{
				break;
			}
		}
	}
	if(_Lambda)
	{
		_Lambda(XString::fromBytes(vBytes));
	}
	if(vBuffer)
	{
		XANADU_DELETE_ARR(vBuffer);
	}
#else
	XANADU_UNUSED(_Handle);
	XANADU_UNUSED(_Lambda);
#endif
}

// 从句柄读取输出
void x_process_read_output_from_file(FILE* _Handle, const std::function<bool(const XString& _Output)>& _Lambda) noexcept
{
	auto		vBuffer = new(std::nothrow) char[XANADU_SIZE_KB];
	auto		vBytes = XByteArray();
	for(; vBuffer;)
	{
		x_posix_memset(vBuffer, 0, XANADU_SIZE_KB);
		auto		vSync = x_posix_fread(vBuffer, 1, XANADU_SIZE_KB, _Handle);
		if(0 < vSync && vSync <= XANADU_SIZE_KB)
		{
			vBytes.append(vBuffer, vSync);
		}
		x_process_read_output_printf_newline(vBytes, _Lambda);
		if(0 == vSync)
		{
			if(0 != x_posix_ferror(_Handle) || 0 != x_posix_feof(_Handle))
			{
				break;
			}
		}
		if(vSync > XANADU_SIZE_KB)
		{
			break;
		}
	}
	if(_Lambda)
	{
		_Lambda(XString::fromBytes(vBytes));
	}
	if(vBuffer)
	{
		XANADU_DELETE_ARR(vBuffer);
	}
}

// 从句柄读取输出
void x_process_read_output_from_descriptor(int _Handle, const std::function<bool(const XString& _Output)>& _Lambda) noexcept
{
	auto		vBuffer = new(std::nothrow) char[XANADU_SIZE_KB];
	auto		vBytes = XByteArray();
	for(; vBuffer;)
	{
		x_posix_memset(vBuffer, 0, XANADU_SIZE_KB);
		auto		vSync = x_posix_read(_Handle, vBuffer, XANADU_SIZE_KB);
		if(0 < vSync && vSync <= (int)XANADU_SIZE_KB)
		{
			vBytes.append(vBuffer, vSync);
		}
		x_process_read_output_printf_newline(vBytes, _Lambda);
		if(0 == vSync)
		{
			if(0 != x_posix_errno())
			{
				break;
			}
		}
		else if(vSync < 0)
		{
			break;
		}
		if(vSync > (int)XANADU_SIZE_KB)
		{
			break;
		}
	}
	if(_Lambda)
	{
		_Lambda(XString::fromBytes(vBytes));
	}
	if(vBuffer)
	{
		XANADU_DELETE_ARR(vBuffer);
	}
}



// 进程参数转换
char** x_process_param_string_to_argv(const char* _Argv) noexcept
{
	auto		vProgram = std::string(_Argv ? _Argv : "");
	auto		vArgs = std::vector<std::string>();
	auto 		vTemp = std::string();
	auto		vQuoteCount = 0;
	auto		vInQuote = false;
	char**		vArgsC = nullptr;

	// handle quoting. tokens can be surrounded by double quotes
	// "hello world". three consecutive double quotes represent
	// the quote character itself.
	for (char vIndex : vProgram)
	{
		if (vIndex == '\"')
		{
			++vQuoteCount;
			if (vQuoteCount == 3)
			{
				// third consecutive quote
				vQuoteCount = 0;
				vTemp += vIndex;
			}
			continue;
		}
		if (vQuoteCount)
		{
			if (vQuoteCount == 1)
			{
				vInQuote = !vInQuote;
			}
			vQuoteCount = 0;
		}
		if (!vInQuote && vIndex == ' ')
		{
			if (!vTemp.empty())
			{
				vArgs.push_back(vTemp);
				vTemp.clear();
			}
		}
		else
		{
			vTemp += vIndex;
		}
	}
	if (!vTemp.empty())
	{
		vArgs.push_back(vTemp);
	}

	vArgsC = (char**) x_posix_malloc(sizeof(char*) * (vArgs.size() + 1));
	for(auto vIndex = 0U; vIndex < vArgs.size(); ++vIndex)
	{
		vArgsC[vIndex] = x_posix_strdup(vArgs[vIndex].data());
	}
	vArgsC[vArgs.size()] = nullptr;
	return vArgsC;
}

// 进程参数转换
char* x_process_param_argv_to_string(char** _Argv) noexcept
{
	size_t 		vPos = 0;
	char*		vParam = nullptr;
	size_t 		vLength = 10;
	for(int vIndex = 0; _Argv[vIndex]; ++vIndex)
	{
		vLength += x_posix_strlen(_Argv[vIndex]) + 2;
	}
	vParam = (char*)x_posix_malloc(vLength);
	x_posix_memset(vParam, 0, vLength);

	for(int vIndex = 0; _Argv[vIndex]; ++vIndex)
	{
		if(vPos != 0)
		{
			vParam[vPos] = ' ';
			++vPos;
		}
		x_posix_strcpy(vParam + vPos, _Argv[vIndex]);
		vLength += x_posix_strlen(_Argv[vIndex]) + 2;
		vPos += x_posix_strlen(_Argv[vIndex]);
	}

	return vParam;
}

// 进程参数释放
void x_process_param_free(char** _Argv) noexcept
{
	if(_Argv == nullptr)
	{
		return;
	}
	for(auto vIndex = 0; _Argv[vIndex]; ++vIndex)
	{
		x_posix_free(_Argv[vIndex]);
	}
	x_posix_free(_Argv);
}
