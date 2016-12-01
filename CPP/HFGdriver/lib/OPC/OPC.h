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
 * DC: 2/01/11/2016
 * UD: 3/02/11/2016
 * UD: 4/03/11/2016
 * UD: 7/13/11/2016
 * UD: 1/14/11/2016
 * UP: 3/30/11/2016
 * UD: 4/1/12/2016
 * ---------------
 * Dev: Add your name here
 * UP: Date you made changes
 * ---------------
*/

#ifndef OPC_H
#define OPC_H

#include <Arduino.h>
#include <Bridge.h>
#include <Ethernet.h>
#include <SPI.h>

#define SERIALCOMMAND_MAXCOMMANDLENGTH 64
#define SERIALCOMMAND_BUFFER 128

enum opctypes{
  opc_bool,
  opc_byte,
  opc_int,
  opc_float
};

enum opcAccessRights{
  opc_read,
  opc_write,
  opc_readwrite
};

enum opcOperation{
  opc_opread,
  opc_opwrite,
};

class OPC {
private:
 void internaladdItem(const char *itemID, opcAccessRights opcAccessRight, opctypes opctype, int callback_function);
protected:
  byte OPCItemsCount;
  char buffer[SERIALCOMMAND_BUFFER + 1];
  byte bufPos;
public:
  OPC();
  struct OPCItemType {
    char *itemID;
    opcAccessRights opcAccessRight;
    opctypes itemType;
    unsigned int ptr_callback;
  };
  OPCItemType *OPCItemList;
  void addItem(const char *itemID, opcAccessRights opcAccessRight, opctypes opctype, bool  (*function)(const char *itemID, const opcOperation opcOP, const bool value));
  void addItem(const char *itemID, opcAccessRights opcAccessRight, opctypes opctype, byte  (*function)(const char *itemID, const opcOperation opcOP, const byte value));
  void addItem(const char *itemID, opcAccessRights opcAccessRight, opctypes opctype, int   (*function)(const char *itemID, const opcOperation opcOP, const int value));
  void addItem(const char *itemID, opcAccessRights opcAccessRight, opctypes opctype, float (*function)(const char *itemID, const opcOperation opcOP, const float value));
};

class OPCSerial : public OPC {
protected:
  void sendOPCItemsMap();
  void sendOPCItemsMapBT();
public:
  OPCSerial();
  void setup();
  void processOPCCommands();
  void processOPCCommandsBT();
};

class OPCEthernet : public OPC {
private:
  EthernetServer *internal_ethernet_server;
  EthernetClient client;
  void after_setup(uint8_t listen_port);
protected:
  void sendOPCItemsMap();
  void processClientCommand();
public:
  OPCEthernet();
  int  setup(uint8_t listen_port, uint8_t *mac_address);
  void setup(uint8_t listen_port, uint8_t *mac_address, IPAddress local_ip);
  void setup(uint8_t listen_port, uint8_t *mac_address, IPAddress local_ip, IPAddress dns_server);
  void setup(uint8_t listen_port, uint8_t *mac_address, IPAddress local_ip, IPAddress dns_server, IPAddress gateway);
  void setup(uint8_t listen_port, uint8_t *mac_address, IPAddress local_ip, IPAddress dns_server, IPAddress gateway, IPAddress subnet);
  void processOPCCommands();
};

#endif
