#ifndef CINEMAS_H
#define CINEMAS_H

#include <vector>
#include <string>
#include <unordered_map>
#include "CINEMA.h"
#include "FILME.h"
#include "Filmes.h"

using namespace std;

class Cinemas{
private:
    vector<Cinema*> lista;
    unordered_map<string, Cinema*> mapa;
    unordered_map<string, vector<Cinema*>> mapaFilme;

    string limpar(string s);

public:
    Cinemas();
    ~Cinemas();

    void carregar(string arquivo);

    Cinema* buscarPorId(string id);

    Cinema* buscarPorIdMaisProximo(string id);

    vector<Cinema*> getTodos();

    vector<Cinema*> buscarPorFilme(string idFilme);

    vector<Cinema*> filtrarPorPreco(double max);
    vector<Cinema*> filtrarPorDistancia(int x, int y, double maxDist);

    vector<Cinema*> filtrarPorGenero(string genero, Filmes& filmes);
    vector<Cinema*> filtrarPorTipo(string tipo, Filmes& filmes);
    vector<Cinema*> filtrarPorAno(int min, int max, Filmes& filmes);
    vector<Cinema*> filtrarPorDuracao(int min, int max, Filmes& filmes);

    vector<Cinema*> intersecao(vector<Cinema*> a, vector<Cinema*> b);
    vector<Cinema*> uniao(vector<Cinema*> a, vector<Cinema*> b);
};

#endif