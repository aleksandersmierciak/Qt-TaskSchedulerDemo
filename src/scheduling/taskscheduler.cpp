#include <stdexcept>
#include <QDebug>
#include <QListIterator>
#include "taskscheduler.h"


TaskScheduler::TaskScheduler(QObject *parent)
    : QObject(parent)
{
}

void TaskScheduler::schedule(int machineCount, QList<QSharedPointer<Job> > jobs)
{
    if (jobs.count() == 0)
    {
        throw std::invalid_argument("One or more jobs need to be provided");
    }
    if (m_machineCount == 0)
    {
        throw std::invalid_argument("One or more machines need to be provided");
    }

    m_jobs = jobs;
    m_machineCount = machineCount;

    calculateMaxTime();
    initializeMachines();
    assignJobs();
}

void TaskScheduler::initializeMachines()
{
    clear();
    for (unsigned int i = 0; i < m_machineCount; ++i)
    {
        m_machines.append(QSharedPointer<Machine>(new Machine(i, m_maxTime)));
    }
}

void TaskScheduler::clear()
{
    m_machines.clear();
}

void TaskScheduler::calculateMaxTime()
{
    unsigned int maxTime = 0;
    unsigned int totalDuration = 0;
    for (auto job : m_jobs)
    {
        maxTime = std::max(maxTime, job.data()->duration());
        totalDuration += job.data()->duration();
    }
    totalDuration /= m_machineCount;

    m_maxTime = std::max(maxTime, totalDuration);
}

void TaskScheduler::assignJobs()
{
    QListIterator<QSharedPointer<Machine> > machineIterator(m_machines);
    QListIterator<QSharedPointer<Job> > jobIterator(m_jobs);
    while (jobIterator.hasNext())
    {
        Machine &machine = *machineIterator.peekNext();
        QSharedPointer<Job> job = jobIterator.peekNext();
        if (!machine.tryAdd(job))
        {
            unsigned int durationLeft = machine.durationLeft();
            if (durationLeft > 0)
            {
                QSharedPointer<Job> splitJob = job.data()->split(durationLeft);
                machine.add(job);
                machineIterator.next();
                machineIterator.peekNext().data()->add(splitJob);
                jobIterator.next();
            }
            else
            {
                machineIterator.next();
            }
        }
        else
        {
            jobIterator.next();
        }
    }
}
