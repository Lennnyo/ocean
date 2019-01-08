#include "fauna.cpp"


//takes current position an creates new fish entry

void reproduce_F(Fish* f){
    
    Fish* newF = new Fish();
    newF->posX = f->posX;
    newF->posY = f->posY;

    fishes.push_back(newF);

    g_map[f->posX][f->posY].occBy = fish;
    g_map[f->posX][f->posY].animal = newF;
}



// look up surrounding tiles and moves to random one, if its free or has plancton. In last case it calls plancEaten() and resets roundsNotEaten. Increments age.

void moveFish(Fish* f){
    Surround s = scan(f); 
    Plancton* p = nullptr; 
    int x = rand()%4;

    for(int i = 0; i < 4; i++){
        
       if(s.t[x]->occBy == none || s.t[x]->occBy == plancton){

            g_map[f->posX][f->posY].animal = nullptr;
            g_map[f->posX][f->posY].occBy = none;
            
            //Check if old enough to reproduce and does if moved          
            if(f->age >= REPRODUCTION_AGE){
                reproduce_F(f);
                        printf("fishbaby");
            }
            
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
            
printf("->%d%d\n",f->posX, f->posY);

            if(s.t[x]->occBy == plancton){
                p = static_cast<Plancton*>(s.t[x]->animal);
                plancEaten(p);
                f->roundsNotEaten = 0;
                printf("fish ate\n");
            }else f->roundsNotEaten++;

            g_map[f->posX][f->posY].occBy = fish;
            g_map[f->posX][f->posY].animal = f;
            
            i = 100;
            f->age++;
        }


        x = (x+1)%4;    
    } 
}
