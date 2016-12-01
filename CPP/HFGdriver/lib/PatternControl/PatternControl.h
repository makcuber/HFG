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
 * UP: 3/30/11/2016
 * UD: 4/1/12/2016
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

#define MAX_PATTERN_LENGTH 12
#define DEFAULT_DURATION 500
#define MAX_PULSE_DURATION 3000

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

class pulse1x1{
  public:
    int duration;
    bool state;

    void set(int *d, bool *s);
    pulse1x1();
};
class pulse2x4{
  public:
    int duration;
    bool state;
    bool States[2][4];

    void set(int *d, bool b[2][4]);
    pulse2x4();
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
    pulse1x1 pulses[MAX_PATTERN_LENGTH];
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
    pulse2x4 pulses[MAX_PATTERN_LENGTH];
};

class PatternControl {
  public:
    //Inherited object
    VerboseControl *verboseControl;
    MotorControl *motorControl;

    //constants - declare values that will remain constant throughout the program here
    const static int defaultGloveID=MAX_MOTORS-1;
    //values - place class variables here
    int defaultDuration;
    bool motorVerbose;

    //Functions
    PatternControl(VerboseControl *vc, MotorControl *mc, int d);
    void setMotorArrayPins(char c, int ids[2][4], String s);
    void setMotorArrayPins(String s, int p);
    void runPattern(motorArray1x1 *mA, pattern1x1 *pat);
    void runPattern(motorArray2x4 *mA, pattern2x4 *pat);
    void runOnOff(int d[MAX_PATTERN_LENGTH], int n);
    void runOnOff(int d, int n);
    void runOnOff(int n);
    void runYYZ(int b, int m, int n);
    void runYYZ(int b, int n);
    void runYYZ(int n);
  private:
    motorArray1x1 *gloveMotor;
    motorArray2x4 *motorArrayA,*motorArrayB;
    pattern1x1 *onOff1x1;
    pattern2x4 *onOff2x4;
    pattern2x4 *sweepUp, *sweepDown, *sweepLeft, *sweepRight;
    pattern2x4 *alternateRow, *alternateCol;

    void setOnOff1x1(int *d);
    pattern1x1* getOnOff1x1(int *d);
    void setOnOff2x4(int d);
    void setOnOff2x4(int d[MAX_PATTERN_LENGTH]);
    pattern2x4* getOnOff2x4(int d);
    pattern2x4* getOnOff2x4(int d[MAX_PATTERN_LENGTH]);
};
#endif
