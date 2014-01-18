#include <stdexcept>
#include "machine.h"

Machine::Machine(const int id, unsigned int duration)
    : m_id(id), m_duration(duration), m_durationLeft(duration)
{
    if (duration == 0)
    {
        throw std::invalid_argument("Duration cannot be zero");
    }
}

int Machine::id() const
{
    return m_id;
}

unsigned int Machine::duration() const
{
    return m_duration;
}

QList<QSharedPointer<Job> > Machine::jobs() const
{
    return m_jobs;
}

bool Machine::tryAdd(QSharedPointer<Job> job)
{
    bool outcome = canAdd(job);
    if (outcome)
    {
        try
        {
            add(job);
        }
        catch (int e)
        {
            outcome = false;
        }
    }
    return outcome;
}

void Machine::add(QSharedPointer<Job> job)
{
    if (!canAdd(job))
    {
        throw m_durationLeft - job.data()->duration();
    }

    m_jobs.append(job);
    m_durationLeft -= job.data()->duration();
}

bool Machine::canAdd(QSharedPointer<Job> job) const
{
    return (job.data()->duration() > 0 &&
            ((int)m_durationLeft - (int)job.data()->duration()) >= 0);
}
