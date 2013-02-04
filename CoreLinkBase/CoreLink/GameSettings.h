#pragma once

#include "CoreLink/Types.h"

namespace CoreLink { 

class GameSettings
{
public:
    virtual ~GameSettings() { }

    virtual int getTimeSliceSize() const { return 50; }
    virtual int getCost(InstructionCost::Enum cost) const
    {
        using namespace InstructionCost;
        switch (cost)
        {
        default:
        case Slice:
        case Free:
            return 0;
        case Cheap:
            return 1;
        case Moderate:
            return 10;
        case Expensive:
            return 50;
        case Extreme:
            return 200;
        }
    }
};

} // namespace CoreLink

