// Copyright Mit Bailey 2020
// mitbailey.com

// Created for the Intro to Aerospace Lab at University of Massachusetts Lowell.
// Designed to allow easy calculating of rocket related mathematics.

// http://www.rocketmime.com/rockets/rckt_eqn.html#Method

#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <vector>

#define g 9.80665 // Force of gravity, m/s^2
#define R 287.05 // Gas constant for dry air, J/(kg.K)
#define pi 3.1415926535897932384626433832795028841971 // Pi

// Forward declarations
class Vehicle;

// Mass
// Cross-sectional Area
// Wind resistance force
// Air density
// Drag coefficient of rocket
// Engine impulse and thrust
// Engine burn time

class Conditions {
public:
	Conditions() { pressure = 101325; temperature = 273.15; calculateAirDensity(); } // Default to STP
	Conditions(double temperature, double pressure) { this->pressure = pressure; this->temperature = temperature; calculateAirDensity(); }
	void updateConditions(double temperature, double pressure) { this->pressure = pressure; this->temperature = temperature; calculateAirDensity(); }

	double pressure; // Pascals
	double temperature; // Kelvin
	double airDensity; // kg/m^3

	double calculateAirDensity() { airDensity = pressure / (R * temperature); return airDensity; }
};

// Mass measured in kilograms.
class Mass {
public:
	Mass() { this->loaded = 0; this->empty = 0; calculateAverageMass(); }
	Mass(double loaded, double empty) { this->loaded = loaded; this->empty = empty; calculateAverageMass(); }

	double loaded;
	double empty;
	double average; // Use this if this objects mass never changes, or goes from 100% to 0% in this timeframe.

	double calculateAverageMass() { average = (loaded + empty) / 2; return average; } // Assuming a constant burn rate.
};

class Engine {
public:
	Mass mass;

	double impulse;
	double thrust;
	double burnTime;

	double calculateBurnTime() { burnTime = impulse / thrust; return burnTime; }
};

class Parachute {
public:
	void updateParachute(double diameter, double coefficientOfDrag, double landingVelocity) {
		if (diameter >= 0)
			this->diameter = diameter;
		if (coefficientOfDrag >= 0)
			this->coefficientOfDrag = coefficientOfDrag;
		if (landingVelocity >= 0)
			this->landingVelocity = landingVelocity;
	}

	// Calculates the diameter required to achieve the desired descent speed.
	double calculateDiameter(Vehicle& vehicle);

	// Calculates the speed given the diameter.
	double calculateDescentSpeed(Vehicle& vehicle);

	void displayParachute() {
		std::cout << "Diameter: " << diameter << std::endl;
		std::cout << "Coefficient of Drag: " << coefficientOfDrag << std::endl;
		std::cout << "Landing Velocity: " << landingVelocity << std::endl;
	}

	//diameter = sqrt( (8 vehicle.mass * g) / (3.14 * airDensity * parachuteDragCoefficient * maxDescentSpeed^2) )

	double coefficientOfDrag = 0.75; // Assumption is this is parasheet (estes rocket). Use 1.5 for a real dome-shaped 'chute.
	double diameter;
	double landingVelocity = 3; // Maximum speed we want the rocket to be hitting the ground.
};

// Vehicle phases:
// Pre-Launch - Rocket has not been fired.
// Boost - The engine(s) are firing.
// Coast - The engine(s) have expended their fuel, but the rocket continues upwards.
// Descent - The rocket has passed altitudeMax and is now heading towards the surface.
// Landing - Rocket has landed.
class Vehicle {
public:
	Vehicle(Conditions conditions) {
		// Set the things we didn't receive to default values.
		this->conditions = conditions;
		this->dragCoefficient = 0.75;
		mass.empty = 0;
		mass.loaded = 0;
		engine.mass.empty = 0;
		engine.mass.loaded = 0;
		this->area = 0;
		engine.impulse = 0;
		engine.thrust = 0;

		performCalculations();
	}

	// Given vehicle information, conditions, and dragCoefficient.
	Vehicle(double massVehicleEmpty, double massVehicleLoaded, double massEngineEmpty, double massEngineLoaded,
		double area, double impulse, double thrust, double dragCoefficient, Conditions conditions) {
		// Set the things we didn't receive to default values.
		this->conditions = conditions;
		this->dragCoefficient = dragCoefficient;
		mass.empty = massVehicleEmpty;
		mass.loaded = massVehicleLoaded;
		engine.mass.empty = massEngineEmpty;
		engine.mass.loaded = massEngineLoaded;
		this->area = area;
		engine.impulse = impulse;
		engine.thrust = thrust;

		performCalculations();
	}

	void updateVehicle(double massVehicleEmpty, double massVehicleLoaded, double massEngineEmpty, double massEngineLoaded,
		double area, double impulse, double thrust, double dragCoefficient, Conditions conditions) {

		this->conditions = conditions;
		this->dragCoefficient = dragCoefficient;
		mass.empty = massVehicleEmpty;
		mass.loaded = massVehicleLoaded;
		engine.mass.empty = massEngineEmpty;
		engine.mass.loaded = massEngineLoaded;
		this->area = area;
		engine.impulse = impulse;
		engine.thrust = thrust;

		performCalculations();
	}

	void performCalculations() {
		this->conditions.calculateAirDensity();
		engine.calculateBurnTime();
		mass.calculateAverageMass();
		calculateK();
		calculateQ();
		calculateX();
		calculateVelocityMax();
		calculateAltitudeBoost();
		calculateHeightCoast();
		calculateAltitudeMax();
		calculateTimeMECOToAP();
		calculateTimeAPToGround();
		calculateTimeAPToGroundParachute();
		calculateTimeOfFlight();
		parachute.calculateDescentSpeed(*this);
	}

