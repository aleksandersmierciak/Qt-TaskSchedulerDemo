#include <stdexcept>
#include <QDebug>
#include <QListIterator>
#include "taskscheduler.h"


TaskScheduler::TaskScheduler(QObject *parent)
    : QObject(parent)
{
}

void TaskScheduler::schedule(unsigned int machineCount, QList<int> jobDurations)
{
    initializeJobs(jobDurations);
    calculateMaxTime(machineCount);
    initializeMachines(machineCount);

    assignJobs();
}

QVariantList TaskScheduler::getResults()
{
    QVariantList results;
    for (auto machine : m_machines)
    {
        QVariantList innerList;
        for (auto job : machine.data()->jobs())
        {
            innerList.append(QVariant(QVariantList({job.data()->id(), job.data()->duration()})));
        }
        results.append(QVariant(innerList));
    }
    return results;
}

void TaskScheduler::initializeMachines(const unsigned int size)
{
    if (size == 0)
    {
        throw std::invalid_argument("One or more machines need to be provided");
    }
    m_machines.clear();
    for (unsigned int i = 0; i < size; ++i)
    {
        m_machines.append(QSharedPointer<Machine>(new Machine(i, m_maxTime)));
    }
}

void TaskScheduler::initializeJobs(QList<int> jobDurations)
{
    if (jobDurations.size() == 0)
    {
        throw std::invalid_argument("One or more jobs need to be provided");
    }
    m_jobs.clear();
    for (int i = 0; i < jobDurations.size(); ++i)
    {
        m_jobs.append(QSharedPointer<Job>(new Job(i, jobDurations.at(i))));
    }
}

void TaskScheduler::calculateMaxTime(unsigned int machineCount)
{
    unsigned int maxTime = 0;
    unsigned int totalDuration = 0;
    for (auto job : m_jobs)
    {
        maxTime = std::max(maxTime, job.data()->duration());
        totalDuration += job.data()->duration();
    }
    totalDuration /= machineCount;

    m_maxTime = std::max(maxTime, totalDuration);
}

void TaskScheduler::assignJobs()
{
    QListIterator<QSharedPointer<Machine> > machineIterator(m_machines);
    QMutableListIterator<QSharedPointer<Job> > jobIterator(m_jobs);
    while (machineIterator.hasNext())
    {
        Machine &machine = *machineIterator.next();
        while (jobIterator.hasNext())
        {
            QSharedPointer<Job> job = jobIterator.peekNext();
            if (machine.canAdd(job))
            {
                machine.add(job);
                jobIterator.next();
            }
            else
            {
                unsigned int durationLeft = machine.durationLeft();
                if (durationLeft > 0)
                {
                    QSharedPointer<Job> splitJob = job.data()->split(durationLeft);
                    jobIterator.insert(splitJob);
                    machine.add(splitJob);
                }
                break;
            }
        }
    }
}
