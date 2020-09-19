#ifndef HEATERFAN_H
#define HEATERFAN_H

#include <QString>

#include <tagsystem/tagsocket.h>

#include "../factorybase.h"

class HeaterFan : public FactoryBase
{
public:
    HeaterFan(QString &aTagSystem, const QString &aName, TagSocket::Type aType);

protected:
    void onTagSocketValueChanged(TagSocket *aTagSocket);

private:
    int mWireingPiPin = 3;
};

#endif // HEATERFAN_H
