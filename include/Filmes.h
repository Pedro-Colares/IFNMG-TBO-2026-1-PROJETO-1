#ifndef FILMES_H
#define FILMES_H

#include "FILME.h"
#include<string>
#include<vector>
#include <unordered_map>

using namespace std;

class Filmes{

    private:
    vector<Filme*> listaDireta;
    vector<Filme*> lista;    
    unordered_map<string, vector<Filme*>> mapaGenero; 
    unordered_map<string, vector<Filme*>> mapaTipo;

    public:
      Filmes();
      virtual ~Filmes();

      void carregar(string arquivo);
      Filme* buscarPorId(string id);

      vector<Filme*> filtrarPorGenero(string genero);
      vector<Filme*> filtrarPorAno(int min, int max);
      vector<Filme*> filtrarPorDuracao(int min, int max);
      vector<Filme*> filtrarPorTipo(string tipo);
      vector<Filme*> filtrarConsulta(string consulta);

};
#endif 