#include <xanadu-core/xanadu.h>


// 动态库初始化
static bool __xcall__ xanadu_core_library_initialize() noexcept
{
	return true;
};

// 动态库释放
static void __xcall__ xanadu_core_library_release() noexcept
{
};


// 动态库入口
#if defined(XANADU_SYSTEM_WINDOWS)
extern "C" BOOL WINAPI DllMain(HANDLE _HDllHandle, DWORD _Reason, LPVOID _Reserved)
{
	XANADU_UNUSED(_HDllHandle);
	XANADU_UNUSED(_Reserved);

	switch(_Reason)
	{
		case DLL_PROCESS_ATTACH:
			xanadu_core_library_initialize();
			break;
		case DLL_PROCESS_DETACH:
			xanadu_core_library_release();
			break;
		default:
			break;
	}
	return TRUE;
}
#else
__attribute((constructor)) void xanadu_core_dynamic_library_init(void)
{
	xanadu_core_library_initialize();
};

__attribute((destructor)) void xanadu_core_dynamic_library_fini(void)
{
	xanadu_core_library_release();
};
#endif
