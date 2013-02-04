#include "CoreLink/InstructionSet.h"

#include "CoreLink/Node.h"

namespace CoreLink { 

using namespace std::placeholders;

template<class Fcn>
Message CreateMessage(Fcn f, typename Fcn::result_type& result)
{
    return [&](Node& n) { result = f(n); };
}

template<class Fcn>
void InstructionSet::WrapCall(NodeID dest, InstructionCost::Enum cost, Fcn f) const
{
    m_yield(cost);
    if (dest == NodeID())
    {
        f(m_node);
        return;
    }

    (void)m_node.postMessage(dest, f); 

    yield();
}

template<class Fcn>
void InstructionSet::WrapCall(
    NodeID dest, InstructionCost::Enum cost, Fcn f, typename Fcn::result_type& r)
    const
{
    m_yield(cost);
    if (dest == NodeID())
    {
        r = f(m_node);
        return;
    }

    (void)m_node.postMessage(dest, CreateMessage(f, r));

    yield();
}

InstructionSet::InstructionSet(YieldFcn yield, ExitFcn exit, Node& node) :
    m_yield(yield), m_exit(exit), m_node(node)
{
}

void InstructionSet::noOp() const
{
    m_yield(InstructionCost::Cheap);
}

void InstructionSet::yield() const
{
    m_yield(InstructionCost::Slice);
}

PIDList InstructionSet::getRunningPrograms(NodeID id) const
{
    PIDList r;
    WrapCall(id, InstructionCost::Cheap, std::mem_fn(&Node::getRunningPrograms), r);
    return r;
}

ProgramIDList InstructionSet::getInstalledPrograms(NodeID id) const
{
    ProgramIDList r;
    WrapCall(id, InstructionCost::Cheap, std::mem_fn(&Node::getInstalledPrograms), r);
    return r;
}

ProgramID InstructionSet::getProgramID(PID pid, NodeID dest) const
{
    ProgramID r;
    WrapCall(dest, InstructionCost::Cheap, 
        std::bind(&Node::getProgramID, _1, pid), r);
    return r;
}

PID InstructionSet::spawnProcess(ProgramID program, NodeID dest)
{
    PID r;
    WrapCall(dest, InstructionCost::Moderate, 
        std::bind(&Node::spawnProcess, _1, program), r );
    return r;
}

bool InstructionSet::killProcess(PID pid, NodeID dest)
{
    bool r;
    WrapCall(dest, InstructionCost::Expensive,
        std::bind(&Node::killProcess, _1, pid), r);
    return r;
}

bool InstructionSet::deleteProgram(ProgramID id, NodeID dest)
{
    bool r;
    WrapCall(dest, InstructionCost::Extreme, 
        std::bind(&Node::deleteProgram, _1, id), r);
    return r;
}

NodeIDList InstructionSet::getNeighbors() const
{
    m_yield(InstructionCost::Cheap);
    return m_node.getNeighbors();
}

void InstructionSet::exit()
{
    m_exit();
}

} // namespace CoreLink

