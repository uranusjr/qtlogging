#ifndef QTLOGGINGTEST_H
#define QTLOGGINGTEST_H

#include <QtTest>

class QtLoggingTest : public QObject
{
    Q_OBJECT

public:
    QtLoggingTest();

private slots:
    void testDemo();
};



#endif  // QTLOGGINGTEST_H

