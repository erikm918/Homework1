#include <iostream>
#include <vector>
#include <queue>
#include <array>
#include "functions.h"
using namespace std;

Basic_Info get_info() {
    Basic_Info data;

    // Get the information from the user about the plane. Stores it in global variables for later use.
    cout << "Please input the airplane emtpy weight: " << endl;
    cin >> data.empt_weight;
    cout << "Please input the airplane empty weight moment: " << endl;
    cin >> data.empt_weight_moment;

    // Front Seat Info
    cout << "Please input the number of front seat passengers: " << endl;
    cin >> data.num_front_seat;

    for (int i = 0; i < data.num_front_seat; i++) {
        double pass_weight;
        cout << "Enter weight of passenger " << i+1 << ": " << endl;
        cin >> pass_weight;
        data.front_seat_weight = data.front_seat_weight + pass_weight;
    }

    cout << "Please input the front seat moment arm: " << endl;
    cin >> data.front_moment_arm;

    // Rear Seat Info
    cout << "Please input the number of rear seat passengers: " << endl;
    cin >> data.num_rear_seat;

    for (int i = 0; i < data.num_rear_seat; i++) {
        double pass_weight;
        cout << "Enter weight of passenger " << i+1 << ": " << endl;
        cin >> pass_weight;
        data.rear_seat_weight = data.rear_seat_weight + pass_weight;
    }

    cout << "Please input the rear seat moment arm: " << endl;
    cin >> data.rear_moment_arm;

    // Fuel Info
    cout << "Please input the number of gallons of usable fuel: " << endl;
    cin >> data.gal_usable_fuel;
    cout << "Please input the usable fuel weight: " << endl;
    cin >> data.usable_fuel_weight;
    cout << "Please input the fuel tank moment arm: " << endl;
    cin >> data.fuel_moment_arm;

    // Baggage Info
    cout << "Please input the baggage weight: " << endl;
    cin >> data.baggage_weight;
    cout << "Please input the baggage moment arm: " << endl;
    cin >> data.baggage_moment_arm;

    return data;    
}

double moment_func (double arm, double weight) {
    // Function that determines the moment of a given part of the plane.
    double moment = 0;
    moment = arm*weight;
    return moment;
}

Data weight_limit(array<double, 4> moments, double usable_fuel_weight, double fuel_moment_arm, double total_weight) {
    Data resulting_data;
    
    double sum_of_non_fuel_moments;
    for (int i = 0; i < 4; i++) {
        sum_of_non_fuel_moments = sum_of_non_fuel_moments + moments[i];
    }
    // Weight limit
    if (total_weight > 2950) {
        int over_weight = total_weight - 2950;
        double remove_fuel = over_weight + 0.01;
        // If the requirements cannot be met, this notifies as such and ends the program.
        if (remove_fuel > usable_fuel_weight) {
            cout << "WARNING: Cannot remove enough fuel to meet design limitations. Program will now end." << endl;
            
            exit(0);
        }
        // Reevaluates the CoG and the total weight, as well as how much fuel needs to be removed.
        else {
            cout << "Must remove " << remove_fuel << " lbs of fuel to meet weight limit." << endl;
            double new_usable_fuel = usable_fuel_weight - remove_fuel;
            double new_moment = sum_of_non_fuel_moments + moment_func(fuel_moment_arm, new_usable_fuel);
            double new_total_weight = total_weight - usable_fuel_weight + new_usable_fuel;
            double new_center_gravity = new_moment/new_total_weight;

            resulting_data.center_of_gravity = new_center_gravity;
            resulting_data.usable_fuel_weight = new_usable_fuel;
            resulting_data.total_weight = new_total_weight;

            cout << "New center of gravity location is: " << resulting_data.center_of_gravity << endl;
        }
    }

    return resulting_data;
}

Data center_of_gravity_limit(array<double, 4> moments, double usable_fuel_weight, double fuel_moment_arm,
                             double total_weight, double center_of_gravity) {
    Data resulting_data;

    double sum_of_non_fuel_moments;
    for (int i = 0; i < 3; i++) {
        sum_of_non_fuel_moments = sum_of_non_fuel_moments + moments[i];
    }

    // CoG limit. 
    // A more elegant solution is possible, will figure that out later.
    if (center_of_gravity < 82.1) {
        cout << "Center of gravity does not meet design limitations (lower than allowable)." << endl;
            
        double old_fuel_weight = usable_fuel_weight;
        // Increments the fuel to meet the requirement. ONLY for under limit.
        while (resulting_data.center_of_gravity < 82.1) {
            double new_usable_fuel = usable_fuel_weight - 0.01;
            double new_moment_sum = sum_of_non_fuel_moments + moment_func(fuel_moment_arm, new_usable_fuel);
            double new_total_weight = total_weight - usable_fuel_weight + new_usable_fuel;
            double new_center_gravity = new_moment_sum/new_total_weight;

            resulting_data.center_of_gravity = new_center_gravity;
            resulting_data.total_weight = new_total_weight;
            resulting_data.usable_fuel_weight = new_usable_fuel;
        }
        double fuel_difference = old_fuel_weight - usable_fuel_weight; 

        cout << "New usable fuel weight is: " << usable_fuel_weight << "lbs. Must remove "
            << fuel_difference << "lbs of fuel." << endl;
        cout << "New total weight is: " << total_weight << endl;
        cout << "New center of gravity is: " << center_of_gravity << endl;
    }

   // Increments the fuel weight to meet limiations. ONLY for over limit.
    else if (center_of_gravity > 84.7) {
        cout << "Center of gravity does not meet design limitations (greater than allowable)." << endl;
        // Maintains old fuel weight for later calculations.
        double old_fuel_weight = usable_fuel_weight;

        while (center_of_gravity > 84.7) { 
            // Checks to determine whether it is possible to maintain weight limit.
            // PROBLEM!!!! Will not break out of loop. Will be fixed when defined as a function
            if (total_weight > 2950) {
                cout << "WARNING: Design limitations cannot be met. Program will now end." << endl;
                exit(0);
            }
            else {
                // Assigns placeholder values to do calculations.
                double new_usable_fuel = usable_fuel_weight + 0.01;
                double new_moment_sum = sum_of_non_fuel_moments + moment_func(fuel_moment_arm, new_usable_fuel);
                double new_total_weight = total_weight - usable_fuel_weight + new_usable_fuel;
                double new_center_gravity = new_moment_sum/new_total_weight;

                resulting_data.center_of_gravity = new_center_gravity;
                resulting_data.total_weight = new_total_weight;
                resulting_data.usable_fuel_weight = new_usable_fuel;
            }
        }
        // Fuel difference.
        double fuel_difference = usable_fuel_weight - old_fuel_weight;

        cout << "New usable fuel weight is: " << usable_fuel_weight << "lbs. Must remove " 
            << fuel_difference << "lbs of fuel." << endl;
        cout << "New total weight is: " << total_weight << endl;
        cout << "New center of gravity is: " << center_of_gravity << endl;
    }

    return resulting_data;
}