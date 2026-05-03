#ifndef HASHSET_H
#define HASHSET_H
#include <vector>
#include <list>
using namespace std;

template<typename T>
class HashSet{

private:
    int capacidade;
    vector<list<T>> tabela;

    int funcaoHash(const T& chave) const {
        long long addr = (long long)(void*)chave;
        if(addr < 0) addr = -addr;
        return (int)(addr % capacidade);
    }

public:

    friend class Cinemas;

    HashSet(int cap = 1007) : capacidade(cap){ tabela.resize(cap); }

    void inserir(const T& valor){
        int i = funcaoHash(valor);
        for(T& v : tabela[i])
            if(v == valor) return;
        tabela[i].push_back(valor);
    }

    bool existe(const T& valor) const {
        int i = funcaoHash(valor);
        for(const T& v : tabela[i])
            if(v == valor) return true;
        return false;
    }

    vector<T> elementos() const {
    vector<T> resultado;

    for(const auto& bucket : tabela){
        for(const T& v : bucket){
            resultado.push_back(v);
        }
    }

    return resultado;
}
};

#endif