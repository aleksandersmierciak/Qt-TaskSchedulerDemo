#ifndef TST_SCHEDULINGTEST_H
#define TST_SCHEDULINGTEST_H

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

#endif // TST_SCHEDULINGTEST_H
