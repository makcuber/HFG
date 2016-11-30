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
 * DC: 4/10/09/2015
 * UP: 4/29/09/2016
 * UP: 5/30/09/2016
 * UP: 4/6/10/2016
 * UP: 5/7/10/2016
 * UP: 6/15/10/2016
 * UP: 1/17/10/2016
 * UP: 2/18/10/2016
 * UD: 3/02/11/2016
 * UD: 4/03/11/2016
 * UD: 7/13/11/2016
 * UD: 1/14/11/2016
 * UD: 2/15/11/2016
 * UD: 3/16/11/2016
 * UP: 2/22/11/2016
 * UP: 3/23/11/2016
 * UP: 2/29/11/2016
 * ---------------
 * Dev: Add your name here
 * UP: Date you made changes
 * ---------------
*/

//includes
#include <Arduino.h>
#include <MotorControl.h>
#include <CommControl.h>
#include <VerboseControl.h>
#include <CommandControl.h>
#include <opcControl.h>
#include <PatternControl.h>

//constants - declare values that will remain constant throughout the program here

//values - place global variables here
char runMode = 'n';
int opcChannel=2;
int resetPin=2;

//Define Control objects
CommControl commControl;
VerboseControl verboseControl(&commControl);
MotorControl motorControl(&verboseControl);
BootControl bootControl(&commControl,&verboseControl,&motorControl, &resetPin);
opcControl opcControl(&verboseControl, &commControl, &motorControl, &opcChannel);
PatternControl patternControl(&verboseControl,&motorControl,500);
CommandControl commandControl(&commControl,&verboseControl,&motorControl,&bootControl, &patternControl);

//cmd [];

//function declarations
void secret();

void bluetooth();
void bluetoothRead();
void bluetoothWrite(String msg);

//Eastereggs
void secret(){
  //hide something fun here :)
}

//BOOTUP

void setup() {
  switch (runMode) {
    case 'b':
      bootControl.btBoot();
      break;
    default:
      bootControl.boot();
      opcControl.enabled=true;
      opcControl.setup();
      commandControl.opcChannel=&opcChannel;
      break;
  }
}

//Bluetooth Run Mode

void bluetooth(){
  bluetoothRead();
  bluetoothWrite(Serial.readString());
}
void bluetoothRead() {
  // Read device output if available.
  if (Serial1.available()) {
    String tmp = Serial1.readString();

    //Serial.println(cmdS);
    commandControl.cmdSort(commandControl.commMode[1], tmp, "");
    tmp = ""; // No repeats
  }
}
void bluetoothWrite(String msg){
  // Read user input if available.
  if (Serial.available()) {
    //delay(10); // The delay is necessary to get this working!
    Serial1.println(msg);
  }
}

//MAIN

void loop() {
  switch (runMode) {
    case 'b':
      bluetooth();
      break;
    default:
      //USB Communication
      if(verboseControl.verboseLevel[0]>1){
        commandControl.usbComm();
      }
      if(verboseControl.verboseLevel[1]>1){
        commandControl.btComm();
      }

      //Bluetooth Communication
      //commandControl.btComm();
      //push Bluetooth communications to USB communications
      /*
      if (commControl.btEnabled) {
        //comm2Comm(1, 0, 's');
        bluetoothRead();
      }
      */
      //OPC
      //opcControl.updateOPC();
      break;
  }
}
