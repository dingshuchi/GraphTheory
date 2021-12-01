#include <iostream>
#include<Windows.h>
#include "Matching.cpp"
#include "Floyd_Warshall.cpp"
#include "Dijkstra.cpp"
#include "tree.cpp"
using namespace std;


void Choise(){
    int temp = 1;
    while (temp) {
        system("cls");
        cout << "============图论算法程序============" << endl;
        cout << "== 1 Kruskal------------2 Prim    ==" << endl;
        cout << "== 3 BCircle------------4 Dijkstra==" << endl;
        cout << "== 5 Floyd  ------------6 F-Warshall" << endl;
        cout << "== 7 Hungary------------8 KM      ==" << endl;
        cout << "== 0 退出" << endl;
        cout << "请输入您的选择：";
        cin >> temp;
        switch (temp) {
        case 0:
            exit(0);
        case 1:
            system("cls");
            ST(temp);
            break;
        case 2:
            system("cls");
            ST(temp);
            break;
        case 3:
            system("cls");
            ST(temp);
            break;
        case 4:
            system("cls");
            Dijkstra dijkstra;
            dijkstra.dijkstra();
            break;
        case 5:
            system("cls");
            F_main();
            break;
        case 6:
            system("cls");
            FW_main();
            break;
        case 7:
            system("cls");
            Hungary();
            break;
        case 8:
            system("cls");
            KM();
            break;
        default:
            cout << "输入错误，请重新输入！";
            for (int i = 1; i <= 6; i++) {
                cout << ".";
                Sleep(300);
            }
        }
        system("cls");
    }
}

int main(){
    Choise();
    return 0;
}
