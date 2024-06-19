#include <iostream>
#define MAX 100							//ʹ�ú궨���������
using namespace std;
void Output(int arr[][MAX]);			//����������ݵĺ���
void Zifan(int arr2[][MAX]);			//�����Է��հ����㷨
void Duichen(int arr2[][MAX]);		//����ԳƱհ����㷨
void Chuandi(int arr2[][MAX]);		//���㴫�ݱհ����㷨
void Select();							//ѡ����Ӧ�����ĺ���
void Exitprogram();						//�˳�����ĺ���
int arr[MAX][MAX], choice;				//��������ȫ�ֱ�������ϵ�����ѡ������ı���
int row, col, i, j;						//������������ѭ������
//�������������֤����ľ���Ԫ��ֻ��0��1��
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
			cout << "����������������룡";
			continue;
		}
		break;
	}
	return retint;
}
//������������ѡ����
int main()
{
	Select();
	return 0;
}
//ѡ����
void Select()
{
	cout << "��������������:";			//��������
	while (1)
	{
		cin >> row;
		if (cin.good() == 0 || row < 1)
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "���������������������룡" << endl;
			continue;
		}
		break;
	}
	cout << "��������������:";			//��������
	while (1)
	{
		cin >> col;
		if (cin.good() == 0 || col < 1)
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "���������������������룡" << endl;
			continue;
		}
		break;
	}
	cout << "�������ϵ����:" << endl;	//�����ϵ����
	for (i = 0; i < row; i++)
	{
		cout << endl << "���������ĵ�" << i << "��Ԫ��(Ԫ���Կո�ָ�):";
		for (j = 0; j < col; j++)
			arr[i][j] = Get_element();
	}
	cout << "�����Ӧ���ѡ���㷨" << endl << "1:�Է��հ�" << endl << "2:���ݱհ�" << endl << "3:�ԳƱհ�" << endl << "4:�˳�" << endl;
	cin >> choice;
	switch (choice)
	{
	case 1:
		Zifan(arr);						//�����Է��հ��㷨����
		break;
	case 2:
		Chuandi(arr);					//���ô��ݱհ��㷨����
		break;
	case 3:
		Duichen(arr);					//���öԳƱհ��㷨����
		break;
	case 4:
		Exitprogram();					//�˳�����
		break;
	default:
		cout << "ѡ�����������ѡ��" << endl; //���������ʱ������ʾ
		Select();						//����ѡ�����
	}
}
//����������ݵĺ���
void Output(int arr[][MAX])
{
	cout << "�����ϵ����Ϊ:" << endl;	//���������ʾ
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
			cout << arr[i][j];			//�����ϵ����
		cout << endl;
	}
	cout << endl;
}
//�����Է��հ����㷨
void Zifan(int arr2[][MAX])
{
	for (i = 0; i < row; i++)
		arr2[i][i] = 1;				//�Է��հ��Ĺ������Խ����ϵ�Ԫ�ض���Ϊ1
	Output(arr2);					//�����Ӧ�ĵĹ�ϵ����
	Select();						//����ѡ�����
}
//����ԳƱհ����㷨
void Duichen(int arr2[][MAX])
{
	int arr1[MAX][MAX];
	for (i = 0; i < row; i++)
		for (j = 0; j < col; j++)
			arr1[j][i] = arr2[i][j];				//��ȡ��ϵ�����ת�þ���
	for (i = 0; i < row; i++)
		for (j = 0; j < col; j++)
		{
			arr2[i][j] = arr2[i][j] + arr1[i][j];	//�ԳƱհ��Ĺ��죺����Ԫ������ת��Ԫ�����
			if (arr2[i][j] > 1)
				arr2[i][j] = 1;						//����1��Ԫ��ȫ����Ϊ1
		}
	Output(arr2);									//�����Ӧ�ĵĹ�ϵ����
	Select();										//����ѡ�����
}
//���㴫�ݱհ����㷨
void Chuandi(int arr2[][MAX])
{
	int temparr1[MAX][MAX], temparr2[MAX][MAX], k, h;	//����������ʱ����temparr1��temparr2��ѭ������k��h
	int result_arr[MAX][MAX];							//������飬��Ž��
	//��ʼ����������
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			temparr2[i][j] = 0;						//temparr2���鸳ֵΪ0
			result_arr[i][j] = arr2[i][j];			//result_arr��temparr1���鸳ֵΪԭ��������
			temparr1[i][j] = arr2[i][j];
		}
	}
	//��������������
	for (h = 0; h < row; h++)
	{
		for (i = 0; i < row; i++)
			for (j = 0; j < col; j++)
				if (temparr1[i][j] == 1)			//���temparr1����ĳ��λ��Ϊ1
				{
					for (k = 0; k < row; k++)		//�����ԭ����Ķ�Ӧ�У��������1����temparr2��Ӧλ����Ϊ1
						if (arr2[j][k] == 1)
							temparr2[i][k] = 1;
				}
		for (i = 0; i < row; i++)
			for (j = 0; j < col; j++)
			{
				temparr1[i][j] = temparr2[i][j];
				result_arr[i][j] += temparr2[i][j];		//��result_arr��temparr2�������
				temparr2[i][j] = 0;
				if (result_arr[i][j] > 1)				//����1��Ԫ��ȫ����Ϊ1
					result_arr[i][j] = 1;
			}
	}
	Output(result_arr);									//������ս������		
	Select(); 
}
//�˳�����ĺ���
void Exitprogram()
{
	cout << "��ӭ�´��ٴ�ʹ��!" << endl;		//�����ӭ��ʾ
	exit(0);								//�˳�����
}