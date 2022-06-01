#include <xanadu-core/XNative.h>
#include <xanadu-core/XMutex.h>


// Native platform variable declarations
#ifndef XANADU_SYSTEM_WINDOWS
std::map<unsigned long, std::vector<MSG>>	_StaticMessageArray;			// 全局线程消息队列
XMutex						_StaticMessageMutex;			// 消息队列互斥量
#endif

#ifndef XANADU_SYSTEM_WINDOWS
//从调用线程的消息队列里取得一个消息并将其放于指定的结构。
//此函数可取得与指定窗口联系的消息和由PostThreadMessage寄送的线程消息。
//此函数接收一定范围的消息值。GetMessage不接收属于其他线程或应用程序的消息。
//获取消息成功后，线程将从消息队列中删除该消息。
//函数会一直等待直到有消息到来才有返回值。
_XCOREAPI_ bool __xcall__ GetMessageW(LPMSG lpMsg, HWND hWnd, unsigned int wMsgFilterMin, unsigned int wMsgFilterMax)
{
	XANADU_CHECK_RETURN(lpMsg, false);

	while(!PeekMessageW(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax, PM_REMOVE))
	{
		x_posix_msleep(1);
	};
	return true;
}

//检查线程消息队列，并将该消息（如果存在）放于指定的结构
_XCOREAPI_ bool __xcall__ PeekMessageW(LPMSG lpMsg, HWND hWnd, unsigned int wMsgFilterMin, unsigned int wMsgFilterMax, unsigned int wRemoveMsg)
{
	XANADU_CHECK_RETURN(lpMsg, false);

	auto			vThreadID = x_posix_gettid();
	auto			vFind = false;
	XANADU_MUTEX_AUTO(_StaticMessageMutex);

	auto		vIterator = _StaticMessageArray.find(vThreadID);
	if(vIterator != _StaticMessageArray.end())
	{
		if(vIterator->second.size())
		{
			for(auto vIteratorArray = vIterator->second.begin(); vIteratorArray != vIterator->second.end(); ++vIteratorArray)
			{
				if(wMsgFilterMin <= vIteratorArray->message && vIteratorArray->message <= wMsgFilterMax)
				{
					vFind = true;
					memcpy(lpMsg, &(*vIteratorArray), sizeof(MSG));

					switch(wRemoveMsg)
					{
						case PM_REMOVE:
							vIterator->second.erase(vIteratorArray);
							break;
						default:
							break;
					}
					break;
				}
			}
		}
		else
		{
			_StaticMessageArray.erase(vIterator);
		}
	}
	return vFind;
}

//将一个队列消息放入（寄送）到指定线程的消息队列里，不等待线程处理消息就返回
_XCOREAPI_ bool __xcall__ PostThreadMessageW(unsigned long _ThreadID, unsigned int Msg, WPARAM wParam, LPARAM lParam)
{
	XANADU_MUTEX_AUTO(_StaticMessageMutex);

	auto		vIterator = _StaticMessageArray.find(_ThreadID);
	if(vIterator == _StaticMessageArray.end())
	{
		_StaticMessageArray.insert(std::map<unsigned long, std::vector<MSG>>::value_type(_ThreadID, std::vector<MSG>()));
	}
	vIterator = _StaticMessageArray.find(_ThreadID);
	if(vIterator != _StaticMessageArray.end())
	{
		MSG	vMessage;
		x_posix_memset(&vMessage, 0, sizeof(MSG));
		vMessage.message = Msg;
		vMessage.wParam = wParam;
		vMessage.lParam = lParam;

		vIterator->second.push_back(vMessage);
		return true;
	}
	return false;
}

#endif

// 创建注册表项
_XCOREAPI_ bool PlatformRegeditCreate(HKEY _Key, const wchar_t* _SubKey)
{
#if defined(XANADU_SYSTEM_WINDOWS)
	HKEY			vNewKey = nullptr;
	::RegCreateKeyW(_Key, _SubKey, &vNewKey);
	if(vNewKey)
	{
		::RegCloseKey(vNewKey);
		return true;
	}
#endif
	return false;
}
