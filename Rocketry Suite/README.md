Designed to allow easy calculation of model rocketry related equations. 
Currently calculates the total burn-time, altitude achieved during the boost phase, height gained during the coast phase, the maximum altitude, and the maximum velocity.
Accepts a variety of configurable variables for the launch vehicle as well as current temperature and pressure.

### **Installation and Use**
**PLEASE NOTE THAT INSTALLATION OF THIS PROGRAM IS OPTIONAL**
*While the standalone executable should work, if it doesn't, or if you would like an "installed" program version on your computer, go through the INSTALLATION process. Otherwise, if you would just like a standalone executable to run the program as you please, see the STANDALONE process.*

**STANDALONE PROCESS**
Download the standalone executable in the "Standalone" folder.
Place it wherever is convenient.
Double click to run.

**INSTALLATION PROCESS**
Download the "Setup" folder.
Run setup.exe.
Rocketry Suite will now be installed under whichever directory was selected during installation (by default this is "C:\Program File(x86)\Mit Bailey\Rocketry Suite".
Navigate to the install directory and run RocketrySuite.exe or search for it in the Start menu.

### **Commands**

	.help - Display available commands and what they do.
  
	.help units - Display required units.
  
	.help <command> - Display detailed information about that command.
  
  	.run - Run the simulation given the current launch vehicle configuration and weather conditions.
  
	.set vehicle - Creates a new launch vehicle with the relevant parameters.
  
	.set conditions - Creates a new set of weather conditions.
  
	.set parachute - Sets the parameters of the vehicle's parachute.
  
	.set angle - Manually sets the launch angle of the vehicle.
  
	.display vehicle - Displays the current launch vehicle.
  
	.display conditions - Displays the current weather conditions.
  
	.display parachute - Displays the current parachute configuration.
  
	.display angle - Displays the current launch angle.
  
	.calculate parachute diameter - Uses the current parachute configuration to determine optimal diameter.
  
	.calculate parachute velocity - Uses the current parachute configuration to determine landing velocity.
  
	.calculate angle - Sets the launch angle to what will return the rocket to the launchsite.
	
	.calculate area - Displays the area of a circle with the given diameter.
  
	.update - Can be used to change a single value of a class.
  
	.credits - Shows the credits for the program.
  
	.exit - Closes the program.

### **About**
Written in C++.
See code folder for details.

### **Changelog**
Version 2 Update 1  
	Added Features  
	- Provided area of a circle calculator.  
	- Updaters to update all of the values of a particular thing at once, example: .update engine <val> <val> <val>  
	- Added warnings to alert user of strange or dangerous results.
	Fixed Bugs  
	- Double print of average mass in current configuration.  
	- Doesn't correctly calculate deployment altitude.  
	- Update parachute command was using the penultimate argument, instead of the final argument, for the value, resulting in the program crashing. i.e. it would use 	"deploymentTime" instead of "7" when running the command .update parachute deploymentTime 7  
	- Times for deployment-to-ground and total aloft displaying negative values.  
	- Range and Drift values can be ridiculously close to zero (e-16), or negative zero. Should just round at that point.  
	- Should detect if the parachute will deploy before reaching apogee (see warnings).  
	- Always displays N/A for apogee to ground w/o parachute time.  
	- Should be .update engine propellant <val> not .update engine mass empty <val>    
	
Version 2  
	- Incorporates manual launch angle specification and adjusts all calculations accordingly.  
	- Added calculation to find range (change in position from launchsite to parachute deployment).  
	- Added parachute deployment value in mission elapsed time.  
	- Added calculation to find drift (distance traveled after parachute deployment due to wind).  
	- Added windspeed value to conditions.  
	- Added appropriate commands to allow user interaction with new features.  
	- Refactored code.  

Version 1 Update 1  
	- Added parachute class.  
	- Program now calculates time to reach the ground after the parachute deploys (assuming deployment is at apoapsis).  
	- Added parachute related set and display commands.  

Version 1  
	- Initial commit.  
	- Accurately predicts the trajectory of a model rocket given appropriate inputs assuming launch angle is equal to 90' and a windless environment.  
	- Allows user to set custom conditions and launch vehicle.  
	- Displays velocity, time, and altitude values when the simulation is run.  
