#include "gpioout.h"
#include "../wiringpiwrapper.h"

GpioOut::GpioOut(QString &aTagSystem, const QString &aName, TagSocket::Type aType) : FactoryBase(aTagSystem, aName, aType)
{
    mWireingPiPin = aName.split("_").last().toInt();
    WiringPi::pinMode(mWireingPiPin, WiringPi::eOutput);
}

void GpioOut::onTagSocketValueChanged(TagSocket *aTagSocket)
{
    bool value;
    if(!aTagSocket->readValue(value))
        return;
    if(value)
        WiringPi::digitalWrite(mWireingPiPin, WiringPi::eHigh);
    else
        WiringPi::digitalWrite(mWireingPiPin, WiringPi::eLow);
}
