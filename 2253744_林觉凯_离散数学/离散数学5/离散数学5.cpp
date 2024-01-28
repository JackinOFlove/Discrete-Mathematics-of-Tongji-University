#include <iostream>
#include <cstring>
#include <climits>
using namespace std;
//代码输入的健壮性保证
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
//哈夫曼树节点类
class Treenode
{
public:
	int weight;					//权重
	Treenode* left;				//左指针
	Treenode* right;			//右指针
	Treenode* parent;			//指向父节点的指针
	Treenode(int Number, Treenode* Parent = NULL, Treenode* Left = NULL, Treenode* Right = NULL)
	{ 
		weight = Number; 
		left = Left;
		right = Right;
		parent = Parent;
	}
};
//哈夫曼树类
class Huffmantree
{
public:
	Huffmantree(int* Array,int number);			//构造函数
	~Huffmantree() {};							//默认析构函数
	void Printcode(Treenode* node);				//打印通信码
	Treenode* root;
	Treenode** leaf;
	int number;
};
//构造函数
Huffmantree::Huffmantree(int* Array,int number)
{
	root = NULL;
	this->number = number;
	leaf = new Treenode * [number];					//为叶子数组动态分配空间
	for (int i = 0; i < number; i++)
		leaf[i] = new Treenode(Array[i]);
	for (int i = 0; i < number - 1; i++)			//找两个权重最小的叶子节点
	{
		int min1 = INT_MAX, min2 = INT_MAX;
		int index1 = -1, index2 = -1;
		for (int j = 0; j < number; j++)
		{
			if (leaf[j] != NULL)
			{
				if (leaf[j]->weight < min1)			//找到最小权值
				{
					min2 = min1;
					index2 = index1;
					min1 = leaf[j]->weight;
					index1 = j;
				}
				else if (leaf[j]->weight < min2)	//找到第二小的权值
				{
					min2 = leaf[j]->weight;
					index2 = j;
				}
			}
		}
		Treenode* newnode = new Treenode(min1 + min2, NULL, leaf[index1], leaf[index2]);	//构造新的哈夫曼树结点
		leaf[index1]->parent = newnode;				//指向父节点
		leaf[index2]->parent = newnode;				//指向父节点
		leaf[index1] = newnode;						//使1结点重置为新节点（父节点）
		leaf[index2] = NULL;						//另外一个为NULL
	}
	for (int i = 0; i < number; i++)				//所以到最后其他结点都为NULL，唯一一个不为NULL的是根结点
	{
		if (leaf[i] != NULL)
		{
			root = leaf[i];
			break;
		}
	}
}
//打印通信编码
void Huffmantree::Printcode(Treenode* node)
{
	if (node == NULL)
		return;
	if (node->left == NULL && node->right == NULL)
	{
		cout << node->weight << "：\t";
		Treenode* current = node;
		string code = "";
		while (current->parent != NULL)				//不断向上找父节点
		{
			if (current->parent->left == current)
				code = "0" + code;					//如果这个节点是其父节点的左孩子，则加“0”
			else
				code = "1" + code;					//如果这个节点是其父节点的右孩子，则加“1”
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
	cout << "请输入节点个数：";					
	int number = Get_int(1, INT_MAX, "输入错误！请重新输入！");		//输入节点个数
	int* Array = new int[number];
	cout << "请输入节点：";
	for (int i = 0; i < number; i++)
		Array[i] = Get_int(1, INT_MAX, "输入错误！请重新输入！");		//输入节点权重
	Huffmantree Coding_tree(Array, number);							//实例化哈夫曼树Coding_tree
	Coding_tree.Printcode(Coding_tree.root);
	delete[] Array;
	return 0;
}