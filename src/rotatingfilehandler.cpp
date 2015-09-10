#include <QDateTime>
#include <QFile>
#include <QFileInfo>
#include <QTextCodec>
#include "rotatingfilehandler.h"

namespace qtlogging
{


static bool tryOpen(QFile &file, QIODevice::OpenMode mode)
{
    if (!file.open(mode))
    {
        fprintf(stderr, "Could not open file %s with mode %d for logging.",
                qPrintable(file.fileName()), static_cast<int>(mode));
        fflush(stderr);
        return false;
    }
    return true;
}


class RotatingFileHandlerPrivate
{
    Q_DECLARE_PUBLIC(RotatingFileHandler)
    RotatingFileHandler * const q_ptr;

public:
    RotatingFileHandlerPrivate(
            RotatingFileHandler *q, const QString &filename,
            const QByteArray &encoding, QIODevice::OpenMode mode,
            RotatingFileHandler::RolloverType type);
    ~RotatingFileHandlerPrivate();

    QDateTime computeRollover(const QDateTime &current);

    QFile file;
    QIODevice::OpenMode mode;
    QTextEncoder *encoder;

    QString suffix;
    RotatingFileHandler::RolloverType type;
    quint32 interval;
    QDateTime nextRollOver;
};

RotatingFileHandlerPrivate::RotatingFileHandlerPrivate(
        RotatingFileHandler *q, const QString &filename,
        const QByteArray &encoding, QIODevice::OpenMode mode,
        RotatingFileHandler::RolloverType type) :
    q_ptr(q), file(filename), mode(mode | QIODevice::WriteOnly), encoder(0),
    type(type), interval(0)
{
    QTextCodec *codec = QTextCodec::codecForName(encoding);
    if (!codec)
    {
        const char *msg =
                "No matching codec found for encoding %s. Default locale "
                "codec will be used.";
        fprintf(stderr, msg, encoding.constData());
        codec = QTextCodec::codecForLocale();
    }
    encoder = codec->makeEncoder();
}

RotatingFileHandlerPrivate::~RotatingFileHandlerPrivate()
{
    if (encoder)
        delete encoder;
}

QDateTime RotatingFileHandlerPrivate::computeRollover(const QDateTime &current)
{
    QDateTime result;

    switch (type)
    {
    case RotatingFileHandler::Midnight:
        result = QDateTime(current.date().addDays(1));
        break;
    case RotatingFileHandler::Seconds:
    case RotatingFileHandler::Minutes:
    case RotatingFileHandler::Hours:
    case RotatingFileHandler::Days:
        result = current.addSecs(interval);
        break;
    }
    return result;
}


RotatingFileHandler::RotatingFileHandler(
        const QString &filename, RotatingFileHandler::RolloverType type,
        quint32 interval, const QByteArray &encoding,
        QIODevice::OpenMode mode) :
    AbstractHandler(),
    d_ptr(new RotatingFileHandlerPrivate(this, filename, encoding, mode, type))
{
    Q_D(RotatingFileHandler);

    switch (type)
    {
    case Seconds:
        d->suffix = "yyyy-MM-dd_HH-mm-ss";
        break;
    case Minutes:
        d->interval = interval * 60;
        d->suffix = "yyyy-MM-dd_HH-mm";
        break;
    case Hours:
        d->interval = interval * 60 * 60;
        d->suffix = "yyyy-MM-dd_HH";
        break;
    case Days:
    case Midnight:
        d->interval = interval * 60 * 60 * 24;
        d->suffix = "yyyy-MM-dd";
        break;
    }

    QFileInfo fi(filename);
    QDateTime lastLog;
    if (fi.exists())
        lastLog = fi.lastModified();
    else
        lastLog = QDateTime::currentDateTime();
    d->nextRollOver = d->computeRollover(lastLog);
}

RotatingFileHandler::~RotatingFileHandler()
{
    delete d_ptr;
}

void RotatingFileHandler::handle(const QString &message)
{
    Q_D(RotatingFileHandler);

    if (shouldRollover())
        rollover();
    if (!d->file.isOpen() && !tryOpen(d->file, d->mode))
        return;

    d->file.write(d->encoder->fromUnicode(message));
    d->file.write("\n");
    flush();
}

void RotatingFileHandler::flush()
{
    Q_D(RotatingFileHandler);
    if (d->file.isOpen())
        d->file.flush();
}

bool RotatingFileHandler::shouldRollover() const
{
    return (QDateTime::currentDateTime() >= d_func()->nextRollOver);
}

void RotatingFileHandler::rollover()
{
    Q_D(RotatingFileHandler);

    // Calculate when this log file was first used, so that we can name it with
    // the start time of logging, not the end time.
    QDateTime startTime = d->nextRollOver.addSecs(0 - d->interval);
    QString moveTo = QString("%1.%2")
            .arg(d->file.fileName()).arg(startTime.toString(d->suffix));
    if (QFileInfo(moveTo).exists() && QFile(moveTo).remove())
    {
        fprintf(stderr, "Could not remove existing file %s.",
                qPrintable(moveTo));
        fflush(stderr);
        return;
    }
    if (d->file.exists())
        d->file.rename(moveTo);
    d->nextRollOver = d->computeRollover(QDateTime::currentDateTime());
}

}   // namespace qtlogging
