#include "Controller.h"
#include<iostream>
#include<chrono>

using namespace std;
using namespace chrono;

Controller::Controller(Filmes& f, Cinemas& c): filmes(f), cinemas(c){}
Controller::~Controller(){}


void Controller::consultaFilmes(){
    vector<Filme*> resultado;
    bool primeiraConsulta = true;
    int escolha;

    do{
        cout <<"\n----- FILMES -----\n";
        cout <<"1 - Filtrar por Genero\n";
        cout <<"2 - Filtrar por Tipo\n";
        cout <<"3 - Filtrar por Duracao\n";
        cout <<"4 - Filtrar por Ano\n";
        cout <<"5 - Mostrar Resultado\n";
        cout <<"0 - Voltar\n";

        cout <<"Escolha: ";
        cin >> escolha;

        vector<Filme*> m;
        auto inicio = high_resolution_clock::now();

        switch(escolha){

            case 1:{
                string genero;
                cout <<"Digite o genero: ";
                cin >> genero;
                m = filmes.filtrarPorGenero(genero);
                break;
            }

            case 2:{
                string tipo;
                cout <<"Digite o tipo: ";
                cin >> tipo;
                m = filmes.filtrarPorTipo(tipo);
                break;
            }

            case 3:{
                int min, max;
                cout <<"Duracao minima: ";
                cin >> min;
                cout <<"Duracao maxima: ";
                cin >> max;
                m = filmes.filtrarPorDuracao(min, max);
                break;
            }

            case 4:{
                int min, max;
                cout <<"Ano minimo: ";
                cin >> min;
                cout <<"Ano maximo: ";
                cin >> max;
                m = filmes.filtrarPorAno(min, max);
                break;
            }

            case 5:{
                auto inicio = high_resolution_clock::now();

                cout << "\nTotal: " << resultado.size() << endl;
                for(Filme* f : resultado){
                    cout << f->getTitulo() << endl;
                }

                auto fim = high_resolution_clock::now();
                cout << "Tempo da busca: "
                     << duration_cast<milliseconds>(fim - inicio).count()
                     << " ms\n";
                continue;
            }

            case 0:
                cout << "Voltando...\n";
                break;

            default:
                cout << "Opcao invalida!\n";
        }

        auto fim = high_resolution_clock::now();
        cout << "Tempo do filtro: "
             << duration_cast<milliseconds>(fim - inicio).count()
             << " ms\n";

        if(escolha >= 1 && escolha <= 4){

            if(primeiraConsulta){
                resultado = m;
                primeiraConsulta = false;
            } 
            else{
                int modo;
                cout << "1 - AND\n2 - OR\nEscolha: ";
                cin >> modo;

                if(modo == 1)
                    resultado = filmes.intersecao(resultado, m);
                else
                    resultado = filmes.uniao(resultado, m);
            }
        }

    }while(escolha != 0);
}

void Controller::consultaCinemas(){
    vector<Cinema*>resultado;
    bool primeiraConsulta = true;
    int escolha;
    do{
        cout <<"\n ----- CINEMAS -----\n";
        cout << "1 - Genero\n";
        cout << "2 - Tipo\n";
        cout << "3 - Duracao\n";
        cout << "4 - Ano\n";
        cout << "5 - Distancia\n";
        cout << "6 - Preco\n";
        cout << "7 - Buscar por filme\n";
        cout << "8 - Mostrar resultado\n";
        cout << "0 - Voltar\n";

        cout << "Escolha: ";
        cin >> escolha;

        vector<Cinema*> mt;
        auto inicio = high_resolution_clock::now();

        switch(escolha){

            case 1:{
                string genero;
                cout <<"Digite o genero: ";
                cin >> genero;
                mt = cinemas.filtrarPorGenero(genero, filmes);
                break;
            }

            case 2:{
                string tipo;
                cout <<"Digite o tipo: ";
                cin >> tipo;
                mt = cinemas.filtrarPorTipo(tipo, filmes);
                break;
            }

            case 3:{
                int min, max;
                cout <<"Duracao minima: ";
                cin >> min;
                cout <<"Duracao maxima: ";
                cin >> max;
                mt = cinemas.filtrarPorDuracao(min, max, filmes);
                break;
            }

            case 4:{
                int min, max;
                cout <<"Ano minimo: ";
                cin >> min;
                cout <<"Ano maximo: ";
                cin >> max;
                mt = cinemas.filtrarPorAno(min, max, filmes);
                break;
            }

            case 5:{
                int x, y, max;
                cout <<"Digite a coordenada x: ";
                cin >> x;
                cout <<"Digite a coordenada y: ";
                cin >> y;
                cout <<"Distancia maxima: ";
                cin >> max;
                mt = cinemas.filtrarPorDistancia(x, y, max);
                break;
            }
                

            case 6:{
                double max;
                cout <<"Preco: ";
                cin >> max;
                mt = cinemas.filtrarPorPreco(max);
                break;
            }

            case 7:{
                string id;
                cout <<"Digite o id: ";
                cin >> id;
                mt = cinemas.buscarPorFilme(id);
                break;
            }

            case 8:{
                auto inicio = high_resolution_clock::now();

                cout << "\nTotal: " << resultado.size() << endl;
                for(Cinema* c : resultado){
                    cout << c->getNome() << endl;
                }
 
                auto fim = high_resolution_clock::now();
                cout << "Tempo da busca: "
                << duration_cast<milliseconds>(fim - inicio).count()
                << " ms\n";

               cout << "\nPressione Enter para continuar...";
               cin.ignore();
               cin.get();

               continue;
            }

            case 0:
                cout << "Voltando...\n";
                break;

            default:
                cout << "Opcao invalida!\n";
        }

        auto fim = high_resolution_clock::now();
        cout << "Tempo do filtro: "
             << duration_cast<milliseconds>(fim - inicio).count()
             << " ms\n";

        if(escolha >= 1 && escolha <= 7){

            if(primeiraConsulta){
                resultado = mt;
                primeiraConsulta = false;
            } 
            else{
                int modo;
                cout << "1 - AND\n2 - OR\nEscolha: ";
                cin >> modo;

                if(modo == 1)
                    resultado = cinemas.intersecao(resultado, mt);
                else
                    resultado = cinemas.uniao(resultado, mt);
            }
            
        }

    }while(escolha != 0);
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
