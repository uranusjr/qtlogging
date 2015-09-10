#ifndef QTLOGGING_H
#define QTLOGGING_H

#include <QObject>

#if defined(QTLOGGING_LIBRARY)
#  define QTLOGGINGSHARED_EXPORT Q_DECL_EXPORT
#else
#  define QTLOGGINGSHARED_EXPORT Q_DECL_IMPORT
#endif

namespace qtlogging
{

class AbstractHandler;

QTLOGGINGSHARED_EXPORT void install(AbstractHandler *handler);

QTLOGGINGSHARED_EXPORT AbstractHandler *handler();

QTLOGGINGSHARED_EXPORT void setLogLevel(QtMsgType level);
QTLOGGINGSHARED_EXPORT QtMsgType logLevel();

}   // namespace qtlogging

#endif // QTLOGGING_H
