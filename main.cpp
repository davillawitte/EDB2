#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <stdlib.h>
#include <stack>

#include "arvoreb.h"

//TRABALHO DE EDB2 - ALUNA: ROSANGELA D AVILLA

using namespace std;

int main()
{
    //lendo_arquivo();

    ofstream arquivoPreOrdem;
    arquivoPreOrdem.open("prefixa.out.txt");

    ifstream posfixa;
    ofstream aval, prefixa, infixa;

    string linha;

    //Abrindo arquivo poxfixa.in conforme solicitado
    posfixa.open ("posfixa.in.txt");

    if(posfixa.is_open()){

        while(getline(posfixa, linha)){ // pegando linha por linha do arquivo, pois cada linha é uma expressão

            Node* raiz = construct(linha);

            cout << endl << endl << "Expressao em pos-fixa: ";
            imprimePosfixa(raiz);

            cout << endl << "Expressao em in-fixa: ";
            imprimeInfixa(raiz);

            cout << endl << "Expressao em pre-fixa: ";
            imprimePrefixa(raiz);

        }

            posfixa.close(); // fechando arquivo posfixa

        }else{
        cout << "Nao foi possível abrir posfixa.txt" << endl;
    }

    return 0;
}
