# CC1101 debug service tool v0.1

Caution. This library is at the very beginning and should be viewed as a pre-release version. More functions will be added over time.
if you have any suggestions, feel free to share them under "issues".

---------------------------------------------
Description
---------------------------------------------
With this tool, you can register entries of the CC1101 during operation
read and change. You can switch to send or receive.
Set the transmission strength and change or call up the frequency.

For: https://github.com/LSatan/SmartRC-CC1101-Driver-Lib

---------------------------------------------
Commands
---------------------------------------------
Enter in the serial monitor.


reg 		 (Shows all settings of the register.)

ver 		 (Displays the cc1101 version number.)

mhz? 		 (shows the current frequency and the associated register entries.)

mhz=433.92 	 (sets the specified frequency and then displays it.)

pa=10 		 (sets the transmission strength to the set value.)

tx 		 (puts the cc1101 in transmit mode.)

rx 		 (puts the cc1101 in receive mode.)

Register entry +? Example:

MDMCFG0? 	 (shows the current value for this entry.)

Register entry + hex value Example:

MDMCFG0=FF 	 (sets the hex value FF for this entry.)



---------------------------------------------
Impressions
---------------------------------------------
CC1101 debug service tool for SmartRC-CC1101-Driver-Lib from version V2.3.3 and newer.

add to sketch:

#include <cc1101_debug_service.h>

at the beginning of the loop:

cc1101_debug.debug ();


Finished!


---------------------------------------------
Preview
---------------------------------------------

<img src="https://github.com/LSatan/CC1101-Debug-Service-Tool/blob/master/img/install_example.png"/>

<img src="https://github.com/LSatan/CC1101-Debug-Service-Tool/blob/master/img/start_example.png"/>

<img src="https://github.com/LSatan/CC1101-Debug-Service-Tool/blob/master/img/commands_example.png"/>
