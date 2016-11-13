//Command Control

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
 * UD: 4/03/11/2016
 * UD: 6/12/11/2016
 * ---------------
 * Dev: Add your name here
 * UP: Date you made changes
 * ---------------
*/

#ifndef __CommandControl_H_defined__
#define __CommandControl_H_defined__

#include <Arduino.h>
#include <VerboseControl.h>
#include <CommControl.h>
#include <MotorControl.h>
#include <BootControl.h>
//#include <opcControl.h>

class CommandControl {
  public:
    //Inherited object
    CommControl *commControl;
    VerboseControl *verboseControl;
    MotorControl *motorControl;
    BootControl *bootControl;
    //opcControl *opcControl;

    //constants - declare values that will remain constant throughout the program here

    //values - place class variables here
    int mode;
    String cmdS,valS;
    int btMode;
    int usbMode;

    int usbChannel;
    int bluetoothChannel;

    bool opcEnabled;

    //Functions
    CommandControl(CommControl *cc, VerboseControl *vc, MotorControl *mc, BootControl *bc);

    void cmdSort(int mode, String cmdS, String valS);
    void btComm();
    void btcmd(String cmdS, String valS);
    void usbComm();
    void usbcmd(String cmdS, String valS);
  private:

};
#endif
