//MotorControl

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
 * UP: 3/23/11/2016
 * ---------------
 * Dev: Add your name here
 * UP: Date you made changes
 * ---------------
*/

#ifndef __MotorControl_H_defined__
#define __MotorControl_H_defined__

#include <Arduino.h>
#include <VerboseControl.h>

#define MAX_MOTORS 18

class MotorControl{
  public:
    //Inherited object
    VerboseControl *verboseControl;

    //constants - declare values that will remain constant throughout the program here

    MotorControl(VerboseControl *vc);

    //pinout - declare pins to be used here
    int motorPin[MAX_MOTORS];
    int startMotorPin;

    //values - place class variables here
    bool motorState[MAX_MOTORS];
    bool motorChangeVerbose;

    void toggleMotor(int motorID);
    void killAll();
    void toggleAll();
    void setMotorState(int motorID, bool state);

  private:

};
#endif
