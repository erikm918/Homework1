#include <iostream>
#include <memory>
#include <algorithm>
#include <cmath>
#include "functions.h"
#include "pilot.h"
#include "plane.h"

Basic_Info get_info() {
    Basic_Info data;

    // Basic plane info
    std::cout << "Please input the airplane emtpy weight: " << std::endl;
    std::cin >> data.empt_weight;
    std::cout << "Please input the airplane empty weight moment: " << std::endl;
    std::cin >> data.empt_weight_moment;

    // Front Seat Info
    std::cout << "Please input the number of front seat passengers: " << std::endl;
    std::cin >> data.num_front_seat;

    for (int i = 0; i < data.num_front_seat; i++) {
        double pass_weight;
        std::cout << "Enter weight of passenger " << i+1 << ": " << std::endl;
        std::cin >> pass_weight;
        data.front_seat_weight = data.front_seat_weight + pass_weight;
    }

    std::cout << "Please input the front seat moment arm: " << std::endl;
    std::cin >> data.front_moment_arm;

    // Rear Seat Info
    std::cout << "Please input the number of rear seat passengers: " <<std::endl;
    std::cin >> data.num_rear_seat;

    for (int i = 0; i < data.num_rear_seat; i++) {
        double pass_weight;
        std::cout << "Enter weight of passenger " << i+1 << ": " << std::endl;
        std::cin >> pass_weight;
        data.rear_seat_weight = data.rear_seat_weight + pass_weight;
    }

    std::cout << "Please input the rear seat moment arm: " << std::endl;
    std::cin >> data.rear_moment_arm;

    // Fuel Info
    std::cout << "Please input the number of gallons of usable fuel: " << std::endl;
    std::cin >> data.gal_usable_fuel;
    std::cout << "Please input the usable fuel weight: " << std::endl;
    std::cin >> data.usable_fuel_weight;
    std::cout << "Please input the fuel tank moment arm: " << std::endl;
    std::cin >> data.fuel_moment_arm;

    // Baggage Info
    std::cout << "Please input the baggage weight: " << std::endl;
    std::cin >> data.baggage_weight;
    std::cout << "Please input the baggage moment arm: " << std::endl;
    std::cin >> data.baggage_moment_arm;

    return data;    
}

double moment_func (double arm, double weight) {
    // Function that determines the moment of a given part of the plane.
    double moment;
    moment = arm*weight;
    return moment;
}

Data weight_limit(double moments, double usable_fuel_weight, double fuel_moment_arm, 
                  double total_weight) {
    Data resulting_data;
    
    // Sum of all none fuel moments
    double sum_of_non_fuel_moments = moments - moment_func(fuel_moment_arm, usable_fuel_weight);
    
    // Weight limit
    if (total_weight > 2950) {
        int over_weight = total_weight - 2950;
        double remove_fuel = over_weight + 0.01;
        // If the requirements cannot be met, this notifies as such and ends the program.
        if (remove_fuel > usable_fuel_weight) {
            std::cout << "WARNING: Cannot remove enough fuel to meet design limitations. Program will now end."
                      << std::endl;
            exit(0);
        }
        // Reevaluates the CoG and the total weight, as well as how much fuel needs to be removed.
        else {
            std::cout << "Must remove " << remove_fuel << " lbs of fuel to meet weight limit." << std::endl;
            double new_usable_fuel = usable_fuel_weight - remove_fuel;
            double new_moment = sum_of_non_fuel_moments + moment_func(fuel_moment_arm, new_usable_fuel);
            double new_total_weight = total_weight - usable_fuel_weight + new_usable_fuel;
            double new_center_gravity = new_moment/new_total_weight;

            resulting_data.center_of_gravity = new_center_gravity;
            resulting_data.usable_fuel_weight = new_usable_fuel;
            resulting_data.total_weight = new_total_weight;

            std::cout << "New center of gravity location is: " << resulting_data.center_of_gravity << std::endl;
        }
    }

    return resulting_data;
}

