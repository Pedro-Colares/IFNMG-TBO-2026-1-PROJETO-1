#include "Cinemas.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>
#include <unordered_set>

using namespace std;

static string limpar(string s){
    while(!s.empty() && (s[0] == ' ' || s[0] == '\t'))
        s.erase(0, 1);
    while(!s.empty() && (s.back() == ' ' || s.back() == '\t' || s.back() == '\r' || s.back() == '\n'))
        s.pop_back();
    return s;
}

static int extrairNumeroId(string id) {
    if (id.size() < 2) return 0;
    string num = "";
    for(char c : id) if(isdigit(c)) num += c;
    try {
        return stoi(num);
    } catch (...) {
        return 0;
    }
}

Cinemas::Cinemas(){}

Cinemas::~Cinemas(){
    for(int i = 0; i < lista.size(); i++){
        delete lista[i];
    }
    lista.clear();
}

void Cinemas::carregar(string arquivo) {
    ifstream file(arquivo);
    string linha;

    if (!file.is_open()) return;

    getline(file, linha);

    while (getline(file, linha)) {
        if (linha.empty()) continue;

        stringstream ss(linha);
        string id, nome, xStr, yStr, precoStr, resto;

        getline(ss, id, ',');
        getline(ss, nome, ',');
        getline(ss, xStr, ',');
        getline(ss, yStr, ',');
        getline(ss, precoStr, ',');
        
        getline(ss, resto);

        Cinema* c = new Cinema();
        c->setId(limpar(id));
        c->setNome(limpar(nome));
        c->setX(stoi(limpar(xStr)));
        c->setY(stoi(limpar(yStr)));
        c->setPreco(stod(limpar(precoStr)));

        stringstream ssFilmes(resto);
        string filmeId;
        while (getline(ssFilmes, filmeId, ',')) {
            filmeId = limpar(filmeId);
            if (!filmeId.empty()) {
                c->addFilme(filmeId);
            }
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
        long long dx = c->getX() - x;
        long long dy = c->getY() - y;
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
        bruto -= 1;
        string novoId = "tt" + to_string(bruto);
        if(novoId.length() < id.length()){
            string padding(id.length() - novoId.length(), '0');
            novoId = "tt" + padding + to_string(bruto);
        }
        f = filmes.buscarPorId(novoId);
        if(f != nullptr) return f;
        if(bruto < (extrairNumeroId(id) - 100)) break;
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