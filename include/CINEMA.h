#ifndef CINEMA_H
#define CINEMA_H

#include<string>
#include<vector>

using namespace std;


class Cinema{

    public:
      string Cinema_ID;
      string Nome_do_Cinema;
      int Coordenada_X;
      int Coordenada_Y;
      double Preco_Ingresso;
      string Filmes_Em_Exibicao;

    Cinema();
    virtual ~Cinema(); 
};
#endif