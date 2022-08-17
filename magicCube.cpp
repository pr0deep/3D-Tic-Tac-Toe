/*
 * Author : Pradeep S
 * 
 * */

#include<bits/stdc++.h>
#include "print.h"

using namespace std;
using i64 = long long int; 
const int magicNumber = 42;

int grid[3][3][3];

int madd(int i,int j){
    return (i + j + 3)%3;
}

void siamese_3d(int i,int j,int k,int n){
    if(n > 27)
        return;
    grid[i][j][k] = n;
    if(grid[madd(i,-1)][j][madd(k,-1)] == -1)
        return siamese_3d(madd(i,-1),j,madd(k,-1),n + 1);
    if(grid[madd(i,-1)][madd(j,-1)][k] == -1)
        return siamese_3d(madd(i,-1),madd(j,-1),k,n + 1);
    if(grid[madd(i,1)][j][k] == -1)
        return siamese_3d(madd(i,1),j,k,n + 1);
}

void siamese_3d(vector<vector<vector<pair<int,int>>>>& grid,int i,int j,int k,int n){
    if(n > 27)
        return;
    grid[i][j][k].second = n;
    if(grid[madd(i,-1)][j][madd(k,-1)].second == -1)
        return siamese_3d(madd(i,-1),j,madd(k,-1),n + 1);
    if(grid[madd(i,-1)][madd(j,-1)][k].second == -1)
        return siamese_3d(madd(i,-1),madd(j,-1),k,n + 1);
    if(grid[madd(i,1)][j][k].second == -1)
        return siamese_3d(madd(i,1),j,k,n + 1);
}
int main(){
    memset(grid,-1,sizeof(grid));
    siamese_3d(0,0,0,1);
    for(int i = 0;i < 3;i++)
        for(int j = 0;j < 3;j++)
            for(int k = 0;k < 3;k++)
                cout << grid[i][j][k] << " ";
    return 0;
}
