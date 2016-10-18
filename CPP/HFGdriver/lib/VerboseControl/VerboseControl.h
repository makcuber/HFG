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
 * ---------------
 * Dev: Add your name here
 * UP: Date you made changes
 * ---------------
*/

#ifndef __VerboseControl_H_defined__
#define __VerboseControl_H_defined__

#include <Arduino.h>
#include <CommControl.h>

class VerboseControl {
  public:
    //Inherited object
    CommControl *commControl;

    //Variables
    int defaultClearWidth;
    bool verboseEnabled[4];

    VerboseControl(CommControl *cc);

    void verboseMsg(String msg);
    void setVerbose(bool state, int comm);

    void clearConsole();
    void showMenu(int m);
  private:

};

#endif
