#ifndef PLANE
#define PLANE

#include <iostream>
#include <string>

class Plane {
    private:
        double pos, vel, distance;
        bool at_SCE;
        std::string destination;
        std::string origin;

    public:
        double get_pos() {return this->pos;}
        std::string get_origin() {return this->origin;}
        std::string get_destination() {return this->destination;}
        bool get_atSCE() {return this->at_SCE;}

        double get_vel() {return this->vel;}
        void set_vel(double vel) {this->vel = vel;}

        void operate (double dt);

        double assign_distance(std::string from, std::string to);

        Plane (std::string from, std::string to);

        ~Plane();
};

#endif