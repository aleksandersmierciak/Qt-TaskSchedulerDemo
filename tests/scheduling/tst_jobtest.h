#ifndef TST_JOBTEST_H
#define TST_JOBTEST_H

#include <QString>
#include <QtTest>

class JobTest : public QObject
{
    Q_OBJECT

public:
    JobTest();

private Q_SLOTS:
    void testCanCreateWithPositiveDuration();
    void testCannotCreateWithZeroDuration();
    void testSplittedJobsIds();
    void testSplittedJobsDuration();
    void testSplittedJobsDuration2();
};

#endif // TST_JOBTEST_H
