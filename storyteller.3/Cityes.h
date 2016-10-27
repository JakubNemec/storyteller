#include <iostream>
#include <string>

using namespace std;

#include "Contries.h"

#ifndef CITYES_H
#define CITYES_H

class Cityes{
      public:
      //constructor
      Cityes();
      Cityes(Contries, string);
      //destructor
      ~Cityes();
      //access
      void setCountry(Contries);
      Contries getCountry() const; 
      void setName(string);
      string getName() const;           
      //mutation
      
      private:
      //vars
      Contries isIn;
      string name;
};



#endif
