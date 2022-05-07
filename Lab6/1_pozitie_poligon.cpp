#include <fstream>
#include <iostream>
#include <vector>
#include <stack>

std::ifstream f("date.in");
std::ofstream g("pozitie.out");

struct Punct{
    int x;
    int y;
};

int testOrientare(Punct P, Punct Q, Punct R){
    int d = (Q.x * R.y) + (R.x * P.y) + (P.x * Q.y) - (Q.x * P.y) - (R.x * Q.y) - (P.x * R.y);

    if(d < 0) return 1; // dreapta
    else if(d == 0) return 2; //coliniare
    else return 3; //stanga
}

int intersecteaza(Punct P, Punct Q, Punct A, Punct B){
    int rez_a = testOrientare(P, Q, A);
    int rez_b = testOrientare(P, Q, B);
    int rez_p = testOrientare(A, B, P);
    int rez_q = testOrientare(A, B, Q);

    if(rez_p == 2 && rez_q == 2) return 0; // pe linie cu ambele puncte
    if(rez_p == 2 && rez_a != rez_b) return 1; // pe linie cu P
    if(rez_q == 2 && rez_a != rez_b) return 2; // pe linie cu Q
    if( rez_a != rez_b && rez_p != rez_q) return 3; // intersecteaza latura dar nu punctele

    return -1;
}

// 0- inafara poligonului
// 1- inauntrul poligonului
// 2- pe latura poligonului
int pozitie(int n, const std::vector<Punct>& poligon, Punct punct){
    int intersectari = 0;
    Punct extrem = {1000, punct.y};

    for(int i = 0 ; i<=n-1 ; i++){
        int j = (i+1)%n;
        int rezultat = intersecteaza(poligon[i], poligon[j], punct, extrem);
        if( rezultat != -1){

            if(testOrientare(poligon[i], poligon[j], punct) == 2)
                if( punct.x >= std::min( poligon[i].x, poligon[j].x) && punct.x <= std::max(poligon[i].x, poligon[j].x) )
                    if( punct.y >= std::min( poligon[i].y, poligon[j].y) && punct.y <= std::max(poligon[i].y, poligon[j].y) ){
                        return 2;
                    }

            if( rezultat == 0){
                //std::cout<<"sunt pe aceeasi linie\n";
                continue;
            }
            else if( rezultat == 1){
                if( poligon[i].y > poligon[j].y)
                    intersectari++;
            }
            else if( rezultat == 2){
                if( poligon[j].y > poligon[i].y)
                    intersectari++;
            }
            else{
                intersectari++;
            }
        }
    }

    if(intersectari % 2 == 0) return 0;
    else return 1;
}

int main() {
    int n, m, x, y;
    std::vector<Punct> poligon;
    std::cin>>n;
    for(int i = 0 ; i<n ; i++){
        std::cin>>x>>y;
        poligon.push_back(Punct{x, y});
    }

    std::cin>>m;
    while(m--){
        std::cin>>x>>y;
        Punct Q{x, y};
        int rezultat = pozitie(n, poligon, Q);

        if(rezultat == 0)std::cout<<"OUTSIDE\n";
        else if(rezultat == 1) std::cout<<"INSIDE\n";
        else std::cout<<"BOUNDARY\n";
    }
    return 0;
}
