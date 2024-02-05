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

#define MOVEMENT_CTRL_VERT A0
#define MOVEMENT_CTRL_HORZ A1

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
#define L_MOV_THRESHOLD 400
#define R_MOV_THRESHOLD 800
#define F_MOV_THRESHOLD 800
#define B_MOV_THRESHOLD 400

bool isHumanoid = true;

String determineMovementVert(int movY) {

  
  String cmdY = "";

  if (movY <= B_MOV_THRESHOLD && !isHumanoid) {
    cmdY = "VEHICLE-BACKWARD";
  }

  else if (movY >= F_MOV_THRESHOLD && !isHumanoid) {
    cmdY = "VEHICLE-FORWARD";
  }

  else if (movY <= B_MOV_THRESHOLD && isHumanoid) {
    cmdY = "HUMANOID-BACKWARD";
  }

  else if (movY >= F_MOV_THRESHOLD && isHumanoid) {
    cmdY = "HUMANOID-FORWARD";
  }

  return cmdY;

}

String determineMovementHorz(int movX) {

  String cmdX = "";

  if (movX <= L_MOV_THRESHOLD  && !isHumanoid) {
    cmdX = "VEHICLE-LEFT";
  }

  else if (movX >= R_MOV_THRESHOLD && !isHumanoid) {
    cmdX = "VEHICLE-RIGHT";
  }

  // There's no need to add another condition for humanoid, it'll return "" as it should be. (Humanoid can't move to the left or to the right.)

  return cmdX;

}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Started!");

}

void loop() {
  

  int movX = analogRead(MOVEMENT_CTRL_HORZ);
  int movY = analogRead(MOVEMENT_CTRL_VERT);


  String horzCmd = determineMovementHorz(movX);
  String vertCmd = determineMovementVert(movY);

  Serial.println(horzCmd);
  Serial.println(vertCmd);

  delay(2000);


 

  



}
