// Copyright Mit Bailey 2020
// mitbailey.com

// Created for the Intro to Aerospace Lab at University of Massachusetts Lowell.
// Designed to allow easy calculating of rocket related mathematics.

#include <iostream>
#include <cstdlib>
#include "userinterface.hpp"
#include "implementation.hpp"

int main(int argc, char* argv[]) {
	introduction();
	displayHelpAbridged();

	// Initialize weather and launchVehicle with default values.
	Conditions weather;
	Vehicle launchVehicle(weather);

	bool exit = false;
	while (!exit) {
		exit = userInputHandler(weather, launchVehicle);
	}

	return 0;
}

// Test Case 1: Estes Farside w/ C6-7
// .set vehicle 0.045 0.01248 0.0269 0.000506707479 10 15.3
// .set parachute -1 -1 3
// .calculate parachute diameter
// .run

/*
CURRENT CONDITIONS
Temperature: 273.15
Pressure: 101325

CURRENT CONFIGURATION
Coefficient of Drag: 0.75
Mass empty: 0.045
Mass loaded: 0.0719
Mass average: 0.05845
Mass average: 0.05845
Engine mass empty: 0.01442
Engine mass loaded: 0.0269
Engine mass average: 0.02066
Cross-sectional area: 0.000506707
Engine impulse: 10
Engine thrust: 15.3
Parachute diameter: 0.453695
Parachute Coefficient of Drag: 0.75


RUNNING SIMULATION...
=====================================================================
ALTITUDE~
At MECO: 50.1907
Gained during coast phase: +274.857
At apogee: 325.047

VELOCITY~
Maximum: 143.651
Landing: 3

TIME~
To MECO: 0.653595
MECO to apogee: 14.6483
Total aloft: 23.4439
Apogee to ground (no parachute): 8.14194
Apogee to ground (parachute)*: 108.349
*Assuming the parachute opens at apogee. Subtract from this value the seconds the parachute takes to deploy.

=====================================================================
*/