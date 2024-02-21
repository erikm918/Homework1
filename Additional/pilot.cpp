#include <iostream>
#include <string>
#include "pilot.h"
#include "pilot.h"


Pilot::Pilot(string pilot_name) {
    std::cout << "Pilot Name: " << pilot_name << " \nMemory Address: " << this
         << "\nPilot is at the gate and ready to board." << "\n" << std::endl;

    name = pilot_name;
} 

Pilot::~Pilot() {
    std::cout << "Pilot " << get_name() << " is out of the plane." << std::endl;
}