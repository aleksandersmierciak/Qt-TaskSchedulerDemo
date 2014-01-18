#ifndef TASKSCHEDULER_H
#define TASKSCHEDULER_H

#include <QList>
#include <QSharedPointer>
#include "scheduling_global.h"
#include "machine.h"

class SCHEDULINGSHARED_EXPORT TaskScheduler
{
public:
    TaskScheduler();

    void schedule(int machineCount, QList<QSharedPointer<Job> > jobs);

private:
    unsigned int m_maxTime;
    unsigned int m_machineCount;
    QList<QSharedPointer<Machine> > m_machines;
    QList<QSharedPointer<Job> > m_jobs;

    void initializeMachines();
    void clear();
    void calculateMaxTime();
    void assignJobs();
};

#endif // TASKSCHEDULER_H
