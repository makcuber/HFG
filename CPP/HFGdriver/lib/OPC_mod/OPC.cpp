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
 * UD: 2/15/11/2016
 * UP: 3/30/11/2016
 * ---------------
 * Dev: Add your name here
 * UP: Date you made changes
 * ---------------
*/

#include <OPC.h>
#include <Arduino.h>
#include <HardwareSerial.h>
#include <Ethernet.h>

/************************************* OPC */

OPC::OPC(VerboseControl *vc) : OPCItemList(NULL) ,  OPCItemsCount(0)  {
  verboseControl=vc;
}

void OPC::addItem(const char *itemID, opcAccessRights opcAccessRight, opctypes opctype, bool (*function)(const char *itemID, const opcOperation opcOP, const bool value))
{
  internaladdItem(itemID, opcAccessRight, opctype, int(&function));
}

void OPC::addItem(const char *itemID, opcAccessRights opcAccessRight, opctypes opctype, byte (*function)(const char *itemID, const opcOperation opcOP, const byte value))
{
  internaladdItem(itemID, opcAccessRight, opctype, int(&function));
}

void OPC::addItem(const char *itemID, opcAccessRights opcAccessRight, opctypes opctype,  int (*function)(const char *itemID, const opcOperation opcOP, const int value))
{
  internaladdItem(itemID, opcAccessRight, opctype, int(&function));
}

void OPC::addItem(const char *itemID, opcAccessRights opcAccessRight, opctypes opctype,  float (*function)(const char *itemID, const opcOperation opcOP, const float value))
{
  internaladdItem(itemID, opcAccessRight, opctype, int(&function));
}

void OPC::internaladdItem(const char *itemID, opcAccessRights opcAccessRight, opctypes opctype,  int callback_function)
{
  OPCItemList = (OPCItemType *) realloc(OPCItemList, (OPCItemsCount + 1) * sizeof(OPCItemType));
  if (OPCItemList != NULL) {
    OPCItemList[OPCItemsCount].itemType = opctype;

    OPCItemList[OPCItemsCount].itemID = (char *) malloc(strlen(itemID)+1);
    strncpy(&OPCItemList[OPCItemsCount].itemID[0], itemID, strlen(itemID)+1);

    OPCItemList[OPCItemsCount].opcAccessRight = opcAccessRight;
    OPCItemList[OPCItemsCount].ptr_callback = callback_function;
    OPCItemsCount++;
  } else {
     verboseControl->verboseMsg("Not enough memory");
  }

}

/************************************* OPCSerial */

void OPCSerial::setup() {}

void OPCSerial::sendOPCItemsMap()
{
  String str;
  str+=String("<0");

  for(int k=0;k<OPCItemsCount;k++) {
    str+=String(",");
    str+=String(OPCItemList[k].itemID);
    str+=String(",");
    str+=String(int(OPCItemList[k].opcAccessRight));
    str+=String(",");
    str+=String(int(OPCItemList[k].itemType));
  }

  str+=String(">");
  verboseControl->debugMsg("OPCItems Map: "+str);
  commControl->SerialWriteS(commID,str);
}

OPCSerial::OPCSerial(VerboseControl *vc, CommControl *cc, int ID) : OPC(vc)  {
  buffer[0] = '\0';
  commControl=cc;
  commID=ID;
}

