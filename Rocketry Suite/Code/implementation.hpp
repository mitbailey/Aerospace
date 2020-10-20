// Copyright Mit Bailey 2020
// mitbailey.com

// Created for the Intro to Aerospace Lab at University of Massachusetts Lowell.
// Designed to allow easy calculating of rocket related mathematics.

// References~
// RocketMime:
// http://www.rocketmime.com/rockets/rckt_eqn.html#Method
// NASA:
// https://www.grc.nasa.gov/WWW/k-12/airplane/flteqs.html

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
double areaOfACircle(double diameter);

double areaOfACircle(double diameter) {
	return (pi * pow((diameter / 2), 2));
}

class Conditions {
public:
	Conditions() { pressure = 101325; temperature = 273.15; windspeed = 0; calculateAirDensity(); } // Default to STP
	Conditions(double temperature, double pressure) { this->pressure = pressure; this->temperature = temperature; calculateAirDensity(); }
	Conditions(double temperature, double pressure, double windspeed);
	void updateConditions(double temperature, double pressure) { this->pressure = pressure; this->temperature = temperature; calculateAirDensity(); }
	void updateConditions(double temperature, double pressure, double windspeed);

	double pressure; // Pascals
	double temperature; // Kelvin
	double windspeed = 0; // m/s

	double airDensity; // kg/m^3

	double calculateAirDensity() { airDensity = pressure / (R * temperature); return airDensity; }
};

Conditions::Conditions(double temperature, double pressure, double windspeed) {
	this->pressure = pressure; this->temperature = temperature; calculateAirDensity();
	this->windspeed = windspeed;
}

void Conditions::updateConditions(double temperature, double pressure, double windspeed) {
	this->pressure = pressure; this->temperature = temperature; calculateAirDensity();
	this->windspeed = windspeed;
}

// Mass measured in kilograms.
class Mass {
public:
	Mass() { this->loaded = 0; this->empty = 0; calculateAverageMass(); }
	Mass(double loaded, double empty) { this->loaded = loaded; this->empty = empty; calculateAverageMass(); }

	void updateLoaded(double value) { loaded = value; calculateAverageMass(); }

	void updateEmpty(double value) { empty = value;	calculateAverageMass();	}

	double loaded;
	double empty;
	double average; // Use this if this objects mass never changes, or goes from 100% to 0% in this timeframe.

	double calculateAverageMass() { average = (loaded + empty) / 2; return average; } // Assuming a constant burn rate.
};

class Engine {
public:
	void updateEngine(double impl, double thrs, double burn, double load, double empt);

	void updateImpulse(double value) { impulse = value; }

	void updateThrust(double value) { thrust = value; }

	void updateBurntime(double value) {	burnTime = value; }

	Mass mass;

	double impulse;
	double thrust;
	double burnTime;

	double calculateBurnTime() { burnTime = impulse / thrust; return burnTime; }
};

void Engine::updateEngine(double impl, double thrs, double burn, double load, double empt) {
	impulse = impl;
	thrust = thrs;
	burnTime = burn;
	mass.loaded = load;
	mass.empty = empt;
}

class Parachute {
public:
	void updateParachute(double diameter, double coefficientOfDrag, double landingVelocity, double deploymentTime);

	void updateDiamater(double value) { diameter = value; }

	void updateDragCoefficient(double value) { coefficientOfDrag = value; }

	void updateLandingVelocity(double value) { landingVelocity = value; }

	void updateDeploymentTime(double value) { deploymentTime = value; }

	// Calculates the diameter required to achieve the desired descent speed.
	double calculateDiameter(Vehicle& vehicle);

	// Calculates the speed given the diameter.
	double calculateDescentSpeed(Vehicle& vehicle);

	void displayParachute();

	double coefficientOfDrag = 0.75; // Assumption is this is parasheet (estes rocket). Use 1.5 for a real dome-shaped 'chute.
	double diameter;
	double landingVelocity = 3; // Maximum speed we want the rocket to be hitting the ground.
	double deploymentTime;
};

