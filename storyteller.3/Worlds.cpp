#include "Worlds.h"

Worlds::Worlds(){
               
}

Worlds::Worlds(string called){
     name = called;
}

Worlds::~Worlds(){
               
}

void Worlds::setName(string called){
     name = called;
}

string Worlds::getName() const{
       return name;
}
