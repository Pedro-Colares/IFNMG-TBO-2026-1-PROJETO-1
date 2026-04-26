#include "Cinemas.h"
#include <fstream>
#include <sstream>
#include <cmath>
#include <unordered_set>

using namespace std;

string Cinemas::limpar(string s){
    while(!s.empty() && (s[0]==' ' || s[0]=='\t')) s.erase(0,1);
    while(!s.empty() && (s.back()==' ' || s.back()=='\t' || s.back()=='\r' || s.back()=='\n')) s.pop_back();
    return s;
}

Cinemas::Cinemas(){}

Cinemas::~Cinemas(){
    for(auto c: lista) delete c;
}

vector<Cinema*> Cinemas::getTodos(){
    return lista;
}

void Cinemas::carregar(string arquivo){
    ifstream file(arquivo);
    string linha;

    if(!file.is_open()) return;

    getline(file, linha);

    while(getline(file, linha)){
        if(linha.empty()) continue;

        stringstream ss(linha);
        string id,nome,x,y,preco,filmesStr;

        getline(ss,id,',');
        getline(ss,nome,',');
        getline(ss,x,',');
        getline(ss,y,',');
        getline(ss,preco,',');
        getline(ss,filmesStr);

        Cinema* c = new Cinema();
        c->setId(limpar(id));
        c->setNome(limpar(nome));
        c->setX(stoi(limpar(x)));
        c->setY(stoi(limpar(y)));
        c->setPreco(stod(limpar(preco)));

        lista.push_back(c);
        mapa[c->getId()] = c;

        indicePreco[c->getPreco()].push_back(c);

        stringstream sf(filmesStr);
        string fid;

        while(getline(sf,fid,',')){
            fid = limpar(fid);
            if(fid.empty()) continue;
            c->addFilme(fid);
            mapaFilme[fid].push_back(c);
        }
    }
}

Cinema* Cinemas::buscarPorId(string id){
    if(mapa.count(id)) return mapa[id];
    return nullptr;
}

Cinema* Cinemas::buscarPorIdMaisProximo(string id){
    Cinema* base = buscarPorId(id);
    if(!base) return nullptr;

    Cinema* melhor = nullptr;
    double melhorDist = 1e18;

    for(auto c: lista){
        if(c == base) continue;

        int dx = c->getX() - base->getX();
        int dy = c->getY() - base->getY();
        double dist = sqrt(dx*dx + dy*dy);

        if(dist < melhorDist){
            melhorDist = dist;
            melhor = c;
        }
    }

    return melhor;
}

vector<Cinema*> Cinemas::filtrarPorPreco(double max){
    vector<Cinema*> resultado;

    for(auto &p: indicePreco){
        if(p.first <= max){
            resultado.insert(resultado.end(), p.second.begin(), p.second.end());
        }
    }

    return resultado;
}

vector<Cinema*> Cinemas::filtrarPorDistancia(int x,int y,double distanciaMaxima){
    vector<Cinema*> resultado;

    for(auto c: lista){
        int dx = c->getX() - x;
        int dy = c->getY() - y;

        if(sqrt(dx*dx + dy*dy) <= distanciaMaxima)
            resultado.push_back(c);
    }

    return resultado;
}

vector<Cinema*> Cinemas::buscarPorFilme(string idFilme){
    if(mapaFilme.count(idFilme)) return mapaFilme[idFilme];
    return {};
}

vector<Cinema*> Cinemas::filtrarPorGenero(string genero, Filmes& filmes){
    vector<Cinema*> resultado;
    unordered_set<Cinema*> usado;

    for(auto &p: mapaFilme){
        Filme* f = filmes.buscarPorId(p.first);

        if(f && f->temGenero(genero)){
            for(auto c: p.second){
                if(!usado.count(c)){
                    resultado.push_back(c);
                    usado.insert(c);
                }
            }
        }
    }

    return resultado;
}

vector<Cinema*> Cinemas::filtrarPorTipo(string tipo, Filmes& filmes){
    vector<Cinema*> resultado;
    unordered_set<Cinema*> usado;

    for(auto &p: mapaFilme){
        Filme* f = filmes.buscarPorId(p.first);

        if(f && f->ehDoTipo(tipo)){
            for(auto c: p.second){
                if(!usado.count(c)){
                    resultado.push_back(c);
                    usado.insert(c);
                }
            }
        }
    }

    return resultado;
}

vector<Cinema*> Cinemas::filtrarPorAno(int min,int max,Filmes& filmes){
    vector<Cinema*> resultado;
    unordered_set<Cinema*> usado;

    for(auto &p: mapaFilme){
        Filme* f = filmes.buscarPorId(p.first);

        if(f && f->estaNoIntervaloAno(min,max)){
            for(auto c: p.second){
                if(!usado.count(c)){
                    resultado.push_back(c);
                    usado.insert(c);
                }
            }
        }
    }

    return resultado;
}

vector<Cinema*> Cinemas::filtrarPorDuracao(int min,int max,Filmes& filmes){
    vector<Cinema*> resultado;
    unordered_set<Cinema*> usado;

    for(auto &p: mapaFilme){
        Filme* f = filmes.buscarPorId(p.first);

        if(f && f->estaNoIntervaloDuracao(min,max)){
            for(auto c: p.second){
                if(!usado.count(c)){
                    resultado.push_back(c);
                    usado.insert(c);
                }
            }
        }
    }

    return resultado;
}

vector<Cinema*> Cinemas::buscarPorGenero(string genero, Filmes& filmes){
    vector<Cinema*> resultado;
    unordered_set<Cinema*> usado;

    for(auto &p: mapaFilme){
        Filme* f = filmes.buscarPorId(p.first);

        if(f && f->temGenero(genero)){
            for(auto c: p.second){
                if(!usado.count(c)){
                    resultado.push_back(c);
                    usado.insert(c);
                }
            }
        }
    }

    return resultado;
}

vector<Cinema*> Cinemas::intersecao(vector<Cinema*> a, vector<Cinema*> b){
    unordered_set<Cinema*> setB(b.begin(), b.end());
    vector<Cinema*> resultado;

    for(auto c: a)
        if(setB.count(c))
            resultado.push_back(c);

    return resultado;
}

vector<Cinema*> Cinemas::uniao(vector<Cinema*> a, vector<Cinema*> b){
    unordered_set<Cinema*> s(a.begin(), a.end());

    for(auto c: b)
        s.insert(c);

    return vector<Cinema*>(s.begin(), s.end());
}