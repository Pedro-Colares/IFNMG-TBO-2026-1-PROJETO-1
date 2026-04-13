#include "Filmes.h"
#include<fstream>
#include<sstream>
#include<iostream>

using namespace std;

Filmes::Filmes(){}
Filmes::~Filmes(){
    for(int i=0; i<lista.size(); i++){
        Filme* f = lista[i];
        delete f;
    }
    lista.clear();
}

void Filmes::carregar(string arquivo){

    ifstream file(arquivo);
    string linha;
    if(!file.is_open()){
        cout << "Erro ao abrir o arquivo!" << endl;
        return;
    }

    while(getline(file, linha)){
        stringstream ss(linha);

        string id, tipo, titulo, isAdultStr, anoStr, endYearStr, duracaoStr, generosStr;
        getline(ss, id, '\t');
        getline(ss, tipo, '\t');
        getline(ss, titulo, '\t');
        getline(ss, isAdultStr, '\t');
        getline(ss, anoStr, '\t');
        getline(ss, endYearStr, '\t');
        getline(ss, duracaoStr, '\t');
        getline(ss, generosStr, '\t');

        Filme* f = new Filme();
        f->setId(id);
        f->setTipo(tipo);
        f->setTitulo(titulo);
        f->setIsAdult(isAdultStr == "1");
        f->setStartYear((anoStr == "\\N") ? 0 : stoi(anoStr));
        f->setEndYear((endYearStr == "\\N") ? 0 : stoi(endYearStr));
        f->setDuracao((duracaoStr == "\\N") ? 0 : stoi(duracaoStr));

        stringstream generos(generosStr);
        string genero;

        while(getline(generos, genero, ',')){
            f->addGenero(genero);
        }

        lista.push_back(f);
        mapa[id] = f;

    }

    file.close();

}

Filme* Filmes::buscarPorId(string id){
    if(mapa.find(id) != mapa.end()){
        return mapa[id];
    }
    return nullptr;
}

vector<Filme*> Filmes::filtrarPorGenero(string genero){
    vector<Filme*> resultado;
    for(int i=0; i<lista.size(); i++){
        Filme* f = lista[i];
        if(f->temGenero(genero)){
            resultado.push_back(f);
        }
    }
    return resultado;
}

vector<Filme*> Filmes::filtrarPorAno(int min, int max){
    vector<Filme*>resultado;
    for(int i=0; i<lista.size(); i++){
        Filme* f = lista[i];
        if(f->estaNoIntervaloAno(min, max)){
            resultado.push_back(f);
        }
    }
    return resultado;
}

vector<Filme*> Filmes::filtrarPorDuracao(int min, int max){
    vector<Filme*>resultado;
    for(int i=0; i<lista.size(); i++){
        Filme* f = lista[i];
        if(f->estaNoIntervaloDuracao(min, max)){
            resultado.push_back(f);
        }
    }
    return resultado;
}

vector<Filme*> Filmes::filtrarPorTipo(string tipo){
    vector<Filme*>resultado;
    for(int i=0; i<lista.size(); i++){
        Filme* f = lista[i];
        if(f->ehDoTipo(tipo)){
            resultado.push_back(f);
        }
    }
    return resultado;
}