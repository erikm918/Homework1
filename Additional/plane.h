#ifndef PLANE
#define PLANE

#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

class Plane {
    private:
        double pos, vel, distance;
        bool at_SCE;
        string destination;
        string origin;

    public:
        double get_pos() {return this->pos;}
        string get_origin() {return this->origin;}
        string get_destination() {return this->destination;}
        bool get_atSCE() {this->at_SCE;}

        double get_vel() {return this->vel;}
        void set_vel(double vel) {this->vel = vel;}

        void operate (double dt) {}

        double assign_distnace(string from, string to) {}

        Plane (std::string from, std::string to) {
            origin = from, destination = to;
            assign_distnace(from, to);


            // std::cout << "Plane created at " << &Plane << std::endl;
        }

        ~Plane() {cout << "Plane Destroyed" << endl;}
};

#endif