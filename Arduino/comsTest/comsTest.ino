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
bool motorChangeVerbose=false;
bool btVerbose = false;
bool verboseEnabled[maxComms];
bool commState[maxComms];

//Serial variables
String cmdS;
String valS;
int mode = 1;

void clusterfuck() {
  verboseMsg("Gabe made me write this function");
}

void setup() {
  //put your setup code here, to run once:

  //enable serial communications
  Serial.begin(9600);
  Serial1.begin(9600);

  //set comm port states
  commState[0] = Serial.available();
  commState[1] = Serial1.available();
  commState[2] = Serial2.available();
  commState[3] = Serial3.available();

  verboseEnabled[0] = true;

  verboseMsg("Serial Communications Established");
  verboseMsg("---------------------------------");
  verboseMsg("CommPort\t|Status\t|Verbose");
  verboseMsg("---------------------------------");
  for (int i = 0; i < maxComms; i++) {
    verboseMsg("Comm#" + String(i) + "\t\t|" + String(commState[i])+ "\t|" + String(verboseEnabled[i]));
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
  
  for (int i = 0; i < maxMotors; i++) {

    //set motor pin number
    motorPin[i] = startMotorPin + i;

    //set pinmode for pin
    pinMode(motorPin[i], OUTPUT);

    //set starting motor state
    setMotorState(i, false);
    
    verboseMsg(String(i)+"\t|" + String(motorPin[i]) + "\t\t|" + String(motorState[i]));
  }
  verboseMsg("-----------------------------------");
  motorChangeVerbose=true;
  verboseMsg("Initialization COMPLETE\n");
  //clusterfuck();
}

void loop() {
  //USB Communication
  usbComm();
  //Bluetooth Communication
  btComm();
}

String SerialRead(int comm) {
  switch (comm) {
    case 0:
      return "";
      break;
    case 1:
      return Serial1.readStringUntil('\n');
      break;
    case 2:
      return "";
      break;
    case 3:
      return "";
      break;
    default:
      return "";
      break;
  }
}
void SerialWrite(int comm, String msg) {
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
      showHelp(btMode);
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
      if (btVerbose) {

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
      showHelp(usbMode);
      break;
    case 1:
      verboseMsg("USB cmd#1");
      setMotorState(0, false);
      break;
    case 2:
      verboseMsg("USB cmd#2");
      toggleMotor(0);
      break;
    case 3:
      verboseMsg("USB cmd#3");
      setBTverbose(true);
      break;
    case 4:
      verboseMsg("USB cmd#4");
      digitalWrite(motorPin[val], HIGH);
      break;
    case 5:
      verboseMsg("USB cmd#5");
      break;
    default:
      //WARNING: code placed here will run on every cycle that you dont send a command
      break;
  }
}

void verboseMsg(String msg) {
  if (verboseEnabled[0]) {
    Serial.println(msg);
  }
  if (verboseEnabled[1]) {
    Serial1.println(msg);
  }
  if (verboseEnabled[2]) {
    Serial.println(msg);
  }
}

void setBTverbose(bool state) {
  btVerbose = state;
}

void comm2Comm(String cmd, int commA, int commB) {

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
  if (motorChangeVerbose) {
    verboseMsg("Motor State Change");
    verboseMsg("------------------");
    verboseMsg("MotorPin:" + String(motorPin[motorID]));
    verboseMsg("MotorState:" + String(motorState[motorID]));
    verboseMsg("\n");
  }
}

void showHelp(int m) {
  verboseMsg("------------------");
  verboseMsg("Help");
  verboseMsg("------------------");
  switch (m) {
    case 0:
      verboseMsg("1 = Stop Motor");
      verboseMsg("2 = Toggle Motor State");
      verboseMsg("3 = Set BT verbose");
      verboseMsg("4 = Turn on motor x");
      //verboseMsg("5 = cmd#5");
      break;
    default:
      break;
  }
  verboseMsg("------------------");
}
