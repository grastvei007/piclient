#ifndef HEATERPREHEAT_H
#define HEATERPREHEAT_H

#include <QString>

#include <tagsystem/tagsocket.h>

#include "../factorybase.h"

class HeaterPreHeat : public FactoryBase
{
public:
    HeaterPreHeat(QString &aTagSystem, const QString &aName, TagSocket::Type aType);

protected:
    void onTagSocketValueChanged(TagSocket *aTagSocket);

private:
    int mWireingPiPin = 0;
};

#endif // HEATERPREHEAT_H
