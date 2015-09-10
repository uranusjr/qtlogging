#include "streaminghandler.h"

namespace qtlogging
{


class StreamingHandlerPrivate
{
    Q_DECLARE_PUBLIC(StreamingHandler)
    StreamingHandler * const q_ptr;

public:
    StreamingHandlerPrivate(StreamingHandler *q, FILE *stream);

    FILE *stream;
};

StreamingHandlerPrivate::StreamingHandlerPrivate(
        StreamingHandler *q, FILE *stream) : q_ptr(q), stream(stream)
{
}


StreamingHandler::StreamingHandler(FILE *stream) :
    AbstractHandler(), d_ptr(new StreamingHandlerPrivate(this, stream))
{

}

StreamingHandler::~StreamingHandler()
{
    delete d_ptr;
}

void StreamingHandler::handle(const QString &message)
{
    Q_D(StreamingHandler);
    fprintf(d->stream, "%s", message.toLocal8Bit().data());
}

void StreamingHandler::flush()
{
    Q_D(StreamingHandler);
    fflush(d->stream);
}

}   // namespace qtlogging
