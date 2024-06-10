#include <ArduinoHub.h>
#define SERIAL_BPS (9600)
#define PORT_VOLTMETER (A2)
#define PORT_SERVO (3)
#define TRIG_PORT (8)
#define ECHO_PORT (9)
#define LED_R (6)
#define LED_G (7)
#define LED_B (5)

void setup() {
  // put your setup code here, to run once:
  Serial.begin(SERIAL_BPS);
}

void loop() {
  // put your main code here, to run repeatedly:
  ArduinoHub ardHub;
  ardHub.init();
  ardHub.start();

}
