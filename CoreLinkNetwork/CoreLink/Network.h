#pragma once

#include <memory>
#include <QHash>

#include "CoreLink/Types.h"

namespace CoreLink { 

class Node;

/// Represents a network of CoreLink nodes.
class Network
{
    typedef std::shared_ptr<Node> NodePtr;
    typedef QHash<NodeID,NodePtr> NodePtrList;
    NodePtrList m_nodes;

public:
    Network();

    void tick(int time_quanta);

    NodeID addNode();
    bool connectNodes(NodeID first, NodeID second);

    NodeIDList getNodes() const;
    NodeIDList getNeighbors(NodeID id) const;
    const Node *getNode(NodeID id) const;

};

} // namespace CoreLink

