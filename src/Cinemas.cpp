#include "Cinemas.h"
#include <fstream>
#include <sstream>
#include <cmath>
#include <unordered_set>
#include <stack>

using namespace std;

string Cinemas::limpar(string s){
    while(!s.empty() && (s[0]==' ' || s[0]=='\t')) s.erase(0,1);
    while(!s.empty() && (s.back()==' ' || s.back()=='\t' || s.back()=='\r' || s.back()=='\n')) s.pop_back();
    return s;
}

Cinemas::Cinemas(){}

Cinemas::~Cinemas(){
    for(Cinema* c: lista) delete c;
}

vector<Cinema*> Cinemas::getTodos(){
    return lista;
}

void Cinemas::carregar(string arquivo, Filmes& filmes){
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

        int bx = c->getX() / TAM;
        int by = c->getY() / TAM;
        long long chave = (long long)bx * 100000 + by;

        grade[chave].push_back(c);

        stringstream sf(filmesStr);
        string fid;

        while(getline(sf,fid,',')){
            fid = limpar(fid);
            if(fid.empty()) continue;
            c->addFilme(fid);
            mapaFilme[fid].push_back(c);

            Filme* f = filmes.buscarPorId(fid);

            if(!f)
            f = filmes.buscarMaisProximo(fid);

            if(f){
                for(string g : f->getGeneros()){
                    mapaGenero[g].insert(c);
                }

                mapaTipo[f->getTipo()].insert(c);
            }
        }
    }
}

Cinema* Cinemas::buscarPorId(string id){
    if(mapa.count(id)) return mapa[id];
    return nullptr;
}



vector<Cinema*> Cinemas::filtrarPorPreco(double max){
    vector<Cinema*> resultado;

    for(pair<const double, vector<Cinema*>> &p: indicePreco){
        if(p.first <= max){
            resultado.insert(resultado.end(), p.second.begin(), p.second.end());
        }
    }

    return resultado;
}

vector<Cinema*> Cinemas::filtrarPorDistancia(int x, int y, double distanciaMaxima){
    vector<Cinema*> resultado;

    int bx = x / TAM;
    int by = y / TAM;

    int raioBlocos = distanciaMaxima / TAM + 1;

    for(int i = -raioBlocos; i <= raioBlocos; i++){
        for(int j = -raioBlocos; j <= raioBlocos; j++){

            long long chave = (long long)(bx + i) * 100000 + (by + j);

            if(grade.count(chave)){
                for(Cinema* c : grade[chave]){

                    int dx = c->getX() - x;
                    int dy = c->getY() - y;

                    double dist = sqrt(dx*dx + dy*dy);

                    if(dist <= distanciaMaxima){
                        resultado.push_back(c);
                    }
                }
            }
        }
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

    for(pair<const string, vector<Cinema*>> &p: mapaFilme){
        Filme* f = filmes.buscarPorId(p.first);

        if(f && f->estaNoIntervaloAno(min,max)){
            for(Cinema* c: p.second){
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

    for(pair<const string, vector<Cinema*>> &p: mapaFilme){
        Filme* f = filmes.buscarPorId(p.first);

        if(f && f->estaNoIntervaloDuracao(min,max)){
            for(Cinema* c: p.second){
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

    for(Cinema* c: a)
        if(setB.count(c))
            resultado.push_back(c);

    return resultado;
}

vector<Cinema*> Cinemas::uniao(vector<Cinema*> a, vector<Cinema*> b){
    unordered_set<Cinema*> s(a.begin(), a.end());

    for(Cinema* c: b)
        s.insert(c);

    return vector<Cinema*>(s.begin(), s.end());
}

vector<Cinema*> Cinemas::aplicarFiltro(string palavra, Filmes& filmes){

    int pos = palavra.find(":");

    if(pos != string::npos){
        string chave = palavra.substr(0, pos);
        string valor = palavra.substr(pos + 1);

        valor = limpar(valor);

        if(chave == "preco"){
            return filtrarPorPreco(stod(valor));
        }

        if(chave == "filme"){
            return buscarPorFilme(valor);
        }

        if(chave == "genero"){
            return filtrarPorGenero(valor, filmes);
        }

        if(chave == "tipo"){
            return filtrarPorTipo(valor, filmes);
        }

        if(chave == "ano"){
            int h = valor.find("-");
            if(h != string::npos){
                int min = stoi(valor.substr(0,h));
                int max = stoi(valor.substr(h+1));
                return filtrarPorAno(min,max,filmes);
            } else {
                int a = stoi(valor);
                return filtrarPorAno(a,a,filmes);
            }
        }

        if(chave == "duracao"){
            int h = valor.find("-");
            if(h != string::npos){
                int min = stoi(valor.substr(0,h));
                int max = stoi(valor.substr(h+1));
                return filtrarPorDuracao(min,max,filmes);
            } else {
                int d = stoi(valor);
                return filtrarPorDuracao(d,d,filmes);
            }
        }

        if(chave == "dist"){
            stringstream ss(valor);
            string sx, sy, sr;

            getline(ss, sx, ',');
            getline(ss, sy, ',');
            getline(ss, sr, ',');

            int x = stoi(sx);
            int y = stoi(sy);
            int r = stoi(sr);

            return filtrarPorDistancia(x,y,r);
        }
    }

    if(mapaFilme.count(palavra)) return buscarPorFilme(palavra);

    vector<Cinema*> porGenero = filtrarPorGenero(palavra, filmes);
    if(!porGenero.empty()) return porGenero;

    vector<Cinema*> porTipo = filtrarPorTipo(palavra, filmes);
    if(!porTipo.empty()) return porTipo;

    return {};
}

vector<Cinema*> Cinemas::filtrarConsulta(string consulta, Filmes& filmes){
    vector<string> tokens = tokenizar(consulta);
    return avaliarConsultaSimples(tokens, filmes);
}

vector<Cinema*> Cinemas::avaliarConsultaSimples(vector<string> tokens, Filmes& filmes){

    stack<vector<Cinema*>> pilhaResultados;
    stack<string> pilhaOperadores;

    pilhaResultados.push({});
    pilhaOperadores.push("&");

    for(const string& t : tokens){

        if(t == "("){
            pilhaResultados.push({});
            pilhaOperadores.push("&");
        }

        else if(t == ")"){
            vector<Cinema*> fechado = pilhaResultados.top();
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

        else if(t == "&" || t == "|"){
            pilhaOperadores.top() = t;
        }

        else{
            vector<Cinema*> atual = aplicarFiltro(t, filmes);
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


vector<string> Cinemas::tokenizar(string s){
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