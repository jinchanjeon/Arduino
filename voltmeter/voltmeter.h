#pragma once // 한 번만 include

class Voltmeter
{

/*
객체 특징

1. 캡슐화
    class voltmeter{};

    권한    외부접근    상속접근
---------------------------------
 public       o         o
 private      x         x (private은 잘 안 씀. 대신에 protected 씀)
 protected    x         o (자식 클래스에서는 접근 가능한데 외부에서는 접근 불가능)


2. 생성자(constructor)
   : class(설계도)가 선언될 때 (instance(제품) 만들 때) 호출되는 함수 

*/

public:
    //constructor
    Voltmeter(void)
    {

    }

    Voltmeter(int nVoltPort)
    {
        m_nVoltPort = nVoltPort;
    }

//private:

protected:
    //properties(변수)
    int m_nVoltPort;    //m : 멤버라는 뜻

};