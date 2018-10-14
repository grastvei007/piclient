#ifndef APP_H
#define APP_H

#include <QCoreApplication>
#include <QVector>

class GpioPin;

class App : public QCoreApplication
{
    Q_OBJECT
public:
    explicit App(int argc, char *argv[]);

signals:

public slots:

private:
    QVector<GpioPin*> mGpioPins;
};

#endif // APP_H
