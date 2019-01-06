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

extern tile** g_map;

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

Surround scan(Fauna* f){
    Surround s;

    s.t[0] = &g_map[f->posX][(f->posY+1)%SIZE];          //MOD SIZE so if it leaves grid on one side it enters it on the other
    s.t[1] = &g_map[(f->posX+1)%SIZE][f->posY];
    s.t[2] = &g_map[f->posX][(SIZE+f->posY-1)%SIZE];
    s.t[3] = &g_map[(SIZE+f->posX-1)%SIZE][f->posY];

printf("%d", f->posX);
printf("%d", f->posY);
    printf("\n");
    return s;
}

void reproduce_F(Fish* f){
    
    Fish* newF = new Fish();
    newF->posX = f->posX;
    newF->posY = f->posY;

    fishes.push_back(newF);

    g_map[f->posX][f->posY].occBy = fish;
    g_map[f->posX][f->posY].animal = newF;
}

void killOld(){
    Fish* f;
    for(int i = 0; i < fishes.size(); i++){
        f = fishes[i];
        if(f->age >= MOVES_TILL_DEATH){
            g_map[f->posX][f->posY].animal = nullptr;
            g_map[f->posX][f->posY].occBy = none;
            delete fishes[i]; 
            fishes.erase(fishes.begin()+i);
            printf("fish died\n");
        }else i++;
    }
}

void moveFish(Fish* f){
    Surround s = scan(f); 
    
    int x = rand()%4;

    for(int i = 0; i < 4; i++){
        
       if(s.t[x]->occBy == none || s.t[x]->occBy == plancton){

            g_map[f->posX][f->posY].animal = nullptr;
            g_map[f->posX][f->posY].occBy = none;
            
            switch(x){
                case 0: f->posY = (f->posY+1)%SIZE;
                    break;
                case 1: f->posX = (f->posX+1)%SIZE;
                    break;
                case 2: f->posY = (SIZE+f->posY-1)%SIZE;
                    break;
                case 3: f->posX = (SIZE+f->posX-1)%SIZE;
                    break;
            }

            if(s.t[x]->occBy == plancton){
                Plancton* p = static_cast<Plancton*>(s.t[x]->animal);
                plancEaten(p);
                f->roundsNotEaten = 0;
                printf("fish ate\n");
            }else f->roundsNotEaten++;

            s.t[x]->occBy = fish;
            s.t[x]->animal = f;
            
            //Check if old enough to reproduce and does if moved          
            if(f->age >= REPRODUCTION_AGE){
                reproduce_F(f);
            }
            i = 100;
            f->age++;
        }
        x = (x+1)%4;    
    } 
}

