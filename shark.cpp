#include "fish.cpp"


void reproduce_S(Shark* s){
    
    Shark* newS = new Shark();
    newS->posX = s->posX;
    newS->posY = s->posY;

    sharks.push_back(newS);

    g_map[s->posX][s->posY].occBy = shark;
    g_map[s->posX][s->posY].animal = newS;
}



// look up surrounding tiles and moves to random one, if its free. If fish on a tile it moves to this one and the fish entry gets deleted. Increments age.


void moveShark(Shark* s){
    Surround sur = scan(s); 
    
    int x = rand()%4;
    bool moved = false;

    for(int i = 0; i < 4; i++){
        
       if(sur.t[x]->occBy == fish){

            g_map[s->posX][s->posY].animal = nullptr;
            g_map[s->posX][s->posY].occBy = none;
            
            //Check if old enough to reproduce and does if moved          
            if(s->age >= REPRODUCTION_AGE){
                reproduce_S(s);
                        printf("shay");
            }

            switch(x){
                case 0: s->posY = (s->posY+1)%SIZE;
                    break;
                case 1: s->posX = (s->posX+1)%SIZE;
                    break;
                case 2: s->posY = (SIZE+s->posY-1)%SIZE;
                    break;
                case 3: s->posX = (SIZE+s->posX-1)%SIZE;
                    break;
            }

            Fish* f = static_cast<Fish*>(sur.t[x]->animal);
            s->roundsNotEaten = 0;

            printf("shark ate\n");
            fishes.erase(std::remove( fishes.begin(), fishes.end(), f),fishes.end());
            delete f;
            sur.t[x]->occBy = shark;
            sur.t[x]->animal = s;
            
            i = 100;
            s->age++;
            moved = true;
        }
        x = (x+1)%4;
    }
    if(!moved){
        for(int i = 0; i < 4; i++){
            if(sur.t[x]->occBy == none){
                
                g_map[s->posX][s->posY].animal = nullptr;
                g_map[s->posX][s->posY].occBy = none;
                
                if(s->age >= REPRODUCTION_AGE){
                        reproduce_S(s);
                        printf("sharkbaby");
                }
                switch(x){
                    case 0: s->posY = (s->posY+1)%SIZE;
                        break;
                    case 1: s->posX = (s->posX+1)%SIZE;
                        break;
                    case 2: s->posY = (SIZE+s->posY-1)%SIZE;
                        break;
                    case 3: s->posX = (SIZE+s->posX-1)%SIZE;
                        break;
                }

                sur.t[x]->occBy = shark;
                sur.t[x]->animal = s;
                
                //Check if old enough to reproduce and does if moved          
                i = 100;
                s->age++;
                s->roundsNotEaten++;
            }
            x = (x+1)%4;
        } 
    }
printf("->%d%d\n",s->posX, s->posY);
}
