#include <Servo.h>

// servo objects to steer both servos
Servo servoH, servoV; 

// values of the 4 LDRs
int topleft;   // pin A0
int topright;  // pin A1
int downleft;  // pin A2
int downright; // pin A3

// pins of the 2 servos
int pinHServo = 9; // pin 9
int pinVServo = 10;// pin 10

// position (in degrees) of the servo
int posHServo = 90;
int posVServo = 90;

// reaction speed (in ms) - lower means faster
int waittime = 10;

// determines minimal threshold 
// to detect difference in light
int diffThresh = 40;

// only move servos when sufficient light
// i.e. LDR value below lightThreshold 
// normal value is 500
int lightThreshold = 500; 

void setup() {
  // connect servos to pins
  servoH.attach(pinHServo);
  servoV.attach(pinVServo);
  
  // put servos in neutral position
  servoH.write(posHServo);
  servoV.write(posVServo);
  
  // open serial channel
  Serial.begin(9600);
}

void loop() {
  // read LDR values (between O and 1024)
  // higher value means darker enviroment
  // value below 500 indicate bright light
  topleft = analogRead(A0);
  topright = analogRead(A1);
  downleft = analogRead(A2);
  downright = analogRead(A3);

  // print LDR values
  Serial.print("TL ");
  Serial.print(topleft);
  Serial.print("/ TR ");
  Serial.print(topright);
  Serial.print("/ DL ");
  Serial.print(downleft);
  Serial.print("/ DR ");
  Serial.println(downright);

  // compare the LDR values and determine
  // whether servo should adjust
  // when too dark, don't move the servo's
  if ((topleft > lightThreshold) && (topright > lightThreshold) && (downleft > lightThreshold) && (downright > lightThreshold)) {
    Serial.println("no direct light");
    delay(waittime);
  } else {
    // check if horizontal movement is needed 
    if (topleft > topright + diffThresh) {
      posHServo++;
      delay(waittime);
    }
    if (downleft > downright + diffThresh) {
      posHServo++;
      delay(waittime);
    }
    if (topleft < topright - diffThresh) {
      posHServo--;
      delay(waittime);
    }
    if (downleft < downright - diffThresh) {
      posHServo--;
      delay(waittime);
    }

    // constrain servo angle between 0 and 180 degrees
    if (posHServo > 180) {
      posHServo = 180;
    }
    if (posHServo < 0) {
      posHServo = 0;
    }
    
    // check if vertical movement is needed 
    if (topleft > downleft + diffThresh) {
      posVServo--;
      delay(waittime);
    }
    if (topright > downright + diffThresh) {
      posVServo--;
      delay(waittime);
    }
    if (topleft < downleft - diffThresh) {
      posVServo++;
      delay(waittime);
    }
    if (topright < downright - diffThresh) {
      posVServo++;
      delay(waittime);
    }

    // constrain servo angle between 0 and 180 degrees
    if (posVServo > 180) {
      posVServo = 180;
    }
    if (posVServo < 0) {
      posVServo = 0;
    }
  }
  // reposition servoc
  servoH.write(posHServo);
  servoV.write(posVServo);
  
  // print new servo angle
  Serial.print("H ");
  Serial.print(posHServo);
  Serial.print(" / V ");
  Serial.println(posVServo);
}



