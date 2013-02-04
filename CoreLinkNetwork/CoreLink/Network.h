#pragma once

#include <memory>
#include <QHash>

#include "CoreLink/Types.h"

namespace CoreLink { 

class GameSettings;
class Node;

/// Represents a network of CoreLink nodes.
class Network
{
    typedef std::shared_ptr<Node> NodePtr;
    typedef QHash<NodeID,NodePtr> NodePtrList;
    const GameSettings& m_settings;
    NodePtrList m_nodes;

public:
    Network(const GameSettings& settings);
    ~Network();

    void tick();

    NodeID addNode();
    bool connectNodes(NodeID first, NodeID second);
    void postMessage(NodeID node, Message msg);

    NodeIDList getNodes() const;
    const Node *getNode(NodeID id) const;
};

} // namespace CoreLink

