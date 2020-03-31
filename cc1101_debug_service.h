#define cc1101_debug_service_h
#include <Arduino.h>




class CC1101_debug
{
private:
void print_register(byte b);
void print_line(byte l);
void show_version(void);
void show_register(void);

public:


void debug(void);

};

extern CC1101_debug cc1101_debug;
