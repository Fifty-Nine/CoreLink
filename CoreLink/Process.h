#pragma once

#include <memory>

#include "CoreLink/Types.h"

namespace CoreLink
{

class Node;
class Program;

class Process
{
    struct Data;
    std::unique_ptr<Data> d; 

public:
    Process(Program& program, Node& node, PID pid);
    ~Process();

    ProgramID getProgramID() const;
    PID getPID() const;

    bool run(int time);
};

} // namespace CoreLink
