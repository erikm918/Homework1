#include <iostream>
#include <array>
#include <vector>
#include <string>
#include "Additional/plane.h"
#include "Additional/pilot.h"
#include "Additional/functions.h"
using namespace std;

double empt_weight, empt_weight_moment, front_moment_arm, rear_moment_arm, front_seat_weight, rear_seat_weight,
        gal_usable_fuel, usable_fuel_weight, fuel_moment_arm, baggage_moment_arm, baggage_weight;
int num_front_seat, num_rear_seat;

int main() {
    get_info();

    // Moments & Total Weight
    double front_moment, rear_moment, fuel_moment, baggage_moment;
    front_moment = moment_func(front_moment_arm, front_seat_weight);
    rear_moment = moment_func(rear_moment_arm, rear_seat_weight);
    fuel_moment = moment_func(fuel_moment_arm, usable_fuel_weight);
    baggage_moment = moment_func(baggage_moment_arm, baggage_weight);

    // Main values for CG calculation.
    double moment_sum = front_moment + rear_moment + fuel_moment + baggage_moment + empt_weight_moment;
    double total_weight = empt_weight + front_seat_weight + rear_seat_weight + usable_fuel_weight + baggage_weight;

    // Check if design limits are met. INCOMPLETE
    double center_of_gravity = moment_sum/total_weight;

    // Was here for checking an issue; fixed.
    // cout << moment_sum << ", " << total_weight << endl; 
    // cout << center_of_gravity << endl;

    // Weight limit
    if (total_weight > 2950) {
        int over_weight = total_weight - 2950;
        double remove_fuel = over_weight + 0.01;
        // If the requirements cannot be met, this notifies as such
        if (remove_fuel > usable_fuel_weight) {
            cout << "Cannot remove enough fuel to meet design limitations." << endl;
        }
        // Reevaluates the CoG and the total weight, as well as how much fuel needs to be removed.
        else {
            cout << "Must remove " << remove_fuel << " lbs of fuel to meet weight limit." << endl;
            double new_usable_fuel = usable_fuel_weight - remove_fuel;
            double new_moment = front_moment + rear_moment + baggage_moment + empt_weight_moment 
                                    + moment_func(fuel_moment_arm, new_usable_fuel);
            double new_total_weight = total_weight - usable_fuel_weight + new_usable_fuel;
            double new_center_gravity = new_moment/new_total_weight;

            center_of_gravity = new_center_gravity;
            usable_fuel_weight = new_usable_fuel;
            total_weight = new_total_weight;

            cout << "New center of gravity location is: " << center_of_gravity << endl;
        }

        // CoG limit. 
        // A more elegant solution is possible, will figure that out later.
        if (center_of_gravity < 82.1) {
            cout << "Center of gravity does not meet design limitations (lower than allowable)." << endl;
            
            double old_fuel_weight = usable_fuel_weight;
            // Increments the fuel to meet the requirement. ONLY for under limit.
            while (center_of_gravity < 82.1) {
                double new_usable_fuel = usable_fuel_weight - 0.01;
                double new_moment_sum = front_moment + rear_moment + baggage_moment + empt_weight_moment
                                        + moment_func(fuel_moment_arm, new_usable_fuel);
                double new_total_weight = total_weight - usable_fuel_weight + new_usable_fuel;
                double new_center_gravity = new_moment_sum/new_total_weight;

                usable_fuel_weight = new_usable_fuel, total_weight = new_total_weight; 
                center_of_gravity = new_center_gravity;
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
                if (total_weight > 2950) {
                    cout << "Design limitations cannot be met." << endl;
                }
                else {
                    // Assigns placeholder values to do calculations.
                    double new_usable_fuel = usable_fuel_weight + 0.01;
                    double new_moment_sum = front_moment + rear_moment + baggage_moment + empt_weight_moment
                                            + moment_func(fuel_moment_arm, new_usable_fuel);
                    double new_total_weight = total_weight - usable_fuel_weight + new_usable_fuel;
                    double new_center_gravity = new_moment_sum/new_total_weight;

                    usable_fuel_weight = new_usable_fuel, total_weight = new_total_weight; 
                    center_of_gravity = new_center_gravity;
                }
            }
            // Fuel difference.
            double fuel_difference = usable_fuel_weight - old_fuel_weight;

            cout << "New usable fuel weight is: " << usable_fuel_weight << "lbs. Must remove " 
                << fuel_difference << "lbs of fuel." << endl;
            cout << "New total weight is: " << total_weight << endl;
            cout << "New center of gravity is: " << center_of_gravity << endl;
        }

    }

    return 0;
}