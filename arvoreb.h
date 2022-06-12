#ifndef ARVOREB_H_INCLUDED
#define ARVOREB_H_INCLUDED

using namespace std;

/*void lendo_arquivo(){

    ifstream arquivo;

    string linha;

    //Abrindo arquivo poxfixa.in conforme solicitado
    arquivo.open ("posfixa.in.txt");

    if(arquivo.is_open()){
        while(getline(arquivo, linha)){
            cout << linha << endl;
        }
        arquivo.close();
    }else{
        cout << "Nao foi possível abrir posfixa.txt" << endl;
    }

    cout << linha[1] << ", " << linha[2];

}*/

//Construindo a àrvore binária
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

//Imprime em notação prefixa
char imprimePrefixa(Node* raiz)
{
    ofstream arquivoPreOrdem;

    arquivoPreOrdem.open ("prefixa.out.txt", ios::app);

	if (raiz == nullptr) {
 		return 0;
	}

    cout << raiz->data;
    imprimePrefixa(raiz->esq);
    imprimePrefixa(raiz->dir);

}

// Essa função vai ver se é um operador ou nao
bool ehOperador(char op) {
	return (op == '+' || op == '-' || op == '*' || op == '/');
}

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



#endif // ARVOREB_H_INCLUDED
