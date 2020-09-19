#ifndef FACTORY_H
#define FACTORY_H

#include <map>
#include <string>
#include <iostream>
#include <QString>

#include <tagsystem/tagsocket.h>

//#include "factorybase.h"

class FactoryBase;

template<typename Type>
FactoryBase* createType(QString aTagSystem, QString aName, TagSocket::Type aType)
{
    return new Type(aTagSystem, aName, aType);
}

class Factory
{
public:
    static Factory& sGetFactory()
    {
        static Factory sFactory;
        return sFactory;
    }

    FactoryBase* createInstance(const std::string &aKey, const QString &aTagSystem, const QString &aName, TagSocket::Type aType)
    {
        if(mConstructors.find(aKey) == mConstructors.end())
            return nullptr;
        Creator createor = mConstructors[aKey];
        return createor(aTagSystem, aName, aType);
    }


    template<typename Type>
     void addFactory(const std::string &aCreateKey);

private:
     Factory(){}

protected:
    typedef FactoryBase* (*Creator)(QString aTagSystem, QString aName, TagSocket::Type aType);

    std::map<std::string, Creator> mConstructors;
};


template<typename Type>
void Factory::addFactory(const std::string &aCreateKey)
{
    Creator creator = &createType<Type>;
    mConstructors.insert(std::make_pair(aCreateKey, creator));
}


#endif // FACTORY_H
