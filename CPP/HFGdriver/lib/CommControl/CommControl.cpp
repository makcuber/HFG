//CommControl

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
 * DC: 6/15/10/2016
 * UP: 1/17/10/2016
 * UP: 2/18/10/2016
 * UD: 6/12/11/2016
 * UD: 7/13/11/2016
 * UD: 1/14/11/2016
 * ---------------
 * Dev: Add your name here
 * UP: Date you made changes
 * ---------------
*/

#include "CommControl.h"

//Communications

CommControl::CommControl(){
  int tmp[]={300,1200,2400,4800,9600,19200};
  for(int i=0;i<MAX_BAUD;i++){
    baudRates[i]=tmp[i];
  }
  btEnabled = true;
}

void CommControl::reconnectComm(int comm) {
  disconnectComm(comm);
  connectComm(comm);
}
void CommControl::connectComm(int comm) {
  switch (comm) {
    case 0:
      Serial.begin(commBaud[0]);
      serialState[0] = Serial.available();
      break;
    case 1:
      Serial1.begin(commBaud[1]);
      serialState[1] = Serial1.available();
      break;
    case 2:
      Serial2.begin(commBaud[2]);
      serialState[2] = Serial2.available();
      break;
    case 3:
      Serial3.begin(commBaud[3]);
      serialState[3] = Serial3.available();
      break;
    default:
      break;
  }
}
bool CommControl::getCommStatus(int comm) {
  switch (comm) {
    case 0:
      serialState[0] = Serial.available();
      return Serial.available();
      break;
    case 1:
      serialState[1] = Serial1.available();
      return Serial1.available();
      break;
    case 2:
      serialState[2] = Serial2.available();
      return Serial2.available();
      break;
    case 3:
      serialState[3] = Serial3.available();
      return Serial3.available();
      break;
    default:
      return false;
      break;
  }
}
void CommControl::disconnectComm(int comm) {
  switch (comm) {
    case 0:
      Serial.end();
      serialState[0] = Serial.available();
      break;
    case 1:
      Serial1.end();
      serialState[1] = Serial1.available();
      break;
    case 2:
      Serial2.end();
      serialState[2] = Serial2.available();
      break;
    case 3:
      Serial3.end();
      serialState[3] = Serial3.available();
      break;
    default:
      break;
  }
}
void CommControl::setAllCommBaud(int baud) {
  for (int i = 0; i < MAX_COMMS; i++) {
    commBaud[i] = baud;
  }
}
void CommControl::reconnectAllComms() {
  for (int i = 0; i < MAX_COMMS; i++) {
    reconnectComm(i);
  }
}
void CommControl::connectAllComms() {
  for (int i = 0; i < MAX_COMMS; i++) {
    connectComm(i);
  }
}
void CommControl::disconnectAllComms() {
  for (int i = 0; i < MAX_COMMS; i++) {
    disconnectComm(i);
  }
}

//Default Run Mode

void CommControl::comm2Comm(int commA, int commB, char mode) {
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

int CommControl::SerialReadB(int comm) {
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
      break;
  }
  return -1;
}
void CommControl::SerialWriteB(int comm, int msg) {
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
String CommControl::SerialReadS(int comm) {
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
      }
    default:
      break;
  }
  return "";
}
void CommControl::SerialWriteS(int comm, String msg) {
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
String CommControl::SerialReadUntil(int comm, char c) {
  switch (comm) {
    case 0:
      if (getCommStatus(comm)) {
        return Serial.readStringUntil(c);
      }
      break;
    case 1:
      if (getCommStatus(comm)) {
        return Serial1.readStringUntil(c);
      }
      break;
    case 2:
      if (getCommStatus(comm)) {
        return Serial2.readStringUntil(c);
      }
      break;
    case 3:
      if (getCommStatus(comm)) {
        return Serial3.readStringUntil(c);
        break;
      }
    default:
      break;
  }
  return "";
}
