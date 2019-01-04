#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <vector>

#include "parameter.nfo"

enum  occ{none, plancton, fish, shark};

struct Fauna{
    int posX;
    int posY;
};

struct tile{
    tile() : occBy(none) {}
    occ occBy;
    Fauna* animal;
};

extern tile** g_map;

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

std::vector<Fish*> fishes;
Plancton planctons[NUM_OF_PLANCTON];
std::vector<Shark*> sharks;

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

tile* scan(Fauna f){
    tile surrounding[4];

    surrounding[0] = g_map[f.posX][f.posY+1];
    surrounding[1] = g_map[f.posX+1][f.posY];
    surrounding[2] = g_map[f.posX][f.posY-1];
    surrounding[3] = g_map[f.posX-1][f.posY];

    return surrounding;
}

void killOld(){
    for(auto i = fishes.begin(); i != fishes.end();){
        Fish* f = *i;
        if(f->age >= MOVES_TILL_DEATH){
            i = fishes.erase(i);
        }else i++;
    }
}

void moveFish(Fish f){

    tile* surr = scan(f); 


    srand(time(0));
    int x = rand()%4;

    for(int i = 0; i < 4; i++){
        
        if(surr[x].occBy == none || surr[x].occBy == plancton){
            switch(x){
                case 0: f.posY+1;
                    break;
                case 1: f.posX+1;
                    break;
                case 2: f.posY-1;
                    break;
                case 3: f.posX-1;
                    break;
            }

            if(surr[x].occBy == plancton){
                Plancton* p = static_cast<Plancton*>(surr[x].animal);
                plancEaten(p);
                f.roundsNotEaten = 0;
            }else f.roundsNotEaten++;

            surr[x].occBy = fish;
            surr[x].animal = &f;
            
            //Check if old enough to reproduce and does if moved          
            if(f.age >= REPRODUCTION_AGE){
               
                Fish* newF = new Fish();
                newF->posX = f.posX;
                newF->posY = f.posY;

                fishes.push_back(newF);

                g_map[f.posX][f.posY].occBy = fish;
                g_map[f.posX][f.posY].animal = new Fish();
            }
        }
        x = (x+1)%4;    
        f.age++;
    } 
}

