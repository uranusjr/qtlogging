#ifndef QTLOGGING_ROTATINGFILEHANDLER_H
#define QTLOGGING_ROTATINGFILEHANDLER_H

#include <QIODevice>
#include <QObject>
#include "abstracthandler.h"

namespace qtlogging
{

class RotatingFileHandlerPrivate;

class QTLOGGINGSHARED_EXPORT RotatingFileHandler : public AbstractHandler
{

    Q_OBJECT
    Q_DECLARE_PRIVATE(RotatingFileHandler)
    RotatingFileHandlerPrivate * const d_ptr;

public:

    enum RolloverType
    {
        Seconds,
        Minutes,
        Hours,
        Days,

        Midnight,
    };

    RotatingFileHandler(
            const QString &filename,
            RolloverType type = Hours, quint32 interval = 1,
            const QByteArray &encoding = QByteArray("System"),
            QIODevice::OpenMode mode = QIODevice::Append | QIODevice::Text);
    ~RotatingFileHandler();

public slots:
    virtual void handle(const QString &message);
    virtual void flush();

    virtual bool shouldRollover() const;
    virtual void rollover();
};

}   // namespace qtlogging

#endif // QTLOGGING_ROTATINGFILEHANDLER_H
