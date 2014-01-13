#include <QString>
#include <QtTest>

class SchedulingTest : public QObject
{
    Q_OBJECT

public:
    SchedulingTest();

private Q_SLOTS:
    void testCase1();
};

SchedulingTest::SchedulingTest()
{
}

void SchedulingTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(SchedulingTest)

#include "tst_schedulingtest.moc"
