#include <fstream>
#include <iostream>
#include <vector>
#include <stack>

std::ifstream f("file.in");
std::ofstream g("pozitie.out");

/*
      | ax-dx, ay-dy, (ax-dx)² + (ay-dy)² |   { = 0, d is on circle
det = | bx-dx, by-dy, (bx-dx)² + (by-dy)² | = { > 0, d is inside circle
      | cx-dx, cy-dy, (cx-dx)² + (cy-dy)² |   { < 0, d is outside circle

 */

struct Punct{
    double x;
    double y;
};

// 0- inafara poligonului
// 1- inauntrul poligonului
// 2- pe latura poligonului
int pozitie(const std::vector<Punct>& triunghi, Punct punct) {
    double ax = triunghi[0].x - punct.x;
    double ay = triunghi[0].y - punct.y;
    double bx = triunghi[1].x - punct.x;
    double by = triunghi[1].y - punct.y;
    double cx = triunghi[2].x - punct.x;
    double cy = triunghi[2].y - punct.y;

    double d = (ax*ax + ay*ay)*(cy*bx - cx*by) +
               (bx*bx + by*by)*(ay*cx - ax*cy) +
               (cx*cx + cy*cy)*(by*ax - bx*ay);

    if( d<0 ) return 0;
    else if( d>0 ) return 1;
    else return 2;
}


int main() {
    double n, m, x, y;
    std::vector<Punct> triunghi;
    for(int i = 0 ; i<3 ; i++){
        std::cin>>x>>y;
        triunghi.push_back(Punct{x, y});
    }

    std::cin>>m;
    while(m--){
        std::cin>>x>>y;
        Punct Q{x, y};
        int rezultat = pozitie(triunghi, Q);

        if(rezultat == 0)std::cout<<"OUTSIDE\n";
        else if(rezultat == 1) std::cout<<"INSIDE\n";
        else std::cout<<"BOUNDARY\n";
    }
    return 0;
}
