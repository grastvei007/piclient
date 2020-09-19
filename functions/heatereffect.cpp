#include "heatereffect.h"

#include "../wiringpiwrapper.h"

HeaterEffect::HeaterEffect(QString &aTagSystem, const QString &aName, TagSocket::Type aType) : FactoryBase(aTagSystem, aName, aType)
{
    WiringPi::softPwmCreate(mWireingPiPin, 0, 100);
}

void HeaterEffect::onTagSocketValueChanged(TagSocket *aTagSocket)
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
