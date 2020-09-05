# autotopoffsystem

This Auto Top Off (ATO) system is designed to use an Arduino, optical water sensor, and small pump to top off evaporated water in an aquarium in order to maintain a constant water level to help keep water parameters stable in the system.

The pump turns on when the water level drops below the optical sensor, drawing water from a reservoir and into the aquarium through airline tubing. The pump shuts off when the sensor is submerged.

Note: only use on a system that has an emergency drain installed

Current features
* On/Off switch to disable the ATO
* Timeout to prevent flooding
* LED to indicate timeout
* LED to indicate pumping water
* Optical water sensor (rather than float valve)

Future features
* 2 optical sensors
* Better pump/motor
* Text alert when system fails
* Convert to Raspberry Pi to create entire aquarium controller (pH, temp, light schedules, enable/disable equipment, web interface, data/graphs, etc)

Components
* Optical water sensor
* MOSFET (IRFZ44N)
* Resisters
* 12V DC dosing pump
* Switch
* LEDs (x2)
* Solid single core wire (22AWG)
* Power supply (12V 2A) & DC connector
* Airline tubing
