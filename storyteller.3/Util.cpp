#include "Util.h"

void arrayOut(int* content, int length){
	for (int i = 0; i < length; i++)
		cout << content[i]<< " , ";
}

bool anyOf(int* within, int till, int look)
{
	bool result = false;
	for (int i = 0; i < till - 1; i++){
		if (within[i] == look){
			result = true;
		}
	}
	return result;
}

//returns a name corsponding to the actor in relationship table numbering
string getNameFromRNumbering(int substitute, Worlds worldList[], Contries contList[], Cityes cityList[], Characters peopleList[]){
	string actor;
	if (substitute < maxPeople){
		actor = peopleList[substitute].getName();
	}
	else{
		substitute -= maxPeople;

		if (substitute < maxCityes){
			actor = cityList[substitute].getName();
		}
		else{
			substitute -= maxCityes;

			if (substitute < maxContries){
				actor = contList[substitute].getName();
			}
			else{
				substitute -= maxContries;

				if (substitute < maxWorlds){
					actor = worldList[substitute].getName();
				}
				else{
					cout << "the hell did this number get into chosen???" << endl;
				}
			}
		}
	}
	return actor;
}

//replaces all occurences of one substring with another in a string
string replace(string base, string placeholder, string insert){
	string updated = "";
	string substring;
	if (base.find(placeholder) == string::npos){
		//cout << base.find(placeholder)<<endl;
		updated = base;
	}
	else{
		while (base.find(placeholder) != string::npos){
			updated = updated + base.substr(0, base.find(placeholder)) + insert;
			base = base.substr(base.find(placeholder) + placeholder.length(), base.length());
		}
		updated = updated + base;
	}
	return updated;
}

/*temp[0]=number of actors needed. //max 6 atm.
	temp[1+5x]=actor type; -1= mc exclusive,0=none,  1=char, 2=city,3=contry, 4=world //[following is meaningless for mc]/ -2=edit?
	temp[2+5x]=relation to mc best be further from 0 then this number, but on the same side of 0.// 0 is irrelevant
	temp[3+5x]=actor2 type; -1= previously mentioned actor, 0=none, 1=char,2=city,3=contry, 4=world //additional relationship stipulation 
	temp[4+5x]=actor2 number; num of the actor in the role
	temp[5+5x]=relation to actor2 best be further from 0 then this number, but on the same side of 0.// 0 is irrelevant*/

