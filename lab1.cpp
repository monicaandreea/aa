// 0/1 KnapSack Problem

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    ifstream in("knapsack.in");

    int n, w;
    in >> n >> w;

    vector<int> weight(n +1), valori(n + 1);
//    vector<vector<int>> matrice(w + 1);
    int matrice[w + 1][n + 1];

    for(int i = 0; i <= w; i++){
        for(int j = 0; j <= n; j++){
            matrice[i][j] = 0;
        }
    }

    for(int j = 0; j <= n; j++){
        matrice[0][j] = 0;
    }

    for(int i = 1; i <= n; i++){
        in >> valori[i];
    }

    for(int i = 1; i <= n; i++) {
        in >> weight[i];
    }

    for(int i = 1; i <= w; i++){
        for(int j = 1; j <= n; j++){
            if (i - weight[j] >= 0) // nu iese din matrice
                matrice[i][j] = max(matrice[i][j - 1], valori[j] + matrice[i - weight[j]][j - 1]);
            else{
                matrice[i][j] = matrice[i][j - 1];
            }
        }
    }

    for(int i = 0; i <= w; i++){
        for(int j = 0; j <= n; j++){
            cout << matrice[i][j] << " ";
        }
        cout << "\n";
    }

    cout << "Profitul maxim este " << matrice[w][n] << "\n";
    int profitMaxim = matrice[w][n], g = w, i = w + 1, j = n + 1;

    while(i > 0 && j > 0){
        if(i - weight[j] >= 0){
            i -= weight[j];
            j -= 1;
            cout << "Obiectul " << j << '\n';
        }
        else if(matrice[i][j - 1] == matrice[i][j]) {
            j -= 1;
        }
        else if(i - weight[j] < 0) {
            j -= 1;
        }
    }

    in.close();
    return 0;
}
