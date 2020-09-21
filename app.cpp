#include "app.h"

#include <QCommandLineParser>
#include <QStringList>
#include <QDir>
#include <QDebug>
#include <QXmlStreamWriter>

#include "wiringpiwrapper.h"
#include "gpiopinfactory.h"
#include "factory.h"
#include "factorybase.h"

#include <tagsystem/taglist.h>
#include <tagsystem/tag.h>
#include <tagsystem/tagsocket.h>
#include <tagsystem/tagsocketlist.h>


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

    TagSocketList::sGetInstance().setApplicationName("piclient");
    TagSocketList::sGetInstance().loadBindingList();

    TagList::sGetInstance().setClientName("piclient");
    TagList::sGetInstance().connectToServer(parser.value(serverIp), 5000);

    setupGpioFromSettingsFile();

    mHeater = std::make_unique<Heater>();
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

            QString tagSocketSubsystem = stream.name().toString();
            QString tagSocketName = stream.attributes().value("name").toString();
            TagSocket::Type tagSocketType = TagSocket::typeFromString(stream.attributes().value("tagtype").toString());
            QString functionType = stream.attributes().value("type").toString();

            QString tagSubsystem = stream.attributes().value("tagsubsystem").toString();
            QString tagName = stream.attributes().value("tagname").toString();
            Tag::Type tagType = Tag::typeFromString(stream.attributes().value("tagtype").toString());

            int value = stream.attributes().value("value").toInt();

            FactoryBase *function = Factory::sGetFactory().createInstance(functionType.toStdString(), tagSocketSubsystem, tagSocketName, tagSocketType);
            if(function)
            {
                Tag *tag = TagList::sGetInstance().createTag(tagSubsystem, tagName, tagType);
                if(tag)
                {
                    tag->setValue(value);
                    function->hookupTag(tag);
                }

                mGpioPins.push_back(function);
            }
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
        stream.writeAttribute("name", QString("pin_%1").arg(i+1));
        stream.writeAttribute("type", "out"); //out
        stream.writeAttribute("value", "0"); // off
        stream.writeAttribute("tagsubsystem", "subsytem");
        stream.writeAttribute("tagname", "tagname");
        stream.writeAttribute("tagtype", Tag::toString(Tag::eBool));
        stream.writeEndElement();
    }

    stream.writeEndElement();
    stream.writeEndDocument();

    file.close();
}
