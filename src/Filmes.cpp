#include "Filmes.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

Filmes::Filmes(){}

Filmes::~Filmes(){
    for(int i = 0; i < lista.size(); i++){
        delete lista[i];
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
        if(linha.empty()) continue;

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

        if(id.size() < 3)continue;

        int bruto = stoi(id.substr(2));
        if(bruto % 2 != 0)continue;
        int idNumerico = bruto / 2;

        Filme* f = new Filme();
        f->setId(id);
        f->setTipo(tipo);
        f->setTitulo(titulo);
        f->setIsAdult(isAdultStr == "1");
        f->setStartYear((anoStr == "\\N") ? 0 : stoi(anoStr));
        f->setEndYear((endYearStr == "\\N") ? 0 : stoi(endYearStr));
        f->setDuracao((duracaoStr == "\\N") ? 0 : stoi(duracaoStr));

        if(idNumerico >= listaDireta.size()){
            listaDireta.resize(idNumerico + 1, nullptr);
        }

        if(listaDireta[idNumerico] == nullptr){
            listaDireta[idNumerico] = f;
        }

        mapaTipo[tipo].push_back(f);
        stringstream ssGeneros(generosStr);
        string genero;

        while(getline(ssGeneros, genero, ',')){
            f->addGenero(genero);
            mapaGenero[genero].push_back(f);
        }

        lista.push_back(f);
    }

    file.close();
}

Filme* Filmes::buscarPorId(string id){

    if(id.size() < 3) return nullptr;
    int bruto = stoi(id.substr(2));
    if(bruto % 2 != 0) return nullptr;
    int idNumerico = bruto / 2;
    if(idNumerico >= 0 && idNumerico < listaDireta.size()){
        return listaDireta[idNumerico];
    }

    return nullptr;
}

vector<Filme*> Filmes::filtrarPorGenero(string genero){
    if(mapaGenero.count(genero)){
        return mapaGenero[genero];
    }
    return {};
}

vector<Filme*> Filmes::filtrarPorTipo(string tipo){
    if(mapaTipo.count(tipo)){
        return mapaTipo[tipo]; 
    }
    return {};
}

vector<Filme*> Filmes::filtrarPorAno(int min, int max){
    vector<Filme*> resultado;
    for(int i = 0; i < lista.size(); i++){
        Filme* f = lista[i];
        if(f->estaNoIntervaloAno(min, max)){
            resultado.push_back(f);
        }
    }

    return resultado;
}

vector<Filme*> Filmes::filtrarPorDuracao(int min, int max){
    vector<Filme*> resultado;
    for(int i = 0; i < lista.size(); i++){
        Filme* f = lista[i];
        if(f->estaNoIntervaloDuracao(min, max)){
            resultado.push_back(f);
        }
    }

    return resultado;
}

vector<Filme*> intersecao(vector<Filme*> a, vector<Filme*> b){
    vector<Filme*> resultado;

    for(Filme* f1 : a){
        for(Filme* f2 : b){
            if(f1 == f2){
                resultado.push_back(f1);
                break;
            }
        }
    }

    return resultado;
}


vector<Filme*> uniao(vector<Filme*> a, vector<Filme*> b){
    vector<Filme*> resultado = a;

    for(Filme* f : b){
        bool existe = false;

        for(Filme* r : resultado){
            if(r == f){
                existe = true;
                break;
            }
        }

        if(!existe){
            resultado.push_back(f);
        }
    }

    return resultado;
}

vector<Filme*> Filmes::filtrarConsulta(string consulta){

    stringstream ss(consulta);
    vector<string> tokens;
    string token;

    // separa por espaço
    while(ss >> token){
        tokens.push_back(token);
    }

    // primeiro filtro
    vector<Filme*> resultado = filtrarPorGenero(tokens[0]);

    // percorre operadores
    for(int i = 1; i < tokens.size(); i += 2){
        string op = tokens[i];
        string valor = tokens[i+1];

        vector<Filme*> novo = filtrarPorGenero(valor);

        if(op == "&"){
            resultado = intersecao(resultado, novo);
        }
        else if(op == "|"){
            resultado = uniao(resultado, novo);
        }
    }

    return resultado;
}