#include "gpiopinfactory.h"

#include "factory.h"

#include "functions/heaterpump.h"

void GpioPinFactory::createFactory()
{
    Factory::sGetFactory().addFactory<HeaterPump>("heaterpump");
}
