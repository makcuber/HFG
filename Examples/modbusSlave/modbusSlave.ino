#include <modbus.h>
002
#include <modbusDevice.h>
003
#include <modbusRegBank.h>
004
#include <modbusSlave.h>
005
 
006
/* PINS
007
Add more registers if needed
008
Digital input pins 2,3,4,5,6,7
009
Digital output pins 8,9,12,13
010
Analog output pins 10,11 (PWM)
011
Analog input pins 0,1,2,3,4,5
012
*/
013
 
014
 
015
modbusDevice regBank;
016
modbusSlave slave;
017
 
018
int AI0,AI1,AI2,AI3,AI4,AI5;
019
 
020
 
021
void setup()
022
{   
023
  regBank.setId(10); ///Set Slave ID
024
 
025
//Add Digital Input registers
026
  regBank.add(10002);
027
  regBank.add(10003);
028
  regBank.add(10004);
029
  regBank.add(10005);
030
  regBank.add(10006);
031
  regBank.add(10007);
032
// Add Digital Output registers
033
  regBank.add(8);
034
  regBank.add(9);
035
  regBank.add(12);
036
  regBank.add(13);
037
//Analog input registers
038
  regBank.add(30001);
039
  regBank.add(30002);
040
  regBank.add(30003);
041
  regBank.add(30004);
042
  regBank.add(30005);
043
  regBank.add(30006);
044
//Analog Output registers
045
  regBank.add(40010);  
046
  regBank.add(40011);  
047
 
048
  slave._device = &regBank;  
049
  slave.setBaud(9600);   
050
   
051
  pinMode(2,INPUT);
052
  pinMode(3,INPUT);
053
  pinMode(4,INPUT);
054
  pinMode(5,INPUT);
055
  pinMode(6,INPUT);
056
  pinMode(7,INPUT);
057
  pinMode(8,OUTPUT);
058
  pinMode(9,OUTPUT);
059
  pinMode(12,OUTPUT);
060
  pinMode(13,OUTPUT);
061
    
062
}
063
void loop(){
064
 
065
  while(1){   
066
  //Digital Input
067
    byte DI2 = digitalRead(2);
068
    if (DI2 >= 1)regBank.set(10002,1);
069
    if (DI2 <= 0)regBank.set(10002,0);
070
    byte DI3 = digitalRead(3);
071
    if (DI3 >= 1)regBank.set(10003,1);
072
    if (DI3 <= 0)regBank.set(10003,0);
073
    byte DI4 = digitalRead(4);
074
    if (DI4 >= 1)regBank.set(10004,1);
075
    if (DI4 <= 0)regBank.set(10004,0);
076
    byte DI5 = digitalRead(5);
077
    if (DI5 >= 1)regBank.set(10005,1);
078
    if (DI5 <= 0)regBank.set(10005,0);
079
    byte DI6 = digitalRead(6);
080
    if (DI6 >= 1)regBank.set(10006,1);
081
    if (DI6 <= 0)regBank.set(10006,0);
082
    byte DI7 = digitalRead(7);
083
    if (DI7 >= 1)regBank.set(10007,1);
084
    if (DI7 <= 0)regBank.set(10007,0);
085
                                 
086
  //Digital output
087
    int DO8 = regBank.get(8);
088
      if (DO8 <= 0 && digitalRead(8) == HIGH)digitalWrite(8,LOW);
089
      if (DO8 >= 1 && digitalRead(8) == LOW)digitalWrite(8,HIGH);
090
    int DO9 = regBank.get(9);
091
      if (DO9 <= 0 && digitalRead(9) == HIGH)digitalWrite(9,LOW);
092
      if (DO9 >= 1 && digitalRead(9) == LOW)digitalWrite(9,HIGH);
093
    int DO12 = regBank.get(12);
094
      if (DO12 <= 0 && digitalRead(12) == HIGH)digitalWrite(12,LOW);
095
      if (DO12 >= 1 && digitalRead(12) == LOW)digitalWrite(12,HIGH);
096
    int DO13 = regBank.get(13);
097
      if (DO13 <= 0 && digitalRead(13) == HIGH)digitalWrite(13,LOW);
098
      if (DO13 >= 1 && digitalRead(13) == LOW)digitalWrite(13,HIGH);
099
             
100
  //Analog input  ***READ Twice deliberately
101
    AI0 = analogRead(0);
102
    delay(10);
103
    AI0 = analogRead(0);
104
    regBank.set(30001, (word) AI0);
105
    delay(10);
106
     
107
    AI1 = analogRead(1);
108
    delay(10);
109
    AI1 = analogRead(1);
110
    regBank.set(30002, (word) AI1);
111
    delay(10);
112
     
113
    AI2 = analogRead(2);
114
    delay(10);
115
    AI2 = analogRead(2);
116
    regBank.set(30003, (word) AI2);
117
    delay(10);
118
     
119
    AI3 = analogRead(3);
120
    delay(10);
121
    AI3 = analogRead(3);
122
    regBank.set(30004, (word) AI3);
123
    delay(10);
124
     
125
    AI4 = analogRead(4);
126
    delay(10);
127
    AI4 = analogRead(4);
128
    regBank.set(30005, (word) AI4);
129
    delay(10);
130
     

    AI5 = analogRead(5);

    delay(10);

    AI5 = analogRead(5);

    regBank.set(30006, (word) AI5);

    delay(10);

         

  //Analog output 

    word AO10 = regBank.get(40010);

    analogWrite(10,AO10);

    delay(10);
    word AO11 = regBank.get(40011)
    analogWrite(11,AO11);

    delay(10);

  slave.run();  

  }

}

