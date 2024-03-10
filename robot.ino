/*
Copyright 2024 Mehmet Yaşar Tekman

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), 
to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <SoftwareSerial.h>
#include "ucode.h"

/*
IMPORTANT TO DO, DO NOT FORGET TO IMPLEMENT:
TEMP/HUMIDITY SENSOR
LED DISPLAY
*/

#define ULTRA_SONIC_ID 10

// If there's an obstacle closer than DISTANCE_LIMIT, robot won't move forward. Only in vehicle mode.
#define DISTANCE_LIMIT 2

// These are the servo ids of the different compontents.
#define RIGHT_SHOULDER_ID 1
#define LEFT_SHOULDER_ID 4

#define RIGHT_ELBOW_ID 5
#define RIGHT_ARM_ID 6

#define LEFT_ELBOW_ID 2
#define LEFT_ARM_ID 3

// How much microcontroller should wait to let the robot transform, in miliseconds.
#define TRANSFORMATION_DELAY 4000

// Change the RX and TX pins accordingly.
SoftwareSerial BT(10,11);

void setup() {
    Initialization();
    if (protocolRunState == false) {
      BT.begin(9600);
      Serial.begin(9600);
    }
}

void loop() {
    protocol();
    if (protocolRunState == false) {

      delay(2000);

      float distance = readUltrasonicDistance(ULTRA_SONIC_ID);

      if (BT.available()) {
        String cmd = BT.readStringUntil('\n');

        // Remove the last char, which is \n
        cmd.remove(cmd.length() - 1);
        
        int indexOfSpace = cmd.indexOf(' ');
        if (indexOfSpace == -1) {

          Serial.println(cmd);

          if (cmd.equals("VEHICLE-FORWARD") && distance > DISTANCE_LIMIT) {
            // NOC robot acts move forward (vehicle) run times 1 
            Serial.println("ROBOT SHOULD MOVE FORWARD");
            motion_case(9, 1);
          }

          if (cmd.equals("VEHICLE-BACKWARD")) {
            // NOC robot acts move backward (vehicle) run times 1
            Serial.println("ROBOT SHOULD MOVE BACKWARD")
            motion_case(10,1);

          }



          if (cmd.equals("VEHICLE-LEFT")) {
            // NOC robot acts turn left (vehicle) run times 1
            motion_case(11,1);

          }

          if (cmd.equals("VEHICLE-RIGHT")) {
            // NOC robot acts turn right (vehicle) run times 1
            motion_case(12,1);
          }

/*

          if (cmd.equals("HUMANOID-FORWARD")) {
            // NOC robot acts move forward (humanoid) run times 1
            motion_case(1,1);
          }

          if (cmd.equals("HUMANOID-BACKWARD")) {
            // NOC robot acts move backward (humanoid) run times 1
            motion_case(2,1);
          }

          if (cmd.equals("HUM-TO-VEHIC")) {
            // NOC robot acts humanoid to vehicle run times 1
            motion_case(13,1);
            delay(TRANSFORMATION_DELAY);
          }

          if (cmd.equals("VEHIC-TO-HUM")) {
            // NOC robot acts vehicle to humanoid run times 1
            motion_case(0,1);
            delay(TRANSFORMATION_DELAY);
          }
*/

        }
        else {
          String rootCmd = cmd.substring(0,indexOfSpace);
          int angleCmd = cmd.substring(indexOfSpace+1).toInt();

          Serial.print(rootCmd+" ");
          Serial.println(angleCmd);

/*

          if (rootCmd.equals("LEFT-ELBOW")) {
            setServoAngle(LEFT_ELBOW_ID,angleCmd,1000);
          }

          if (rootCmd.equals("RIGHT-ELBOW")) {
            setServoAngle(RIGHT_ELBOW_ID,angleCmd,1000);
          }

          if (rootCmd.equals("LEFT-ARM")) {
            setServoAngle(LEFT_ARM_ID,angleCmd,1000);
          }

          if (rootCmd.equals("RIGHT-ARM")) {
            setServoAngle(RIGHT_ARM_ID,angleCmd,1000);
          }

          if (rootCmd.equals("LEFT-SHOULDER")) {
            setServoAngle(LEFT_SHOULDER_ID,angleCmd,1000);
          }

          if (rootCmd.equals("RIGHT-SHOULDER")) {
            setServoAngle(RIGHT_SHOULDER_ID,angleCmd,1000);
          }

*/

        }

      }

    }
}