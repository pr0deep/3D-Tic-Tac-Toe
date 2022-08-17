#include "print.h"
#include<iostream>

void print(vector<int> a){
    cout << "{ ";
    for(int i = 0;i < a.size() - 1;i++)
        cout << a[i] << ",";
    cout << a[a.size() -1];
    cout <<  " }" << endl;

}

void print(set<int> s){
    cout << "{  ";
    for(int i : s)
        cout << i << " ";
    cout << " }" << endl;
}

void printline(int n){
    cout << "x";
    for(int i = 0;i < n;i++)
        cout << "-";
    cout << "x";
    cout << endl;
}

void print(vector<struct point> points){
    cout << "[";
    for(struct point p:points){
        cout << "{ " << p.x <<","<<p.y <<","<<p.z<<"} ";
    }
    cout <<"]" << endl;
}

void print(vector<struct move> moves){
    cout << "[";
    for(struct move m:moves){
        cout << "{ " << m.pt.x <<","<<m.pt.y <<","<<m.pt.z<<","<<m.n << "} ";
    }
    cout <<"]" << endl;
}


void print(vector<vector<struct move>> v){
    cout << "[ ";
    for(vector<struct move> m:v){
        print(m);
    }
    cout << " ]" << endl;
}



void print(int round,int p1score,int p2score,vector<struct move> p1move,vector<vector<struct move>> p1wmove,vector<struct move> p2move,vector<vector<struct move>> p2wmove,set<int> s){

    cout << "Round : " << round << endl;
    cout << "Score : " << p1score << " - " << p2score << endl;
    cout << "Player 1 : ";
    print(p1move);
    cout << "win lines : ";
    print(p1wmove);
    cout << "Player 2 : ";
    print(p2move);
    cout << "win lines : ";
    print(p2wmove);
    cout << "Available numbers : ";
    print(s);
}