void OPCSerial::processOPCCommands() {
  bool matched = false;
  char *p,*j;

  bool (*bool_callback)(const char *itemID, const opcOperation opcOP, const bool value);
  byte (*byte_callback)(const char *itemID, const opcOperation opcOP, const byte value);
  int (*int_callback)(const char *itemID, const opcOperation opcOP, const int value);
  float (*float_callback)(const char *itemID, const opcOperation opcOP, const float value);

  while (commControl->getCommStatus(commID)) {
    char inChar = commControl->SerialReadB(commID);

    verboseControl->debugMsg("1 OPC inChar: "+String(inChar));

    if (inChar == '\r') {
      verboseControl->debugMsg("2 OPC Buffer: "+String(buffer));
      if (buffer[0] == '\0')
        sendOPCItemsMap();
      else {
        // Lets search for read
        verboseControl->debugMsg("3 OPC Buffer Old: "+String(buffer));

        //Shift buffer back 1 position to overwrite a random '\r' that appears
        /*
        char c[SERIALCOMMAND_BUFFER+1];
        for(int i=1;i<SERIALCOMMAND_BUFFER+1;i++){
          c[i-1]=buffer[i];
        }
        strcpy(buffer, c);
        //delete[] c;
        */
        
        verboseControl->debugMsg("4 OPC Buffer New: "+String(buffer));
        for (int i = 0; i < OPCItemsCount; i++) {
          //verboseControl->debugMsg("OPC Read Item Tested: "+String(OPCItemList[i].itemID));

         if (!strncmp(buffer, OPCItemList[i].itemID, SERIALCOMMAND_MAXCOMMANDLENGTH)) {
          verboseControl->debugMsg("5 OPC Item ID: "+String(OPCItemList[i].itemID));
          verboseControl->debugMsg("6 OPC Item Type: "+String(OPCItemList[i].itemType));
          // Execute the stored handler function for the command
          switch (OPCItemList[i].itemType) {
            case opc_bool :

                      bool_callback = (bool (*)(const char *itemID, const opcOperation opcOP, const bool value))(OPCItemList[i].ptr_callback);
                      verboseControl->debugMsg("7 OPC bool");
                      Serial.println(bool_callback(OPCItemList[i].itemID,opc_opread,NULL));

                      break;
            case opc_byte :
                      byte_callback = (byte (*)(const char *itemID, const opcOperation opcOP, const byte value))(OPCItemList[i].ptr_callback);
                      Serial.println(byte_callback(OPCItemList[i].itemID,opc_opread,NULL));
                      verboseControl->debugMsg("7 OPC byte");
                      break;
            case opc_int :
                      int_callback = (int (*)(const char *itemID, const opcOperation opcOP, const int value))(OPCItemList[i].ptr_callback);
                      Serial.println(int_callback(OPCItemList[i].itemID,opc_opread,NULL));
                      verboseControl->debugMsg("7 OPC int");
                      break;
            case opc_float :
                      float_callback = (float (*)(const char *itemID, const opcOperation opcOP, const float value))(OPCItemList[i].ptr_callback);
                      Serial.println(float_callback(OPCItemList[i].itemID,opc_opread,NULL));
                      verboseControl->debugMsg("7 OPC float");
                      break;
          }

          matched = true;
          break;
          } /* endif */
        } /* endfor */

        if (!matched) {
          // Lets search for write
          verboseControl->debugMsg("7 OPC Buffer: "+String(buffer));
          p = strtok_r(buffer,"=",&j);
          verboseControl->debugMsg("8 OPC Write CMD: "+String(p));
          for (int i = 0; i < OPCItemsCount; i++) {
            //verboseControl->debugMsg("OPC Write Item Tested: "+String(OPCItemList[i].itemID));
            if (!strncmp(p, OPCItemList[i].itemID, SERIALCOMMAND_MAXCOMMANDLENGTH)) {
              verboseControl->debugMsg("9 OPC Item: "+String(OPCItemList[i].itemID));
              // Call the stored handler function for the command
              switch (OPCItemList[i].itemType) {
                case opc_bool :
                        bool_callback = (bool (*)(const char *itemID, const opcOperation opcOP, const bool value))(OPCItemList[i].ptr_callback);
                        verboseControl->debugMsg("10 OPC Write Value: "+String(atoi(j)));
                        bool_callback(OPCItemList[i].itemID,opc_opwrite,atoi(j));
                        break;
                case opc_byte :
                        byte_callback = (byte (*)(const char *itemID, const opcOperation opcOP, const byte value))(OPCItemList[i].ptr_callback);
                        verboseControl->debugMsg("11 OPC Write Value: "+String(atoi(j)));
                        byte_callback(OPCItemList[i].itemID,opc_opwrite,atoi(j));
                        break;
                case opc_int :
                        int_callback = (int (*)(const char *itemID, const opcOperation opcOP, const int value))(OPCItemList[i].ptr_callback);
                        verboseControl->debugMsg("12 OPC Write Value: "+String(atoi(j)));
                        int_callback(OPCItemList[i].itemID,opc_opwrite,atoi(j));
                        break;
                case opc_float :
                        float_callback = (float (*)(const char *itemID, const opcOperation opcOP, const float))(OPCItemList[i].ptr_callback);
                        verboseControl->debugMsg("13 OPC Write Value: "+String(atof(j)));
                        float_callback(OPCItemList[i].itemID,opc_opwrite,atof(j));
                        break;
              }

              break;
            } /* endif */
          } /* endfor */
        }
      }

      buffer[0] = '\0';
      bufPos = 0;
    }
    else {
      if (bufPos < SERIALCOMMAND_BUFFER) {
        buffer[bufPos++] = inChar;
        buffer[bufPos] = '\0';
        verboseControl->debugMsg("14 OPC Buffer: "+String(buffer));
        verboseControl->debugMsg("15 OPC Buffer Position: "+String(bufPos));
      }
    }
  }
}

