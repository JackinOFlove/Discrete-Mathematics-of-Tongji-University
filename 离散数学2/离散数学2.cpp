#include<iostream>
using namespace std;
int main()
{
	//展示每一个命题的内容和相对应的命题变元:
	cout << "命题如下：" << endl;
	cout << "(1)营业员A或B偷了手表" << endl;
	cout << "(2)若A作案，则作案不在营业时间" << endl;
	cout << "(3)若B提供的证据正确，则货柜未上锁" << endl;
	cout << "(4)若B提供的证据不正确，则作案发生在营业时间" << endl;
	cout << "(5)货柜上了锁" << endl;
	//将命题可符号化:
	cout << endl << "用命题变元表示如下：" << endl;
	cout << "A : 营业员A偷了手表" << endl;
	cout << "B : 营业员B偷了手表" << endl;
	cout << "C : 作案不在营业时间" << endl;
	cout << "D : B提供的证据正确" << endl;
	cout << "E : 货柜未上锁" << endl;
	//将命题转化为符号化语言:
	cout << endl << "则上面的命题可符号化：" << endl;
	cout << "(1)营业员A或B偷了手表\t\t\t\t->\tA||B " << endl;
	cout << "(2)若A作案，则作案不在营业时间\t\t\t->\t!A||C" << endl;
	cout << "(3)若B提供的证据正确，则货柜未上锁\t\t->\t!D||E" << endl;
	cout << "(4)若B提供的证据不正确，则作案发生在营业时间\t->\tD||!C" << endl;
	cout << "(5)货柜上了锁\t\t\t\t\t->\t!E" << endl << endl;
	//循环遍历结果
	int A, B, C, D, E;
	for (A = 0; A <= 1; A++)
	{
		for (B = 0; B <= 1; B++)
		{
			for (C = 0; C <= 1; C++)
			{
				for (D = 0; D <= 1; D++)
				{
					for (E = 0; E <= 1; E++)
					{
						if ((A || B) && (!A || C) && (!D || E) && (D || !C) && !E)
						{
							cout << "A = " << A <<","<< "B = " << B << endl;
							cout << "根据以上推理：";
							A ? cout << "A偷了手表" : cout << "A没有偷手表";  
							cout << ",";
							B ? cout << "B偷了手表" : cout << "B没有偷手表"; 
							cout << endl;
							//如果A==1，则说明是A偷了手表，反之则说明是B偷了手表
						}
					}
				}
			}
		}
	}
	return 0;
}