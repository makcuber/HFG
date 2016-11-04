//BootControl

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
 * UD: 3/02/11/2016
 * UD: 4/03/11/2016
 * ---------------
 * Dev: Add your name here
 * UP: Date you made changes
 * ---------------
*/

#include "BootControl.h"

BootControl::BootControl(CommControl *cc, VerboseControl *vc, MotorControl *mc){
  commControl=cc;
  verboseControl=vc;
  motorControl=mc;
}

void BootControl::btBoot() {
  // Open serial communications:
  Serial.begin(9600);
  Serial.println("Type AT commands!");

  // The HC-06 defaults to 9600 according to the datasheet.
  Serial1.begin(9600);

}
void BootControl::boot() {
  //put your setup code here, to run once:

  //enable serial communications
  commControl->setAllCommBaud(9600);
  commControl->connectComm(0);
  commControl->connectComm(1);

  //set comm port states

  verboseControl->verboseEnabled[0] = false;
  verboseControl->verboseEnabled[1] = true;

  verboseControl->verboseMsg("Serial Communications Established");
  verboseControl->verboseMsg("---------------------------------");
  verboseControl->verboseMsg("CommPort\t|Status\t|Verbose");
  verboseControl->verboseMsg("---------------------------------");
  for (int i = 0; i < commControl->maxComms; i++) {
    verboseControl->verboseMsg("Comm#" + String(i) + "\t\t|" + String(commControl->commState[i]) + "\t|" + String(verboseControl->verboseEnabled[i]));
  }
  verboseControl->verboseMsg("---------------------------------");
  verboseControl->verboseMsg("");

  verboseControl->verboseMsg("Initializing System");
  verboseControl->verboseMsg("-------------------");

  //configure motors pins for each motor
  verboseControl->verboseMsg("Configuring motor pins...");
  verboseControl->verboseMsg("-----------------------------------");
  verboseControl->verboseMsg("Loop#\t|motorPin\t|motorState");
  verboseControl->verboseMsg("-----------------------------------");
  motorControl->motorChangeVerbose = false;
  for (int i = 0; i < motorControl->maxMotors; i++) {

    //set motor pin number
    motorControl->motorPin[i] = motorControl->startMotorPin + i;

    //set pinmode for pin
    pinMode(motorControl->motorPin[i], OUTPUT);

    //set starting motor state
    motorControl->setMotorState(i, false);

    verboseControl->verboseMsg(String(i) + "\t|" + String(motorControl->motorPin[i]) + "\t\t|" + String(motorControl->motorState[i]));
  }
  verboseControl->verboseMsg("-----------------------------------");
  motorControl->motorChangeVerbose = true;
  verboseControl->verboseMsg("Initialization COMPLETE\n");

  //clusterfuck();
}
