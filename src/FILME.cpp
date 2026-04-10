#include "FILME.h"

using namespace std;

Filme::Filme(){
    tconst = "";
    titleType = "";
    primaryTitle = "";
    isAdult = false;
    startYear = 0;
    runtimeMinutes = 0;
}

Filme::~Filme() {}

string Filme::getId(){
    return tconst;
}
void Filme::setId(string id) {
    tconst = id;
}

string Filme::getTipo(){
    return titleType;
}
void Filme::setTipo(string tipo) {
    titleType = tipo;
}

string Filme::getTitulo(){
    return primaryTitle;
}
void Filme::setTitulo(string titulo) {
    primaryTitle = titulo;
}

int Filme::getAno(){
    return startYear;
}
void Filme::setStartYear(int ano) {
    startYear = ano;
}

int Filme::getDuracao(){
    return runtimeMinutes;
}
void Filme::setDuracao(int duracao) {
    runtimeMinutes = duracao;
}

vector<string> getGeneros(){
    return genres;
}
void Filme::addGenero(string genero) {
    genres.push_back(genero);
}

bool Filme::temGenero(string genero){
    for(string g: genres){
        if(g==genero)return true;
    }
    return false;
}

void Filme::setIsAdult(bool adult) {
    isAdult = adult;
}

bool Filme::ehDoTipo(string tipo){
    return titleType = tipo;
}

bool Filme::estaNoIntervaloAno(int min, int max){
    return startYear >= min && startYear <= max;
}

bool Filme::estaNoIntervaloDuracao(int min, int max){
    return runtimeMinutes >= min && runtimeMinutes <= max;
}