#include "Filmes.h"
#include "Cinemas.h"
#include "Controller.h"
#include <iostream>
#include <chrono>

using namespace std;
using namespace chrono;

int main() {

    cout << "INICIO\n";

    Filmes filmes;
    Cinemas cinemas;

    auto inicio = high_resolution_clock::now();

    filmes.carregar("data/filmesCrop.txt");
    cinemas.carregar("data/cinemas(1).txt", filmes);

    auto fim = high_resolution_clock::now();

    cout << "Tempo de carregamento: "
         << duration_cast<milliseconds>(fim - inicio).count()
         << " ms\n";

    Controller controller(filmes, cinemas);
    controller.executar();

    return 0;
}