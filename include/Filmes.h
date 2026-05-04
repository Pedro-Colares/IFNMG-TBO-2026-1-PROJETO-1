#ifndef FILMES_H
#define FILMES_H
#include "FILME.h"
#include "Hash.h"
#include "HashSet.h"
#include<string>
#include<vector>
#include "MergeSort.h"
using namespace std;
class Filmes{
    private:
    HashString<Filme*> mapaTitulo;
    vector<Filme*> listaDireta;   
    HashString<vector<Filme*>> mapaGenero; 
    HashString<vector<Filme*>> mapaTipo;
    vector<Filme*> listaPorAno;
    vector<Filme*> listaPorDuracao;
    int BuscaBinariaMenorAno(int valor);
    int BuscaBinariaMaiorAno(int valor);
    int BuscaBinariaMenorDuracao(int valor);  
    int BuscaBinariaMaiorDuracao(int valor);
    public:
      Filmes();
      virtual ~Filmes();
      void carregar(string arquivo);
      Filme* buscarPorId(string id);
      vector<Filme*> filtrarPorGenero(string genero);
      vector<Filme*> filtrarPorAno(int min, int max);
      vector<Filme*> filtrarPorDuracao(int min, int max);
      vector<Filme*> filtrarPorTipo(string tipo);
      Filme* buscarMaisProximo(string id);
      vector<Filme*> intersecao(vector<Filme*> a, vector<Filme*> b);
      vector<Filme*> uniao(vector<Filme*> a, vector<Filme*> b);
      vector<Filme*> filtrarConsulta(string consulta);
      vector<string> tokenizar(string s);
      vector<Filme*> aplicarFiltro(string palavra);
      vector<Filme*> avaliarConsultaSimples(vector<string> tokens);
      Filme* buscarPorTitulo(string titulo);
};

bool comparaFilmeAno(Filme* a, Filme* b);
bool comparaFilmeDuracao(Filme* a, Filme* b);

#endif