#include <iostream>
#define MAXWEIGHT INT_MAX
using namespace std;
//�����ȷ�Ľ�����ͱ������д���Ľ�׳�Լ��飩
void Get_node_edge_numbers(int& Vertices_num, int& Edges_num)
{
	while (1)
	{
		cin >> Vertices_num >> Edges_num;
		//�������������������������󡢽ڵ���С��2������С��1���������ڽڵ���*���ڵ���-1����
		if (cin.good() == 0 || Vertices_num < 2 || Edges_num < 1 || Edges_num > Vertices_num * (Vertices_num - 1) / 2)
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "����������������룡" << endl;
			continue;
		}
		break;
	}
}
//�߽����
class Edgenode
{
public:
	char start;				//�ߵ���ʼ����
	char end;				//�ߵ���ֹ����
	int weight;				//�ߵ�Ȩ��
	Edgenode() { start = end = ' '; weight = 0; }
};
//ͼ��
class Graph
{
public:
	int Vertices_num = 0;							//ͼ�Ķ�����
	int Edges_num = 0;								//ͼ�ı���
	int* Vertices = NULL;							//��������
	Edgenode* Edges = NULL;							//�߽������
	int** Matrix = NULL;							//�ڽӾ�������
	Graph();										//���캯��
	~Graph() {};									//Ĭ����������
	void Create_tree_by_Kruskal();					//Kruskal�㷨����С������
	int FindUFSets(int* UFSets, int node);			//���ҽڵ����ڵļ���
	void Union(int* UFSets, int node1, int node2);	//�ϲ���������
};
//���캯����������ϵ����
Graph::Graph()
{
	//���붥����Ŀ�ͱ���
	cout << "����������ͼ�Ķ�����Ŀ�ͱߵ���Ŀ(�Կո�ָ�����������������0����)��";
	Get_node_edge_numbers(Vertices_num, Edges_num);
	//��ʼ����������
	Vertices = new int[Vertices_num];
	for (int i = 0; i < Vertices_num; i++)
		Vertices[i] = i;
	//��ʼ��������
	Edges = new Edgenode [Edges_num];
	//��ʼ���ڽӾ��󣨶Խ��ߵ�ȨֵΪ0��������Ϊ���Ȩֵ��
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
	//����ߵ���㡢�յ��Ȩ��
	cout << "�����������ߵĽڵ�����Լ����ǵ�Ȩֵ(�Կո�ָ�������)��" << endl;
	for (int i = 0; i < Edges_num; i++)
	{
		int Startnode, Endnode, Edgeweight;
		cin >> Startnode >> Endnode >> Edgeweight;
		cin.ignore(1024, '\n');
		//����Ĵ��뽡׳�Լ���
		if (cin.good() == 0 || Startnode < 1 || Startnode > Vertices_num || Endnode < 1 || Endnode>Vertices_num)
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "����������������룡" << endl;
			i--;
			continue;
		}
		Edges[i].start = Startnode;
		Edges[i].end = Endnode;
		Edges[i].weight = Edgeweight;
		//����Ҫע�����λ�ú���ŵĹ�ϵ������λ�õ��ڽڵ����-1
		Matrix[Startnode - 1][Endnode - 1] = Matrix[Endnode - 1][Startnode - 1] = Edgeweight;
	}
}
//����ĳ���ڵ����ڵļ���
int Graph::FindUFSets(int* UFSets, int node)
{
	//ѭ�����ϲ��Ҹ��ڵ㣨���ȣ�
	while (UFSets[node] != node)
		node = UFSets[node];
	return node;
}
//�ϲ�����������ڵļ���
void Graph::Union(int* UFSets, int node1, int node2)
{
	int Parent1 = FindUFSets(UFSets, node1);
	int Parent2 = FindUFSets(UFSets, node2);
	//node1������ָ��node2�����ȣ��Ӷ�����������ϵĺϲ�
	UFSets[Parent1] = Parent2;						
}
//����Kruskal�����С����������ӡ
void Graph::Create_tree_by_Kruskal()
{
	cout << "------Kruskal�㷨����С������------" << endl;
	//���ߵ�Ȩ�ذ�С��������
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
	//��ʼ�����鼯
	int* UFSets = new int[Vertices_num];
	for (int i = 0; i < Vertices_num; i++)
		UFSets[i] = i;
	int Mincost = 0;
	for (int i = 0; i < Edges_num; i++)
	{
		int Startnode = Edges[i].start - 1;
		int Endnode = Edges[i].end - 1;
		int Edgeweight = Edges[i].weight;
		//��������ڵ㲻����ͬһ������
		if (FindUFSets(UFSets, Startnode) != FindUFSets(UFSets, Endnode))
		{
			//����滮����С�������ڣ�ͬʱ���ϸ�·���ĺķ�
			Union(UFSets, Startnode, Endnode);
			Mincost += Edges[i].weight;
			cout << "\t" << "��С�ķ��ǣ�" << Startnode + 1 << "��" << Endnode + 1 << endl;
		}
	}
	cout << "\t" << "��С�ܺķ�Ϊ��" << Mincost << endl;
	//��̬�ͷſռ䣬��������ڴ���˷�
	delete[] UFSets;
}
//��������ʵ��
int main()
{
	Graph City_road;							//ʵ����Graph City_road
	City_road.Create_tree_by_Kruskal();
	return 0;
}