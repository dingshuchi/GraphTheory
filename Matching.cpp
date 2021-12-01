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
// ��������
int Neighbor[Max][Max];     // Neighbor[i][j]>0��ʾ i j֮������
int X = Max, Y = Max;       // X,Y�ֱ�Ϊ����ͼ���㼯�Ĵ�С
int lx[Max], ly[Max];       // X��Y�����Ķ����
int Mx[Max], My[Max];       // ƥ�����飬�������X��Y���໥ƥ��Ľ�㣬Mx[i]��ʾX�����iƥ���Y���Ľ�㣬My[i]ͬ��
int min_l = INF;            // ���������ͼl ʱ����ȥ����С�����
int H_S[Max], T[Max];         //  Ѱ������·ʱ���Լ��뵽����·�ĵ� ���


// ��������
void input_graph(){
    cout << "�������ͼ���㼯X��Y�Ĵ�С��";
    cin >> X >>Y;
    cout <<"�������ͼ�Ĵ�Ȩ�ڽӾ���\n";
    for(int i=1; i<=X; i++){
        for(int j=1; j<=Y; j++){
            cin >> Neighbor[i][j];
        }

    }
}

//������
int hu_dfs(int x){
    for(int y=1; y <= Y; y++){
        //��� xy֮��������yĿǰû�м�������·
        if(Neighbor[x][y] && !T[y] ){
            T[y] = 1;

            if(My[y] == -1 || hu_dfs(My[y])){
                Mx[x] = y;
                My[y] = x;
                return 1;
            }
        }
    }   
    return 0;   //ƥ��ʧ��
}

void Hungary(){
    input_graph();
    int ans = 0;    //  ƥ�����
    //����ƥ�����飬ȫ����Ϊ-1
    memset(Mx+1, -1, sizeof(int)*X);
    memset(My+1, -1, sizeof(int)*Y);
    for(int i=1; i <= X; i++){
        if(Mx[i] == -1) //���X���� i��㻹δƥ��
        {
            memset(T+1, 0, sizeof(int)*(Y+1));       //ÿ��������·ʱ�����ö�Y���ı��
            ans += hu_dfs(i);
        }
    }
    for(int i=1; i <= X; i++){
        if(Mx[i] != -1){
            cout<<"x"<<i<<"����"<<"y"<<Mx[i]<<endl;
        }
    }
    cout << "����������ز˵�...";
    system("pause");
}
//������


// KM
int km_dfs(int x){
    H_S[x] = 1;
    for(int y=1; y <= Y; y++){
        /*
        1. x y֮��Ҫ����
        2. Ŀǰ�� y û�м��뵽����·������
        */
        if( Neighbor[x][y] != INF && !T[y]){  

            // lx[x] + ly [y] ����֮��Ҫ���� x y֮���Ȩ��, ���������� ����ͼ��Ѱ�����ƥ��
            if( lx[x]+ly[y] == Neighbor[x][y] ){    
                T[y] = 1;
                /*
                1. ��ǰ y û����ƥ������ƥ��ɹ�
                2. ���� ��ǰ yƥ���My[y] = x' ����Ѱ�ҵ������� y'����ƥ��, ���� x-y-x'-y'��һ������·��ƥ������(x-y,x'-y')
                */
                if( My[y] == -1 || km_dfs(My[y]))
                {
                    Mx[x] = y;
                    My[y] = x;
                    return 1;
                }
            }else {
                // ����������ǣ�lx[x]+ly[y] > Neighbor[x][y] 
                // ˵����ʱ�� y û��������·���ϣ� ���� Y - T�� ���� x ������ H_S�ģ��ʿ���������õ���С�� min_l
                min_l = min(min_l, lx[x]+ly[y] - Neighbor[x][y]);
            }
        }
    }

    return 0;   //ƥ��ʧ��
}

int KM(){
    input_graph();          // ����ͼ����
    // ��ʼ�����꼯��ƥ�伯
    memset(lx+1, 0, X*sizeof(lx[0]));
    memset(ly+1, 0, Y*sizeof(ly[0]));
    memset(Mx+1, -1, X*sizeof(Mx[0]));
    memset(My+1, -1, Y*sizeof(My[0]));
    // Ԥ���� X ���Ķ���
    for(int i=1; i<=X; i++){
        for(int j=1; j<=Y; j++){
            lx[i] = max(lx[i], Neighbor[i][j]);
        }
    }
    // ����X���ĵ�
    for(int i=1; i<=X; i++){
        if( Mx[i] == -1){
            while(1){
            
                min_l = INF;
                memset(H_S+1, 0, X*sizeof(H_S[0]));
                memset(T+1, 0, Y*sizeof(H_S[0]));
                if(km_dfs(i)) break;   //ƥ��ɹ�


                //ƥ��ʧ�ܣ��������ͼ, H_S ֵΪ1 ��ʾѰ������·�γɵ� H_S���ϣ�ͬ�� H_S ֵΪ1�� T����
                // H_S,T ���ϵĶ��� Ҫ��ȥ min_l
                for(int j=1; j<=X; j++){
                    if(H_S[j]) lx[j] -= min_l;
                }
                for(int j=1; j<=Y; j++){
                    if(T[j]) ly[j] += min_l;
                }
            }
        }

    }

    // ��ӡ����ƥ�伯����������Ȩ��
    int sumWeight = 0;
    for(int i=1; i <= X; i++){
        if(Mx[i] != -1 && Neighbor[i][Mx[i]] > 0){
            cout<<"x"<<i<<"����"<<"y"<<Mx[i]<<endl;
            sumWeight += Neighbor[i][Mx[i]];
        }
    }
    cout << "���Ȩ�أ�"<<sumWeight<<endl;
    cout << "����������ز˵�...";
    system("pause");
    return 0;
}