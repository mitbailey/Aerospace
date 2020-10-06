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
	std::cout << "--- MODEL ROCKETRY CALCULATION SUITE V2 ---" << std::endl;
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
	std::cout << std::endl;

	std::cout << ".run - Run the simulation given the current launch vehicle configuration and weather conditions." << std::endl;
	std::cout << ".set vehicle - Creates a new launch vehicle with the relevant parameters." << std::endl;
	std::cout << ".set conditions - Creates a new set of weather conditions." << std::endl;
	std::cout << ".set parachute - Sets the parameters of the vehicle's parachute." << std::endl;
	std::cout << ".set angle - Manually sets the launch angle of the vehicle." << std::endl;
	std::cout << ".display vehicle - Displays the current launch vehicle." << std::endl;
	std::cout << ".display conditions - Displays the current weather conditions." << std::endl;
	std::cout << ".display parachute - Displays the current parachute configuration." << std::endl;	
	std::cout << ".display angle - Displays the current launch angle." << std::endl;
	std::cout << ".calculate parachute diameter - Uses the current parachute configuration to determine optimal diameter." << std::endl;
	std::cout << ".calculate parachute velocity - Uses the current parachute configuration to determine landing velocity." << std::endl;
	std::cout << ".calculate angle - Sets the launch angle to what will return the rocket to the launchsite." << std::endl;
	std::cout << ".update - Can be used to change a single value of a class." << std::endl;
	std::cout << std::endl;

	std::cout << ".credits - Shows the credits for the program." << std::endl;
	std::cout << ".exit - Closes the program." << std::endl;
	std::cout << std::endl;
}

