#include <stdexcept>
#include "job.h"

Job::Job(const int id, const unsigned int duration)
    : m_id(id), m_duration(duration)
{
    if (duration == 0)
    {
        throw std::invalid_argument("Duration cannot be zero");
    }
}

int Job::id() const
{
    return m_id;
}

unsigned int Job::duration() const
{
    return m_duration;
}

QSharedPointer<Job> Job::split(const unsigned int firstDuration)
{
    m_duration -= firstDuration;
    return QSharedPointer<Job>(new Job(m_id, firstDuration));
}
