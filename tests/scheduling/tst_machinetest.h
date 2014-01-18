#ifndef TST_MACHINETEST_H
#define TST_MACHINETEST_H

#include <QString>
#include <QtTest>

class MachineTest : public QObject
{
    Q_OBJECT

public:
    MachineTest();

private Q_SLOTS:
    void testCanCreateWithPositiveDuration();
    void testCannotCreateWithZeroDuration();
    void testCanAddJob_data();
    void testCanAddJob();
    void testCannotAddJob_data();
    void testCannotAddJob();
    void testJobAdd_data();
    void testJobAdd();
    void testJobTryAdd_data();
    void testJobTryAdd();
};

#endif // TST_MACHINETEST_H
