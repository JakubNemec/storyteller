#include <iostream>
#include <string>

using namespace std;

#ifndef CHARACTERS_H
#define CHARACTERS_H

class Characters{
      public:
      //constructor
      Characters();
      Characters(bool,string);
      //destructor
      ~Characters();
      //access
      bool flipMC();
      bool flipDead();
      void setName(string);
      string getName() const;             
      //mutation
      
      private:
      //vars
      bool MC;
      bool alive;
      string name;
      
};



#endif
