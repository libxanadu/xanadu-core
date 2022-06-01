#include <xanadu-core/xanadu.h>

bool __xcall__ _Xanadu_Core_Initialize() noexcept
{
	return true;
};

void __xcall__ _Xanadu_Core_Release() noexcept
{
};

#if defined(XANADU_SYSTEM_WINDOWS)
BOOL WINAPI DllMain(HANDLE _HDllHandle, DWORD _Reason, LPVOID _Reserved)
{
	XANADU_UNUSED(_HDllHandle);
	XANADU_UNUSED(_Reserved);

	BOOL	vResult = TRUE;
	switch(_Reason)
	{
		case DLL_PROCESS_ATTACH:
			_Xanadu_Core_Initialize();
			break;
		case DLL_THREAD_ATTACH:
			break;
		case DLL_THREAD_DETACH:
			break;
		case DLL_PROCESS_DETACH:
			_Xanadu_Core_Release();
			break;
		default:
			break;
	}
	return vResult;
}
#else
__attribute((constructor)) void _Xanadu_Core_Dynamic_Library_Init(void)
{
	_Xanadu_Core_Initialize();
};

__attribute((destructor)) void _Xanadu_Core_Dynamic_Library_Fini(void)
{
	_Xanadu_Core_Release();
};
#endif
