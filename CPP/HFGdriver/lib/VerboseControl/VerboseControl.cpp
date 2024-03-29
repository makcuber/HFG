//VerboseControl

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
 * UD: 4/03/11/2016
 * UP: 2/08/11/2016
 * UD: 1/14/11/2016
 * UD: 2/15/11/2016
 * UD: 3/16/11/2016
 * UD: 1/21/11/2016
 * UP: 2/22/11/2016
 * UP: 3/23/11/2016
 * UP: 3/30/11/2016
 * ---------------
 * Dev: Add your name here
 * UP: Date you made changes
 * ---------------
*/

#include "VerboseControl.h"

//Verbose

VerboseControl::VerboseControl(CommControl *cc){
  commControl=cc;
  if(MAX_COMMS!=maxComms){
    if(MAX_COMMS>maxComms){
      int tmp=MAX_COMMS-maxComms;
      debugMsg("Warning: commControl reports "+String(tmp)+" more commPorts than verboseControl is aware of");
    } else{
      int tmp=maxComms-MAX_COMMS;
      debugMsg("Warning: verboseControl reports "+String(tmp)+" more commPorts than commControl is aware of");
    }

  }
  defaultClearWidth=80;
  for(int i=0;i<MAX_COMMS;i++){
    setVerboseLevel(0, i);
  }
}

void VerboseControl::setVerboseLevel(int level, int comm) {
  if((comm<MAX_COMMS)&(comm>=0)){
    if((level<=maxVerboseLevel)&(level>=0)){
      switch(level){
        case 0:
          setVerbose(false, comm);
          setDebug(false, comm);
          verboseLevel[comm]=level;
          break;
        case 1:
          setVerbose(true, comm);
          setDebug(false, comm);
          verboseLevel[comm]=level;
          break;
        case 2:
          setVerbose(false, comm);
          setDebug(true, comm);
          verboseLevel[comm]=level;
          break;
        case 3:
          setVerbose(true, comm);
          setDebug(true, comm);
          verboseLevel[comm]=level;
          break;
        default:
          break;
      }
    }
  }
}

void VerboseControl::verboseMsg(String msg) {
  for(int i=0;i<MAX_COMMS;i++){
    if (verboseEnabled[i]) {
      commControl->SerialWriteS(i, msg);
    }
  }
}
void VerboseControl::setVerbose(bool state, int comm) {
  if((comm<MAX_COMMS)&(comm>=0)){
    verboseEnabled[comm] = state;
  }
}

//Debug

void VerboseControl::debugMsg(String msg) {
  for(int i=0;i<MAX_COMMS;i++){
    if (debugEnabled[i]) {
      commControl->SerialWriteS(i, msg);
    }
  }
}
void VerboseControl::setDebug(bool state, int comm) {
  if((comm<MAX_COMMS)&(comm>=0)){
    debugEnabled[comm] = state;
  }
}

//CLI

void VerboseControl::clearConsole() {
  verboseMsg(String(defaultClearWidth));
  for (int i = 0; i < defaultClearWidth; i++) {
    verboseMsg("\n");
  }
}
void VerboseControl::showMenu(int m) {
  switch (m) {
    case 0:
      verboseMsg("------------------");
      verboseMsg("Menu");
      verboseMsg("------------------");
      verboseMsg("0 = Show menu");
      verboseMsg("1 = Stop All Motors");
      verboseMsg("2 = Toggle Motor State (int motorId)");
      verboseMsg("3 = Toggle OPC channel verbose");
      verboseMsg("4 = Turn on motor x (int motorId)");
      verboseMsg("5 = Clear");
      verboseMsg("6 = Reset System (int delay)");
      verboseMsg("7 = Toggle all motors");
      verboseMsg("8 = Run OnOff Pattern on GloveMotor (int duration)");
      verboseMsg("9 = Run OnOff Pattern on MotorArrayA (int duration)");
      verboseMsg("10 = Run OnOff Pattern on MotorArrayB (int duration)");
      break;
    default:
      break;
  }
  verboseMsg("------------------");
}
