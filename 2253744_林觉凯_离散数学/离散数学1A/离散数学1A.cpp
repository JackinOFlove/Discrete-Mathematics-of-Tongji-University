#include <iostream>
using namespace std;
//��ӡ��ӭ���溯��
void Print_Welcome()
{
    cout << "***************************************" << endl;
    cout << "**                                   **" << endl;
    cout << "**        ��ӭ�����߼��������       **" << endl;
    cout << "**                                   **" << endl;
    cout << "***************************************" << endl << endl;
}
//���ѡ������Ӧ��ѡ��ֵ�����������˴��������ƴ���Ľ�׳�ԣ�
int Get_Int(char key)
{
    int Ret_Int = 0;
    while(1)
    {
        cout << endl <<  "  ������" << key << "��ֵ��0��1��,�Իس�����:";
        cin >> Ret_Int;
        //����Ľ�׳���жϣ�����Ĳ���0��1��������������ʹ���
        if (Ret_Int != 0 && Ret_Int != 1 || cin.good() == 0)
        {
            cout << endl <<  "  " << key << "��ֵ��������,����������!" << endl;
            cin.clear();
            cin.ignore(1024, '\n');
            continue;
        }
        break;
    }
    return Ret_Int;
}
//�ж��Ƿ����ʹ��������������������˴��������ƴ���Ľ�׳�ԣ�
bool Is_Continue()
{
    bool choice;
    char keydown;
    while (1)
    {
        cout << endl <<  "�Ƿ��������y/n��:";
        cin >> keydown;
        //ֻ������y����n�Ĵ��뽡׳�Լ���
        if (cin.good() == 0 || keydown != 'y' && keydown != 'n')   
        {
            cout << "�������,����������!" << endl;
            cin.clear();
            cin.ignore(1024, '\n');
            continue;
        }
        if (keydown == 'y')
            choice = true;
        else
        {
            cout<<"��ӭ�´��ٴ�ʹ��!"<<endl;
            choice = false;
        }
        return choice;
    }
}
//����������ɳ��������ܹ�
int main()
{
    Print_Welcome();
    //��һ������a���洢���յĽ��
    int a[4];
    int P, Q;
    while (1)
    {
        P = Get_Int('P');
        Q = Get_Int('Q');
        a[0] = P && Q;                               //��ȡ
        a[1] = P || Q;                               //��ȡ
        a[2] = (!P) || Q;                            //����
        a[3] = ((!P) || Q) && ((!Q) || P);           //˫����
        cout << "\n\n  ��ȡ:\n       P/\\Q = " << a[0] << endl; 
        cout << "  ��ȡ:\n       P\\/Q = " << a[1] << endl;
        cout << "  ����:\n       P->Q = " << a[2] << endl;
        cout << "  ˫����:\n       P<->Q = " << a[3] << endl;
        if (!Is_Continue())                         //�ж��Ƿ����
            break;
    }
    return 0;
}