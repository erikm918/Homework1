#ifndef PLANE
#define PLANE

#include <iostream>
#include <string>

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
        bool get_atSCE() {return this->at_SCE;}

        double get_vel() {return this->vel;}
        void set_vel(double vel) {this->vel = vel;}

        void operate (double dt);

        double assign_distance(std::string from, std::string to);

        Plane (std::string from, std::string to);

        ~Plane();
};

#endif