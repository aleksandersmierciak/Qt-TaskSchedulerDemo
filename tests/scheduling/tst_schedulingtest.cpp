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
    QTest::addColumn<int>("machineDuration");
    QTest::addColumn<QList<int> >("jobDurations");

    QTest::newRow("no_machines")    << 0  << QList<int>({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    QTest::newRow("no_jobs")        << 3  << QList<int>();
    QTest::newRow("zero_job")       << 10 << QList<int>({0});
}

void SchedulingTest::testCannotCreate()
{
    QFETCH(int, machineDuration);
    QFETCH(QList<int>, jobDurations);

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
    QTest::addColumn<int>("machineDuration");
    QTest::addColumn<QList<int> >("jobDurations");

    QTest::newRow("more_machines")  << 15 << QList<int>({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    QTest::newRow("more_jobs")      << 3  << QList<int>({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    QTest::newRow("single_machine") << 1  << QList<int>({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    QTest::newRow("large_job")      << 10 << QList<int>({150});
}

void SchedulingTest::testCanSchedule()
{
    QFETCH(int, machineDuration);
    QFETCH(QList<int>, jobDurations);

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
    QTest::addColumn<int>("machineDuration");
    QTest::addColumn<QList<int> >("jobDurations");

    QTest::newRow("more_machines")  << (uint)15 << QList<int>({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    QTest::newRow("more_jobs")      << (uint)3  << QList<int>({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    QTest::newRow("single_machine") << (uint)1  << QList<int>({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    QTest::newRow("large_job")      << (uint)10 << QList<int>({150});
}

void SchedulingTest::testCanScheduleMultipleTimes()
{
    QFETCH(int, machineDuration);
    QFETCH(QList<int>, jobDurations);

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
