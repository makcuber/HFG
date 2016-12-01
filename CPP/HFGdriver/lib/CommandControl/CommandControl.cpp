//CommandContol

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
 * UD: 1/14/11/2016
 * UD: 2/15/11/2016
 * UD: 3/16/11/2016
 * UD: 1/21/11/2016
 * UP: 2/22/11/2016
 * UP: 3/23/11/2016
 * UD: 5/25/11/2016
 * UD: 2/29/11/2016
 * UP: 3/30/11/2016
 * ---------------
 * Dev: Add your name here
 * UP: Date you made changes
 * ---------------
*/

#include "CommandControl.h"

//
cmd::cmd(String *id, String *desc, int *callback){
  item=new menuItem(id,desc);
}

//

cmdGroup::cmdGroup(String *s, cmd *cmd0, VerboseControl *vc){
  cmds[0]=cmd0;
  name=*s;
  verboseControl=vc;
}
bool cmdGroup::swapCmdPos(int a, int b){
  if((a>=0)&(a<MAX_CMDS)){
    if((b>=0)&(b<MAX_CMDS)){
      cmd *tmpC=cmds[a];
      cmds[a]=cmds[b];
      cmds[b]=tmpC;
      delete tmpC;
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}
cmd *cmdGroup::CMD(int n){
  if((n>=0)&(n<MAX_CMDS)){
    return cmds[n];
  }
}
int cmdGroup::CmdCount(){
  return cmdCount;
}
void cmdGroup::PrintMenu() {
  verboseControl->verboseMsg("------------------");
  verboseControl->verboseMsg(name);
  verboseControl->verboseMsg("------------------");
  for(int i=0;i<CmdCount();i++){
    verboseControl->verboseMsg(CMD(i)->item->id+" = "+CMD(i)->item->description);
  }
  verboseControl->verboseMsg("------------------");
}

//Command Processing

CommandControl::CommandControl(CommControl *cc, VerboseControl *vc, MotorControl *mc, BootControl *bc, PatternControl *pc){
  commControl=cc;
  verboseControl=vc;
  motorControl=mc;
  bootControl=bc;
  patternControl=pc;

  mode = 0;

  for(int i=0;i<MAX_COMMS;i++){
    commControl->commCmd[i]=false;
    commMode[i]=0;
  }

  resetParameters();
  cmdS = "-1";
  valS = "-1";
}
void CommandControl::processCMDs(){
  for(int i=0;i<MAX_COMMS;i++){
    if(commControl->commCmd[i]){
      readComm(&i);
    }
  }
}
void CommandControl::cmdExe(String *input[], cmdGroup *cg) {
  for(int i=0;i<cg->CmdCount();i++){
    if (*input[0]==cg->CMD(i)->item->id) {
       verboseControl->verboseMsg(String(cg->name)+" cmd#"+String(i));
    }
  }
}
void CommandControl::resetParameters(){
  for(int i=0;i<MAX_PARAMETERS;i++){
    parameters[i]="";
  }
}
void CommandControl::cmdProcess(int *n, String *s){

}
void CommandControl::parseParameters(int *n, char *c){
  char *pt;
  pt = strtok (c,",");
  while (pt != NULL) {
      int a = atoi(pt);
      printf("%d\n", a);
      pt = strtok (NULL, ",");
  }
}
void CommandControl::readComm(int *n) {
  String tmpS;
  while (commControl->getCommStatus(*n)) {
    tmpS=commControl->SerialReadUntilC(n, &delimiter[*n]);
  }

  cmdProcess(n, &tmpS);
  //reset the cmd and val variables for the next cycle
  resetParameters();
}
void CommandControl::cmdSort(int mode, String cmdS, String valS) {
  switch (mode) {
    case 0:
      //verboseControl->verboseMsg("commMode#0");
      usbcmd(cmdS, valS);
      break;
    case 1:
      //verboseControl->verboseMsg("commMode#1");
      //btcmd(cmdS, valS);
      break;
    case 2:
      //verboseControl->verboseMsg("commMode#2");
      break;
    case 3:
      //verboseControl->verboseMsg("commMode#3");
      break;
    case 4:
      //verboseControl->verboseMsg("commMode#4");
      break;
    case 5:
      //verboseControl->verboseMsg("commMode#5");
      break;
    default:
      //WARNING: code placed here will run on every cycle that you dont send a command
      break;
  }
}
void CommandControl::btComm() {
  //String cmdS,valS;
  while (commControl->getCommStatus(bluetoothChannel)) {
    cmdS = commControl->SerialReadUntilS(bluetoothChannel,',');
    valS = commControl->SerialReadUntilS(bluetoothChannel,'\n');
  }

  cmdSort(commMode[1], cmdS, valS);

  //reset the cmd and val variables for the next cycle
  cmdS = "-1";
  valS = "-1";
}
void CommandControl::usbComm() {
  while (Serial.available()) {
    cmdS = Serial.readStringUntil(',');
    valS = Serial.readStringUntil('\n');
  }

  cmdSort(commMode[0], cmdS, valS);

  //reset the cmd and val variables for the next cycle
  cmdS = "-1";
  valS = "-1";
}
void CommandControl::usbcmd(String cmdS, String valS) {
  int cmd = cmdS.toInt();
  int val = valS.toInt();
  switch (cmd) {
    case 0:
      verboseControl->verboseMsg("USB cmd#0");
      verboseControl->showMenu(commMode[0]);
      break;
    case 1:
     verboseControl->verboseMsg("USB cmd#1");
      motorControl->killAll();
      break;
    case 2:
     verboseControl->verboseMsg("USB cmd#2");
      motorControl->toggleMotor(0);
      break;
    case 3:
     verboseControl->verboseMsg("USB cmd#3");
     if(verboseControl->verboseLevel[*opcChannel]>0){
       verboseControl->setVerboseLevel(0, *opcChannel);
     }else{
       verboseControl->setVerboseLevel(1,*opcChannel);
     }
     verboseControl->verboseMsg("Comm #"+String(*opcChannel)+" Verbose Level set to: "+String(verboseControl->verboseLevel[*opcChannel]));

     break;
    case 4:
     verboseControl->verboseMsg("USB cmd#4");
     motorControl->setMotorState(val, true);
      break;
    case 5:
      verboseControl->verboseMsg("USB cmd#5");
      verboseControl->clearConsole();
      break;
    case 6:
      verboseControl->verboseMsg("USB cmd#6");
      if(val>=0){
        bootControl->reset(val);
      } else {
        bootControl->reset(0);
      }
      break;
    case 7:
      verboseControl->verboseMsg("USB cmd#7");
      motorControl->toggleAll();
      break;
    case 8:
      verboseControl->verboseMsg("USB cmd#8");
      if(val>0){
        patternControl->runOnOff(val,0);
      }else{
        patternControl->runOnOff(0);
      }
      break;
    case 9:
      verboseControl->verboseMsg("USB cmd#9");
      if(val>0){
        patternControl->runOnOff(val,1);
      }else{
        patternControl->runOnOff(1);
      }
      break;
    case 10:
      verboseControl->verboseMsg("USB cmd#10");
      if(val>0){
        patternControl->runOnOff(val,2);
      }else{
        patternControl->runOnOff(2);
      }
      break;
    default:
      //WARNING: code placed here will run on every cycle that you dont send a command
      break;
  }
}
