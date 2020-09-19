#ifndef GPIOOUT_H
#define GPIOOUT_H

#include <QObject>
#include "factorybase.h"

class GpioOut : public FactoryBase
{
    Q_OBJECT
public:
    explicit GpioOut();

signals:

};

#endif // GPIOOUT_H
