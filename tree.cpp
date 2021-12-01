#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define INFINITE (float)0x3F3FFF
#define Vertexv  int  //顶点数据
char vextex[] = { 'A', 'B', 'C', 'D', 'E', 'F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };//将顶点映射为字母表示
//prim
struct node
{
	Vertexv v;
	float lowestcost;
};//lowestcost表示在prim算法中加入该点的最低权重，v为该代价下所连接的顶点。
int Mincost(vector<node> closedge, int vexCounts)  //返回最小权重边，closedge为各顶点的权重信息
{
	float min = INFINITE;
	int index = -1;
	for (int i = 0; i < vexCounts; i++)
	{
		if (closedge[i].lowestcost < min && closedge[i].lowestcost != 0)//lowestcost=0表示该点已添加，遍历点权重数组，找出最低权重点，返回点索引。
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
	}//初始权重都为最大
	closedge[s].v = s;      //从顶点s开始添加
	closedge[s].lowestcost = 0;//已添加点权重置为0
	for (int i = 0; i < vexCounts; i++)  //添加初始点s后更新权重数组
	{
		if (i != s)
		{
			closedge[i].v = s;
			closedge[i].lowestcost = adjMat[s][i];
		}
	}
	for (int e = 1; e <= vexCounts - 1; e++)  //开始添加，n-1条边时退出
	{
		int k = Mincost(closedge, vexCounts);  //选择最小权重边
		cout << vextex[closedge[k].v] << "-------" << vextex[k] << endl;//加入到最小生成树
		closedge[k].lowestcost = 0; //权重置为0
		for (int i = 0; i < vexCounts; i++)  //更新v中顶点最小权重边信息
		{
			if (adjMat[k][i] < closedge[i].lowestcost)     //每加入一个新点更新权重数组
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
	float cost;  //边的权重
}Edge;  //定义一个边的信息结构
void ReadEdge(vector<vector<float>> adjMat, vector<Edge>& vertexEdge, int vexCounts) //保存图的边权重信息
{
	Edge* temp = NULL;
	for (int i = 0; i < vexCounts; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (adjMat[i][j] != INFINITE) //保存所有非环边的信息加入容器
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
	for (unsigned int i = 0; i < Tree.size(); i++)  //检查u,v分别属于哪颗树
	{
		if (find(Tree[i].begin(), Tree[i].end(), u) != Tree[i].end())
			index_u = i;
		if (find(Tree[i].begin(), Tree[i].end(), v) != Tree[i].end())
			index_v = i;
	}

	if (index_u != index_v)   //u,v不在一颗树上，合并两颗树
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
	ReadEdge(adjMat, vertexEdge, vexCounts);//读取边信息
	sort(vertexEdge.begin(), vertexEdge.end(), compare);//边按从小到大排序
	vector<vector<Vertexv> > Tree(vexCounts); //6棵独立树
	for (int i = 0; i < vexCounts; i++)
	{
		Tree[i].push_back(i);  //初始化6棵独立树的信息
	}
	for (unsigned i = 0; i < vertexEdge.size(); i++)//依次从小到大取最小权重边
	{
		Vertexv u = vertexEdge[i].u;
		Vertexv v = vertexEdge[i].v;
		if (FindTree(u, v, Tree))//检查此边的两个顶点是否在一颗树内
		{
			cout << vextex[u] << "-------" << vextex[v] << endl;//把此边加入到最小生成树中
		}
	}
}
//破圈
void dfs(vector<vector<float>> adjMat, Vertexv v, vector<int>& vis, int vexcounts) {//vis为标志数组，为1表示该点已访问，0表示未访问
	vis[v] = 1;
	for (int i = 0; i < vexcounts; i++) {
		if (!vis[i] && adjMat[v][i] != 0 && adjMat[v][i] != INFINITE) {//遍历每个顶点，如果未访问，且与v点有边，则对该点进行递归操作。
			dfs(adjMat, i, vis, vexcounts);//深度优先递归遍历
		}
	}
}
bool Isconnect(vector<vector<float>> adjMat, int vexcounts) {//依照传入领接矩阵判定是否连通
	vector<int>vis(vexcounts, 0);
	dfs(adjMat, 0, vis, vexcounts);
	if (find(vis.begin(), vis.end(), 0) == vis.end())//查找vis数组是否有0，有则不连通
		return true;
	else return false;

}
void pq(vector<vector<float>> adjMat, int vexCounts) {
	vector<Edge> vertexEdge;
	Edge Edge_temp;
	ReadEdge(adjMat, vertexEdge, vexCounts);//读取边信息
	int n = vertexEdge.size();//n为当前边数
	sort(vertexEdge.begin(), vertexEdge.end(), compare);//边按从小到大排序
	for (int i = vertexEdge.size() - 1; i >= 0; i--) {//从边权最大的边开始删边
		if (n == vexCounts - 1)//当边数等于顶点数减1则完成破圈过程
			break;
		Edge_temp = vertexEdge[i];//保存被删除边的信息
		vertexEdge.erase(vertexEdge.begin() + i);//删边
		adjMat[Edge_temp.u][Edge_temp.v] = adjMat[Edge_temp.v][Edge_temp.u] = INFINITE;//删边后再矩阵中把权值变为最大
		if (Isconnect(adjMat, vexCounts))
			n = n - 1;//连通则删除边，边数减1
		else {//否则操作还原
			vertexEdge.push_back(Edge_temp);
			adjMat[Edge_temp.u][Edge_temp.v] = adjMat[Edge_temp.v][Edge_temp.u] = Edge_temp.cost;
		}
	}
	for (int i = 0; i < n; i++) {//作为破圈操作的边权数组则为最小生成树
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
	cout << "请输入顶点的个数" << endl;
	cin >> vexCounts;
	vector<vector<float>> adjMat(vexCounts);
	for (int i = 0; i < vexCounts; i++)//动态二维数组
	{
		adjMat[i].resize(vexCounts);
	}
	cout << "请输入图的的邻接矩阵,无穷也用0表示" << endl;
	for (int i = 0; i < vexCounts; i++) {
		for (int j = 0; j < vexCounts; j++) {
			cin >> temp;
			adjMat[i][j] = temp;
			if (adjMat[i][j] == 0)
				adjMat[i][j] = INFINITE;
		}
	}//读入数据，并将0置为最大值

	vector<node> closedge(vexCounts);//new 一个动态结构数组
	switch (i)
	{
	case 1:
		cout << "Kruskal :" << endl;
		Kruskal(adjMat, vexCounts);//Kruskal算法
		break;
	case 2:
		cout << "Prim :" << endl;
		MiniSpanTree_Prim(adjMat, closedge, 0, vexCounts); //Prim算法，从顶点0开始.
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