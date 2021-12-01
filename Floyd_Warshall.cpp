#include <iostream>
#include <algorithm>
#include <string>
#include <cstdio>

using namespace std;
#define inf 999999	//定义无穷
int num_of_v;	//节点数

int** Generate_matrix() {	//生成一个num_of_v阶的矩阵空间
	int** matrix;
	matrix = (int**)malloc(num_of_v * sizeof(int*));
	for (int i = 0; i < num_of_v; i++) {
		matrix[i] = (int*)malloc(num_of_v * sizeof(int));
	}
	return matrix;
}
int** F_input() {	//用户输入边权矩阵
	cout << "\n--输入时以-1表示权为无穷--" << endl;
	cout << "输入示例：" << endl;
	cout << "-1 1 2 -1 -1 -1\n-1 -1 1 3 -1 7\n-1 -1 -1 1 2 -1"
		"\n-1 -1 -1 -1 -1 3\n-1 -1 -1 -1 -1 6\n-1 -1 -1 -1 -1 -1" << endl;
	int** weigh = Generate_matrix();
	cout << "\n请输入图的边权矩阵：" << endl;
	for (int i = 0; i < num_of_v; i++)
		for (int j = 0; j < num_of_v; j++) {
			scanf_s("%d", &weigh[i][j]);	//scanf()
			if (weigh[i][j] == -1)
				weigh[i][j] = inf;
		}
	return weigh;
}

void F_print(int** matrix) {	//格式化输出矩阵
	for (int i = 0; i < num_of_v; i++) {
		for (int j = 0; j < num_of_v; j++)
			if (matrix[i][j] >= inf || i==j)
				cout << "inf ";
			else
				cout << " " << matrix[i][j] << "  ";
		cout << endl;
	}
	cout << endl;
}

int** D_multi(int** matrix, int n) {	//求Floyd算法中矩阵D的n次方
	int** result = Generate_matrix();
	for (int i = 0; i < num_of_v; i++)	//给result赋初值
		for (int j = 0; j < num_of_v; j++)
			result[i][j] = matrix[i][j];
	int min_add;	//某一行和某一列相加后的最小值
	int* row = (int*)malloc(num_of_v * sizeof(int));	//用于保存某一行求出的最小值
	for (int m = 1; m < n; m++)	//D的m次方
		for (int i = 0; i < num_of_v; i++) {
			for (int j = 0; j < num_of_v; j++) {
				min_add = result[i][0] + matrix[0][j];
				for (int k = 1; k < num_of_v; k++)
					if (min_add > result[i][k] + matrix[k][j])
						min_add = result[i][k] + matrix[k][j];
				row[j] = min_add;
			}
			for (int a = 0; a < num_of_v; a++)	//将得出的最小值更新到result中
				result[i][a] = row[a];
		}
	return result;
}


int** S_multi(int** Di, int** Dj) {	//求矩阵D各次方的S乘，即最短路径矩阵
	int** result = Generate_matrix();
	for (int i = 0; i < num_of_v; i++)	//将Di和Dj对应位置的最小值给result的相应位置
		for (int j = 0; j < num_of_v; j++)
			result[i][j] = min(Di[i][j], Dj[i][j]);
	return result;
}

void F_main() {	//Floyd算法的主函数
	cout << "---开始Floyd算法---\n"
	<<"请输入图的结点数(阶数)：" << endl;
	cin >> num_of_v;
	int** D = F_input();
	int** S = Generate_matrix();
	for (int i = 0; i < num_of_v; i++)	//给S赋初值为D
		for (int j = 0; j < num_of_v; j++)
			S[i][j] = D[i][j];
	for (int i = 2; i < num_of_v; i++)	//循环求S=S*D^i
		S = S_multi(S, D_multi(D, i));
	cout << "\n图的最短路径为(inf表示无穷)：" << endl;
	F_print(S);
	system("pause");
}

void Floyd_Warshall(int** weigh) {	//Floyd_Warshall算法
	for (int k = 0; k < num_of_v; k++) {   //k为从i到j的中间节点
		for (int i = 0; i < num_of_v; i++) {
			for (int j = 0; j < num_of_v; j++) {
				if (weigh[i][k] != inf && weigh[k][j] != inf)  //如果i到k或者k到j有一条边的权重为无穷，则循环下一个k
					if (weigh[i][j] == inf || weigh[i][j] > weigh[i][k] + weigh[k][j])    //此时i到k加上k到j的权重为有限值
						weigh[i][j] = weigh[i][k] + weigh[k][j];	//如果i到j的权为无穷，或者大于前者，则更新权重
			}
		}
	}
}

void FW_main() {	//Floyd_Warshall算法的主函数
	cout << "---开始Floyd-Warshall算法---\n"
	<< "请输入图的结点数(阶数)：" << endl;
	cin >> num_of_v;
	int** weigh = F_input();
	Floyd_Warshall(weigh);
	cout<<"\n图的最短路径为(inf表示无穷)：" << endl;
	F_print(weigh);
	system("pause");
}
