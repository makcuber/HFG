//CommandContol

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
 * ---------------
 * Dev: Add your name here
 * UP: Date you made changes
 * ---------------
*/

#include "PatternControl.h"

//Motor Arrays
motorArray1x1::motorArray1x1(String *s, int *n){
  name=*s;
  motorID=*n;
}
motorArray2x4::motorArray2x4(String *s,int *x[2], int *y[4]){
  for(int i=0;i<width;i++){
    xIDs[i]=*x[i];
  }
  for(int i=0;i<length;i++){
    yIDs[i]=*y[i];
  }
}

//1x1

//pulse1x1
pulse1x1::pulse1x1(int *d, bool *s){
  duration=*d;
  state=*s;
}
//Pattern1x1
pattern1x1::pattern1x1(String *s){
  name=*s;
}
void pattern1x1::setPulse(int *duration, bool *state, int *n){
  pulse1x1 p(duration,state);
  pulses[*n]=&p;
}
pulse1x1 *pattern1x1::getPulse(int *n){
  return pulses[*n];
}

//2x4

//pulse2x4
pulse2x4::pulse2x4(int *d, bool *x[2], bool *y[4]){
  duration=*d;
  for(int i=0;i<2;i++){
    xStates[i]=x[i];
  }
  for(int i=0;i<4;i++){
    yStates[i]=y[i];
  }
}
//Pattern2x4
pattern2x4::pattern2x4(String *s){
  name=*s;
}
void pattern2x4::setPulse(int *duration, bool *x[2], bool *y[4], int *n){
  pulse2x4 p(duration,x,y);
  pulses[*n]=&p;
}
pulse2x4 *pattern2x4::getPulse(int *n){
  return pulses[*n];
}


//Pattern Control
PatternControl::PatternControl(VerboseControl *vc, MotorControl *mc){
  verboseControl=vc;
  motorControl=mc;
}
PatternControl::PatternControl(VerboseControl *vc, MotorControl *mc, int n){
  verboseControl=vc;
  motorControl=mc;
}
