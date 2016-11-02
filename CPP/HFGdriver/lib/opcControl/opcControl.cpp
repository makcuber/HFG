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
 * ---------------
 * Dev: Add your name here
 * UP: Date you made changes
 * ---------------
*/

#include <opcControl.h>

/*
 * create a callback function for the OPCItem
 */
bool opcControl::callback(const char *itemID, const opcOperation opcOP, const bool value){
  static bool tmpB = false;
  /*
   * if operation is a write command from OPC Client
   */
  if (opcOP == opc_opwrite) {
    tmpB = value;
    //verboseControl->verboseMsg("ItemID "+String(*itemID)+" set to "+value);
    if (tmpB){

    } else {

    }

  } else {
    /*
     * read the led status
     */
  }
  return tmpB;
}

opcControl::opcControl(VerboseControl *vc, CommControl *cc, int *ID) {
  /*
   * OPC Object initialization
   */
  serialOPC=new OPCSerial(vc,cc,ID);

  serialOPC->setup();

  /*
   * led OPCItem declaration
   */
  serialOPC->addItem("led", opc_readwrite, opc_bool, callback);
}

void opcControl::updateOPC() {
  serialOPC->processOPCCommands();
}
