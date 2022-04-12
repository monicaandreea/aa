#include <fstream>
#include <iostream>
#include <vector>

std::ifstream f("roby.in");
std::ofstream g("roby.out");

/* TEST DE ORIENTARE
 *            |  1  1  1 |   { <0, R in dreapta lui PQ => CAZ 1
 * d(P,Q,R) = | xp xq xr | = { 0, coliniare            => CAZ 2
 *            | yp yq yr |   { >0, R in stanga lui PQ  => CAZ 3
 */

struct Punct{
    int x;
    int y;
};

int testOrientare(Punct P, Punct Q, Punct R){
    int d = (Q.x * R.y) + (R.x * P.y) + (P.x * Q.y) - (Q.x * P.y) - (R.x * Q.y) - (P.x * R.y);

    if(d < 0) return 1;
    else if(d == 0) return 2;
    else return 3;
}

int main() {
    int n, x, y;
    int dreapta = 0, stanga = 0, inainte = 0;
    std::vector<Punct> poligon;
    f>>n;
    for(int i = 0 ; i<n ; i++){
        f>>x>>y;
        poligon.push_back(Punct{x, y});
    }

    for(int i = 2 ; i<n ; i++){
        int rezultat = testOrientare(poligon[i-2], poligon[i-1], poligon[i]);
        if(rezultat == 1) dreapta++;
        else if(rezultat == 2) inainte++;
        else stanga++;
    }

    int rezultat = testOrientare(poligon[n-2], poligon[n-1], poligon[0]);
    if(rezultat == 1) dreapta++;
    else if(rezultat == 2) inainte++;
    else stanga++;

    g<<stanga<<" "<<dreapta<<" "<<inainte;

    return 0;
}
