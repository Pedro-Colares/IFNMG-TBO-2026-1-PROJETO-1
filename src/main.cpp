#include <iostream>
#include "Filmes.h"

using namespace std;

int main(){
    Filmes filmes;

    // carrega o arquivo (coloca o caminho certo aqui)
    filmes.carregar("data/filmesCrop.txt");
    cout << "FUNCIONANDO" << endl;

    Filme* f = filmes.buscarPorId("tt7917518");

if(f != nullptr){
    cout << "Filme encontrado!" << endl;
} else {
    cout << "Filme NAO encontrado!" << endl;
}
    return 0;
}