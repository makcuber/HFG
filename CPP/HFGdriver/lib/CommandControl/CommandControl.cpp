//CommandContol

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

#include "CommandControl.h"

//Command Processing

CommandControl::CommandControl(CommControl *cc, VerboseControl *vc, MotorControl *mc, BootControl *bc){
  commControl=cc;
  verboseControl=vc;
  motorControl=mc;
  bootControl=bc;

  mode = 1;

  btMode = 0;
  usbMode = 0;
}

void CommandControl::cmdSort(int mode, String cmdS, String valS) {
  switch (mode) {
    case 0:
      //verboseControl->verboseMsg("commMode#0");
      usbcmd(cmdS, valS);
      break;
    case 1:
      //verboseControl->verboseMsg("commMode#1");
      btcmd(cmdS, valS);
      break;
    case 2:
      //verboseControl->verboseMsg("commMode#2");
      break;
    case 3:
      //verboseControl->verboseMsg("commMode#3");
      break;
    case 4:
      //verboseControl->verboseMsg("commMode#4");
      break;
    case 5:
      //verboseControl->verboseMsg("commMode#5");
      break;
    default:
      //WARNING: code placed here will run on every cycle that you dont send a command
      break;
  }
}
void CommandControl::btComm() {
  String cmdS,valS;
  while (Serial1.available()) {
    cmdS = Serial1.readStringUntil(',');
    valS = Serial1.readStringUntil('\n');
  }

  cmdSort(btMode, cmdS, valS);

  //reset the cmd and val variables for the next cycle
  //cmdS = "-1";
  //valS = "-1";
}
void CommandControl::btcmd(String cmdS, String valS) {
  int cmd = cmdS.toInt();
  //int val = valS.toInt();
  switch (cmd) {
    case 0:
     verboseControl->verboseMsg("BT cmd#0");
     verboseControl->showMenu(btMode);
      break;
    case 1:
     verboseControl->verboseMsg("BT cmd#1");
      break;
    case 2:
     verboseControl->verboseMsg("BT cmd#2");
      break;
    case 3:
     verboseControl->verboseMsg("BT cmd#3");
      break;
    case 4:
     verboseControl->verboseMsg("BT cmd#4");
      break;
    case 5:
     verboseControl->verboseMsg("BT cmd#5");
      break;
    default:
      //WARNING: code placed here will run on every cycle that you dont send a command
      if (verboseControl->verboseEnabled[1]) {

      }
      break;
  }
}
void CommandControl::usbComm() {
  String cmdS,valS;
  while (Serial.available()) {
    cmdS = Serial.readStringUntil(',');
    valS = Serial.readStringUntil('\n');
  }

  cmdSort(usbMode, cmdS, valS);

  //reset the cmd and val variables for the next cycle
  //cmdS = "-1";
  //valS = "-1";
}
void CommandControl::usbcmd(String cmdS, String valS) {
  int cmd = cmdS.toInt();
  int val = valS.toInt();
  switch (cmd) {
    case 0:
      verboseControl->verboseMsg("USB cmd#0");
      verboseControl->showMenu(usbMode);
      break;
    case 1:
     verboseControl->verboseMsg("USB cmd#1");
      motorControl->killAll();
      break;
    case 2:
     verboseControl->verboseMsg("USB cmd#2");
      motorControl->toggleMotor(0);
      break;
    case 3:
     verboseControl->verboseMsg("USB cmd#3");
     verboseControl->setVerbose(true,1);
      break;
    case 4:
     verboseControl->verboseMsg("USB cmd#4");
     motorControl->setMotorState(val, true);
      break;
    case 5:
      verboseControl->verboseMsg("USB cmd#5");
      verboseControl->clearConsole();
      break;
    case 6:
      verboseControl->verboseMsg("USB cmd#6");
      bootControl->boot();
      break;
    case 7:
      verboseControl->verboseMsg("USB cmd#7");
      //bluetoothWrite(valS);
      break;

    default:
      //WARNING: code placed here will run on every cycle that you dont send a command
      break;
  }
}