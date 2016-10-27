#include <iostream>
#include <string>
#include <stdio.h>
//#include <algorithm>

#include "Defenitions.h"
#include "Worlds.h"
#include "Contries.h"
#include "Cityes.h"
#include "Characters.h"
#include "Events.h"
#include "Arcs.h"



using namespace std;

#ifndef UTIL_H
#define UTIL_H

//build story
string makeStory(string Story, Worlds worldList[], Contries contList[], Cityes cityList[], Characters peopleList[], Events eventList[], Arcs arcList[], int relationships[maxTotal][maxTotal],int flagsA[maxArcs], int flagsE[maxEvents]);

//initialize objects
int init(Worlds worldList[], Contries contList[], Cityes cityList[], Characters peopleList[], Events eventList[], Arcs arcList[], int relationships[maxTotal][maxTotal],int flagsA[maxArcs], int flagsE[maxEvents]);

#endif
