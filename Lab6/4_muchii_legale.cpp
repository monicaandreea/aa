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

void legal(const std::vector<Punct>& patrat){
    std::vector<Punct> ABC;
    ABC.push_back(patrat[0]);
    ABC.push_back(patrat[1]);
    ABC.push_back(patrat[2]);
    int rez_AC = pozitie(ABC, patrat[3]);

    if(rez_AC != 1) std::cout<<"AC: LEGAL\n";
    else std::cout<<"AC: ILLEGAL\n";

    std::vector<Punct> BCD;
    BCD.push_back(patrat[1]);
    BCD.push_back(patrat[2]);
    BCD.push_back(patrat[3]);
    int rez_BD = pozitie(BCD, patrat[0]);

    if(rez_BD != 1) std::cout<<"BD: LEGAL";
    else std::cout<<"BD: ILLEGAL";
}

int main() {
    double n, m, x, y;
    std::vector<Punct> patrulater;
    for(int i = 0 ; i<4 ; i++){
        std::cin>>x>>y;
        patrulater.push_back(Punct{x, y});
    }
    legal(patrulater);
}