Data center_of_gravity_limit(double moments, double usable_fuel_weight, double fuel_moment_arm,
                             double total_weight, double center_of_gravity) {
    Data resulting_data;

    double sum_of_non_fuel_moments = moments - moment_func(fuel_moment_arm, usable_fuel_weight);
    
    // Determines how much fuel needs to be removed to meet limitations
    if (center_of_gravity < 82.1) {
        std::cout << "Center of gravity does not meet design limitations (lower than allowable)." << std::endl;

        double remove_fuel = usable_fuel_weight + (sum_of_non_fuel_moments - (center_of_gravity *
                             (total_weight - usable_fuel_weight)))/(center_of_gravity - fuel_moment_arm);
        
        // Rounds up to 2 decimal places (ie. 3.114 -> 311.4 -> 312 -> 3.12). This will ensure enough fuel
        // will be removed and keep a precision of 0.01.
        remove_fuel = std::ceil(remove_fuel * 100 ) / 100;

        if (remove_fuel >= usable_fuel_weight) {
            std::cout << "WARNING: Cannot remove enough fuel to meet design limits. The program will now end." 
                      << std::endl;
            exit(0);
        }
        else {
            // Determines the new fuel weight and new sum of moments
            double new_usable_fuel = usable_fuel_weight - remove_fuel;
            double new_moment_sum = sum_of_non_fuel_moments + moment_func(fuel_moment_arm, new_usable_fuel);

            // Determines the new weight and new center of gravity
            double new_total_weight = total_weight - remove_fuel;
            double new_center_gravity = new_moment_sum/new_total_weight;

            // Puts resulting information into the structure that will later be returned
            resulting_data.center_of_gravity = new_center_gravity;
            resulting_data.total_weight = new_total_weight;
            resulting_data.usable_fuel_weight = new_usable_fuel;

            // Prints new values
            std::cout << "New usable fuel weight is: " << resulting_data.usable_fuel_weight << "lbs. Must remove "
                << remove_fuel << "lbs of fuel." << std::endl;
            std::cout << "New total weight is: " << resulting_data.total_weight << std::endl;
            std::cout << "New center of gravity is: " << resulting_data.center_of_gravity << std::endl;
        }
    }

   // Determines how much fuel needs to be added to meet limitations
    else if (center_of_gravity > 84.7) {
        std::cout << "Center of gravity does not meet design limitations (greater than allowable)." << std::endl;

        double add_fuel;
        add_fuel = ((sum_of_non_fuel_moments - (center_of_gravity*(total_weight - usable_fuel_weight)))/
                   (center_of_gravity - fuel_moment_arm)) - usable_fuel_weight;

        // Rounds down to a precision of 0.01 to ensure enough fuel, but not more than needed, is removed.
        add_fuel = std::floor(add_fuel * 100) / 100;

        // Checks to determine whether it is possible to maintain weight limit.
        if ((total_weight + add_fuel) > 2950) {
            std::cout << "WARNING: Required amount of fuel added will cause the plane to excede weight limitations. "
                      << "Program will now end." << std::endl;
            exit(0);
        }
        else {
            // Assigns placeholder values to do calculations.
            double new_fuel_weight = add_fuel + usable_fuel_weight;
            double new_moment_sum = sum_of_non_fuel_moments + moment_func(fuel_moment_arm, new_fuel_weight);
            double new_total_weight = total_weight + add_fuel;
            double new_center_gravity = new_moment_sum/new_total_weight;

            resulting_data.center_of_gravity = new_center_gravity;
            resulting_data.total_weight = new_total_weight;
            resulting_data.usable_fuel_weight = new_fuel_weight;
        }

        // Fuel difference.
        std::cout << "New usable fuel weight is: " << resulting_data.usable_fuel_weight << "lbs. Must add " << add_fuel
                  << "lbs of fuel." << std::endl;
        std::cout << "New total weight is: " << resulting_data.total_weight << std::endl;
        std::cout << "New center of gravity is: " << resulting_data.center_of_gravity << std::endl;
    }

    return resulting_data;
}

