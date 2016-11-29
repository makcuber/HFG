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
 * UD: 1/28/11/2016
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
  if((*n<MAX_PATTERN_LENGTH)&(*n>=0)){
    pulse1x1 p(duration,state);
    pulses[*n]=&p;
    pulseState[*n]=true;
    calcPulseCount();
  }
}
pulse1x1 *pattern1x1::getPulse(int *n){
  return pulses[*n];
}
void pattern1x1::calcPulseCount(){
  pulseCount=0;
  for(int i=0;i<MAX_PATTERN_LENGTH;i++){
    if(pulseState[i]==true){
      pulseCount++;
    }
  }
}
int pattern1x1::PulseCount(){
  return pulseCount;
}
bool pattern1x1::PulseState(int *n){
  return pulseState[*n];
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
  if((*n<MAX_PATTERN_LENGTH)&(*n>=0)){
    pulse2x4 p(duration,x,y);
    pulses[*n]=&p;
    pulseState[*n]=true;
  }
}
pulse2x4 *pattern2x4::getPulse(int *n){
  return pulses[*n];
}
void pattern2x4::calcPulseCount(){
  pulseCount=0;
  for(int i=0;i<MAX_PATTERN_LENGTH;i++){
    if(pulseState[i]==true){
      pulseCount++;
    }
  }
}
int pattern2x4::PulseCount(){
  return pulseCount;
}
bool pattern2x4::PulseState(int *n){
  return pulseState[*n];
}

//Pattern Control
PatternControl::PatternControl(VerboseControl *vc, MotorControl *mc){
  verboseControl=vc;
  motorControl=mc;
}
void PatternControl::runPattern(motorArray1x1 *mA, pattern1x1 *pat){
  verboseControl->verboseMsg("Running pattern "+pat->name+" on motor array "+mA->name);
  for(int i=0;i<MAX_PATTERN_LENGTH;i++){
    if(pat->PulseState(&i)==true){
      motorControl->setMotorState(mA->motorID, pat->getPulse(&i)->state);
    }
  }
}
void PatternControl::runPattern(motorArray2x4 *mA, pattern2x4 *pat){
  verboseControl->verboseMsg("Running pattern "+pat->name+" on motor array "+mA->name);
  for(int i=0;i<MAX_PATTERN_LENGTH;i++){
    if(pat->PulseState(&i)==true){
      for(int l=0;l<mA->length;l++){
          motorControl->setMotorState(mA->yIDs[l], pat->getPulse(&i)->yStates[l]);
      }
      for(int w=0;w<mA->width;w++){
          motorControl->setMotorState(mA->xIDs[w], pat->getPulse(&i)->xStates[w]);
      }
    }
  }
}
