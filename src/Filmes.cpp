#include "Filmes.h"
#include<fstream>
#include<sstream>

using namespace std;

Filmes::Filmes(){}
Filmes::~Filmes(){}

void Filmes::carregar(string arquivo){

    ifstream file(arquivo);
    string linha;
    if(!file.is_open()){
        cout << "Erro ao abrir o arquivo!" << endl;
        return;
    }

    while(getline(file, linha)){
        stringstream ss(linha);

        string id, tipo, titulo, isAdultStr, anoStr, endYearStr, duracaoStr, generosStr;
        getline(ss, id, '\t');
        getline(ss, tipo, '\t');
        getline(ss, titulo, '\t');
        getline(ss, isAdult, '\t');
        getline(ss, anoStr, '\t');
        getline(ss, endYearStr, '\t');
        getline(ss, duracaoStr, '\t');
        getline(ss, generosStr, '\t');

        Filme f;
        f.setId(id);
        f.setTipo(tipo);
        f.setTitulo(titulo);
        f.setIsAdult(isAdultStr == "1");
        f.setStartYear((anoStr == "\\N") ? 0 : stoi(anoStr));
        f.setEndYear((endYearStr == "\\N") ? 0 : stoi(endYearStr));
        f.setDuracao((duracaoStr == "\\N") ? 0 : stoi(duracaoStr));

    }

}