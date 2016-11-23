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
 * UD: 4/03/11/2016
 * UD: 7/13/11/2016
 * UD: 1/14/11/2016
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

  enabled=false;
  serialOPC=new OPCSerial(vc,cc,ID);
}
void opcControl::setup(){
  serialOPC->setup();
  for(int i=0;i<MAX_MOTORS;i++){
    String str = "Motor"+String(i);
    const char *c=str.c_str();
    verboseControl->debugMsg("Added OPC Item "+str);
    serialOPC->addItem(c, opc_readwrite, opc_bool, &opcCallback::motorCallback);
  }
  //serialOPC->sendOPCItemsMap();
}
void opcControl::updateOPC() {
  if(enabled){
    serialOPC->processOPCCommands();
  }
}
