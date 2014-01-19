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
    void testCannotCreate_data();
    void testCannotCreate();
    void testCanSchedule_data();
    void testCanSchedule();
    void testCanScheduleMultipleTimes_data();
    void testCanScheduleMultipleTimes();
};

#endif // TST_SCHEDULINGTEST_H
