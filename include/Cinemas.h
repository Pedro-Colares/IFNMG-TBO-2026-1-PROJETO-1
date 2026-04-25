#ifndef CINEMAS_H
#define CINEMAS_H

#include "CINEMA.h"
#include "Filmes.h"
#include<vector>
#include<unordered_map>

using namespace std;

class Cinemas{
    private:
      vector<Cinema*>lista;
    
    public:
      Cinemas();
      ~Cinemas();

      void carregar(string arquivo);

      vector<Cinema*>filtrarPorPreco(double max);
      vector<Cinema*>filtrarPorDistancia(int x, int y, int distanciaMaxima);

      vector<Cinema*>filtrarPorGenero(string genero, Filmes& filmes);
      vector<Cinema*>filtrarPorTipo(string tipo, Filmes& filmes);
      vector<Cinema*>filtrarPorAno(int min, int max, Filmes& filmes);
      vector<Cinema*>filtrarPorDuracao(int min, int max, Filmes& filmes);

      vector<Cinema*>buscarPorFilme(string idFilme);
      vector<Cinema*> intersecao(vector<Cinema*> a, vector<Cinema*> b);
      vector<Cinema*> uniao(vector<Cinema*> a, vector<Cinema*> b);
      vector<Cinema*> filtrarConsulta(string consulta, Filmes& filmes);
};
#endif