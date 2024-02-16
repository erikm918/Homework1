#include <iostream>
#include <map>
#include "plane.h"

Plane::Plane(std::string from, std::string to) {
    origin = from, destination = to;
    assign_distance(from, to);

    set_vel(0);
    at_SCE = 0;
    pos = 0;

    std::cout << "Plane created at: " << this << std::endl;
}

Plane::~Plane() {std::cout << "Plane Destroyed" << std::endl;}

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

        std::string new_origin = get_origin();
        std::string new_destination = get_destination();

        destination = new_origin, origin = new_destination;
        pos = 0;
    }
    else {
        std::string new_origin = get_origin();
        std::string new_destination = get_destination();

        destination = new_origin, origin = new_destination;
        pos = 0;
    }
}

double Plane::assign_distance(std::string from, std::string to) {
    // Creates a map to assign locations to distances from SCE. Then creates a vector for later storage and will 
    // be used in the summing and assigning of distances.
    std::map<std::string, int> locations;
    locations.insert(std::pair<std::string, int>("SCE", 0));
    locations.insert(std::pair<std::string, int>("PHL", 160));
    locations.insert(std::pair<std::string, int>("EWR", 220));
    locations.insert(std::pair<std::string, int>("ORD", 640));
    std::vector<int> from_to;

    // Assigns desired origin and destination to the storage vector from the map of locations, then sums the results
    // to return the final distance.
    from_to.push_back(locations[from]), from_to.push_back(locations[to]);
    distance = from_to[0] + from_to[1];
    return distance;
}

