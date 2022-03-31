#include <iostream>
#include <vector>
#include <bitset>
#include <algorithm>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <random>

std::ifstream f("date.in");

#define NR_GENE 22

class Individ{
    std::vector<int> cod; // numarul codificat in baza 2
    double valoare; // numarul din intervalul initial
    int valoare_cod; // numarul codificat in baza 10
    double fitness;
public:
    Individ(std::vector<int> cod, double valoare, int valoare_cod, double fitness) : cod(std::move(cod)), valoare(valoare), valoare_cod(valoare_cod), fitness(fitness) {}

    Individ() {}

    const std::vector<int> &getCod() const {
        return cod;
    }

    void setCod(const  std::vector<int> &cod) {
        Individ::cod = cod;
    }

    double getValoare() const {
        return valoare;
    }

    void setValoare(double valoare) {
        Individ::valoare = valoare;
    }

    int getValoareCod() const {
        return valoare_cod;
    }

    void setValoareCod(int valoareCod) {
        valoare_cod = valoareCod;
    }

    double getFitness() const {
        return fitness;
    }

    void setFitness(double fitness) {
        Individ::fitness = fitness;
    }
};

class Algoritm{
    int dim_pop, stanga, dreapta, a, b, c, precizie, nr_etape, etapa_curenta;
    double  p_crossover, p_mutatie;
    std::vector<Individ> generatie;
    std::vector<double> probabilitate_selectie;
    std::vector<double> interval;
    std::vector<int> doi;

    double fitness(double x, int a, int b, int c){
        return (float)a * x * x + b * x + c;
    }

    // [1, 2, 4, 8, 16...] pentru gene
    void puteriDoi(){
        doi.push_back(1);
        int nr = 1;

        for(int i=2; i<=NR_GENE ; i++){
            nr *= 2;
            doi.push_back(nr);
        }
    }

    // baza 10 -> baza 2
    std::vector<int> codificare(int x)
    {
        std::vector<int> cod(NR_GENE, 0);
        int rest = x, cnt = NR_GENE -1 ;
        while(x > 0){
            rest = x % 2;
            x = x / 2;
            cod[cnt] = rest;
            cnt--;
        }
        return cod;
    }

    // baza 2 -> (baza 10, valoarea din interval, fitness)
    std::pair<int, std::pair<double, double>> decodificare( std::vector<int> cod){
        int x=0;

        for(int i = 0 ; i <= NR_GENE-1 ; i++){
            if(cod[i] == 1) x = x + doi[NR_GENE - i - 1];
        }

        int val = 1;
        int p = precizie;

        while( p > 0 ){
            val = val * 10;
            p--;
        }

        int st = stanga * val;

        double y = x + st;
        y = y / val;

        double f = fitness(y, a, b, c);

        return std::make_pair(x, std::make_pair(y, f));
    }

    std::vector<Individ> generareIndivizi(){
        srand( time(NULL) );
        std::vector<Individ> indivizi(dim_pop);
        int val = 1;
        int p = precizie;

        while( p > 0 ){
            val = val * 10;
            p--;
        }

        int stanga_generare = stanga, dreapta_generare = dreapta;
        stanga_generare = stanga * val;
        dreapta_generare = dreapta * val;
        int st = stanga_generare, dr = dreapta_generare;
        stanga_generare -= st;
        dreapta_generare -= st;

        // st = -1000000, dr = 2000000
        // stanga_generare = 0, dreapta_generare = 3000000

        //std::random_device rd;
        std::mt19937 rng_mt(std::time(nullptr));
        std::uniform_int_distribution<> distrib(stanga_generare, dreapta_generare);

        for(int i = 0; i < dim_pop; i++){
            int individ = distrib(rng_mt); //generat pe [0, 3000000)

            double nr = (double)(individ + st) / val; // decodificat pe [-1, 2)

            std::vector<int> cod = codificare(individ);
            Individ i1 = Individ(cod, nr, individ, fitness(nr, a, b, c));
            indivizi[i] = i1;
        }
        return indivizi;
    }

    void afisareMatrice(std::vector<Individ> mat){
        for(int i = 0; i < dim_pop; i++){
            std::vector<int> cod = mat[i].getCod();
            if(i+1 < 10) std::cout <<" "<<i+1<<":  ";
            else  std::cout <<i+1<<":  ";

            for(int j = 0; j < NR_GENE ;j ++){
                std::cout << cod[j] << " ";
            }

            std::cout<< " x= " << mat[i].getValoare();
            std::cout << " codificat: " << mat[i].getValoareCod();
            std::cout << " f= " << std::setprecision(15)<< mat[i].getFitness() << "\n";

        }
    }

    // [fitness individ/ suma tuturor fitnesurilor]
    std::vector<double> probabilitateSelectie(){
        double sumaFitness = 0;
        std::vector<double> PS;
        for(auto & i : generatie){
            sumaFitness += i.getFitness();
        }

        for(auto & i : generatie)
        {
            double nr = i.getFitness() / sumaFitness;
            PS.push_back(nr);
        }

        return PS;
    }

