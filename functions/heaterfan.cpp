#include "heaterfan.h"

#include "../wiringpiwrapper.h"

HeaterFan::HeaterFan(QString &aTagSystem, const QString &aName, TagSocket::Type aType) : FactoryBase(aTagSystem, aName, aType)
{
    WiringPi::softPwmCreate(mWireingPiPin, 0, 100);
}

void HeaterFan::onTagSocketValueChanged(TagSocket *aTagSocket)
{
    int value = 0;
    if(!aTagSocket && !aTagSocket->readValue(value))
        return;

    if(value < 0)
        value = 0;
    if(value > 100)
        value = 100;

    WiringPi::softPwmWrite(mWireingPiPin, value);
}
