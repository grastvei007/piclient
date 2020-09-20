#include "heater.h"

#include <tagsystem/taglist.h>
#include <tagsystem/tag.h>

#include <QTimer>

Heater::Heater(QObject *parent) : QObject(parent)
{
    mTagSocketStart.reset(TagSocket::createTagSocket("heater", "start", TagSocket::eBool));
    mTagSocketOn.reset(TagSocket::createTagSocket("heater", "on", TagSocket::eBool));
    mTagSocketFan.reset(TagSocket::createTagSocket("heater", "fan", TagSocket::eInt));
    mTagSocketEffect.reset(TagSocket::createTagSocket("heater", "effect", TagSocket::eInt));

    Tag *heaterStart = TagList::sGetInstance().createTag("heater", "start", Tag::eBool);
    Tag *heaterOn = TagList::sGetInstance().createTag("heater", "on", Tag::eBool);
    Tag *heaterFan = TagList::sGetInstance().createTag("heater", "fan", Tag::eInt);
    Tag *heaterEffect = TagList::sGetInstance().createTag("heater", "effect", Tag::eInt);

    mTagSocketStart->hookupTag(heaterStart);
    mTagSocketOn->hookupTag(heaterOn);
    mTagSocketFan->hookupTag(heaterFan);
    mTagSocketEffect->hookupTag(heaterEffect);

    mTagSocketStart->writeValue(false);
    mTagSocketOn->writeValue(false);
    mTagSocketFan->writeValue(0);
    mTagSocketEffect->writeValue(0);

    connect(mTagSocketStart.get(), qOverload<bool>(&TagSocket::valueChanged), this, &Heater::onTagSocketStartValueChanged);
    connect(mTagSocketOn.get(), qOverload<bool>(&TagSocket::valueChanged), this, &Heater::onTagSocketOnValueChanged);
    connect(mTagSocketFan.get(), qOverload<int>(&TagSocket::valueChanged), this, &Heater::onTagSocketFanValueChanged);
    connect(mTagSocketEffect.get(), qOverload<int>(&TagSocket::valueChanged), this, &Heater::onTagSocketEffectValueChanged);

    //hw
    mTagSocketPumpFunction.reset(TagSocket::createTagSocket("heater", "pump", TagSocket::eInt));
    mTagSocketFanFunction.reset(TagSocket::createTagSocket("heater", "fanpercent", TagSocket::eInt));
    mTagSocketEffectFunction.reset(TagSocket::createTagSocket("heater", "effectpercent", TagSocket::eInt));
    mTagSocketPreHeatFunction.reset(TagSocket::createTagSocket("heater", "preheat", TagSocket::eBool));
}

Heater::~Heater()
{

}

void Heater::onTagSocketStartValueChanged(bool aValue)
{
    if(aValue)
    {
        mTagSocketEffectFunction->writeValue(100);
        mTagSocketPumpFunction->writeValue(1);
        QTimer::singleShot(8000, [&](){
            mTagSocketPreHeatFunction->writeValue(true);
        });
    }
    else
    {
        mTagSocketPumpFunction->writeValue(0);
    }
}


void Heater::onTagSocketOnValueChanged(bool aValue)
{
    mIsOn = aValue;
    if(aValue)
    {
        mTagSocketPreHeatFunction->writeValue(false);
        mTagSocketEffectFunction->writeValue(70);
        mTagSocketFanFunction->writeValue(50);
    }
    else
    {
        mTagSocketEffectFunction->writeValue(0);
        mTagSocketFanFunction->writeValue(0);
    }
}

void Heater::onTagSocketFanValueChanged(int aValue)
{
    if(!mIsOn)
        return;

    if(aValue < 0)
        aValue = 0;
    if(aValue > 10)
        aValue = 10;

    mTagSocketFanFunction->writeValue(aValue*10);
}


void Heater::onTagSocketEffectValueChanged(int aValue)
{
    if(!mIsOn)
        return;

    if(aValue < 0)
        aValue = 0;
    if(aValue > 10)
        aValue = 10;

    mTagSocketEffectFunction->writeValue(aValue*10);
    int speed = 1 + (10 - aValue)/2;
    mTagSocketPumpFunction->writeValue(speed);
}
