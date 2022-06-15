#include <iostream>
#include <fstream>
#include <string.h>
#include <stack>
#include <sstream>
#include <math.h>

//TRABALHO DE EDB2 - UNID 2 - ALUNOS:IVISON FILHO e ROSANGELA D AVILLA

using namespace std;

struct Node
{
	char data;
	Node *esq, *dir;

	Node(char data)
	{
		this->data = data;
		this->esq = this->dir = nullptr;
	};

	Node(char data, Node *esq, Node *dir)
	{
		this->data = data;
		this->esq = esq;
		this->dir = dir;
	};
};

ofstream arquivoPreOrdem("prefixa.out.txt");

//Imprime em notação prefixa
char imprimePrefixa(Node* raiz)
{

	if (raiz == nullptr) {
 		return 0;
	}

    arquivoPreOrdem.put(raiz->data);
    imprimePrefixa(raiz->esq);
    imprimePrefixa(raiz->dir);

}

// Imprime em notação polonesa/posfixa
void imprimePosfixa(Node* raiz)
{
	if (raiz == nullptr) {
		return;
	}

	imprimePosfixa(raiz->esq);
	imprimePosfixa(raiz->dir);
	cout << raiz->data;
}


// Essa função vai ver se é um operador ou nao
bool ehOperador(char op) {
	return (op == '+' || op == '-' || op == '*' || op == '/');
}

ofstream arquivoInfixa("infixa.out.txt");

// Imprime em notação infixa
void imprimeInfixa(Node* raiz)
{

	if (raiz == nullptr) {
		return;
	}

	// Se for um operador, abre parentese
	if (ehOperador(raiz->data)) {
		cout << "(";
	}

	imprimeInfixa(raiz->esq);
	cout << raiz->data;
	imprimeInfixa(raiz->dir);

	// fecha parentese
	if (ehOperador(raiz->data)) {
		cout << ")";
	}
}


// Funcao para construir a árvore >> expressao posfixa
Node* construct(string postfix)
{
	// caso base, quando o tamanho da stack for 0
	if (postfix.length() == 0) {
		return nullptr;
	}

	// criando stack
	stack <Node*> s;

	for (char op: postfix)
	{
		if (ehOperador(op))
		{
			// realizando pop do nó x e do nó y
			Node* x = s.top();
			s.pop();

			Node* y = s.top();
			s.pop();

			// constroi uma nova arvore binaria ( raiz eh um operador)
			Node* node = new Node(op, y, x);

			s.push(node);
		}else {
			s.push(new Node(op));
		}
	}

	return s.top();
}

bool ehFolha(Node* raiz) {
    return raiz->esq == nullptr && raiz->dir == nullptr;
}

// Função que faz o calculo das 'folhas'
int calcfolha(char op, int x, int y)
{
    if (op == '+') { return x + y; }
    if (op == '-') { return x - y; }
    if (op == '*') { return x * y; }
    if (op == '/') { return x / y; }

    return 0;
}

int Resultado(Node* raiz)
{
    // caso base
    if (raiz == nullptr) {
        return 0;
    }

    // ver se é uma folha e faz a conversão de char para int
    if (ehFolha(raiz)) {
        // fazendo a conversão
        stringstream strm;
        strm << raiz->data;
        return stoi(strm.str());
    }

    // calculo recursivo: sub-árvore da esquerda e sub-árvore da direita
    int x = Resultado(raiz->esq);
    int y = Resultado(raiz->dir);

    //função para calculo das folhas x e y (vide função calcFolha())
    return calcfolha(raiz->data, x, y);
}

int main()
{

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

            cout << endl << "RESULTADO: ";
            cout << Resultado(raiz);

            cout << endl << "Expressao em pre-fixa: ";
            cout << imprimePrefixa(raiz);
            arquivoPreOrdem << endl;

        }

            posfixa.close(); // fechando arquivo posfixa

        }else{
        cout << "Nao foi possível abrir posfixa.txt" << endl;
    }

    return 0;
}