int insertActors(Arcs current, Worlds worldList[], Contries contList[], Cityes cityList[], Characters peopleList[], int relationships[maxTotal][maxTotal],int chosen[actorsPerEvent]){
	int e;
	bool done = false;
	int loopCount = 0;
	int inputC[aInputSize];
	current.fullInput(inputC);
	string tale;
	while (!done){
		tale = current.getName();
		int counter = 0;
		int i = 0;
		for (; i < inputC[0];){
			if (inputC[1 + 5 * i] == -1){
				chosen[i] = 0;//mc is set to 0 for now
				i++;
			}
			else if (inputC[1 + 5 * i] == 1){
				e = rand() % (maxPeople - 1);
				while (peopleList[e].getName().empty() || anyOf(chosen, actorsPerEvent, e)){
					e = rand() % (maxPeople - 1);
				}
				double probability = 1;

				//if the relationship of the mc is on the required side
				if (inputC[2 + 5 * i] * relationships[1][e] > 0){
					//prob drops proportional to the difference of the actual and desired numbers.
					probability = probability*(pow(relationships[1][e], 2) / pow(inputC[2 + 5 * i], 2));
					if (probability > 1){
						probability = 1;
					}
				}
				else if(inputC[2 + 5 * i] != 0){
					probability = 0;
				}
				for (int pastCheck = 0; pastCheck < actorsPerEvent; pastCheck++){
					if (e == chosen[pastCheck]){
						probability = 0;
					}
				}
				//need to check secondary condition?
				if (probability != 0 && inputC[3 + 5 * i]!=0){
					//get the number in 'maxtotal'
					int other = inputC[4 + 5 * i];
					if (inputC[3 + 5 * i] > 1){
						other += maxPeople;
					}
					if (inputC[3 + 5 * i] > 2){
						other += maxCityes;
					}
					if (inputC[3 + 5 * i] > 3){
						other += maxContries;
					}
					if (inputC[3 + 5 * i] == -1){
						other = chosen[other];
					}
					//is the relationship on the right side?
					if (inputC[5 + 5 * i] * relationships[e][other] > 0){
						//prob drops proportional to the difference of the actual and desired numbers.
						probability = probability*(pow(relationships[e][other], 2) / pow(inputC[5 + 5 * i], 2));
					}
					else{
						probability = 0;
					}
				}

				//if a random number beats the probability, it happens
				if (probability > (double)rand() / RAND_MAX){
					chosen[i] = e;
					i++;
				}
				else{
					counter++;
				}
			}
			else if (inputC[1 + 5 * i] == 2){
				e = rand() % (maxCityes - 1);
				while (cityList[e].getName().empty() || anyOf(chosen, actorsPerEvent, e + maxPeople)){
					e = rand() % (maxCityes - 1);
				}
				
				e = e + maxPeople;

				double probability = 1;

				//if the relationship of the mc is on the required side
				if (inputC[2 + 5 * i] * relationships[1][e] > 0){
					//prob drops proportional to the difference of the actual and desired numbers.
					probability = probability*(pow(relationships[1][e], 2) / pow(inputC[2 + 5 * i], 2));
					if (probability > 1){
						probability = 1;
					}
				}
				else if (inputC[2 + 5 * i] != 0){
					probability = 0;
				}

				//need to check secondary condition?
				if (probability != 0 && inputC[3 + 5 * i] != 0){

					//get the number in 'maxtotal'
					int other = inputC[4 + 5 * i];
					if (inputC[3 + 5 * i] > 1){
						other += maxPeople;
					}
					if (inputC[3 + 5 * i] > 2){
						other += maxCityes;
					}
					if (inputC[3 + 5 * i] > 3){
						other += maxContries;
					}
					if (inputC[3 + 5 * i] == -1){
						other = chosen[other];
					}

					//cout << other;
					//getchar();

					//is the relationship on the right side?
					if (inputC[5 + 5 * i] * relationships[e][other] > 0){
						//prob drops proportional to the difference of the actual and desired numbers.
						probability = probability*(pow(relationships[e][other], 2) / pow(inputC[5 + 5 * i], 2));
					}
					else{
						probability = 0;
					}
				}
								
				//if a random number beats the probability, it happens
				if (probability > (double)rand() / RAND_MAX){
					chosen[i] = e;
					arrayOut(chosen, 6);
					//getchar();
					i++;
				}
				else{
					counter++;
				}
			}
			else if (inputC[1 + 5 * i] == 3){
				e = rand() % (maxContries - 1);
				while (contList[e].getName().empty() || anyOf(chosen, actorsPerEvent, e + maxPeople + maxCityes)){
					e = rand() % (maxContries - 1);
				}
				e = e + maxPeople + maxCityes;
				double probability = 1;

				//if the relationship of the mc is on the required side
				if (inputC[2 + 5 * i] * relationships[1][e] > 0){
					//prob drops proportional to the difference of the actual and desired numbers.
					probability = probability*(pow(relationships[1][e], 2) / pow(inputC[2 + 5 * i], 2));
					if (probability > 1){
						probability = 1;
					}
				}
				else if (inputC[2 + 5 * i] != 0){
					probability = 0;
				}

				//need to check secondary condition?
				if (probability != 0 && inputC[3 + 5 * i] != 0){

					//get the number in 'maxtotal'
					int other = inputC[4 + 5 * i];
					if (inputC[3 + 5 * i] > 1){
						other += maxPeople;
					}
					if (inputC[3 + 5 * i] > 2){
						other += maxCityes;
					}
					if (inputC[3 + 5 * i] > 3){
						other += maxContries;
					}
					if (inputC[3 + 5 * i] == -1){
						other = chosen[other];
					}
					//is the relationship on the right side?
					if (inputC[5 + 5 * i] * relationships[e][other] > 0){
						//prob drops proportional to the difference of the actual and desired numbers.
						probability = probability*(pow(relationships[e][other], 2) / pow(inputC[5 + 5 * i], 2));
					}
					else{
						probability = 0;
					}
				}

				//if a random number beats the probability, it happens
				if (probability > (double)rand() / RAND_MAX){
					chosen[i] = e;
					i++;
				}
				else{
					counter++;
				}
			}
			else if (inputC[1 + 5 * i] == 4){
				e = rand() % (maxWorlds - 1);
				while (worldList[e].getName().empty() || anyOf(chosen, actorsPerEvent, e + maxPeople + maxCityes + maxContries)){
					e = rand() % (maxWorlds - 1);
				}
				e = e + maxPeople + maxCityes + maxContries;
				double probability = 1;

				//if the relationship of the mc is on the required side
				if (inputC[2 + 5 * i] * relationships[1][e] > 0){
					//prob drops proportional to the difference of the actual and desired numbers.
					probability = probability*(pow(relationships[1][e], 2) / pow(inputC[2 + 5 * i], 2));
					if (probability > 1){
						probability = 1;
					}
				}
				else if (inputC[2 + 5 * i] != 0){
					probability = 0;
				}

				//need to check secondary condition?
				if (probability != 0 && inputC[3 + 5 * i] != 0){

					//get the number in 'maxtotal'
					int other = inputC[4 + 5 * i];
					if (inputC[3 + 5 * i] > 1){
						other += maxPeople;
					}
					if (inputC[3 + 5 * i] > 2){
						other += maxCityes;
					}
					if (inputC[3 + 5 * i] > 3){
						other += maxContries;
					}
					if (inputC[3 + 5 * i] == -1){
						other = chosen[other];
					}
					//is the relationship on the right side?
					if (inputC[5 + 5 * i] * relationships[e][other] > 0){
						//prob drops proportional to the difference of the actual and desired numbers.
						probability = probability*(pow(relationships[e][other], 2) / pow(inputC[5 + 5 * i], 2));
					}
					else{
						probability = 0;
					}
				}

				//if a random number beats the probability, it happens
				if (probability > (double)rand() / RAND_MAX){
					chosen[i] = e;
					i++;
				}
				else{
					counter++;
				}
			}
			//e = rand() % (maxArcs - 1);
			if (counter > 20/*maxTotal*/){
				cout << "failed to find the " << i <<"th actor"<<endl;
				break;
			}
		}

		
		loopCount++;

		//if nothing is found, give up and try a different arc
		if (loopCount == 100){
			cout << "no viable actors found in x loops..." << endl;
			done = true;
			return -1;
		}

		//if a colution was found and the loop exited normally
		if (i > (inputC[0]-1)){
			done = true;
			cout << "found actors";

			//Replace all placeholders in the tale with numerical representations in <>
			return 1;
		}
	}
	cout << "failed actors";
	return -1;
}

