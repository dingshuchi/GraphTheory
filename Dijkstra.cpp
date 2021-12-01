// Dijkstra.cpp : 此文件包含 "dijkstra" 函数。
// author:dingshuchi
//

#include <iostream>
#include <stdlib.h>
#include <vector>
using namespace std;

class Dijkstra {

public:void dijkstra()
{
    //t1,t2,t3作为读取边时的临时变量
    int t1, t2, t3;
    //m,n作为判断距离时的临时变量
    int m, n;
    //定义无穷远值
    int infinity = 99999999;
    //min作为计算距离的中间变量
    int min;
    //vertex顶点，edge边
    int vertex, edge;
    //
    int typeOfGrapy;
    cout << "开始Dijkstra算法，无向图输入1，有向图输入2：";
    cin >> typeOfGrapy;

    cout << "请输入顶点个数：";
    cin >> vertex;

    cout << "请输入边的条数：";
    cin >> edge;
    //邻接矩阵数组，两点的距离，距离是否确定的flag值,用来存放经过路线的数组
    vector<vector<int>> arrayOfAdjacencyMatrices(vertex, vector<int>(vertex, 0));
    //int(*arrayOfAdjacencyMatrices)[vertex] = (int(*)[vertex])malloc(sizeof(int) * vertex * vertex);
    int* distance = new int[vertex];
    int* flagOfDistance = new int[vertex];
    int* path = new int[vertex];

    //初始化邻接矩阵数组，对角线设为0，其他为无穷远
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

    //定义读取边，输入邻接矩阵
    cout << "输入每条边（格式如1 2 5表示1号节点到2号节点的距离为5,有向图也输入一次即可）：\n";
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


    //初始化distance]距离数组，这里数组表示1号节点到其余节点的初始距离
    for (int i = 0; i < vertex; i++) {
        distance[i] = arrayOfAdjacencyMatrices[0][i];
        if (distance[i] < infinity) {
            path[i] = 1;
        }
    }

    //flagOfDistance[20]标志位初始化为0，即距离不确定
    for (int i = 0; i < vertex; i++) {
        flagOfDistance[i] = 0;
    }

    //1号节点与自身距离确定
    flagOfDistance[0] = 1;

    //执行Dijkstra算法
    for (int i = 0; i < vertex - 1; i++) {
        //初始距离为无穷远
        min = infinity;

        //判断松弛算法的起始节点
        for (int j = 0; j < vertex; j++) {
            if (flagOfDistance[j] == 0 && distance[j] < min) {

                min = distance[j];
                m = j;
            }
        }
        //
        flagOfDistance[m] = 1;


        //执行松弛算法
        for (n = 0; n < vertex; n++) {
            if (arrayOfAdjacencyMatrices[m][n] < infinity && distance[n] > distance[m] + arrayOfAdjacencyMatrices[m][n]) {

                distance[n] = distance[m] + arrayOfAdjacencyMatrices[m][n];
                path[n] = m + 1;
            }
        }

    }

    cout << "前驱顶点及距离分别为:\n";
    for (int k = 0; k < vertex; k++) {
        cout << "点" << k + 1 << "\t";
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
