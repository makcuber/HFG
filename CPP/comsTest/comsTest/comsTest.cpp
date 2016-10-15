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
 * ---------------
 * Dev: Add your name here
 * UP: Date you made changes
 * ---------------
*/

//includes
#include <Arduino.h>

//constants - declare values that will remain constant throughout the program here
const int maxMotors = 18;
const int maxComms = 4;

//pinout - declare pins to be used here
int motorPin[maxMotors];
int startMotorPin = 22;

//values - place global variables here
bool motorState[maxMotors];
int btMode = 0;
int usbMode = 0;
char runMode = 'n';
int defaultClearWidth = 50;
bool motorChangeVerbose = false;
bool verboseEnabled[maxComms];
bool commState[maxComms];

//Serial variables
String cmdS;
String valS;
int mode = 1;
int commBaud[maxComms];
bool btEnabled = true;
int baudRates[]={300,1200,2400,4800,9600,19200};

//function declarations
void clusterfuck();
void secret();

void btBoot();
void boot();

void bluetooth();
void bluetoothRead();
void bluetoothWrite(String msg);

void comm2Comm(int commA, int commB, char mode);

int SerialReadB(int comm);
void SerialWriteB(int comm, int msg);
String SerialReadS(int comm);
void SerialWriteS(int comm, String msg);

void cmdSort(int mode, String cmdS, String valS);
void btComm();
void btcmd(String cmdS, String valS);
void usbComm();
void usbcmd(String cmdS, String valS);

void verboseMsg(String msg);
void setVerbose(bool state, int comm);

void toggleMotor(int motorID);
void killAll();
void setMotorState(int motorID, bool state);

void clearConsole();
void showMenu(int m);

void disconnectAllComms();
void connectAllComms();
void reconnectAllComms();
void setAllCommBaud(int baud);
void disconnectComm(int comm);
bool getCommStatus(int comm);
void reconnectComm(int comm);
void connectComm(int comm);

//Eastereggs

void clusterfuck() {
  verboseMsg("Gabe made me write this function");
}
void secret(){
  //hide something fun here :)
}

//BOOTUP

void setup() {
  switch (runMode) {
    case 'b':
      btBoot();
      break;
    default:
      boot();
      break;
  }
}
void btBoot() {
  // Open serial communications:
  Serial.begin(9600);
  Serial.println("Type AT commands!");

  // The HC-06 defaults to 9600 according to the datasheet.
  Serial1.begin(9600);

}
void boot() {
  //put your setup code here, to run once:

  //enable serial communications
  setAllCommBaud(9600);
  connectComm(0);
  connectComm(1);

  //set comm port states

  verboseEnabled[0] = true;
  verboseEnabled[1] = true;

  verboseMsg("Serial Communications Established");
  verboseMsg("---------------------------------");
  verboseMsg("CommPort\t|Status\t|Verbose");
  verboseMsg("---------------------------------");
  for (int i = 0; i < maxComms; i++) {
    verboseMsg("Comm#" + String(i) + "\t\t|" + String(commState[i]) + "\t|" + String(verboseEnabled[i]));
  }
  verboseMsg("---------------------------------");
  verboseMsg("");

  verboseMsg("Initializing System");
  verboseMsg("-------------------");

  //configure motors pins for each motor
  verboseMsg("Configuring motor pins...");
  verboseMsg("-----------------------------------");
  verboseMsg("Loop#\t|motorPin\t|motorState");
  verboseMsg("-----------------------------------");
  motorChangeVerbose = false;
  for (int i = 0; i < maxMotors; i++) {

    //set motor pin number
    motorPin[i] = startMotorPin + i;

    //set pinmode for pin
    pinMode(motorPin[i], OUTPUT);

    //set starting motor state
    setMotorState(i, false);

    verboseMsg(String(i) + "\t|" + String(motorPin[i]) + "\t\t|" + String(motorState[i]));
  }
  verboseMsg("-----------------------------------");
  motorChangeVerbose = true;
  verboseMsg("Initialization COMPLETE\n");

  //clusterfuck();
}

//MAIN

void loop() {
  switch (runMode) {
    case 'b':
      bluetooth();
      break;
    default:
      //USB Communication
      usbComm();
      //Bluetooth Communication
      //btComm();
      //push Bluetooth communications to USB communications
      if (btEnabled) {
        //comm2Comm(1, 0, 's');
        bluetoothRead();
      }
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
    cmdS = Serial1.readString();

    //Serial.println(cmdS);
    cmdSort(btMode, cmdS, "");
    cmdS = ""; // No repeats
  }
}
void bluetoothWrite(String msg){
  // Read user input if available.
  if (Serial.available()) {
    //delay(10); // The delay is necessary to get this working!
    Serial1.println(msg);
  }
}

