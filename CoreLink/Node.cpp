#include "CoreLink/Node.h"

#include "CoreLink/Program.h"

namespace CoreLink { 

Node::Node() : 
    m_next_pid(1)
{
}

void Node::tick(int quanta)
{
    if ((quanta <= 0) || m_running_programs.empty())
    {
        return;
    }

    quanta /= m_running_programs.count();
    quanta = std::max(1, quanta);
    
    PIDList finished;

    for (ProcessPtr& p: m_running_programs)
    {
        if (p->run(quanta))
        {
            finished << p->getPID();
        }
    }

    for (PID p: finished)
    {
        m_running_programs.remove(p);
    }
}

PIDList Node::getRunningPrograms() const
{
    return m_running_programs.keys();
}

ProgramIDList Node::getInstalledPrograms() const
{
    return m_installed_programs.keys();
}

ProgramID Node::getProgramID(PID id) const
{
    ProcessMap::const_iterator it = m_running_programs.find(id);

    return (it != m_running_programs.end()) ? it.value()->getProgramID() : PID();
}

PID Node::getPID(ProgramID id) const
{
    for (const ProcessPtr& p: m_running_programs)
    {
        if (p->getProgramID() == id)
        {
            return p->getPID();
        }
    }

    return -1;
}

PID Node::spawnProcess(ProgramID id)
{
    ProgramMap::const_iterator it = m_installed_programs.find(id);
    if ((it == m_installed_programs.end()) && (getPID(id) != PID()))
    {
        return -1;
    }

    int pid = m_next_pid++;
    ProcessPtr p(new Process(*it.value(), *this, pid));
    m_running_programs.insert(pid, std::move(p));

    return pid;
}

bool Node::installProgram(Program *program_p)
{
    ProgramID id = program_p->getID();
    if (m_installed_programs.contains(id))
    {
        return false;
    }

    m_installed_programs.insert(id, program_p);

    return true;
}

bool Node::deleteProgram(ProgramID id)
{
    ProgramMap::iterator it = m_installed_programs.find(id);
    if ((it == m_installed_programs.end()) || 
        (getPID(id) != PID()))
    {
        return false;
    }

    m_installed_programs.erase(it);

    return true;
}

bool Node::killProcess(PID id)
{
    ProcessMap::iterator it = m_running_programs.find(id);
    if (it == m_running_programs.end())
    {
        return false;
    }

    m_running_programs.erase(it);
    return true;
}

} // namespace CoreLink
