#include <iostream>
#include "plane.h"
using namespace std;

// **QUESTION 2** Containers
// First creates the base values which contains the distance between destinations. Then creates a container to hold
// these values. 
map<string, int> locations = {{"SCE", 0}, {"PHL", 160}, {"EWR", 220}, {"ORD", 640}};
vector<int> from_to;

void Plane::operate(double dt) {
    if (dt < 0 ) {
                // Ensures that the time interval is not negative.
                dt = 0;
            }

            if (pos < distance) {
                while (pos < distance) {
                    pos += vel * dt;
                }
            
                at_SCE = 0;
            }
            else if (destination == "SCE") {
                at_SCE = 1;

                string new_origin = destination; 
                string new_destination = origin;
                destination = new_origin, origin = new_destination;
                pos = 0;
            }
            else {
                string new_origin = destination;
                string new_destination = origin;
                destination = new_origin, origin = new_destination;
                pos = 0;
            }
}

double Plane::assign_distnace(string from, string to) {
    from_to.push_back(locations[from]), from_to.push_back(locations[to]);
    distance = from_to[0] + from_to[1];
    return distance;
}