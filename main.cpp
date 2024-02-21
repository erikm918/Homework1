#include <iostream>
#include <array>
#include <string>
#include "Additional/pilot.h"
#include "Additional/plane.h"
#include "Additional/functions.h"

int main() {
    // Gets basic information and stores it in a structure defined in funcitons.h
    Basic_Info plane_info = get_info();

    // Moments & Total Weight
    std::array<double, 5> plane_moments;
    plane_moments[0] = moment_func(plane_info.front_moment_arm, plane_info.front_seat_weight);
    plane_moments[1] = moment_func(plane_info.rear_moment_arm, plane_info.rear_seat_weight);
    plane_moments[2] = moment_func(plane_info.baggage_moment_arm, plane_info.baggage_weight);
    plane_moments[3] = moment_func(plane_info.fuel_moment_arm, plane_info.usable_fuel_weight);
    plane_moments[4] = plane_info.empt_weight_moment;
    

    // Main values for CG calculation.
    double moment_sum = 0; 
    for (int i = 0; i < 5; i++) {
        moment_sum = moment_sum + plane_moments[i];
    }
    double total_weight = plane_info.empt_weight + plane_info.front_seat_weight + plane_info.rear_seat_weight
                          + plane_info.usable_fuel_weight + plane_info.baggage_weight;
    
    // Center of gravity of the plane. Does not confirm if the plane meets design limitations.
    double center_of_gravity = moment_sum/total_weight;
    Data limit_results;
    limit_results = weight_limit(moment_sum, plane_info.usable_fuel_weight, plane_info.fuel_moment_arm, 
                                 total_weight);

    center_of_gravity = limit_results.center_of_gravity; 
    plane_info.usable_fuel_weight = limit_results.usable_fuel_weight;
    total_weight = limit_results.total_weight;

    center_of_gravity_limit(moment_sum, plane_info.usable_fuel_weight, plane_info.fuel_moment_arm,
                            total_weight, center_of_gravity);
    
    center_of_gravity = limit_results.center_of_gravity; 
    plane_info.usable_fuel_weight = limit_results.usable_fuel_weight;
    total_weight = limit_results.total_weight;

    // Creates plane for basic iterative statement
    Plane plane("SCE", "PHL");

    // Sets the plane's velocity, chosen time step, and the max iterations for the operate function.
    double speed = 450;
    double dt = 30;
    int max_iterations = 1042;
    plane.set_vel(speed);

    // For loop to run the operate function and print the distance to the next airport.
    for (int i = 0; i <= max_iterations; i++) {
        plane.operate(dt);
        std::cout << "Time: " << dt*i << " seconds. Position: " << plane.get_pos() << " miles." << std::endl; 
    }
    std::cout << "\n"; // Only for output readability

    create_flight("Alpha", "Bravo", speed, max_iterations, dt, "SCE", "ORD");
    std::cout << "\n"; // Only for output readability
    create_flight_new_style("Charley", "Delta", speed, max_iterations, dt, "SCE", "ORD");
    std::cout << "\n"; // Only for output readability

    return 0;
}