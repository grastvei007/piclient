#ifndef GPIOOUT_H
#define GPIOOUT_H

#include <QString>

#include <tagsystem/tagsocket.h>

#include "../factorybase.h"

class GpioOut : public FactoryBase
{
    Q_OBJECT
public:
    GpioOut(QString &aTagSystem, const QString &aName, TagSocket::Type aType);

protected:
    void onTagSocketValueChanged(TagSocket *aTagSocket);

private:
    int mWireingPiPin = 0;
};

#endif // GPIOOUT_H
