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