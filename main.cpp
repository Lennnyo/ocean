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

tile** g_map = initMap();

int main (void){

    initFauna();

    for(int i = 0; i < SIZE; i++){
        for (int j =0; j < SIZE; j++){
            if(g_map[i][j].occBy == fish) printf("F ");
            else if(g_map[i][j].occBy == shark) printf("S ");
            else if(g_map[i][j].occBy == plancton) printf("P ");
            else printf("o ");
        }
        printf("\n");
    }
            

    return 0;
}
