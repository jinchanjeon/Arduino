#include <MyLedSensor.h>
#include <StringTok.h>
#define SERIAL_RATE (9600)
#define DELAY_MS (1000)
#define NUM_CHECK_LINE (5)
MyLedSensor myledsensor;

  String getSerialInput()
    {
        StringTok stInput;
        scans(stInput); // wait and return string
        if (!stInput.isEmpty())
        {
            int nCheckLine = 0;
            while (!stInput.hasLine()) // true: enter o, false: enter x
            {
                stInput.appendSerial(); // appendSerial() -> serial로부터 입력받아 StringTok에 붙이기
                nCheckLine++;
                if (nCheckLine > NUM_CHECK_LINE)
                {
                    break;
                }
            }
        }
        return stInput.toString();
    }

void setup() {
  // put your setup code here, to run once:
  String str = getSerialInput();
  myledsensor.initLed();
  myledsensor.turnColor(str);
  Serial.println(str);
  Serial.begin(SERIAL_RATE);
}

void loop() {
  // put your main code here, to run repeatedly:
  myledsensor.loop();
  String str = getSerialInput();
  Serial.println("color = "+ str);
  delay(DELAY_MS);
}
