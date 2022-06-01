#include <source/platform/ntdll.h>



// NtReadVirtualMemory
NTSTATUS ntdll::NtReadVirtualMemory(HANDLE ProcessHandle, PVOID BaseAddress, void* Buffer, SIZE_T BufferSize, PSIZE_T NumberOfBytesRead) noexcept
{
	typedef NTSTATUS (NTAPI *NT_ReadVirtualMemory)(HANDLE ProcessHandle, PVOID BaseAddress, void* Buffer, SIZE_T BufferSize, PSIZE_T NumberOfBytesRead);
	auto		vModule = LoadLibraryA("ntdll.dll");
	auto		vFunction = (NT_ReadVirtualMemory)GetProcAddress(vModule, "NtReadVirtualMemory");
	return vFunction(ProcessHandle, BaseAddress, Buffer, BufferSize, NumberOfBytesRead);
}

// NtWriteVirtualMemory
NTSTATUS ntdll::NtWriteVirtualMemory(HANDLE ProcessHandle, PVOID BaseAddress, const void* Buffer, SIZE_T BufferSize, PSIZE_T NumberOfBytesWritten) noexcept
{
	typedef NTSTATUS (NTAPI *NT_WriteVirtualMemory)(HANDLE ProcessHandle, PVOID BaseAddress, const void* Buffer, SIZE_T BufferSize, PSIZE_T NumberOfBytesWritten);
	auto		vModule = LoadLibraryA("ntdll.dll");
	auto		vFunction = (NT_WriteVirtualMemory)GetProcAddress(vModule, "NtWriteVirtualMemory");
	return vFunction(ProcessHandle, BaseAddress, Buffer, BufferSize, NumberOfBytesWritten);
}

// NtUnmapViewOfSection
NTSTATUS ntdll::NtUnmapViewOfSection(HANDLE ProcessHandle, PVOID BaseAddress) noexcept
{
	typedef NTSTATUS (NTAPI *NT_UnmapViewOfSection)(HANDLE ProcessHandle, PVOID BaseAddress);
	auto		vModule = LoadLibraryA("ntdll.dll");
	auto		vFunction = (NT_UnmapViewOfSection)GetProcAddress(vModule, "NtUnmapViewOfSection");
	return vFunction(ProcessHandle, BaseAddress);
}
