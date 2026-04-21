#include "Cinemas.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>

using namespace std;

Cinemas::Cinemas(){}
Cinemas::~Cinemas(){
    for(int i=0; i<lista.size(); i++){
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
        c->setX(stoi(xStr));
        c->setY(stoi(yStr));
        c->setPreco(stod(precoStr));
        
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
    vector<Cinema*>resultado;
    for(Cinema* c: lista){
        if(c->getPreco() <= max){
            resultado.push_back(c);
        }
    }

    return resultado;
}

vector<Cinema*> Cinemas::filtrarPorDistancia(int x, int y, int distanciaMaxima){
    vector<Cinema*>resultado;
    for(Cinema* c: lista){
        int distanciaX = c->getX() - x;
        int distanciaY = c->getY() - y;
        double distancia = sqrt(distanciaX*distanciaX + distanciaY*distanciaY);

        if(distancia <= distanciaMaxima){
            resultado.push_back(c);
        }
    }

    return resultado;
}

vector<Cinema*> Cinemas::filtrarPorGenero(string genero, Filmes& filmes){
    vector<Cinema*>resultado;
    for(Cinema* c: lista){
        for(string id: c->getFilmes()){
            Filme* f = filmes.buscarPorId(id);

            if(f != nullptr && f->temGenero(genero)){
                resultado.push_back(c);
                break;
            }
        }
    }

    return resultado;
}

vector<Cinema*> Cinemas::filtrarPorTipo(string tipo, Filmes& filmes){
    vector<Cinema*>resultado;
    for(Cinema* c: lista){
        for(string id: c->getFilmes()){
            Filme* f = filmes.buscarPorId(id);

            if(f != nullptr && f->ehDoTipo(tipo)){
                resultado.push_back(c);
                break;
            }
        }
    }
    return resultado;
}

vector<Cinema*> Cinemas::filtrarPorAno(int min, int max, Filmes& filmes){
    vector<Cinema*>resultado;
    for(Cinema* c: lista){
        for(string id: c->getFilmes()){
            Filme* f = filmes.buscarPorId(id);

            if(f != nullptr && f->estaNoIntervaloAno(min, max)){
                resultado.push_back(c);
                break;
            }
        }
    }

    return resultado;
}

vector<Cinema*> Cinemas::filtrarPorDuracao(int min, int max, Filmes& filmes){
    vector<Cinema*>resultado;
    for(Cinema* c: lista){
        for(string id: c->getFilmes()){
            Filme* f = filmes.buscarPorId(id);

            if(f != nullptr && f->estaNoIntervaloDuracao(min, max)){
                resultado.push_back(c);
                break;
            }
        }
    }

    return resultado;
}

vector<Cinema*> Cinemas::buscarPorFilme(string idFilme){
    vector<Cinema*>resultado;
    for(Cinema* c: lista){
        if(c->temFilme(idFilme)){
            resultado.push_back(c);
        }
    }
    return resultado;
}