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

#ifndef __opcControl_H_defined__
#define __opcControl_H_defined__

#include <VerboseControl.h>
#include <MotorControl.h>

enum opcOperation{
  opc_opread,
  opc_opwrite,
};

class opcCallback{
public:
  //Inherited object
  VerboseControl *verboseControl;
  MotorControl *motorControl;

  //constants - declare values that will remain constant throughout the program here

  //values - place class variables here

  //Functions

  opcCallback();
  opcCallback(VerboseControl *vc, MotorControl *mc);
  bool motorCallback(const char *itemID, const opcOperation opcOP, const bool value);
};
#endif
