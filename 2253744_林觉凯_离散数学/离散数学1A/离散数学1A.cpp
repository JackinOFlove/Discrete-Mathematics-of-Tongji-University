#include <iostream>
using namespace std;
//打印欢迎界面函数
void Print_Welcome()
{
    cout << "***************************************" << endl;
    cout << "**                                   **" << endl;
    cout << "**        欢迎进入逻辑运算软件       **" << endl;
    cout << "**                                   **" << endl;
    cout << "***************************************" << endl << endl;
}
//获得选项所对应的选项值函数（进行了错误处理，完善代码的健壮性）
int Get_Int(char key)
{
    int Ret_Int = 0;
    while(1)
    {
        cout << endl <<  "  请输入" << key << "的值（0或1）,以回车结束:";
        cin >> Ret_Int;
        //代码的健壮性判断：输入的不是0或1、输入的数据类型错误
        if (Ret_Int != 0 && Ret_Int != 1 || cin.good() == 0)
        {
            cout << endl <<  "  " << key << "的值输入有误,请重新输入!" << endl;
            cin.clear();
            cin.ignore(1024, '\n');
            continue;
        }
        break;
    }
    return Ret_Int;
}
//判断是否继续使用运算软件函数（进行了错误处理，完善代码的健壮性）
bool Is_Continue()
{
    bool choice;
    char keydown;
    while (1)
    {
        cout << endl <<  "是否继续？（y/n）:";
        cin >> keydown;
        //只能输入y或者n的代码健壮性检验
        if (cin.good() == 0 || keydown != 'y' && keydown != 'n')   
        {
            cout << "输入错误,请重新输入!" << endl;
            cin.clear();
            cin.ignore(1024, '\n');
            continue;
        }
        if (keydown == 'y')
            choice = true;
        else
        {
            cout<<"欢迎下次再次使用!"<<endl;
            choice = false;
        }
        return choice;
    }
}
//主函数，完成程序的主题架构
int main()
{
    Print_Welcome();
    //用一个数组a来存储最终的结果
    int a[4];
    int P, Q;
    while (1)
    {
        P = Get_Int('P');
        Q = Get_Int('Q');
        a[0] = P && Q;                               //合取
        a[1] = P || Q;                               //析取
        a[2] = (!P) || Q;                            //条件
        a[3] = ((!P) || Q) && ((!Q) || P);           //双条件
        cout << "\n\n  合取:\n       P/\\Q = " << a[0] << endl; 
        cout << "  析取:\n       P\\/Q = " << a[1] << endl;
        cout << "  条件:\n       P->Q = " << a[2] << endl;
        cout << "  双条件:\n       P<->Q = " << a[3] << endl;
        if (!Is_Continue())                         //判断是否继续
            break;
    }
    return 0;
}