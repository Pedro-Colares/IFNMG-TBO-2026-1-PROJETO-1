#include <vector>
using namespace std;

template<typename T>
void Merge(vector<T>& L, int e, int m, int d, bool (*compara)(T, T)){
    vector<T> temp;
    int i = e;
    int j = m;

    while (i<m && j<d){
        if(compara(L[i], L[j])){
            temp.push_back(L[i]);
            i++;
        }else{
            temp.push_back(L[j]);
            j++;
        }
    }

    while(i<m){
        temp.push_back(L[i]);
        i++;
    }

    while(j<d){
        temp.push_back(L[j]);
        j++;
    }
   
    for(int k=0; k<temp.size(); k++){
        L[e+k] = temp[k];
    }

}

template<typename T>
void MergeSort(vector<T>& L, int e, int d, bool (*compara)(T, T)){
    if(e<d-1){
        int m = (e+d)/2;
        MergeSort(L, e, m, compara);
        MergeSort(L, m, d, compara);
        Merge(L, e, m, d, compara);
    }
}
 