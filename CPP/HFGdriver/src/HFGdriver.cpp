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
 * UP: 3/30/11/2016
 * UD: 4/1/12/2016
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
#include <OPC.h>
#include <PatternControl.h>

//constants - declare values that will remain constant throughout the program here

//values - place global variables here
char runMode = 'n';
int resetPin=2;

//Define Control objects
CommControl commControl;
VerboseControl verboseControl(&commControl);
MotorControl motorControl(&verboseControl);
BootControl bootControl(&commControl,&verboseControl,&motorControl, &resetPin);
OPCSerial OPCSerial;
PatternControl patternControl(&verboseControl,&motorControl,250);
CommandControl commandControl(&commControl,&verboseControl,&motorControl,&bootControl,&patternControl);

//function declarations
void secret();

void bluetooth();
void bluetoothRead();
void bluetoothWrite(String msg);

//Eastereggs
void secret(){
  //hide something fun here :)
}

//OPC Functions
bool YYZA(const char *itemID, const opcOperation opcOP, const bool value){
  static bool tmpB = false;
  /*
   * if operation is a write command from OPC Client
   */
  if (opcOP == opc_opwrite) {
    tmpB=value;
    if(tmpB){
      patternControl.runYYZ(1);
    }
    verboseControl.debugMsg("OPC ItemID "+String(*itemID)+" set to "+value);

  } else {
    verboseControl.debugMsg("OPC ItemID "+String(*itemID)+" = "+tmpB);
    return tmpB;
  }
}
bool YYZB(const char *itemID, const opcOperation opcOP, const bool value){
  static bool tmpB = false;
  /*
   * if operation is a write command from OPC Client
   */
  if (opcOP == opc_opwrite) {
    tmpB=value;
    if(tmpB){
      patternControl.runYYZ(2);
    }
    verboseControl.debugMsg("OPC ItemID "+String(*itemID)+" set to "+value);

  } else {
    verboseControl.debugMsg("OPC ItemID "+String(*itemID)+" = "+tmpB);
    return tmpB;
  }
}
bool OnOffA(const char *itemID, const opcOperation opcOP, const bool value){
  static bool tmpB = false;
  /*
   * if operation is a write command from OPC Client
   */
  if (opcOP == opc_opwrite) {
    tmpB=value;
    if(tmpB){
      patternControl.runOnOff(1);
    }
    verboseControl.debugMsg("OPC ItemID "+String(*itemID)+" set to "+value);

  } else {
    verboseControl.debugMsg("OPC ItemID "+String(*itemID)+" = "+tmpB);
    return tmpB;
  }
}
bool OnOffB(const char *itemID, const opcOperation opcOP, const bool value){
  static bool tmpB = false;
  /*
   * if operation is a write command from OPC Client
   */
  if (opcOP == opc_opwrite) {
    tmpB=value;
    if(tmpB){
      patternControl.runOnOff(2);
    }
    verboseControl.debugMsg("OPC ItemID "+String(*itemID)+" set to "+value);

  } else {
    verboseControl.debugMsg("OPC ItemID "+String(*itemID)+" = "+tmpB);
    return tmpB;
  }
}
bool OnOffGlove(const char *itemID, const opcOperation opcOP, const bool value){
  static bool tmpB = false;
  /*
   * if operation is a write command from OPC Client
   */
  if (opcOP == opc_opwrite) {
    tmpB=value;
    if(tmpB){
      patternControl.runOnOff(0);
    }
    verboseControl.debugMsg("OPC ItemID "+String(*itemID)+" set to "+value);

  } else {
    verboseControl.debugMsg("OPC ItemID "+String(*itemID)+" = "+tmpB);
    return tmpB;
  }
}
bool led(const char *itemID, const opcOperation opcOP, const bool value){
  static bool ledValue = false;

  /*
   * if operation is a write command from OPC Client
   */
  if (opcOP == opc_opwrite) {
    ledValue = value;

    if (ledValue)
      digitalWrite(13, HIGH);
    else
      digitalWrite(13, LOW);
    verboseControl.debugMsg("OPC ItemID "+String(*itemID)+" set to "+value);
  }
  else
    /*
     * read the led status
     */
    verboseControl.debugMsg("OPC ItemID "+String(*itemID)+" = "+ledValue);
    return ledValue;
}

//BOOTUP

void setup() {
  switch (runMode) {
    case 'b':
      bootControl.btBoot();
      break;
    case 't':
      Serial.begin(9600);
      Serial.println("Hello World!");
      break;
    default:
      bootControl.boot();
      OPCSerial.setup();
      OPCSerial.addItem("OnOffA", opc_readwrite, opc_bool, OnOffA);
      OPCSerial.addItem("OnOffB", opc_readwrite, opc_bool, OnOffB);
      OPCSerial.addItem("YYZA", opc_readwrite, opc_bool, YYZA);
      OPCSerial.addItem("YYZB", opc_readwrite, opc_bool, YYZB);
      OPCSerial.addItem("OnOffGlove", opc_readwrite, opc_bool, OnOffGlove);
      OPCSerial.addItem("LED", opc_readwrite, opc_bool, led);
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
    case 't':
      while (Serial.available() > 0) {
        Serial.println(Serial.readStringUntil('\n'));
      }
      break;
    default:
      //USB Communication
      if(commControl.commCmd[0]){
        commandControl.usbComm();
      }
      if(commControl.commCmd[1]){
        commandControl.btComm();
      }

      //OPC
      if(commControl.OPC_CHANNEL==0){
        OPCSerial.processOPCCommands();
      }else{
        OPCSerial.processOPCCommandsBT();
      }
      /*
      while(commControl.getCommStatus(1)){
        verboseControl.verboseMsg(String(Serial1.read()));
      }
      */
      break;
  }
}
