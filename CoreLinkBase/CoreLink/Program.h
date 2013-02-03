#pragma once

#include "CoreLink/Types.h"

namespace CoreLink
{

class InstructionSet;
class Node;

/// Represents a program that may be run on a node.
class Program
{
    ProgramID m_id;

public:
    /// Get the ID for this program.
    /// \return The ID.
    ProgramID getID() const { return m_id; }

    /// The main function for this program.
    /// \param[in] is The instruction set instance
    ///               used by this program.
    virtual void main(InstructionSet& is) = 0;

protected:
    /// Constructor.
    Program();
};

} // namespace CoreLink