void create_flight(std::string pilot1_name, std::string pilot2_name, double speed, int iterations, double dt,
                   std::string origin, std::string destination) {
    
    // Create pilots for alternating pilots
    Pilot pilot1(pilot1_name);
    Pilot pilot2(pilot2_name);

    // Plane assigned to pilots using old C++ style pointers
    Plane* plane = new Plane(origin, destination);
    plane->set_vel(speed);

    // Assigns memory addresses to the respective pilots
    pilot1.myPlane = plane;
    pilot2.myPlane = nullptr;

    std::cout << "Pilot " << pilot1_name << " with memory address " << &pilot1 
         << " is in control of the plane with memory address " << pilot1.myPlane <<  std::endl;

    std::cout << "Pilot " << pilot2_name << " with memory address " << &pilot2 
         << " is in control of the plane with memory address " << pilot2.myPlane << "\n" << std::endl;

    // For loop to run the operate command for plane 2
    for (int i = 0; i <= iterations; i++) {
        plane->operate(dt);

        // Determines if the plane is at SCE and which pilot is currently in control.
        if (plane->get_atSCE() && pilot1.myPlane) {
            std::cout << "The plane " << plane << " is at SCE." << std::endl;
            
            swap(pilot1.myPlane, pilot2.myPlane);

            std::cout << "Pilot " << pilot2_name << " is in control of plane " << pilot2.myPlane << std::endl;
            std::cout << "Pilot " << pilot1_name << " is in control of plane " << pilot1.myPlane << "\n" << std::endl;
        }
        else if (plane->get_atSCE() && pilot2.myPlane) {
            std::cout << "The plane " << plane << " is at SCE." << std::endl;
            
            swap(pilot1.myPlane, pilot2.myPlane);

            std::cout << "Pilot " << pilot1_name << " is in control of plane " << pilot1.myPlane << std::endl;
            std::cout << "Pilot " << pilot2_name << " is in control of plane " << pilot2.myPlane << "\n" << std::endl;
        }
    }

    // Returns the allocated memory for the pilots to the computer
    delete plane;
}

void create_flight_new_style(std::string pilot1_name, std::string pilot2_name, double speed, int iterations, 
                             double dt, std::string origin, std::string destination) {
    // New C++ style pointer created to the plane that will be used throughout this function
    std::shared_ptr<Plane> plane = std::make_shared<Plane>(origin, destination);

    // Sets the plane's veolocity
    plane->set_vel(speed);
    
    // Creates alternating pilots
    Pilot pilot1(pilot1_name);
    Pilot pilot2(pilot2_name);

    // Sets the pilots plane as the one they control
    pilot1.myPlane_new_style = plane;
    pilot2.myPlane_new_style = nullptr;

    std::cout << "Pilot " << pilot1_name << " with memory address " << &pilot1 
         << " is in control of the plane with memory address " << pilot1.myPlane_new_style <<  std::endl;

    std::cout << "Pilot " << pilot2_name << " with memory address " << &pilot2 
         << " is in control of the plane with memory address " << pilot2.myPlane_new_style << "\n" << std::endl;

    // For loop that controls the operate function of the plane and the checks of who is in control of the plane
    // and where the plane is.
    for (int i = 0; i <= iterations; i++) {
        plane->operate(dt);

        // Determines if the plane is at SCE and which pilot is currently in control.
        if (plane->get_atSCE() && pilot1.myPlane_new_style) {
            std::cout << "The plane " << plane << " is at SCE." << std::endl;
            
            std::swap(pilot1.myPlane_new_style, pilot2.myPlane_new_style);

            std::cout << "Pilot " << pilot2_name << " is in control of plane " 
                                                       << pilot2.myPlane_new_style << std::endl;
            std::cout << "Pilot " << pilot1_name << " is in control of plane " 
                                                       << pilot1.myPlane_new_style << "\n" << std::endl;
        } 
        else if (plane->get_atSCE() && pilot2.myPlane_new_style) {
            std::cout << "The plane " << &plane << " is at SCE." << std::endl;
            
            swap(pilot1.myPlane_new_style, pilot2.myPlane_new_style);

            std::cout << "Pilot " << pilot1_name << " is in control of plane " 
                                                       << pilot1.myPlane_new_style << std::endl;
            std::cout << "Pilot " << pilot2_name << " is in control of plane " 
                                                       << pilot2.myPlane_new_style << "\n" << std::endl;
        }
    }

    // Sets both pointers as a null pointer placeholder so that the deconstruction is cohesive. Does not have
    // any effect on the funcitonality or results.
    pilot1.myPlane_new_style = nullptr;
    pilot2.myPlane_new_style = nullptr;
    // No need to return memory back to computer because of smart pointers
}