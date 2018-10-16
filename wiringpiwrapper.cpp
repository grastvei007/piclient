#include "wiringpiwrapper.h"

#ifdef __arm__
#include <wiringPi.h>
#include <softPwm.h>
#else
#include <QDebug>
#endif



void WiringPi::wiringPiSetup()
{
#ifdef __arm__
    wiringPiSetup();
#else
    qDebug() << __FUNCTION__;
#endif
}

void WiringPi::pinMode(int aPin, PinDir aDir)
{
#ifdef __arm__
    if(aDir == eInput)
        pinMode(aPin, INPUT);
    else if(aDir == eOutput)
        pinMode(aPin, OUTPUT);
#else
    qDebug() << __FUNCTION__;
#endif

}


void WiringPi::digitalWrite(int aPin, Value aVal)
{
#ifdef __arm__
    if(aVal == eLow)
        digitalWrite(aPin, LOW);
    else if(aVal == eHigh)
        digitalWrite(aPin, HIGH);
#else
    qDebug() << __FUNCTION__;
#endif
}


int WiringPi::softPwmCreate(int aPin, int aInitVal, int aPwmRange)
{
#ifdef __arm__
      return softPwmCreate(aPin, aInitVal, aPwmRange);
#else
    qDebug() << __FUNCTION__;
    return 0;
#endif
}


void WiringPi::softPwmWrite(int aPin, int aValue)
{
#ifdef __arm__
    softPwmWrite(aPinNumber, aValue);
#else
    qDebug() << __FUNCTION__;
#endif
}


void WiringPi::pwmSetClock(int aClock)
{
#ifdef __arm__
    pwmSetClock(aClock);
#else
    qDebug() << __FUNCTION__;
#endif
}


void WiringPi::pwmSetRange(int aRange)
{
#ifdef __arm__
    pwmSetRange(aRange);
#else
    qDebug() << __FUNCTION__;
#endif
}
