#include "Arcs.h"



Arcs::Arcs()

{   
	/*	: int Arcs::inputC[aInputSize] = { 
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1
}
int bob[aInputSize];
	std::fill(bob, bob + aInputSize, 0);
	inputC = bob;//( 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 );*/
}

Arcs::Arcs(string called,int num, int inSize, bool fin){
     name = called;
	 inputLength = inSize;
	 //int inputC(aInputSize);
     finale=fin;
     eventNum=num;
}

Arcs::~Arcs(){
	//delete[] inputC;
}

void Arcs::setName(string called){
     name = called;
}

void Arcs::setInput(int* in){
	for (int i = 0; i < aInputSize; i++) {
		inputC[i] = in[i];
	}
	inputLength = actorsPerEvent*5+1;
}

void Arcs::setEventNum(int num){
     eventNum=num;
}

void Arcs::setFinale(bool fin){
     finale=fin;
}

void Arcs::setReq(int flagA[maxArcFlags], int flagE[maxEventFlags], int triggers[maxFlagTriggers]){
	mid = false;
	for (int i = 0; i < maxArcFlags; i++){
		reqAFlags[i] = flagA[i];
		if (flagA[i] > 0){
			mid = true;
		}
	}	
	for (int i = 0; i < maxEventFlags; i++){
		reqEFlags[i] = flagE[i];
		if (flagE[i] > 0){
			mid = true;
		}
	}
	for (int i = 0; i < maxFlagTriggers; i++){
		if (triggers[i]>maxArcFlags){
			cout << "error: attempt to set flag to trigger to nonexistant arc flag" << endl;
			break;
		}
		triggerFlags[i] = triggers[i];
	}
}

void Arcs::updateFlags(int flags[maxArcFlags]){
	for (int i = 0; i < maxFlagTriggers; i++){ 
		int trigger = triggerFlags[i];
		if (trigger == -1){
			break;
		}
		else
		{
			flags[trigger] = 1;
		}
	}
}

int Arcs::getInputLength() const{
    return inputLength;
}

int Arcs::getEventNum() const{
    return eventNum;
}

bool Arcs::getIsMid() const{
	return mid;
}

bool Arcs::getFinale() const{
    return finale;
}

int Arcs::getInput(int place) const{
     return inputC[place];
}

double Arcs::checkReq(int flagA[maxArcFlags], int flagE[maxEventFlags]) const{
	double allFlags=0;
	double doneFlags=0;
	bool impossible = false;
	for (int i = 0; i < maxArcFlags; i++){
		if (reqAFlags[i]!=0){
			allFlags++;
			if (flagA[i]){
				doneFlags++;
			}
		}
		/*if (reqAFlags[i] == 2){
			cout << endl<< flagA[i] << " is on" << endl;
		}*/
		//-1 is a flag incompatible with this event, 2 is absolutely necesary
		if ((reqAFlags[i] == -1 && flagA[i]) || (reqAFlags[i] == 2 && !flagA[i])){
			cout << " impossible ";
			impossible = true;
		}
	}
	for (int i = 0; i < maxEventFlags; i++){
		if (reqEFlags[i] != 0){
			allFlags++;
			if (flagE[i]){
				doneFlags++;
			}
		}
		if ((reqEFlags[i] == -1 && flagE[i]) || (reqEFlags[i] == 2 && !flagE[i])){
			impossible = true;
		}
	}

	//result translates to the likelyhood that an event will happen given how many of it's flags are fufilled
	double result;
	//if there are no flags it's a free event. can happen whenever
	if (allFlags == 0){
		result = 1;
	}
	else if (impossible){
		result = 0;
	}
	else{
		result = (doneFlags + .1) / (allFlags + .1);//TODO:0/1 flags = possible but less likely then 1/2 flags...
		//if there are more events, a small minority won't cut it...
		if (result <= cutoff){
			result = 0;
		}
		//add more randomness
		if (result >= .85){
			result = .85;
		}
	}
	cout << "result; " << result << endl;
	return result;
}


void Arcs::fullInput(int result[aInputSize]) const{
	for (int i = 0; i < aInputSize; i++){ 
		if (i < inputLength)
			result[i] = inputC[i];
		else
			result[i] = 0;
	}
}

string Arcs::getName() const{
       return name;
}
