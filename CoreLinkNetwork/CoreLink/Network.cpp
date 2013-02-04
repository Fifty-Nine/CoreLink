#include "CoreLink/Network.h"

#include "CoreLink/Node.h"

namespace CoreLink { 

Network::Network(const GameSettings& settings) : 
    m_settings(settings)
{
}

Network::~Network()
{
}

void Network::tick()
{
    /// \todo Make parallel.
    for (NodePtr& node_p: m_nodes)
    {
        node_p->tick();
    }
}

NodeID Network::addNode()
{
    NodePtr node_p(new Node(m_settings));

    m_nodes[node_p->getID()] = node_p;

    return node_p->getID();
}

bool Network::connectNodes(NodeID n1_id, NodeID n2_id)
{
    NodePtr n1 = m_nodes.value(n1_id);
    NodePtr n2 = m_nodes.value(n2_id);

    if (!n1 || !n2 || n1->hasNeighbor(n2_id) || n2->hasNeighbor(n1_id))
    {
        return false;
    }

    n1->addNeighbor(n2_id);
    n2->addNeighbor(n1_id);

    return true;
}

NodeIDList Network::getNodes() const
{
    return m_nodes.keys();
}

const Node *Network::getNode(NodeID id) const
{
    return m_nodes.value(id).get();
}

} // namespace CoreLink

