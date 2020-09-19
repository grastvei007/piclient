#ifndef FACTORYBASE_H
#define FACTORYBASE_H

#include <string>

#include <QObject>
#include <QDebug>

#include <tagsystem/taglist.h>
#include <tagsystem/tagsocket.h>
#include <tagsystem/tag.h>

class FactoryBase : public QObject
{
    Q_OBJECT
public:
    FactoryBase(const QString &aTagSystem, const QString &aName, TagSocket::Type aType){
        mTagSocket = TagSocket::createTagSocket(aTagSystem, aName, aType);
        connect(mTagSocket, qOverload<TagSocket*>(&TagSocket::valueChanged), this, &FactoryBase::onTagSocketValueChanged);
    }
    virtual ~FactoryBase(){

    }

    void hookupTag(Tag *aTag){
        if(mTagSocket && aTag)
            mTagSocket->hookupTag(aTag);
    }

    void hookupTag(const QString &aSubsystem, const QString &aName){
        if(mTagSocket)
            mTagSocket->hookupTag(aSubsystem, aName);
    }

protected:
    virtual void onTagSocketValueChanged(TagSocket *aTagSocket){
        Q_UNUSED(aTagSocket);
        qDebug() << __FUNCTION__ << "Override this function";
    }

private:
    TagSocket *mTagSocket;

};

#endif // FACTORYBASE_H
