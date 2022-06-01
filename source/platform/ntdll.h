#ifndef			_XANADU_CORE_NTDLL_H_
#define			_XANADU_CORE_NTDLL_H_

#include <xanadu-core/xanadu.h>


// namespace ntdll
namespace ntdll
{
	// NtReadVirtualMemory
	NTSTATUS NtReadVirtualMemory(HANDLE ProcessHandle, PVOID BaseAddress, void* Buffer, SIZE_T BufferSize, PSIZE_T NumberOfBytesRead) noexcept;

	// NtWriteVirtualMemory
	NTSTATUS NtWriteVirtualMemory(HANDLE ProcessHandle, PVOID BaseAddress, const void* Buffer, SIZE_T BufferSize, PSIZE_T NumberOfBytesWritten) noexcept;

	// NtUnmapViewOfSection
	NTSTATUS NtUnmapViewOfSection(HANDLE ProcessHandle, PVOID BaseAddress) noexcept;
}

#endif
