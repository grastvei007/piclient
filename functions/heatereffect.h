#ifndef HEATEREFFECT_H
#define HEATEREFFECT_H

#include <QString>

#include <tagsystem/tagsocket.h>

#include "../factorybase.h"

class HeaterEffect : public FactoryBase
{
public:
    HeaterEffect(QString &aTagSystem, const QString &aName, TagSocket::Type aType);

protected:
    void onTagSocketValueChanged(TagSocket *aTagSocket);

private:
    int mWireingPiPin = 4;
};

#endif // HEATEREFFECT_H
