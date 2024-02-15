#include <iostream>
#include <map>
#include "plane.h"
using namespace std;

Plane::Plane(string from, string to) {
    origin = from, destination = to;
    assign_distance(from, to);

    set_vel(0);
    at_SCE = 0;
    pos = 0;

    cout << "Plane created at: " << this << endl;
}

Plane::~Plane() {cout << "Plane Destroyed" << endl;}

void Plane::operate(double dt) {
    if (dt < 0 ) {
        // Ensures that the time interval is not negative.
        dt = 0;
    }

    if (pos < distance) {
        double to_hours;
        to_hours = dt/3600;
        pos += vel * to_hours;
        at_SCE = 0;
    }
    else if (destination == "SCE") {
        at_SCE = 1;

        string new_origin = get_origin();
        string new_destination = get_destination();

        destination = new_origin, origin = new_destination;
        pos = 0;
    }
    else {
        string new_origin = get_origin();
        string new_destination = get_destination();

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

