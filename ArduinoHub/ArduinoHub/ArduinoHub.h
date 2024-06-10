#pragma once
#include <Voltmeter.h>
#include <StringTok.h>

class ArduinoHub
{
public:
    //생성자
    ArduinoHub(void){}

protected:
    //properties(member 변수)
    StringTok m_stCmd;
    Voltmeter m_voltmeter;
    
};