void displayHelp(std::string command) {
	if (command == "help") {
		std::cout << "Description: " << std::endl;
		std::cout << "Displays all commands with a short description of what they do." << std::endl;
		std::cout << std::endl;
		std::cout << "Parameters: " << std::endl;
		std::cout << "Required... N/A" << std::endl;
		std::cout << "Optional... <units>, <command> " << std::endl;
		std::cout << std::endl;
	}
	else if (command == "<command>") {
		std::cout << "Try it without the <> and with a command name instead." << std::endl;
		std::cout << std::endl;
	}
	else if (command == "credits") {
		std::cout << "Description: " << std::endl;
		std::cout << "Shows the credits for the program." << std::endl;
		std::cout << std::endl;
		std::cout << "Parameters: " << std::endl;
		std::cout << "Required... N/A" << std::endl;
		std::cout << "Optional... N/A" << std::endl;
		std::cout << std::endl;
	}
	else if (command == "units") {
		std::cout << "Mass -------- Kilograms" << std::endl;
		std::cout << "Length ------ Meters" << std::endl;
		std::cout << "Distance ---- Meters" << std::endl;
		std::cout << "Velocity ---- Meters per Second" << std::endl;
		std::cout << "Pressure ---- Pascals" << std::endl;
		std::cout << "Temperature - Kelvin" << std::endl;
		std::cout << "Area -------- Square Meters" << std::endl;
		std::cout << "Impulse ----- Newton-Seconds" << std::endl;
		std::cout << "Thrust ------ Newtons" << std::endl;
		std::cout << "Time -------- Seconds" << std::endl;
		std::cout << std::endl;
	}
	else if (command == "set vehicle") {
		std::cout << "Description: " << std::endl;
		std::cout << "Creates a new launch vehicle with the relevant parameters." << std::endl;
		std::cout << std::endl;
		std::cout << "Parameters: " << std::endl;
		std::cout << "Required... <Vehicle Mass (Empty)> <Propellant Mass> <Engine Mass (Loaded)> <Cross-Sectional Area> <Engine Impulse> <Engine Thrust>" << std::endl;
		std::cout << "Optional... <Coefficient of Drag>, <Angle>" << std::endl;
		std::cout << std::endl;
	}
	else if (command == "set conditions") {
		std::cout << "Description: " << std::endl;
		std::cout << "Creates a new set of weather conditions." << std::endl;
		std::cout << std::endl;
		std::cout << "Parameters: " << std::endl;
		std::cout << "Required... <Temperature> <Pressure>" << std::endl;
		std::cout << "Optional... <Windspeed>" << std::endl;
		std::cout << std::endl;
	}
	else if (command == "set parachute") {
		std::cout << "Description: " << std::endl;
		std::cout << "Sets the parameters of the vehicle's parachute." << std::endl;
		std::cout << std::endl;
		std::cout << "Parameters: " << std::endl;
		std::cout << "Required... <Diameter> <Coefficient of Drag> <Desired Landing Velocity> <Deployment Time>" << std::endl;
		std::cout << "Optional... N/A" << std::endl;
		std::cout << "Notes...    To omit one or more arguments, enter a negative value for that argument." << std::endl;
		std::cout << std::endl;
	}
	else if (command == "set angle") {
		std::cout << "Description: " << std::endl;
		std::cout << "Sets the launch angle of the vehicle." << std::endl;
		std::cout << std::endl;
		std::cout << "Parameters: " << std::endl;
		std::cout << "Required... <Launch Angle>" << std::endl;
		std::cout << "Optional... N/A" << std::endl;
		std::cout << "Notes...    Angle is only used in range and drift calculations." << std::endl;
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
	else if (command == "display parachute") {
		std::cout << "Description: " << std::endl;
		std::cout << "Displays the current parachute configuration." << std::endl;
		std::cout << std::endl;
		std::cout << "Parameters: " << std::endl;
		std::cout << "Required... N/A" << std::endl;
		std::cout << "Optional... N/A" << std::endl;
		std::cout << std::endl;
	}	
	else if (command == "display angle") {
		std::cout << "Description: " << std::endl;
		std::cout << "Displays the current launch angle." << std::endl;
		std::cout << std::endl;
		std::cout << "Parameters: " << std::endl;
		std::cout << "Required... N/A" << std::endl;
		std::cout << "Optional... N/A" << std::endl;
		std::cout << std::endl;
	}
	else if (command == "calculate angle") {
		std::cout << "Description: " << std::endl;
		std::cout << "Sets the launch angle to what will return the rocket to the launchsite." << std::endl;
		std::cout << std::endl;
		std::cout << "Parameters: " << std::endl;
		std::cout << "Required... N/A" << std::endl;
		std::cout << "Optional... N/A" << std::endl;
		std::cout << std::endl;
	}
	else if (command == "calculate parachute diameter") {
		std::cout << "Description: " << std::endl;
		std::cout << "Uses the current parachute configuration to determine optimal diameter." << std::endl;
		std::cout << std::endl;
		std::cout << "Parameters: " << std::endl;
		std::cout << "Required... N/A" << std::endl;
		std::cout << "Optional... N/A" << std::endl;
		std::cout << std::endl;
	}
	else if (command == "calculate parachute velocity") {
		std::cout << "Description: " << std::endl;
		std::cout << "Uses the current parachute configuration to determine landing velocity." << std::endl;
		std::cout << std::endl;
		std::cout << "Parameters: " << std::endl;
		std::cout << "Required... N/A" << std::endl;
		std::cout << "Optional... N/A" << std::endl;
		std::cout << std::endl;
	} // .update - Can be used to change a single value of a class.
	else if (command == "update") {
		std::cout << "Description: " << std::endl;
		std::cout << "Can be used to change a single value of a class." << std::endl;
		std::cout << std::endl;
		std::cout << "Parameters: " << std::endl;
		std::cout << "	conditions" << std::endl;
		std::cout << "		<temperature> <pressure> <windspeed>" << std::endl;
		std::cout << "		temperature <value>" << std::endl;
		std::cout << "		pressure <value>" << std::endl;
		std::cout << "		windspeed <value>" << std::endl;
		std::cout << "	parachute" << std::endl;
		std::cout << "		diameter <value>" << std::endl;
		std::cout << "		dragCoefficient <value>" << std::endl;
		std::cout << "		landingVelocity <value>" << std::endl;
		std::cout << "		deploymentTime <value>" << std::endl;
		std::cout << "	engine" << std::endl;
		std::cout << "		impulse <value>" << std::endl;
		std::cout << "		thrust <value>" << std::endl;
		std::cout << "		burntime <value>" << std::endl;
		std::cout << "		mass" << std::endl;
		std::cout << "			loaded <value>" << std::endl;
		std::cout << "			empty <value>" << std::endl;
		std::cout << "	vehicle" << std::endl;
		std::cout << "		area <value>" << std::endl;
		std::cout << "		dragCoefficient <value>" << std::endl;
		std::cout << "		mass" << std::endl;
		std::cout << "			loaded <value>" << std::endl;
		std::cout << "			empty <value>" << std::endl;
		std::cout << std::endl;
		std::cout << "Examples:" << std::endl;
		std::cout << ".update engine mass loaded 2.5" << std::endl;
		std::cout << ".update conditions 275 101256" << std::endl;
		std::cout << ".update conditions temperature 275" << std::endl;
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
		if (tokens.size() < 2) {
			std::cout << "[userinterface.hpp/userInputHandler] Error: Too few arguments entered for .set command." << std::endl;
		}
		else if (tokens.size() < 8 && tokens.size() > 6) {
			std::cout << "[userinterface.hpp/userInputHandler] Error: Invalid number of arguments entered for .set command." << std::endl;
		}
		else if (tokens.size() > 9) {
			std::cout << "[userinterface.hpp/userInputHandler] Error: Too many arguments entered for .set command. Try entering less arguments." << std::endl;
		}
		if (tokens.at(1) == "vehicle") {
			if (tokens.size() == 8) {
				// Didn't receive a coefficient of drag, so use a reasonable default value of 0.75.
				launchVehicle.updateVehicle(std::stod(tokens.at(2)), std::stod(tokens.at(4)) + std::stod(tokens.at(2)),
					std::stod(tokens.at(4)) - std::stod(tokens.at(3)), std::stod(tokens.at(4)), std::stod(tokens.at(5)),
					std::stod(tokens.at(6)), std::stod(tokens.at(7)), 0.75, weather);
			}
			else if (tokens.size() == 9) {
				launchVehicle.updateVehicle(std::stod(tokens.at(2)), std::stod(tokens.at(4)) + std::stod(tokens.at(2)),
					std::stod(tokens.at(4)) - std::stod(tokens.at(3)), std::stod(tokens.at(4)), std::stod(tokens.at(5)),
					std::stod(tokens.at(6)), std::stod(tokens.at(7)), std::stod(tokens.at(8)), weather);
			}
		}
		else if (tokens.at(1) == "conditions") {
			if (tokens.size() == 4) {
				launchVehicle.updateConditions(std::stod(tokens.at(2)), std::stod(tokens.at(3)));
			}
			else if (tokens.size() == 5) {
				launchVehicle.updateConditions(std::stod(tokens.at(2)), std::stod(tokens.at(3)), std::stod(tokens.at(4)));
			}
		}
		else if (tokens.at(1) == "parachute") {
			launchVehicle.parachute.updateParachute(std::stod(tokens.at(2)), 
				std::stod(tokens.at(3)), std::stod(tokens.at(4)), std::stod(tokens.at(5)));
		}
		else if (tokens.at(1) == "angle") {
			launchVehicle.launchAngle = std::stod(tokens.at(2));
		}
	}
	else if (tokens.at(0) == ".display") {
		if (tokens.at(1) == "vehicle") {
			launchVehicle.displayConfiguration();
		}
		else if (tokens.at(1) == "conditions") {
			launchVehicle.displayConditions();
		}
		else if (tokens.at(1) == "parachute") {
			launchVehicle.parachute.displayParachute();
		}
		else if (tokens.at(1) == "angle") {
			launchVehicle.displayAngle();
		}
		else {
			std::cout << "[userinterface.hpp/userInputHandler] Error: Invalid .display command. Try .display vehicle or .display conditions." << std::endl;
		}
	}
	else if (tokens.at(0) == ".calculate") {
		if (tokens.at(1) == "parachute") {
			if (tokens.at(2) == "diameter") {
				launchVehicle.parachute.calculateDiameter(launchVehicle);
			}
			else if (tokens.at(2) == "velocity") {
				launchVehicle.parachute.calculateDescentSpeed(launchVehicle);
			}
		}
		else if (tokens.at(1) == "angle") {
			launchVehicle.calculateLaunchAngle();
		}
	}
	else if (tokens.at(0) == ".update") {
		if (tokens.at(1) == "conditions") {
			if (tokens.size() == 2) {
				launchVehicle.updateConditions(stod(tokens.at(3)), stod(tokens.at(4)));
			}
			else if (tokens.at(2) == "temperature") {
				launchVehicle.updateTemperature(stod(tokens.at(3)));
			}
			else if (tokens.at(2) == "pressure") {
				launchVehicle.updatePressure(stod(tokens.at(3)));
			} 
			else if (tokens.at(2) == "windspeed") {
				launchVehicle.updateWindspeed(stod(tokens.at(3)));
			}
		}
		else if (tokens.at(1) == "parachute") {
			if (tokens.at(2) == "diameter") {
				launchVehicle.parachute.updateDiamater(stod(tokens.at(2)));
				launchVehicle.parachute.calculateDescentSpeed(launchVehicle);
			}
			else if (tokens.at(2) == "dragCoefficient") {
				launchVehicle.parachute.updateDragCoefficient(stod(tokens.at(2)));
				launchVehicle.parachute.calculateDescentSpeed(launchVehicle);
			}
			else if (tokens.at(2) == "landingVelocity") {
				launchVehicle.parachute.updateLandingVelocity(stod(tokens.at(2)));
				launchVehicle.parachute.calculateDiameter(launchVehicle);
			}
			else if (tokens.at(2) == "deploymentTime") {
				launchVehicle.parachute.updateDeploymentTime(stod(tokens.at(2)));
			}
		}
		else if (tokens.at(1) == "engine") {
			if (tokens.at(2) == "impulse") {
				launchVehicle.engine.updateImpulse(stod(tokens.at(3)));
			}
			else if (tokens.at(2) == "thrust") {
				launchVehicle.engine.updateImpulse(stod(tokens.at(3)));
			}
			else if (tokens.at(2) == "burntime") {
				launchVehicle.engine.updateImpulse(stod(tokens.at(3)));
			}
			else if (tokens.at(2) == "mass") {
				if (tokens.at(3) == "loaded") {
					launchVehicle.engine.mass.updateLoaded(stod(tokens.at(4)));
				}
				else if (tokens.at(3) == "empty") {
					launchVehicle.engine.mass.updateEmpty(stod(tokens.at(4)));
				}
			}
		}
		else if (tokens.at(1) == "vehicle") {
			if (tokens.at(2) == "area") {
				launchVehicle.updateArea(stod(tokens.at(3)));
			}
			else if (tokens.at(2) == "dragCoefficient") {
				launchVehicle.updateDragCoefficient(stod(tokens.at(3)));
			}
			else if (tokens.at(2) == "mass") {
				if (tokens.at(3) == "loaded") {
					launchVehicle.mass.updateLoaded(stod(tokens.at(4)));
				}
				else if (tokens.at(3) == "empty") {
					launchVehicle.mass.updateEmpty(stod(tokens.at(4)));
				}
			}
		}
	}
	else if (tokens.at(0) == ".credits") {
		std::cout << "Program created by Mit Bailey" << std::endl;
		std::cout << "Equations sourced from http://www.rocketmime.com/rockets/rckt_eqn.html" << std::endl;
		std::cout << std::endl;
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