#include "app.h"

#include <QCommandLineParser>
#include <QStringList>
#include <QDebug>

#ifdef __arm__
#include <wiringPi.h>
#include <softPwm.h>
#endif
#include <tagsystem/taglist.h>

#include "gpiopin.h"

App::App(int argc, char *argv[]) : QCoreApplication(argc, argv)
{
    setApplicationName("Pi client");
    setApplicationVersion("0.1");

    QCommandLineParser parser;
    parser.setApplicationDescription("Pi client to map the gpio to a june server, and manipulate the values over local network");
    parser.addVersionOption();
    parser.addHelpOption();

    QCommandLineOption ip(QStringList() << "a" << "server_adress", "Server Adress");
    ip.setValueName("adress");
    ip.setDefaultValue("localhost");
    parser.addOption(ip);

    parser.process(*this);
#ifdef __arm__
    wiringPiSetup();
#endif

    QString adress = parser.value(ip);
    TagList::sGetInstance().connectToServer(adress, 5000);


    TagList::sGetInstance().createTag("pi", "gpioPin0Mode", Tag::eInt);
    TagList::sGetInstance().createTag("pi", "gpioPin1Mode", Tag::eInt);
    TagList::sGetInstance().createTag("pi", "gpioPin2Mode", Tag::eInt);
    TagList::sGetInstance().createTag("pi", "gpioPin3Mode", Tag::eInt);
    TagList::sGetInstance().createTag("pi", "gpioPin4Mode", Tag::eInt);
    TagList::sGetInstance().createTag("pi", "gpioPin5Mode", Tag::eInt);
    TagList::sGetInstance().createTag("pi", "gpioPin6Mode", Tag::eInt);
    TagList::sGetInstance().createTag("pi", "gpioPin7Mode", Tag::eInt);

    TagList::sGetInstance().createTag("pi", "gpioPin0Value", Tag::eInt);
    TagList::sGetInstance().createTag("pi", "gpioPin1Value", Tag::eInt);
    TagList::sGetInstance().createTag("pi", "gpioPin2Value", Tag::eInt);
    TagList::sGetInstance().createTag("pi", "gpioPin3Value", Tag::eInt);
    TagList::sGetInstance().createTag("pi", "gpioPin4Value", Tag::eInt);
    TagList::sGetInstance().createTag("pi", "gpioPin5Value", Tag::eInt);
    TagList::sGetInstance().createTag("pi", "gpioPin6Value", Tag::eInt);
    TagList::sGetInstance().createTag("pi", "gpioPin7Value", Tag::eInt);

    for(int i=0; i<8; ++i)
    {
        GpioPin *pin = new GpioPin(i);
        mGpioPins.push_back(pin);
    }
}
