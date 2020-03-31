#include "cc1101_debug_service.h"
#include <Arduino.h>
#include <ELECHOUSE_CC1101_SRC_DRV.h>


static const char *Register[] = {

"IOCFG2",
"IOCFG1",
"IOCFG0",
"FIFOTHR",
"SYNC1",
"SYNC0",
"PKTLEN",
"PKTCTRL1",
"PKTCTRL0",
"ADDR",
"CHANNR",
"FSCTRL1",
"FSCTRL0",
"FREQ2",
"FREQ1",
"FREQ0",
"MDMCFG4",
"MDMCFG3",
"MDMCFG2",
"MDMCFG1",
"MDMCFG0",
"DEVIATN",
"MCSM2",
"MCSM1",
"MCSM0",
"FOCCFG",
"BSCFG",
"AGCCTRL2",
"AGCCTRL1",
"AGCCTRL0",
"WOREVT1",
"WOREVT0",
"WORCTRL",
"FREND1",
"FREND0",
"FSCAL3",
"FSCAL2",
"FSCAL1",
"FSCAL0",
"RCCTRL1",
"RCCTRL0",
"FSTEST",
"PTEST",
"AGCTEST",
"TEST2",
"TEST1",
"TEST0",
};

bool startup = 0;

//----------------------------------------------------
void CC1101_debug::debug(void){
if (startup == 0){
print_line(50);
Serial.println("CC1101 service/debug tool v0.1");
print_line(50);
show_version();
show_register();
startup = 1;
}

if (Serial.available() > 0){
String s = (Serial.readString());
char buf[4];
int val;

const char filter = '=';
int Low = s.indexOf(filter);
String s1 = s.substring(0, Low);
int High = s.indexOf(filter, Low+1);
String s2 = s.substring(Low+1, High);

s2.replace("\n", "");
s2.toCharArray(buf,4);
val = strtol(buf, 0, 16);

for (int i = 0; i<=46; i++){
String r = Register[i];
if (s1 == r+"?\n" && s2 == r+"?"){
print_line(30);
Serial.println("Read Register");
print_line(30);
print_register(i);
i = 47;
}
else if (s1 == r && val>= 0 && val<= 255){
print_line(30);
Serial.println("Write Register");
print_line(30);
ELECHOUSE_cc1101.SpiWriteReg(i,val);
print_register(i);
}
}
if (s == "reg\n"){show_register();}
else if (s == "ver\n"){show_version();}
else if (s1 == "mhz" && s2 != "mhz"){
float f = s2.toFloat();
print_line(30);
Serial.println("Write MHZ");
print_line(30);
ELECHOUSE_cc1101.setMHZ(f);
Serial.print("MHZ");
for (int i = 0; i<7; i++){
Serial.print(" ");}
Serial.println(f,3);
print_register(13);
print_register(14);
print_register(15);
}
else if (s == "mhz?\n"){
print_line(30);
Serial.println("Read MHZ");
print_line(30);
float f;
f = ELECHOUSE_cc1101.SpiReadStatus(13)*26;
f = ELECHOUSE_cc1101.SpiReadStatus(14)*0.1015625 + f;
f = ELECHOUSE_cc1101.SpiReadStatus(15)*0.00039675 + f;
Serial.print("MHZ");
for (int i = 0; i<7; i++){
Serial.print(" ");}
Serial.println(f,3);
print_register(13);
print_register(14);
print_register(15);
}
else if (s == "rx\n"){
print_line(30);
Serial.println("cc1101 RX");
ELECHOUSE_cc1101.SetRx();
}
else if (s == "tx\n"){
print_line(30);
Serial.println("cc1101 TX");
ELECHOUSE_cc1101.SetTx();
}
else if (s1 == "pa"){
val = s2.toInt(); 
print_line(30);
Serial.print("cc1101 PA ");
Serial.println(val);
ELECHOUSE_cc1101.setPA(val);
}
}
}
//----------------------------------------------------
void CC1101_debug::show_version(void){
print_line(30);
Serial.println("CC1101 Version");
print_line(30);
Serial.print("PARTNUM   ");
Serial.println(ELECHOUSE_cc1101.SpiReadStatus(0x30), HEX);
Serial.print("VERSION   ");
Serial.println(ELECHOUSE_cc1101.SpiReadStatus(0x31), HEX);
Serial.print("MARCSTATE ");
Serial.println(ELECHOUSE_cc1101.SpiReadStatus(0x35), HEX);
}
//----------------------------------------------------
void CC1101_debug::show_register(void){
print_line(30);
Serial.println("CC1101 Register");
print_line(30);

for (int i = 0; i<=46; i++){
print_register(i);
}
}
//----------------------------------------------------
void CC1101_debug::print_register(byte b){
Serial.print(Register[b]);
int len = strlen(Register[b]);
len = 10 - len;
for (int i2 = 0; i2<len; i2++){
Serial.print(" ");
}
Serial.println(ELECHOUSE_cc1101.SpiReadStatus(b), HEX);  
}
//----------------------------------------------------
void CC1101_debug::print_line(byte l){
for (int i = 0; i<l; i++){
Serial.print("-");
}
Serial.println();
}

CC1101_debug cc1101_debug;
