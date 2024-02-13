#include <iostream>
#include <map>
#include "plane.h"
using namespace std;

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

double Plane::assign_distance(string from, string to) {
    // Creates a map to assign locations to distances from SCE. Then creates a vector for later storage and will 
    // be used in the summing and assigning of distances.
    map<string, int> locations;
    locations.insert(pair<string, int>("SCE", 0));
    locations.insert(pair<string, int>("PHL", 160));
    locations.insert(pair<string, int>("EWR", 220));
    locations.insert(pair<string, int>("ORD", 640));
    vector<int> from_to;

    // Assigns desired origin and destination to the storage vector from the map of locations, then sums the results
    // to return the final distance.
    from_to.push_back(locations[from]), from_to.push_back(locations[to]);
    distance = from_to[0] + from_to[1];
    return distance;
}