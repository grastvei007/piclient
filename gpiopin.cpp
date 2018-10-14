#include "gpiopin.h"
#ifdef __arm__
#include <wiringPi.h>
#include <softPwm.h>
#endif

#include <QDebug>
#include <QtGlobal>

#include <tagsystem/tagsocket.h>
#include <tagsystem/taglist.h>



GpioPin::GpioPin(int aPinNumber, QObject *parent) : QObject(parent),
    mMode(eUnknown),
    mPin(aPinNumber)
{
    mPinMode = new TagSocket("gpio", QString("pin%1Mode").arg(aPinNumber), TagSocket::eInt);
    mPinMode->hookupTag("pi", QString("gpioPin%1Mode").arg(aPinNumber));

    mPinValue = new TagSocket("gpio", QString("pin%1Value").arg(aPinNumber), TagSocket::eInt);
    mPinValue->hookupTag("pi", QString("gpioPin%1Value").arg(aPinNumber));

    Tag *pwmClock = TagList::sGetInstance().createTag("pi", QString("gpioPin%1PwmClock").arg(aPinNumber), Tag::eInt);
    Tag *pwmRange = TagList::sGetInstance().createTag("pi", QString("gpioPin%1PwmRange").arg(aPinNumber), Tag::eInt);

    pwmClock->setValue(-1);
    pwmRange->setValue(-1);

    mPwmClockTagSocket = new TagSocket("gpio", QString("pin%1PwmClock").arg(aPinNumber), TagSocket::eInt);
    mPwmClockTagSocket->hookupTag(pwmClock);

    mPwmRangeTagSocket = new TagSocket("gpio", QString("pin%1PwmRange").arg(aPinNumber), TagSocket::eInt);
    mPwmRangeTagSocket->hookupTag(pwmRange);

    // set default as pin out and off
    mPinMode->writeValue(eOut);
    mPinValue->writeValue(0);
#ifdef __arm__
     pinMode(aPinNumber, OUTPUT);
     digitalWrite(aPinNumber,  LOW);
#endif

    connect(mPinMode, QOverload<int>::of(&TagSocket::valueChanged), this, &GpioPin::onPinModeChanged);
    connect(mPinValue, QOverload<int>::of(&TagSocket::valueChanged), this, &GpioPin::onPinValueChanged);
}

void GpioPin::onPinModeChanged(int aMode)
{
    qDebug() << __FUNCTION__ << "mode: " <<aMode;

    if(aMode == 0)
    {
        mMode = eIn;
    }
    else if(aMode == 1)
    {
        mMode = eOut;
#ifdef __arm__
         pinMode(aPinNumber, OUTPUT);
#endif
    }
    else if(aMode == 2)
    {
        mMode = ePwm;
#ifdef __arm__
      softPwmCreate(aPinNumber, 0, 100);
#endif
    }
    else
        mMode = eUnknown;
}


void GpioPin::onPinValueChanged(int aValue)
{
    switch (mMode) {
    case eIn:

        break;
    case eOut:
    {
        {
#ifdef __arm__
      if(aValue == 0)
          digitalWrite(aPinNumber,  LOW);
       else if(aValue == 1)
          digitalWrite(aPinNumber, HIGH);

#endif
        qDebug() << "out" << aValue;
        break;
        }
    }
    case ePwm:
    {
#ifdef __arm__
        if(aValue >= 0 && aValue <= 100)
            softPwmWrite(aPinNumber, aValue);
#endif
        qDebug() << "pwm" << aValue;
        break;
    }
    case eUnknown:
        break;
    }

}
