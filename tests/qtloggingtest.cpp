#include "qtloggingtest.h"


QtLoggingTest::QtLoggingTest() : QObject()
{
}

void QtLoggingTest::testDemo()
{
    QVERIFY(1 + 1 == 2);
}
