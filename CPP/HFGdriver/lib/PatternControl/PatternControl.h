//Pattern Control

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
 * DC: 3/19/10/2016
 * ---------------
 * Dev: Add your name here
 * UP: Date you made changes
 * ---------------
*/

#ifndef __PatternControl_H_defined__
#define __PatternControl_H_defined__

#include <Arduino.h>
#include <VerboseControl.h>
#include <MotorControl.h>

class PatternControl {
  public:
    //Inherited object
    VerboseControl *verboseControl;
    MotorControl *motorControl;

    //constants - declare values that will remain constant throughout the program here
    static const int maxPatternLength = 4;

    //values - place class variables here
    struct pulse {
      bool motorIDs[motorControl->maxMotors];
      int duration;
      bool state;
    };
    struct motorArray{
      int width,length;
      bool motorIDs[motorControl->maxMotors];
    };

    //Functions
    PatternControl(VerboseControl *vc, MotorControl *mc);

    pulse getPulseAllMotors(int duration, bool state);

    class pattern{
      public:
        pulse pulses[maxPatternLength];
        String name;
        int motorIDs[motorControl->maxMotors];
        int duration;
      private:

    };

  private:

};
#endif
