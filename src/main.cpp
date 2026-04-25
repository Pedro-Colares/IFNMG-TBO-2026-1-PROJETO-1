#include <iostream>
#include "Filmes.h"

using namespace std;

int main() {

    cout << "INICIO\n";

    Filmes filmes;

    filmes.carregar("data/filmesCrop.txt");

    cout << "\n=== TESTES SIMPLES ===\n";

    cout << "Action: " << filmes.filtrarConsulta("Action").size() << endl;
    cout << "Comedy: " << filmes.filtrarConsulta("Comedy").size() << endl;
    cout << "Short: " << filmes.filtrarConsulta("Short").size() << endl;

    cout << "\n=== TESTE AND ===\n";
    cout << "Action & Short: " << filmes.filtrarConsulta("Action & Short").size() << endl;

    cout << "\n=== TESTE OR ===\n";
    cout << "(Action | Comedy): " << filmes.filtrarConsulta("Action | Comedy").size() << endl;

    cout << "\n=== TESTE COM PARÊNTESES ===\n";
    cout << "(Action & Short) | Comedy: " 
         << filmes.filtrarConsulta("(Action & Short) | Comedy").size() << endl;

    cout << "\n=== TESTE ANO ===\n";
    cout << "ano 2000: "         << filmes.filtrarConsulta("ano:2000").size()         << endl;
    cout << "ano 1990-2000: "    << filmes.filtrarConsulta("ano:1990-2000").size()    << endl;
    cout << "Action 1990-2000: " << filmes.filtrarConsulta("Action & ano:1990-2000").size() << endl;

    return 0;
}