Arcs getArc(Worlds worldList[], Contries contList[], Cityes cityList[], Characters peopleList[], Events eventList[], Arcs arcList[], int relationships[maxTotal][maxTotal], int flagsA[maxArcs], int flagsE[maxEvents], int chosen[actorsPerEvent]){
	int e;
	bool done = false;
	int loopCount = 0;
	int order[maxArcs-1];
	//randomOrder(order);
	int position = -1;
	for (int i = 0; i < maxArcs-1; i++){
		order[i] = -1;
	}
	for (int i = 0; i < maxArcs-1; i++){
		int e = (rand() % maxArcs) + 1;
		while (e > 0){
			if (position + 1 == maxArcs)
				position = -1;
			if (order[position + 1] == -1){
				e--;
				position++;
			}
			else
				position++;
		}
		order[position] = i;
	}

	while (!done){

		//if nothing is found in x loops, assume the progran is stuck in a impossible situation.
		if (loopCount > 5){
			e = maxArcs - 1;
			cout << "No arc found in x loops...\n";
			break;
		}

		//run through avalible endings
		for (int i = 0; i < maxArcs-1; i++){
			e = order[i];
			if (arcList[e].getName().empty()){
				//check things exist and if then
			}
			else if (flagsA[e] > 0){
				//check if the arc has not yet occured.
			}
			//start with the endings and check them all
			else if (arcList[e].getFinale()){
				double rNum = ((double)rand() / (RAND_MAX));
				cout << arcList[e].getName() << " rand is " << rNum << " and result is ";
				if (arcList[e].checkReq(flagsA, flagsE) >= rNum){
					//the event is possible and the probability is beat by RNG, so if there ezist actors to do it, it happens

					//replace event placeholders with actors, 5 attempts
					for (int a = 0; a < 5; a++){
						int possible = insertActors(arcList[e], worldList, contList, cityList, peopleList, relationships, chosen);
						//if no actors fit the bill, the event can't happen, but won't count against loopcount.
						if (possible == -1){
							cout << "end " << arcList[e].getName() << endl;
						}
						else{
							done = true;
							i = maxArcs;
							arcList[e].updateFlags(flagsA);
							a = 100;
						}
					}
					if (done == false){
						cout << "failed to find sutable actors." << endl;
					}
				}
			}
		}

		//run through avalible mid events
		for (int i = 0; i < maxArcs-1; i++){
			if (done){
				break;
			}
			e = order[i];
			if (arcList[e].getName().empty()||done){
				//check things exist and if then
			}
			else if (flagsA[e] > 0){
				//check if the arc has not yet occured.
			}
			//start with the endings and check them all
			else if ((!arcList[e].getFinale()) && (arcList[e].getIsMid())){
				double rNum = ((double)rand() / (RAND_MAX));
				cout << arcList[e].getName() << " rand is " << rNum << " and result is ";
				if (arcList[e].checkReq(flagsA, flagsE) >= rNum){
					//the event is possible and the probability is beat by RNG, so if there ezist actors to do it, it happens

					//replace event placeholders with actors, 5 attempts
					for (int a = 0; a < 5; a++){
						int possible = insertActors(arcList[e], worldList, contList, cityList, peopleList, relationships, chosen);
						//if no actors fit the bill, the event can't happen, but won't count against loopcount.
						if (possible == -1){
							cout << "mid " << arcList[e].getName() << endl;
						}
						else{
							done = true;
							i = maxArcs;
							arcList[e].updateFlags(flagsA);
							a = 100;
						}
					}
					if (done == false){
						cout << "failed to find sutable actors." << endl;
					}
				}
			}
		}

		//run through base events
		for (int i = 0; i < maxArcs-1; i++){
			if (done){ 
				break;
			}
			e = order[i];
			if (arcList[e].getName().empty()||done){
				//check things exist and if then
			}
			else if (flagsA[e] > 0){
				//check if the arc has not yet occured.
			}
			//start with the endings and check them all
			else if (!arcList[e].getIsMid()){
				double rNum = ((double)rand() / (RAND_MAX));
				cout << arcList[e].getName() << " rand is " << rNum << " and result is ";
				//getchar();
				if (arcList[e].checkReq(flagsA, flagsE) >= rNum){
					//the event is possible and the probability is beat by RNG, so if there ezist actors to do it, it happens

					//replace event placeholders with actors, 5 attempts
					for (int a = 0; a < 5; a++){
						int possible = insertActors(arcList[e], worldList, contList, cityList, peopleList, relationships, chosen);
						//if no actors fit the bill, the event can't happen, but won't count against loopcount.
						if (possible == -1){
							cout << "base " << arcList[e].getName() << endl;
						}
						else{
							done = true;
							i = maxArcs;
							arcList[e].updateFlags(flagsA);
							a = 100;
						}
					}
					if (done == false){
						cout << "failed to find sutable actors." << endl;
					}
				}
			}
		}
		cout << done << endl;
		//getchar();

		//update loopCount
		loopCount++;
	}
	return arcList[e];
}
Events getEvent(Worlds worldList[], Contries contList[], Cityes cityList[], Characters peopleList[], Events eventList[], Arcs arcList[], int relationships[maxTotal][maxTotal], int flagsA[maxArcs], int flagsE[maxEvents], int chosen[actorsPerEvent]){
	int e;
	bool done = false;
	int loopCount = 0;
	while (!done){
		//if no event is found in x loops the event is skipped
		if (loopCount > 200){
			e = maxEvents - 1;
			cout << "No event found in x loops...\n";
			break;
		}

		//choose random event
		e = rand() % (maxEvents - 1);
		if (eventList[e].getName().empty()){
			//check things exist and if then
		}
		else if (flagsE[e] > 0){
			//check if the event has not yet occured.
		}
		else{
			double rNum = ((double)rand() / (RAND_MAX));
			cout << eventList[e].getName() << " rand is " << rNum << " and result is ";
			if (eventList[e].checkReq(flagsA, flagsE) >= rNum){
				//the event is possible and the probability is beat by RNG, so it happens
				done = true;
				eventList[e].updateFlags(flagsE);
			}
			//getchar();
		}
		loopCount++;
	}
	return eventList[e];
}

