#include "Filmes.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_set>

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

vector<Filme*> Filmes::intersecao(vector<Filme*> a, vector<Filme*> b){
    vector<Filme*> resultado;
    unordered_set<Filme*> setB(b.begin(), b.end());
    for(Filme* f : a){
        if(setB.count(f)){
            resultado.push_back(f);
        }
    }

    return resultado;
}


vector<Filme*> Filmes::uniao(vector<Filme*> a, vector<Filme*> b){
    unordered_set<Filme*> setRes(a.begin(), a.end());
    for(Filme* f : b){
        setRes.insert(f);
    }

    return vector<Filme*>(setRes.begin(), setRes.end());
}

vector<Filme*> Filmes::filtrarConsulta(string consulta){

    stringstream ss(consulta);
    vector<string> tokens;
    string token;

    // separa por espaço
    while(ss >> token){
        tokens.push_back(token);
    }

    if(tokens.empty()) return {};

    vector<Filme*> resultado;

    // primeiro filtro
    int pos0 = tokens[0].find(":");
    if(pos0 == string::npos) return {};

    string chave0 = tokens[0].substr(0, pos0);
    string valor0 = tokens[0].substr(pos0 + 1);

    if(chave0 == "genero"){
        resultado = filtrarPorGenero(valor0);
    }
    else if(chave0 == "tipo"){
        resultado = filtrarPorTipo(valor0);
    }
    else if(chave0 == "ano"){
        int ano = stoi(valor0);
        resultado = filtrarPorAno(ano, ano);
    }

    // percorre operadores
    for(int i = 1; i < tokens.size(); i += 2){

        if(i + 1 >= tokens.size()) break;

        string op = tokens[i];
        string filtroStr = tokens[i+1];

        int pos = filtroStr.find(":");
        if(pos == string::npos) continue;

        string chave = filtroStr.substr(0, pos);
        string valor = filtroStr.substr(pos + 1);

        vector<Filme*> novo;

        if(chave == "genero"){
            novo = filtrarPorGenero(valor);
        }
        else if(chave == "tipo"){
            novo = filtrarPorTipo(valor);
        }
        else if(chave == "ano"){
            int ano = stoi(valor);
            novo = filtrarPorAno(ano, ano);
        }

        if(op == "AND"){
            resultado = intersecao(resultado, novo);
        }
        else if(op == "OR"){
            resultado = uniao(resultado, novo);
        }
    }

    return resultado;
}