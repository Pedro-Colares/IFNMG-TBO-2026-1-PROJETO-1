#ifndef HASHSET_H
#define HASHSET_H

#include "Hash.h"

template<typename T>

class HashSet{

private:

    Hash<T, bool> hash;

public:

    void inserir(const T& valor){
        hash.inserir(valor, true);
    }

    bool existe(const T& valor)const{
        return hash.existe(valor);
    }


};
#endif