string makeStory(string Story, Worlds worldList[], Contries contList[], Cityes cityList[], Characters peopleList[], Events eventList[], Arcs arcList[], int relationships[maxTotal][maxTotal], int flagsA[maxArcs], int flagsE[maxEvents]){
       bool done = false;
       while(!done){
		   int chosen[actorsPerEvent];//stores the event actors in the maxTotal numbering nonexistant = -100
		   for (int i = 0; i < actorsPerEvent; i++){
			   chosen[i] = -100;
		   }
            //get an arc to add
		   Arcs step = getArc(worldList, contList, cityList, peopleList, eventList, arcList, relationships, flagsA,flagsE,chosen);
			string arcContent = step.getName();
            //is it an ending?
            done = step.getFinale();

			arrayOut(chosen, 6);

			//translate placeholders into actors  TODO handel no arcs found, ect...
			if (chosen[0] != -100){
				string actor = getNameFromRNumbering(chosen[0], worldList, contList, cityList, peopleList);
				arcContent = replace(arcContent, "<A>", actor);
			}
			if (chosen[1] != -100){
				string actor = getNameFromRNumbering(chosen[1], worldList, contList, cityList, peopleList);
				arcContent = replace(arcContent, "<B>", actor);
			}
			if (chosen[2] != -100){
				string actor = getNameFromRNumbering(chosen[2], worldList, contList, cityList, peopleList);
				arcContent = replace(arcContent, "<C>", actor);
			}
			if (chosen[3] != -100){
				string actor = getNameFromRNumbering(chosen[3], worldList, contList, cityList, peopleList);
				arcContent = replace(arcContent, "<D>", actor);
			}
			if (chosen[4] != -100){
				string actor = getNameFromRNumbering(chosen[4], worldList, contList, cityList, peopleList);
				arcContent = replace(arcContent, "<E>", actor);
			}
			if (chosen[5] != -100){
				string actor = getNameFromRNumbering(chosen[5], worldList, contList, cityList, peopleList);
				arcContent = replace(arcContent, "<F>", actor);
			}
            
			//get add events
			size_t pos = 0;
			string delimiter = "<event>";
			//replace each <event> placeholder with an actual event
			while ((pos = arcContent.find(delimiter)) != std::string::npos) {
				//find the next <event> slot in the arc
				string part = arcContent.substr(0, pos);
				arcContent.erase(0, pos + delimiter.length());
				//find an event to go there
				Events subStep = getEvent(worldList, contList, cityList, peopleList, eventList, arcList, relationships, flagsA, flagsE,chosen);

				//place the event in the arc
				arcContent = part + subStep.getName() + arcContent;
			}

            //add to story
			Story = Story + arcContent + "\n\n";
			cout << arcContent;
			//getchar();
       }
       

       return Story;
}

