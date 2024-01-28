#include <iostream>
#define MAX 100							//使用宏定义代替数字
using namespace std;
void Output(int arr[][MAX]);			//输出矩阵内容的函数
void Zifan(int arr2[][MAX]);			//计算自反闭包的算法
void Duichen(int arr2[][MAX]);		//计算对称闭包的算法
void Chuandi(int arr2[][MAX]);		//计算传递闭包的算法
void Select();							//选择相应操作的函数
void Exitprogram();						//退出程序的函数
int arr[MAX][MAX], choice;				//设置两个全局变量：关系矩阵和选择操作的变量
int row, col, i, j;						//行数、列数、循环变量
//输入矩阵函数（保证输入的矩阵元素只有0和1）
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
			cout << "输入错误！请重新输入！";
			continue;
		}
		break;
	}
	return retint;
}
//主函数：调用选择函数
int main()
{
	Select();
	return 0;
}
//选择函数
void Select()
{
	cout << "请输入矩阵的行数:";			//输入行数
	while (1)
	{
		cin >> row;
		if (cin.good() == 0 || row < 1)
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "输入行数错误！请重新输入！" << endl;
			continue;
		}
		break;
	}
	cout << "请输入矩阵的列数:";			//输入列数
	while (1)
	{
		cin >> col;
		if (cin.good() == 0 || col < 1)
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "输入列数错误！请重新输入！" << endl;
			continue;
		}
		break;
	}
	cout << "请输入关系矩阵:" << endl;	//输入关系矩阵
	for (i = 0; i < row; i++)
	{
		cout << endl << "请输入矩阵的第" << i << "行元素(元素以空格分隔):";
		for (j = 0; j < col; j++)
			arr[i][j] = Get_element();
	}
	cout << "输入对应序号选择算法" << endl << "1:自反闭包" << endl << "2:传递闭包" << endl << "3:对称闭包" << endl << "4:退出" << endl;
	cin >> choice;
	switch (choice)
	{
	case 1:
		Zifan(arr);						//调用自反闭包算法函数
		break;
	case 2:
		Chuandi(arr);					//调用传递闭包算法函数
		break;
	case 3:
		Duichen(arr);					//调用对称闭包算法函数
		break;
	case 4:
		Exitprogram();					//退出程序
		break;
	default:
		cout << "选择错误！请重新选择！" << endl; //在输入错误时给出提示
		Select();						//重新选择操作
	}
}
//输出矩阵内容的函数
void Output(int arr[][MAX])
{
	cout << "所求关系矩阵为:" << endl;	//给出输出提示
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
			cout << arr[i][j];			//输出关系矩阵
		cout << endl;
	}
	cout << endl;
}
//计算自反闭包的算法
void Zifan(int arr2[][MAX])
{
	for (i = 0; i < row; i++)
		arr2[i][i] = 1;				//自反闭包的构建：对角线上的元素都设为1
	Output(arr2);					//输出对应的的关系矩阵
	Select();						//重新选择操作
}
//计算对称闭包的算法
void Duichen(int arr2[][MAX])
{
	int arr1[MAX][MAX];
	for (i = 0; i < row; i++)
		for (j = 0; j < col; j++)
			arr1[j][i] = arr2[i][j];				//获取关系矩阵的转置矩阵
	for (i = 0; i < row; i++)
		for (j = 0; j < col; j++)
		{
			arr2[i][j] = arr2[i][j] + arr1[i][j];	//对称闭包的构造：矩阵元素与其转置元素相加
			if (arr2[i][j] > 1)
				arr2[i][j] = 1;						//超过1的元素全部设为1
		}
	Output(arr2);									//输出相应的的关系矩阵
	Select();										//重新选择操作
}
//计算传递闭包的算法
void Chuandi(int arr2[][MAX])
{
	int temparr1[MAX][MAX], temparr2[MAX][MAX], k, h;	//设置两个临时数组temparr1和temparr2，循环变量k和h
	int result_arr[MAX][MAX];							//结果数组，存放结果
	//初始化三个数组
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			temparr2[i][j] = 0;						//temparr2数组赋值为0
			result_arr[i][j] = arr2[i][j];			//result_arr和temparr1数组赋值为原数组内容
			temparr1[i][j] = arr2[i][j];
		}
	}
	//计算结果矩阵内容
	for (h = 0; h < row; h++)
	{
		for (i = 0; i < row; i++)
			for (j = 0; j < col; j++)
				if (temparr1[i][j] == 1)			//如果temparr1里面某个位置为1
				{
					for (k = 0; k < row; k++)		//则遍历原数组的对应行，如果存在1，则将temparr2相应位置置为1
						if (arr2[j][k] == 1)
							temparr2[i][k] = 1;
				}
		for (i = 0; i < row; i++)
			for (j = 0; j < col; j++)
			{
				temparr1[i][j] = temparr2[i][j];
				result_arr[i][j] += temparr2[i][j];		//将result_arr和temparr2矩阵相加
				temparr2[i][j] = 0;
				if (result_arr[i][j] > 1)				//超过1的元素全部设为1
					result_arr[i][j] = 1;
			}
	}
	Output(result_arr);									//输出最终结果矩阵		
	Select(); 
}
//退出程序的函数
void Exitprogram()
{
	cout << "欢迎下次再次使用!" << endl;		//输出欢迎提示
	exit(0);								//退出程序
}