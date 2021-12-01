#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define INFINITE (float)0x3F3FFF
#define Vertexv  int  //��������
char vextex[] = { 'A', 'B', 'C', 'D', 'E', 'F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };//������ӳ��Ϊ��ĸ��ʾ
//prim
struct node
{
	Vertexv v;
	float lowestcost;
};//lowestcost��ʾ��prim�㷨�м���õ�����Ȩ�أ�vΪ�ô����������ӵĶ��㡣
int Mincost(vector<node> closedge, int vexCounts)  //������СȨ�رߣ�closedgeΪ�������Ȩ����Ϣ
{
	float min = INFINITE;
	int index = -1;
	for (int i = 0; i < vexCounts; i++)
	{
		if (closedge[i].lowestcost < min && closedge[i].lowestcost != 0)//lowestcost=0��ʾ�õ�����ӣ�������Ȩ�����飬�ҳ����Ȩ�ص㣬���ص�������
		{
			min = closedge[i].lowestcost;
			index = i;
		}
	}
	return index;
}
void MiniSpanTree_Prim(vector<vector<float>> adjMat, vector<node> closedge, Vertexv s, int vexCounts)
{
	for (int i = 0; i < vexCounts; i++)
	{
		closedge[i].lowestcost = INFINITE;
	}//��ʼȨ�ض�Ϊ���
	closedge[s].v = s;      //�Ӷ���s��ʼ���
	closedge[s].lowestcost = 0;//����ӵ�Ȩ����Ϊ0
	for (int i = 0; i < vexCounts; i++)  //��ӳ�ʼ��s�����Ȩ������
	{
		if (i != s)
		{
			closedge[i].v = s;
			closedge[i].lowestcost = adjMat[s][i];
		}
	}
	for (int e = 1; e <= vexCounts - 1; e++)  //��ʼ��ӣ�n-1����ʱ�˳�
	{
		int k = Mincost(closedge, vexCounts);  //ѡ����СȨ�ر�
		cout << vextex[closedge[k].v] << "-------" << vextex[k] << endl;//���뵽��С������
		closedge[k].lowestcost = 0; //Ȩ����Ϊ0
		for (int i = 0; i < vexCounts; i++)  //����v�ж�����СȨ�ر���Ϣ
		{
			if (adjMat[k][i] < closedge[i].lowestcost)     //ÿ����һ���µ����Ȩ������
			{
				closedge[i].v = k;
				closedge[i].lowestcost = adjMat[k][i];
			}
		}
	}
}
//kruskal
typedef struct
{
	Vertexv u;
	Vertexv v;
	float cost;  //�ߵ�Ȩ��
}Edge;  //����һ���ߵ���Ϣ�ṹ
void ReadEdge(vector<vector<float>> adjMat, vector<Edge>& vertexEdge, int vexCounts) //����ͼ�ı�Ȩ����Ϣ
{
	Edge* temp = NULL;
	for (int i = 0; i < vexCounts; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (adjMat[i][j] != INFINITE) //�������зǻ��ߵ���Ϣ��������
			{
				temp = new Edge;
				temp->u = i;
				temp->v = j;
				temp->cost = adjMat[i][j];
				vertexEdge.push_back(*temp);
				free(temp);
			}
		}
	}
}
bool compare(Edge  A, Edge  B)
{
	return A.cost < B.cost;
}
bool FindTree(Vertexv u, Vertexv v, vector<vector<Vertexv> >& Tree)
{
	int index_u = INFINITE;
	int index_v = INFINITE;
	for (unsigned int i = 0; i < Tree.size(); i++)  //���u,v�ֱ������Ŀ���
	{
		if (find(Tree[i].begin(), Tree[i].end(), u) != Tree[i].end())
			index_u = i;
		if (find(Tree[i].begin(), Tree[i].end(), v) != Tree[i].end())
			index_v = i;
	}

	if (index_u != index_v)   //u,v����һ�����ϣ��ϲ�������
	{
		for (unsigned i = 0; i < Tree[index_v].size(); i++)
		{
			Tree[index_u].push_back(Tree[index_v][i]);
		}
		Tree[index_v].clear();
		return true;
	}
	return false;
}
void Kruskal(vector<vector<float>> adjMat, int vexCounts)
{
	vector<Edge> vertexEdge;
	ReadEdge(adjMat, vertexEdge, vexCounts);//��ȡ����Ϣ
	sort(vertexEdge.begin(), vertexEdge.end(), compare);//�߰���С��������
	vector<vector<Vertexv> > Tree(vexCounts); //6�ö�����
	for (int i = 0; i < vexCounts; i++)
	{
		Tree[i].push_back(i);  //��ʼ��6�ö���������Ϣ
	}
	for (unsigned i = 0; i < vertexEdge.size(); i++)//���δ�С����ȡ��СȨ�ر�
	{
		Vertexv u = vertexEdge[i].u;
		Vertexv v = vertexEdge[i].v;
		if (FindTree(u, v, Tree))//���˱ߵ����������Ƿ���һ������
		{
			cout << vextex[u] << "-------" << vextex[v] << endl;//�Ѵ˱߼��뵽��С��������
		}
	}
}
//��Ȧ
void dfs(vector<vector<float>> adjMat, Vertexv v, vector<int>& vis, int vexcounts) {//visΪ��־���飬Ϊ1��ʾ�õ��ѷ��ʣ�0��ʾδ����
	vis[v] = 1;
	for (int i = 0; i < vexcounts; i++) {
		if (!vis[i] && adjMat[v][i] != 0 && adjMat[v][i] != INFINITE) {//����ÿ�����㣬���δ���ʣ�����v���бߣ���Ըõ���еݹ������
			dfs(adjMat, i, vis, vexcounts);//������ȵݹ����
		}
	}
}
bool Isconnect(vector<vector<float>> adjMat, int vexcounts) {//���մ�����Ӿ����ж��Ƿ���ͨ
	vector<int>vis(vexcounts, 0);
	dfs(adjMat, 0, vis, vexcounts);
	if (find(vis.begin(), vis.end(), 0) == vis.end())//����vis�����Ƿ���0��������ͨ
		return true;
	else return false;

}
void pq(vector<vector<float>> adjMat, int vexCounts) {
	vector<Edge> vertexEdge;
	Edge Edge_temp;
	ReadEdge(adjMat, vertexEdge, vexCounts);//��ȡ����Ϣ
	int n = vertexEdge.size();//nΪ��ǰ����
	sort(vertexEdge.begin(), vertexEdge.end(), compare);//�߰���С��������
	for (int i = vertexEdge.size() - 1; i >= 0; i--) {//�ӱ�Ȩ���ı߿�ʼɾ��
		if (n == vexCounts - 1)//���������ڶ�������1�������Ȧ����
			break;
		Edge_temp = vertexEdge[i];//���汻ɾ���ߵ���Ϣ
		vertexEdge.erase(vertexEdge.begin() + i);//ɾ��
		adjMat[Edge_temp.u][Edge_temp.v] = adjMat[Edge_temp.v][Edge_temp.u] = INFINITE;//ɾ�ߺ��پ����а�Ȩֵ��Ϊ���
		if (Isconnect(adjMat, vexCounts))
			n = n - 1;//��ͨ��ɾ���ߣ�������1
		else {//���������ԭ
			vertexEdge.push_back(Edge_temp);
			adjMat[Edge_temp.u][Edge_temp.v] = adjMat[Edge_temp.v][Edge_temp.u] = Edge_temp.cost;
		}
	}
	for (int i = 0; i < n; i++) {//��Ϊ��Ȧ�����ı�Ȩ������Ϊ��С������
		cout << vextex[vertexEdge[i].u] << "-------" << vextex[vertexEdge[i].v] << endl;
	}
}
int ST(int i)
{
	int vexCounts;
	float temp;
	cout << "0 5 6.1 9 8.5" << endl;
	cout << "5 0 6 7 12" << endl;
	cout << "6.1 6 0 10 8" << endl;
	cout << "9 7 10 0 6.4" << endl;
	cout << "8.5 12 8 6.4 0" << endl;
	cout << "�����붥��ĸ���" << endl;
	cin >> vexCounts;
	vector<vector<float>> adjMat(vexCounts);
	for (int i = 0; i < vexCounts; i++)//��̬��ά����
	{
		adjMat[i].resize(vexCounts);
	}
	cout << "������ͼ�ĵ��ڽӾ���,����Ҳ��0��ʾ" << endl;
	for (int i = 0; i < vexCounts; i++) {
		for (int j = 0; j < vexCounts; j++) {
			cin >> temp;
			adjMat[i][j] = temp;
			if (adjMat[i][j] == 0)
				adjMat[i][j] = INFINITE;
		}
	}//�������ݣ�����0��Ϊ���ֵ

	vector<node> closedge(vexCounts);//new һ����̬�ṹ����
	switch (i)
	{
	case 1:
		cout << "Kruskal :" << endl;
		Kruskal(adjMat, vexCounts);//Kruskal�㷨
		break;
	case 2:
		cout << "Prim :" << endl;
		MiniSpanTree_Prim(adjMat, closedge, 0, vexCounts); //Prim�㷨���Ӷ���0��ʼ.
		break;
	case 3:
		cout << "Broke Circle :" << endl;
		pq(adjMat, vexCounts);
		break;
	default:
		break;
	}
	system("pause");
	return 0;
}