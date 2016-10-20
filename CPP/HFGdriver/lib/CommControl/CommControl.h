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
 * ---------------
 * Dev: Add your name here
 * UP: Date you made changes
 * ---------------
*/

#ifndef __CommControl_H_defined__
#define __CommControl_H_defined__

#include <Arduino.h>

class CommControl{
  public:
    //Inherited objects

    //Constants
    static const int maxComms = 4;
    static const int maxBaud = 6;

    //Serial variables
    int commBaud[maxComms];
    int baudRates[maxBaud];
    bool btEnabled;

    //values - place class variables here
    bool commState[maxComms];
    String cmdS;
    String valS;

    CommControl();

    void comm2Comm(int commA, int commB, char mode);

    int SerialReadB(int comm);
    void SerialWriteB(int comm, int msg);
    String SerialReadS(int comm);
    void SerialWriteS(int comm, String msg);

    void reconnectComm(int comm);
    void connectComm(int comm);
    bool getCommStatus(int comm);
    void disconnectComm(int comm);
    void setAllCommBaud(int baud);
    void reconnectAllComms();
    void connectAllComms();
    void disconnectAllComms();

  private:

};
#endif