//Default Run Mode

void comm2Comm(int commA, int commB, char mode) {
  String tmpS;
  int tmpI;
  switch (mode) {
    case 's':
      SerialWriteS(commB, SerialReadS(commA));
      break;
    case 'b':
      tmpI = SerialReadB(commA);
      delay(10);
      SerialWriteB(commB, tmpI);
      break;
    default:
      break;
  }
}

int SerialReadB(int comm) {
  switch (comm) {
    case 0:
      if (getCommStatus(comm)) {
        return Serial.read();
      }
      break;
    case 1:
      if (getCommStatus(comm)) {
        return Serial1.read();
      }
      break;
    case 2:
      if (getCommStatus(comm)) {
        return Serial2.read();
      }
      break;
    case 3:
      if (getCommStatus(comm)) {
        return Serial3.read();
      }
      break;
    default:
      return -1;
      break;
  }
}
void SerialWriteB(int comm, int msg) {
  if (msg != 0) {
    switch (comm) {
      case 0:
        Serial.write(msg);
        break;
      case 1:
        Serial1.write(msg);
        break;
      case 2:
        Serial2.write(msg);
        break;
      case 3:
        Serial3.write(msg);
        break;
      default:
        break;
    }
  }
}
String SerialReadS(int comm) {
  switch (comm) {
    case 0:
      if (getCommStatus(comm)) {
        return Serial.readString();
      }
      break;
    case 1:
      if (getCommStatus(comm)) {
        return Serial1.readString();
      }
      break;
    case 2:
      if (getCommStatus(comm)) {
        return Serial2.readString();
      }
      break;
    case 3:
      if (getCommStatus(comm)) {
        return Serial3.readString();
        break;
      default:
        return "";
        break;
      }
  }
}
void SerialWriteS(int comm, String msg) {
  if (msg != "") {
    switch (comm) {
      case 0:
        Serial.println(msg);
        break;
      case 1:
        Serial1.println(msg);
        break;
      case 2:
        Serial2.println(msg);
        break;
      case 3:
        Serial3.println(msg);
        break;
      default:
        break;
    }
  }
}

void cmdSort(int mode, String cmdS, String valS) {
  switch (mode) {
    case 0:
      //verboseMsg("commMode#0");
      usbcmd(cmdS, valS);
      break;
    case 1:
      //verboseMsg("commMode#1");
      btcmd(cmdS, valS);
      break;
    case 2:
      //verboseMsg("commMode#2");
      break;
    case 3:
      //verboseMsg("commMode#3");
      break;
    case 4:
      //verboseMsg("commMode#4");
      break;
    case 5:
      //verboseMsg("commMode#5");
      break;
    default:
      //WARNING: code placed here will run on every cycle that you dont send a command
      break;
  }
}
void btComm() {
  while (Serial1.available()) {
    cmdS = Serial1.readStringUntil(',');
    valS = Serial1.readStringUntil('\n');
  }

  cmdSort(btMode, cmdS, valS);

  //reset the cmd and val variables for the next cycle
  cmdS = "-1";
  valS = "-1";
}
void btcmd(String cmdS, String valS) {
  int cmd = cmdS.toInt();
  //int val = valS.toInt();
  switch (cmd) {
    case 0:
      verboseMsg("BT cmd#0");
      showMenu(btMode);
      break;
    case 1:
      verboseMsg("BT cmd#1");
      break;
    case 2:
      verboseMsg("BT cmd#2");
      break;
    case 3:
      verboseMsg("BT cmd#3");
      break;
    case 4:
      verboseMsg("BT cmd#4");
      break;
    case 5:
      verboseMsg("BT cmd#5");
      break;
    default:
      //WARNING: code placed here will run on every cycle that you dont send a command
      if (verboseEnabled[1]) {

      }
      break;
  }
}
void usbComm() {
  while (Serial.available()) {
    cmdS = Serial.readStringUntil(',');
    valS = Serial.readStringUntil('\n');
  }

  cmdSort(usbMode, cmdS, valS);

  //reset the cmd and val variables for the next cycle
  cmdS = "-1";
  valS = "-1";
}
void usbcmd(String cmdS, String valS) {
  int cmd = cmdS.toInt();
  int val = valS.toInt();
  switch (cmd) {
    case 0:
      verboseMsg("USB cmd#0");
      showMenu(usbMode);
      break;
    case 1:
      verboseMsg("USB cmd#1");
      killAll();
      break;
    case 2:
      verboseMsg("USB cmd#2");
      toggleMotor(0);
      break;
    case 3:
      verboseMsg("USB cmd#3");
      setVerbose(true,1);
      break;
    case 4:
      verboseMsg("USB cmd#4");
      setMotorState(val, true);
      break;
    case 5:
      verboseMsg("USB cmd#5");
      clearConsole();
      break;
    case 6:
      verboseMsg("USB cmd#6");
      boot();
      break;
    case 7:
      verboseMsg("USB cmd#7");
      bluetoothWrite(valS);
      break;

    default:
      //WARNING: code placed here will run on every cycle that you dont send a command
      break;
  }
}

