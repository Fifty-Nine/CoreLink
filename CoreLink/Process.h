#pragma once

#include "CoreLink/Types.h"

namespace CoreLink
{

class Node;
class Program;

class Process
{
    ProgramID m_program_id;
    Node& m_node;
    PID m_pid;
    int m_remaining_time;

public:
    Process(Program& program, Node& node, PID pid);

    ProgramID getProgramID() const;
    PID getPID() const;

    Node& getNode();
    const Node& getNode() const;

    bool run(int time);

private:
    void yield(int time);
};

} // namespace CoreLink
