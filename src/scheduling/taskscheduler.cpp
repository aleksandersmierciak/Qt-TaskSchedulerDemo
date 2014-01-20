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

    const unsigned int maxTime = calculateMaxTime(size);

    m_machines.clear();
    for (unsigned int i = 0; i < size; ++i)
    {
        m_machines.append(QSharedPointer<Machine>(new Machine(i, maxTime)));
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

unsigned int TaskScheduler::calculateMaxTime(const unsigned int machineCount)
{
    unsigned int maxSingleTime = 0;
    unsigned int meanTimePerMachine = 0;
    for (auto job : m_jobs)
    {
        maxSingleTime = std::max(maxSingleTime, job.data()->duration());
        meanTimePerMachine += job.data()->duration();
    }

    meanTimePerMachine = (int) std::ceil((double)meanTimePerMachine / machineCount);
    return std::max(maxSingleTime, meanTimePerMachine);
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
