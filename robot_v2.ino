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

#define B 12

// These are the frequencies of the notes 
#define C4 261.626
#define D4 293.665
#define E4 329.628
#define F4 349.228
#define G4 391.995
#define GSharp4 415.305 
#define a4 440
#define B4 493.883
#define C5 523.251
#define D5 587.33

// This determines how many miliseconds a quarter note sounds
#define QUARTER_DUR 300

const float EIGHTH_DUR = QUARTER_DUR / 2;
const float HALF_DUR = QUARTER_DUR * 2;
const float WHOLE_DUR = QUARTER_DUR * 4;

#define ULTRA_SONIC_ID 10

// If there's an obstacle closer than DISTANCE_LIMIT, robot won't move forward. Only in vehicle mode.
#define DISTANCE_LIMIT 2000000

// These are the servo ids of the different compontents.
#define RIGHT_SHOULDER_ID 1
#define LEFT_SHOULDER_ID 4

#define RIGHT_ELBOW_ID 5
#define RIGHT_ARM_ID 6

#define LEFT_ELBOW_ID 2
#define LEFT_ARM_ID 3

// How much a component should move when it takes a command.
#define MOVEMENT_ANGLE 15

// How much microcontroller should wait to let the robot transform, in miliseconds.
#define TRANSFORMATION_DELAY 4000


#define SERVO_MOVEMENT_DURATION 150

// Change the RX and TX pins accordingly.
SoftwareSerial BT(10,11);

bool leftShoulderKeepGoingDown = false;
bool rightShoulderKeepGoingDown = false;

void setup() {
    Initialization();
    if (protocolRunState == false) {
      BT.begin(9600);
      Serial.begin(9600);
      pinMode(B, OUTPUT);

    }
}

void playNote(String note, int noteValue) {
  
  float freq;
  float dur;
  
  if (note.equals("C4")) {freq = C4;}
  else if (note.equals("D4")) {freq = D4;}
  else if (note.equals("E4")) {freq = E4;}
  else if (note.equals("F4")) {freq = F4;}
  else if (note.equals("G4")) {freq = G4;}
  else if (note.equals("GSharp4")) {freq = GSharp4;}
  else if (note.equals("A4")) {freq = a4;}
  else if (note.equals("B4")) {freq = B4;}
  else if (note.equals("C5")) {freq = C5;}
  else if (note.equals("D5")) {freq = D5;} 
  
  if (noteValue == 4) {dur = QUARTER_DUR;}
  else if (noteValue == 8) {dur = EIGHTH_DUR;}
  else if (noteValue == 2) {dur = HALF_DUR;}
  else if (noteValue == 1) {dur = WHOLE_DUR;}
  else if (noteValue == 84) {dur = QUARTER_DUR + EIGHTH_DUR;}
  else if (noteValue == 42) {dur = QUARTER_DUR + HALF_DUR;}
  else if (noteValue == 82) {dur = EIGHTH_DUR + HALF_DUR;}
  
  tone(B,freq);
  delay(dur);
  noTone(B);
  delay(100);
  
}

