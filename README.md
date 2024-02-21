# Homework 1

## Question 1
Determines if plane is within flight limitations. If not, it attempts to create a situation such that this is possible. There is certainly a better way of determining how much fuel must be added/removed to reach limitations for the center of gravity, I will come back to that at a later date. 

## Question 2
Containers consist of a map that takes strings that are then associated with the distance between the origin (SCE) and their locations. Also consists of a vector that is used to add the distances between the two locations.

This is all within the plane.cpp file.

## Question 3 & 4
Plane class.

Operate function includes the correct conversion of units to ensure that all calculations are correct.

## Question 5
Loop to run operate function for the called plane.

## Question 6
Includes pilot class and two pointer declarations, one for the new C++ style pointer and one for the old C++ style pointer.

## Question 7
Using the old pointer system, checks to see which pilot is in control of the airplane and whether the plane has landed at SCE. With this information it switches which pilot is in control of the plane, returns the memory address of the plane attached to the name of the pilot in control.

After the while loop controling the operate function is finished, memory is returned to the computer to ensure there is no issue with memory leaks.

## Question 8
Same functionality as Q7, but includes the use of smart pointers and the new style of C++ pointers.

Does not include explicit memory return as this is a built in feature of smart pointers.