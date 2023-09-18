#include "listaadj/Grafo.h" 
#include <fstream>
using namespace std;

int main (int argc, char **argv) 
{
    ifstream in ("input.txt");
    Grafo *grafo = new Grafo (in);
    // grafo->imprime ();  

    //Ex1: criar e imprimir grafo transposto.
    // Grafo *grafo_transposto = new Grafo(7);
    // grafo_transposto = grafo -> grafoTransposto();
    // grafo_transposto -> imprime();

    //Ex2: Criar e imprimir um grafo não orientado.
    // Grafo *grafo_nao_direcionado = grafo -> grafoNaoOrientado();
    // grafo_nao_direcionado->imprime();

    //Ex3: Ler e inserir nova aresta, verificando se ela já existe.
    // bool existente = 1;
    // Grafo::Aresta *aresta = lerAresta();
    // existente = grafo->existeAresta(aresta->_v1(), aresta->_v2());
    // if (existente == 1) {
    //     cout << "aresta já presente no grafo";
    // }
    // else {
    //     cout << "aresta não presente no grafo";
    //     grafo->insereAresta(aresta->_v1(), aresta->_v2(), aresta->_peso());
    // }
    // grafo->imprime();

    //Ex4: Ler e remover uma aresta, verificando se ela já existe.
    // bool existente = 1;
    // Grafo::Aresta *aresta = lerAresta();
    // existente = grafo->existeAresta(aresta->_v1(), aresta->_v2());
    // if (existente == 1) {
    //     aresta = grafo->retiraAresta(aresta->_v1(), aresta->_v2());
    //     cout << "aresta presente no grafo";
    // }
    // else {
    //     cout << "aresta não presente no grafo";
    // }

    //Ex5: Imprimir uma lista adjacente de um determinado vértices.
    // implementação da lista
    // int v = 0;
    // Grafo::Aresta *aresta = grafo->primeiroListaAdj(v);
    // cout << "verticie passado   " << aresta->_v1() << "\n";
    // while (aresta != NULL)
    // {
    //     cout << "proximo vertice  " << aresta->_v2() << "\n";
    //     aresta = grafo->proxAdj(aresta->_v1());
    // }
    
    // implementação da matriz
    // a implementar

    // Ex: 6 Encontrando Grau do vertice :: Matriz
    // para testar o grafo transoforamar em não direcionado
    // Grafo *grafo_nao_direcionado = grafo->grafoNaoDirecionado();
    // cout << grafo_nao_direcionado->grauVertice(0);

    // Ex: 7 Verificação se o grafo é completo
    // cout << grafo_nao_direcionado->completo();

    // Ex: 8 Verificação se o grafo é regular
    // cout << grafo_nao_direcionado->regular();

    // Ex: 9 Verificar se é euleriano
    // cout << grafo_nao_direcionado->euleriano();

    // Ex: 10 Verificar se é subeuleriano
    // cout << grafo_nao_direcionado->subeuleriano();

    // Ex: 11 verificar se é direcionado
    // if(grafo_nao_direcionado->direcionado() == 0)
    //     cout << "não é direcionado";
    // else cout << "direcionado";

    // cout << grafo_nao_direcionado->direcionado();
    // grafo->buscaProfundidade();

    // verificação se um grafo é ciclico 
    // if (grafo->grafoAciclico() == 1)
    //     cout << "Grafo é Ciclico" << endl;
    // if (grafo->grafoAciclico() == 0)
    //     cout << "Grafo é Aciclico" << endl;
    
    // cout << endl;
    
    // verificação topologica
    // cout << "Ordenação Topologica: "<< endl;
    // grafo->ordenacaoTopologica();

    // cout << endl;

    // obtendo o número de componentes de um grafo
    // int k = grafo->nComponentes();
    // cout << "Número de Componentes: " << k << endl;

    // grafo->buscaLargura();

    grafo->caminhoMaisCurto(2, 0);
}
