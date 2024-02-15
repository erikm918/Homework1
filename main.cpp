#include <iostream>
#include <array>
#include <vector>
#include <map>
#include <string>
#include <memory>
#include "Additional/plane.h"
#include "Additional/pilot.h"
#include "Additional/functions.h"
using namespace std;

int main() {
    /* Basic_Info plane_info = get_info();

    // Moments & Total Weight
    array<double, 4> plane_moments;
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
    
    // CoG
    double center_of_gravity = moment_sum/total_weight;

    // Was here for checking an issue; fixed.
    // cout << moment_sum << ", " << total_weight << endl; 
    // cout << center_of_gravity << endl;

    weight_limit(plane_moments, plane_info.usable_fuel_weight, plane_info.fuel_moment_arm, total_weight);

    center_of_gravity_limit(plane_moments, plane_info.usable_fuel_weight, plane_info.fuel_moment_arm,
                            total_weight, center_of_gravity);  */

    Plane plane1("SCE", "PHL");

    // Sets the plane's velocity and chosen time step for the operate function.
    double speed = 450;
    double dt = 30;
    int max_iterations = 1042;
    plane1.set_vel(speed);

    // for (int i = 0; i <= max_iterations; i++) {
    //     plane1.operate(dt);
    //     cout << "Time: " << dt*i << " seconds. Position: " << plane1.get_pos() << " miles." << endl; 
    //     std::cout << plane1.get_atSCE() << std::endl;
    // } 

    Pilot pilot1("Alpha");
    Pilot pilot2("Bravo");

    Plane plane2("SCE", "PHL");
    plane2.set_vel(speed);

    pilot1.myPlane = &plane2;
    pilot2.myPlane = 0;

    cout << "Pilot " << pilot1.get_name() << " with memory address " << &pilot1 
         << " is in control of the plane with memory address " << pilot1.myPlane << endl;

    cout << "Pilot " << pilot2.get_name() << " with memory address " << &pilot2 
         << " is in control of the plane with memory address " << pilot2.myPlane << endl;

    for (int i = 0; i <= max_iterations; i++) {
        plane2.operate(dt);

        if (plane2.get_atSCE() && pilot1.myPlane) {
            cout << "The plane " << &plane2 << " is at SCE." << endl;
            
            pilot2.myPlane = &plane2;
            pilot1.myPlane = 0;

            cout << "Pilot " << pilot2.get_name() << " is in control of plane " << pilot2.myPlane << endl;
            cout << "Pilot " << pilot1.get_name() << " is in control of plane " << pilot1.myPlane << endl;
        }
        else if (plane2.get_atSCE() && pilot2.myPlane && !pilot1.myPlane) {
            cout << "The plane " << &plane2 << " is at SCE." << endl;
            
            pilot1.myPlane = &plane2;
            pilot2.myPlane = 0;

            cout << "Pilot " << pilot1.get_name() << " is in control of plane " << pilot1.myPlane << endl;
            cout << "Pilot " << pilot2.get_name() << " is in control of plane " << pilot2.myPlane << endl;
        }
    }

    delete pilot1.myPlane, pilot2.myPlane;

    return 0;
}