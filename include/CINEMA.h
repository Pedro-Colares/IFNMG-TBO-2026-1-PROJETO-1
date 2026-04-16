#ifndef CINEMA_H
#define CINEMA_H

#include <string>
#include <vector>

using namespace std;

class Cinema{

private:
    string id;
    string nome;
    int coordenada_x;
    int coordenada_y;
    double preco;
    vector<string> filmesIds;

public:
    Cinema();
    ~Cinema();

    string getId();
    void setId(string id);

    string getNome();
    void setNome(string nome);

    int getX();
    void setX(int x);

    int getY();
    void setY(int y);

    double getPreco();
    void setPreco(double preco);

    vector<string> getFilmes();
    void addFilme(string id);

    bool temFilme(string id);
};
#endif