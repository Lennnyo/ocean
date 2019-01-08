#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>

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

struct Shark : Fauna{
    Shark() : age(0), roundsNotEaten(0) {}
    int age;
    int roundsNotEaten;
};

struct Plancton : Fauna{
};

struct tile{
    tile() : occBy(none) {}
    occ occBy;
    Fauna* animal;
};

struct Surround{
    tile* t[4];
};



//Declarations

extern tile** g_map;

std::vector<Fish*> fishes;
Plancton planctons[NUM_OF_PLANCTON];
std::vector<Shark*> sharks;




//initiate given number of fish, shark and plancton

void initFauna(){
    int x,y;

    for(int i = 0; i < NUM_OF_FISH; i++){
        srand(time(0));
        bool set = false;

        Fish* f = new Fish();
        fishes.push_back(f);

        while(!set){
            x = rand()%SIZE;
            y = rand()%SIZE;
       
            if(g_map[x][y].occBy == none){
                f->posX = x; 
                f->posY = y;
            
                g_map[x][y].occBy = fish;
                g_map[x][y].animal = f;

                set = true;
            }
        }
    }

    for(int i = 0; i < NUM_OF_SHARK; i++){
        srand(time(0));
        bool set = false;

        Shark* s = new Shark();
        sharks.push_back(s);

        while(!set){
            x = rand()%SIZE;
            y = rand()%SIZE;
   
            if(g_map[x][y].occBy == none){
                s->posX = x; 
                s->posY = y;
        
                g_map[x][y].occBy = shark;
                g_map[x][y].animal = s;

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
   
            if(g_map[x][y].occBy == none){
                p.posX = x; 
                p.posY = y;
        
                g_map[x][y].occBy = plancton;
                g_map[x][y].animal = &p;

                set = true;
            }
        }
    }
}


void plancEaten(Plancton* p){
    int x, y;

    srand(time(0));
    bool set = false;

    while(!set){
        x = rand()%SIZE;
        y = rand()%SIZE;
       
        if(g_map[x][y].occBy == none){
            p->posX = x; 
            p->posY = y;

            g_map[x][y].occBy = plancton;
            g_map[x][y].animal = p;

            set = true;
        }
    }
}


//retruns array with pointer to surroundig tiles

Surround scan(Fauna* f){
    Surround s;

    s.t[0] = &g_map[f->posX][(f->posY+1)%SIZE];          //MOD SIZE so if it leaves grid on one side it enters it on the other
    s.t[1] = &g_map[(f->posX+1)%SIZE][f->posY];
    s.t[2] = &g_map[f->posX][(SIZE+f->posY-1)%SIZE];
    s.t[3] = &g_map[(SIZE+f->posX-1)%SIZE][f->posY];

printf("%d", f->posX);
printf("%d", f->posY);
    return s;
}


//goes through fish and shark vector and deletes Entries that haven't eaten for a given time

void killOld(){
    Fish* f;
    Shark* s;
    int tmpSize = fishes.size();
    for(int i = 0; i < tmpSize; i){
        f = fishes[i];
        if(f->age >= MOVES_TILL_DEATH){
            g_map[f->posX][f->posY].animal = nullptr;
            g_map[f->posX][f->posY].occBy = none;
            delete fishes[i]; 
            fishes.erase(fishes.begin()+i);
            printf("fish died\n");
        }else i++;
        
        fishes.size() <= 0 ? i = 100 : i = i;
    }

    for(int i = 0; i < tmpSize; i){
        s = sharks[i];
        if(s->age >= MOVES_TILL_DEATH){
            g_map[s->posX][s->posY].animal = nullptr;
            g_map[s->posX][s->posY].occBy = none;
            delete sharks[i]; 
            sharks.erase(sharks.begin()+i);
            printf("shark died\n");
        }else i++;

        sharks.size() <= 0 ? i = 100 : i = i;
    }
}


