#include "Cityes.h"

Cityes::Cityes(){

}

Cityes::Cityes(Contries location, string called){
    isIn = location;   
    name = called;
}

Cityes::~Cityes(){
               
}

void Cityes::setCountry(Contries location){
     isIn = location;
}

Contries Cityes::getCountry() const{
       return isIn;
}

void Cityes::setName(string called){
     name = called;
}

string Cityes::getName() const{
       return name;
}
