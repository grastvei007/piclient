#include "app.h"

#include <QCommandLineParser>
#include <QStringList>
#include <QDir>
#include <QDebug>
#include <QXmlStreamWriter>

#include "wiringpiwrapper.h"
#include "gpiopinfactory.h"

#include <tagsystem/taglist.h>
#include <tagsystem/tag.h>


App::App(int argc, char *argv[]) : QCoreApplication(argc, argv)
{
    setApplicationName("Pi client");
    setApplicationVersion("0.1");

    QCommandLineParser parser;
    parser.setApplicationDescription("Pi client to map the gpio to a june server, and manipulate the values over local network");
    parser.addVersionOption();
    parser.addHelpOption();

    QCommandLineOption serverIp("ip", "server-ip", "Connect to server");
    serverIp.setDefaultValue("localhost");
    parser.addOption(serverIp);

    parser.process(*this);
    GpioPinFactory::createFactory();

    WiringPi::wiringPiSetup();

    TagList::sGetInstance().setClientName("piclient");
    TagList::sGetInstance().connectToServer(parser.value(serverIp), 5000);

    setupGpioFromSettingsFile();
}

void App::setupGpioFromSettingsFile()
{
    QString path = QDir::homePath() + QDir::separator() + ".config" + QDir::separator() + "june";
    QDir dir(path);
    if(!dir.exists())
        QDir().mkpath(path);
    path.append(QDir::separator());
    path.append("rpigpiosetup.xml");
    QFile file(path);
    if(!file.exists())
    {
        writeDefaultSettings();
        setupGpioFromSettingsFile();
        return;
    }
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << __FUNCTION__ << "Error opening file, " << path;
        return;
    }
    QXmlStreamReader stream(&file);

    while(!stream.atEnd() && !stream.hasError())
    {
        QXmlStreamReader::TokenType token = stream.readNext();
        if(token == QXmlStreamReader::StartDocument)
            continue;
        if(token == QXmlStreamReader::StartElement)
        {
            if(stream.name() == "rpi")
                continue;

            QString tagsystem = stream.name().toString()         ;
            QString name = stream.attributes().value("name").toString();
            QString type = stream.attributes().value("type").toString();
            int value = stream.attributes().value("value").toInt();

        }
    }

    file.close();
}

void App::writeDefaultSettings()
{
    QString path = QDir::homePath() + QDir::separator() + ".config" + QDir::separator() + "june";
    QDir dir(path);
    if(!dir.exists())
        QDir().mkpath(path);
    path.append(QDir::separator());
    path.append("rpigpiosetup.xml");
    QFile file(path);
    if(!file.open(QIODevice::WriteOnly))
    {
        qDebug() << __FUNCTION__ << "Error opening file, " << path;
        return;
    }

    QXmlStreamWriter stream(&file);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("rpi");

    for(int i=0; i<8; ++i)
    {
        stream.writeStartElement("gpio");
        stream.writeAttribute("name", QString("pin_%1").arg(i));
        stream.writeAttribute("type", "out"); //out
        stream.writeAttribute("value", "0"); // off
        stream.writeAttribute("tagsubsystem", "subsytem");
        stream.writeAttribute("tagname", "tagname");
        stream.writeAttribute("tagtype", Tag::toString(Tag::eInt));
        stream.writeEndElement();
    }

    stream.writeEndElement();
    stream.writeEndDocument();

    file.close();
}
