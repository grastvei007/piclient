#include "gpiopinfactory.h"

#include "factory.h"

#include "functions/heaterpump.h"
#include "functions/heaterpreheat.h"
#include "functions/heatereffect.h"
#include "functions/heaterfan.h"

void GpioPinFactory::createFactory()
{
    Factory::sGetFactory().addFactory<HeaterPump>("heaterpump");
    Factory::sGetFactory().addFactory<HeaterPreHeat>("heaterpreheat");
    Factory::sGetFactory().addFactory<HeaterEffect>("heatereffect");
    Factory::sGetFactory().addFactory<HeaterFan>("heaterfan");
}
