#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Filmes.h"
#include "Cinemas.h"
#include <vector>

class Controller{

    private:
        Filmes& filmes;
        Cinemas& cinemas;

    public:
        Controller(Filmes& f, Cinemas& c);
        ~Controller();

        vector<Filme*>consultarFilmes(string consulta);
        vector<Cinema*>consultarCinemas();

        void executar();
};
#endif