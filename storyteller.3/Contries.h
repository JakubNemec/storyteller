#include <iostream>
#include <string>

using namespace std;

#include "Worlds.h"

#ifndef CONTRIES_H
#define CONTRIES_H

class Contries{
      public:
      //constructor
      Contries();
      Contries(Worlds, string);
      //destructor
      ~Contries();
      //access
      void setWorld(Worlds);
      Worlds getWorld() const;
      void setName(string);
      string getName() const;
      //mutation      
      
      private:
      //vars
      Worlds isOn;
      string name;
             
};



#endif
