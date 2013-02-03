#include "CoreLink/InstructionSet.h"

#include "CoreLink/Node.h"

namespace CoreLink { 

InstructionSet::InstructionSet(YieldFcn yield, ExitFcn exit, Node& node) :
    m_yield(yield), m_exit(exit), m_node(node)
{
}

void InstructionSet::noOp() const
{
    m_yield(1);
}

void InstructionSet::wait(int time) const
{
    m_yield(time);
}

PIDList InstructionSet::getRunningPrograms() const
{
    m_yield(1);
    return m_node.getRunningPrograms();
}

ProgramIDList InstructionSet::getInstalledPrograms() const
{
    m_yield(1);
    return m_node.getInstalledPrograms();
}

ProgramID InstructionSet::getProgramID(PID pid) const
{
    m_yield(1);
    return m_node.getProgramID(pid);
}

bool InstructionSet::killProcess(PID pid)
{
    m_yield(5);
    return m_node.killProcess(pid);
}

bool InstructionSet::deleteProgram(ProgramID id)
{
    m_yield(5);
    return m_node.deleteProgram(id);
}

void InstructionSet::exit()
{
    m_exit();
}

} // namespace CoreLink

