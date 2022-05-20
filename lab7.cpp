#include <iostream>
#define INF 10000000

int main(){
    int n, a,b,c;
    int N = INF;
    int S = -INF;
    int E = INF;
    int V = -INF;

    std::cin>>n;

    while(n--){
        std::cin>>a>>b>>c;
        if(b<0){
            if(c>S) S=(-c/b);
        }
        if(b>0){
            if(c<N) N=(-c/b);
        }
        if(a<0){
            if(c>V) V=(-c/a);
        }
        if(a>0){
            if(c<E) E=(-c/a);
        }
    }

    std::cout<<S<<" "<<N<<" "<<E<<" "<<V;
    
    
    if(N<S || V>E) std::cout<<

    return 0;
}
