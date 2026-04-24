#include <iostream>
#include "Filmes.h"

using namespace std;

int main(){
    Filmes filmes;

    // carrega o arquivo (coloca o caminho certo aqui)
    filmes.carregar("dados.tsv");

    return 0;
}