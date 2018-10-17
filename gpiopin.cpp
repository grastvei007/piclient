#include "gpiopin.h"
#include "wiringpiwrapper.h"

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


     WiringPi::pinMode(aPinNumber, WiringPi::eOutput);
     WiringPi::digitalWrite(aPinNumber,  WiringPi::eLow);


    connect(mPinMode, static_cast<void(TagSocket::*)(int)>(&TagSocket::valueChanged), this, &GpioPin::onPinModeChanged);
    connect(mPinValue, static_cast<void(TagSocket::*)(int)>(&TagSocket::valueChanged), this, &GpioPin::onPinValueChanged);
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
        WiringPi::pinMode(mPin, WiringPi::eOutput);
    }
    else if(aMode == 2)
    {
        mMode = ePwm;

      WiringPi::pwmSetMode(WiringPi::ePwmModeMs);
      WiringPi::softPwmCreate(mPin, 0, 100);

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

      if(aValue == 0)
          WiringPi::digitalWrite(mPin, WiringPi::eLow);
       else if(aValue == 1)
          WiringPi::digitalWrite(mPin, WiringPi::eHigh);

        break;
        }
    }
    case ePwm:
    {
        if(aValue >= 0 && aValue <= 100)
            WiringPi::softPwmWrite(mPin, aValue);
        qDebug() << "pwm" << aValue;
        break;
    }
    case eUnknown:
        break;
    }

}


void GpioPin::onPinPwmClockValueChanged(int aValue)
{
    WiringPi::pwmSetClock(aValue);
}


void GpioPin::onPinPwmRangeValueChanged(int aValue)
{
    WiringPi::pwmSetRange(aValue);
}
