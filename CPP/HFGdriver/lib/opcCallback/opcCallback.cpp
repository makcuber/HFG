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
 * DC: 3/02/11/2016
 * ---------------
 * Dev: Add your name here
 * UP: Date you made changes
 * ---------------
*/

#include <opcCallback.h>

opcCallback::opcCallback(VerboseControl *vc, MotorControl *mc){
  verboseControl=vc;
  motorControl=mc;
}

bool opcCallback::motorCallback(const char *itemID, const opcOperation opcOP, const bool value){
  static bool tmpB = false;
  /*
   * if operation is a write command from OPC Client
   */
  if (opcOP == opc_opwrite) {
    tmpB = value;
    verboseControl->debugMsg("OPC ItemID "+String(*itemID)+" set to "+value);
    motorControl->setMotorState(int(*itemID), value);

  } else {
    tmpB=motorControl->motorState[int(*itemID)];
    verboseControl->debugMsg("OPC ItemID "+String(*itemID)+" = "+tmpB);
  }
  verboseControl->debugMsg("OPC ItemID "+String(*itemID)+" = "+tmpB);
  return tmpB;
}
