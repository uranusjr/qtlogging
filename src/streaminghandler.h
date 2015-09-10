#ifndef QTLOGGING_STREAMINGHANDLER_H
#define QTLOGGING_STREAMINGHANDLER_H

#include <cstdio>
#include "abstracthandler.h"

namespace qtlogging
{

class StreamingHandlerPrivate;

class QTLOGGINGSHARED_EXPORT StreamingHandler : public AbstractHandler
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(StreamingHandler)
    StreamingHandlerPrivate * const d_ptr;

public:
    explicit StreamingHandler(FILE *stream = stderr);
    virtual ~StreamingHandler();

public slots:
    virtual void handle(const QString &message);
    virtual void flush();
};

}   // namespace qtlogging

#endif // QTLOGGING_STREAMINGHANDLER_H
