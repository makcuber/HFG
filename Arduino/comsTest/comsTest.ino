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
 * ---------------
 * Dev: Add your name here
 * UP: Date you made changes
 * ---------------
*/

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
bool btVerbose=false;

//Serial variables
String cmdS;
String valS;
int mode = 1;

void clusterfuck(){
  Serial.println("Gabe made me write this function");
}

void setup() {
  //put your setup code here, to run once:
  //configure motors pins for each motor
  for (int i = 0; i < maxMotors; i++) {
    //set motor pin number
    motorPin[i]=startMotorPin+i;
    //set pinmode for pin
    pinMode(motorPin[i], OUTPUT);
    //set starting motor state
    setMotorState(i,false);
  }
  Serial.begin(9600);
  Serial1.begin(9600);
  clusterfuck();
}

void loop() {
  //USB Communication
  usbComm();
  //Bluetooth Communication
  btComm();
}

String SerialRead(int comm){
  switch(comm){
    case 0:
      break;
    case 1:
      String     
      return Serial1.read();
      break;
    case 2:
      break;
    case 3:
      break;
    default:
      return "";
      break;
  }
}

void cmdSort(int mode, String cmdS, String valS) {
  switch (mode) {
    case 0:
      //Serial.println("commMode#0");
      usbcmd(cmdS, valS);
      break;
    case 1:
      //Serial.println("commMode#1");
      btcmd(cmdS, valS);
      break;
    case 2:
      Serial.println("commMode#2");
      break;
    case 3:
      Serial.println("commMode#3");
      break;
    case 4:
      Serial.println("commMode#4");
      break;
    case 5:
      Serial.println("commMode#5");
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
      showHelp(btMode);
      break;
    case 1:
      Serial.println("cmd#1");
      break;
    case 2:
      Serial.println("cmd#2");
      break;
    case 3:
      Serial.println("cmd#3");
      break;
    case 4:
      Serial.println("cmd#4");
      break;
    case 5:
      Serial.println("cmd#5");
      break;
    default:
      //WARNING: code placed here will run on every cycle that you dont send a command
      if(btVerbose){
          
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
  //int val = valS.toInt();
  switch (cmd) {
    case 0:
      showHelp(usbMode);
      break;
    case 1:
      //Serial.println("cmd#1");
      setMotorState(0, false);
      break;
    case 2:
      //Serial.println("cmd#2");
      toggleMotor(0);
      break;
    case 3:
      //Serial.println("cmd#3");
      setBTverbose(true);
      break;
    case 4:
      Serial.println("cmd#4");
      break;
    case 5:
      Serial.println("cmd#5");
      break;
    default:
      //WARNING: code placed here will run on every cycle that you dont send a command
      break;
  }
}

void setBTverbose(bool state){
  btVerbose=state;
}

void comm2Comm(String cmd, int commA, int commB){
  
}

void toggleMotor(int motorID) {
  setMotorState(motorID, !motorState[motorID]);
}

void setMotorState(int motorID, bool state) {
  if (state) {
    motorState[motorID] = true;
    digitalWrite(motorPin[motorID], HIGH);
  } else {
    motorState[motorID] = false;
    digitalWrite(motorPin[motorID], LOW);
  }
}

void showHelp(int m) {
  Serial.println("------------------");
  Serial.println("Help");
  Serial.println("------------------");
  switch (m) {
    case 0:
      Serial.println("1 = Stop Motor");
      Serial.println("2 = Toggle Motor State");
      //Serial.println("3 = cmd#3");
      //Serial.println("4 = cmd#4");
      //Serial.println("5 = cmd#5");
      break;
    default:
      break;
  }
  Serial.println("------------------");
}
