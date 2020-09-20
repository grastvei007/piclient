#ifndef HEATER_H
#define HEATER_H

#include <memory>

#include <QObject>

#include <tagsystem/tagsocket.h>

class Heater : public QObject
{
    Q_OBJECT
public:
    Heater(QObject *parent = nullptr);
    virtual ~Heater();
signals:
private:
    void onTagSocketStartValueChanged(bool aValue);
    void onTagSocketOnValueChanged(bool aValue);
    void onTagSocketFanValueChanged(int aValue);
    void onTagSocketEffectValueChanged(int aValue);

private:
    // user interactive values
    std::unique_ptr<TagSocket> mTagSocketStart;
    std::unique_ptr<TagSocket> mTagSocketOn;
    std::unique_ptr<TagSocket> mTagSocketFan;
    std::unique_ptr<TagSocket> mTagSocketEffect;

    //hardware function interaction
    std::unique_ptr<TagSocket> mTagSocketPumpFunction;
    std::unique_ptr<TagSocket> mTagSocketFanFunction;
    std::unique_ptr<TagSocket> mTagSocketEffectFunction;
    std::unique_ptr<TagSocket> mTagSocketPreHeatFunction;

    //variables
    bool mIsOn = false;
};

#endif // HEATER_H
