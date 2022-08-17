#include "point.h"
#include <iostream>

vector<vector<point>> generateCollinearPoints(){
    vector<point> allPoints;
    vector<vector<point>> collinearLines;
    for(int i = 0;i < 3;i++){
        for(int j = 0;j < 3;j++){
            for(int k = 0;k < 3;k++){
               allPoints.push_back({i,j,k}); 
            }
        }
    }
    // choose three points and check if they are collinear..
    point origin = {0,0,0};
    for(int i = 0;i < allPoints.size();i++){
        for(int j = i + 1;j < allPoints.size();j++){
            for(int k = j + 1;k < allPoints.size();k++){
                point ij = allPoints[i] - allPoints[j],ik = allPoints[i] - allPoints[k];
                if(ij * ik == origin && i != j && j != k && i != k)
                    collinearLines.push_back({allPoints[i],allPoints[j],allPoints[k]});
            }
        }
    }
return collinearLines;
}

point getCollinearPoint(point a,point b,vector<vector<point>> collinearLines){

  for(vector<point> pts:collinearLines){
        for(int i = 0;i < 3;i++){
            for(int j = i + 1;j < 3;j++){
                if((pts[i] == a && pts[j] == b) || (pts[j] == a && pts[i] == b)){
                    set<int> s = {0,1,2};
                    s.erase(i);s.erase(j);
                    return pts[*s.begin()];
                }
            }
        }
  }
  return {-1,-1,-1};
}


void fillLines(vector<vector<point>> allCollinearLines,vector<point> cornerPts,vector<vector<point>>& noDiag){
    for(vector<point> l : allCollinearLines){
        int m = (l[0].x == l[1].x && l[0].x == l[2].x) + (l[0].y == l[1].y && l[0].y == l[2].y) + (l[0].z == l[1].z && l[0].z == l[2].z);
        if(m == 2){
                noDiag.push_back(l);
        }
    }
}
