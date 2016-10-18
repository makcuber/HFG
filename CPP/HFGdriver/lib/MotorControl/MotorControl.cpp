//Motor Control

/*
 * Credit Format
 * ---------------
 * Dev: Your Name Here
 * DC: Date file was originally create on (only if you are the first contributor)
 * UP: Date that you made changes to the file
 *
 * Note - Date format = day of the week/day of the month/month/year
 * Ex: Wednesday, July, 1st, 2014 => 3/01/07/2014
 * ---------------
 * Dev: Jonathan Brunath
 * DC: 6/15/10/2016
 * UP: 1/17/10/2016
 * UP: 2/18/10/2016
 * ---------------
 * Dev: Add your name here
 * UP: Date you made changes
 * ---------------
*/

#include "MotorControl.h"

MotorControl::MotorControl(VerboseControl *vc){
  verboseControl=vc;
  startMotorPin = 22;
  motorChangeVerbose = false;
}

void MotorControl::toggleMotor(int motorID) {
  setMotorState(motorID, !motorState[motorID]);
}
void MotorControl::killAll() {
  motorChangeVerbose = false;
  for (int i = 0; i < maxMotors; i++) {
    setMotorState(i, false);
  }
  verboseControl->verboseMsg("Motor State Change");
  verboseControl->verboseMsg("------------------");
  verboseControl->verboseMsg("MotorPin:" + String(motorPin[0]) + " - " + String(motorPin[maxMotors - 1]));
  verboseControl->verboseMsg("MotorState:" + String(motorState[0]));
  motorChangeVerbose = true;
}
void MotorControl::setMotorState(int motorID, bool state) {
  if (state) {
    motorState[motorID] = true;
    digitalWrite(motorPin[motorID], HIGH);
  } else {
    motorState[motorID] = false;
    digitalWrite(motorPin[motorID], LOW);
  }
  if (motorChangeVerbose) {
    verboseControl->verboseMsg("Motor State Change");
    verboseControl->verboseMsg("------------------");
    verboseControl->verboseMsg("MotorPin:" + String(motorPin[motorID]));
    verboseControl->verboseMsg("MotorState:" + String(motorState[motorID]));
    verboseControl->verboseMsg("\n");
  }
}
