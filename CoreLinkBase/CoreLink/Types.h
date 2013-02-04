#pragma once

#include <functional>
#include <QList>
#include <QUuid>

namespace CoreLink
{

/// A value that uniquely identifies a process on a node.
typedef int PID;

/// A list of PIDs.
typedef QList<PID> PIDList;


/// A value that uniquely identifies a program on any node.
typedef QUuid ProgramID;

/// A list of program IDs.
typedef QList<ProgramID> ProgramIDList;


/// A value that uniquely identifies a node in a network.
typedef QUuid NodeID;

/// A list of node IDs.
typedef QList<QUuid> NodeIDList;

namespace InstructionCost
{
enum Enum 
{
    Slice, 
    Free, 
    Cheap, 
    Moderate,
    Expensive,
    Extreme
};
}

class Node;
/// The type of a message passed to a node.
typedef std::function<void(Node&)> Message;

} // namespace CoreLink
