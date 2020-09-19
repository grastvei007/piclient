#ifndef GPIOPIN_H
#define GPIOPIN_H

#include <QObject>
#include <QString>

class TagSocket;

class GpioPin : public QObject
{
    Q_OBJECT
public:
    explicit GpioPin(QObject *parent=nullptr);

protected:
    TagSocket *mPinTagSocket;
    QString mName;
    QString mSubsystem;
    int mMode;
    int mValue;
};

#endif // GPIOPIN_H
