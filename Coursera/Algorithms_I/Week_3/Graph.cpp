#include "Graph.h"
#include <algorithm>

using namespace std;

Vertex::Vertex()
    : m_neighbours()
{
}


Vertex::Vertex(const Neighbours& neighbours)
    : m_neighbours(neighbours)
{
}


Vertex::~Vertex()
{
}


bool Vertex::addNeighbour(uint32_t neighbour)
{
    return (m_neighbours.insert(neighbour)).second;
}


bool Vertex::addNeighbours(const Neighbours& neighbours)
{
    m_neighbours.insert(neighbours.begin(), neighbours.end());
    return true;
}


bool Vertex::removeNeighbour(uint32_t neighbour)
{
    return (m_neighbours.erase(neighbour) ? true : false);
}


bool Vertex::removeNeighbours(const Neighbours& neighbours)
{
    m_neighbours.erase(neighbours.begin(), neighbours.end());
    return true;
}


size_t Vertex::getNeighboursCount() const
{
    return m_neighbours.size();
}


const Neighbours& Vertex::getNeighbours() const
{
    return m_neighbours;
}


// -----------------------------------------------------------------------------


Graph::Graph()
    : m_vertices()
    , m_numOfEdges(0)
{
    // Initializing the first element to NO neighbours
    addVertex(0);
}


Graph::~Graph()
{
}


bool Graph::addEdge(uint32_t v1, uint32_t v2)
{
    addVertex(v1);
    addVertex(v2);

    m_vertices[v1].addNeighbour(v2);
    m_vertices[v2].addNeighbour(v1);

    ++m_numOfEdges;
    return true;
}


bool Graph::removeEdge(uint32_t v1, uint32_t v2)
{
    if (m_vertices[v1].getNeighboursCount() != 0)
    {
        m_vertices[v1].removeNeighbour(v2);
        --m_numOfEdges;
    }
    if (m_vertices[v2].getNeighboursCount() != 0)
    {
        m_vertices[v2].removeNeighbour(v1);
        --m_numOfEdges;
    }

    return true;
}


bool Graph::addVertex(uint32_t v)
{
    bool retVal(true);
    while (m_vertices.size() < (v+1))
    {
        Vertex vertex;
        m_vertices.push_back(vertex);
    }
    return retVal;
}


// Private
bool Graph::addNeighbours(uint32_t v, Neighbours& neighbours)
{
    addVertex(v);
    m_vertices[v].addNeighbours(neighbours);
    return true;
}


size_t Graph::getNumberOfVertices() const
{
    return m_vertices.size() - 1;
}


size_t Graph::getNumberOfEdges() const
{
    return (m_numOfEdges/2);
}


ostream& operator<<(ostream& os, const Graph& g)
{
    size_t verticesLen(g.m_vertices.size());
    for(size_t i(1); i < verticesLen; ++i)
    {
        os << i << " : ";
        const Neighbours& neighbours = g.m_vertices[i].getNeighbours();
        Neighbours::const_iterator neighboursCit = neighbours.cbegin();
        Neighbours::const_iterator neighboursCitEnd = neighbours.cend();
        for(; neighboursCit != neighboursCitEnd; ++neighboursCit)
        {
            os << *neighboursCit << " ";
        }
        os << endl;
    }

    return os;
}

