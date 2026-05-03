#include "Filmes.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stack>

using namespace std;

Filmes::Filmes(){}

// Destrutor: libera a memória de todos os filmes alocados dinamicamente
Filmes::~Filmes(){
    for(int i = 0; i < lista.size(); i++){
        delete lista[i];
    }
    lista.clear();
}

// Remove espaços, tabs e \r das bordas de uma string
string limpar(string s){
    while(!s.empty() && (s[0] == ' ' || s[0] == '\t'))
        s.erase(0, 1);
    while(!s.empty() && (s.back() == ' ' || s.back() == '\t' || s.back() == '\r'))
        s.pop_back();
    return s;
}

bool comparaFilmeAno(Filme* a, Filme* b){
    return a->getAno() < b->getAno();
}

bool comparaFilmeDuracao(Filme* a, Filme* b){
    return a->getDuracao() < b->getDuracao();
}

// acha o primeiro índice com ano >= valor
int Filmes::BuscaBinariaMenorAno(int valor){
    int esq = 0, dir = listaPorAno.size();
    while(esq < dir){
        int meio = (esq + dir) / 2;
        if(listaPorAno[meio]->getAno() < valor)
            esq = meio + 1;
        else
            dir = meio;
    }
    return esq;
}

// acha o primeiro índice com ano > valor
int Filmes::BuscaBinariaMaiorAno(int valor){
    int esq = 0, dir = listaPorAno.size();
    while(esq < dir){
        int meio = (esq + dir) / 2;
        if(listaPorAno[meio]->getAno() <= valor)
            esq = meio + 1;
        else
            dir = meio;
    }
    return esq;
}

int Filmes::BuscaBinariaMenorDuracao(int valor){
    int esq = 0, dir = listaPorDuracao.size();
    while(esq < dir){
        int meio = (esq + dir) / 2;
        if(listaPorDuracao[meio]->getDuracao() < valor)
            esq = meio + 1;
        else
            dir = meio;
    }
    return esq;
}

int Filmes::BuscaBinariaMaiorDuracao(int valor){
    int esq = 0, dir = listaPorDuracao.size();
    while(esq < dir){
        int meio = (esq + dir) / 2;
        if(listaPorDuracao[meio]->getDuracao() <= valor)
            esq = meio + 1;
        else
            dir = meio;
    }
    return esq;
}

void Filmes::carregar(string arquivo){
    ifstream file(arquivo);
    string linha;

    if(!file.is_open()){
        cout << "Erro ao abrir o arquivo!" << endl;
        return;
    }

    getline(file, linha); // pula a linha de cabeçalho

    while(getline(file, linha)){
        if(linha.empty()) continue;

        stringstream ss(linha);
        string id, tipo, titulo, originalTitulo, isAdultStr,
               anoStr, endYearStr, duracaoStr, generosStr;

        getline(ss, id, '\t');
        getline(ss, tipo, '\t');
        getline(ss, titulo, '\t');
        getline(ss, originalTitulo, '\t'); // coluna 4 — não usada, mas precisa ser consumida
        getline(ss, isAdultStr, '\t');
        getline(ss, anoStr, '\t');
        getline(ss, endYearStr, '\t');
        getline(ss, duracaoStr, '\t');
        getline(ss, generosStr);           

        tipo = limpar(tipo);
        generosStr = limpar(generosStr);

        if(id.size() < 3) continue;
        id.erase(0, 2);
        if(id.empty()) continue;

        int bruto = stoi(id);
        if(bruto % 2 != 0) continue;      
        int idNumerico = bruto / 2;        

        Filme* f = new Filme();
        f->setId(id);
        f->setTipo(tipo);
        f->setTitulo(titulo);
        f->setIsAdult(isAdultStr == "1");
        f->setStartYear((anoStr == "\\N" || anoStr.empty()) ? 0 : stoi(anoStr));
        f->setEndYear ((endYearStr == "\\N" || endYearStr.empty()) ? 0 : stoi(endYearStr));
        f->setDuracao ((duracaoStr == "\\N" || duracaoStr.empty()) ? 0 : stoi(duracaoStr));

        if(idNumerico >= (int)listaDireta.size()){
            listaDireta.resize(idNumerico + 1, nullptr);
        }

        if(listaDireta[idNumerico] != nullptr){
            delete f;
            continue;
        }

        listaDireta[idNumerico] = f;
        mapaTipo.getRef(tipo).push_back(f);

        stringstream ssGeneros(generosStr);
        string genero;
        while(getline(ssGeneros, genero, ',')){
            genero = limpar(genero);
            if(genero == "\\N" || genero.empty()) continue;
            f->addGenero(genero);
            mapaGenero.getRef(genero).push_back(f);
        }

        lista.push_back(f);
    }

    file.close();

    listaPorAno = lista;
    MergeSort(listaPorAno, 0, listaPorAno.size(), comparaFilmeAno);

    listaPorDuracao = lista;
    MergeSort(listaPorDuracao, 0, listaPorDuracao.size(), comparaFilmeDuracao);
}

