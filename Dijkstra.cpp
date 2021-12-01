// Dijkstra.cpp : ���ļ����� "dijkstra" ������
// author:dingshuchi
//

#include <iostream>
#include <stdlib.h>
#include <vector>
using namespace std;

class Dijkstra {

public:void dijkstra()
{
    //t1,t2,t3��Ϊ��ȡ��ʱ����ʱ����
    int t1, t2, t3;
    //m,n��Ϊ�жϾ���ʱ����ʱ����
    int m, n;
    //��������Զֵ
    int infinity = 99999999;
    //min��Ϊ���������м����
    int min;
    //vertex���㣬edge��
    int vertex, edge;
    //
    int typeOfGrapy;
    cout << "��ʼDijkstra�㷨������ͼ����1������ͼ����2��";
    cin >> typeOfGrapy;

    cout << "�����붥�������";
    cin >> vertex;

    cout << "������ߵ�������";
    cin >> edge;
    //�ڽӾ������飬����ľ��룬�����Ƿ�ȷ����flagֵ,������ž���·�ߵ�����
    vector<vector<int>> arrayOfAdjacencyMatrices(vertex, vector<int>(vertex, 0));
    //int(*arrayOfAdjacencyMatrices)[vertex] = (int(*)[vertex])malloc(sizeof(int) * vertex * vertex);
    int* distance = new int[vertex];
    int* flagOfDistance = new int[vertex];
    int* path = new int[vertex];

    //��ʼ���ڽӾ������飬�Խ�����Ϊ0������Ϊ����Զ
    for (int i = 0; i < vertex; i++) {
        for (int j = 0; j < vertex; j++) {
            if (i == j) {
                arrayOfAdjacencyMatrices[i][j] = 0;
            }
            else {
                arrayOfAdjacencyMatrices[i][j] = infinity;
            }
        }
    }

    //�����ȡ�ߣ������ڽӾ���
    cout << "����ÿ���ߣ���ʽ��1 2 5��ʾ1�Žڵ㵽2�Žڵ�ľ���Ϊ5,����ͼҲ����һ�μ��ɣ���\n";
    if (typeOfGrapy == 1) {
        for (int i = 0; i < edge; i++) {
            cin >> t1 >> t2 >> t3;
            arrayOfAdjacencyMatrices[t1 - 1][t2 - 1] = t3;
            arrayOfAdjacencyMatrices[t2 - 1][t1 - 1] = t3;
        }
    }
    if (typeOfGrapy == 2) {
        for (int i = 0; i < edge; i++) {
            cin >> t1 >> t2 >> t3;
            arrayOfAdjacencyMatrices[t1 - 1][t2 - 1] = t3;
        }
    }


    //��ʼ��distance]�������飬���������ʾ1�Žڵ㵽����ڵ�ĳ�ʼ����
    for (int i = 0; i < vertex; i++) {
        distance[i] = arrayOfAdjacencyMatrices[0][i];
        if (distance[i] < infinity) {
            path[i] = 1;
        }
    }

    //flagOfDistance[20]��־λ��ʼ��Ϊ0�������벻ȷ��
    for (int i = 0; i < vertex; i++) {
        flagOfDistance[i] = 0;
    }

    //1�Žڵ����������ȷ��
    flagOfDistance[0] = 1;

    //ִ��Dijkstra�㷨
    for (int i = 0; i < vertex - 1; i++) {
        //��ʼ����Ϊ����Զ
        min = infinity;

        //�ж��ɳ��㷨����ʼ�ڵ�
        for (int j = 0; j < vertex; j++) {
            if (flagOfDistance[j] == 0 && distance[j] < min) {

                min = distance[j];
                m = j;
            }
        }
        //
        flagOfDistance[m] = 1;


        //ִ���ɳ��㷨
        for (n = 0; n < vertex; n++) {
            if (arrayOfAdjacencyMatrices[m][n] < infinity && distance[n] > distance[m] + arrayOfAdjacencyMatrices[m][n]) {

                distance[n] = distance[m] + arrayOfAdjacencyMatrices[m][n];
                path[n] = m + 1;
            }
        }

    }

    cout << "ǰ�����㼰����ֱ�Ϊ:\n";
    for (int k = 0; k < vertex; k++) {
        cout << "��" << k + 1 << "\t";
    }
    cout << "\n";
    for (int k = 0; k < vertex; k++) {
        cout << path[k] << "\t";
    }
    cout << "\n";
    for (int k = 0; k < vertex; k++) {
        cout << distance[k] << "\t";
    }
    cout << endl;
    system("pause");
    }
};