void loop() {


  String notes[] = {
     
                    "A4","C5","B4","C5","A4",
                    "C5","B4","C5",
                    "A4","C5","C5","B4","C5","B4","C5",
                    "D5","C5","D5","C5","C5","B4",
                    "B4","B4","A4","B4","GSharp4",
                    "B4","A4","B4",
                    "B4","B4","A4","B4",
                    "A4","B4",
                    "C5","B4","C5","B4","B4","A4",  
    
                    "E4","E4","D4","C4",
                    "D4","E4","F4","E4","D4","C4",
                    "F4","F4","E4","D4","E4",
                    "F4","F4","F4","G4","F4","D4",
                    "E4","E4","D4","C4",
                    "E4","E4","E4","D4","E4",

                    "E4","E4","D4","C4",
                    "D4","E4","F4","E4","D4","C4",
                    "F4","F4","E4","D4","E4",
                    "F4","F4","F4","G4","F4","D4",
                    "E4","E4","D4","C4",
                    "E4","E4","E4","D4","E4",

                   	"A4","C5","B4","C5","A4",
                    "C5","B4","C5",
                    "A4","C5","C5","B4","C5","B4","C5",
                    "D5","C5","D5","C5","C5","B4",
                    "B4","B4","A4","B4","GSharp4",
                    "B4","A4","B4",
                    "B4","B4","A4","B4",
                    "A4","B4",
                    "C5","B4","C5","B4","B4","A4",

                    "A4","C5","B4","C5","A4",
                    "C5","B4","C5",
                    "A4","C5","C5","B4","C5","B4","C5",
                    "D5","C5","D5","C5","C5","B4",
                    "B4","B4","A4","B4","GSharp4",
                    "B4","A4","B4",
                    "B4","B4","A4","B4",
                    "A4","B4",
                    "C5","B4","C5","B4","B4","A4",        
                   };
  int durations[] = {

                     8,4,8,4,4,
                     4,8,42,              
                     8,8,8,8,4,8,8,
                     4,8,4,8,8,8,
                     8,8,8,4,4,
                     4,8,82,
                     8,8,8,4,
                     8,8,
                     4,8,4,8,8,8,
    
    
                     8,8,8,84,
                     8,4,8,4,8,4,  
                     8,8,8,84,8,
                     4,8,4,8,8,8,
                     8,8,8,82,
                     4,4,4,4,1,

                     8,8,8,84,
                     8,4,8,4,8,4,
                     8,8,8,84,8,
                     4,8,4,8,8,8,
                     8,8,8,82,
                     4,4,4,4,1,

                     8,4,8,4,4,
                     4,8,42,              
                     8,8,8,8,4,8,8,
                     4,8,4,8,8,8,
                     8,8,8,4,4,
                     4,8,82,
                     8,8,8,4,
                     8,8,
                     4,8,4,8,8,8,

                     8,4,8,4,4,
                     4,8,42,
                     8,8,8,8,4,8,8,
                     4,8,4,8,8,8,
                     8,8,8,4,4,
                     4,8,82,
                     8,8,8,4,
                     8,8,
                     4,8,4,8,8,8,
                    };

  int numberOfNotes = sizeof(durations) / sizeof(durations[0]);


    protocol();
    if (protocolRunState == false) {

      button1.Update();
      if(button1.clicks == 1) {
        for (int i=0;i<numberOfNotes;i++) {
          playNote(notes[i],durations[i]);
        }
      }

      float distance = readUltrasonicDistance(ULTRA_SONIC_ID);

      if (BT.available()) {
        String cmd = BT.readStringUntil('\n');
        
        int indexOfSpace = cmd.indexOf(' ');
        if (indexOfSpace == -1) {

          Serial.println(cmd);

          if (cmd.equals("VEHICLE-FORWARD") /*&& distance > DISTANCE_LIMIT*/) {
            // NOC robot acts move forward (vehicle) run times 1 
            Serial.println("ROBOT SHOULD MOVE FORWARD");
            motion_case(9, 1);
          }

          if (cmd.equals("VEHICLE-BACKWARD")) {
            // NOC robot acts move backward (vehicle) run times 1
            Serial.println("ROBOT SHOULD MOVE BACKWARD");
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

        }
        else {
          String rootCmd = cmd.substring(0,indexOfSpace);


          int isHigh = 1;
          String movementType = cmd.substring(indexOfSpace+1);
          if (movementType.equals("L")) {
            isHigh = -1;
          }

          Serial.print(rootCmd+" ");
          Serial.println(movementType);

          if (rootCmd.equals("LEFT-ELBOW")) {

            int currentAngle = readServoAngleNPD(LEFT_ELBOW_ID);
            Serial.println("Current angle of left elbow: "+ String(currentAngle));
            int desiredAngle = currentAngle + isHigh * MOVEMENT_ANGLE;
            Serial.println("Angle will be changed as: "+String(desiredAngle));
            setServoAngle(LEFT_ELBOW_ID,desiredAngle,SERVO_MOVEMENT_DURATION);
          }

          if (rootCmd.equals("RIGHT-ELBOW")) {

            int currentAngle = readServoAngleNPD(RIGHT_ELBOW_ID);
            int desiredAngle = currentAngle + isHigh * MOVEMENT_ANGLE;
            setServoAngle(RIGHT_ELBOW_ID,desiredAngle,SERVO_MOVEMENT_DURATION);

          }

          if (rootCmd.equals("LEFT-ARM")) {

            int currentAngle = readServoAngleNPD(LEFT_ARM_ID);
            int desiredAngle = currentAngle + isHigh * MOVEMENT_ANGLE;
            setServoAngle(LEFT_ARM_ID,desiredAngle,SERVO_MOVEMENT_DURATION);

          }

          if (rootCmd.equals("RIGHT-ARM")) {

            int currentAngle = readServoAngleNPD(RIGHT_ARM_ID);
            int desiredAngle = currentAngle + isHigh * MOVEMENT_ANGLE;
            setServoAngle(RIGHT_ARM_ID,desiredAngle,SERVO_MOVEMENT_DURATION);

          }

          if (rootCmd.equals("LEFT-SHOULDER")) {

            int currentAngle = readServoAngleNPD(LEFT_SHOULDER_ID);

            if (currentAngle >= 100) {
              leftShoulderKeepGoingDown = true;
              isHigh = -1;
            }

            if (leftShoulderKeepGoingDown) {
              isHigh = -1;
            }

            if (currentAngle <= -100) {
              leftShoulderKeepGoingDown = false;
              isHigh = 1;
            }
          

            int desiredAngle = currentAngle + isHigh * MOVEMENT_ANGLE;
            setServoAngle(LEFT_SHOULDER_ID,desiredAngle,SERVO_MOVEMENT_DURATION);


          }

          if (rootCmd.equals("RIGHT-SHOULDER")) {

            int currentAngle = readServoAngleNPD(RIGHT_SHOULDER_ID);

            if (currentAngle >= 100) {
              rightShoulderKeepGoingDown = true;
              isHigh = -1;
            }

            if (rightShoulderKeepGoingDown) {
              isHigh = -1;
            }

            if (currentAngle <= -100) {
              rightShoulderKeepGoingDown = false;
              isHigh = 1;
            }

            int desiredAngle = currentAngle + isHigh * MOVEMENT_ANGLE;
            setServoAngle(RIGHT_SHOULDER_ID,desiredAngle,SERVO_MOVEMENT_DURATION);


        }

        }

      }

    }
}