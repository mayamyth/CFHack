#include "PrcocessRead.h"

BOOL OpenDriver()
{
	m_hDevice = CreateFileA(DRIVER_LINK_NAME, GENERIC_READ | GENERIC_WRITE, 0,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL);
	if (m_hDevice == (HANDLE)-1)
	{
		MessageBox(0, "驱动加载失败", 0, 0);
		exit(0);
	}
	char KaMi[] = "CFMB0089A34F72D2E46D36793A6BA356";
	DWORD n;
	_Hread h;
	h.Flage = 6;
	h.WriteBufferAddr = (ULONG)&KaMi;
	BOOL nRet = DeviceIoControl(m_hDevice, SET_PROCESS, &h, sizeof(_Hread), NULL, 0, &n, 0);
	if (!nRet) {
		MessageBox(0, "验证失败", 0, 0);
		exit(0);
	}

	return 0;
}

void CloseDeiver()
{
	CloseHandle(m_hDevice);
}

void SetPid(int pid)
{
	DWORD n;
	_Hread h;
	m_pid = pid;
    h.Pid = m_pid;
	h.Flage = SETPROCESS;
	BOOL nRet = DeviceIoControl(m_hDevice, SET_PROCESS, &h, sizeof(_Hread), NULL, 0, &n, 0);
}

 BOOL DrvReadProcessMemory(HANDLE m_hDevice, int lpBaseAddress, LPVOID lpBuffer, DWORD nSize)
{
	 DWORD n;
	   _Hread h;
	   h.Addr = lpBaseAddress;
	   h.Size = nSize;
	   h.Flage =READPROCESS;
	   h.IsWin10 = FALSE;
	   BOOL nRet = DeviceIoControl(m_hDevice, SET_PROCESS, &h, sizeof(_Hread), lpBuffer, nSize, &n, 0);
       return nRet;

}
BOOL ReadProcessInt(int Addr)
{

	BOOL nRet = FALSE;
	int Val = 0;
	nRet = DrvReadProcessMemory(m_hDevice, Addr, &Val, sizeof(int));
	if (!nRet) return nRet;
	return Val;
}

BOOL ReadProcessByteBuffer(int Addr, int Size, BYTE * Buffer)
{
	BOOL nRet = FALSE;

	nRet = DrvReadProcessMemory(m_hDevice, Addr, Buffer, Size);

	return nRet;
}

ULONGLONG GetDllBase()
{
	_Hread h;
	DWORD n;
	ULONGLONG BaseAddr = 0;
	char CNmae[] = "cshell.dll";
	h.Flage = GETDLLBASSE;
	h.WriteBufferAddr = (ULONG)&CNmae;
	BOOL nRet = DeviceIoControl(m_hDevice, SET_PROCESS, &h, sizeof(_Hread), &BaseAddr, 8, &n, 0);
	return BaseAddr;
}


short ReadProcessshort(int Addr)
{
	BOOL nRet = FALSE;
	short Val = 0;
	DrvReadProcessMemory(m_hDevice, Addr, &Val, sizeof(short));
	return Val;
}




float ReadProcessFlaot(int Addr)
{
	float Val = 0;
	DrvReadProcessMemory(m_hDevice, Addr, &Val, sizeof(float));
	return Val;
}