/************************************* OPCEthernet */

OPCEthernet::OPCEthernet(VerboseControl *vc) : OPC(vc) {}

void OPCEthernet::after_setup(uint8_t listen_port)
{
  internal_ethernet_server = new EthernetServer(listen_port);
  internal_ethernet_server->begin();
}

int OPCEthernet::setup(uint8_t listen_port, uint8_t *mac_address)
{
  Ethernet.begin(mac_address);
  after_setup(listen_port);
}

void OPCEthernet::setup(uint8_t listen_port, uint8_t *mac_address, IPAddress local_ip)
{
  Ethernet.begin(mac_address,local_ip);
  after_setup(listen_port);
}

void OPCEthernet::setup(uint8_t listen_port, uint8_t *mac_address, IPAddress local_ip, IPAddress dns_server)
{
  Ethernet.begin(mac_address,local_ip,dns_server);
  after_setup(listen_port);
}

void OPCEthernet::setup(uint8_t listen_port, uint8_t *mac_address, IPAddress local_ip, IPAddress dns_server, IPAddress gateway)
{
  Ethernet.begin(mac_address,local_ip,dns_server,gateway);
  after_setup(listen_port);
}

void OPCEthernet::setup(uint8_t listen_port, uint8_t *mac_address, IPAddress local_ip, IPAddress dns_server, IPAddress gateway, IPAddress subnet)
{
  Ethernet.begin(mac_address,local_ip,dns_server,gateway,subnet);
  after_setup(listen_port);
}

void OPCEthernet::sendOPCItemsMap()
{
  buffer[0]='\0';
  strcat(buffer,"{\"ItemsMap\":[");

  for(int k=0;k<OPCItemsCount;k++) {
    if (k) strcat(buffer,",");

    strcat(buffer,"{\"ItemId\":\"");
    strcat(buffer,OPCItemList[k].itemID);
    strcat(buffer,"\",\"AccessRight\":\"");

    bufPos = strlen(buffer);
    buffer[bufPos] = 48 + int(OPCItemList[k].opcAccessRight);
    buffer[bufPos+1] = '\0';

    strcat(buffer,"\",\"ItemType\":\"");

    bufPos = strlen(buffer);
    buffer[bufPos] = 48 + int(OPCItemList[k].itemType);
    buffer[bufPos+1] = '\0';

    strcat(buffer,"\"}");

    if (k==OPCItemsCount-1) strcat(buffer,"]");

    client.write((unsigned char *) buffer,strlen(buffer));
    buffer[0]='\0';
  }

  client.write((unsigned char *) "}",1);
}