void Parachute::updateParachute(double diameter, double coefficientOfDrag, double landingVelocity, double deploymentTime) {
	if (diameter >= 0)
		this->diameter = diameter;
	if (coefficientOfDrag >= 0)
		this->coefficientOfDrag = coefficientOfDrag;
	if (landingVelocity >= 0)
		this->landingVelocity = landingVelocity;
	if (deploymentTime >= 0)
		this->deploymentTime = deploymentTime;
}

void Parachute::displayParachute() {
	std::cout << "Diameter: " << diameter << std::endl;
	std::cout << "Coefficient of Drag: " << coefficientOfDrag << std::endl;
	std::cout << "Landing Velocity: " << landingVelocity << std::endl;
	std::cout << "Deployment Time: " << deploymentTime << std::endl;
}


// Vehicle phases:
// Pre-Launch - Rocket has not been fired.
// Boost - The engine(s) are firing.
// Coast - The engine(s) have expended their fuel, but the rocket continues upwards.
// Descent - The rocket has passed altitudeMax and is now heading towards the surface.
// Landing - Rocket has landed.
class Vehicle {
public:

	// CONSTRUCTORS
	Vehicle(Conditions conditions);

	// Given vehicle information, conditions, and dragCoefficient.
	Vehicle(double massVehicleEmpty, double massVehicleLoaded, double massEngineEmpty, double massEngineLoaded,
		double area, double impulse, double thrust, double dragCoefficient, Conditions conditions);


	// UPDATERS
	void updateVehicle(double massVehicleEmpty, double massVehicleLoaded, double massEngineEmpty, double massEngineLoaded,
		double area, double impulse, double thrust, double dragCoefficient, Conditions conditions);

	void updateMassLoaded(double value) { mass.loaded = value; performCalculations(); }

	void updateMassEmpty(double value) { mass.empty = value; performCalculations(); }

	void updateArea(double value) {	area = value; performCalculations(); }

	void updateDragCoefficient(double value) { dragCoefficient = value;	performCalculations(); }

	void updateConditions(double temp, double pres) { conditions.updateConditions(temp, pres); performCalculations(); }

	void updateConditions(double temp, double pres, double wind) { conditions.updateConditions(temp, pres, wind); performCalculations(); }

	void updateParachute(double diam, double drag, double land, double time) { parachute.updateParachute(diam, drag, land, time); performCalculations(); }

	void updateEngine(double impl, double thrs, double burn, double load, double empt) { engine.updateEngine(impl, thrs, burn, load, empt); performCalculations(); }

	void updateTemperature(double value) { conditions.temperature = value; performCalculations(); }

	void updatePressure(double value) { conditions.pressure = value; performCalculations(); }

	void updateWindspeed(double value) { conditions.windspeed = value; performCalculations(); }


	// DISPLAYERS
	void displayAngle() { std::cout << "Launch angle: " << launchAngle << std::endl; }

	void displayConditions();

	void displayConfiguration();

	void displayResults();


	// RUN SIMULATION
	void runSimulation();


	// VARIABLES
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
	double dragCoefficient;

	double timeMECOToAPA;
	double timeAPToGround;
	double timeDeploymentToGround;
	double timeOfFlight;

	double drift; // Drift post parachute deployment.
	double rangeBoost; // Downrange distance while engine is on.
	double rangeCoast; // Downrange distance until parachute deployed.
	double range; // rangeBoost + rangeCoast

	double deploymentAltitudeA;
	double timeAPToDeploymentA;
	double deploymentVelocityA;

	double launchAngle = 90; // Angle the vehicle is launched at. By default this is 90 (straight up).

	// Variables based on angle (marked with suffix -A).
	double velocityTerminal;
	double velocityMaxXA; // Max horizontal velocity
	double velocityMaxYA; // Max vertical velocity
	double altitudeBoostA;
	double altitudeCoastA;
	double heightCoastA;
	double altitudeMaxA;
	double timeDeploymentToGroundA;
	double timeOfFlightA;


