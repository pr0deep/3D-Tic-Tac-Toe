#pragma once
#include "point.h"
#include <vector>


//each move is characterised by x,y,z and the number..
struct move{
    struct point pt;
    int n;
    
    bool operator==(const move& b) const{
        return (pt.x == b.pt.x && pt.y == b.pt.y && pt.z == b.pt.z && n == b.n);
    }
};
