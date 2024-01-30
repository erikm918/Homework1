#include <iostream>
#include <array>

double moment_func (int arm, int weight) {
    // Function that determines the moment of a given part of the plane.
    double moment = 0;
    moment = arm*weight;
    return moment;
}

int main() {
    double empt_weight, empt_weight_moment, front_moment_arm, rear_moment_arm, front_seat_weight, rear_seat_weight,
        gal_usable_fuel, usable_fuel_weight, fuel_moment_arm, baggage_moment_arm, baggage_weight;
    int num_front_seat, num_rear_seat;

    // General Info
    std::cout << "Please input the airplane emtpy weight: " << std::endl;
    std::cin >> empt_weight;
    std::cout << "Please input the airplane empty weight moment: " << std::endl;
    std::cin >> empt_weight_moment;

    // Front Seat Info
    std::cout << "Please input the number of front seat passengers: " << std::endl;
    std::cin >> num_front_seat;

    for (int i = 0; i < num_front_seat; i++) {
        double pass_weight;
        std::cout << "Enter weight of passenger " << i+1 << ": " << std::endl;
        std::cin >> pass_weight;
        front_seat_weight = front_seat_weight + pass_weight;
    }

    std::cout << "Please input the front seat moment arm: " << std::endl;
    std::cin >> front_moment_arm;

    // Rear Seat Info
    std::cout << "Please input the number of rear seat passengers: " << std::endl;
    std::cin >> num_rear_seat;

    for (int i = 0; i < num_rear_seat; i++) {
        double pass_weight;
        std::cout << "Enter weight of passenger " << i+1 << ": " << std::endl;
        std::cin >> pass_weight;
        rear_seat_weight = rear_seat_weight + pass_weight;
    }

    std::cout << "Please input the rear seat moment arm: " << std::endl;
    std::cin >> rear_moment_arm;

    // Fuel Info
    std::cout << "Please input the number of gallons of usable fuel: " << std::endl;
    std::cin >> gal_usable_fuel;
    std::cout << "Please input the usable fuel weight: " << std::endl;
    std::cin >> usable_fuel_weight;
    std::cout << "Please input the fuel tank moment arm: " << std::endl;
    std::cin >> fuel_moment_arm;

    // Baggage Info
    std::cout << "Please input the baggage weight: " << std::endl;
    std::cin >> baggage_weight;
    std::cout << "Please input the baggage moment arm: " << std::endl;
    std::cin >> baggage_moment_arm;

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
    // std::cout << moment_sum << ", " << total_weight << std::endl; 
    // std::cout << center_of_gravity << std::endl;

    // Weight limit
    if (total_weight > 2950) {
        int over_weight = total_weight - 2950;
        double remove_fuel = over_weight + 0.01;
        // If the requirements cannot be met, this notifies as such
        if (remove_fuel > usable_fuel_weight) {
            std::cout << "Cannot remove enough fuel to meet design limitations." << std::endl;
        }
        // Reevaluates the CoG and the total weight, as well as how much fuel needs to be removed.
        else {
            std::cout << "Must remove " << remove_fuel << " lbs of fuel to meet weight limit." << std::endl;
            double new_usable_fuel = usable_fuel_weight - remove_fuel;
            double new_moment = front_moment + rear_moment + baggage_moment + empt_weight_moment 
                                    + moment_func(fuel_moment_arm, new_usable_fuel);
            double new_total_weight = total_weight - usable_fuel_weight + new_usable_fuel;
            double new_center_gravity = new_moment/new_total_weight;

            center_of_gravity = new_center_gravity;
            usable_fuel_weight = new_usable_fuel;
            total_weight = new_total_weight;

            std::cout << "New center of gravity location is: " << center_of_gravity << std::endl;
        }

        // CoG limit. 
        // A more elegant solution is possible, will figure that out later.
        if (center_of_gravity < 82.1) {
            std::cout << "Center of gravity does not meet design limitations (lower than allowable)." << std::endl;
            
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

            std::cout << "New usable fuel weight is: " << usable_fuel_weight << "lbs. Must remove "
                << fuel_difference << "lbs of fuel." << std::endl;
            std::cout << "New total weight is: " << total_weight << std::endl;
            std::cout << "New center of gravity is: " << center_of_gravity << std::endl;
        }

        // Increments the fuel weight to meet limiations. ONLY for over limit.
        else if (center_of_gravity > 84.7) {
            std::cout << "Center of gravity does not meet design limitations (greater than allowable)." << std::endl;
            // Maintains old fuel weight for later calculations.
            double old_fuel_weight = usable_fuel_weight;

            while (center_of_gravity > 84.7) { 
                // Checks to determine whether it is possible to maintain weight limit.
                if (total_weight > 2950) {
                    std::cout << "Design limitations cannot be met." << std::endl;
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

            std::cout << "New usable fuel weight is: " << usable_fuel_weight << "lbs. Must remove " 
                << fuel_difference << "lbs of fuel." << std::endl;
            std::cout << "New total weight is: " << total_weight << std::endl;
            std::cout << "New center of gravity is: " << center_of_gravity << std::endl;
        }

    }

    return 0;
}