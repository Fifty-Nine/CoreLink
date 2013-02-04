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

    /// Get the list of running programs on the given node.
    /// \param[in] id The ID of the node to examine.
    /// \return The PIDs of the running programs.
    PIDList getRunningPrograms(NodeID dest = NodeID()) const;

    /// Get the list of installed programs on the given node.
    /// \param[in] dest The ID of the node, or a null ID for the current node.
    /// \return The ProgramIDs of the installed programs.
    ProgramIDList getInstalledPrograms(NodeID dest = NodeID()) const;

    /// Get the ID of the program being executed by the process
    /// with the given ID.
    /// \param[in] pid The process ID to look for.
    /// \param[in] dest The ID of the node to execute on.
    /// \return The program ID, or a null ID if not found.
    ProgramID getProgramID(PID process_id, NodeID dest = NodeID()) const;

    /// Spawn the given process on the given node.
    /// \param[in] program The program to start.
    /// \param[in] dest The node to spawn the process on.
    /// \return The PID of the spawned process, or PID() on failure.
    PID spawnProcess(ProgramID program, NodeID dest = NodeID());

    /// Kill the given process on the given node.
    /// \param[in] pid The ID of the process to kill.
    /// \param[in] dest The ID of the node to execute on.
    /// \return True if a process with the given ID was successfully killed.
    bool killProcess(PID pid, NodeID dest = NodeID());

    /// Delete the program from the current node with the given ID.
    /// \param[in] id The ID of the program to delete.
    /// \return True if a program with the given ID was successfully deleted.
    bool deleteProgram(ProgramID id, NodeID dest = NodeID());

    /// Get the IDs of the nodes that are connected to the current node.
    /// \return The IDs.
    NodeIDList getNeighbors() const;

    /// Exit the currently running process.
    void exit();

private:
    template<class Fcn>
    void WrapCall(NodeID dest, InstructionCost::Enum cost, Fcn f) const;
    template<class Fcn>
    void WrapCall(NodeID dest, InstructionCost::Enum cost, Fcn f, typename Fcn::result_type& result) const;
};

} // namespace CoreLink
