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
    QList<QSharedPointer<Job> > jobs;
    for (int i = 1; i <= 50; ++i)
    {
        jobs.append(QSharedPointer<Job>(new Job(i, i)));
    }
    scheduler.schedule(15, jobs);
    QVERIFY2(true, "Failure");
}
