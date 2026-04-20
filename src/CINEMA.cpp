#include "CINEMA.H"

using namespace std;

Cinema::Cinema(){}
Cinema::~Cinema(){}

string Cinema::getId(){
    return id;
}
void Cinema::setId(string id){
    this->id = id;
}

string Cinema::getNome(){
    return nome;
}
void Cinema::setNome(string nome){
    this->nome = nome;
}

int Cinema::getX(){
    return x;
}
void Cinema::setX(int x){
    coordenada_x = x;
}

int Cinema::getY(){
    return y;
}
void Cinema::setY(int y){
    coordenada_y = y;
}

double Cinema::getPreco(){
    return preco;
}
void Cinema::setPreco(double preco){
    this->preco = preco;
}

vector<string>Cinema::getFilmes(){
    return filmesIds;
}

void Cinema::addFilme(string id){
    filmesIds.push_back(id);
}

bool Cinema::temFilme(string id){
    for(int i=0; i<filmesIds.size(); i++){
        if(filmesIds[i]==id)return true;
    }
    return false;
}