//Verbose

void verboseMsg(String msg) {
  if (verboseEnabled[0]) {
    Serial.println(msg);
  }
  if (verboseEnabled[1]) {
    Serial1.println(msg);
  }
  if (verboseEnabled[2]) {
    Serial2.println(msg);
  }
  if (verboseEnabled[3]) {
    Serial3.println(msg);
  }
}
void setVerbose(bool state, int comm) {
  if((comm<maxComms)&(comm>0)){
    verboseEnabled[comm] = state;
  }
}

//Motor Control

void toggleMotor(int motorID) {
  setMotorState(motorID, !motorState[motorID]);
}
void killAll() {
  motorChangeVerbose = false;
  for (int i = 0; i < maxMotors; i++) {
    setMotorState(i, false);
  }
  verboseMsg("Motor State Change");
  verboseMsg("------------------");
  verboseMsg("MotorPin:" + String(motorPin[0]) + " - " + String(motorPin[maxMotors - 1]));
  verboseMsg("MotorState:" + String(motorState[0]));
  motorChangeVerbose = true;
}
void setMotorState(int motorID, bool state) {
  if (state) {
    motorState[motorID] = true;
    digitalWrite(motorPin[motorID], HIGH);
  } else {
    motorState[motorID] = false;
    digitalWrite(motorPin[motorID], LOW);
  }
  if (motorChangeVerbose) {
    verboseMsg("Motor State Change");
    verboseMsg("------------------");
    verboseMsg("MotorPin:" + String(motorPin[motorID]));
    verboseMsg("MotorState:" + String(motorState[motorID]));
    verboseMsg("\n");
  }
}

//CLI

void clearConsole() {
  for (int i = 0; i < defaultClearWidth; i++) {
    verboseMsg("");
  }
}
void showMenu(int m) {
  verboseMsg("------------------");
  verboseMsg("Help");
  verboseMsg("------------------");
  switch (m) {
    case 0:
      verboseMsg("1 = Stop Motor");
      verboseMsg("2 = Toggle Motor State");
      verboseMsg("3 = Set BT verbose");
      verboseMsg("4 = Turn on motor x");
      verboseMsg("5 = Clear");
      verboseMsg("6 = Re-Initialize");
      break;
    default:
      break;
  }
  verboseMsg("------------------");
}

//Communications

void reconnectComm(int comm) {
  disconnectComm(comm);
  connectComm(comm);
}
void connectComm(int comm) {
  switch (comm) {
    case 0:
      Serial.begin(commBaud[0]);
      commState[0] = Serial.available();
      break;
    case 1:
      Serial1.begin(commBaud[1]);
      commState[1] = Serial1.available();
      break;
    case 2:
      Serial2.begin(commBaud[2]);
      commState[2] = Serial2.available();
      break;
    case 3:
      Serial3.begin(commBaud[3]);
      commState[3] = Serial3.available();
      break;
    default:
      break;
  }
}
bool getCommStatus(int comm) {
  switch (comm) {
    case 0:
      commState[0] = Serial.available();
      return Serial.available();
      break;
    case 1:
      commState[1] = Serial1.available();
      return Serial1.available();
      break;
    case 2:
      commState[2] = Serial2.available();
      return Serial2.available();
      break;
    case 3:
      commState[3] = Serial3.available();
      return Serial3.available();
      break;
    default:
      return false;
      break;
  }
}
void disconnectComm(int comm) {
  switch (comm) {
    case 0:
      Serial.end();
      commState[0] = Serial.available();
      break;
    case 1:
      Serial1.end();
      commState[1] = Serial1.available();
      break;
    case 2:
      Serial2.end();
      commState[2] = Serial2.available();
      break;
    case 3:
      Serial3.end();
      commState[3] = Serial3.available();
      break;
    default:
      break;
  }
}
void setAllCommBaud(int baud) {
  for (int i = 0; i < maxComms; i++) {
    commBaud[i] = baud;
  }
}
void reconnectAllComms() {
  for (int i = 0; i < maxComms; i++) {
    reconnectComm(i);
  }
}
void connectAllComms() {
  for (int i = 0; i < maxComms; i++) {
    connectComm(i);
  }
}
void disconnectAllComms() {
  for (int i = 0; i < maxComms; i++) {
    disconnectComm(i);
  }
}
