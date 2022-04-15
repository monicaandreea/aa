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
    long x;
    long y;
};

int testOrientare(Punct P, Punct Q, Punct R){
    long d = (Q.x * R.y) + (R.x * P.y) + (P.x * Q.y) - (Q.x * P.y) - (R.x * Q.y) - (P.x * R.y);

    if(d < 0) return 1;
    else if(d == 0) return 2;
    else return 3;
}

int main() {
    int n, x, y;
    int dreapta = 0, stanga = 0, inainte = 0;
    f>>n;
    f>>x>>y;
    Punct primul{x, y};
    f>>x>>y;
    Punct b{x, y};
    f>>x>>y;
    Punct c{x, y};
    Punct a = primul;

    int rezultat = testOrientare(primul, b, c);
    if(rezultat == 1) dreapta++;
    else if(rezultat == 2) inainte++;
    else stanga++;

    for(int i = 3 ; i<n ; i++){
        f>>x>>y;
        a = b;
        b = c;
        c = Punct{x, y};

        rezultat = testOrientare(a, b, c);
        if(rezultat == 1) dreapta++;
        else if(rezultat == 2) inainte++;
        else stanga++;
    }

    rezultat = testOrientare(b, c, primul);
    if(rezultat == 1) dreapta++;
    else if(rezultat == 2) inainte++;
    else stanga++;

    g<<stanga<<" "<<dreapta<<" "<<inainte;

    return 0;
}