int init(Worlds worldList[], Contries contList[], Cityes cityList[], Characters peopleList[], Events eventList[], Arcs arcList[], int relationships[maxTotal][maxTotal], int flagsA[maxArcs], int flagsE[maxEvents]){

	//set flags to 0
	for (int i = 0; i < maxArcs; i++){
		flagsA[i] = 0;
	}
	for (int i = 0; i < maxEvents; i++){
		flagsE[i] = 0;
	}

	//cout << "in init: " << arcList[0].getInput() << endl;
	//set worlds
    worldList[0].setName("Outer Lands");
    worldList[1].setName("Qliphoth");
    
    //set contries
    contList[0].setName("Kimlasca");
    contList[0].setWorld(worldList[0]);
    
    contList[1].setName("Malkuth");
    contList[1].setWorld(worldList[0]);
    
    contList[2].setName("Qliphoth Safezone");
    contList[2].setWorld(worldList[1]);
    
    contList[3].setName("Daath");
    contList[3].setWorld(worldList[0]);
    
    contList[4].setName("Aberria");
    contList[4].setWorld(worldList[0]);
    
    //set cityes
    cityList[0].setName("Baticul");
    cityList[0].setCountry(contList[0]);
    
    cityList[1].setName("Belkend");
    cityList[1].setCountry(contList[0]);
    
    cityList[2].setName("Sheridan");
    cityList[2].setCountry(contList[0]);
    
    cityList[3].setName("Kaitzur");
    cityList[3].setCountry(contList[0]);
    
    cityList[4].setName("Grand Chokmah");
    cityList[4].setCountry(contList[1]);
    
    cityList[5].setName("St. Binah");
    cityList[5].setCountry(contList[1]);
    
    cityList[6].setName("Keterburg");
    cityList[6].setCountry(contList[1]);
    
    cityList[7].setName("Engeve");
    cityList[7].setCountry(contList[1]);
    
    cityList[8].setName("Akzeriuth");
    cityList[8].setCountry(contList[1]);
    
    cityList[9].setName("Yulia City");
    cityList[9].setCountry(contList[2]);
    
    cityList[10].setName("Daath City");
    cityList[10].setCountry(contList[3]);
    
    cityList[11].setName("Chesedonia");
    cityList[11].setCountry(contList[3]);
    
    //set people
    peopleList[0].setName("Luke von Fabre");
    peopleList[1].setName("Natalia Luzu Kimlasca-Lanvaldear");
    peopleList[2].setName("Van Grants");
    peopleList[3].setName("Tear Grants");
    peopleList[4].setName("Guy Cecil");
    peopleList[5].setName("Jade Curtiss");
    peopleList[6].setName("Anise Tatlin");
    peopleList[7].setName("Fon Master Ion");
    peopleList[8].setName("Arietta");
    peopleList[9].setName("Asch the Bloody");
    peopleList[10].setName("Largo");
    peopleList[11].setName("Dist");
    peopleList[12].setName("Synch");
    peopleList[13].setName("Mohs");
    peopleList[14].setName("Jozette Cecille");
    peopleList[15].setName("Aslan Frings");
    peopleList[16].setName("Yulia Jue");
    peopleList[17].setName("Lorelei");
    peopleList[18].setName("Yulia Jue");
    peopleList[19].setName("King Ingobert VI");
    peopleList[20].setName("Emperor Peony Upala Malkuth IX");
    peopleList[21].setName("Mayor Teodoro");
    peopleList[22].setName("Astor");
     
    //set relationships 200 (shows that entry is untouched)
	for (int i = 0; i < maxTotal - 1; i++){
		for (int j = 0; j < maxTotal - 1; j++){
			relationships[i][j] = 200;
		}
	}

	//set relationships 100 to -100, where the diagonal is 0 and each side is a mirror image
	for (int i = 0; i<maxTotal - 1; i++){
		for (int j = 0; j<maxTotal - 1; j++){
			if (i==j){
				relationships[i][j] = 0;
			}
			else if (relationships[j][i] == 200){
				  relationships[i][j] = rand() % 201 - 100;
			}
			else{
				  relationships[i][j] = relationships[j][i];
			}
        }
    }
    
    
     
    //set arcs
	/*legend
	temp[0]=number of actors needed. //max 6 atm.
	temp[1+5x]=actor type; -1= mc exclusive,0=none,  1=char, 2=city,3=contry, 4=world //[following is meaningless for mc]/ -2=edit?
	temp[2+5x]=relation to mc best be further from 0 then this number, but on the same side of 0.// 0 is irrelevant
	temp[3+5x]=actor2 type; -1= previously mentioned actor, 0=none, 1=char,2=city,3=contry, 4=world //additional relationship stipulation 
	temp[4+5x]=actor2 number; num of the actor in the role
	temp[5+5x]=relation to actor2 best be further from 0 then this number, but on the same side of 0.// 0 is irrelevant
	quality= */
    int temp[aInputSize];
	int tempA[maxArcFlags];
	int tempE[maxEventFlags];
	int tempT[maxFlagTriggers];//-1 for ones not set

	std::fill(temp, temp + aInputSize, 0);
	std::fill(tempA, tempA + maxArcFlags, 0);
	std::fill(tempE, tempE + maxEventFlags, 0);
	std::fill(tempT, tempT + maxFlagTriggers, -1);
	tempT[0] = 0;//set to self in case relevant in future
	temp[0] = 4; //4 actors
	temp[1] = -1; //mc
	temp[6] = 1; temp[7] = 40; //positive with mc
	temp[11] = 3; temp[12] = 50; //positive with mc
	temp[16] = 3; temp[18] = -1; temp[19] = 3; temp[20] = -20;//slightly antagonistic to 3d actor

    arcList[0].setName("<A> and <B> are caught up in a hyperresonance and are teleported from <C> to <D>. They journey back. \n<event> \n<event> \nThey reach <C>.");
    arcList[0].setInput(temp);
    arcList[0].setEventNum(1);
    arcList[0].setFinale(false);
	arcList[0].setReq(tempA, tempE, tempT);

	std::fill(temp, temp + aInputSize, 0);
	std::fill(tempA, tempA + maxArcFlags, 0);
	std::fill(tempE, tempE + maxEventFlags, 0);
	std::fill(tempT, tempT + maxFlagTriggers, -1);
	tempT[0] = 1;
	temp[0] = 2; //2 actors
	temp[1] = -1; //mc
	temp[6] = 2; temp[7] = 1;//city positive with mc

    arcList[1].setName("<A> journyes to <B> and gets involved in flight reaserch. \n<event> \nWith <A>'s help, the reserch succeeds in making a functional aircraft.");
    arcList[1].setInput(temp);
    arcList[1].setEventNum(1);
	arcList[1].setFinale(false);
	arcList[1].setReq(tempA, tempE, tempT);
    
	std::fill(temp, temp + aInputSize, 0);
	std::fill(tempA, tempA + maxArcFlags, 0);
	std::fill(tempE, tempE + maxEventFlags, 0);
	std::fill(tempT, tempT + maxFlagTriggers, -1);
	tempT[0] = 2;
	temp[0] = 4; //4 actors
	temp[1] = 1; //mc
	temp[6] = 1; temp[7] = -50; //rather negarive with mc
	temp[11] = 1; temp[12] = 30; //positive with mc
	temp[16] = 2; temp[18] = -1; temp[19] = 2; temp[20] = 1;//non-antagonistic to 2d actor

    arcList[2].setName("<C> is kidnapped by <B>. <A> goes to <D> to rescue <C>. \n<event> \n<A> rescues <C>. \n<event>");
    arcList[2].setInput(temp);
    arcList[2].setEventNum(1);
	arcList[2].setFinale(false);
	arcList[2].setReq(tempA, tempE, tempT);

	std::fill(temp, temp + aInputSize, 0);
	std::fill(tempA, tempA + maxArcFlags, 0);
	std::fill(tempE, tempE + maxEventFlags, 0);
	std::fill(tempT, tempT + maxFlagTriggers, -1);
	tempT[0] = 3;
	temp[0] = 2; //2 actors
	temp[1] = -1; //mc
	temp[6] = 2; //any city

	tempE[5] = 2;//must learn of fon gates first*

    arcList[3].setName("<A> goes to <B> and powers up the fone gates.");
    arcList[3].setInput(temp);
    arcList[3].setEventNum(1);
	arcList[3].setFinale(false);
	arcList[3].setReq(tempA, tempE, tempT);

	std::fill(temp, temp + aInputSize, 0);
	std::fill(tempA, tempA + maxArcFlags, 0);
	std::fill(tempE, tempE + maxEventFlags, 0);
	std::fill(tempT, tempT + maxFlagTriggers, -1);
	tempT[0] = 4;
	temp[0] = 2; //2 actors
	temp[1] = -1; //mc
	temp[6] = 1; temp[7] = -60; //negative with mc

	tempE[1] = 2;//axeriuth in crisis*
    
    arcList[4].setName("<A> goes to axeriuth. \n<event> \n<B> tricks <A> into manipulating the fone gates. Axeriuth is destroyed.");
    arcList[4].setInput(temp);
    arcList[4].setEventNum(1);
    arcList[4].setFinale(false);
	arcList[4].setReq(tempA, tempE, tempT);
    
	std::fill(temp, temp + aInputSize, 0);
	std::fill(tempA, tempA + maxArcFlags, 0);
	std::fill(tempE, tempE + maxEventFlags, 0);
	std::fill(tempT, tempT + maxFlagTriggers, -1);
	tempT[0] = 5;
	temp[0] = 1; //1 actor
	temp[1] = -1; //mc

	tempA[1] = 1;//flight reaserch
	tempE[0] = 2; tempE[8] = 1;//learn of the fonstone*

    arcList[5].setName("<A> set out to find the lost seventh fone stone. \n<event> \nThe seventh fone stone was found and retrived.");
    arcList[5].setInput(temp);
    arcList[5].setEventNum(1);
	arcList[5].setFinale(false);
	arcList[5].setReq(tempA, tempE, tempT);
    
	std::fill(temp, temp + aInputSize, 0);
	std::fill(tempA, tempA + maxArcFlags, 0);
	std::fill(tempE, tempE + maxEventFlags, 0);
	std::fill(tempT, tempT + maxFlagTriggers, -1);
	tempT[0] = 6;
	temp[0] = 2; //2 actors
	temp[1] = 3; temp[2] = 30; //a countrie positive with mc
	temp[6] = 3; temp[8] = -1; temp[9] = 1; temp[10] = -20;//negative with 2nd actor

	tempA[4] = 1; //destroy axeriuth
	tempE[0] = 1; tempE[4] = 1; tempE[6] = 1;//hear rumors of war or learn of the fonstone that predicts it

    arcList[6].setName("<A> goes to war with <B>.");
    arcList[6].setInput(temp);
    arcList[6].setEventNum(1);
	arcList[6].setFinale(false);
	arcList[6].setReq(tempA, tempE, tempT);

	std::fill(temp, temp + aInputSize, 0);
	std::fill(tempA, tempA + maxArcFlags, 0);
	std::fill(tempE, tempE + maxEventFlags, 0);
	std::fill(tempT, tempT + maxFlagTriggers, -1);
	tempT[0] = 7;
	temp[0] = 1; //1 actor
	temp[1] = -1; //mc

	tempA[6] = 2;//start war*
    
    arcList[7].setName("<A> stops the war.");
    arcList[7].setInput(temp);
    arcList[7].setEventNum(1);
	arcList[7].setFinale(false);
	arcList[7].setReq(tempA, tempE, tempT);

	std::fill(temp, temp + aInputSize, 0);
	std::fill(tempA, tempA + maxArcFlags, 0);
	std::fill(tempE, tempE + maxEventFlags, 0);
	std::fill(tempT, tempT + maxFlagTriggers, -1);
	tempT[0] = 8;
	temp[0] = 1; //1 actor
	temp[1] = -1; //mc

	tempA[3] = 1;tempA[4] = 1;//power up fon gates and destroy axeriuth

    arcList[8].setName("<A> meets with the world's leaders and convinces them that the current situation cannot last. \n<event> \n<A> uses the fone gates to lower the outer land into the qulipoth.");
    arcList[8].setInput(temp);
    arcList[8].setEventNum(1);
	arcList[8].setFinale(false);
	arcList[8].setReq(tempA, tempE, tempT);

	std::fill(temp, temp + aInputSize, 0);
	std::fill(tempA, tempA + maxArcFlags, 0);
	std::fill(tempE, tempE + maxEventFlags, 0);
	std::fill(tempT, tempT + maxFlagTriggers, -1);
	tempT[0] = 9;
	tempA[8] = 2; tempA[7] = 2;//stop war* and lower land*

    arcList[9].setName("all plots stopped and world safe");
    arcList[9].setInput(temp);
    arcList[9].setEventNum(1);
	arcList[9].setFinale(true);
	arcList[9].setReq(tempA, tempE, tempT);

	std::fill(temp, temp + aInputSize, 0);
	std::fill(tempA, tempA + maxArcFlags, 0);
	std::fill(tempE, tempE + maxEventFlags, 0);
	std::fill(tempT, tempT + maxFlagTriggers, -1);
	tempT[0] = 10;
	tempA[4] = 1; tempA[5] = 2; tempA[6] = 1; tempA[7] = -1;//find fonstone*, war ongoing and destroy axeriuth
    
    arcList[10].setName("100 years of prosperity (then doom...)");
    arcList[10].setInput(temp);
    arcList[10].setEventNum(1);
	arcList[10].setFinale(true);
	arcList[10].setReq(tempA, tempE, tempT);
    
	std::fill(temp, temp + aInputSize, 0);
	std::fill(tempA, tempA + maxArcFlags, 0);
	std::fill(tempE, tempE + maxEventFlags, 0);
	std::fill(tempT, tempT + maxFlagTriggers, -1);
	tempT[0] = 11;
	tempA[2] = 2; tempA[3] = 2; tempA[12] = 1;//kidnap*, explore cloning facility and power up gates*
	tempE[9] = 1;//learn of cloning

	arcList[11].setName("world born anew (with clones)");
	arcList[11].setInput(temp);
	arcList[11].setEventNum(1);
	arcList[11].setFinale(true);
	arcList[11].setReq(tempA, tempE, tempT);
	
	std::fill(temp, temp + aInputSize, 0);
	std::fill(tempA, tempA + maxArcFlags, 0);
	std::fill(tempE, tempE + maxEventFlags, 0);
	std::fill(tempT, tempT + maxFlagTriggers, -1);
	tempT[0] = 12;
	temp[0] = 1; //1 actors
	temp[1] = -1; //mc

	tempE[9] = 2; //learn of cloning* 

	arcList[12].setName("<A> explores a shutdown experimental cloning facility. <event> <A> learns of the horrors of cloning and the emmense amounts of energy it requires.");
	arcList[12].setInput(temp);
	arcList[12].setEventNum(1);
	arcList[12].setFinale(false);
	arcList[12].setReq(tempA, tempE, tempT);

	//the error event; used only to end the story if no other arcs can be triggered.
	std::fill(temp, temp + aInputSize, 0);
	std::fill(tempA, tempA + maxArcFlags, 0);
	std::fill(tempE, tempE + maxEventFlags, 0);
	std::fill(tempT, tempT + maxFlagTriggers, -1);

	arcList[maxArcs - 1].setName("ERROR: no other arcs avalible. tale cannot be finished and ended prematurely.");
	arcList[maxArcs - 1].setInput(temp);
	arcList[maxArcs - 1].setEventNum(1);
	arcList[maxArcs - 1].setFinale(true);
	arcList[maxArcs - 1].setReq(tempA, tempE, tempT);
    
    /*input legend;
    type;
    1=world
    2=contry
    3=city
    4=character
    */
    //set events
	std::fill(tempA, tempA + maxArcFlags, 0);
	std::fill(tempE, tempE + maxEventFlags, 0);
	std::fill(tempT, tempT + maxFlagTriggers, -1);
	tempT[0] = 0;
    int temp1[3] = {1,1,3};
	tempE[8] = 1;//learn about fonestones
	eventList[0].setName("learn of the lost seventh fonestone");
	eventList[0].setInput(temp1, sizeof(temp1));
	eventList[0].setReq(tempA, tempE, tempT);

	std::fill(tempA, tempA + maxArcFlags, 0);
	std::fill(tempE, tempE + maxEventFlags, 0);
	std::fill(tempT, tempT + maxFlagTriggers, -1);
	tempT[0] = 1;
	int temp2[3] = { 4, 4, 3 };
	tempE[7] = 1;//hear of axeriuth
    eventList[1].setName("axeriuth in crisis");
	eventList[1].setInput(temp2, sizeof(temp2));
	eventList[1].setReq(tempA, tempE, tempT);

	std::fill(tempA, tempA + maxArcFlags, 0);
	std::fill(tempE, tempE + maxEventFlags, 0);
	std::fill(tempT, tempT + maxFlagTriggers, -1);
	tempT[0] = 2;
    int temp3[2] = {4,4};
    eventList[2].setName("chat 1");    
	eventList[2].setInput(temp3, sizeof(temp3));
	eventList[2].setReq(tempA, tempE, tempT);

	std::fill(tempA, tempA + maxArcFlags, 0);
	std::fill(tempE, tempE + maxEventFlags, 0);
	std::fill(tempT, tempT + maxFlagTriggers, -1);
	tempT[0] = 3;
    int temp4[1] = {4};
    eventList[3].setName("chat 2");    
	eventList[3].setInput(temp4, sizeof(temp4));
	eventList[3].setReq(tempA, tempE, tempT);

	std::fill(tempA, tempA + maxArcFlags, 0);
	std::fill(tempE, tempE + maxEventFlags, 0);
	std::fill(tempT, tempT + maxFlagTriggers, -1);
	tempT[0] = 4;
	int temp5[2] = { 2, 2 };
	tempA[6] = -1;//makes no sense if war ongoing
	tempE[7] = 1;//hear rumors of war
    eventList[4].setName("prediction of war");
	eventList[4].setInput(temp5, sizeof(temp5));
	eventList[4].setReq(tempA, tempE, tempT);

	std::fill(tempA, tempA + maxArcFlags, 0);
	std::fill(tempE, tempE + maxEventFlags, 0);
	std::fill(tempT, tempT + maxFlagTriggers, -1);
	tempT[0] = 5;
	int temp6[2] = { 4, 3 };
	eventList[5].setName("learn about fone gates and how they can generate massive amounts of fone energy");
	eventList[5].setInput(temp6, sizeof(temp6));
	eventList[5].setReq(tempA, tempE, tempT);

	std::fill(tempA, tempA + maxArcFlags, 0);
	std::fill(tempE, tempE + maxEventFlags, 0);
	std::fill(tempT, tempT + maxFlagTriggers, -1);
	tempT[0] = 6;
	int temp7[1] = { 4 };
	tempA[6] = -1;//makes no sense if war ongoing
	eventList[6].setName("rumors of war");
	eventList[6].setInput(temp7, sizeof(temp7));
	eventList[6].setReq(tempA, tempE, tempT);

	std::fill(tempA, tempA + maxArcFlags, 0);
	std::fill(tempE, tempE + maxEventFlags, 0);
	std::fill(tempT, tempT + maxFlagTriggers, -1);
	tempT[0] = 7;
	int temp8[1] = { 4 };
	eventList[7].setName("mention of axeriuth as a mining city");
	eventList[7].setInput(temp8, sizeof(temp8));
	eventList[7].setReq(tempA, tempE, tempT);

	std::fill(tempA, tempA + maxArcFlags, 0);
	std::fill(tempE, tempE + maxEventFlags, 0);
	std::fill(tempT, tempT + maxFlagTriggers, -1);
	tempT[0] = 8;
	int temp9[1] = { 4 };
	eventList[8].setName("explenation of fone stones and their relation to loreli");
	eventList[8].setInput(temp9, sizeof(temp9));
	eventList[8].setReq(tempA, tempE, tempT);

	std::fill(tempA, tempA + maxArcFlags, 0);
	std::fill(tempE, tempE + maxEventFlags, 0);
	std::fill(tempT, tempT + maxFlagTriggers, -1);
	tempT[0] = 9;
	int temp10[1] = { 4 };
	eventList[9].setName("learn of cloning and it's origins");
	eventList[9].setInput(temp10, sizeof(temp10));
	eventList[9].setReq(tempA, tempE, tempT);
	
	//the empty event: no events avalible at this time, nothing happens.
	eventList[maxEvents - 1].setName("");
    
    return 1;
}
