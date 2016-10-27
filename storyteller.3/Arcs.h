#include <iostream>
#include <string>
#include "Defenitions.h"

#define aInputSize 1+5*actorsPerEvent
#define cutoff 0//may set to arc specific...


using namespace std;

#ifndef ARCS_H
#define ARCS_H

class Arcs{
      public:
      //constructor
      Arcs();
      Arcs(string,int,int,bool);
      //destructor
      ~Arcs();
      //access
      void setName(string);
      void setInput(int*);
      void setEventNum(int);
	  void setFinale(bool);
	  void setReq(int[maxArcFlags], int[maxEventFlags], int[maxFlagTriggers]);
	  void updateFlags(int[maxArcFlags]);
      int getInputLength() const;
      int getEventNum() const;
	  bool getIsMid() const;
      bool getFinale() const;
      int getInput(int) const;
	  double checkReq(int[maxArcFlags], int[maxEventFlags]) const;
	  void fullInput(int[aInputSize]) const;
      string getName() const;      
      //mutation
      
      private:
      //vars
      string name;
      int inputLength;
	  int inputC[aInputSize];
	  int reqAFlags[maxArcFlags];
	  int reqEFlags[maxEventFlags];
	  int triggerFlags[maxFlagTriggers];
      int eventNum;
	  bool mid;
      bool finale;
};



#endif
