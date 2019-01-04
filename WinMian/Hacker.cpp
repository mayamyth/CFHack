#include "Hacker.h"
int Add(int a, int b)
{
	return a + b;
}
int sub(int a, int b)
{

	return a - b;
}

int axb(int a, int b)
{
	return a * b;
}

VOID Process::Init(int pid, int CShellAddr)
{
	
	OpenDriver();
	SetPid(pid);
	游戏基址.矩阵基址 = 7939308; //OK
	游戏基址.模块基址 = GetDllBase();

	游戏基址.数组大小 = 1840;
	游戏基址.本人地址 = 500; //本人ID

	游戏基址.视角基址 = Add(游戏基址.模块基址, 29483088); //FOV 基址

	游戏基址.模式基址 = Add(游戏基址.模块基址, 21040148);//模式机制

	游戏基址.玩家数组 = Add(游戏基址.模块基址, 21040180); //玩家数组

	游戏基址.人物基址 = Add(ReadProcessInt(游戏基址.玩家数组), 120);//OJBK

	游戏基址.人物数据 = Add(ReadProcessInt(游戏基址.玩家数组), 504);  //OJBK
}

char * Process::GetPlageName(int Index)
{
	BYTE Buffer[16] = { 0 };
	static char strBuffer[100] = " ";
	ReadProcessByteBuffer(Add(Add(游戏基址.人物数据, 6), axb(sub(Index, 1), 游戏基址.数组大小)), 16, Buffer);
	if (strlen((char*)Buffer) == 0) return NULL;

	wsprintf(strBuffer, "人物名称:%s", Buffer);
	return &strBuffer[0];
}

int Process::GetBoold(int i)
{
      int Addr = Add(Add(游戏基址.人物数据, 52), axb(sub(i, 1), 游戏基址.数组大小));
      int Val = ReadProcessshort(Addr);
	  return Val;

}


bool Process ::矩阵转换(世界坐标 a, 屏幕坐标 *b, int &敌我距离)
{
	int 视角;
	int 数据;
	float 距离 = 0;
	float 倍数 = 0;

	D3DXVECTOR3 敌人, 镜像, 差距, 自己;
	byte 世界[64] = { 0, 0, 128, 63, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 63, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 63, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 63 };
	BYTE 观察[64] = { 0x0 };
	BYTE 投影[64] = { 0x0 };
	BYTE 视口[64] = { 0x0 };

	敌人.x = a.x;
	敌人.y = a.z;
	敌人.z = a.y;


	数据 = ReadProcessInt(ReadProcessInt(游戏基址.玩家数组) + 48);
	视角 = ReadProcessFlaot(游戏基址.视角基址) / 0.01745329251994;
	自己.x = ReadProcessFlaot(数据 + 108);
	自己.z = ReadProcessFlaot(数据 + 112);
	自己.y = ReadProcessFlaot(数据 + 116);
	差距.x = 自己.x - a.x;
	差距.y = 自己.y - a.y;
	差距.z = 自己.z - a.z;


	ReadProcessByteBuffer((游戏基址.矩阵基址), 64, 视口);
	ReadProcessByteBuffer((游戏基址.矩阵基址 - 128), 64, 观察);
	ReadProcessByteBuffer((游戏基址.矩阵基址 - 64), 64, 投影);
	D3DXVec3Project(&镜像, &敌人, (D3D10_VIEWPORT *)&视口, (D3DXMATRIX*)&投影, (D3DXMATRIX*)&观察, (D3DXMATRIX*)&世界);
	if (镜像.z > 1.00002)
	{
		return false;
	}
	距离 = (float)sqrt((差距.x * 差距.x) + (差距.y * 差距.y) + (差距.z * 差距.z));
	倍数 = 1000 / 距离;
	敌我距离 = 距离 / 100;
	b->X = (int)(镜像.x - ((((60 * 倍数) / 2) * 100) / 视角));
	b->Y = (int)(镜像.y - (((((100 * 倍数) / 2) * 100) / 视角)*1.35325931));
	b->W = (int)((((50 * 倍数) / 2) * 100) / 视角) * 2;
	b->H = (int)((((130 * 倍数) / 2) * 100) / 视角) * 2;
	return true;
}

int Process :: GeyXy(世界坐标 * a, int Flage)
{
	int Addr = Add(axb(sub(Flage, 1), 游戏基址.数组大小), 游戏基址.人物数据);
	int XyAddr = ReadProcessInt(Addr);
	if (XyAddr < 0)
		return 0;
	a->x = ReadProcessFlaot(Add(XyAddr, 224));
	a->z = ReadProcessFlaot(Add(XyAddr, 228));
	a->y = ReadProcessFlaot(Add(XyAddr, 232));

	return 1;
}

int Process::GetMySelfXy()
{
	return  ReadProcessInt(ReadProcessInt(游戏基址.玩家数组) + 游戏基址.本人地址) + 1;
}

int Process::GetShengHuo(int ID)
{
	return  ReadProcessInt(ReadProcessInt(游戏基址.人物数据 + 20 + (ID - 1)*游戏基址.数组大小) + 314660);
}

int Process::GetPlagyer()
{
	int 类型;
	int 模式指针;
	int 模式[2];
	模式指针 = ReadProcessInt(游戏基址.模式基址);
	类型 = ReadProcessInt(模式指针 + 20);
	if (类型 == 2)
	{
		return 15;
	}
	if (类型 == 7)
	{
		return 16;
	}
	if (类型 == 8)
	{
		return 30;
	}
	模式[0] = ReadProcessInt(模式指针 + 12);
	模式[1] = ReadProcessInt(模式[0] + 220);
	if (模式[1] == 8)
	{
		return 16;
	}
	return 8;

}

int Process::IsPlayGame()
{
	int a;
	a = ReadProcessInt(游戏基址.人物基址 + 4);
	if (a == 1)
	{
		return true;
	}
	return false;
}

BOOL Process::GetC4(int a)
{
    	char Hp[30] = { "" };
		BYTE Val = 0;
      int NC4 = Add(游戏基址.人物数据, 32);
	  ReadProcessByteBuffer(Add(NC4, axb(sub(a, 1), 游戏基址.数组大小)), 1, &Val);
	  int tmp = (int)Val;
	  if(tmp == 1)
		  return 1;
	  else return 0;
}
