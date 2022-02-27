// Algoritm pseudo-polinomial
// pentru suma maxima a elementelor dintr-un vector, mai mica sau egala decat un K dat

// Similar cu 0/1 KnapSack, doar ca aici si greutatea si valoarea sunt reprezentate de acelasi numar.
// Astfel, am inlocuit toate aparitiile lui "greutate[i]" cu "valoare[i]"
// mat[i][j] = suma maxima ce nu depaseste numarul i si foloseste primele j numere din vector
// mat[i][j] = 0, i=0, j=0
// mat[i][j] = max( mat[i][j-1], valoare[j] + mat[i - valoare[j]][j-1]

#include <iostream>
#include <fstream>
#include<vector>

std::ifstream f("text.in");

int main() {
    int n, k, x;
    f >> n >> k;

    std::vector<int> valoare;
    std::vector< std::vector<int> > mat;
    std::vector<int> lin(n + 1);

    for( int i=0 ; i<n ; i++){
        f >> x;
        valoare.push_back(x);
    }

    for( int i=0 ; i<=k ; i++){
        mat.push_back( lin);
    }

    for( int i= 1 ; i<=k ; i++){
        for(int j=1 ; j<=n ; j++) {
            if (i - valoare[j-1] >= 0)
                mat[i][j] = std::max(mat[i][j - 1], valoare[j-1] + mat[i - valoare[j-1]][j - 1]);
            else
                mat[i][j] = mat[i][j - 1];
        }
    }

    int val = mat[k][n];
    std::cout<<"Suma maxima este: "<<val<<"\n";

    //pentru verificare, afisarea elementelor alese
    int i = k;
    for( int j=n ; j>0 && val >0; j--){
        if(val == mat[i][j-1]) { continue;}
        else{
            std::cout<<"A fost adaugat elementul de pe poz "<<j<<" cu valoarea "<<valoare[j-1]<<"\n";
            val -= valoare[j-1];
            i -= valoare[j-1];
        }
    }

    return 0;
}
