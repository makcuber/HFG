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
 * ---------------
 * Dev: Add your name here
 * UP: Date you made changes
 * ---------------
*/

#ifndef __BootControl_H_defined__
#define __BootControl_H_defined__

#include <Arduino.h>
#include <VerboseControl.h>
#include <CommControl.h>
#include <MotorControl.h>

class BootControl {
  public:
    //Inherited object
    CommControl *commControl;
    VerboseControl *verboseControl;
    MotorControl *motorControl;

    //constants - declare values that will remain constant throughout the program here

    //pinout - declare pins to be used here
    int *resetPin;

    //values - place class variables here

    //Functions
    BootControl(CommControl *cc, VerboseControl *vc, MotorControl *mc, int *pin);

    void btBoot();
    void boot();
    void reset(int n);

  private:
    void killReset();
    const static int resetDelay = 100;

};

#endif