	// CALCULATORS
	void performCalculations();
	double calculateK() { k = 0.5 * conditions.airDensity * dragCoefficient * area;	return k; }
	double calculateQ() { q = std::sqrt((engine.thrust - (mass.average * g)) / k); return q; }
	double calculateX() { x = (2 * k * q) / mass.average; return x; }

	double calculateVelocityMax();
	
	double calculateAltitudeBoost();
		
	double calculateTimeAPToDeploymentA();

	double calculateTimeMECOToAPA();
	
	double calculateDeploymentVelocityA() {  deploymentVelocityA = g * timeAPToDeploymentA; return deploymentVelocityA; }
		
	double calculateRange();

	// deploymentTime is measured in Mission Elapsed Time (time from launch).
	double calculateDrift();

	// Will override any manually input launch angles.
	double calculateLaunchAngle();

	double calculateVelocityTerminal();

	double calculateAltitudeBoostA();

	double calculateRangeBoost();

	double calculateRangeCoast();

	double calculateVelocityMaxXA();

	double calculateVelocityMaxYA();

	double calculateHeightCoastA();

	double calculateAltitudeMaxA();

	double calculateDeploymentAltitudeA();

	double calculateTimeDeploymentToGroundA();

	double calculateTimeOfFlightA();

};

Vehicle::Vehicle(Conditions conditions) {
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

Vehicle::Vehicle(double massVehicleEmpty, double massVehicleLoaded, double massEngineEmpty, double massEngineLoaded,
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

void Vehicle::updateVehicle(double massVehicleEmpty, double massVehicleLoaded, double massEngineEmpty, double massEngineLoaded,
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

void Vehicle::displayConditions() {
	std::cout << "Temperature: " << conditions.temperature << std::endl;
	std::cout << "Pressure: " << conditions.pressure << std::endl;
	std::cout << "Windspeed: " << conditions.windspeed << std::endl;
}

void Vehicle::displayConfiguration() {
	std::cout << "Coefficient of Drag: " << dragCoefficient << std::endl;
	std::cout << "Mass empty: " << mass.empty << std::endl;
	std::cout << "Mass loaded: " << mass.loaded << std::endl;
	std::cout << "Mass average: " << mass.average << std::endl;
	std::cout << "Engine mass empty: " << engine.mass.empty << std::endl;
	std::cout << "Engine mass loaded: " << engine.mass.loaded << std::endl;
	std::cout << "Engine mass average: " << engine.mass.calculateAverageMass() << std::endl;
	std::cout << "Cross-sectional area: " << area << std::endl;
	std::cout << "Engine impulse: " << engine.impulse << std::endl;
	std::cout << "Engine thrust: " << engine.thrust << std::endl;
	std::cout << "Parachute diameter: " << parachute.diameter << std::endl;
	std::cout << "Parachute Coefficient of Drag: " << parachute.coefficientOfDrag << std::endl;
	std::cout << "Launch angle: " << launchAngle << std::endl;
}

void Vehicle::displayResults() {
	std::cout << std::endl;
	std::cout << "RUNNING SIMULATION..." << std::endl;
	std::cout << "=====================================================================" << std::endl;
	std::cout << "ALTITUDE~" << std::endl;
	std::cout << "At MECO: " << altitudeBoostA << std::endl;
	std::cout << "Gained during coast phase: +" << heightCoastA << std::endl;
	std::cout << "At apogee: " << altitudeMaxA << std::endl;
	std::cout << "At deployment: " << deploymentAltitudeA << std::endl;
	std::cout << std::endl;

	std::cout << "DISTANCE~" << std::endl;
	std::cout << "Range: " << range << std::endl;
	std::cout << "Drift: " << drift << std::endl;
	std::cout << std::endl;

	std::cout << "VELOCITY~" << std::endl;
	std::cout << "Maximum: " << velocityMax << std::endl;
	std::cout << "Terminal: " << velocityTerminal << std::endl;
	std::cout << "Deployment: " << deploymentVelocityA << std::endl;
	std::cout << "Landing: " << parachute.landingVelocity << std::endl;
	std::cout << std::endl;

	std::cout << "TIME~" << std::endl;
	std::cout << "Launch to MECO: " << engine.burnTime << std::endl;
	std::cout << "MECO to apogee: " << timeMECOToAPA << std::endl;
	///std::cout << "Apogee to ground (no parachute): " << "N/A" << std::endl;
	std::cout << "Apogee to deployment: " << timeAPToDeploymentA << std::endl;
	std::cout << "Deployment to ground: " << timeDeploymentToGroundA << std::endl;
	std::cout << "Total aloft: " << timeOfFlightA << std::endl;
	std::cout << std::endl;

	// Warnings
	std::cout << "WARNINGS~" << std::endl;
	bool safe = true;

	if (range - drift > 15 || range - drift < -15) {
		std::cout << "Vehicle will land more than 15 meters from the launch site." << std::endl;
		safe = false;
	}

	if (timeAPToDeploymentA <= 0) {
		std::cout << "Parachute will deploy " << -1 * timeAPToDeploymentA << " seconds prior to reaching apogee." << std::endl;
		safe = false;
	}

	if (altitudeMaxA < 15) {
		std::cout << "Vehicle will not exceed 15 meters in altitude." << std::endl;
		safe = false;
	}
	else if (altitudeMaxA > 2000) {
		std::cout << "Vehicle will exceed 2000 meters in altitude." << std::endl;
		safe = false;
	}
	else if (altitudeMaxA > 1000) {
		std::cout << "Vehicle will exceed 1000 meters in altitude." << std::endl;
		safe = false;
	}
	else if (altitudeMaxA > 650) {
		std::cout << "Vehicle will exceed 650 meters in altitude." << std::endl;
		safe = false;
	}
	else if (altitudeMaxA > 300) {
		std::cout << "Vehicle will exceed 300 meters in altitude." << std::endl;
		safe = false;
	}

	if (velocityMax > 340) {
		std::cout << "Congratulations! Your vehicle will surpass Mach 1. But seriously, you might want to fix that." << std::endl;
		safe = false;
	}

	if (safe){
		std::cout << "No warnings." << std::endl;
	}

	std::cout << std::endl;

	std::cout << "=====================================================================" << std::endl;
	std::cout << std::endl;
}

void Vehicle::runSimulation() {
	performCalculations();
	displayResults();
}

void Vehicle::performCalculations() {
	this->conditions.calculateAirDensity();
	engine.calculateBurnTime();
	mass.calculateAverageMass();
	calculateK();
	calculateQ();
	calculateX();
	calculateVelocityMax();
	calculateAltitudeBoost();
	parachute.calculateDescentSpeed(*this);
	//calculateLaunchAngle(); // We dont want to calculate this here, or it'll override any manual angles (even though the program knows best).

	// Angle based calculations.
	calculateVelocityTerminal();
	calculateDrift();
	calculateVelocityMaxXA();
	calculateVelocityMaxYA();
	calculateAltitudeBoostA();
	calculateHeightCoastA();
	calculateAltitudeMaxA();
	calculateTimeMECOToAPA();
	calculateTimeAPToDeploymentA();
	calculateTimeDeploymentToGroundA();
	calculateDeploymentVelocityA();
	calculateTimeOfFlightA();
	calculateDeploymentAltitudeA();

	calculateRangeBoost();
	calculateRangeCoast();
	calculateRange();
}

double Vehicle::calculateTimeAPToDeploymentA() {
	timeAPToDeploymentA = parachute.deploymentTime - (engine.burnTime + timeMECOToAPA);
	return timeAPToDeploymentA;
}

double Vehicle::calculateTimeMECOToAPA() {
	timeMECOToAPA = velocityMaxYA / g;
	return timeMECOToAPA;
}

double Vehicle::calculateRange() {
	range = rangeBoost + rangeCoast;
	if (range < 0.00001)
		range = 0;
	return range;
}

// deploymentTime is measured in Mission Elapsed Time (time from launch).
double Vehicle::calculateDrift() {
	drift = deploymentAltitudeA / (parachute.landingVelocity / conditions.windspeed);
	if (drift < 0.00001)
		range = 0;
	return drift;
}

// Will override any manually input launch angles.
double Vehicle::calculateLaunchAngle() {
	calculateVelocityMax();
	calculateDeploymentAltitudeA();

	// Finding the angle mathematically is incredibly difficult.
	// Instead, I find it iteratively.
	double proposedRange = 0;
	double proposedAngle = 90;
	while ((proposedRange < drift - 0.001 || proposedRange > drift + 0.001) && proposedAngle > 45) {
		proposedRange = (altitudeBoost * (cos(proposedAngle / (180 / pi))))
			+ ((pow(velocityTerminal, 2) / g) *	log((pow(velocityTerminal, 2)
				+ g * (velocityMax * (cos(proposedAngle / (180 / pi)))) * parachute.deploymentTime) / (pow(velocityTerminal, 2))));
		proposedAngle -= 0.000001;
	}
	launchAngle = proposedAngle;

	return launchAngle;
}

double Vehicle::calculateVelocityTerminal() {
	double massCoast = mass.empty + engine.mass.empty;
	double mg = massCoast * g;
	velocityTerminal = sqrt((2 * mg) / (dragCoefficient * conditions.airDensity * area));
	return velocityTerminal;
}

double Vehicle::calculateAltitudeBoostA() {
	altitudeBoostA = altitudeBoost * (sin(launchAngle / (180 / pi)));
	return altitudeBoostA;
}

double Vehicle::calculateRangeBoost() {
	rangeBoost = altitudeBoost * (cos(launchAngle / (180 / pi)));
	return rangeBoost;
}

double Vehicle::calculateRangeCoast() {
	rangeCoast = (pow(velocityTerminal, 2) / g) *
		log((pow(velocityTerminal, 2) + g * velocityMaxXA * parachute.deploymentTime) / (pow(velocityTerminal, 2)));
	return rangeCoast;
}

double Vehicle::calculateVelocityMaxXA() {
	velocityMaxXA = velocityMax * (cos(launchAngle / (180 / pi)));
	return velocityMaxXA;
}

double Vehicle::calculateVelocityMaxYA() {
	velocityMaxYA = velocityMax * (sin(launchAngle / (180 / pi)));
	return velocityMaxYA;
}

double Vehicle::calculateHeightCoastA() {
	heightCoastA = ((pow(velocityTerminal, 2)) / (2 * g)) * log((pow(velocityMaxYA, 2) + pow(velocityTerminal, 2)) / (pow(velocityTerminal, 2)));
	return heightCoastA;
}

double Vehicle::calculateAltitudeMaxA() {
	altitudeMaxA = heightCoastA + altitudeBoostA;
	return altitudeMaxA;
}

double Vehicle::calculateDeploymentAltitudeA() {
	calculateTimeAPToDeploymentA();
	deploymentAltitudeA = altitudeMaxA - (0.5 * g * pow(timeAPToDeploymentA, 2)); // t^2
	return deploymentAltitudeA;
}

double Vehicle::calculateTimeDeploymentToGroundA() {
	calculateDeploymentAltitudeA();
	timeDeploymentToGroundA = deploymentAltitudeA / parachute.landingVelocity; return timeDeploymentToGroundA;
}

double Vehicle::calculateTimeOfFlightA() {
	timeOfFlightA = engine.burnTime + timeMECOToAPA + timeAPToDeploymentA + timeDeploymentToGroundA; return timeOfFlightA;
}

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