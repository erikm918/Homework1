#ifndef FUNC 
#define FUNC

#include <array>
using namespace std;


/*
    Basic structures to store infomration. All of the information is determined from functions within this file
    and then may be used in the may file for calculations. 
*/
struct Basic_Info {
    double empt_weight, empt_weight_moment, front_moment_arm, rear_moment_arm, front_seat_weight, rear_seat_weight, 
        gal_usable_fuel, usable_fuel_weight, fuel_moment_arm, baggage_moment_arm, baggage_weight;
    int num_front_seat, num_rear_seat;  
};

struct Data{
    double center_of_gravity, usable_fuel_weight, total_weight;
};

/*
    Takes user input to get the basic information about the plane that will be later operated on. Stores it in a 
    structure Basic_Info.
*/
Basic_Info get_info();


// Funciton that uses the definition of a moment to determine the moment of a given moment arm and weight.
double moment_func (double arm, double weight);

/*
    Function that checks if the weight limit is met. If the plane is overweight, it attempts to remove fuel such
    that the plane will be able to meet the limitations. If fuel cannot be removed to meet the given requirements,
    it will warn the user and exit the program.
*/
Data weight_limit(double moments, double usable_fuel_weight, double fuel_moment_arm, 
                  double total_weight);

/* 
    Determines if the center of gravity is over or under the limit. If it is, it determines how much 
    fuel needs to be added or removed in order to meet the design limitations. If the design limitations
    cannot be met (ie. too much fuel is added or removed) the program will be terminated and alert the 
    user of the problem. 
*/
Data center_of_gravity_limit(double moments, double usable_fuel_weight, double fuel_moment_arm,
                             double total_weight, double center_of_gravity);

/*
    Creates two pilots who have names as given by the inputs to the function. Creates a raw pointer for a plane that
    is then is operated on later. Using a while loop and conditionals it swaps the pointer defined in the pilot class
    with the plane pointer and a null pointer that is used as a placeholder. Location (if the plane is at SCE) and 
    which pilot is in control is checked upon each iteration to see if pilot swapping is needed. After the max
    iterations is reached, the memory is returned to the computer to prevent a memory leak.
*/
void create_flight(std::string pilot1_name, std::string pilot2_name, double speed, int iterations, double dt,
                   std::string origin, std::string destination);

/*
    Same funcitonality as the function using raw pointers, but uses smart pointers so returning memory to the computer
    not necessary as this is done automatically.
*/
void create_flight_new_style(std::string pilot1_name, std::string pilot2_name, double speed, int iterations, 
                   double dt, std::string origin, std::string destination);

#endif 