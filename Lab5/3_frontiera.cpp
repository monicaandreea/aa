#include <fstream>
#include <iostream>
#include <vector>
#include <stack>

std::ifstream f("frontiera.in");
std::ofstream g("frontiera.out");

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

Punct penultimul(std::stack<Punct> stiva){
    Punct ultimul = stiva.top();
    stiva.pop();
    Punct penultimul = stiva.top();
    stiva.push(ultimul);

    return penultimul;
}

Punct ultimul(std::stack<Punct> stiva){
    return stiva.top();
}

std::stack<Punct> frontiera_inferioara(int n, const std::vector<Punct>& multime){
    std::stack<Punct> stiva;
    stiva.push(multime[0]);
    stiva.push(multime[1]);
    stiva.push(multime[2]);

    for( int i = 3; i<n ; i++){
        int rezultat = testOrientare(penultimul(stiva), ultimul(stiva), multime[i]);

        if(rezultat == 3) stiva.push(multime[i]);
        else{
            while(testOrientare(penultimul(stiva), ultimul(stiva), multime[i]) == 1 && stiva.size() > 1)
                stiva.pop();
            stiva.push(multime[i]);
        }
    }

    return stiva;
}

std::stack<Punct> frontiera_superioara(int n, const std::vector<Punct>& multime){
    std::stack<Punct> stiva;
    stiva.push(multime[n-1]);
    stiva.push(multime[n-2]);
    stiva.push(multime[n-3]);

    for( int i = n-4; i>=0 ; i--){
        int rezultat = testOrientare(penultimul(stiva), ultimul(stiva), multime[i]);

        if(rezultat == 3) stiva.push(multime[i]);
        else{
            while(testOrientare(penultimul(stiva), ultimul(stiva), multime[i]) == 1 && stiva.size() > 1)
                stiva.pop();
            stiva.push(multime[i]);
        }
    }

    return stiva;
}

void frontiera(int n, const std::vector<Punct>& multime){
    std::stack<Punct> stiva_i = frontiera_inferioara(n, multime);

    while(!stiva_i.empty()){
        g<<"("<<stiva_i.top().x<<", "<<stiva_i.top().y<<")\n";
        stiva_i.pop();
    }

    std::stack<Punct> stiva_s = frontiera_superioara(n, multime);
    stiva_s.pop();

    while(stiva_s.size()>1){
        g<<"("<<stiva_s.top().x<<", "<<stiva_s.top().y<<")\n";
        stiva_s.pop();
    }
}

int main() {
    int n, x, y;
    std::vector<Punct> multime;
    f>>n;
    for(int i = 0 ; i<n ; i++){
        f>>x>>y;
        multime.push_back(Punct{x, y});
    }

    frontiera(n, multime);

    return 0;
}
