#include "heaterpump.h"
#include "wiringpiwrapper.h"

#include <QTimer>

HeaterPump::HeaterPump(const QString &aTagSystem, const QString &aName, TagSocket::Type aType) : FactoryBase(aTagSystem, aName, aType)
{

}

HeaterPump::~HeaterPump()
{
    if(mPumpTimer)
        mPumpTimer->deleteLater();
}

void HeaterPump::onTagSocketValueChanged(TagSocket *aTagSocket)
{
    int value = 0;
    if(!aTagSocket && !aTagSocket->readValue(value))
        return;
    if(value < mMinValue)
        value = mMinValue;
    if(value > mMaxValue)
        value = mMaxValue;

    mCurrentPumpSpeed = value;
    if(!mPumpTimer)
    {
        mPumpTimer = new QTimer;
        connect(mPumpTimer, &QTimer::timeout, this, &HeaterPump::onPumpTimerTimeout);
    }
    mPumpTimer->stop();
    mPumpTimer->setInterval(mCurrentPumpSpeed);
    mPumpTimer->start();
}

void HeaterPump::onPumpTimerTimeout()
{
    //turn pump on
    WiringPi::digitalWrite(mWireingPiPin, WiringPi::eHigh);
    // turn pump off
    QTimer::singleShot(500, [&](){
        WiringPi::digitalWrite(mWireingPiPin, WiringPi::eLow);
    });
}
