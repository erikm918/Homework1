#include <iostream>
#include <array>

int main() {
    int empt_weight, empt_weight_moment, num_front_seat, front_seat_weight[num_front_seat], front_moment_arm, 
        num_rear_seat, rear_seat_weight[num_rear_seat], rear_moment_arm, gal_usable_fuel, usable_fuel_weight, 
        fuel_moment, baggage_moment, baggage_weight;


    std::cout << "Please input the airplane emtpy weight: " << std::endl;
    std::cin >> empt_weight;
    std::cout << "Please input the airplane empty weight moment: " << std::endl;
    std::cin >> empt_weight_moment;
    std::cout << "Please input the number of front seat passengers: " << std::endl;
    std::cin >> num_front_seat;
    for (int i = 0; i < num_front_seat; i++) {
        std::cout << "Enter weight of passenger " << i+1 << ": " << std::endl;
        std::cin >> front_seat_weight[i];
    }


    // std::cout << "Please input the airplane emtpy weight: " << std::endl;
    // std::cin >> empt_weight;
    // std::cout << "Please input the airplane emtpy weight: " << std::endl;
    // std::cin >> empt_weight;
    // std::cout << "Please input the airplane emtpy weight: " << std::endl;
    // std::cin >> empt_weight;
    // std::cout << "Please input the airplane emtpy weight: " << std::endl;
    // std::cin >> empt_weight;
    // std::cout << "Please input the airplane emtpy weight: " << std::endl;
    // std::cin >> empt_weight;
    // std::cout << "Please input the airplane emtpy weight: " << std::endl;
    // std::cin >> empt_weight;
    // std::cout << "Please input the airplane emtpy weight: " << std::endl;
    // std::cin >> empt_weight;
    // std::cout << "Please input the airplane emtpy weight: " << std::endl;
    // std::cin >> empt_weight;
    // std::cout << "Please input the airplane emtpy weight: " << std::endl;
    // std::cin >> empt_weight;
    // std::cout << "Please input the airplane emtpy weight: " << std::endl;
    // std::cin >> empt_weight;
    return 0;
}