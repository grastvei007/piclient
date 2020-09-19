#ifndef HEATERPUMP_H
#define HEATERPUMP_H

#include <QString>

#include <tagsystem/tagsocket.h>

#include "../factorybase.h"

class HeaterPump : public FactoryBase
{
public:
    HeaterPump(const QString &aTagSystem, const QString &aName, TagSocket::Type aType);
    ~HeaterPump();
};

#endif // HEATERPUMP_H
