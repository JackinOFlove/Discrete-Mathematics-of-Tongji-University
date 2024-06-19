#include <iostream>
#include <cstring>
#include <climits>
using namespace std;
//��������Ľ�׳�Ա�֤
int Get_int(int Min = INT_MAX, int Max = INT_MIN, string errortips = "")
{
	int retint;
	while (1)
	{
		cin >> retint;
		if (cin.good() == 0 || retint < Min || retint > Max)
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << errortips << endl;
			continue;
		}
		break;
	}
	return retint;
}
//���������ڵ���
class Treenode
{
public:
	int weight;					//Ȩ��
	Treenode* left;				//��ָ��
	Treenode* right;			//��ָ��
	Treenode* parent;			//ָ�򸸽ڵ��ָ��
	Treenode(int Number, Treenode* Parent = NULL, Treenode* Left = NULL, Treenode* Right = NULL)
	{ 
		weight = Number; 
		left = Left;
		right = Right;
		parent = Parent;
	}
};
//����������
class Huffmantree
{
public:
	Huffmantree(int* Array,int number);			//���캯��
	~Huffmantree() {};							//Ĭ����������
	void Printcode(Treenode* node);				//��ӡͨ����
	Treenode* root;
	Treenode** leaf;
	int number;
};
//���캯��
Huffmantree::Huffmantree(int* Array,int number)
{
	root = NULL;
	this->number = number;
	leaf = new Treenode * [number];					//ΪҶ�����鶯̬����ռ�
	for (int i = 0; i < number; i++)
		leaf[i] = new Treenode(Array[i]);
	for (int i = 0; i < number - 1; i++)			//������Ȩ����С��Ҷ�ӽڵ�
	{
		int min1 = INT_MAX, min2 = INT_MAX;
		int index1 = -1, index2 = -1;
		for (int j = 0; j < number; j++)
		{
			if (leaf[j] != NULL)
			{
				if (leaf[j]->weight < min1)			//�ҵ���СȨֵ
				{
					min2 = min1;
					index2 = index1;
					min1 = leaf[j]->weight;
					index1 = j;
				}
				else if (leaf[j]->weight < min2)	//�ҵ��ڶ�С��Ȩֵ
				{
					min2 = leaf[j]->weight;
					index2 = j;
				}
			}
		}
		Treenode* newnode = new Treenode(min1 + min2, NULL, leaf[index1], leaf[index2]);	//�����µĹ����������
		leaf[index1]->parent = newnode;				//ָ�򸸽ڵ�
		leaf[index2]->parent = newnode;				//ָ�򸸽ڵ�
		leaf[index1] = newnode;						//ʹ1�������Ϊ�½ڵ㣨���ڵ㣩
		leaf[index2] = NULL;						//����һ��ΪNULL
	}
	for (int i = 0; i < number; i++)				//���Ե����������㶼ΪNULL��Ψһһ����ΪNULL���Ǹ����
	{
		if (leaf[i] != NULL)
		{
			root = leaf[i];
			break;
		}
	}
}
//��ӡͨ�ű���
void Huffmantree::Printcode(Treenode* node)
{
	if (node == NULL)
		return;
	if (node->left == NULL && node->right == NULL)
	{
		cout << node->weight << "��\t";
		Treenode* current = node;
		string code = "";
		while (current->parent != NULL)				//���������Ҹ��ڵ�
		{
			if (current->parent->left == current)
				code = "0" + code;					//�������ڵ����丸�ڵ�����ӣ���ӡ�0��
			else
				code = "1" + code;					//�������ڵ����丸�ڵ���Һ��ӣ���ӡ�1��
			current = current->parent;
		}
		code = "0" + code;
		cout << code << endl;
		return;
	}
	else
	{
		Printcode(node->left);
		Printcode(node->right);
	}
}
int main()
{
	cout << "������ڵ������";					
	int number = Get_int(1, INT_MAX, "����������������룡");		//����ڵ����
	int* Array = new int[number];
	cout << "������ڵ㣺";
	for (int i = 0; i < number; i++)
		Array[i] = Get_int(1, INT_MAX, "����������������룡");		//����ڵ�Ȩ��
	Huffmantree Coding_tree(Array, number);							//ʵ������������Coding_tree
	Coding_tree.Printcode(Coding_tree.root);
	delete[] Array;
	return 0;
}