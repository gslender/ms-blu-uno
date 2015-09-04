#include "Arduino.h"
#include <Bluetooth_HC05.h>
#include <SoftwareSerial.h>

#define DEBUG // comment out to en/disable
//#define DEBUG_USE_SOFTSERIAL
#include "debug.h"
// D(SoftwareSerial debugSerial;)

#include "MegaSquirt.h"

MegaSquirt ms;
SoftwareSerial bt_serial(6, 5);
Bluetooth_HC05 blumod(bt_serial);
#define HC05_MODE_PIN 7

void setup() {
	Serial.begin(115200);

	blumod.begin(38400, HC05_MODE_PIN, HC05_MODE_COMMAND);
	blumod.restoreDefaults();
	delay(500);
	blumod.setSerialMode(9600, 1, HC05_NO_PARITY);
	blumod.setRole(HC05_ROLE_SLAVE);
	blumod.setPassword("0000");
	blumod.changeMode(HC05_MODE_DATA);
	blumod.softReset();
	delay(500);

	blumod.println("ms-blu-uno");
}

void loop()
{
}
