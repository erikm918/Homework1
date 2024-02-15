#ifndef FUNC 
#define FUNC

#include <array>
using namespace std;

struct Basic_Info {
    double empt_weight, empt_weight_moment, front_moment_arm, rear_moment_arm, front_seat_weight, rear_seat_weight, 
        gal_usable_fuel, usable_fuel_weight, fuel_moment_arm, baggage_moment_arm, baggage_weight;
    int num_front_seat, num_rear_seat;  
};

struct Data{
        double center_of_gravity, usable_fuel_weight, total_weight;
    };

// Get the information from the user about the plane.
Basic_Info get_info();

// Moment calculation.
double moment_func (double arm, double weight);

// Determines if weight requirements are met.
Data weight_limit(array<double, 4> moments, double usable_fuel_weight, double fuel_moment_arm, double total_weight);

// Determines if the center of gravity requirements are met.
Data center_of_gravity_limit(array<double, 4> moments, double usable_fuel_weight, double fuel_moment_arm,
                             double total_weight, double center_of_gravity);

#endif 