	void updateConditions(double temp, double pres) {
		conditions.updateConditions(temp, pres);
	}

	void runSimulation() {
		performCalculations();
		displayResults();
	}

	void displayConditions(){
		std::cout << "Temperature: " << conditions.temperature << std::endl;
		std::cout << "Pressure: " << conditions.pressure << std::endl;
	}

	void displayConfiguration(){
		std::cout << "Coefficient of Drag: " << dragCoefficient << std::endl;
		std::cout << "Mass empty: " << mass.empty << std::endl;
		std::cout << "Mass loaded: " << mass.loaded << std::endl;
		std::cout << "Mass average: " << mass.average << std::endl;
		std::cout << "Mass average: " << mass.calculateAverageMass() << std::endl;
		std::cout << "Engine mass empty: " << engine.mass.empty << std::endl;
		std::cout << "Engine mass loaded: " << engine.mass.loaded << std::endl;
		std::cout << "Engine mass average: " << engine.mass.calculateAverageMass() << std::endl;
		std::cout << "Cross-sectional area: " << area << std::endl;
		std::cout << "Engine impulse: " << engine.impulse << std::endl;
		std::cout << "Engine thrust: " << engine.thrust << std::endl;
		std::cout << "Parachute diameter: " << parachute.diameter << std::endl;
		std::cout << "Parachute Coefficient of Drag: " << parachute.coefficientOfDrag << std::endl;
	}

	void displayResults(){
		std::cout << std::endl;
		std::cout << "RUNNING SIMULATION..." << std::endl;
		std::cout << "=====================================================================" << std::endl;
		std::cout << "ALTITUDE~" << std::endl;
		std::cout << "At MECO: " << altitudeBoost << std::endl;
		std::cout << "Gained during coast phase: +" << heightCoast << std::endl;
		std::cout << "At apogee: " << altitudeMax << std::endl;
		std::cout << std::endl;

		std::cout << "VELOCITY~" << std::endl;
		std::cout << "Maximum: " << velocityMax << std::endl;
		std::cout << "Landing: " << parachute.landingVelocity << std::endl;
		std::cout << std::endl;

		std::cout << "TIME~" << std::endl;
		std::cout << "To MECO: " << engine.burnTime << std::endl;
		std::cout << "MECO to apogee: " << timeMECOToAP << std::endl;
		std::cout << "Total aloft: " << timeOfFlight << std::endl;
		std::cout << "Apogee to ground (no parachute): " << timeAPToGround << std::endl;
		std::cout << "Apogee to ground (parachute)*: " << timeAPToGroundParachute << std::endl;
		std::cout << "*Assuming the parachute opens at apogee. Subtract from this value the seconds the parachute takes to deploy." << std::endl;
		std::cout << std::endl;
		std::cout << "=====================================================================" << std::endl;
		std::cout << std::endl;
	}

	Conditions conditions;

	Mass mass;
	Engine engine;
	Parachute parachute;

	double k;
	double q;
	double x;

	double area; //cross sectional area
	double velocityMax;
	double altitudeBoost;
	double heightCoast;
	double altitudeMax;
	double dragCoefficient;

	double timeMECOToAP;
	double timeAPToGround;
	double timeAPToGroundParachute;
	double timeOfFlight;

	// Functions
	double calculateK() { k = 0.5 * conditions.airDensity * dragCoefficient * area;	return k; }
	double calculateQ() { q = std::sqrt((engine.thrust - (mass.average * g)) / k); return q; }
	double calculateX() { x = (2 * k * q) / mass.average; return x; }

	double calculateVelocityMax();
	double calculateAltitudeBoost();
	double calculateHeightCoast();

	double calculateAltitudeMax();

	// New
	double calculateTimeMECOToAP() { timeMECOToAP = velocityMax / g; return timeMECOToAP; }
	double calculateTimeAPToGround() { timeAPToGround = sqrt((2 * altitudeMax) / g); return timeAPToGround; }
	double calculateTimeAPToGroundParachute() { timeAPToGroundParachute = altitudeMax / parachute.landingVelocity; return timeAPToGroundParachute; }
	double calculateTimeOfFlight() { timeOfFlight = engine.burnTime + timeMECOToAP + timeAPToGround; return timeOfFlight; }
};

double Vehicle::calculateVelocityMax() {
	velocityMax = q * ((1 - std::exp(-x * engine.burnTime)) / (1 + std::exp(-x * engine.burnTime)));
	return velocityMax;
}

double Vehicle::calculateAltitudeBoost() {
	double z = engine.thrust - mass.average * g;
	double y = k * velocityMax * velocityMax;
	altitudeBoost = (-mass.average / (2 * k)) * std::log((z - y) / (z));
	return altitudeBoost;
}

double Vehicle::calculateHeightCoast() {
	double massCoast = mass.empty + engine.mass.empty;
	double mg = massCoast * g;
	heightCoast = (massCoast / (2 * k))*std::log((mg + k * velocityMax * velocityMax) / (mg));
	return heightCoast;
}

double Vehicle::calculateAltitudeMax() {
	altitudeMax = altitudeBoost + heightCoast;
	return altitudeMax;
}

// Calculates the diameter required to achieve the desired descent speed.
double Parachute::calculateDiameter(Vehicle& vehicle) {
	diameter = std::sqrt((8 * vehicle.mass.loaded * g) / (pi * vehicle.conditions.airDensity * coefficientOfDrag * (landingVelocity * landingVelocity)));
	return diameter;
};

// Calculates the speed given the diameter.
double Parachute::calculateDescentSpeed(Vehicle& vehicle) {
	landingVelocity = std::sqrt((8 * vehicle.mass.loaded * g) / (pi * vehicle.conditions.airDensity * coefficientOfDrag * (diameter * diameter)));
	return landingVelocity;
};