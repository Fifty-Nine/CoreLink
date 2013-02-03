#pragma once

#include <memory>
#include <QHash>

#include "CoreLink/Process.h"
#include "CoreLink/Types.h"

namespace CoreLink
{

class Program;
class Process;

class Node;
typedef QList<Node*> NodeList;

class Node
{
    typedef std::shared_ptr<Process> ProcessPtr;
    typedef QHash<PID,ProcessPtr> ProcessMap;
    typedef QHash<ProgramID, Program*> ProgramMap;
    ProcessMap m_running_programs;
    ProgramMap m_installed_programs;
    int m_next_pid;
    NodeList m_neighbors;
    NodeID m_id;

public:
    Node();
    
    void tick(int time_quanta);
    void addNeighbor(Node *node_p);

    NodeID getID() const;
    PIDList getRunningPrograms() const;
    ProgramIDList getInstalledPrograms() const;
    ProgramID getProgramID(PID id) const;
    PID getPID(ProgramID id) const;
    NodeList getNeighbors() const;
    
    PID spawnProcess(ProgramID id);
    bool installProgram(Program *program_p);
    bool deleteProgram(ProgramID id);
    bool killProcess(PID id);
};

} // namespace CoreLink
