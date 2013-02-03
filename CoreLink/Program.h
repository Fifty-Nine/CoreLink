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
    ProgramID getID() const { return m_id; }

    virtual void main(InstructionSet& is) = 0;

protected:
    Program();
};

} // namespace CoreLink
