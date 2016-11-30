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
 * UP: 2/08/11/2016
 * UD: 7/13/11/2016
 * UD: 1/14/11/2016
 * UD: 2/15/11/2016
 * UP: 2/22/11/2016
 * UP: 3/23/11/2016
 * UP: 3/30/11/2016
 * ---------------
 * Dev: Add your name here
 * UP: Date you made changes
 * ---------------
*/

#include "BootControl.h"

BootControl::BootControl(CommControl *cc, VerboseControl *vc, MotorControl *mc, int *pin){
  commControl=cc;
  verboseControl=vc;
  motorControl=mc;
  resetPin=pin;
}
void BootControl::reset(int n){
  if(n>0){
    verboseControl->verboseMsg("System will shut down in "+String(n)+" seconds");
    delay(n*1000);
    verboseControl->verboseMsg("System will now shut down");
  } else{
    verboseControl->verboseMsg("System is going down NOW!");
    verboseControl->verboseMsg("---------------------------------");
    verboseControl->verboseMsg("\r");
  }
  delay(resetDelay);
  pinMode(*resetPin, OUTPUT);
  digitalWrite(*resetPin, HIGH);
}
void BootControl::killReset(){
  pinMode(*resetPin, INPUT); //set the pin as an Input to halt the reset signal
}
void BootControl::btBoot() {
  // Open serial communications:
  commControl->btEnabled=true;
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
  verboseControl->setVerboseLevel(3, 0);
  verboseControl->setVerboseLevel(3, 1);

  verboseControl->verboseMsg("---------------------------------");
  verboseControl->verboseMsg("Serial Communications Established");
  verboseControl->verboseMsg("---------------------------------");
  verboseControl->verboseMsg("CommPort\t|Status\t|Verbose");
  verboseControl->verboseMsg("---------------------------------");
  for (int i = 0; i < MAX_COMMS; i++) {
    verboseControl->verboseMsg("Comm#" + String(i) + "\t\t|" + String(commControl->getCommStatus(i)) + "\t|" + String(verboseControl->verboseEnabled[i]));
  }
  verboseControl->verboseMsg("-----------------------------------");
  killReset();
  verboseControl->verboseMsg("Kill reset signal");
  verboseControl->verboseMsg("---------------------------------");
  verboseControl->verboseMsg("");

  verboseControl->verboseMsg("Initializing System");
  verboseControl->verboseMsg("-------------------");
  verboseControl->verboseMsg("Configuring CommPort Access");
  verboseControl->verboseMsg("-------------------");
  //configure motors pins for each motor
  verboseControl->verboseMsg("Configuring motor pins...");
  verboseControl->verboseMsg("-----------------------------------");
  verboseControl->verboseMsg("Loop#\t|motorPin\t|motorState");
  verboseControl->verboseMsg("-----------------------------------");
  motorControl->motorChangeVerbose = false;
  for (int i = 0; i < MAX_MOTORS; i++) {

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
}
