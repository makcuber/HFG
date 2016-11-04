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
 * ---------------
 * Dev: Add your name here
 * UP: Date you made changes
 * ---------------
*/

#include "VerboseControl.h"

//Verbose

VerboseControl::VerboseControl(CommControl *cc){
  commControl=cc;
  defaultClearWidth=80;
}

void VerboseControl::verboseMsg(String msg) {
  for(int i=0;i<commControl->maxComms;i++){
    if (verboseEnabled[i]) {
      commControl->SerialWriteS(i, msg);
    }
  }
}
void VerboseControl::setVerbose(bool state, int comm) {
  if((comm<commControl->maxComms)&(comm>0)){
    verboseEnabled[comm] = state;
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
  verboseMsg("------------------");
  verboseMsg("Help");
  verboseMsg("------------------");
  switch (m) {
    case 0:
      verboseMsg("1 = Stop Motor");
      verboseMsg("2 = Toggle Motor State");
      verboseMsg("3 = Set BT verbose");
      verboseMsg("4 = Turn on motor x");
      verboseMsg("5 = Clear");
      verboseMsg("6 = Re-Initialize");
      verboseMsg("7 = Toggle OPC");
      break;
    default:
      break;
  }
  verboseMsg("------------------");
}
