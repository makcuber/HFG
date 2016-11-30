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
 * UD: 1/14/11/2016
 * UD: 5/25/11/2016
 * UD: 1/28/11/2016
 * UP: 2/29/11/2016
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

#define MAX_PATTERN_LENGTH 4

class motorArray1x1{
  public:
    String name;
    int motorID;

    motorArray1x1(String s, int n);
};
class motorArray2x4{
  public:
    String name;
    const static int width=2;
    const static int length=4;
    int motorIDs[width][length];

    motorArray2x4(String s, int ids[width][length]);
};

struct pulse1x1{
  int duration;
  bool state;

  pulse1x1(int *d, bool *s);
};
struct pulse2x4{
  int duration;
  bool state;
  bool States[2][4];

  pulse2x4(int *d, bool b[2][4]);
};

class pattern1x1{
  public:
    String name;

    pattern1x1(String s);
    void setPulse(int *duration, bool *state, int *n);
    pulse1x1 *getPulse(int *n);
    int PulseCount();
    bool PulseState(int *n);
  private:
    int pulseCount;
    bool pulseState[MAX_PATTERN_LENGTH];
    void calcPulseCount();
    pulse1x1 *pulses[MAX_PATTERN_LENGTH];
};
class pattern2x4{
  public:
    String name;

    pattern2x4(String s);
    void setPulse(int *duration, bool b[2][4], int *n);
    pulse2x4 *getPulse(int *n);
    int PulseCount();
    bool PulseState(int *n);
  private:
    int pulseCount;
    bool pulseState[MAX_PATTERN_LENGTH];
    void calcPulseCount();
    pulse2x4 *pulses[MAX_PATTERN_LENGTH];
};

class PatternControl {
  public:
    //Inherited object
    VerboseControl *verboseControl;
    MotorControl *motorControl;

    //constants - declare values that will remain constant throughout the program here
    const static int defaultGlovePin=DEFAULT_MOTOR_START_PIN+8*2;
    //values - place class variables here
    int defaultDuration;

    //Functions
    PatternControl(VerboseControl *vc, MotorControl *mc, int *d);
    void setMotorArrayPins(char c, int ids[2][4], String s);
    void setMotorArrayPins(String s, int p);
    void runPattern(motorArray1x1 *mA, pattern1x1 *pat);
    void runPattern(motorArray2x4 *mA, pattern2x4 *pat);
    void onOff(int *d, int *n);
  private:
    motorArray1x1 *gloveMotor;
    motorArray2x4 *motorArrayA,*motorArrayB;
    pattern1x1 *onOff1x1;
    pattern2x4 *onOff2x4;
    pattern2x4 *sweepUp, *sweepDown, *sweepLeft, *sweepRight;
    pattern2x4 *alternateRow, *alternateCol;
};
#endif
