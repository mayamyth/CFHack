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
	��Ϸ��ַ.�����ַ = 7939308; //OK
	��Ϸ��ַ.ģ���ַ = GetDllBase();

	��Ϸ��ַ.�����С = 1840;
	��Ϸ��ַ.���˵�ַ = 500; //����ID

	��Ϸ��ַ.�ӽǻ�ַ = Add(��Ϸ��ַ.ģ���ַ, 29483088); //FOV ��ַ

	��Ϸ��ַ.ģʽ��ַ = Add(��Ϸ��ַ.ģ���ַ, 21040148);//ģʽ����

	��Ϸ��ַ.������� = Add(��Ϸ��ַ.ģ���ַ, 21040180); //�������

	��Ϸ��ַ.�����ַ = Add(ReadProcessInt(��Ϸ��ַ.�������), 120);//OJBK

	��Ϸ��ַ.�������� = Add(ReadProcessInt(��Ϸ��ַ.�������), 504);  //OJBK
}

char * Process::GetPlageName(int Index)
{
	BYTE Buffer[16] = { 0 };
	static char strBuffer[100] = " ";
	ReadProcessByteBuffer(Add(Add(��Ϸ��ַ.��������, 6), axb(sub(Index, 1), ��Ϸ��ַ.�����С)), 16, Buffer);
	if (strlen((char*)Buffer) == 0) return NULL;

	wsprintf(strBuffer, "��������:%s", Buffer);
	return &strBuffer[0];
}

int Process::GetBoold(int i)
{
      int Addr = Add(Add(��Ϸ��ַ.��������, 52), axb(sub(i, 1), ��Ϸ��ַ.�����С));
      int Val = ReadProcessshort(Addr);
	  return Val;

}


bool Process ::����ת��(�������� a, ��Ļ���� *b, int &���Ҿ���)
{
	int �ӽ�;
	int ����;
	float ���� = 0;
	float ���� = 0;

	D3DXVECTOR3 ����, ����, ���, �Լ�;
	byte ����[64] = { 0, 0, 128, 63, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 63, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 63, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 63 };
	BYTE �۲�[64] = { 0x0 };
	BYTE ͶӰ[64] = { 0x0 };
	BYTE �ӿ�[64] = { 0x0 };

	����.x = a.x;
	����.y = a.z;
	����.z = a.y;


	���� = ReadProcessInt(ReadProcessInt(��Ϸ��ַ.�������) + 48);
	�ӽ� = ReadProcessFlaot(��Ϸ��ַ.�ӽǻ�ַ) / 0.01745329251994;
	�Լ�.x = ReadProcessFlaot(���� + 108);
	�Լ�.z = ReadProcessFlaot(���� + 112);
	�Լ�.y = ReadProcessFlaot(���� + 116);
	���.x = �Լ�.x - a.x;
	���.y = �Լ�.y - a.y;
	���.z = �Լ�.z - a.z;


	ReadProcessByteBuffer((��Ϸ��ַ.�����ַ), 64, �ӿ�);
	ReadProcessByteBuffer((��Ϸ��ַ.�����ַ - 128), 64, �۲�);
	ReadProcessByteBuffer((��Ϸ��ַ.�����ַ - 64), 64, ͶӰ);
	D3DXVec3Project(&����, &����, (D3D10_VIEWPORT *)&�ӿ�, (D3DXMATRIX*)&ͶӰ, (D3DXMATRIX*)&�۲�, (D3DXMATRIX*)&����);
	if (����.z > 1.00002)
	{
		return false;
	}
	���� = (float)sqrt((���.x * ���.x) + (���.y * ���.y) + (���.z * ���.z));
	���� = 1000 / ����;
	���Ҿ��� = ���� / 100;
	b->X = (int)(����.x - ((((60 * ����) / 2) * 100) / �ӽ�));
	b->Y = (int)(����.y - (((((100 * ����) / 2) * 100) / �ӽ�)*1.35325931));
	b->W = (int)((((50 * ����) / 2) * 100) / �ӽ�) * 2;
	b->H = (int)((((130 * ����) / 2) * 100) / �ӽ�) * 2;
	return true;
}

int Process :: GeyXy(�������� * a, int Flage)
{
	int Addr = Add(axb(sub(Flage, 1), ��Ϸ��ַ.�����С), ��Ϸ��ַ.��������);
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
	return  ReadProcessInt(ReadProcessInt(��Ϸ��ַ.�������) + ��Ϸ��ַ.���˵�ַ) + 1;
}

int Process::GetShengHuo(int ID)
{
	return  ReadProcessInt(ReadProcessInt(��Ϸ��ַ.�������� + 20 + (ID - 1)*��Ϸ��ַ.�����С) + 314660);
}

int Process::GetPlagyer()
{
	int ����;
	int ģʽָ��;
	int ģʽ[2];
	ģʽָ�� = ReadProcessInt(��Ϸ��ַ.ģʽ��ַ);
	���� = ReadProcessInt(ģʽָ�� + 20);
	if (���� == 2)
	{
		return 15;
	}
	if (���� == 7)
	{
		return 16;
	}
	if (���� == 8)
	{
		return 30;
	}
	ģʽ[0] = ReadProcessInt(ģʽָ�� + 12);
	ģʽ[1] = ReadProcessInt(ģʽ[0] + 220);
	if (ģʽ[1] == 8)
	{
		return 16;
	}
	return 8;

}

int Process::IsPlayGame()
{
	int a;
	a = ReadProcessInt(��Ϸ��ַ.�����ַ + 4);
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
      int NC4 = Add(��Ϸ��ַ.��������, 32);
	  ReadProcessByteBuffer(Add(NC4, axb(sub(a, 1), ��Ϸ��ַ.�����С)), 1, &Val);
	  int tmp = (int)Val;
	  if(tmp == 1)
		  return 1;
	  else return 0;
}
