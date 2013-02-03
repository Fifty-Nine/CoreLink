#pragma once

#include <QList>
#include <QUuid>

namespace CoreLink
{

typedef int PID;
typedef QList<PID> PIDList;

typedef QUuid ProgramID;
typedef QList<ProgramID> ProgramIDList;

typedef QUuid NodeID;
typedef QList<QUuid> NodeIDList;


} // namespace CoreLink
