#include "Events.h"

Events::Events(){
               
}

Events::Events(string called){
     name = called;
}

Events::~Events(){
               
}

void Events::setName(string called){
     name = called;
}

void Events::setInput(int* in, int size){
	for (int i = 0; i < eInputSize; i++) {
		inputC[i] = in[i];
	}
	inputLength = size;
     
}

void Events::setReq(int flagA[maxArcFlags], int flagE[maxEventFlags], int triggers[maxFlagTriggers]){
	for (int i = 0; i < maxArcFlags; i++){
		reqAFlags[i] = flagA[i];
	}
	for (int i = 0; i < maxEventFlags; i++){
		reqEFlags[i] = flagE[i];
	}
	for (int i = 0; i < maxFlagTriggers; i++){
		if (triggers[i]>maxArcFlags){
			cout << "error: attempt to set flag to trigger to nonexistant event flag" << endl;
			break;
		}
		triggerFlags[i] = triggers[i];
	}
}

void Events::updateFlags(int flags[maxEventFlags]){
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

int Events::getInputLength() const{
    return inputLength;
}

int Events::getInput(int place) const{
     return inputC[place];
}

string Events::getName() const{
       return name;
}

double Events::checkReq(int flagA[maxArcFlags], int flagE[maxEventFlags]) const{
	double allFlags = 0;
	double doneFlags = 0;
	bool impossible = false;
	for (int i = 0; i < maxEventFlags; i++){
		if (reqAFlags[i] != 0){
			allFlags++;
			if (flagA[i]){
				doneFlags++;
			}
		}
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
		result = (doneFlags + .1) / (allFlags + .1);
		//if there are more events, a small minority won't cut it...
		if (result <= cutoff){
			result = 0;
		}
	}
	cout << "result; " << result << endl;
	return result;
}