#include "Cinemas.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>
#include <unordered_set>

using namespace std;

static int safeStoi(string s){
    if(s == "" || s == "\\N") return 0;
    try{
        return stoi(s);
    }catch(...){
        return 0;
    }
}

static double safeStod(string s){
    if(s == "" || s == "\\N") return 0.0;
    try{
        return stod(s);
    }catch(...){
        return 0.0;
    }
}

static int extrairNumeroId(string id){
    if(id.size() < 3) return 0;
    string num = id.substr(2);
    return safeStoi(num);
}


Cinemas::Cinemas(){}

Cinemas::~Cinemas(){
    for(int i = 0; i < lista.size(); i++){
        delete lista[i];
    }
    lista.clear();
}

void Cinemas::carregar(string arquivo){
    ifstream file(arquivo);
    string linha;

    if(!file.is_open()){
        cout << "Erro ao abrir o arquivo!" << endl;
        return;
    }

    while(getline(file, linha)){
        if(linha.empty()) continue;

        stringstream ss(linha);
        string id, nome, xStr, yStr, precoStr, filmesStr;

        getline(ss, id, '\t');
        getline(ss, nome, '\t');
        getline(ss, xStr, '\t');
        getline(ss, yStr, '\t');
        getline(ss, precoStr, '\t');
        getline(ss, filmesStr, '\t');

        Cinema* c = new Cinema();
        c->setId(id);
        c->setNome(nome);

        c->setX(safeStoi(xStr));
        c->setY(safeStoi(yStr));
        c->setPreco(safeStod(precoStr));

        stringstream ssFilmes(filmesStr);
        string filmeId;

        while(getline(ssFilmes, filmeId, ',')){
            c->addFilme(filmeId);
        }

        lista.push_back(c);
    }

    file.close();
}

vector<Cinema*> Cinemas::filtrarPorPreco(double max){
    vector<Cinema*> resultado;

    for(Cinema* c : lista){
        if(c->getPreco() <= max){
            resultado.push_back(c);
        }
    }

    return resultado;
}

vector<Cinema*> Cinemas::filtrarPorDistancia(int x, int y, int distanciaMaxima){
    vector<Cinema*> resultado;

    for(Cinema* c : lista){
        int dx = c->getX() - x;
        int dy = c->getY() - y;

        double dist = sqrt(dx*dx + dy*dy);

        if(dist <= distanciaMaxima){
            resultado.push_back(c);
        }
    }

    return resultado;
}

Filme* buscarFilmeSeguro(Filmes& filmes, string id){
    Filme* f = filmes.buscarPorId(id);
    if(f != nullptr) return f;

    int bruto = extrairNumeroId(id);

    while(bruto > 0){
        bruto += 2;  
        string novoId = "tt" + to_string(bruto);
        f = filmes.buscarPorId(novoId);
        if(f != nullptr) return f;
    }

    return nullptr;
}

vector<Cinema*> Cinemas::filtrarPorGenero(string genero, Filmes& filmes){
    vector<Cinema*> resultado;

    for(Cinema* c : lista){
        for(string id : c->getFilmes()){

            Filme* f = buscarFilmeSeguro(filmes, id);

            if(f != nullptr && f->temGenero(genero)){
                resultado.push_back(c);
                break;
            }
        }
    }

    return resultado;
}

vector<Cinema*> Cinemas::filtrarPorTipo(string tipo, Filmes& filmes){
    vector<Cinema*> resultado;

    for(Cinema* c : lista){
        for(string id : c->getFilmes()){

            Filme* f = buscarFilmeSeguro(filmes, id);

            if(f != nullptr && f->ehDoTipo(tipo)){
                resultado.push_back(c);
                break;
            }
        }
    }

    return resultado;
}

vector<Cinema*> Cinemas::filtrarPorAno(int min, int max, Filmes& filmes){
    vector<Cinema*> resultado;

    for(Cinema* c : lista){
        for(string id : c->getFilmes()){

            Filme* f = buscarFilmeSeguro(filmes, id);

            if(f != nullptr && f->estaNoIntervaloAno(min, max)){
                resultado.push_back(c);
                break;
            }
        }
    }

    return resultado;
}

vector<Cinema*> Cinemas::filtrarPorDuracao(int min, int max, Filmes& filmes){
    vector<Cinema*> resultado;

    for(Cinema* c : lista){
        for(string id : c->getFilmes()){

            Filme* f = buscarFilmeSeguro(filmes, id);

            if(f != nullptr && f->estaNoIntervaloDuracao(min, max)){
                resultado.push_back(c);
                break;
            }
        }
    }

    return resultado;
}

vector<Cinema*> Cinemas::buscarPorFilme(string idFilme){
    vector<Cinema*> resultado;

    for(Cinema* c : lista){
        if(c->temFilme(idFilme)){
            resultado.push_back(c);
        }
    }

    return resultado;
}

vector<Cinema*> Cinemas::intersecao(vector<Cinema*> a, vector<Cinema*> b){
    vector<Cinema*> resultado;
    unordered_set<Cinema*> setB(b.begin(), b.end());

    for(Cinema* c : a){
        if(setB.count(c)){
            resultado.push_back(c);
        }
    }

    return resultado;
}

vector<Cinema*> Cinemas::uniao(vector<Cinema*> a, vector<Cinema*> b){
    unordered_set<Cinema*> setRes(a.begin(), a.end());

    for(Cinema* c : b){
        setRes.insert(c);
    }

    return vector<Cinema*>(setRes.begin(), setRes.end());
}