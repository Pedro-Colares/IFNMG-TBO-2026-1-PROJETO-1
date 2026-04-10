#ifndef FILMES_H
#define FILMES_H

#include "FILME.h"
#include<string>
#include<vector>

class Filmes{

    private:
    vector<Filme> lista;
      unordered_map<string, Filme*> mapa;

    public:
      Filmes();
      virtual ~Filmes();

      void carregar(string arquivo);
      Filme* buscarPorId(string id);

      string genero;
      int min, max;
      string tipo;
      
      vector<Filme*> filtrarPorGenero(string genero);
      vector<Filme*> filtrarPorAno(int min, int max);
      vector<Filme*> filtrarPorDuracao(int min, int max);
      vector<Filme*> filtrarPorTipo(string tipo);

};
#endif 