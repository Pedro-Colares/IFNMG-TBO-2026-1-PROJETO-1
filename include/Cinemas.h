#ifndef CINEMAS_H
#define CINEMAS_H

#include <vector>
#include <string>
#include <map>
#include "Hash.h"
#include "HashSet.h"
#include "CINEMA.h"
#include "FILME.h"
#include "Filmes.h"

using namespace std;

class Cinemas{

private:
    vector<Cinema*> lista;
    vector<Cinema*> listaOrdenadaPreco;
    HashString<Cinema*> mapa;
    map<double, vector<Cinema*>> indicePreco;
    HashString<vector<Cinema*>> mapaFilme;
    HashString<HashSet<Cinema*>> mapaGenero;
    HashString<HashSet<Cinema*>> mapaTipo;
    HashLong<vector<Cinema*>> grade;
    int TAM = 1000;
    string limpar(string s);

public:
    Cinemas();
    ~Cinemas();
    void carregar(string arquivo, Filmes& filmes);
    Cinema* buscarPorId(string id);
    vector<Cinema*> getTodos();
    vector<Cinema*> buscarPorFilme(string idFilme);
    vector<Cinema*> ordenarPorPreco();
    int buscaBinariaPreco(double max);
    vector<Cinema*> filtrarPorPreco(double max);
    vector<Cinema*> filtrarPorDistancia(int x, int y, double maxDist);
    vector<Cinema*> filtrarPorGenero(string genero, Filmes& filmes);
    vector<Cinema*> filtrarPorTipo(string tipo, Filmes& filmes);
    vector<Cinema*> filtrarPorAno(int min, int max, Filmes& filmes);
    vector<Cinema*> filtrarPorDuracao(int min, int max, Filmes& filmes);
    vector<Cinema*> intersecao(vector<Cinema*> a, vector<Cinema*> b);
    vector<Cinema*> uniao(vector<Cinema*> a, vector<Cinema*> b);
    vector<Cinema*> filtrarConsulta(string consulta, Filmes& filmes);
    vector<string> tokenizar(string s);
    vector<Cinema*> avaliarConsultaSimples(vector<string> tokens, Filmes& filmes);
    vector<Cinema*> aplicarFiltro(string palavra, Filmes& filmes);

};
#endif