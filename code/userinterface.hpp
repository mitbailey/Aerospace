// Copyright Mit Bailey 2020
// mitbailey.com

// Created for the Intro to Aerospace Lab at University of Massachusetts Lowell.
// Designed to allow easy calculating of rocket related mathematics.

#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include "implementation.hpp"

void introduction() {
	std::cout << "--- MODEL ROCKETRY CALCULATION SUITE ---" << std::endl;
	std::cout << "Copyright Mit Bailey 2020" << std::endl;
	std::cout << "mitbailey.com" << std::endl;
	std::cout << std::endl;
}

void displayHelpAbridged() {
	std::cout << "To view help, type .help" << std::endl;
	std::cout << "To view command-specific help, type .help <command>" << std::endl;
	std::cout << std::endl;
}

void displayHelp() {
	std::cout << ".help - Display available commands and what they do." << std::endl;
	std::cout << ".help units - Display required units." << std::endl;
	std::cout << ".help <command> - Display detailed information about that command." << std::endl;
	std::cout << ".run - Run the simulation given the current launch vehicle configuration and weather conditions." << std::endl;
	std::cout << ".set vehicle - Creates a new launch vehicle with the relevant parameters." << std::endl;
	std::cout << ".set conditions - Creates a new set of weather conditions." << std::endl;
	std::cout << ".display vehicle - Displays the current launch vehicle." << std::endl;
	std::cout << ".display conditions - Displays the current weather conditions." << std::endl;
	std::cout << ".exit - Closes the program." << std::endl;
	std::cout << std::endl;
}

void displayHelp(std::string command) {
	if (command == "help") {
		std::cout << "But why?" << std::endl;
		std::cout << std::endl;
	}
	else if (command == "units") {
		std::cout << "Mass -------- Kilograms" << std::endl;
		std::cout << "Length ------ Meters" << std::endl;
		std::cout << "Pressure ---- Pascals" << std::endl;
		std::cout << "Temperature - Kelvin" << std::endl;
		std::cout << "Area -------- Square Meters" << std::endl;
		std::cout << "Impulse ----- Newton-Seconds" << std::endl;
		std::cout << "Thrust ------ Newtons" << std::endl;
		std::cout << std::endl;
	}
	else if (command == "set vehicle") {
		std::cout << "Description: " << std::endl;
		std::cout << "Creates a new launch vehicle with the relevant parameters." << std::endl;
		std::cout << std::endl;
		std::cout << "Parameters: " << std::endl;
		std::cout << "Required... <Vehicle Mass (Empty)> <Vehicle Mass (Loaded)> <Engine Mass (Empty)> <Engine Mass (Loaded)> <Cross-Sectional Area> <Engine Impulse> <Engine Thrust>" << std::endl;
		std::cout << "Optional... <Coefficient of Drag>" << std::endl;
		std::cout << std::endl;
	}
	else if (command == "set conditions") {
		std::cout << "Description: " << std::endl;
		std::cout << "Creates a new set of weather conditions." << std::endl;
		std::cout << std::endl;
		std::cout << "Parameters: " << std::endl;
		std::cout << "Required... <Temperature> <Pressure>" << std::endl;
		std::cout << std::endl;
	}
	else if (command == "display vehicle") {
		std::cout << "Description: " << std::endl;
		std::cout << "Displays the current launch vehicle." << std::endl;
		std::cout << std::endl;
		std::cout << "Parameters: " << std::endl;
		std::cout << "Required... N/A" << std::endl;
		std::cout << "Optional... N/A" << std::endl;
		std::cout << std::endl;
	}
	else if (command == "display conditions") {
		std::cout << "Description: " << std::endl;
		std::cout << "Displays the current weather conditions." << std::endl;
		std::cout << std::endl;
		std::cout << "Parameters: " << std::endl;
		std::cout << "Required... N/A" << std::endl;
		std::cout << "Optional... N/A" << std::endl;
		std::cout << std::endl;
	}
	else if (command == "exit") {
		std::cout << "Description: " << std::endl;
		std::cout << "Closes the program." << std::endl;
		std::cout << std::endl;
		std::cout << "Parameters: " << std::endl;
		std::cout << "Required... N/A" << std::endl;
		std::cout << "Optional... N/A" << std::endl;
		std::cout << std::endl;
	}
}

