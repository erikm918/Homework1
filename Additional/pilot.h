#ifndef PILOT
#define PILOT

#include <string>
#include <memory>
#include "plane.h"
using namespace std;

class Pilot {
    private: 
        string name;

    public:
        // Old style pointer
        Plane* myPlane;

        // New style pointer
        std::shared_ptr<Plane> myPlane_new_style;

        Pilot(string pilot_name);
        ~Pilot();

        string get_name() {return this->name;}
};

#endif