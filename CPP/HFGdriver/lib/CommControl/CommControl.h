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
 * UD: 3/02/11/2016
 * UD: 4/03/11/2016
 * UD: 6/12/11/2016
 * UD: 3/16/11/2016
 * UD: 5/25/11/2016
 * UD: 4/1/12/2016
 * ---------------
 * Dev: Add your name here
 * UP: Date you made changes
 * ---------------
*/

#ifndef __CommControl_H_defined__
#define __CommControl_H_defined__

#include <Arduino.h>

#define MAX_COMMS 4
#define MAX_BAUD 6
#define SERIAL_BUFFER 128

enum channelType{
  usbChannel,
  bluetoothChannel,
  wifiChannel,
  ethernetChannel
};

class CommControl{
  public:
    //Inherited objects
    int OPC_CHANNEL;

    //Serial variables
    int commBaud[MAX_COMMS];
    int baudRates[MAX_BAUD];
    bool commCmd[MAX_COMMS];
    bool btEnabled;

    //values - place class variables here

    CommControl();

    void comm2Comm(int commA, int commB, char mode);

    int SerialReadB(int comm);
    void SerialWriteB(int comm, int msg);
    String SerialReadS(int comm);
    void SerialWriteS(int comm, String msg);
    String SerialReadUntilS(int comm, char c);
    String SerialReadUntilC(int *comm, char *d);

    void reconnectComm(int comm);
    void connectComm(int comm);
    bool getCommStatus(int comm);
    void disconnectComm(int comm);
    void setAllCommBaud(int baud);
    void reconnectAllComms();
    void connectAllComms();
    void disconnectAllComms();

  private:
    char buffer[SERIAL_BUFFER + 1];
};
#endif
