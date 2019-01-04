
#include "WinMain.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND MyWIndowHwnd = 0;
	BOOL nRet = CreateWindows(hInstance, MyWIndowHwnd);
	if (!nRet)
	{
		exit(0);
	}
	else   //业务逻辑线程启动
	{
		CloseHandle(CreateThread(NULL, 0, OnServer, NULL, 0, 0));
		CloseHandle(CreateThread(NULL, 0, OnGameRun, MyWIndowHwnd, 0, 0));
		MsgRecv();
	}
	return 0;
}

VOID MegText(const char * Text)
{
	MessageBox(NULL, Text, " ",0);
}



LRESULT  CALLBACK MyWinMain(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CLOSE:  PostQuitMessage(0);	 break;
	}
	return  DefWindowProc(hWnd, uMsg, wParam, lParam);
}
void MsgRecv()
{
	MSG msg;
	while (::GetMessage(&msg, 0, 0, 0))
	{

		::TranslateMessage(&msg);   //将得到的消息翻译
		::DispatchMessage(&msg);    //翻译来的消息发送

	}
}

BOOL CreateWindows(HINSTANCE hPrevInstance, HWND &Out_Hwnd)
{
	BOOL nRet = FALSE;
	g_WindowObject =  Window::NewWindow(hPrevInstance);
	if (g_WindowObject == NULL)
	{
		MegText("创建窗口失败");
		return nRet;
		
	}
	nRet = g_WindowObject->MyRegisterClassEx(WINDWS_NAME, MyWinMain);
	if (!nRet)
	{
		MegText("注册窗口失败");
		return nRet;
	}
	Out_Hwnd = g_WindowObject->MyCreateWindow(WINDWS_NAME, 0, 0, 768, 1024, 0);
	if (!Out_Hwnd)
	{
		MegText("注册窗口窗口创建失败");
		return nRet;
	}

	g_DxObject = DrawDx::NewDraw();
	if (g_DxObject == NULL)
	{
		MegText("创建DX对象失败");
		return nRet;
	}
	nRet = g_DxObject->DxInit(Out_Hwnd);
	if (!nRet)
	{
		MegText("DX对初始化失败");
		return nRet;
	}
	
	return nRet;
}



DWORD WINAPI OnServer(LPVOID lp)
{

	while (1)
	{
		if (GetAsyncKeyState(VK_F6))
		{
			exit(0);
		}
		g_GameHwnd = FindWindow("CrossFire", "穿越火线");
		if (g_GameHwnd != NULL)
		{
			IsGamgProcessRun = TRUE;
			break;
		}
		g_DxObject->DxDrawStart();
		g_DxObject->DxDrawText(5, 10, L"游      戏       未   启       动", D2D1::ColorF::Yellow, g_WindowObject->GetMyRect(), 10.0f);
		g_DxObject->DxDrawText(5, 20, L"按      下       F    6        退         出          外         挂", D2D1::ColorF::Yellow, g_WindowObject->GetMyRect());
		g_DxObject->DxEndDraw();

	}

	return 0;
}
static 世界坐标 Sava;
static 屏幕坐标 Xy[32];
static char Hp[50] = { '/0' };
void Draw(Process *m_Read)
{
	
	int 警察;
	int 位置 = m_Read->GetMySelfXy();
	int 人数 = m_Read->GetPlagyer();
	bool 敌人;

	if (位置 <= 8)
	{
		警察 = 0;
	}
	else
	{
		警察 = 1;
	}
	if (m_Read->IsPlayGame())
	{

		for (int i = 0; i < 64; i++)
		{
			if (警察 == 1)
			{
				if (i + 1 - 警察 <= 8)
				{
					敌人 = true;
				}
				else
				{
					敌人 = false;
				}
			}
			if (警察 == 0)
			{
				if (i + 1 - 警察 >9)
				{
					敌人 = true;
				}
				else
				{
					敌人 = false;
				}
			}
			if (人数 >= 16)
			{
				敌人 = true;
			}
			if (人数 == 15)
			{
				if (m_Read->GetShengHuo(位置) - m_Read->GetShengHuo(i) != 0)
				{
					敌人 = true;
				}
				else
				{
					敌人 = false;
				}
			}
			if (敌人 == true)
			{
				if (i != m_Read->GetMySelfXy())
				{
					

					if (m_Read->GeyXy(&Sava, i))
					{
						wsprintf(Hp, "%d", m_Read->GetMySelfXy());
						int M = 0;
						if (m_Read->矩阵转换(Sava, &Xy[i], M))
						{
							int hp = m_Read->GetBoold(i);
                            
							if (hp > 0)
							{
								if (GetAsyncKeyState(VK_TAB))
								{
									wsprintf(Hp, "血量:%d.距离:%d", hp, M);
									g_DxObject->DrawRenderTextA(Xy[i].X, Xy[i].Y - 10, Hp, D2D1::ColorF::Red, g_WindowObject->GetMyRect());
								}
							
	                              g_DxObject->DxDrawBox(Xy[i].X, Xy[i].Y, Xy[i].W, Xy[i].H, D2D1::ColorF::Red, 1.0f);

							
								ZeroMemory(Hp, 50);
							}
						}
					}
				}
			}

		}
		
	}



}

DWORD WINAPI OnGameRun(LPVOID lp)
{
	HWND MyHwnd = (HWND)lp;
	Process *m_Read = new Process();
	//crossfire.exe (6424), Mapped image, F:\Program Files\腾讯游戏\穿越火线\CShell.dll, 0x16940000




	
	while (1)
	{
		if (!IsGamgProcessRun) continue;
		break;
	}	
	DWORD    Pid = 0;
	g_GameHwnd = FindWindow("CrossFire", "穿越火线");
	GetWindowThreadProcessId(g_GameHwnd, &Pid);


    m_Read->Init(Pid, 0x16940000);
	while (1)
	{
		if (GetAsyncKeyState(VK_F6))
		{
	
			exit(0);
		}	
		g_DxObject->MoveWindowAndDraw(g_GameHwnd, MyHwnd);
		g_DxObject->DxDrawStart();
		Draw(m_Read);
		g_DxObject->DxEndDraw();
	}


	return 0;
}
