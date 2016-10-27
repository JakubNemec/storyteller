#include "Contries.h"

Contries::Contries(){
      
}

Contries::Contries(Worlds location, string called){
    isOn = location;   
    name = called;
}

Contries::~Contries(){
               
}

void Contries::setWorld(Worlds location){
     isOn = location;
}
          
Worlds Contries::getWorld() const{
       return isOn;
}

void Contries::setName(string called){
     name = called;
}

string Contries::getName() const{
       return name;
}