    // intervale[curent] = intervale [predecesor] + probabilitate_selectie[curent]
    // probabilitatile au suma 1
    std::vector<double> intervalSelectie(){
        std::vector<double> intervale;
        intervale.push_back(0);
        for(int i = 0; i < probabilitate_selectie.size(); i++){
            intervale.push_back(intervale[i] + probabilitate_selectie[i]);
        }
        return intervale;
    }

    //binary search
    int gasesteInterval(double nr, int st, int dr){
        int mid;
        while( st <= dr ){
            mid = (st +dr) / 2;
            if( interval[mid] < nr )
                st = mid + 1;
            else if( interval[mid] >= nr) {
                if( interval[mid- 1] < nr ){
                    return mid;
                }
                dr = mid - 1;
            }
        }
        return mid;
    }

    // numar random intre 0 si 1 => folosit in intervalul de selectie
    std::vector<Individ> selectie(){
        std::vector<Individ> generatie_selectie;

        if(etapa_curenta > 1) dim_pop--;

        int i = 1;
        while( i<= dim_pop){
            double nr = (float)rand()/RAND_MAX;
            double poz = gasesteInterval(nr, 0, interval.size()-1);

            if(etapa_curenta == 1) std::cout<<"random: "<<nr<<" selectam cromozomul: "<<poz<<"\n";

            generatie_selectie.push_back(generatie[poz-1]);
            i ++;
        }

        return generatie_selectie;
    }

    // indivizii ce trebuie incrucisati
    std::vector<int> pozitiiIncrucisare( std::vector<Individ> generatie_selectie ){
        std::vector<int> indivizi_incrucisare; // pozitiile celor ce trebuie incrucisati

        int i = 1;
        while( i<= dim_pop){
            double nr = (float)rand()/RAND_MAX;

            std::vector<int> cod = generatie_selectie[i-1].getCod();

            if(etapa_curenta == 1){
                std::cout<<"\n"<<i<<": ";
                for( int k=0; k<NR_GENE; k++){
                    std::cout<< cod[k]<<" ";
                }
                std::cout<<"nr= "<<nr;
            }


            if( nr < p_crossover){
                indivizi_incrucisare.push_back( i-1 );

                if(etapa_curenta == 1)std::cout<<" < "<<p_crossover<<" => participa";
            }

            i ++;
        }

        return indivizi_incrucisare;
    }

    // incrucisarea = intre doi indivizi, se interschimba primele k gene
    // se pastreaza schimbarea doar la numerele care raman in intervalul [-1,2)
    void incrucisare( std::vector<Individ> generatie_selectie,  std::vector<int> indivizi_incrucisare){
        std::vector<int> aux_a, aux_b;

        for(int i = 0 ; i<indivizi_incrucisare.size() - 1 ; i = i + 2){
            int breakpoint = rand()%NR_GENE;

            aux_a =  generatie_selectie[indivizi_incrucisare[i]].getCod();
            aux_b =  generatie_selectie[indivizi_incrucisare[i+1]].getCod();

            if( etapa_curenta == 1 ){
                std::cout<<indivizi_incrucisare[i]+1<<" cu "<<indivizi_incrucisare[i+1]+1<<" => ";
                for(int k= 0; k<NR_GENE ; k++)
                    std::cout<<aux_a[k]<<" ";
                std::cout<<"  ";
                for(int k= 0; k<NR_GENE ; k++)
                    std::cout<<aux_b[k]<<" ";
                std::cout<<" breakpoint: "<<breakpoint<<"\n";
            }

            for(int j = 0; j< breakpoint ; j++){
                int aux = aux_a[j];
                aux_a[j] = aux_b[j];
                aux_b[j] = aux;
            }


            if( etapa_curenta == 1 ){
                std::cout<<"Rezultat: ";
                for(int k= 0; k<NR_GENE ; k++)
                    std::cout<<aux_a[k]<<" ";
                std::cout<<"  ";
                for(int k= 0; k<NR_GENE ; k++)
                    std::cout<<aux_b[k]<<" ";
                std::cout<<"\n";
            }


            //( val_cod, (val, f))
            std::pair<int, std::pair<double, double>> a_decod = decodificare(aux_a);
            std::pair<int, std::pair<double, double>> b_decod = decodificare(aux_b);


            if(a_decod.second.first < dreapta){
                generatie_selectie[indivizi_incrucisare[i]].setCod(aux_a);
                generatie_selectie[indivizi_incrucisare[i]].setValoare( a_decod.second.first);
                generatie_selectie[indivizi_incrucisare[i]].setValoareCod( a_decod.first);
                generatie_selectie[indivizi_incrucisare[i]].setFitness( a_decod.second.second);
            }

            if(b_decod.second.first < dreapta){
                generatie_selectie[indivizi_incrucisare[i+1]].setCod(aux_b);
                generatie_selectie[indivizi_incrucisare[i+1]].setValoare( b_decod.second.first);
                generatie_selectie[indivizi_incrucisare[i+1]].setValoareCod( b_decod.first);
                generatie_selectie[indivizi_incrucisare[i+1]].setFitness( b_decod.second.second);
            }

        }
    }

