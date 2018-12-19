#include <stdio.h>

#include "fauna.cpp"
#include "parameter.nfo"

tile** initMap(){

    tile** map = new tile*[SIZE];
    
    for (int i = 0; i < SIZE; i++){
       map[i] = new tile[SIZE]; 
    }

    return map;
}
    


int main (void){

    tile** map = initMap();
    initFauna(map);

    for(int i = 0; i < SIZE; i++){
        for (int j =0; j < SIZE; j++){
            if(map[i][j].occBy == fish) printf("F ");
            else if(map[i][j].occBy == shark) printf("S ");
            else if(map[i][j].occBy == plancton) printf("P ");
            else printf("o ");
        }
        printf("\n");
    }
            

    return 0;
}
