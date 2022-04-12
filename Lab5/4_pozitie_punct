#include <fstream>
#include <iostream>
#include <vector>
#include <stack>

std::ifstream f("pozitie.in");
std::ofstream g("pozitie.out");

/*
 * Vedem de cate ori intersecteaza polinomul cu dreapta formata din (Q.x, Q.y) si (inf, Q.y)
 * numar impar => este inauntru
 * numar par => este inafara
 * se verifica de asemenea pentru fiecare dreapta daca este coliniar Q cu capetele dreptei
 * (daca se intersecteaza si este coliniar => este pe dreapta => este pe latura polinomului)
 * puncte testate: (-6,1), (2,5), (-1,4), (-2, 8), (4,2)
 */

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

bool intersecteaza(Punct P, Punct Q, Punct A, Punct B){
    int rez_a = testOrientare(P, Q, A);
    int rez_b = testOrientare(P, Q, B);
    int rez_p = testOrientare(A, B, P);
    int rez_q = testOrientare(A, B, Q);

    if(testOrientare(A, B, P) == 2) return false;
    if(testOrientare(A, B, Q) == 2) return false;

    if( rez_a != rez_b && rez_p != rez_q) return true;

    return false;
}

// 0- inafara poligonului
// 1- inauntrul poligonului
// 2- pe latura poligonului
int pozitie(int n, const std::vector<Punct>& poligon, Punct punct){
    int intersectari = 0;
    Punct extrem = {1000, punct.y};

    for(int i = 0 ; i<n-1 ; i++){
        if(intersecteaza(poligon[i], poligon[i+1], punct, extrem)){
            std::cout<<"intersecteaza: "<<i+1<<" si "<<i+2<<"\n";
            if(testOrientare(poligon[i], poligon[i+1], punct) == 2)
                        return 2;
            intersectari++;
        }
    }

    if(intersecteaza(poligon[n-1], poligon[0], punct, extrem)){
        if(testOrientare(poligon[n-1], poligon[0], punct) == 2)
                    return 2;
        intersectari++;
    }

    if(intersectari % 2 == 0 && intersectari != 0) return 0;
    else return 1;
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
