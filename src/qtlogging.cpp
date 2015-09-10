#include <QScopedPointer>
#include "abstracthandler.h"
#include "qtlogging.h"

namespace qtlogging
{

static QScopedPointer<AbstractHandler> gHandler;
static QtMsgType gLogLevel = QtDebugMsg;

static void logMessage(
        QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    if (type < gLogLevel)
        return;

    QString content = qFormatLogMessage(type, context, msg);
    if (!gHandler)
    {
        fprintf(stderr, "Log handler not initialized.");
        fflush(stderr);
        return;
    }
    QMetaObject::invokeMethod(
                gHandler.data(), "handle", Qt::QueuedConnection,
                Q_ARG(QString, content));
}

void install(AbstractHandler *handler)
{
    qInstallMessageHandler(logMessage);
    gHandler.reset(handler);
}

AbstractHandler *handler()
{
    return gHandler.data();
}

void setLogLevel(QtMsgType level)
{
    gLogLevel = level;
}

QtMsgType logLevel()
{
    return gLogLevel;
}

}   // namespace qtlogging
