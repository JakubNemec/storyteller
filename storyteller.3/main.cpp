#include <iostream>
#include <string>
#include <list>
#include <ctime>

#include "Util.h"



using namespace std;

//int init(Worlds* worldList,Contries* contList,Cityes* cityList,Characters* peopleList,Events* eventList,int relationships[maxTotal][maxTotal]);

//string makeStory(string story,Worlds* worldList,Contries* contList,Cityes* cityList,Characters* peopleList,Events* eventList,int relationships[maxTotal][maxTotal]);

int main(){
    //reset rand
	srand(time(NULL));
	int seed=rand();
	srand(seed);
	//srand(24135);//3,5

    //make empty object lists
    Worlds worldList[maxWorlds];
    Contries contList[maxContries];
    Cityes cityList[maxCityes];
    Characters peopleList[maxPeople];
    Events eventList[maxEvents];
    Arcs arcList[maxArcs];
	//matrix of relationships
	int relationships[maxTotal][maxTotal];
	//list of flags for events
	int flagsE[maxEventFlags];
	//list fo flags for arcs
	int flagsA[maxArcFlags];
	for (int z = 0; z < 5; z++){//testing
		string story = "";

		int bob[aInputSize];
		std::fill(bob, bob + aInputSize, 0);
		arcList[0].setInput(bob);
		//cout << "in main: " << arcList[0].getInput()<<endl;
		//init objects
		init(worldList, contList, cityList, peopleList, eventList, arcList, relationships, flagsA, flagsE);
		cout << "init done" << endl;

		story = makeStory(story, worldList, contList, cityList, peopleList, eventList, arcList, relationships, flagsA, flagsE);

		cout << endl << endl << endl << "final story: " << endl << story;

		cout << endl << endl << "seed is " << seed;

		getchar();

		//testing start
		for (int i = 0; i < maxArcs; i++){
			flagsA[i] = 0;
		}
		for (int i = 0; i < maxEvents; i++){
			flagsE[i] = 0;
		}

	}//testing end
    //delete [] eventList;
   // delete [] peopleList;
   // delete [] cityList;
   // delete [] contList;
   // delete [] worldList;
   // delete [] arcList;
    
    return 0;
}

