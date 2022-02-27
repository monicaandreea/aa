// 0/1 KnapSack Problem
// 1/2 Aproximativ

// vectorul obj tine obiectele sortate crescator dupa raportul valorii/greutatii
// ( este pair(raport, index) pentur a stii care este obiectul original dupa sortare

// pentru fiecare obiect din obj, parcurs descrescator:
// daca greutate obiect<= G:
// scadem greutarea din G si adaugam valoarea in S

// la final comparam S cu obiectul cu valoarea maxima
// in cazul in care avem un obiect greu, dar cu valoare mare
// dar duce la un rezultat mai bum

// cazul care demonstreaza ca este 1/2 Aproximativ, tight bound:
// valoarea maxima corecta este 100, prin alegerea ultimelor 2 obiecte
// dar algoritmul alege primul obiect, cu o valoare de 52
/*
3 100
51 50 50
52 50 50
*/

#include <iostream>
#include <fstream>
#include<vector>
#include <algorithm>

std::ifstream f("text.in");

int main() {
    int n, w, x, op, v_op=0;
    f >> n >> w;

    std::vector<int> greutate;
    std::vector<int> valoare;
    std::vector< std::vector<int> > mat;
    std::vector< std::pair<float, int>> obj;

    for( int i=0 ; i<n ; i++){
        f >> x;
        greutate.push_back(x);
    }
    for( int i=0 ; i<n ; i++){
        f >> x;
        valoare.push_back(x);
        if(x > v_op){
            v_op = x;
            op = i;
        }
    }

    for( int i=0 ; i<n ; i++){
        obj.push_back( std::make_pair(1.0*valoare[i]/greutate[i] , i));
    }

    std::sort(obj.begin(), obj.end());

    int s=0, G=w;
    for( int i=n-1 ; i>=0 ; i-- ){
        int j = obj[i].second;
        if(greutate[j] <= G){
            std::cout<<"obiectul "<<j+1<<" cu greutate "<<greutate[j]<<" si val "<<valoare[j]<<"\n";
            G -= greutate[j];
            s += valoare[j];
        }
    }

    int rez = std::max(s, valoare[op]);

    std::cout<<"Valoarea totala este: "<<rez;

    return 0;
}
