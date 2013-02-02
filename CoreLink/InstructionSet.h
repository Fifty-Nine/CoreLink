#pragma once

#include <boost/function.hpp>
#include <QList>

#include "CoreLink/Types.h"

namespace CoreLink {

class Node;

class InstructionSet
{
public:
    typedef boost::function<void(int)> YieldFcn;

private:
    YieldFcn m_yield;
    Node& m_node;

public:

    InstructionSet(YieldFcn yield, Node& m_node);

    void noOp() const;
    PIDList getRunningPrograms() const;
    ProgramIDList getInstalledPrograms() const;
    ProgramID getProgramID(PID process_id) const;
    bool killProcess(PID process_id);
    bool deleteProgram(ProgramID id);
};

} // namespace CoreLink
