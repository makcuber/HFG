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
 * UD: 1/14/11/2016
 * UD: 2/15/11/2016
 * UD: 3/16/11/2016
 * UD: 1/21/11/2016
 * UP: 2/22/11/2016
 * UP: 3/23/11/2016
 * UD: 5/25/11/2016
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
#include <String.h>
//#include <opcControl.h>

#define MAX_CMDS 8
#define MAX_PARAMETERS 3

struct cmd{
  menuItem *item;
  int pnt_callback;
  cmd(String *id, String *desc, int *callback);
};

class cmdGroup{
  public:
    String name;
    VerboseControl *verboseControl;
    cmdGroup(String *s, cmd *cmd0, VerboseControl *vc);
    bool swapCmdPos(int a, int b);
    cmd *CMD(int n);
    int CmdCount();
    void PrintMenu();
  private:
    int cmdCount;
    cmd *cmds[MAX_CMDS];
};

class CommandControl {
  public:
    //Inherited object
    CommControl *commControl;
    VerboseControl *verboseControl;
    MotorControl *motorControl;
    BootControl *bootControl;
    //opcControl *opcControl;

    //values - place class variables here
    int mode;
    String cmdS,valS;
    int *opcChannel;

    String parameters[MAX_PARAMETERS];

    int commMode[MAX_COMMS];
    bool commCmd[MAX_COMMS];
    char seperator[MAX_COMMS];
    char delimiter[MAX_COMMS];
    bool opcEnabled;

    cmdGroup *internalCMDS;
    //Functions
    CommandControl(CommControl *cc, VerboseControl *vc, MotorControl *mc, BootControl *bc);

    void PrintCMDmenu(cmdGroup *cg);
    void cmdExe(String *input[], cmdGroup *cg);
    void processCMDs();

    void cmdSort(int mode, String cmdS, String valS);
    void btComm();
    void usbComm();
    void usbcmd(String cmdS, String valS);
  private:
    cmdGroup *motorCMDS;
    cmdGroup *verboseCMDS;
    cmdGroup *commCMDS;
    cmdGroup *bootCMDS;
    void readComm(int *n);
    void resetParameters();
    void parseParameters(int *n, char *c);
    void cmdProcess(int *n, String *s);
};
#endif
