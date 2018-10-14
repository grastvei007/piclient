#ifndef GPIOPIN_H
#define GPIOPIN_H

#include <QObject>

class TagSocket;


class GpioPin : public QObject
{
    Q_OBJECT
public:
    enum Mode{
        eIn,
        eOut,
        ePwm,
        eUnknown
    };
    explicit GpioPin(int aPinNumber, QObject *parent = nullptr);

signals:

public slots:

private slots:
    void onPinModeChanged(int aMode);
    void onPinValueChanged(int aValue);
    void onPinPwmClockValueChanged(int aValue);
    void onPinPwmRangeValueChanged(int aValue);

private:
    TagSocket *mPinMode;
    TagSocket *mPinValue;
    TagSocket *mPwmClockTagSocket;
    TagSocket *mPwmRangeTagSocket;
    int mPin;
    Mode mMode;
};

#endif // GPIOPIN_H
