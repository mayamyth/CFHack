#pragma once
#include "Windows.h"
#include "DX.h"
#include "Hacker.h"
#define WINDWS_NAME "TestOn"
static Window *g_WindowObject = NULL; //���ڶ���
static DrawDx *g_DxObject = NULL;   //DX����
static HWND g_GameHwnd= NULL;    //��Ϸ���ھ��
static BOOL IsGamgProcessRun = FALSE;     //��Ϸ������־
VOID MegText(const char *Text);
void MsgRecv();
void  Draw(Process *m_Read);
LRESULT  CALLBACK MyWinMain(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam); //��Ϣ����
BOOL CreateWindows(HINSTANCE hPrevInstance,HWND  &Out_Hwnd);
DWORD WINAPI OnServer(LPVOID lp);  //ҵ���߳�1
DWORD WINAPI OnGameRun(LPVOID lp); //ҵ���߳�2

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);