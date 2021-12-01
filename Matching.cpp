#include <iostream>
#include<Windows.h>
#include<algorithm>
#include<map>
#include<vector>
#include<cstring>
#include<math.h>
using namespace std;


#define Max 1005
#define INF 0x3f3f3f3f
// 定义数据
int Neighbor[Max][Max];     // Neighbor[i][j]>0表示 i j之间连边
int X = Max, Y = Max;       // X,Y分别为二部图顶点集的大小
int lx[Max], ly[Max];       // X，Y集结点的顶标号
int Mx[Max], My[Max];       // 匹配数组，用来标记X，Y部相互匹配的结点，Mx[i]表示X部结点i匹配的Y部的结点，My[i]同理
int min_l = INF;            // 扩大相等子图l 时，减去的最小顶标差
int H_S[Max], T[Max];         //  寻找增广路时，对加入到增广路的点 标记


// 函数定义
void input_graph(){
    cout << "输入二部图顶点集X，Y的大小：";
    cin >> X >>Y;
    cout <<"输入二部图的带权邻接矩阵：\n";
    for(int i=1; i<=X; i++){
        for(int j=1; j<=Y; j++){
            cin >> Neighbor[i][j];
        }

    }
}

//匈牙利
int hu_dfs(int x){
    for(int y=1; y <= Y; y++){
        //如果 xy之间连边且y目前没有加入增广路
        if(Neighbor[x][y] && !T[y] ){
            T[y] = 1;

            if(My[y] == -1 || hu_dfs(My[y])){
                Mx[x] = y;
                My[y] = x;
                return 1;
            }
        }
    }   
    return 0;   //匹配失败
}

void Hungary(){
    input_graph();
    int ans = 0;    //  匹配边数
    //重置匹配数组，全部置为-1
    memset(Mx+1, -1, sizeof(int)*X);
    memset(My+1, -1, sizeof(int)*Y);
    for(int i=1; i <= X; i++){
        if(Mx[i] == -1) //如果X部的 i结点还未匹配
        {
            memset(T+1, 0, sizeof(int)*(Y+1));       //每次找增广路时，重置对Y部的标记
            ans += hu_dfs(i);
        }
    }
    for(int i=1; i <= X; i++){
        if(Mx[i] != -1){
            cout<<"x"<<i<<"——"<<"y"<<Mx[i]<<endl;
        }
    }
    cout << "按任意键返回菜单...";
    system("pause");
}
//匈牙利


// KM
int km_dfs(int x){
    H_S[x] = 1;
    for(int y=1; y <= Y; y++){
        /*
        1. x y之间要连边
        2. 目前的 y 没有加入到增广路集合中
        */
        if( Neighbor[x][y] != INF && !T[y]){  

            // lx[x] + ly [y] 顶标之和要等于 x y之间的权重, 这样就是在 等子图中寻找最大匹配
            if( lx[x]+ly[y] == Neighbor[x][y] ){    
                T[y] = 1;
                /*
                1. 当前 y 没有在匹配中则匹配成功
                2. 或者 当前 y匹配的My[y] = x' 可以寻找到其他的 y'进行匹配, 则让 x-y-x'-y'是一条增广路，匹配增大(x-y,x'-y')
                */
                if( My[y] == -1 || km_dfs(My[y]))
                {
                    Mx[x] = y;
                    My[y] = x;
                    return 1;
                }
            }else {
                // 如果不等于那，lx[x]+ly[y] > Neighbor[x][y] 
                // 说明此时的 y 没有在增广路集合， 属于 Y - T， 但是 x 是属于 H_S的，故可以在这里得到最小的 min_l
                min_l = min(min_l, lx[x]+ly[y] - Neighbor[x][y]);
            }
        }
    }

    return 0;   //匹配失败
}

int KM(){
    input_graph();          // 二部图输入
    // 初始化顶标集，匹配集
    memset(lx+1, 0, X*sizeof(lx[0]));
    memset(ly+1, 0, Y*sizeof(ly[0]));
    memset(Mx+1, -1, X*sizeof(Mx[0]));
    memset(My+1, -1, Y*sizeof(My[0]));
    // 预处理 X 部的顶标
    for(int i=1; i<=X; i++){
        for(int j=1; j<=Y; j++){
            lx[i] = max(lx[i], Neighbor[i][j]);
        }
    }
    // 遍历X部的点
    for(int i=1; i<=X; i++){
        if( Mx[i] == -1){
            while(1){
            
                min_l = INF;
                memset(H_S+1, 0, X*sizeof(H_S[0]));
                memset(T+1, 0, Y*sizeof(H_S[0]));
                if(km_dfs(i)) break;   //匹配成功


                //匹配失败，扩大等子图, H_S 值为1 表示寻找增广路形成的 H_S集合，同理 H_S 值为1是 T集合
                // H_S,T 集合的顶标 要减去 min_l
                for(int j=1; j<=X; j++){
                    if(H_S[j]) lx[j] -= min_l;
                }
                for(int j=1; j<=Y; j++){
                    if(T[j]) ly[j] += min_l;
                }
            }
        }

    }

    // 打印最优匹配集，并计算总权和
    int sumWeight = 0;
    for(int i=1; i <= X; i++){
        if(Mx[i] != -1 && Neighbor[i][Mx[i]] > 0){
            cout<<"x"<<i<<"——"<<"y"<<Mx[i]<<endl;
            sumWeight += Neighbor[i][Mx[i]];
        }
    }
    cout << "最大权重："<<sumWeight<<endl;
    cout << "按任意键返回菜单...";
    system("pause");
    return 0;
}