void OPCEthernet::processClientCommand()
{
  char *p,*j;
  bool matched = false;
  bool (*bool_callback)(const char *itemID, const opcOperation opcOP, const bool value);
  byte (*byte_callback)(const char *itemID, const opcOperation opcOP, const byte value);
  int (*int_callback)(const char *itemID, const opcOperation opcOP, const int value);
  float (*float_callback)(const char *itemID, const opcOperation opcOP, const float value);

  client.println(F("HTTP/1.1 200 OK\r\nContent-Type: text/json\r\nConnection: close\r\n"));

  if (!strcmp(buffer, "itemsmap")) {
    sendOPCItemsMap();
  }
  else
  {
    p = strtok_r(buffer,"=",&j);
    if (!j[0])  {
      for (int i = 0; i < OPCItemsCount; i++) {
        if (!strcmp(buffer, OPCItemList[i].itemID))  {
          // Execute the stored handler function for the command
          client.print(F("{\"ItemId\":\""));
          client.print(buffer);
          client.print(F("\",\"ItemValue\":\""));

          switch (OPCItemList[i].itemType) {
            case opc_bool :
              bool_callback = (bool (*)(const char *itemID, const opcOperation opcOP, const bool value))(OPCItemList[i].ptr_callback);
              client.print(bool_callback(OPCItemList[i].itemID,opc_opread,NULL));
              break;
            case opc_byte :
              byte_callback = (byte (*)(const char *itemID, const opcOperation opcOP, const byte value))(OPCItemList[i].ptr_callback);
              client.print(byte_callback(OPCItemList[i].itemID,opc_opread,NULL));
              break;
            case opc_int :
              int_callback = (int (*)(const char *itemID, const opcOperation opcOP, const int value))(OPCItemList[i].ptr_callback);
              client.print(int_callback(OPCItemList[i].itemID,opc_opread,NULL));
              break;
            case opc_float :
              float_callback = (float (*)(const char *itemID, const opcOperation opcOP, const float value))(OPCItemList[i].ptr_callback);
              client.print(float_callback(OPCItemList[i].itemID,opc_opread,NULL));
              break;
          } /* end switch */

          client.print(F("\"}"));

          matched = true;
          break;
        } /* end if */
      } /* end for */
    } /* end if */
    else
    {
      for (int i = 0; i < OPCItemsCount; i++) {
        if (!strcmp(buffer, OPCItemList[i].itemID))  {

          // Call the stored handler function for the command
          switch (OPCItemList[i].itemType) {
          case opc_bool :
                  bool_callback = (bool (*)(const char *itemID, const opcOperation opcOP, const bool value))(OPCItemList[i].ptr_callback);
                  bool_callback(OPCItemList[i].itemID,opc_opwrite,atoi(j));
                  break;
          case opc_byte :
                  byte_callback = (byte (*)(const char *itemID, const opcOperation opcOP, const byte value))(OPCItemList[i].ptr_callback);
                  byte_callback(OPCItemList[i].itemID,opc_opwrite,atoi(j));
                  break;
          case opc_int :
                  int_callback = (int (*)(const char *itemID, const opcOperation opcOP, const int value))(OPCItemList[i].ptr_callback);
                  int_callback(OPCItemList[i].itemID,opc_opwrite,atoi(j));
                  break;
          case opc_float :
                  float_callback = (float (*)(const char *itemID, const opcOperation opcOP, const float))(OPCItemList[i].ptr_callback);
                  float_callback(OPCItemList[i].itemID,opc_opwrite,atof(j));
                  break;
          } /* end case */

          matched = true;
          break;
        } /* end if */
      } /* end for */
    } /* end else */
  } /* end else */
}

void OPCEthernet::processOPCCommands()
{
  client = internal_ethernet_server->available();

  if (client) {
    boolean currentLineIsBlank = true;

    byte s = 0;
    boolean responsed = false;

    while (!responsed && client.connected()) {
      if (client.available()) {
        char c = client.read();

        if (c == '\n' && currentLineIsBlank) {
          processClientCommand();
          responsed = true;
        }
        else if (c == '\n') {
          currentLineIsBlank = true;
        }
        else if (c != '\r') {
          currentLineIsBlank = false;

          switch (s) {
            case 0 : if (c == 'G') s++; break;
            case 1 : if (c == 'E') s++; else s = 0; break;
            case 2 : if (c == 'T') s++; else s = 0; break;
            case 3 : if (c == ' ') s++; else s = 0; break;
            case 4 : if (c == '/') { s++; bufPos = 0;} else s = 0; break;
            case 5 : if (c != ' ') {
                      buffer[bufPos++] = c;
                      buffer[bufPos] = '\0';
                      }
                      else s = 0;
          }
        }
      }
    }
    delay(1); // Espera para dar tiempo al navegador a recibir los datos.
    client.stop(); // Cierra la conexión.
  }
}