    // pentru fiecare gena se verifica daca o sa aibe loc o mutatie
    std::vector<Individ> mutatii(std::vector<Individ> mat){
        srand( time(NULL) );
        for(int i = 0; i < dim_pop; i++){
            std::vector<int> cod = mat[i].getCod();

            for(int j = 0; j < NR_GENE ;j ++){
                double nr = (float)rand()/RAND_MAX;
                if( nr <= p_mutatie ){
                    if(cod[j] == 0) cod[j] = 1;
                    else cod[j] = 0;
                }
            }

            if( mat[i].getCod() != cod){
                if(etapa_curenta == 1)std::cout<<"A fost modificat cromozomul: "<<i+1<<"\n";

                std::pair<int, std::pair<double, double>> aux_cod = decodificare(cod);
                if(aux_cod.second.first < dreapta){
                    mat[i].setCod(cod);
                    mat[i].setValoare( aux_cod.second.first);
                    mat[i].setValoareCod( aux_cod.first);
                    mat[i].setFitness( aux_cod.second.second);
                }
            }
        }

        return mat;
    }

    // pozitia numarului maxim din generatie
    int maximGeneratie( std::vector<Individ> mat){
        double maxim_f, maxim_val;
        int poz;
        for(int i = 0; i < dim_pop; i++){
            if( mat[i].getFitness() > maxim_f){
                maxim_f = mat[i].getFitness();
                maxim_val = mat[i].getValoare();
                poz = i;
            }
        }

    return poz;
    }

    // etapa care contine afisari
    // returneaza individul maxim
    Individ primaEtapa(){
        puteriDoi();

        generatie = generareIndivizi();
        std::cout<<"Populatia initiala:\n";
        afisareMatrice(generatie);

        std::cout << "\nSELECTIE\nProbabilitati de selectie:\n";

        probabilitate_selectie = probabilitateSelectie();

        for(auto i : probabilitate_selectie){
            std::cout << i << " ";
        }

        std::cout << "\n\nIntervale probabilitati de selectie:\n";

        interval = intervalSelectie();
        for(auto i : interval){
            std::cout << i << " ";
        }

        std::cout << "\n\n";

        srand( time(NULL) );

        std::vector<Individ> generatie_selectie = selectie();

        std::cout<<"\nPopulatia dupa selectie:\n";
        afisareMatrice(generatie_selectie);

        std::cout<<"\nINCRUCISARE:";

        std::vector<int> indivizi_incrucisare = pozitiiIncrucisare(generatie_selectie);

        std::cout<<"\n\n";

        incrucisare(generatie_selectie, indivizi_incrucisare);

        std::cout<<"\nPopulatia dupa incrucisare:\n";
        afisareMatrice(generatie_selectie);

        std::cout<<"\nMUTATIE:\n";

        generatie = mutatii(generatie_selectie);

        std::cout<<"\nPopulatia dupa mutatie:\n";
        afisareMatrice(generatie);

        Individ maxim = generatie[maximGeneratie(generatie)];

        std::cout<<"Maximul primei generatii: "<<maxim.getValoare() << " "<< maxim.getFitness()<<"\n";


    return maxim;
    }



public:
    Algoritm(int dimPop, int stanga, int dreapta, int a, int b, int c, int precizie, double pCrossover, double pMutatie,
             int nrEtape) : dim_pop(dimPop), stanga(stanga), dreapta(dreapta), a(a), b(b), c(c), precizie(precizie),
                            p_crossover(pCrossover), p_mutatie(pMutatie), nr_etape(nrEtape) {}
    double functie(){
        etapa_curenta = 1;
        double valoare_maxim;

        Individ maxim = primaEtapa();

       while( etapa_curenta < nr_etape ){
           //SELECTIE
           generatie.push_back(maxim);

           dim_pop ++;

           etapa_curenta++;

           probabilitate_selectie = probabilitateSelectie();

           interval = intervalSelectie();

           srand( time(NULL) );

           std::vector<Individ> generatie_selectie = selectie();

           //INCRUCISARE
           std::vector<int> indivizi_incrucisare = pozitiiIncrucisare(generatie_selectie);

           incrucisare(generatie_selectie, indivizi_incrucisare);

           //MUTATIE
           generatie = mutatii(generatie_selectie);

           //MAXIM
           Individ maxim_nou = generatie[maximGeneratie(generatie)];

           if(maxim_nou.getFitness() > maxim.getFitness()){
               maxim = maxim_nou;
           }

           std::cout<<maxim.getValoare() << " "<< maxim.getFitness()<<"\n";

       }

        return valoare_maxim;
    }

};

int main() {

    int dim_pop, stanga, dreapta, a, b, c, precizie, nr_etape;
    double  p_crossover, p_mutatie;

    f >> dim_pop >> stanga >> dreapta >> a >> b >> c;
    f >> precizie >> p_crossover >> p_mutatie >> nr_etape;

    Algoritm Prb = Algoritm(dim_pop, stanga, dreapta, a, b, c, precizie,  p_crossover, p_mutatie, nr_etape);

    Prb.functie();

    return 0;
}

