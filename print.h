#include <bits/stdc++.h>
#include "point.h"
#include "move.h"

using namespace std;

void print(vector<int>);
void print(set<int>);
void printline(int n);
void print(struct move);
void print(struct point);
void print(vector<vector<vector<pair<int,int>>>>);
void print(vector<struct point>);
void print(vector<struct move>);
void print(vector<vector<struct move>>);
void print(int,int,int,vector<struct move>,vector<vector<struct move>>,vector<struct move>,vector<vector<struct move>>,set<int>);
#define debug(x) cout << "["<<#x<<" : ";print(x);cout <<" ] " <<endl;
