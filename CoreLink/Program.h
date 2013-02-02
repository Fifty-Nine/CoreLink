#pragma once

#include "CoreLink/Types.h"

namespace CoreLink
{

class InstructionSet;
class Node;

class Program
{
    ProgramID m_id;

public:
    Process start(Node& node, PID pid);
    ProgramID getID() const { return m_id; }

    virtual void main(InstructionSet& is);

protected:
    Program();

};

} // namespace CoreLink
