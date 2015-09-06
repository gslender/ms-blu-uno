#include "Arduino.h"
#include <Bluetooth_HC05.h>
#include <SoftwareSerial.h>

//#define DEBUG // comment out to en/disable
//#define DEBUG_USE_SOFTSERIAL
#include "debug.h"
// D(SoftwareSerial debugSerial;)

#include "MegaSquirt.h"

MegaSquirt ms;
SoftwareSerial bt_serial(6, 5);
Bluetooth_HC05 blumod(bt_serial);
#define HC05_MODE_PIN 7

int loopcnt;

void setup() {
	Serial.begin(115200);

	blumod.begin(38400, HC05_MODE_PIN, HC05_MODE_COMMAND);
	delay(2000);// wait for hc05 to start up
	blumod.restoreDefaults();
	delay(500);
	blumod.setRole(HC05_ROLE_SLAVE);
	blumod.setPassword("0000");
	blumod.changeMode(HC05_MODE_DATA);

    // enable interrupts to capture serial reads (megasquirt etc)
	cli();//stop interrupts
    OCR0A = 0xAF;
    TIMSK0 |= _BV(OCIE0A);
    sei();//allow interrupts
}

void loop()
{
}


// Interrupt is called once a millisecond, looks for any new GPS data, and stores it
// at 9600 this is roughly 1 byte or more per interrupt
// at 115200 this is nearly 15 bytes or more per interrupt
SIGNAL(TIMER0_COMPA_vect) {
	 while (Serial.available() > 0)
	    ms.process(Serial.read());
}
