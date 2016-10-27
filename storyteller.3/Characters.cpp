#include "Characters.h"

Characters::Characters(){
     MC = 0;
     alive=1;     
}

Characters::Characters(bool focus, string called){
     MC = focus;     
     name = called;
     alive = 0;
}

Characters::~Characters(){
               
}

bool Characters::flipMC(){
     MC = !MC;
     return MC;
}

bool Characters::flipDead(){
     alive = !alive;
     return alive;
}

void Characters::setName(string called){
     name = called;
}

string Characters::getName() const{
       return name;
}

