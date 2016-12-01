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
 * UP: 2/29/11/2016
 * UP: 3/30/11/2016
 * UD: 4/1/12/2016
 * ---------------
 * Dev: Add your name here
 * UP: Date you made changes
 * ---------------
*/

#include "PatternControl.h"

//Motor Arrays
motorArray1x1::motorArray1x1(String s, int n){
  name=s;
  motorID=n;
}
motorArray2x4::motorArray2x4(String s,int ids[2][4]){
  for(int w=0;w<width;w++){
    for(int l=0;l<length;l++){
      motorIDs[w][l]=ids[w][l];
    }
  }
  name=s;
}

//1x1

//pulse1x1
void pulse1x1::set(int *d, bool *s){
  duration=*d;
  state=*s;
}
pulse1x1::pulse1x1(){
  duration=DEFAULT_DURATION;
  state=false;
}
//Pattern1x1
pattern1x1::pattern1x1(String s){
  name=s;
}
void pattern1x1::setPulse(int *duration, bool *state, int *n){
    pulses[*n].set(duration, state);
    pulseState[*n]=true;
    calcPulseCount();
}
pulse1x1 *pattern1x1::getPulse(int *n){
  return &pulses[*n];
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
void pulse2x4::set(int *d, bool b[2][4]){
  duration=*d;
  for(int w=0;w<2;w++){
    for(int l=0;l<4;l++){
      States[w][l]=b[w][l];
    }
  }
}
pulse2x4::pulse2x4(){
  duration=DEFAULT_DURATION;
  for(int w=0;w<2;w++){
    for(int l=0;l<4;l++){
      States[w][l]=false;
    }
  }
}
//Pattern2x4
pattern2x4::pattern2x4(String s){
  name=s;
}
void pattern2x4::setPulse(int *duration, bool b[2][4], int *n){
  if((*n<MAX_PATTERN_LENGTH)&(*n>=0)){
    pulses[*n].set(duration,b);
    pulseState[*n]=true;
  }
}
pulse2x4 *pattern2x4::getPulse(int *n){
  return &pulses[*n];
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
PatternControl::PatternControl(VerboseControl *vc, MotorControl *mc, int d){
  verboseControl=vc;
  motorControl=mc;
  defaultDuration=d;
  motorVerbose=false;

  //config gloveMotor
  setMotorArrayPins("GloveMotor",defaultGloveID);

  //config motorArrayA
  int ids[2][4];
  int c=0;
  for(int w=0;w<2;w++){
    for(int l=0;l<4;l++){
      ids[w][l]=c;
      c++;
    }
  }
  setMotorArrayPins('A',ids,"motorArrayA");

  //config motorArrayB
  for(int w=0;w<2;w++){
    for(int l=0;l<4;l++){
      ids[w][l]+=8;
    }
  }
  setMotorArrayPins('B',ids,"motorArrayB");

  //config onOff1x1
  setOnOff1x1(&defaultDuration);

  //config onOff2x4
  setOnOff2x4(&defaultDuration);

}
void PatternControl::setOnOff1x1(int *d){
  onOff1x1=new pattern1x1("OnOff");
  bool tmpB=true;
  for(int i=0;i<MAX_PATTERN_LENGTH;i++){
    onOff1x1->setPulse(d, &tmpB, &i);
    tmpB=!tmpB;
  }
}
pattern1x1* PatternControl::getOnOff1x1(int *d){
  setOnOff1x1(d);
  return onOff1x1;
}
void PatternControl::setOnOff2x4(int d){
  onOff2x4=new pattern2x4("OnOff");
  bool tmpB=true;
  for(int i=0;i<MAX_PATTERN_LENGTH;i++){
    bool b[2][4];
    for(int w=0;w<2;w++){
      for(int l=0;l<4;l++){
        b[w][l]=tmpB;
      }
    }
    onOff2x4->setPulse(&d, b, &i);
    tmpB=!tmpB;
  }
}
void PatternControl::setOnOff2x4(int d[MAX_PATTERN_LENGTH]){
  onOff2x4=new pattern2x4("OnOff");
  bool tmpB=true;
  for(int i=0;i<MAX_PATTERN_LENGTH;i++){
    bool b[2][4];
    for(int w=0;w<2;w++){
      for(int l=0;l<4;l++){
        b[w][l]=tmpB;
      }
    }
    onOff2x4->setPulse(&d[i], b, &i);
    tmpB=!tmpB;
  }
}
pattern2x4* PatternControl::getOnOff2x4(int duration){
  setOnOff2x4(duration);
  return onOff2x4;
}
pattern2x4* PatternControl::getOnOff2x4(int durations[MAX_PATTERN_LENGTH]){
  setOnOff2x4(durations);
  return onOff2x4;
}
void PatternControl::runPattern(motorArray1x1 *mA, pattern1x1 *pat){
  motorControl->motorChangeVerbose=motorVerbose;
  verboseControl->verboseMsg("Running pattern "+pat->name+" on motor array "+mA->name);
  for(int i=0;i<MAX_PATTERN_LENGTH;i++){
    if(pat->PulseState(&i)==true){
      verboseControl->debugMsg("Set motor "+String(mA->motorID)+" to "+String(pat->getPulse(&i)->state)+" for "+String(pat->getPulse(&i)->duration));
      motorControl->setMotorState(mA->motorID, pat->getPulse(&i)->state);
      //verboseControl->debugMsg("Millis: "+String(millis()));
      delay(pat->getPulse(&i)->duration);
      //verboseControl->debugMsg("Millis: "+String(millis()));
    }
  }
  motorControl->motorChangeVerbose=true;
}
void PatternControl::runPattern(motorArray2x4 *mA, pattern2x4 *pat){
  motorControl->motorChangeVerbose=motorVerbose;
  verboseControl->verboseMsg("Running pattern "+pat->name+" on motor array "+mA->name);
  for(int i=0;i<MAX_PATTERN_LENGTH;i++){
    if(pat->PulseState(&i)==true){
      for(int w=0;w<mA->width;w++){
        for(int l=0;l<mA->length;l++){
            verboseControl->debugMsg("Set motor "+String(mA->motorIDs[w][l])+" to "+String(pat->getPulse(&i)->state)+" for "+String(pat->getPulse(&i)->duration));
            motorControl->setMotorState(mA->motorIDs[w][l], pat->getPulse(&i)->States[w][l]);
        }
      }
      delay(pat->getPulse(&i)->duration);
    }
  }
  motorControl->motorChangeVerbose=true;
}
void PatternControl::setMotorArrayPins(char c, int ids[2][4], String s){
  switch(c){
    case 'A':
      motorArrayA=new motorArray2x4(s, ids);
      break;
    case 'B':
      motorArrayB=new motorArray2x4(s, ids);
      break;
    default:
      break;
  }
}
void PatternControl::setMotorArrayPins(String s, int p){
  gloveMotor=new motorArray1x1(s, p);
}
void PatternControl::runOnOff(int n){
  runOnOff(defaultDuration,n);
}
void PatternControl::runOnOff(int d, int n){
  switch(n){
    case 0:
      runPattern(gloveMotor, getOnOff1x1(&d));
      break;
    case 1:
      runPattern(motorArrayA, getOnOff2x4(&d));
      break;
    case 2:
      runPattern(motorArrayB, getOnOff2x4(&d));
      break;
    default:
      break;
  }
}
void PatternControl::runOnOff(int d[MAX_PATTERN_LENGTH], int n){
  switch(n){
    case 0:
      runPattern(gloveMotor, getOnOff1x1(d));
      break;
    case 1:
      runPattern(motorArrayA, getOnOff2x4(d));
      break;
    case 2:
      runPattern(motorArrayB, getOnOff2x4(d));
      break;
    default:
      break;
  }
}
void PatternControl::runYYZ(int n){
  runYYZ(defaultDuration, 2, n);
}
void PatternControl::runYYZ(int b, int n){
  runYYZ(b, 2, n);
}
void PatternControl::runYYZ(int b, int m, int n){
  int d[]={b*m,b,b*m,b*m,b*m,b,b*m,b*m,b*m,b*m,b,b};
  switch(n){
    case 0:
      //runPattern(gloveMotor, getOnOff1x1(d));
      break;
    case 1:
      runPattern(motorArrayA, getOnOff2x4(d));
      break;
    case 2:
      runPattern(motorArrayB, getOnOff2x4(d));
      break;
    default:
      break;
  }
}
