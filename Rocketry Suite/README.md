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
  
	set parachute - Sets the parameters of the vehicle's parachute.
  
	.set angle - Manually sets the launch angle of the vehicle.
  
	.display vehicle - Displays the current launch vehicle.
  
	.display conditions - Displays the current weather conditions.
  
	.display parachute - Displays the current parachute configuration.
  
	.display angle - Displays the current launch angle.
  
	.calculate parachute diameter - Uses the current parachute configuration to determine optimal diameter.
  
	.calculate parachute velocity - Uses the current parachute configuration to determine landing velocity.
  
	.calculate angle - Sets the launch angle to what will return the rocket to the launchsite.
  
	.update - Can be used to change a single value of a class.
  
	.credits - Shows the credits for the program.
  
	.exit - Closes the program.

### **About**
Written in C++.
See code folder for details.
