#ifndef PILOT
#define PILOT

#include <iostream>
#include <string>
#include "plane.h"
using namespace std;

class Pilot {
    private: 
        string name;

    public:
        Plane* myPlane = (Plane*)malloc(sizeof(Plane));

        Pilot(string pilot_name);
        ~Pilot();

        string get_name() {return this->name;}
};

#endif