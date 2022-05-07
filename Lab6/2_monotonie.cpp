#include <fstream>
#include <iostream>
#include <vector>
#include <stack>

#define MAX 100000000

std::ifstream f("monotonie.in");
std::ofstream g("frontiera.out");

struct Punct{
    int x;
    int y;
};

bool X_monoton(int n, const std::vector<Punct>& multime, int low, int high){
    Punct curent = multime[low];
    int poz = low;
    while(poz != high){
        if(poz<n-1) poz++;
        else poz = 0;

        if(multime[poz].x < curent.x) return false;
        curent = multime[poz];
    }

    while(poz != high){
        if(poz>0) poz--;
        else poz = n-1;

        if(multime[poz].x < curent.x) return false;
        curent = multime[poz];
    }
    return true;
}

bool Y_monoton(int n, const std::vector<Punct>& multime, int low, int high){
    Punct curent = multime[high];
    int poz = high;
    while(poz != low){
        if(poz<n-1) poz++;
        else poz = 0;

        if(multime[poz].y > curent.y) return false;
        curent = multime[poz];
    }

    while(poz != low){
        if(poz>0) poz--;
        else poz = n-1;

        if(multime[poz].y > curent.y) return false;
        curent = multime[poz];
    }
    return true;
}

int main() {
    int n, x, y, minX = MAX, maxX = -MAX, minY = MAX, maxY = -MAX, minX_i, maxX_i, minY_i, maxY_i;
    std::vector<Punct> multime;
    std::cin>>n;
    for(int i = 0 ; i<n ; i++){
        std::cin>>x>>y;
        if(x<minX){minX = x; minX_i = i;}
        if(x>maxX){maxX = x; maxX_i = i;}
        if(y<minY){minY = y; minY_i = i;}
        if(y>maxY){maxY = y; maxY_i = i;}
        multime.push_back(Punct{x, y});
    }

    if(X_monoton(n, multime, minX_i, maxX_i)) std::cout<<"YES\n";
    else std::cout<<"NO\n";
    if(Y_monoton(n, multime, minY_i, maxY_i)) std::cout<<"YES";
    else std::cout<<"NO";

    return 0;
}
