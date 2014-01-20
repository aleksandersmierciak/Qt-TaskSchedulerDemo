#ifndef TASKSCHEDULER_H
#define TASKSCHEDULER_H

#include <QList>
#include <QObject>
#include <QSharedPointer>
#include <QVariantList>
#include "scheduling_global.h"
#include "machine.h"

class SCHEDULINGSHARED_EXPORT TaskScheduler : public QObject
{
    Q_OBJECT

public:
    TaskScheduler(QObject *parent = 0);

    Q_INVOKABLE void schedule(unsigned int , QList<int> );
    Q_INVOKABLE QVariantList getResults();

private:
    unsigned int m_maxTime;
    QList<QSharedPointer<Machine> > m_machines;
    QList<QSharedPointer<Job> > m_jobs;

    void initializeMachines(const unsigned int );
    void initializeJobs(QList<int> );
    unsigned int calculateMaxTime(const unsigned int machineCount);
    void assignJobs();
};

#endif // TASKSCHEDULER_H
