#pragma once

#include <memory>
#include <QHash>

#include "CoreLink/Process.h"
#include "CoreLink/Types.h"

namespace CoreLink
{

class Program;
class Process;

class Node
{
    typedef std::shared_ptr<Process> ProcessPtr;
    typedef QHash<PID,ProcessPtr> ProcessMap;
    typedef QHash<ProgramID, Program*> ProgramMap;
    ProcessMap m_running_programs;
    ProgramMap m_installed_programs;
    int m_next_pid;

public:
    Node();
    
    void tick(int time_quanta);

    PIDList getRunningPrograms() const;
    ProgramIDList getInstalledPrograms() const;
    ProgramID getProgramID(PID id) const;
    PID getPID(ProgramID id) const;
    
    PID spawnProcess(ProgramID id);
    bool installProgram(Program *program_p);
    bool deleteProgram(ProgramID id);
    bool killProcess(PID id);
};

} // namespace CoreLink
