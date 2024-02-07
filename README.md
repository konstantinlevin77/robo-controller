# Simple Controller For UKit Explore Transformer Robot

We have a robot kit called UKit Explore in our university student club. It's possible to make different kinds of robots out of it and we've made the transformer robot as shown in their [website](https://ide.ubtrobot.com/#/). We're going to use the robot in children activities. Thus we've decided to make a bluetooth controller with arduino to control it.

## TODO LIST ✅
❌ Test the all commands. First test them without the controller (via a mobile phone), then test with the controller.
❌ Implement humidity and temperature sensors
❌ Implement the LED display.

### Controller Logic

* Controller is an arduino uno which have three joystick modules, a push button and a HC06 bluetooth module connected.
* The first joystick module is to control the lower body of the humanoid and the movement of the vehicle.
* The second and the third joystick modules are to control the upper left and right body parts of the humanoid (elbows, arms and shoulders.)
* Joysticks are connected to analog pins and they create two analog values when they are pushed to any direction. X for horizontal movement and Y for vertical movement. Those values are 512 when joysticks are not pushed to any direction. 
* There's also a push button as I mentioned before, it changes the form of the robot (humanoid or vehicle)
* Arduino reads the analog values, compares them with thresholds and creates commands like HUMANOID-FORWARD or VEHICLE-LEFT etc. (A list of all commands is below.) Then those commands are sent through HC06.

### Robot Logic
* The robot's bluetooth module reads commands sent from the controller. Then microcontroller on the robot interprets them with switch cases and apply commands using the library of the robot (ucode.h)
* The robot has a ultrasonic sensor which measures the distance in cm, so if distance is smaller than a threshold, robot doesn't move forward. This only works when the robot is humanoid. 

### Full List of Commands
1. VEHICLE-FORWARD
2. VEHICLE-BACKWARD
3. VEHICLE-LEFT
4. VEHICLE-RIGHT
5. HUMANOID-FORWARD
6. HUMANOID-BACKWARD
7. LEFT-SHOULDER (ANGLE)
8. RIGHT-SHOULDER (ANGLE)
9. LEFT-ARM (ANGLE)
10. RIGHT-ARM (ANGLE)
11. LEFT-ELBOW (ANGLE)
12. RIGHT-ELBOW (ANGLE)
13. VEHIC-TO-HUM
14. HUM-TO-VEHIC

