#include "parameter.nfo"

enum  occ{none, plancton, fish, shark};

struct tile{
    tile() : occBy(none) {}
    occ occBy;
    Fauna* animal;
};

tile** initMap(){
    
    tile** map = new tile*[SIZE];
    
    for (int i = 0; i < SIZE; i++){
       map[i] = new tile[SIZE]; 
    }
    
    return map;
}
