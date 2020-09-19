#include "gpiopinfactory.h"

#include "factory.h"

#include "gpioout.h"

void GpioPinFactory::createFactory()
{
    Factory::sGetFactory().addFactory<GpioOut>("pinout");
}
