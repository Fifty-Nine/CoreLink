#include "CoreLink/Process.h"

#include <functional>
#include <ucontext.h>
#include "CoreLink/GameSettings.h"
#include "CoreLink/InstructionSet.h"
#include "CoreLink/Program.h"

namespace CoreLink { 

using namespace std::placeholders;

struct ProcessKilledException { };

static void runProgram(Program *program_p, InstructionSet *is_p)
{
    try
    {
        program_p->main(*is_p);
    }
    catch (ProcessKilledException) { }

    is_p->exit();
}

struct Process::Data
{
    const GameSettings& m_settings;
    ProgramID m_program_id;
    PID m_pid;
    int m_remaining_time;
    InstructionSet m_is;
    ucontext_t runner_context;
    ucontext_t program_context;
    char stack[8192];

    Data(const GameSettings& settings, Program& p, Node& n, PID pid) : 
        m_settings(settings),
        m_program_id(p.getID()), 
        m_pid(pid),
        m_remaining_time(0),
        m_is(
            std::bind(&Data::yield, this, _1),
            std::bind(&Data::exit, this), n)
    {
        getcontext(&program_context);
        program_context.uc_stack.ss_sp = stack;
        program_context.uc_stack.ss_size = sizeof(stack);
        program_context.uc_link = &runner_context;
        makecontext(&program_context, (void (*)(void)) &runProgram, 2, &p, &m_is);
    }

    ~Data()
    {
        if (m_remaining_time >= 0)
        {
            m_remaining_time = -1;
            swapcontext(&runner_context, &program_context);
        }
    }

    void yield(InstructionCost::Enum cost)
    {
        int time = (cost == InstructionCost::Slice) ? 
            m_remaining_time : m_settings.getCost(cost);

        while ((time > m_remaining_time) && (m_remaining_time >= 0))
        {
            swapcontext(&program_context, &runner_context);
        }

        if (m_remaining_time < 0)
        {
            throw ProcessKilledException();
        }

        m_remaining_time -= time;
    }

    void exit()
    {
        m_remaining_time = -1;
        swapcontext(&program_context, &runner_context);
    }
};
    
Process::Process(const GameSettings& s, Program& p, Node& n, PID pid) : 
    d(new Data(s, p, n, pid))
{
}

Process::~Process()
{
}

ProgramID Process::getProgramID() const 
{
    return d->m_program_id;
}

PID Process::getPID() const
{
    return d->m_pid;
}

bool Process::run(int time)
{
    if (d->m_remaining_time < 0)
    {
        return false;
    }
    d->m_remaining_time += time;
    swapcontext(&d->runner_context, &d->program_context);
    return d->m_remaining_time >= 0;
}


} // namespace CoreLink
