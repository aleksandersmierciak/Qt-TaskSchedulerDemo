#include <QSharedPointer>
#include "tst_machinetest.h"
#include "machine.h"

MachineTest::MachineTest()
{
}

void MachineTest::testCanCreateWithPositiveDuration()
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

void MachineTest::testCannotCreateWithZeroDuration()
{
    bool outcome;
    try
    {
        Machine(1, 0);
        outcome = true;
    }
    catch (...)
    {
        outcome = false;
    }
    QVERIFY(!outcome);
}

void MachineTest::testCanAddJob_data()
{
    QTest::addColumn<int>("machineDuration");
    QTest::addColumn<int>("jobDuration");

    QTest::newRow("more_than_enough") << 10 << 5;
    QTest::newRow("just_enough") << 10 << 10;
}

void MachineTest::testCanAddJob()
{
    QFETCH(int, machineDuration);
    QFETCH(int, jobDuration);

    Machine machine = Machine(1, machineDuration);
    QSharedPointer<Job> job = QSharedPointer<Job>(new Job(1, jobDuration));

    QVERIFY(machine.canAdd(job));
}

void MachineTest::testCannotAddJob_data()
{
    QTest::addColumn<int>("machineDuration");
    QTest::addColumn<int>("jobDuration");

    QTest::newRow("insufficient_duration_left") << 10 << 11;
}

void MachineTest::testCannotAddJob()
{
    QFETCH(int, machineDuration);
    QFETCH(int, jobDuration);

    Machine machine = Machine(1, machineDuration);
    QSharedPointer<Job> job = QSharedPointer<Job>(new Job(1, jobDuration));

    QVERIFY(!machine.canAdd(job));
}

void MachineTest::testJobAdd_data()
{

}

void MachineTest::testJobAdd()
{

}

void MachineTest::testJobTryAdd_data()
{

}

void MachineTest::testJobTryAdd()
{

}
