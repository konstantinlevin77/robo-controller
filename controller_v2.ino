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

#define MOVEMENT_CTRL_VERT A0
#define MOVEMENT_CTRL_HORZ A1


// For the arms vertical values will be for elbows
// horizontal values will be for arms and button will move the shoulder.
#define LEFT_CTRL_VERT A2
#define LEFT_CTRL_HORZ A3
#define LEFT_CTRL_BUT 2

#define RIGHT_CTRL_VERT A4
#define RIGHT_CTRL_HORZ A5
#define RIGHT_CTRL_BUT 3

#define HUM_TO_VEHIC_BUT 4

/*
When the joystick is at the center, it returns 512 both for horizontal and vertical axes. When you push it to the left
or to the down, the value gets smaller. When you push it to the right or to the up, the value gets bigger.
These are the threshold values in order to determine in which directions the controller is pushed to.
*/
#define L_THRESHOLD 400
#define H_THRESHOLD 600

bool isHumanoid = true;

SoftwareSerial BT(11, 10); // RX, TX

String determineMovementVert(int movY) {

  String cmdY = "";

  if (movY <= L_THRESHOLD && !isHumanoid) {
    cmdY = "VEHICLE-BACKWARD";
  }

  else if (movY >= H_THRESHOLD && !isHumanoid) {
    cmdY = "VEHICLE-FORWARD";
  }

  else if (movY <= L_THRESHOLD && isHumanoid) {
    cmdY = "HUMANOID-BACKWARD";
  }

  else if (movY >= H_THRESHOLD && isHumanoid) {
    cmdY = "HUMANOID-FORWARD";
  }

  return cmdY;

}

String determineMovementHorz(int movX) {

  String cmdX = "";

  if (movX <= L_THRESHOLD  && !isHumanoid) {
    cmdX = "VEHICLE-LEFT";
  }

  else if (movX >= H_THRESHOLD && !isHumanoid) {
    cmdX = "VEHICLE-RIGHT";
  }

  // There's no need to add another condition for humanoid, it'll return "" as it should be. (Humanoid can't move to the left or to the right.)

  return cmdX;

}

String determineElbowMovement(String elbow, int ctrlY) {

    String cmd = "";
    if ((ctrlY < L_THRESHOLD) && isHumanoid) {
        cmd = elbow+" L";
    }
    if ((ctrlY > H_THRESHOLD) && isHumanoid) {
        cmd = elbow+" H";
    }

    return cmd;
}

String determineArmMovement(String arm, int ctrlX) {

    String cmd = "";
    if ((ctrlX < L_THRESHOLD) && isHumanoid) {
        cmd = arm+" L";
    }
    if ((ctrlX > H_THRESHOLD) && isHumanoid) {
        cmd = arm+" H";
    }

    return cmd;
}

String determineShoulderMovement(bool isLeftShoulder, int ctrlBut) {

    // TODO: Needs to be implemented.
    String cmd = "";
    return cmd;
}

void sendString(String message) {
  int messageLength = message.length();
  for (int i = 0; i < messageLength; i++) {
    BT.write(message[i]);
  }
  BT.write('\n');
}

void setup() {

  pinMode(LEFT_CTRL_BUT,INPUT);
  pinMode(RIGHT_CTRL_BUT,INPUT);
  pinMode(HUM_TO_VEHIC_BUT,INPUT);

  digitalWrite(LEFT_CTRL_BUT,HIGH);
  digitalWrite(RIGHT_CTRL_BUT,HIGH);

  Serial.begin(9600);
  BT.begin(9600);
  Serial.println("Controller has started!");

}

void loop() {

  delay(300);

  String transformCmd = "";

  /*
  if (digitalRead(HUM_TO_VEHIC_BUT)) {
    if (isHumanoid) {
      transformCmd = "HUM-TO-VEHIC";
    }
    else {
      transformCmd = "VEHIC-TO-HUM";
    }
    isHumanoid = !isHumanoid;
  }
  */
  
  int movX = analogRead(MOVEMENT_CTRL_HORZ);
  int movY = analogRead(MOVEMENT_CTRL_VERT);

  String horzCmd = determineMovementHorz(movX);
  String vertCmd = determineMovementVert(movY);

  int leftCtrlX = analogRead(LEFT_CTRL_HORZ);
  int leftCtrlY = analogRead(LEFT_CTRL_VERT);


  String leftArmCmd = determineArmMovement("LEFT",leftCtrlX);
  String leftElbowCmd = determineElbowMovement("LEFT",leftCtrlY);

  int rightCtrlX = analogRead(RIGHT_CTRL_HORZ);
  int rightCtrlY = analogRead(RIGHT_CTRL_VERT);


  String rightArmCmd = determineArmMovement("RIGHT",rightCtrlX);
  String rightElbowCmd = determineElbowMovement("RIGHT",rightCtrlY);

  int leftCtrlBut = digitalRead(LEFT_CTRL_BUT);
  int rightCtrlBut = digitalRead(RIGHT_CTRL_BUT);

  bool isLeft = true;

  String leftShoulderCmd = determineShoulderMovement(isLeft,leftCtrlBut);

  isLeft = false;

  String rightShoulderCmd = determineShoulderMovement(isLeft,rightCtrlBut);

  
  if (!horzCmd.equals("")) {
    sendString(horzCmd);
  }

  if (!vertCmd.equals("")) {
    sendString(vertCmd);
  }

  if (!leftArmCmd.equals("")) {
    sendString(leftArmCmd);
  }

  if (!leftElbowCmd.equals("")) {
    sendString(leftElbowCmd);
  }

  if (!leftShoulderCmd.equals("")) {
    sendString(leftShoulderCmd);
  }

  if (!rightShoulderCmd.equals("")) {
    sendString(rightShoulderCmd);
  }

  if (!rightArmCmd.equals("")) {
    sendString(rightArmCmd);
  }

  if (!rightElbowCmd.equals("")) {
    sendString(rightElbowCmd);
  }

  if (!transformCmd.equals("")) {
    sendString(transformCmd);
  }


}
