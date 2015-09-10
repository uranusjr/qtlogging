#ifndef QTLOGGING_ABSTRACTHANDLER_H
#define QTLOGGING_ABSTRACTHANDLER_H

#include <QObject>
#include "qtlogging.h"

namespace qtlogging
{

class QTLOGGINGSHARED_EXPORT AbstractHandler : public QObject
{
public:
    explicit AbstractHandler() {}

protected:
    virtual void handle(const QString &message) = 0;
    virtual void flush() = 0;
};

}   // namespace qtlogging

#endif // QTLOGGING_ABSTRACTHANDLER_H
