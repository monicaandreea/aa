// 0/1 KnapSack Problem

#include <iostream>
#include <fstream>
#include<vector>

std::ifstream f("text.in");

int main() {
    int n, w, x;
    f >> n >> w;

    std::vector<int> greutate;
    std::vector<int> valoare;
    std::vector< std::vector<int> > mat;
    std::vector<int> lin(n + 1);

    for( int i=0 ; i<n ; i++){
        f >> x;
        greutate.push_back(x);
    }
    for( int i=0 ; i<n ; i++){
        f >> x;
        valoare.push_back(x);
    }

    for( int i=0 ; i<=w ; i++){
        mat.push_back( lin);
    }

    for( int i= 1 ; i<=w ; i++){
        for(int j=1 ; j<=n ; j++) {
            if (i - greutate[j-1] >= 0)
                mat[i][j] = std::max(mat[i][j - 1], valoare[j-1] + mat[i - greutate[j-1]][j - 1]);
            else
                mat[i][j] = mat[i][j - 1];
        }
    }

    /*for( int i= 0 ; i<=w ; i++){
        for(int j=0 ; j<=n ; j++){
            if(mat[i][j]<10)
            std::cout<<mat[i][j]<<"   ";
            else
                std::cout<<mat[i][j]<<"  ";
        }
        std::cout<<"\n";
    }*/

    int val = mat[w][n];
    std::cout<<"Profitul maxim este: "<<val<<"\n";

    int i = w;
    for( int j=n ; j>0 && val >0; j--){
        if(val == mat[i][j-1]) { continue;}
        else{
            std::cout<<"A fost adaugat elementul de pe poz "<<j<<" cu greutatea "<<greutate[j-1]<<" si valoarea " << valoare[j-1]<<"\n";
            val -= valoare[j-1];
            i -= greutate[j-1];
        }
    }

    return 0;
}
