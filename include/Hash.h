#ifndef HASH_H
#define HASH_H
#include <vector>
#include <list>
#include <string>
using namespace std;

// Hash com chave string
template<typename V>
class HashString{
private:
    int capacidade;
    vector<list<pair<string,V>>> tabela;

    int funcaoHash(const string& chave) const {
        long long hash = 0;
        for(char c : chave) hash = hash * 31 + c;
        if(hash < 0) hash = -hash;
        return (int)(hash % capacidade);
    }

public:
    HashString(int cap = 1007) : capacidade(cap){ tabela.resize(cap); }

    void inserir(const string& chave, const V& valor){
        int i = funcaoHash(chave);
        for(pair<string,V>& p : tabela[i]){
            if(p.first == chave){ p.second = valor; return; }
        }
        tabela[i].push_back({chave, valor});
    }

    bool existe(const string& chave) const {
        int i = funcaoHash(chave);
        for(const pair<string,V>& p : tabela[i])
            if(p.first == chave) return true;
        return false;
    }

    V& getRef(const string& chave){
        int i = funcaoHash(chave);
        for(pair<string,V>& p : tabela[i])
            if(p.first == chave) return p.second;
        tabela[i].push_back({chave, V()});
        return tabela[i].back().second;
    }
};

// Hash com chave long long
template<typename V>
class HashLong{
private:
    int capacidade;
    vector<list<pair<long long,V>>> tabela;

    int funcaoHash(long long chave) const {
        if(chave < 0) chave = -chave;
        return (int)(chave % capacidade);
    }

public:
    HashLong(int cap = 1007) : capacidade(cap){ tabela.resize(cap); }

    void inserir(long long chave, const V& valor){
        int i = funcaoHash(chave);
        for(pair<long long,V>& p : tabela[i]){
            if(p.first == chave){ p.second = valor; return; }
        }
        tabela[i].push_back({chave, valor});
    }

    bool existe(long long chave) const {
        int i = funcaoHash(chave);
        for(const pair<long long,V>& p : tabela[i])
            if(p.first == chave) return true;
        return false;
    }

    V& getRef(long long chave){
        int i = funcaoHash(chave);
        for(pair<long long,V>& p : tabela[i])
            if(p.first == chave) return p.second;
        tabela[i].push_back({chave, V()});
        return tabela[i].back().second;
    }
};

#endif