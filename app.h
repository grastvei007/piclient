#ifndef APP_H
#define APP_H

#include <memory>

#include <QCoreApplication>
#include <QVector>

#include "heater.h"

class FactoryBase;

class App : public QCoreApplication
{
    Q_OBJECT
public:
    explicit App(int argc, char *argv[]);

signals:

public slots:

private:
    void setupGpioFromSettingsFile();
    void writeDefaultSettings();

private:
    QVector<FactoryBase*> mGpioPins;
    std::unique_ptr<Heater> mHeater;
};

#endif // APP_H
