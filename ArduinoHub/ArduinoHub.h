#pragma once
#include <voltmeter.h>
#include <StringTok.h>
#define NUM_CHECK_LINE (5)

class ArduinoHub
{
public:
    //생성자
    ArduinoHub(void){}

    //methods(member 함수)
    void init(void){}
    void start(void) {}

protected:
    //properties(member 변수)
    StringTok m_stCmd;
    Voltmeter m_voltmeter;
    

    String getSerialInput()
    {
        StringTok stInput;
        scans(stInput); //wait and return string
        if (!stInput.isEmpty())
        {
            int nCheckLine=0;
            while (!stInput.hasLine()) //true: enter o, false: enter x
            {
                stInput.appendSerial(); //appendSerial() -> serial로부터 입력받아 StringTok에 붙이기 
                nCheckLine++;
                if(nCheckLine > NUM_CHECK_LINE)
                {   
                    break;
                }
            }         
        }        
        return stInput.toString();
    }

void parseCommand(void){}
void exeCmd(void){}
};