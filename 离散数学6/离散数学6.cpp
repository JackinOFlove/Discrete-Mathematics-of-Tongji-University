#include <iostream>
using namespace std;
void Init();						//��ʼ������
void Output();						//���1�������ݺ���
void Warshell();					//Warshell�㷨�󴫵ݱհ�
void DeleteArray();					//���տռ䣬�����ͷ��ڴ�
int** Array, n;						//����ȫ�ֱ�������ά����ָ����У��У���
//�������������֤����ľ���Ԫ��ֻ��0��1��������Ľ�׳��
int Get_element()
{
	int retint;
	while (1)
	{
		cin >> retint;
		if (cin.good() == 0 || (retint != 0 && retint != 1))
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "����������������룺";
			continue;
		}
		break;
	}
	return retint;
}
//��ʼ��������ȷ��������У��У����;�������
void Init()
{
	cout << "����������У��У�����";
	//�����У��У�������������Ľ�׳�Լ���
	while (1) 
	{
		cin >> n;
		if (cin.good() == 0 || n < 1)
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "��������У��У����������ٴ�����:" << endl;
			continue;
		}
		break;
	}
	cout << endl << "���ȴ�����ʼ����" << endl;
	//����̬����ռ䣬��ֹ�ռ��˷�
	Array = new int* [n];
	for (int i = 0; i < n; i++)
		Array[i] = new int[n];
	for (int i = 0; i < n; i++) 
	{
		cout << endl << "���������ĵ�" << i << "��Ԫ�أ�Ԫ���Կո�ָ�����";
		for (int j = 0; j < n; j++)
			Array[i][j] = Get_element();
	}
	cout << endl;
	cout << "��ʼ����Ϊ��" << endl;
	Output();
}
//�������������ݵĺ���
void Output()
{
	//������ϵ���󲢴�ӡ
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cout << Array[i][j] << " ";
		cout << endl << endl;
	}	
}
//Warshell�㷨�󴫵ݱհ�
void Warshell()
{
//(1)����ʹi��0��
//(2)֮���ٶ�����j�������Array[j��i]��1�����k��0��1������n-1��Array[j��k]��Array[j��k]��Array[i��k]��
//(3)��ʹi��1��
//(4)�����жϣ��������i<n����������ת������(2)����ѭ�������������ֹͣ
//(5)���ó���Warshell�㷨�ó��Ĵ��ݱհ�
	int col = 0;
	int row = 0;
	int k = 0;
	for (col = 0; col < n; col++)										//�ܹ���n�α�����col����
	{
		for (row = 0; row < n; row++)									//���м���col���Ƿ���1����
		{
			if (Array[row][col] == 1)									//����row��col����1����ѵ�col�и���Ԫ�ض�Ӧ�ӵ���row��
			{
				for (k = 0; k < n; k++)
					Array[row][k] = Array[row][k] | Array[col][k];		//�����߼��� 
			}
		}
	}
}
//���ոոշ���ռ��Array���飬�ͷ��ڴ�
void DeleteArray()
{
	//���ͷſռ䣬�ͷ�ÿһ�е�����
	for (int i = 0; i < n; i++)
		delete[] Array[i];
}
//���������ø����⺯����������ս��
int main()
{
	Init();
	cout << "------------Warshell�㷨�󴫵ݱհ�------------" << endl << endl;
	Warshell();
	cout << "���õĹ�ϵ����Ϊ��" << endl;
	Output();
	DeleteArray();
	return 0;
}