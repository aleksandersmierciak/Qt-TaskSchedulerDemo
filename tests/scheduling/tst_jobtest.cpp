#include <QString>
#include <QtTest>

#include <QSharedPointer>
#include "tst_jobtest.h"
#include "job.h"

JobTest::JobTest()
{
}

void JobTest::testCanCreateWithPositiveDuration()
{
    bool outcome;
    try
    {
        Job(1, 1);
        outcome = true;
    }
    catch (...)
    {
        outcome = false;
    }
    QVERIFY(outcome);
}

void JobTest::testCannotCreateWithZeroDuration()
{
    bool outcome;
    try
    {
        Job(1, 0);
        outcome = true;
    }
    catch (...)
    {
        outcome = false;
    }
    QVERIFY(!outcome);
}

void JobTest::testSplittedJobsIds()
{
    Job first = Job(1, 5);
    QSharedPointer<Job> second = first.split(3);
    QVERIFY(first.id() == second.data()->id());
}

void JobTest::testSplittedJobsDuration()
{
    Job first = Job(1, 5);
    first.split(3);
    QVERIFY(first.duration() == 3);
}

void JobTest::testSplittedJobsDuration2()
{
    Job first = Job(1, 5);
    QSharedPointer<Job> second = first.split(3);
    QVERIFY(second.data()->duration() == 2);
}
