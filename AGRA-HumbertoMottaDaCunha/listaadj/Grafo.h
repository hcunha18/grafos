#include "Lista.h" 
#include "FPHeapMinIndireto.h"
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <array>
#include <cstring>
#include <float.h>
using namespace std;

	class Grafo {
	public:
		class Aresta {
	  private:
	    int v1, v2, peso; 
	  public: 
	    Aresta (int v1, int v2, int peso) {
	      this->v1 = v1; this->v2 = v2; this->peso = peso;
	    }
	    int _peso () { return this->peso; }
	    int _v1 () { return this->v1; }
	    int _v2 () { return this->v2; }
	    ~Aresta(){}
	  };
	private:	
		class Celula {
    friend class Grafo;
    friend ostream& operator<< (ostream& out, const Celula& celula) {
      out << "vertice:" << celula.vertice << endl;
      out << "peso:"    << celula.peso    << endl;
      return out;
    }    
		private:	
	    int vertice, peso;
	  public:
	    Celula (int v, int p) {
	    	this->vertice = v; this->peso = p;
	    }
	    Celula (const Celula& cel) { *this = cel; }      
      bool operator== (const Celula& celula) const {
        return this->vertice == celula.vertice;
      }
      bool operator!= (const Celula& celula) const {
        return this->vertice != celula.vertice;
      }
      const Celula& operator= (const Celula& cel) {     
        this->vertice = cel.vertice; this->peso = cel.peso;
        return *this; // @{\it permite atribui\c{c}\~oes encadeadas}@
      }      
      ~Celula () {}	    
	  }; 
    Lista<Celula> *adj; 
    int numVertices;
  public:
    Grafo( istream &in );
    Grafo (int numVertices);	  
    Grafo (int numVertices, int numArestas);	  
	  void insereAresta (int v1, int v2, int peso);
	  bool existeAresta (int v1, int v2) const;
	  bool listaAdjVazia (int v) const;
    Aresta *lerAresta ();
	  Aresta *primeiroListaAdj (int v);
	  Aresta *proxAdj (int v);
	  Aresta *retiraAresta (int v1, int v2);
	  void imprime () const ;
	  int _numVertices () const;
	  Grafo *grafoTransposto ();
    Grafo *grafoNaoOrientado ();
    int grauVertice();
    void buscaProfundidade();
    void visitaDfs(int u, int *cor, int *antecessor);
    bool grafoAciclico();
    bool aciclico(int u, int *cor, int *antecessor);
    void ordenacaoTopologica();
    void topologica(int u, int *cor, int *antecessor, vector<int> &L);
    ~Grafo (); 
	};

  Grafo::Grafo( istream &in )
  {
   int v1, v2, peso, numVertices;
   in >> numVertices;
  
   this->adj = new Lista<Celula>[numVertices]; 
   this->numVertices = numVertices; 	  	  	
   
    while (in>>v1>>v2>>peso) {
      Grafo::Aresta *a = new Grafo::Aresta (v1, v2, peso);
      this->insereAresta (a->_v1 (), a->_v2 (), a->_peso ()); 
      delete a;
    }
  }

  Grafo::Grafo (int numVertices) {
  	this->adj = new Lista<Celula>[numVertices]; 
  	this->numVertices = numVertices; 	  	
  }	  
  Grafo::Grafo (int numVertices, int numArestas) {
  	this->adj = new Lista<Celula>[numVertices]; 
  	this->numVertices = numVertices; 	  	
  }	  

  Grafo::Aresta *lerAresta () {
    cout << "Aresta:" << endl;
    cout << "  V1:"; int v1 = 0;
    cin >> v1;
    cout << "  V2:"; int v2 = 0;
    cin >> v2;
    cout << "  Peso:"; int peso = 0;
    cin >> peso;
    return new Grafo::Aresta (v1, v2, peso);
  }

  void Grafo::insereAresta (int v1, int v2, int peso) {
    Celula item (v2, peso); 
    this->adj[v1].insere (item); 
  }
  bool Grafo::existeAresta (int v1, int v2) const {
    Celula item (v2, 0);
    return (this->adj[v1].pesquisa(item) != NULL);
  }
  bool Grafo::listaAdjVazia (int v) const {
		return this->adj[v].vazia ();  
  }	  
  Grafo::Aresta *Grafo::primeiroListaAdj (int v) {
    // @{\it Retorna a primeira aresta que o v\'ertice v participa ou}@
    // @{\it {\bf NULL} se a lista de adjac\^encia de v for vazia}@ 
    Celula *item = this->adj[v]._primeiro ();    
    return item != NULL ? new Aresta(v,item->vertice,item->peso) : NULL;
  }
  Grafo::Aresta *Grafo::proxAdj (int v) {
    // @{\it Retorna a pr\'oxima aresta que o v\'ertice v participa ou}@
    // @{\it {\bf NULL} se a lista de adjac\^encia de v estiver no fim}@
    Celula *item = this->adj[v].proximo ();    
    return item != NULL ? new Aresta(v,item->vertice,item->peso) : NULL;
  }
  Grafo::Aresta *Grafo::retiraAresta (int v1, int v2) {
    Celula chave (v2, 0);
    Celula *item = this->adj[v1].retira (chave);
    Aresta *aresta = item != NULL ? new Aresta(v1,v2,item->peso) : NULL;
    delete item; return aresta;
  }
  void Grafo::imprime () const {
    for (int i = 0; i < this->numVertices; i++) { 
      cout << i << ":";
      Celula *item = this->adj[i]._primeiro ();
      while (item != NULL) {
        cout << "  " << item->vertice << " (" <<item->peso<< ")";
        item = this->adj[i].proximo ();
      }
      cout << endl;
    }
  }
  int Grafo::_numVertices () const { return this->numVertices; }
  
  
  Grafo *Grafo::grafoTransposto () {  	
    Grafo *grafoT = new Grafo (this->numVertices); 
    for (int v = 0; v < this->numVertices; v++)
      if (!this->listaAdjVazia (v)) {
        Aresta *adj = this->primeiroListaAdj (v);
        while (adj != NULL) {
          grafoT->insereAresta (adj->_v2 (), adj->_v1 (), adj->_peso ());
          delete adj;
          adj = this->proxAdj (v);
        }
      }
    return grafoT;
  }
  Grafo *Grafo::grafoNaoOrientado () {
    Grafo *grafoT = new Grafo (this->numVertices); 
    for (int v = 0; v < this->numVertices; v++)
      if (!this->listaAdjVazia (v)) {
        Aresta *adj = this->primeiroListaAdj (v);
        while (adj != NULL) {
          grafoT->insereAresta (adj->_v2 (), adj->_v1 (), adj->_peso ());
          grafoT->insereAresta (adj->_v1 (), adj->_v2 (), adj->_peso ());
          delete adj;
          adj = this->proxAdj (v);
        }
      }
    return grafoT;

  }

  void Grafo::buscaProfundidade(){
    int *cor = new int[this->_numVertices()];
    int *antecessor = new int[this->_numVertices()];
    for (int i=0; i<this->numVertices; i++){
      cor[i] = 0;
      antecessor[i] = -1;
    }
    for (int u = 0; u<this->numVertices; u++){
      if (cor[u] == 0)
        this->visitaDfs(u, cor, antecessor);
    }
  }


  void Grafo::visitaDfs(int u, int *cor, int *antecessor){
    cor[u] = 1;
    cout << "cinza: "<< u << endl;
    if (!this->listaAdjVazia (u)) {
      Aresta *adj = this->primeiroListaAdj (u);
      while (adj != NULL) {
        int v = adj->_v2();
        if(cor[v] == 0){
          antecessor[v] = u;
          this->visitaDfs(v, cor, antecessor);
        } 
        delete adj;
        adj = this->proxAdj(u);
        }
    }
    cor[u] = 2;
    cout << "preto: " << u << endl;
  }

  bool Grafo::grafoAciclico(){
    int *cor = new int[this->_numVertices()];
    int *antecessor = new int[this->_numVertices()];
    for(int i=0; i<this->numVertices; i++){
      cor[i] = 0;
      antecessor[i] = -1;
    }
    bool verification = 0;
    for (int u=0; u<this->numVertices; u++){
      if (cor[u] == 0)
        verification = this->aciclico(u, cor, antecessor);
      if (verification == 1)
        return verification;
    }
    return verification;
  }

  bool Grafo::aciclico(int u, int *cor, int *antecessor){
    cor[u] = 1;
    if (!this->listaAdjVazia (u)) {
      Aresta *adj = this->primeiroListaAdj (u);
      while (adj != NULL) {
        int v = adj->_v2();
        if(cor[v] == 1){
          return 1;
        }
        if(cor[v] == 0){
          antecessor[v] = u;
          this->aciclico(v, cor, antecessor);
        } 
        delete adj;
        adj = this->proxAdj(u);
        }
    }
    cor[u] = 2;
    return 0;
  }

  void Grafo::ordenacaoTopologica(){
    Grafo *grafoT = this->grafoTransposto();
    int *cor = new int[grafoT->_numVertices()];
    int *antecessor = new int[grafoT->_numVertices()];
    vector < int > lista;
    
    for (int i=0; i<grafoT->numVertices; i++){
      cor[i] = 0;
      antecessor[i] = -1;
    }
    for (int u = 0; u<grafoT->numVertices; u++){
      if (cor[u] == 0)
        grafoT->topologica(u, cor, antecessor, lista);
    }
    for (int i=0; i<grafoT->numVertices;i++){
      cout << lista[i] << endl;
    }

  }

  void Grafo::topologica(int u, int *cor, int *antecessor, vector<int> &L){
    cor[u] = 1;
    if (!this->listaAdjVazia (u)) {
      Aresta *adj = this->primeiroListaAdj (u);
      while (adj != NULL) {
        int v = adj->_v2();
        if(cor[v] == 0){
          antecessor[v] = u;
          this->topologica(v, cor, antecessor, L);
        } 
        delete adj;
        adj = this->proxAdj(u);
        }
    }
    cor[u] = 2;
    L.push_back(u);
    
  }

  Grafo::~Grafo () {
    delete [] this->adj;
  }	  


		
