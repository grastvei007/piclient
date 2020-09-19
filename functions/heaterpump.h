#ifndef HEATERPUMP_H
#define HEATERPUMP_H

#include <QString>

#include <tagsystem/tagsocket.h>

#include "../factorybase.h"

class QTimer;

class HeaterPump : public FactoryBase
{
public:
    HeaterPump(const QString &aTagSystem, const QString &aName, TagSocket::Type aType);
    ~HeaterPump();

protected:
    void onTagSocketValueChanged(TagSocket *aTagSocket);
    void onPumpTimerTimeout();

private:
    int mMinValue = 1;
    int mMaxValue = 5;
    int mCurrentPumpSpeed = 5;
    int mWireingPiPin = 1;

    QTimer *mPumpTimer = nullptr;
};

#endif // HEATERPUMP_H
