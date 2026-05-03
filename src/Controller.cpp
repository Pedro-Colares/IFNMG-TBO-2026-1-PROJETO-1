#include "Controller.h"
#include<iostream>
#include<chrono>
#include<limits>

using namespace std;
using namespace chrono;

Controller::Controller(Filmes& f, Cinemas& c): filmes(f), cinemas(c){}
Controller::~Controller(){}


void Controller::consultaFilmes(){
    string query;
    cout << "Digite a query (ex: Drama & ano:1990-1999): " << flush;
    getline(cin, query);

    auto inicio = high_resolution_clock::now();
    vector<Filme*> resultado = filmes.filtrarConsulta(query);
    auto fim = high_resolution_clock::now();

    cout << "\nTotal: " << resultado.size() << "\n";
    for(Filme* f : resultado){
        cout << f->getTitulo() << "\n";
    }

    cout << "Tempo: "
     << duration_cast<milliseconds>(fim - inicio).count()
     << " ms\n";
}

void Controller::consultaCinemas(){
    string query;
    cout << "Digite a query (ex: Drama & preco:20): " << flush;
    getline(cin, query);

    auto inicio = high_resolution_clock::now();
    vector<Cinema*> resultado = cinemas.filtrarConsulta(query, filmes);
    auto fim = high_resolution_clock::now();

    cout << "\nTotal: " << resultado.size() << "\n";
    for(Cinema* c : resultado){
        cout << "Cinema: " << c->getNome()
     << " - ID: " << c->getId() << "\n";
    }

    cout << "Tempo: "
         << duration_cast<milliseconds>(fim - inicio).count()
         << " ms\n";
}

void Controller::executar(){
    int opcao;
    do{
        cout <<"\n ==== MENU ==== \n";
        cout <<"1. Consultar Filmes\n";
        cout <<"2. Consultar Cinemas\n";
        cout <<"0. Sair\n";
        cout <<"Escolha uma opcao: ";
        cin >> opcao;
        cin.ignore();

        switch(opcao){
            case 1:{
                consultaFilmes();
                break;           
            }

            case 2:{
                consultaCinemas();
                break;
            }

            case 0:{
                cout <<"Saindo...\nFim do programa.\n";
                break;
            }

            default:{
                cout <<"Opcao invalida!\n";
            }

        }
    }while(opcao != 0);
}
