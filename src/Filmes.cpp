#include "Filmes.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_set>
#include <stack>

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

    getline(file, linha);

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

        id.erase(0, 2);
        if(id == "") continue;

        int bruto = stoi(id);
        if(bruto % 2 != 0)continue;
        int idNumerico = bruto / 2;

        Filme* f = new Filme();
        f->setId(id);
        f->setTipo(tipo);
        f->setTitulo(titulo);
        f->setIsAdult(isAdultStr == "1");
        f->setStartYear((anoStr == "\\N" || anoStr == "") ? 0 : stoi(anoStr));
        f->setEndYear((endYearStr == "\\N" || endYearStr == "") ? 0 : stoi(endYearStr));
        f->setDuracao((duracaoStr == "\\N" || duracaoStr == "") ? 0 : stoi(duracaoStr));

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

    id.erase(0, 2);
    if(id == "") return nullptr;

    int bruto = stoi(id);
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
vector<Filme*> Filmes::aplicarFiltro(string palavra){

    int pos = palavra.find(":");

    if(pos != string::npos){
        string chave = palavra.substr(0, pos);
        string valor = palavra.substr(pos + 1);

        if(chave == "ano"){
            size_t hifen = valor.find("-");
            if(hifen != string::npos){
                int min = stoi(valor.substr(0, hifen));
                int max = stoi(valor.substr(hifen + 1));
                return filtrarPorAno(min, max);
            } else {
                int ano = stoi(valor);
                return filtrarPorAno(ano, ano);
            }
        }

        if(chave == "duracao"){
            size_t hifen = valor.find("-");
            if(hifen != string::npos){
                int min = stoi(valor.substr(0, hifen));
                int max = stoi(valor.substr(hifen + 1));
                return filtrarPorDuracao(min, max);
            } else {
                int d = stoi(valor);
                return filtrarPorDuracao(d, d);
            }
        }
    }

    if(mapaGenero.count(palavra)){
        return filtrarPorGenero(palavra);
    }
    else if(mapaTipo.count(palavra)){
        return filtrarPorTipo(palavra);
    }

    return {};
}

vector<Filme*> Filmes::filtrarConsulta(string consulta){
    vector<string> tokens = tokenizar(consulta);
    vector<string> posfixa = paraPosfixa(tokens);
    return avaliarPosfixa(posfixa);
}

vector<string> Filmes::tokenizar(string s){
    vector<string> tokens;
    string atual = "";

    for(char c : s){
        if(c == ' '){
            if(!atual.empty()){
                tokens.push_back(atual);
                atual = "";
            }
        }
        else if(c == '(' || c == ')' || c == '&' || c == '|'){
            if(!atual.empty()){
                tokens.push_back(atual);
                atual = "";
            }
            tokens.push_back(string(1, c));
        }
        else{
            atual += c;
        }
    }

    if(!atual.empty()){
        tokens.push_back(atual);
    }

    return tokens;
}

int Filmes::prioridade(string op){
    if(op == "&") return 2;
    if(op == "|") return 1;
    return 0;
}

vector<string> Filmes::paraPosfixa(vector<string> tokens){
    vector<string> saida;
    stack<string> ops;

    for(string t : tokens){

        if(t == "&" || t == "|"){
            while(!ops.empty() && ops.top() != "(" && prioridade(ops.top()) >= prioridade(t)){
                saida.push_back(ops.top());
                ops.pop();
            }
            ops.push(t);
        }
        else if(t == "("){
            ops.push(t);
        }
        else if(t == ")"){
            while(!ops.empty() && ops.top() != "("){
                saida.push_back(ops.top());
                ops.pop();
            }
            if(!ops.empty()) ops.pop();
        }
        else{
            saida.push_back(t);
        }
    }

    while(!ops.empty()){
        saida.push_back(ops.top());
        ops.pop();
    }

    return saida;
}

vector<Filme*> Filmes::avaliarPosfixa(vector<string> posfixa){
    stack<vector<Filme*>> pilha;

    for(string t : posfixa){
        if(t == "&" || t == "|"){

            if(pilha.size() < 2) return {};

            auto b = pilha.top(); pilha.pop();
            auto a = pilha.top(); pilha.pop();

            if(t == "&"){
                pilha.push(intersecao(a, b));
            }
            else{
                pilha.push(uniao(a, b));
            }
        }
        else{
            pilha.push(aplicarFiltro(t));
        }
    }

    if(pilha.empty()) return {};
    return pilha.top();
}