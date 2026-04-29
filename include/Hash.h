#ifndef HASH_H
#define HASH_H

#include <vector>
#include <list>
#include <utility>

using namespace std;

template<typename K, typename V>

class Hash{
    
private: 
    int capacidade = 1007;
    vector<list<pair<K,V>>> tabela;

    int funcaoHash(const K& chave)const{
        long long hash = 0;
        for(char c: chave){
            hash = hash * 31 + c;
        }
        return abs(hash) % capacidade;
    }

 public:

    Hush(){
        tabela.resize(capacidade);
    }

    void inserir(const K& chave, const V& valor){
        int indice = funcaoHash(chave);
        for(auto& p: tabela[indice]){
            if(p.first==chave){
                p.second = valor;
                return;
            }
        }

        tabela[indice].push_back({chave, valor});
    }

    bool existe(const K& chave)const{
        int indice = funcaoHash(chave);
        for(const auto& p: tabela[indice]){
            if(p.first==chave)return true;
        }

        return false;
    }

    V get(const K& chave)const{
        int indice = funcaoHash(chave);
        for(const auto& p: tabela[indice]){
            if(p.first==chave)return p.second;
        }

        throw runtime_error("Chave não encontrada");
    }

    V& getRef(const K& chave){
        int indice = funcaoHash(chave);
        for(auto& p: tabela[indice]){
            if(p.first==chave)return p.second;
        }

        tabela[idx].push_back({chave, V()});
        return tabela[idx].back().second;
    }


};
#endif