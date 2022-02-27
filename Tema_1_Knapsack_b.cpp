// Algoritm 1/2 aproximativ
// pentru suma maxima a elementelor dintr-un vector, mai mica sau egala decat un K dat

// Similar cu 0/1 KnapSack 1/2 aproximativ, doar ca aici si greutatea si valoarea sunt reprezentate de acelasi numar.
// Astfel, am inlocuit toate aparitiile lui "greutate[i]" cu "valoare[i]"
// ordonam obiectele dupa valoare si le verificam in ordine descrescatoare
// daca obiectul are valoarea < G, il pastram la suma

// La KnapSack se tinea cont de obiectul cu valoarea cea mai mare
// (in cazul in care el ducea la un raport prost, dar in final la o solutie mai buna decat ce gasita)
// aici nu mai este nevoie, deoarece el o sa fie primul dupa ordonare, fiindca nu mai exista rapoarte

// cazul care demonstreaza ca este tight bound 1/2 aproximativ:
// algoritmul alege obiectul cu valoarea 51, chiar daca obiectele 2 si 3 au suma 100
/*
3 100
51 50 50
*/


#include <iostream>
#include <fstream>
#include<vector>
#include <algorithm>

std::ifstream f("text.in");

int main() {
    int n, k, x, op, v_op=0;
    f >> n >> k;
    
    std::vector<int> valoare;
    std::vector< std::vector<int> > mat;
    std::vector< std::pair<float, int>> obj;
    
    for( int i=0 ; i<n ; i++){
        f >> x;
        valoare.push_back(x);
    }

    for( int i=0 ; i<n ; i++){
        obj.push_back( std::make_pair(valoare[i] , i));
    }

    std::sort(obj.begin(), obj.end());

    int s=0, G=k;
    for( int i=n-1 ; i>=0 ; i-- ){
        int j = obj[i].second;
        if(valoare[j] <= G){
            std::cout<<"obiectul "<<j+1<<" cu valoare "<<valoare[j]<<"\n";
            G -= valoare[j];
            s += valoare[j];
        }
    }

    int rez = s;

    std::cout<<"Valoarea totala este: "<<rez;

    return 0;
}
