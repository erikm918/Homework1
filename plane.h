#include <iostream>
#include <string>
#include <vector>

// **QUESTION 2** Containers
// First creates the base values which contains the distance between destinations. Then creates a container to hold
// these values. 
int PHL = 160, ORD = 640, EWR = 220, SCE = 0;
std::vector<int> locations{PHL, ORD, EWR, SCE};
std::vector<int> from_to;

class Plane {
    private:
        double pos, vel, distance;
        bool at_SCE;
        std::string destination;
        std::string origin;

    public:
        void operate (double dt) {
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

                std::string new_origin = destination; 
                std::string new_destination = origin;
                destination = new_origin, origin = new_destination;
                pos = 0;
            }
            else {
                std::string new_origin = destination; 
                std::string new_destination = origin;
                destination = new_origin, origin = new_destination;
                pos = 0;
            }
        }

        void get_vel() {
            std::cout << "Enter velocity: " << std::endl;
            // std::cin >> pos;
            std::cin >> vel;
            // std::cin >> origin;
            // std::cin >> destination;
            // std::cin >> at_SCE;
        }

        Plane (std::string from, std::string to) {
            origin = from;
            destination = to;

            if (from.find("SCE") == true || to.find("SCE") == true) {
                int new_distance = distance + SCE;
                distance = new_distance;
            }
            if (from.find("PHL") == true || to.find("PHL")== true) {
                int new_distance = distance + PHL;
                distance = new_distance;
            }
            if (from.find("ORD") == true || to.find("ORD")== true) {
                int new_distance = distance + ORD;
                distance = new_distance;
            }
            if (from.find("EWR") == true || to.find("EWR")== true) {
                int new_distance = distance + EWR;
                distance = new_distance;
            }

            get_vel();
            pos = 0, at_SCE = 0;

            // std::cout << "Plane created at " << &Plane << std::endl;
        }

        ~Plane() {std::cout << "Plane Destroyed";}
};