#pragma once

#include <functional>
#include <memory>
#include <QHash>
#include <QSet>

#include "CoreLink/Process.h"
#include "CoreLink/Types.h"

namespace CoreLink
{

class Program;
class Process;

class Node;
typedef QList<Node*> NodeList;

/// Represents a computer on which programs can run.
class Node
{
public:
    /// A function used to post messages to other nodes.
    typedef std::function<void(NodeID, Message)> PostFcn;

private:
    const GameSettings& m_settings;
    typedef std::shared_ptr<Process> ProcessPtr;
    typedef QHash<PID,ProcessPtr> ProcessMap;
    typedef QHash<ProgramID, Program*> ProgramMap;
    typedef QList<Message> MessageList;
    typedef QSet<NodeID> NodeIDSet;
    ProcessMap m_running_programs;
    PIDList m_finished_programs;
    ProgramMap m_installed_programs;
    int m_next_pid;
    NodeIDSet m_neighbors;
    NodeID m_id;
    MessageList m_mailbox; 
    PostFcn m_post;

public:

    /// Construct a new node.
    Node(const GameSettings& settings, PostFcn post = PostFcn());
    
    /// Run the active programs on the node for the given number of cycles.
    void tick();

    /// Process pending messages in the mailbox.
    void processMailbox();

    /// Remove any processes that have exited.
    void removeFinishedProcesses();

    /// Add the given node to this node's adjacency list.
    /// \param[in] node_p The node to add.
    void addNeighbor(NodeID node);


    /// Get the ID of this node.
    /// \return The ID.
    NodeID getID() const;

    /// Get the PIDs of all the running processes on this node.
    /// \return The PIDs.
    PIDList getRunningPrograms() const;

    /// Get the program IDs of all the installed programs on this
    /// node.
    /// \return The program IDs.
    ProgramIDList getInstalledPrograms() const;

    /// Get the ID of the program being executed by the process with the given
    /// PID.
    /// \param[in] pid The ID of the process to look for.
    /// \return The program ID, or a null program ID if not found.
    ProgramID getProgramID(PID pid) const;

    /// Get the PID of the instance of the program with the given ID.
    /// \param[in] id The program ID to look for.
    /// \return The PID, or a null PID if not found.
    PID getPID(ProgramID id) const;

    /// Get the nodes connected to this node.
    /// \return The nodes.
    NodeIDList getNeighbors() const;

    /// Check whether the node has a neighbor with the given ID.
    /// \return True if the node is a neighbor of this node.
    bool hasNeighbor(NodeID node) const;
    

    /// Spawn a process for the program with the given ID.
    /// \param[in] id The program to start.
    /// \return The PID of the new process, or a null PID if the process failed
    ///         to start.
    PID spawnProcess(ProgramID id);

    /// Install the given program on this node.
    /// \param[in] program_p The node to start.
    /// \return True if successfully installed, or false if the program was
    ///         unable to be installed.
    bool installProgram(Program *program_p);

    /// Delete the program with the given ID from this node.
    /// \param[in] id The ID.
    /// \return True if the program was successfully deleted.
    bool deleteProgram(ProgramID id);

    /// Kill the process with the given PID.
    /// \param[in] id The PID.
    /// \return True if the process was successfully killed.
    bool killProcess(PID id);

    /// Post a message to this node.
    /// \param[in] msg The message to post.
    void postMessage(Message msg);

    /// Post a message to a neighboring node.
    /// \param[in] node The ID of the node to post to.
    /// \param[in] msg The message to post.
    bool postMessage(NodeID node, Message msg);
};

} // namespace CoreLink
