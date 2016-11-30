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
pulse1x1::pulse1x1(int *d, bool *s){
  duration=*d;
  state=*s;
}
//Pattern1x1
pattern1x1::pattern1x1(String s){
  name=s;
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
pulse2x4::pulse2x4(int *d, bool b[2][4]){
  duration=*d;
  for(int w=0;w<2;w++){
    for(int l=0;l<4;l++){
      States[w][l]=b[w][l];
    }
  }
}
//Pattern2x4
pattern2x4::pattern2x4(String s){
  name=s;
}
void pattern2x4::setPulse(int *duration, bool b[2][4], int *n){
  if((*n<MAX_PATTERN_LENGTH)&(*n>=0)){
    pulse2x4 p(duration,b);
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
PatternControl::PatternControl(VerboseControl *vc, MotorControl *mc, int d){
  verboseControl=vc;
  motorControl=mc;
  defaultDuration=d;

  //config gloveMotor
  setMotorArrayPins("GloveMotor",defaultGlovePin);

  //config motorArrayA
  int ids[2][4];
  int c=0;
  for(int i=0;i<2;i++){
    for(int k=0;k<4;k++){
      ids[i][k]=DEFAULT_MOTOR_START_PIN+i;
      c++;
    }
  }
  delete &c;
  setMotorArrayPins('A',ids,"GloveMotor");

  //config motorArrayB
  for(int i=0;i<2;i++){
    for(int k=0;k<4;k++){
      ids[i][k]+=8;
    }
  }

  //config onOff1x1
  onOff1x1=new pattern1x1("OnOff");
  bool tmpB=true;
  for(int i=0;i<MAX_PATTERN_LENGTH;i++){
    onOff1x1->setPulse(&defaultDuration, &tmpB, &i);
    tmpB=!tmpB;
  }
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
      for(int w=0;w<mA->width;w++){
        for(int l=0;l<mA->length;l++){
            motorControl->setMotorState(mA->motorIDs[w][l], pat->getPulse(&i)->States[w][l]);
        }
      }
    }
  }
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
void PatternControl::onOff(int n){
  onOff(defaultDuration,n);
}
void PatternControl::onOff(int d, int n){
  switch(n){
    case 0:
      runPattern(gloveMotor, onOff1x1);
      break;
    case 1:
      runPattern(gloveMotor, onOff1x1);
      break;
    case 2:
      runPattern(gloveMotor, onOff1x1);
      break;
    default:
      break;
  }
}
