#ifndef FILME_H
#define FILME_H

#include<string>
#include<vector>

using namespace std;

class Filme{

    private:
      string tconst;
      string titleType;
      string primaryTitle;
      bool isAdult;
      int startYear;
      int endYear;
      int runtimeMinutes;
      vector<string> genres;

    public:
      Filme();
      ~Filme();

      string getId();
      void setId(string id);
      string getTipo();
      void setTipo(string tipo);
      string getTitulo();
      void setTitulo(string titulo);
      int getAno();
      void setAno(int ano);
      int getDuracao();
      void setDuracao(int duracao);
      vector<string> getGeneros();
      void addGenero(string genero);

      bool temGenero(string genero);
      bool ehDoTipo(string tipo);
      bool estaNoIntervaloAno(int min, int max);
      bool estaNoIntervaloDuracao(int min, int max);

};
#endif