std::vector<std::string> tokenizer(std::string input) {
	// Splits the user's input command into a vector of strings delimited by spaces.
	// Example:
	// .help new vehicle
	// 0 -> .help
	// 1 -> new
	// 2 -> vehicle
	std::vector<std::string> tokenizedInput;
	std::string delimiter = " ";

	unsigned int position = 0;

	position = input.find(delimiter);
	while (position != std::string::npos) {
		tokenizedInput.push_back(input.substr(0, position));
		input.erase(0, position + delimiter.length());
		position = input.find(delimiter);
	}
	tokenizedInput.push_back(input.substr(0, position));
	input.erase(0, position + delimiter.length());
	position = input.find(delimiter);

	/*
	// Prints the contents of the vector for debugging purposes.
	for (std::vector<std::string>::const_iterator i = tokenizedInput.begin(); i != tokenizedInput.end(); ++i)
		std::cout << *i << ' ' << std::endl;
	*/

	return tokenizedInput;
}

bool userInputHandler(Conditions &weather, Vehicle &launchVehicle) {
	std::vector<std::string> tokens;
	std::string input;

	std::cout << ">";

	// Gets a line of input and runs it through tokenizer, making a vector<string> out of it.
	getline(std::cin, input);
	tokens = tokenizer(input);

	// All inputs begin with a string, and some have either a string or a number of ints following it.
	// 1. Determine what the command is by reading in the first string.
	// 2. Take in a number of ints or another string depending.

	if (tokens.at(0) == ".help") {
		switch (tokens.size()) {
		case 1:
			displayHelp();
			break;
		case 2:
			displayHelp(tokens.at(1));
			break;
		case 3:
			displayHelp(tokens.at(1) + " " + tokens.at(2));
			break;
		default:
			std::cout << "[userinterface.hpp/userInputHandler] Error: Default case entered in .help switch. Try entering less arguments." << std::endl;
			break;
		}
	}
	else if (tokens.at(0) == ".run") {
		// Display current LV and Conditions.
		std::cout << std::endl;
		std::cout << "CURRENT CONDITIONS" << std::endl;
		launchVehicle.displayConditions();
		std::cout << std::endl;
		std::cout << "CURRENT CONFIGURATION" << std::endl;
		launchVehicle.displayConfiguration();
		std::cout << std::endl;
		launchVehicle.runSimulation();
	}
	else if (tokens.at(0) == ".set") {
		// .set conditions TEMPERATURE PRESSURE
		// .set vehicle A B C D E F G
		// .set vehicle A B C D E F G H

		if (tokens.size() == 9) {
			// Didn't receive a coefficient of drag, so use a reasonable default value of 0.75.
			launchVehicle.updateVehicle(std::stod(tokens.at(2)), std::stod(tokens.at(3)), std::stod(tokens.at(4)), std::stod(tokens.at(5)),
				std::stod(tokens.at(6)), std::stod(tokens.at(7)), std::stod(tokens.at(8)), 0.75, weather);
		}
		else if (tokens.size() == 10) {
			launchVehicle.updateVehicle(std::stod(tokens.at(2)), std::stod(tokens.at(3)), std::stod(tokens.at(4)), std::stod(tokens.at(5)),
				std::stod(tokens.at(6)), std::stod(tokens.at(7)), std::stod(tokens.at(8)), std::stod(tokens.at(9)), weather);
		}
		else if (tokens.size() == 4) {
			// Wants to set conditions.
			launchVehicle.updateConditions(std::stod(tokens.at(2)), std::stod(tokens.at(3)));
		}
		else if (tokens.size() < 4) {
			std::cout << "[userinterface.hpp/userInputHandler] Error: Too few arguments entered for .set command." << std::endl;
		}
		else if (tokens.size() < 9 && tokens.size() > 4) {
			std::cout << "[userinterface.hpp/userInputHandler] Error: Invalid number of arguments entered for .set command." << std::endl;
		}
		else {
			std::cout << "[userinterface.hpp/userInputHandler] Error: Too many arguments entered for .set command. Try entering less arguments." << std::endl;
		}
	}
	else if (tokens.at(0) == ".display") {
		if (tokens.at(1) == "vehicle") {
			launchVehicle.displayConfiguration();
		}
		else if (tokens.at(1) == "conditions") {
			launchVehicle.displayConditions();
		}
		else {
			std::cout << "[userinterface.hpp/userInputHandler] Error: Invalid .display command. Try .display vehicle or .display conditions." << std::endl;
		}
	}
	else if (tokens.at(0) == ".exit") {
		return true;
	}
	else {
		std::cout << "Command not recognized." << std::endl;
		std::cout << std::endl;
	}

	return false;
	std::cout << std::endl;
}
