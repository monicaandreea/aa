#include <fstream>
#include <iostream>
#include <vector>
#include <stack>

std::ifstream f("pozitie.in");
std::ofstream g("pozitie.out");

struct Punct{
    long x;
    long y;
};

int testOrientare(Punct P, Punct Q, Punct R){
    long d = (Q.x * R.y) + (R.x * P.y) + (P.x * Q.y) - (Q.x * P.y) - (R.x * Q.y) - (P.x * R.y);

    if(d < 0) return 1; // dreapta
    else if(d == 0) return 2; //coliniare
    else return 3; //stanga
}

// 0- inafara poligonului
// 1- inauntrul poligonului
// 2- pe latura poligonului
int pozitie(int n, const std::vector<Punct>& poligon, Punct punct){
    for(int i = 1 ; i<n ; i++){
        int rezultat = testOrientare(poligon[i-1], poligon[i], punct);
        if(rezultat == 1) {std::cout<<i-1<<" "<<i<<"\n";  return 0; }
        else if(rezultat == 2){
            if( punct.x >= std::min( poligon[i-1].x, poligon[i].x) && punct.x <= std::max(poligon[i-1].x, poligon[i].x) )
                if( punct.y >= std::min( poligon[i-1].y, poligon[i].y) && punct.y <= std::max(poligon[i-1].y, poligon[i].y) )
                    return 2;
        }
    }

    int rezultat = testOrientare(poligon[n-1], poligon[0], punct);
    if(rezultat == 1) return 0;
    else if(rezultat == 2){
        if( punct.x >= std::min( poligon[n-1].x, poligon[0].x) && punct.x <= std::max(poligon[n-1].x, poligon[0].x) )
            if( punct.y >= std::min( poligon[n-1].y, poligon[0].y) && punct.y <= std::max(poligon[n-1].y, poligon[0].y) )
                return 2;
    }

    return 1;
}

int main() {
    int n, x, y;
    std::vector<Punct> poligon;
    f>>n;
    for(int i = 0 ; i<n ; i++){
        f>>x>>y;
        poligon.push_back(Punct{x, y});
    }

    f>>x>>y;
    Punct Q{x, y};

    int rezultat = pozitie(n, poligon, Q);

    if(rezultat == 0)std::cout<<"Punctul este inafara poligonului.";
    else if(rezultat == 1) std::cout<<"Punctul este in interiorul poligonului.";
    else std::cout<<"Punctul este pe latura poligonului.";
    return 0;
}
