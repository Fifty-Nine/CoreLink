#pragma once

#include <functional>
#include <QList>

#include "CoreLink/Types.h"

namespace CoreLink {

class Node;

/// Represents the set of instructions available to a program.
class InstructionSet
{
public:
    typedef std::function<void(InstructionCost::Enum)> YieldFcn;
    typedef std::function<void(void)> ExitFcn;

private:
    YieldFcn m_yield;
    ExitFcn m_exit;
    Node& m_node;

public:
    /// Create a new instruction set.
    /// \param[in] yield The function called to yield a specific amount
    ///                  of processor time.
    /// \param[in] exit The function called to end execution.
    /// \param[in] node The node we're executing on.
    InstructionSet(YieldFcn yield, ExitFcn exit, Node& node);

    /// Do nothing for one instruction cycle.
    void noOp() const;

    /// Yield the remaining time slice.
    void yield() const;

    /// Get the list of running programs on the current node.
    /// \return The PIDs of the running programs.
    PIDList getRunningPrograms() const;

    /// Get the list of installed programs on the current node.
    /// \return The ProgramIDs of the installed programs.
    ProgramIDList getInstalledPrograms() const;

    /// Get the ID of the program being executed by the process
    /// with the given ID.
    /// \return The program ID, or a null ID if not found.
    ProgramID getProgramID(PID process_id) const;

    /// Kill the process on the current node with the given ID.
    /// \param[in[ pid The ID of the process to kill.
    /// \return True if a process with the given ID was successfully killed.
    bool killProcess(PID pid);

    /// Delete the program from the current node with the given ID.
    /// \param[in] id The ID of the program to delete.
    /// \return True if a program with the given ID was successfully deleted.
    bool deleteProgram(ProgramID id);

    /// Get the IDs of the nodes that are connected to the current node.
    /// \return The IDs.
    NodeIDList getNeighbors() const;

    /// Exit the currently running process.
    void exit();
};

} // namespace CoreLink
