#include <iostream>
using namespace std;
void Init();						//初始化函数
void Output();						//输出1矩阵内容函数
void Warshell();					//Warshell算法求传递闭包
void DeleteArray();					//回收空间，合理释放内存
int** Array, n;						//两个全局变量，二维数组指针和行（列）数
//输入矩阵函数（保证输入的矩阵元素只有0和1），代码的健壮性
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
			cout << "输入错误！请重新输入：";
			continue;
		}
		break;
	}
	return retint;
}
//初始化函数，确定矩阵的行（列）数和具体内容
void Init()
{
	cout << "请输入矩阵行（列）数：";
	//输入行（列）数，并做代码的健壮性检验
	while (1) 
	{
		cin >> n;
		if (cin.good() == 0 || n < 1)
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "输入矩阵行（列）数错误！请再次输入:" << endl;
			continue;
		}
		break;
	}
	cout << endl << "首先创建初始矩阵：" << endl;
	//合理动态分配空间，防止空间浪费
	Array = new int* [n];
	for (int i = 0; i < n; i++)
		Array[i] = new int[n];
	for (int i = 0; i < n; i++) 
	{
		cout << endl << "请输入矩阵的第" << i << "行元素（元素以空格分隔）：";
		for (int j = 0; j < n; j++)
			Array[i][j] = Get_element();
	}
	cout << endl;
	cout << "初始矩阵为：" << endl;
	Output();
}
//输出矩阵具体内容的函数
void Output()
{
	//遍历关系矩阵并打印
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cout << Array[i][j] << " ";
		cout << endl << endl;
	}	
}
//Warshell算法求传递闭包
void Warshell()
{
//(1)首先使i＝0；
//(2)之后再对所有j如果满足Array[j，i]＝1，则对k＝0，1，…，n-1，Array[j，k]＝Array[j，k]∨Array[i，k]；
//(3)再使i加1；
//(4)进行判断，如果满足i<n，则重新跳转到步骤(2)进行循环操作，否则便停止
//(5)最后得出用Warshell算法得出的传递闭包
	int col = 0;
	int row = 0;
	int k = 0;
	for (col = 0; col < n; col++)										//总共有n次遍历，col是列
	{
		for (row = 0; row < n; row++)									//进行检查第col列是否有1存在
		{
			if (Array[row][col] == 1)									//若第row行col列是1，则把第col列各个元素对应加到第row行
			{
				for (k = 0; k < n; k++)
					Array[row][k] = Array[row][k] | Array[col][k];		//进行逻辑加 
			}
		}
	}
}
//回收刚刚分配空间的Array数组，释放内存
void DeleteArray()
{
	//逐步释放空间，释放每一行的数组
	for (int i = 0; i < n; i++)
		delete[] Array[i];
}
//主函数调用各个解函数来获得最终结果
int main()
{
	Init();
	cout << "------------Warshell算法求传递闭包------------" << endl << endl;
	Warshell();
	cout << "所得的关系矩阵为：" << endl;
	Output();
	DeleteArray();
	return 0;
}