#pragma once
#include"DX.h"
#include"PrcocessRead.h"
#include <d3d9.h>
#include <D3DX10Math.h>
#pragma comment( lib,"Dwmapi.lib" )
#pragma  comment(lib,"d2d1.lib")
#pragma  comment(lib,"Dwrite.lib")
#pragma comment( lib,"winmm.lib" ) 
#pragma comment( lib,"d3dx9.lib" ) 

struct  ��ַ
{
	int ģ���ַ;
	int �ӽǻ�ַ;
	int �������;
	int ģʽ��ַ;
	int �����ַ;
	int ���˻�ַ;
	int �豸��ַ;
	int �����ַ;
	int �����С;
	int ���˵�ַ;
	int ��������;
	int ������ַ;
	int �޺���;
	int ��ɱ;
};

struct ��������
{
	float x;
	float y;
	float z;
};

struct ��Ļ����
{
	int X;
	int Y;
	int W;
	int H;
};

class Process
{
public:
	VOID Init(int pid,int CShellAddr);
	char *GetPlageName(int Index);
	int  GetBoold(int i);
	bool  ����ת��(�������� a, ��Ļ���� *b, int &���Ҿ���);
	int GeyXy(�������� * a, int Flage);
	int GetMySelfXy(); //ȡ�Լ���λ��
	int GetShengHuo(int ID);
	int GetPlagyer();
	int IsPlayGame(); //�Ƿ�����Ϸ
	BOOL GetC4(int a);
public:
	��ַ ��Ϸ��ַ;
};