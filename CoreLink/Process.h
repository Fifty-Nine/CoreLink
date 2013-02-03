#pragma once

#include <memory>

#include "CoreLink/Types.h"

namespace CoreLink
{

class Node;
class Program;

/// Represents an instance of a program on a node.
class Process
{
    struct Data;
    std::unique_ptr<Data> d; 

public:
    /// Create a new process.
    /// \param[in] program The program executed by the process.
    /// \param[in] node The node the process runs on.
    /// \param[in] pid The ID of the process on the given node.
    Process(Program& program, Node& node, PID pid);

    /// Destructor.
    ~Process();

    
    /// Get the ID of the program being executed by this process.
    /// \return The ID.
    ProgramID getProgramID() const;

    /// Get the PID of this process.
    PID getPID() const;

    /// Run this process for the given number of cycles.
    /// \param[in] time The number of cycles to run.
    /// \return True if the process is still running.
    bool run(int time);
};

} // namespace CoreLink
