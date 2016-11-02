#ifndef OPC_H
#define OPC_H

#include <Arduino.h>
#include <Bridge.h>
#include <Ethernet.h>
#include <SPI.h>
#include <VerboseControl.h>

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
  VerboseControl *verboseControl;
  OPC(VerboseControl *vc);
  struct OPCItemType {
    char *itemID;
    opcAccessRights opcAccessRight;
    opctypes itemType;
    unsigned int ptr_callback;
  };
  OPCItemType *OPCItemList;
  void addItem(const char *itemID, opcAccessRights opcAccessRight, opctypes opctype, bool (*function)(const char *itemID, const opcOperation opcOP, const bool value));
  void addItem(const char *itemID, opcAccessRights opcAccessRight, opctypes opctype, byte (*function)(const char *itemID, const opcOperation opcOP, const bool value));
  void addItem(const char *itemID, opcAccessRights opcAccessRight, opctypes opctype, int (*function)(const char *itemID, const opcOperation opcOP, const bool value));
  void addItem(const char *itemID, opcAccessRights opcAccessRight, opctypes opctype, float (*function)(const char *itemID, const opcOperation opcOP, const bool value));
};

class OPCSerial : public OPC {
protected:
  void sendOPCItemsMap();
public:
  CommControl *commControl;
  int *commID;
  OPCSerial(VerboseControl *vc, CommControl *cc, int *ID);
  void setup();
  void processOPCCommands();
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
  OPCEthernet(VerboseControl *vc);
  int  setup(uint8_t listen_port, uint8_t *mac_address);
  void setup(uint8_t listen_port, uint8_t *mac_address, IPAddress local_ip);
  void setup(uint8_t listen_port, uint8_t *mac_address, IPAddress local_ip, IPAddress dns_server);
  void setup(uint8_t listen_port, uint8_t *mac_address, IPAddress local_ip, IPAddress dns_server, IPAddress gateway);
  void setup(uint8_t listen_port, uint8_t *mac_address, IPAddress local_ip, IPAddress dns_server, IPAddress gateway, IPAddress subnet);
  void processOPCCommands();
};

#endif
