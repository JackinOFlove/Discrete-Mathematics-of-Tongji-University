#include <iostream>
#define MAXWEIGHT INT_MAX
using namespace std;
//获得正确的结点数和边数（有代码的健壮性检验）
void Get_node_edge_numbers(int& Vertices_num, int& Edges_num)
{
	while (1)
	{
		cin >> Vertices_num >> Edges_num;
		//输入错误处理：（数据类型输入错误、节点数小于2、边数小于1、边数大于节点数*（节点数-1））
		if (cin.good() == 0 || Vertices_num < 2 || Edges_num < 1 || Edges_num > Vertices_num * (Vertices_num - 1) / 2)
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "输入错误！请重新输入！" << endl;
			continue;
		}
		break;
	}
}
//边结点类
class Edgenode
{
public:
	char start;				//边的起始顶点
	char end;				//边的终止顶点
	int weight;				//边的权重
	Edgenode() { start = end = ' '; weight = 0; }
};
//图类
class Graph
{
public:
	int Vertices_num = 0;							//图的顶点数
	int Edges_num = 0;								//图的边数
	int* Vertices = NULL;							//顶点数组
	Edgenode* Edges = NULL;							//边结点数组
	int** Matrix = NULL;							//邻接矩阵数组
	Graph();										//构造函数
	~Graph() {};									//默认析构函数
	void Create_tree_by_Kruskal();					//Kruskal算法求最小生成树
	int FindUFSets(int* UFSets, int node);			//查找节点所在的集合
	void Union(int* UFSets, int node1, int node2);	//合并两个集合
};
//构造函数：建立关系矩阵
Graph::Graph()
{
	//输入顶点数目和边数
	cout << "请输入所求图的顶点数目和边的数目(以空格分隔各个数，输入两个0结束)：";
	Get_node_edge_numbers(Vertices_num, Edges_num);
	//初始化顶点数组
	Vertices = new int[Vertices_num];
	for (int i = 0; i < Vertices_num; i++)
		Vertices[i] = i;
	//初始化边数组
	Edges = new Edgenode [Edges_num];
	//初始化邻接矩阵（对角线的权值为0，其他都为最大权值）
	Matrix = new int*[Vertices_num];
	for (int i = 0; i < Vertices_num; i++)
	{
		Matrix[i] = new int[Vertices_num];
		for (int j = 0; j < Vertices_num; j++)
		{
			if (i == j)
				Matrix[i][j] = 0;
			else
				Matrix[i][j] = MAXWEIGHT;
		}
	}
	//输入边的起点、终点和权重
	cout << "请输入两条边的节点序号以及它们的权值(以空格分隔各个数)：" << endl;
	for (int i = 0; i < Edges_num; i++)
	{
		int Startnode, Endnode, Edgeweight;
		cin >> Startnode >> Endnode >> Edgeweight;
		cin.ignore(1024, '\n');
		//输入的代码健壮性检验
		if (cin.good() == 0 || Startnode < 1 || Startnode > Vertices_num || Endnode < 1 || Endnode>Vertices_num)
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "输入错误！请重新输入！" << endl;
			i--;
			continue;
		}
		Edges[i].start = Startnode;
		Edges[i].end = Endnode;
		Edges[i].weight = Edgeweight;
		//这里要注意矩阵位置和序号的关系，矩阵位置等于节点序号-1
		Matrix[Startnode - 1][Endnode - 1] = Matrix[Endnode - 1][Startnode - 1] = Edgeweight;
	}
}
//查找某个节点属于的集合
int Graph::FindUFSets(int* UFSets, int node)
{
	//循环向上查找父节点（祖先）
	while (UFSets[node] != node)
		node = UFSets[node];
	return node;
}
//合并两个结点所在的集合
void Graph::Union(int* UFSets, int node1, int node2)
{
	int Parent1 = FindUFSets(UFSets, node1);
	int Parent2 = FindUFSets(UFSets, node2);
	//node1的祖先指向node2的祖先，从而完成两个集合的合并
	UFSets[Parent1] = Parent2;						
}
//按照Kruskal求出最小生成树并打印
void Graph::Create_tree_by_Kruskal()
{
	cout << "------Kruskal算法求最小生成树------" << endl;
	//将边的权重按小到大排序
	for (int i = 0; i < Edges_num; i++)
	{
		for (int j = i + 1; j < Edges_num; j++)
		{
			if (Edges[i].weight > Edges[j].weight)
			{
				int temp_start = Edges[i].start;
				Edges[i].start = Edges[j].start;
				Edges[j].start = temp_start;
				int temp_end = Edges[i].end;
				Edges[i].end = Edges[j].end;
				Edges[j].end = temp_end;
				int temp_weight = Edges[i].weight;
				Edges[i].weight = Edges[j].weight;
				Edges[j].weight = temp_weight;
			}
		}
	}
	//初始化并查集
	int* UFSets = new int[Vertices_num];
	for (int i = 0; i < Vertices_num; i++)
		UFSets[i] = i;
	int Mincost = 0;
	for (int i = 0; i < Edges_num; i++)
	{
		int Startnode = Edges[i].start - 1;
		int Endnode = Edges[i].end - 1;
		int Edgeweight = Edges[i].weight;
		//如果两个节点不属于同一个集合
		if (FindUFSets(UFSets, Startnode) != FindUFSets(UFSets, Endnode))
		{
			//将其规划入最小生成树内，同时加上该路径的耗费
			Union(UFSets, Startnode, Endnode);
			Mincost += Edges[i].weight;
			cout << "\t" << "最小耗费是：" << Startnode + 1 << "和" << Endnode + 1 << endl;
		}
	}
	cout << "\t" << "最小总耗费为：" << Mincost << endl;
	//动态释放空间，以免造成内存的浪费
	delete[] UFSets;
}
//主函数的实现
int main()
{
	Graph City_road;							//实例化Graph City_road
	City_road.Create_tree_by_Kruskal();
	return 0;
}