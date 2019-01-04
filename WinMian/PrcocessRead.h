#pragma once
#include<windows.h>
#define DELAY_ONE_MICROSECOND   (-10)
#define DELAY_ONE_MILLISECOND   (DELAY_ONE_MICROSECOND*1000)
#define CODE_BASE 0x800
#define SETPROCESS 1
#define READPROCESS 2
#define WRITEROCESS 3
#define GETDLLBASSE 4
#define TP 5
#define SET_PROCESS CTL_CODE(FILE_DEVICE_UNKNOWN, CODE_BASE, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define DRIVER_LINK_NAME    "\\??\\DeGuoBe"
#define DEVICE_OBJECT_NAME  "\\Device\\DeGuoBe"

static int m_pid = -1;
static HANDLE m_hDevice;

typedef struct Read_Info
{

	int Addr;
	int Size;
	int Ex;

}m_Read, *p_Read;


typedef struct Hread {
	ULONG Flage;
	ULONG Addr;
	ULONG WriteBufferAddr;
	ULONG Size;
	ULONG Pid;
	ULONG IsWin10;
}_Hread, *PtrHread;

BOOL OpenDriver();

void CloseDeiver();

void SetPid(int pid);

BOOL DrvReadProcessMemory(HANDLE m_hDevice, int lpBaseAddress, LPVOID lpBuffer, DWORD nSize);

int ReadProcessInt(int Addr);


float ReadProcessFlaot(int Addr);

short ReadProcessshort(int Addr);


BOOL ReadProcessByteBuffer(int Addr, int Size, BYTE * Buffer);

ULONGLONG GetDllBase();