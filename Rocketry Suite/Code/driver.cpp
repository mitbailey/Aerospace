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

// Test Case: Estes Farside w/ C6-7
// .set vehicle 0.045 0.01248 0.0269 0.000506707479 10 15.3
// .set parachute -1 -1 3 16
// .calculate parachute diameter
// .update conditions windspeed 0
// .calculate angle
// .run  

/*
CURRENT CONDITIONS
Temperature: 273.15
Pressure: 101325
Windspeed: 0

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
Launch angle: 45

0.5 * g * 0.69808 * 0.69808
calculateVelocityTerminal: 1.16542 / 0.75 * 1.29228 * 0.000506707
altitudeBoostA: 35.4902
calculateHeightCoastA: 2373.05 1.67671
calculateTimeMECOToAPA: 101.577 / 9.80665
calculateTimeAPToDeploymentA: 16 - (0.653595 + 10.3579)
altitudeBoost: 50.1907
rangeBoost: 35.4902
rangeCoast: 494.453
calculateRange: 35.4902 + 494.453

RUNNING SIMULATION...
=====================================================================
ALTITUDE~
At MECO: 50.1907
Gained during coast phase: +274.857
At apogee: 325.047

DISTANCE~
Range: N/A
Drift: 0

VELOCITY~
Maximum: 143.651
Deployment: 6.84583
Landing: 3

TIME~
To MECO: 0.653595
MECO to apogee: 14.6483
Apogee to ground (no parachute): 8.14194
Apogee to deployment: 0.69808
Deployment to ground: 107.553
Total aloft: 123.553

ALTITUDE~
At MECO: 35.4902
Gained during coast phase: +202.868
At apogee: 238.358
At deployment: 322.658

DISTANCE~
Range: 529.943
Drift: 0

VELOCITY~
Maximum: 143.651
Deployment: 48.9202
Landing: 3

TIME~
Launch to MECO: 0.653595
MECO to apogee: 10.3579
Apogee to ground (no parachute): N/A
Apogee to deployment: 4.98848
Deployment to ground: 107.553
Total aloft: 123.553

=====================================================================
*/