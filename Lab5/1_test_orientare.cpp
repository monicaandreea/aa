#include <iostream>

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
    int x, y;
    std::cout<<"P:";
    std::cin>>x>>y;
    Punct P = {x, y};
    std::cout<<"Q:";
    std::cin>>x>>y;
    Punct Q = {x, y};
    std::cout<<"R:";
    std::cin>>x>>y;
    Punct R = {x, y};

    int rezultat = testOrientare(P, Q, R);

    if(rezultat == 1) std::cout<<"Viraj la dreapta.";
    else if(rezultat == 2) std::cout<<"Puncte coliniare";
    else std::cout<<"Viraj la stanga.";

    return 0;
}
