#pragma once
#include <vector>
#include <set>

using namespace std;

struct point{
    int x,y,z;

    struct point operator-(const point& b){
        return {x - b.x,y - b.y,z - b.z};
    }
    struct point operator*(const int r){
        return {x*r,y*r,z*r};
    }
    struct point operator*(const point&b){
        return {y*b.z - z*b.y,z*b.x - x*b.z,x*b.y - y*b.x};
    }
    bool operator==(const point& b){
        return (x == b.x && y == b.y && z == b.z);
    }
};



vector<vector<struct point>> generateCollinearPoints();
point getCollinearPoint(point,point,vector<vector<point>>);
void fillLines(vector<vector<point>> allCollinearLines,vector<point> cornerPts,vector<vector<point>>& noDiag);
void fillLines(vector<vector<point>> allCollinearLines,vector<point> cornerPts,vector<vector<point>>& edges,vector<vector<point>>& facePts,vector<vector<point>>& centerPt);
