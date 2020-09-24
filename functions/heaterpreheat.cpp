#include "heaterpreheat.h"

#include "../wiringpiwrapper.h"

HeaterPreHeat::HeaterPreHeat(QString &aTagSystem, const QString &aName, TagSocket::Type aType) : FactoryBase(aTagSystem, aName, aType)
{
    WiringPi::pinMode(mWireingPiPin, WiringPi::eOutput);
}

void HeaterPreHeat::onTagSocketValueChanged(TagSocket *aTagSocket)
{
    bool value = false;
    if(!aTagSocket)
		return;
 	if(!aTagSocket->readValue(value))
        return;

    if(value)
        WiringPi::digitalWrite(mWireingPiPin, WiringPi::eHigh);
    else
        WiringPi::digitalWrite(mWireingPiPin, WiringPi::eLow);
}
