#include <iostream>
#include <algorithm>
#include <string>
#include <cstdio>

using namespace std;
#define inf 999999	//��������
int num_of_v;	//�ڵ���

int** Generate_matrix() {	//����һ��num_of_v�׵ľ���ռ�
	int** matrix;
	matrix = (int**)malloc(num_of_v * sizeof(int*));
	for (int i = 0; i < num_of_v; i++) {
		matrix[i] = (int*)malloc(num_of_v * sizeof(int));
	}
	return matrix;
}
int** F_input() {	//�û������Ȩ����
	cout << "\n--����ʱ��-1��ʾȨΪ����--" << endl;
	cout << "����ʾ����" << endl;
	cout << "-1 1 2 -1 -1 -1\n-1 -1 1 3 -1 7\n-1 -1 -1 1 2 -1"
		"\n-1 -1 -1 -1 -1 3\n-1 -1 -1 -1 -1 6\n-1 -1 -1 -1 -1 -1" << endl;
	int** weigh = Generate_matrix();
	cout << "\n������ͼ�ı�Ȩ����" << endl;
	for (int i = 0; i < num_of_v; i++)
		for (int j = 0; j < num_of_v; j++) {
			scanf_s("%d", &weigh[i][j]);	//scanf()
			if (weigh[i][j] == -1)
				weigh[i][j] = inf;
		}
	return weigh;
}

void F_print(int** matrix) {	//��ʽ���������
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

int** D_multi(int** matrix, int n) {	//��Floyd�㷨�о���D��n�η�
	int** result = Generate_matrix();
	for (int i = 0; i < num_of_v; i++)	//��result����ֵ
		for (int j = 0; j < num_of_v; j++)
			result[i][j] = matrix[i][j];
	int min_add;	//ĳһ�к�ĳһ����Ӻ����Сֵ
	int* row = (int*)malloc(num_of_v * sizeof(int));	//���ڱ���ĳһ���������Сֵ
	for (int m = 1; m < n; m++)	//D��m�η�
		for (int i = 0; i < num_of_v; i++) {
			for (int j = 0; j < num_of_v; j++) {
				min_add = result[i][0] + matrix[0][j];
				for (int k = 1; k < num_of_v; k++)
					if (min_add > result[i][k] + matrix[k][j])
						min_add = result[i][k] + matrix[k][j];
				row[j] = min_add;
			}
			for (int a = 0; a < num_of_v; a++)	//���ó�����Сֵ���µ�result��
				result[i][a] = row[a];
		}
	return result;
}


int** S_multi(int** Di, int** Dj) {	//�����D���η���S�ˣ������·������
	int** result = Generate_matrix();
	for (int i = 0; i < num_of_v; i++)	//��Di��Dj��Ӧλ�õ���Сֵ��result����Ӧλ��
		for (int j = 0; j < num_of_v; j++)
			result[i][j] = min(Di[i][j], Dj[i][j]);
	return result;
}

void F_main() {	//Floyd�㷨��������
	cout << "---��ʼFloyd�㷨---\n"
	<<"������ͼ�Ľ����(����)��" << endl;
	cin >> num_of_v;
	int** D = F_input();
	int** S = Generate_matrix();
	for (int i = 0; i < num_of_v; i++)	//��S����ֵΪD
		for (int j = 0; j < num_of_v; j++)
			S[i][j] = D[i][j];
	for (int i = 2; i < num_of_v; i++)	//ѭ����S=S*D^i
		S = S_multi(S, D_multi(D, i));
	cout << "\nͼ�����·��Ϊ(inf��ʾ����)��" << endl;
	F_print(S);
	system("pause");
}

void Floyd_Warshall(int** weigh) {	//Floyd_Warshall�㷨
	for (int k = 0; k < num_of_v; k++) {   //kΪ��i��j���м�ڵ�
		for (int i = 0; i < num_of_v; i++) {
			for (int j = 0; j < num_of_v; j++) {
				if (weigh[i][k] != inf && weigh[k][j] != inf)  //���i��k����k��j��һ���ߵ�Ȩ��Ϊ�����ѭ����һ��k
					if (weigh[i][j] == inf || weigh[i][j] > weigh[i][k] + weigh[k][j])    //��ʱi��k����k��j��Ȩ��Ϊ����ֵ
						weigh[i][j] = weigh[i][k] + weigh[k][j];	//���i��j��ȨΪ������ߴ���ǰ�ߣ������Ȩ��
			}
		}
	}
}

void FW_main() {	//Floyd_Warshall�㷨��������
	cout << "---��ʼFloyd-Warshall�㷨---\n"
	<< "������ͼ�Ľ����(����)��" << endl;
	cin >> num_of_v;
	int** weigh = F_input();
	Floyd_Warshall(weigh);
	cout<<"\nͼ�����·��Ϊ(inf��ʾ����)��" << endl;
	F_print(weigh);
	system("pause");
}
