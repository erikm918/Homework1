#ifndef FUNC 
#define FUNC

// Get the information from the user about the plane.
auto get_info();

// Moment calculation.
double moment_func (double arm, double weight);

// Determines if weight requirements are met.
auto weight_limit(array<double, 4> moments, double usable_fuel_weight, double fuel_moment_arm, double total_weight);

// Determines if the center of gravity requirements are met.
auto center_of_gravity_limit(array<double, 4> moments, double usable_fuel_weight, double fuel_moment_arm,
                             double total_weight, double center_of_gravity);

#endif 