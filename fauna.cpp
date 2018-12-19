#include <stdio.h>
#include <cstdlib>
#include <ctime>

#include "parameter.nfo"

enum  occ{none, plancton, fish, shark};


struct Fauna{
    int posX;
    int posY;
};

struct Fish : Fauna{
    Fish() : age(0), roundsNotEaten(0) {}
    int age;
    int roundsNotEaten; 
};

struct Plancton : Fauna{
};

struct Shark : Fauna{
    Shark() : age(0), roundsNotEaten(0) {}
    int age;
    int roundsNotEaten;
};

    struct tile{
    tile() : occBy(none) {}
    occ occBy;
    Fauna* animal;
};

void initFauna(tile** map){
    int x,y;

    Fish fishes[NUM_OF_FISH];
    Plancton planctons[NUM_OF_PLANCTON];
    Shark sharks[NUM_OF_SHARK];

    for(auto f : fishes){
        srand(time(0));
        bool set = false;

        while(!set){
            x = rand()%SIZE;
            y = rand()%SIZE;
       
            if(map[x][y].occBy == none){
                f.posX = x; 
                f.posY = y;
            
                map[x][y].occBy = fish;
                map[x][y].animal = &f;

                set = true;
            }
        }
    }

    for(auto s : sharks){
        srand(time(0));
        bool set = false;

        while(!set){
            x = rand()%SIZE;
            y = rand()%SIZE;
   
            if(map[x][y].occBy == none){
                s.posX = x; 
                s.posY = y;
        
                map[x][y].occBy = shark;
                map[x][y].animal = &s;

                set = true;
            }
        }
    }

    for(auto p : planctons){
        srand(time(0));
        bool set = false;

        while(!set){
            x = rand()%SIZE;
            y = rand()%SIZE;
   
            if(map[x][y].occBy == none){
                p.posX = x; 
                p.posY = y;
        
                map[x][y].occBy = plancton;
                map[x][y].animal = &p;

                set = true;
            }
        }
    }
}


void moveFish(){
}

void plancEaten(&Plancton p){

    srand(time(0));
    bool set = false;

    while(!set){
        x = rand()%SIZE;
        y = rand()%SIZE;
       
        if(map[x][y].occBy == none){
            p.posX = x; 
            p.posY = y;

            map[x][y].occBy = plancton;
            map[x][y].animal = &p;

            set = true;
        }
    }
}
