#ifndef FILME_H
#define FILME_H

#include<string>
#include<vector>

using namespace std;

class Filme{

    public:
      string tconst;
      string titleType;
      string primaryTytle;
      bool isAdult;
      int starYear;
      int endYear;
      int runtimeMinutes;
      vector<string genres;
      
    Filme();
    virtual ~Filme();

};
#endif