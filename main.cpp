#include <iostream>
#include <array>
#include <vector>
#include <map>
#include <string>
#include "Additional/plane.h"
#include "Additional/pilot.h"
#include "Additional/functions.h"
using namespace std;

int main() {
    auto plane_info = get_info();

    // Moments & Total Weight
    array<double, 4> plane_moments;
    plane_moments[0] = moment_func(plane_info.front_moment_arm, plane_info.front_seat_weight);
    plane_moments[1] = moment_func(plane_info.rear_moment_arm, plane_info.rear_seat_weight);
    plane_moments[2] = moment_func(plane_info.fuel_moment_arm, plane_info.usable_fuel_weight);
    plane_moments[3] = moment_func(plane_info.baggage_moment_arm, plane_info.baggage_weight);
    

    // Main values for CG calculation.
    double moment_sum;
    for (int i = 0; i < 3; i++) {
        moment_sum = moment_sum + plane_moments[i];
    }
    double total_weight = plane_info.empt_weight + plane_info.front_seat_weight + plane_info.rear_seat_weight
             + plane_info.usable_fuel_weight + plane_info.baggage_weight;
    
    // CoG
    double center_of_gravity = moment_sum/total_weight;

    // Was here for checking an issue; fixed.
    // cout << moment_sum << ", " << total_weight << endl; 
    // cout << center_of_gravity << endl;

    weight_limit(plane_moments, plane_info.usable_fuel_weight, plane_info.fuel_moment_arm, total_weight);

    center_of_gravity_limit(plane_moments, plane_info.usable_fuel_weight, plane_info.fuel_moment_arm,
                            total_weight, center_of_gravity);

    return 0;
}