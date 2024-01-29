#include <iostream>
#include <array>

int moment_func (int arm, int weight) {
    // Function that determines the moment of a given part of the plane.
    int moment = 0;
    moment = arm*weight;
}

int main() {
    int empt_weight, empt_weight_moment, num_front_seat, front_moment_arm, num_rear_seat, rear_moment_arm,
        gal_usable_fuel, usable_fuel_weight, fuel_moment_arm, baggage_moment_arm, baggage_weight;
    int front_seat_weight, rear_seat_weight;

    // General Info
    std::cout << "Please input the airplane emtpy weight: " << std::endl;
    std::cin >> empt_weight;
    std::cout << "Please input the airplane empty weight moment: " << std::endl;
    std::cin >> empt_weight_moment;

    // Front Seat Info
    std::cout << "Please input the number of front seat passengers: " << std::endl;
    std::cin >> num_front_seat;

    for (int i = 0; i < num_front_seat; i++) {
        int pass_weight;
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
        int pass_weight;
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
    int front_moment, rear_moment, fuel_moment, baggage_moment;
    front_moment = moment_func(front_moment_arm, front_seat_weight);
    rear_moment = moment_func(rear_moment_arm, rear_seat_weight);
    fuel_moment = moment_func(fuel_moment_arm, usable_fuel_weight);
    baggage_moment = moment_func(baggage_moment_arm, baggage_weight);

    int total_weight = front_seat_weight + rear_seat_weight + usable_fuel_weight + baggage_weight;

    // Check if design limits are met. INCOMPLETE
    if (total_weight > 2950) {

    }

    return 0;
}