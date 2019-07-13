#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string>

using namespace std;

//Branje datoteke - podamo pot do datoteke in vektor v katerega bomo zapisovali brana števila
void readFile(string pot, vector<unsigned char> *vect){
    ifstream vhodnaDatoteka;
    int steviloKateregaSprotiBeremo;

    vhodnaDatoteka.open(pot);
    // če se datoteka ni uspešno odprla javimo napakp
    if(!vhodnaDatoteka){
        cout << "Napaka pri odpiranju datoteke!\n" << endl;
        exit(1);
    }
    
    // beremo datoteko dokler ne pridemo do konca...
    while(vhodnaDatoteka.eof() == 0){
        //in sproti shranjujemo števila v vektor
        vhodnaDatoteka >> steviloKateregaSprotiBeremo;
        vect->push_back(steviloKateregaSprotiBeremo);
    }
}
//prejme unsigned char in iz njega pusha bit, nato se izvede logični & z enko, da se dobi ven bit 1
bool getBit(unsigned char x, int k){
    return (x >> k) & 1;
}

void writeToFile(vector<unsigned char> A){
    ofstream izhodnaDatoteka("out.txt");
    
    if(!izhodnaDatoteka){
        cout<<"Napaka pri ustvarjanju izhodne datoteke!";
    }

    for(int i=0; i<A.size(); i++){
        izhodnaDatoteka << (int)A[i] << " ";
    }
}

int main(int argc, char **argv){
    //inicializiramo začetni vektor
    vector<unsigned char> A;//B;
    //preberemo vsebino datoteke v vektor A
    readFile(argv[1], &A);
    //postavimo vektor b na velikost Aja
    vector<unsigned char> B(A.size(), 0);

    //za vseh 8bitov...
    for(int k=0; k<8; k++){
        //prej postavimo C, kamor bomo šteli bite 0 in 1
        unsigned int C[2] = {0,0};
        //...gremo skozi A in prištejemo ustrezni bit kamor je potrebno 
        for(int i = 0; i<A.size(); i++){
            //kot številko indeksa h kateremu prištevamo dodamo ustrezen bit, ki je 1 ali 0
            C[getBit(A[i], k)]++;
        }

        //komulativno seštejemo ničle in enke
        C[1] += C[0];
        
        //gremo od zadnjega mesta in...
        for (int i = A.size()-1; i>=0; i--){
            //v vektor B shranjujemo bite
            B[ C[ getBit(A[i], k)] -1] = A[i];
            //dekrementiramo C
            C[getBit(A[i], k)]--;

        }
        //uredimo A in B
        swap(A,B);

    }
    //zapišemo v datoteko
    writeToFile(A);    

    

    return 0;
}