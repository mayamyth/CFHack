#pragma once
#include "Windows.h"
#include "DX.h"
#include "Hacker.h"
#define WINDWS_NAME "TestOn"
static Window *g_WindowObject = NULL; //窗口对象
static DrawDx *g_DxObject = NULL;   //DX对象
static HWND g_GameHwnd= NULL;    //游戏窗口句柄
static BOOL IsGamgProcessRun = FALSE;     //游戏启动标志
VOID MegText(const char *Text);
void MsgRecv();
void  Draw(Process *m_Read);
LRESULT  CALLBACK MyWinMain(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam); //消息处理
BOOL CreateWindows(HINSTANCE hPrevInstance,HWND  &Out_Hwnd);
DWORD WINAPI OnServer(LPVOID lp);  //业务线程1
DWORD WINAPI OnGameRun(LPVOID lp); //业务线程2

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);