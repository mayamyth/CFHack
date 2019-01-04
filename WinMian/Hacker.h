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

struct  基址
{
	int 模块基址;
	int 视角基址;
	int 玩家数组;
	int 模式基址;
	int 人物基址;
	int 敌人基址;
	int 设备基址;
	int 矩阵基址;
	int 数组大小;
	int 本人地址;
	int 人物数据;
	int 武器基址;
	int 无后座;
	int 秒杀;
};

struct 世界坐标
{
	float x;
	float y;
	float z;
};

struct 屏幕坐标
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
	bool  矩阵转换(世界坐标 a, 屏幕坐标 *b, int &敌我距离);
	int GeyXy(世界坐标 * a, int Flage);
	int GetMySelfXy(); //取自己的位置
	int GetShengHuo(int ID);
	int GetPlagyer();
	int IsPlayGame(); //是否在游戏
	BOOL GetC4(int a);
public:
	基址 游戏基址;
};