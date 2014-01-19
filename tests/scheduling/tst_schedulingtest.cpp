#include <QList>
#include <QString>
#include <QtTest>

#include "tst_schedulingtest.h"
#include "taskscheduler.h"

SchedulingTest::SchedulingTest()
{
}

void SchedulingTest::testCannotCreate_data()
{
    QTest::addColumn<unsigned int>("machineDuration");
    QTest::addColumn<QList<unsigned int> >("jobDurations");

    QTest::newRow("no_machines") << (uint)0 << QList<unsigned int>({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    QTest::newRow("no_jobs") << (uint)3 << QList<unsigned int>();
    QTest::newRow("zero_job") << (uint)10 << QList<unsigned int>({0});
}

void SchedulingTest::testCannotCreate()
{
    QFETCH(unsigned int, machineDuration);
    QFETCH(QList<unsigned int>, jobDurations);

    TaskScheduler scheduler;

    bool outcome;
    try
    {
        scheduler.schedule(machineDuration, jobDurations);
        scheduler.schedule(machineDuration, jobDurations);
        scheduler.schedule(machineDuration, jobDurations);
        scheduler.schedule(machineDuration, jobDurations);
        outcome = true;
    }
    catch(...)
    {
        outcome = false;
    }

    QVERIFY(!outcome);
}

void SchedulingTest::testCanSchedule_data()
{
    QTest::addColumn<unsigned int>("machineDuration");
    QTest::addColumn<QList<unsigned int> >("jobDurations");

    QTest::newRow("more_machines") << (uint)15 << QList<unsigned int>({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    QTest::newRow("more_jobs") << (uint)3 << QList<unsigned int>({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    QTest::newRow("single_machine") << (uint)1 << QList<unsigned int>({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    QTest::newRow("large_job") << (uint)10 << QList<unsigned int>({150});
}

void SchedulingTest::testCanSchedule()
{
    QFETCH(unsigned int, machineDuration);
    QFETCH(QList<unsigned int>, jobDurations);

    TaskScheduler scheduler;

    bool outcome;
    try
    {
        scheduler.schedule(machineDuration, jobDurations);
        outcome = true;
    }
    catch(...)
    {
        outcome = false;
    }

    QVERIFY(outcome);
}

void SchedulingTest::testCanScheduleMultipleTimes_data()
{
    QTest::addColumn<unsigned int>("machineDuration");
    QTest::addColumn<QList<unsigned int> >("jobDurations");

    QTest::newRow("more_machines") << (uint)15 << QList<unsigned int>({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    QTest::newRow("more_jobs") << (uint)3 << QList<unsigned int>({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    QTest::newRow("single_machine") << (uint)1 << QList<unsigned int>({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    QTest::newRow("large_job") << (uint)10 << QList<unsigned int>({150});
}

void SchedulingTest::testCanScheduleMultipleTimes()
{
    QFETCH(unsigned int, machineDuration);
    QFETCH(QList<unsigned int>, jobDurations);

    TaskScheduler scheduler;

    bool outcome;
    try
    {
        scheduler.schedule(machineDuration, jobDurations);
        scheduler.schedule(machineDuration, jobDurations);
        scheduler.schedule(machineDuration, jobDurations);
        scheduler.schedule(machineDuration, jobDurations);
        outcome = true;
    }
    catch(...)
    {
        outcome = false;
    }

    QVERIFY(outcome);
}
