#include <iostream>
#include "functions.h"
using namespace std;

double empt_weight, empt_weight_moment, front_moment_arm, rear_moment_arm, front_seat_weight, rear_seat_weight, 
        gal_usable_fuel, usable_fuel_weight, fuel_moment_arm, baggage_moment_arm, baggage_weight;
int num_front_seat, num_rear_seat;

void get_info() {
    // Get the information from the user about the plane. Stores it in global variables for later use.
    cout << "Please input the airplane emtpy weight: " << endl;
    cin >> empt_weight;
    cout << "Please input the airplane empty weight moment: " << endl;
    cin >> empt_weight_moment;

    // Front Seat Info
    cout << "Please input the number of front seat passengers: " << endl;
    cin >> num_front_seat;

    for (int i = 0; i < num_front_seat; i++) {
        double pass_weight;
        cout << "Enter weight of passenger " << i+1 << ": " << endl;
        cin >> pass_weight;
        front_seat_weight = front_seat_weight + pass_weight;
    }

    cout << "Please input the front seat moment arm: " << endl;
    cin >> front_moment_arm;

    // Rear Seat Info
    cout << "Please input the number of rear seat passengers: " << endl;
    cin >> num_rear_seat;

    for (int i = 0; i < num_rear_seat; i++) {
        double pass_weight;
        cout << "Enter weight of passenger " << i+1 << ": " << endl;
        cin >> pass_weight;
        rear_seat_weight = rear_seat_weight + pass_weight;
    }

    cout << "Please input the rear seat moment arm: " << endl;
    cin >> rear_moment_arm;

    // Fuel Info
    cout << "Please input the number of gallons of usable fuel: " << endl;
    cin >> gal_usable_fuel;
    cout << "Please input the usable fuel weight: " << endl;
    cin >> usable_fuel_weight;
    cout << "Please input the fuel tank moment arm: " << endl;
    cin >> fuel_moment_arm;

    // Baggage Info
    cout << "Please input the baggage weight: " << endl;
    cin >> baggage_weight;
    cout << "Please input the baggage moment arm: " << endl;
    cin >> baggage_moment_arm;
}

double moment_func (double arm, double weight) {
    // Function that determines the moment of a given part of the plane.
    double moment = 0;
    moment = arm*weight;
    return moment;
}

