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
 * DC: 2/01/11/2016
 * UD: 3/02/11/2016
 * ---------------
 * Dev: Add your name here
 * UP: Date you made changes
 * ---------------
*/

#include <opcControl.h>

opcControl::opcControl(VerboseControl *vc, CommControl *cc, MotorControl *mc, int *ID) {
  verboseControl=vc;
  commControl=cc;
  motorControl=mc;
  callbackObj=new opcCallback(vc,mc);

  serialOPC=new OPCSerial(vc,cc,ID);
  serialOPC->setup();
  for(int i=0;i<motorControl->maxMotors;i++){
    char tmp = char(i);
    serialOPC->addItem(&tmp, opc_readwrite, opc_bool, &opcCallback::motorCallback);
  }

}

void opcControl::updateOPC() {
  serialOPC->processOPCCommands();
}
