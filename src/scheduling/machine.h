#ifndef MACHINE_H
#define MACHINE_H

#include <QList>
#include "job.h"

class Machine
{
public:
    Machine(const int id, unsigned int duration);

    int id() const;
    unsigned int duration() const;
    unsigned int durationLeft() const;
    QList<QSharedPointer<Job> > jobs() const;

    bool tryAdd(QSharedPointer<Job>);
    void add(QSharedPointer<Job>);
    bool canAdd(QSharedPointer<Job>) const;

private:
    int m_id;
    unsigned int m_duration;
    unsigned int m_durationLeft;
    QList<QSharedPointer<Job> > m_jobs;
};

#endif // MACHINE_H