Filme* Filmes::buscarMaisProximo(string id){
    if(id.size() < 3) return nullptr;

    id.erase(0, 2); 

    if(id.empty()) return nullptr;

    int bruto = stoi(id);

    while(true){
        if(bruto % 2 == 0){
            int idx = bruto / 2;

            if(idx >= 0 && idx < (int)listaDireta.size()){
                if(listaDireta[idx] != nullptr)
                    return listaDireta[idx];
            }
        }
        bruto++;
    }
}

Filme* Filmes::buscarPorId(string id){
    if(id.size() < 3) return nullptr;
    id.erase(0, 2);
    if(id.empty()) return nullptr;

    int bruto = stoi(id);
    if(bruto % 2 != 0) return nullptr;
    int idNumerico = bruto / 2;

    if(idNumerico >= 0 && idNumerico < (int)listaDireta.size()){
        return listaDireta[idNumerico];
    }
    return nullptr;
}

vector<Filme*> Filmes::filtrarPorGenero(string genero){
    if(mapaGenero.existe(genero)) return mapaGenero.getRef(genero);
    return {};
}

vector<Filme*> Filmes::filtrarPorTipo(string tipo){
    if(mapaTipo.existe(tipo)) return mapaTipo.getRef(tipo);
    return {};
}

vector<Filme*> Filmes::filtrarPorAno(int min, int max){
    vector<Filme*> resultado;
    int inicio = BuscaBinariaMenorAno(min);
    int fim = BuscaBinariaMaiorAno(max);
    for(int i = inicio; i < fim; i++){
        resultado.push_back(listaPorAno[i]);
    }
    return resultado;
}

vector<Filme*> Filmes::filtrarPorDuracao(int min, int max){
    vector<Filme*> resultado;
    int inicio = BuscaBinariaMenorDuracao(min);
    int fim = BuscaBinariaMaiorDuracao(max);
    for(int i = inicio; i < fim; i++){
        resultado.push_back(listaPorDuracao[i]);
    }
    return resultado;
}

vector<Filme*> Filmes::intersecao(vector<Filme*> a, vector<Filme*> b){
    vector<Filme*> resultado;
    HashSet<Filme*> setB;
    for(Filme* f : b) setB.inserir(f);
    for(Filme* f : a){
        if(setB.existe(f))
            resultado.push_back(f);
    }
    return resultado;
}

vector<Filme*> Filmes::uniao(vector<Filme*> a, vector<Filme*> b){
    vector<Filme*> resultado = a;
    HashSet<Filme*> usado;
    for(Filme* f : a) usado.inserir(f);
    for(Filme* f : b){
        if(!usado.existe(f)){
            resultado.push_back(f);
            usado.inserir(f);
        }
    }
    return resultado;
}

vector<Filme*> Filmes::aplicarFiltro(string palavra){
    int pos = palavra.find(":");

    if(pos != (int)string::npos){
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

    if(mapaGenero.existe(palavra)) return filtrarPorGenero(palavra);
    if(mapaTipo.existe(palavra)) return filtrarPorTipo(palavra);
    return {};
}

vector<Filme*> Filmes::avaliarConsultaSimples(vector<string> tokens){

    stack<vector<Filme*>> pilhaResultados;
    stack<string> pilhaOperadores;

    pilhaResultados.push({});
    pilhaOperadores.push("&");

    for(const string& t : tokens){

        if(t == "("){
            pilhaResultados.push({});
            pilhaOperadores.push("&");
        }

        else if(t == ")"){
            if(pilhaResultados.size() > 1){

                vector<Filme*> fechado = pilhaResultados.top();
                pilhaResultados.pop();
                pilhaOperadores.pop();

                string op = pilhaOperadores.top();

                if(pilhaResultados.top().empty()){
                    pilhaResultados.top() = fechado;
                }
                else if(op == "&"){
                    pilhaResultados.top() = intersecao(pilhaResultados.top(), fechado);
                }
                else{
                    pilhaResultados.top() = uniao(pilhaResultados.top(), fechado);
                }
            }
        }

        else if(t == "&" || t == "|"){
            pilhaOperadores.top() = t;
        }

        else{
            vector<Filme*> atual = aplicarFiltro(t);
            string op = pilhaOperadores.top();

            if(pilhaResultados.top().empty()){
                pilhaResultados.top() = atual;
            }
            else if(op == "&"){
                pilhaResultados.top() = intersecao(pilhaResultados.top(), atual);
            }
            else{
                pilhaResultados.top() = uniao(pilhaResultados.top(), atual);
            }
        }
    }

    return pilhaResultados.top();
}

vector<Filme*> Filmes::filtrarConsulta(string consulta){
    vector<string> tokens = tokenizar(consulta);
    return avaliarConsultaSimples(tokens);
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

    if(!atual.empty()) tokens.push_back(atual);

    for(string& t : tokens) t = limpar(t);

    return tokens;
}