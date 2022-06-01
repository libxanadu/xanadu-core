#ifndef			_XANADU_CORE_NATIVE_H_
#define			_XANADU_CORE_NATIVE_H_

#include <xanadu-core/header.h>

// Native platform type definition
#if !defined(XANADU_SYSTEM_WINDOWS)
typedef	HANDLE				HWND;
typedef long				WPARAM;
typedef long				LPARAM;
typedef	HANDLE				HKEY;

// 坐标定义
typedef struct tagPOINT
{
	long	x;
	long	y;
}POINT, *PPOINT, *NPPOINT, *LPPOINT;

// 消息结构
typedef struct tagMSG
{
	HWND				hwnd;
	unsigned int			message;
	WPARAM				wParam;
	LPARAM				lParam;
	unsigned long			time;
	POINT				pt;
#ifdef _MAC
	unsigned long			lPrivate;
#endif
}MSG, *LPMSG;
#endif

// Native platform macro definition
#if !defined(XANADU_SYSTEM_WINDOWS)
#define			WM_USER							0x0400
#define			PM_NOREMOVE						0x0000
#define			PM_REMOVE						0x0001
#define			PM_NOYIELD						0x0002
#define			INVALID_HANDLE_VALUE					((HANDLE)(unsigned long)-1)
#endif

// Native platform-dependent function implementation
#if !defined(XANADU_SYSTEM_WINDOWS)
// 从调用线程的消息队列里取得一个消息并将其放于指定的结构。
// 此函数可取得与指定窗口联系的消息和由PostThreadMessage寄送的线程消息。
// 此函数接收一定范围的消息值。GetMessage不接收属于其他线程或应用程序的消息。
// 获取消息成功后，线程将从消息队列中删除该消息。
// 函数会一直等待直到有消息到来才有返回值。
_XCOREAPI_ bool __xcall__ GetMessageW(LPMSG lpMsg, HWND hWnd, unsigned int wMsgFilterMin, unsigned int wMsgFilterMax);

// 检查线程消息队列，并将该消息（如果存在）放于指定的结构
_XCOREAPI_ bool __xcall__ PeekMessageW(LPMSG lpMsg, HWND hWnd, unsigned int wMsgFilterMin, unsigned int wMsgFilterMax, unsigned int wRemoveMsg);

// 将一个队列消息放入（寄送）到指定线程的消息队列里，不等待线程处理消息就返回
_XCOREAPI_ bool __xcall__ PostThreadMessageW(unsigned long _ThreadID, unsigned int Msg, WPARAM wParam, LPARAM lParam);

#endif

///创建注册表项
_XCOREAPI_ bool PlatformRegeditCreate(HKEY _Key, const wchar_t* _SubKey);

#endif
