#ifndef JOB_H
#define JOB_H

#include <QSharedPointer>

class Job
{
public:
    Job(const int id, unsigned int duration);
    int id() const;
    unsigned int duration() const;

    QSharedPointer<Job> split(const unsigned int firstDuration);

private:
    const int m_id;
    unsigned int m_duration;
};

#endif // JOB_H
