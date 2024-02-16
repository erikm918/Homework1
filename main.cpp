#include <iostream>
#include <array>
#include <vector>
#include <map>
#include <string>
#include <memory>
#include "Additional/plane.h"
#include "Additional/pilot.h"
#include "Additional/functions.h"

int main() {
    Basic_Info plane_info = get_info();

    // Moments & Total Weight
    std::array<double, 4> plane_moments;
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
    
    // Center of gravity of the plane. Does not confirm if the plane meets design limitations.
    double center_of_gravity = moment_sum/total_weight;

    // Creates a counter to ensure that the while loop is not infinite and boolean function to check center of gravity
    int center_counter = 0;
    is_center_of_gravity(center_of_gravity);


    while (!center_of_gravity && center_counter < 10){
        // Functions to determine the design limitations are met.
        // First defines the Data structure 
        Data weight_limit_output;
        Data center_of_gravity_limit_output;

        // Checks the weight limits against requirements and returns the changed relavent information
        weight_limit_output = weight_limit(plane_moments, plane_info.usable_fuel_weight, plane_info.fuel_moment_arm,
                                        total_weight);

        center_of_gravity = weight_limit_output.center_of_gravity;
        plane_info.usable_fuel_weight = weight_limit_output.usable_fuel_weight;
        total_weight = weight_limit_output.total_weight;

        // Checks the center of gravity requirements and inputs the results into structure to assign later
        center_of_gravity_limit_output = center_of_gravity_limit(plane_moments, plane_info.usable_fuel_weight, 
                                                            plane_info.fuel_moment_arm, total_weight, center_of_gravity);

        center_of_gravity = center_of_gravity_limit_output.center_of_gravity;
        plane_info.usable_fuel_weight = center_of_gravity_limit_output.usable_fuel_weight;
        total_weight = center_of_gravity_limit_output.total_weight;

        // Redefines the while loop conditionals
        center_counter++;
        is_center_of_gravity(center_of_gravity);
    }
    

    // Creates the first plane
    Plane plane1("SCE", "PHL");

    // Sets the plane's velocity, chosen time step, and the max iterations for the operate function.
    double speed = 450;
    double dt = 30;
    int max_iterations = 1042;
    plane1.set_vel(speed);

    // For loop to run the operate function and print the distance to the next airport.
    for (int i = 0; i <= max_iterations; i++) {
        plane1.operate(dt);
        std::cout << "Time: " << dt*i << " seconds. Position: " << plane1.get_pos() << " miles." << std::endl; 
    } 


    // Create pilots for alternating pilots
    Pilot pilot1("Alpha");
    Pilot pilot2("Bravo");

    // Creates plane assigned to pilots
    Plane plane2("SCE", "PHL");
    plane2.set_vel(speed);

    // Assigns memory addresses to the respective pilots
    pilot1.myPlane = &plane2;
    pilot2.myPlane = 0;

    std::cout << "Pilot " << pilot1.get_name() << " with memory address " << &pilot1 
         << " is in control of the plane with memory address " << pilot1.myPlane << std::endl;

    std::cout << "Pilot " << pilot2.get_name() << " with memory address " << &pilot2 
         << " is in control of the plane with memory address " << pilot2.myPlane << std::endl;

    // For loop to run the operate command for plane 2
    for (int i = 0; i <= max_iterations; i++) {
        plane2.operate(dt);

        // Determines if the plane is at SCE and which pilot is currently in control.
        if (plane2.get_atSCE() && pilot1.myPlane) {
            std::cout << "The plane " << &plane2 << " is at SCE." << std::endl;
            
            pilot2.myPlane = &plane2;
            pilot1.myPlane = 0;

            std::cout << "Pilot " << pilot2.get_name() << " is in control of plane " << pilot2.myPlane << std::endl;
            std::cout << "Pilot " << pilot1.get_name() << " is in control of plane " << pilot1.myPlane << std::endl;
        }
        else if (plane2.get_atSCE() && pilot2.myPlane) {
            std::cout << "The plane " << &plane2 << " is at SCE." << std::endl;
            
            pilot1.myPlane = &plane2;
            pilot2.myPlane = 0;

            std::cout << "Pilot " << pilot1.get_name() << " is in control of plane " << pilot1.myPlane << std::endl;
            std::cout << "Pilot " << pilot2.get_name() << " is in control of plane " << pilot2.myPlane << std::endl;
        }
    }

    // Returns the allocated memory for the pilots to the computer
    delete pilot1.myPlane, pilot2.myPlane;

    // New style pointers for the previous method
    // Will use different pilots than previous
    Pilot pilot3("Charley");
    Pilot pilot4("Delta");

    // Creates the plane for the new style pointers
    Plane plane_new_style("SCE", "PHL");
    plane_new_style.set_vel(speed);

    pilot3.myPlane_new_style = std::make_shared<Plane>(plane_new_style.get_origin(), 
                                                       plane_new_style.get_destination());
    pilot4.myPlane_new_style = 0;

    for (int i = 0; i <= max_iterations; i++) {
        plane_new_style.operate(dt);

        // Determines if the plane is at SCE and which pilot is currently in control.
        if (plane_new_style.get_atSCE() && pilot3.myPlane_new_style) {
            std::cout << "The plane " << &plane_new_style << " is at SCE." << std::endl;
            
            pilot4.myPlane_new_style = pilot3.myPlane_new_style;
            pilot3.myPlane_new_style = 0;

            std::cout << "Pilot " << pilot4.get_name() << " is in control of plane " 
                                                       << pilot4.myPlane_new_style << std::endl;
            std::cout << "Pilot " << pilot3.get_name() << " is in control of plane " 
                                                       << pilot3.myPlane_new_style << std::endl;
        }
        else if (plane_new_style.get_atSCE() && pilot4.myPlane_new_style) {
            std::cout << "The plane " << &plane_new_style << " is at SCE." << std::endl;
            
            pilot3.myPlane_new_style = pilot4.myPlane_new_style;
            pilot4.myPlane_new_style = 0;

            std::cout << "Pilot " << pilot3.get_name() << " is in control of plane " 
                                                       << pilot3.myPlane_new_style << std::endl;
            std::cout << "Pilot " << pilot4.get_name() << " is in control of plane " 
                                                       << pilot4.myPlane_new_style << std::endl;
        }
    }

    return 0;
}