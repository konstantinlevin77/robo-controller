#include <SoftwareSerial.h>
#include "ucode.h"

// Change the RX and TX pins accordingly.
SoftwareSerial BT(10,11);

void setup() {
    Initialization();
    if (protocolRunState == false) {
      BT.begin(9600);
    }
}

void loop() {
    protocol();
    if (protocolRunState == false) {


    if (BT.available()) {
      String cmd = BT.readStringUntil('\n');

      // Remove the last char, which is \n
      cmd.remove(cmd.length() - 1);
      
      int indexOfSpace = cmd.indexOf(' ');
      if (indexOfSpace == -1) {
        
        // PUT SWITCH CASES HERE
        switch (cmd) {

          case "VEHICLE-FORWARD":
            // NOC robot acts move forward (vehicle) run times 1 
            motion_case(9, 1);
            break;
          
          case "VEHICLE-BACKWARD":
            // NOC robot acts move backward (vehicle) run times 1
            motion_case(10,1);
            break;

          case "VEHICLE-LEFT":
            // NOC robot acts turn left (vehicle) run times 1
            motion_case(11,1);
            break;

          case "VEHICLE-RIGHT":
            // NOC robot acts turn right (vehicle) run times 1
            motion_case(12,1);
            break;
          
          case "HUMANOID-FORWARD":
            // NOC robot acts move forward (humanoid) run times 1
            motion_case(1,1);
            break;

          case "HUMANOID-BACKWARD":
            // NOC robot acts move backward (humanoid) run times 1
            motion_case(2,1);
            break;
          
          case "HUM-TO-VEHIC":
            // NOC robot acts humanoid to vehicle run times 1
            motion_case(13,1);
            break;
          
          case "VEHIC-TO-HUM":
            // NOC robot acts vehicle to humanoid run times 1
            motion_case(0,1);
            break;
        }

      }
      else {
        String rootCmd = cmd.substring(0,indexOfSpace);
        int angleCmd = cmd.substring(indexOfSpace).toInt();

        // PUT SWITCH CASES HERE
        switch (rootCmd) {
          case "LEFT-ELBOW":
            break;
          
          case "RIGHT-ELBOW":
            break;

          case "LEFT-ARM":
            break;

          case "RIGHT-ARM":
            break;

          case "LEFT-SHOULDER":
            break;
          
          case "RIGHT-SHOULDER":
            break;
        }


      }

    }

    }
}


/*

LIST OF COMMANDS 


LEFT-ELBOW (ANGLE)
RIGHT-ELBOW (ANGLE)

LEFT-ARM (ANGLE)
RIGHT-ARM (ANGLE)

LEFT-SHOULDER (ANGLE)
RIGHT-SHOULDER (ANGLE)

HUM-TO-VEHIC
VEHIC-TO-HUM

*/
