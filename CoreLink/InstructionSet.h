#pragma once

#include <functional>
#include <QList>

#include "CoreLink/Types.h"

namespace CoreLink {

class Node;

class InstructionSet
{
public:
    typedef std::function<void(int)> YieldFcn;
    typedef std::function<void(void)> ExitFcn;

private:
    YieldFcn m_yield;
    ExitFcn m_exit;
    Node& m_node;

public:

    InstructionSet(YieldFcn yield, ExitFcn exit, Node& m_node);

    void noOp() const;
    PIDList getRunningPrograms() const;
    ProgramIDList getInstalledPrograms() const;
    ProgramID getProgramID(PID process_id) const;
    bool killProcess(PID process_id);
    bool deleteProgram(ProgramID id);
    void exit();
};

} // namespace CoreLink
