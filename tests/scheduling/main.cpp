#include <QtTest/QtTest>

#include "tst_jobtest.h"
#include "tst_machinetest.h"
#include "tst_schedulingtest.h"

int main()
{
    JobTest jobTest;
    QTest::qExec(&jobTest);

    MachineTest machineTest;
    QTest::qExec(&machineTest);

    SchedulingTest schedulingTest;
    QTest::qExec(&schedulingTest);

    return 0;
}
