#include <stdio.h>

#include "shark.cpp"

tile** initMap(){

    tile** map = new tile*[SIZE];
    
    for (int i = 0; i < SIZE; i++){
       map[i] = new tile[SIZE]; 
    }

    return map;
}

void print_Map(){
    for(int i = 0; i < SIZE; i++){
        for (int j =0; j < SIZE; j++){
            if(g_map[i][j].occBy == fish) printf("F ");
            else if(g_map[i][j].occBy == shark) printf("S ");
            else if(g_map[i][j].occBy == plancton) printf("P ");
            else printf("o ");
        }
        printf("\n");
    }printf("\n");
}

tile** g_map = initMap();

int main (void){

    initFauna();
    print_Map();
    for(int i = 0; i < SIM_STEPS; i++){
        killOld();
        for(auto f : fishes){
            moveFish(f);
        }

        for(auto s: sharks){
            moveShark(s);
        }
        print_Map();
    }

    return 0;
}
