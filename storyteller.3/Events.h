#include <iostream>
#include <string>
#include "Defenitions.h"

#define eInputSize 20
#define cutoff 0//may set to event specific...

using namespace std;

#ifndef EVENTS_H
#define EVENTS_H

class Events{
      public:
      //constructor
      Events();
      Events(string);
      //destructor
      ~Events();
      //access
      void setName(string);
	  void setInput(int*, int);
	  void setReq(int[maxArcFlags], int[maxEventFlags], int[maxFlagTriggers]);
	  void updateFlags(int[maxEventFlags]);//todo
      int getInputLength() const;
      int getInput(int) const;
	  string getName() const;
	  double checkReq(int[maxArcFlags], int[maxEventFlags]) const;
      
      private:
      //vars
      string name;
      int inputLength;
	  int inputC[eInputSize];
	  int reqAFlags[maxArcFlags];
	  int reqEFlags[maxEventFlags];
	  int triggerFlags[maxFlagTriggers];
      
};



#endif
