#include <iostream>
#include <string>

using namespace std;

#ifndef WORLDS_H
#define WORLDS_H

class Worlds{
      public:
      //constructor
      Worlds();
      Worlds(string);
      //destructor
      ~Worlds();
      //access
      void setName(string);
      string getName() const;      
      //mutation
      
      private:
      //vars
      string name;
};



#endif
