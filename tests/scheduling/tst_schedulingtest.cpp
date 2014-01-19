#include <QString>
#include <QtTest>

#include "tst_schedulingtest.h"
#include "taskscheduler.h"

SchedulingTest::SchedulingTest()
{
}

void SchedulingTest::testScheduling()
{
    TaskScheduler scheduler;
    QList<int> jobDurations;
    for (int i = 1; i <= 50; ++i)
    {
        jobDurations.append(i);
    }
    scheduler.schedule(15, jobDurations);
    QVERIFY2(true, "Failure");
}
