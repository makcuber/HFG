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
 * ---------------
 * Dev: Add your name here
 * UP: Date you made changes
 * ---------------
*/

#include "PatternControl.h"

//Patterning

PatternControl::PatternControl(VerboseControl *vc, MotorControl *mc){
  verboseControl=vc;
  motorControl=mc;
}

pulse PatternControl::getPulseAllMotors(int duration, bool state){
  pulse p;
  for(int i=0;i<maxMotors;i++){
    p.motorIDs[i]=true;
  }
  p.duration=duration;
  p.state=state;
  return p;
}

//Pattern Class
pattern(String name, pulse pulses[]){

}
void addPulse(pulse p){
  duration+=p.duration;
  if(p.motorIDs[i]==motorIDs[k]){

  }
}
void runPattern(){

}
