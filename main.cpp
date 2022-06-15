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

//Imprime em nota��o prefixa
char imprimePrefixa(Node* raiz)
{

	if (raiz == nullptr) {
 		return 0;
	}

    arquivoPreOrdem.put(raiz->data);
    imprimePrefixa(raiz->esq);
    imprimePrefixa(raiz->dir);

}

// Imprime em nota��o polonesa/posfixa
void imprimePosfixa(Node* raiz)
{
	if (raiz == nullptr) {
		return;
	}

	imprimePosfixa(raiz->esq);
	imprimePosfixa(raiz->dir);
	cout << raiz->data;
}


// Essa fun��o vai ver se � um operador ou nao
bool ehOperador(char op) {
	return (op == '+' || op == '-' || op == '*' || op == '/');
}

ofstream arquivoInfixa("infixa.out.txt");

// Imprime em nota��o infixa
void imprimeInfixa(Node* raiz)
{

	if (raiz == nullptr) {
		return;
	}

	// Se for um operador, abre parentese
	if (ehOperador(raiz->data)) {
		arquivoInfixa << "(";
		cout << "(";
	}

	imprimeInfixa(raiz->esq);
	arquivoInfixa << raiz->data;
	cout << raiz->data;
	imprimeInfixa(raiz->dir);

	// fecha parentese
	if (ehOperador(raiz->data)) {
		arquivoInfixa << ")";
		cout << ")";
	}
}


// Funcao para construir a �rvore >> expressao posfixa
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
			// realizando pop do n� x e do n� y
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

// Fun��o que faz o calculo das 'folhas'
int calcfolha(char op, int x, int y)
{
    if (op == '+') { return x + y; }
    if (op == '-') { return x - y; }
    if (op == '*') { return x * y; }
    if (op == '/') { return x / y; }

    return 0;
}

ofstream result("aval.out.txt");

int Resultado(Node* raiz)
{
    // caso base
    if (raiz == nullptr) {
        return 0;
    }

    // ver se � uma folha e faz a convers�o de char para int
    if (ehFolha(raiz)) {
        // fazendo a convers�o
        stringstream strm;
        strm << raiz->data;
        return stoi(strm.str());
    }

    // calculo recursivo: sub-�rvore da esquerda e sub-�rvore da direita
    int x = Resultado(raiz->esq);
    int y = Resultado(raiz->dir);

    //fun��o para calculo das folhas x e y (vide fun��o calcFolha())
    return calcfolha(raiz->data, x, y);
}

int main()
{

    ifstream posfixa;
    ofstream aval, prefixa, infixa;

    string linha;

	if(arquivoPreOrdem.is_open()){
		cout << "arquivoPreOrdem: aberto com sucesso!" << endl;
	}else{
		cout << "arquivoPreOrdem: Erro na abertura do arquivo" << endl;
	}

	if(arquivoInfixa.is_open()){
		cout << "arquivoInfixa: aberto com sucesso!" << endl;
	}else{
		cout << "arquivoInfixa: Erro na abertura do arquivo" << endl;
	}

	if(result.is_open()){
		cout << "result: aberto com sucesso!" << endl;
	}else{
		cout << "result: Erro na abertura do arquivo" << endl;
	}

    //Abrindo arquivo poxfixa.in conforme solicitado
    posfixa.open ("posfixa.in.txt");

    if(posfixa.is_open()){

        while(getline(posfixa, linha)){ // pegando linha por linha do arquivo, pois cada linha � uma express�o

            Node* raiz = construct(linha);

            cout << endl << endl << "Expressao em pos-fixa: ";
            imprimePosfixa(raiz);

            cout << endl << "Expressao em in-fixa: ";
            imprimeInfixa(raiz);
			arquivoInfixa << endl;

            cout << endl << "RESULTADO: ";
			result << Resultado(raiz) << endl;
            cout << Resultado(raiz);

			

            cout << endl << "Expressao em pre-fixa: ";
            cout << imprimePrefixa(raiz);
            arquivoPreOrdem << endl;

        }
			//fecha os respectivos arquivos
            posfixa.close(); 
			arquivoInfixa.close(); 
			arquivoPreOrdem.close();
			result.close();

        }else{
        cout << "Nao foi poss�vel abrir posfixa.txt" << endl;
    }

    return 0;
}


