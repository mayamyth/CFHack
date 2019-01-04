
#include "WinMain.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND MyWIndowHwnd = 0;
	BOOL nRet = CreateWindows(hInstance, MyWIndowHwnd);
	if (!nRet)
	{
		exit(0);
	}
	else   //ҵ���߼��߳�����
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

		::TranslateMessage(&msg);   //���õ�����Ϣ����
		::DispatchMessage(&msg);    //����������Ϣ����

	}
}

BOOL CreateWindows(HINSTANCE hPrevInstance, HWND &Out_Hwnd)
{
	BOOL nRet = FALSE;
	g_WindowObject =  Window::NewWindow(hPrevInstance);
	if (g_WindowObject == NULL)
	{
		MegText("��������ʧ��");
		return nRet;
		
	}
	nRet = g_WindowObject->MyRegisterClassEx(WINDWS_NAME, MyWinMain);
	if (!nRet)
	{
		MegText("ע�ᴰ��ʧ��");
		return nRet;
	}
	Out_Hwnd = g_WindowObject->MyCreateWindow(WINDWS_NAME, 0, 0, 768, 1024, 0);
	if (!Out_Hwnd)
	{
		MegText("ע�ᴰ�ڴ��ڴ���ʧ��");
		return nRet;
	}

	g_DxObject = DrawDx::NewDraw();
	if (g_DxObject == NULL)
	{
		MegText("����DX����ʧ��");
		return nRet;
	}
	nRet = g_DxObject->DxInit(Out_Hwnd);
	if (!nRet)
	{
		MegText("DX�Գ�ʼ��ʧ��");
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
		g_GameHwnd = FindWindow("CrossFire", "��Խ����");
		if (g_GameHwnd != NULL)
		{
			IsGamgProcessRun = TRUE;
			break;
		}
		g_DxObject->DxDrawStart();
		g_DxObject->DxDrawText(5, 10, L"��      Ϸ       δ   ��       ��", D2D1::ColorF::Yellow, g_WindowObject->GetMyRect(), 10.0f);
		g_DxObject->DxDrawText(5, 20, L"��      ��       F    6        ��         ��          ��         ��", D2D1::ColorF::Yellow, g_WindowObject->GetMyRect());
		g_DxObject->DxEndDraw();

	}

	return 0;
}
static �������� Sava;
static ��Ļ���� Xy[32];
static char Hp[50] = { '/0' };
void Draw(Process *m_Read)
{
	
	int ����;
	int λ�� = m_Read->GetMySelfXy();
	int ���� = m_Read->GetPlagyer();
	bool ����;

	if (λ�� <= 8)
	{
		���� = 0;
	}
	else
	{
		���� = 1;
	}
	if (m_Read->IsPlayGame())
	{

		for (int i = 0; i < 64; i++)
		{
			if (���� == 1)
			{
				if (i + 1 - ���� <= 8)
				{
					���� = true;
				}
				else
				{
					���� = false;
				}
			}
			if (���� == 0)
			{
				if (i + 1 - ���� >9)
				{
					���� = true;
				}
				else
				{
					���� = false;
				}
			}
			if (���� >= 16)
			{
				���� = true;
			}
			if (���� == 15)
			{
				if (m_Read->GetShengHuo(λ��) - m_Read->GetShengHuo(i) != 0)
				{
					���� = true;
				}
				else
				{
					���� = false;
				}
			}
			if (���� == true)
			{
				if (i != m_Read->GetMySelfXy())
				{
					

					if (m_Read->GeyXy(&Sava, i))
					{
						wsprintf(Hp, "%d", m_Read->GetMySelfXy());
						int M = 0;
						if (m_Read->����ת��(Sava, &Xy[i], M))
						{
							int hp = m_Read->GetBoold(i);
                            
							if (hp > 0)
							{
								if (GetAsyncKeyState(VK_TAB))
								{
									wsprintf(Hp, "Ѫ��:%d.����:%d", hp, M);
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
	//crossfire.exe (6424), Mapped image, F:\Program Files\��Ѷ��Ϸ\��Խ����\CShell.dll, 0x16940000




	
	while (1)
	{
		if (!IsGamgProcessRun) continue;
		break;
	}	
	DWORD    Pid = 0;
	g_GameHwnd = FindWindow("CrossFire", "��Խ����");
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
