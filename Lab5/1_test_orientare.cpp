#include <iostream>

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
    int n;
    std::cin>>n;
    while(n--){
    int x, y;
    std::cin>>x>>y;
    Punct P = {x, y};
    std::cin>>x>>y;
    Punct Q = {x, y};
    std::cin>>x>>y;
    Punct R = {x, y};

    int rezultat = testOrientare(P, Q, R);

    if(rezultat == 1) std::cout<<"RIGHT\n";
    else if(rezultat == 2) std::cout<<"TOUCH\n";
    else std::cout<<"LEFT\n";

    }

    return 0;
}

