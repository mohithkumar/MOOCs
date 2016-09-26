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


bool Vertex::isNeighbourPresent(uint32_t neighbour) const
{
    bool retVal(true);

    if (m_neighbours.find(neighbour) != m_neighbours.end())
    {
        retVal = false;
    }
    return retVal;
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
    m_vertices[v1].addNeighbour(v2);
    try
    {
        const Vertex& vertex2 = m_vertices.at(v2);
        if (vertex2.isNeighbourPresent(v1) == false)
        {
            ++m_numOfEdges;
        }
    }
    catch(...)
    {
    }

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


size_t Graph::getNumberOfVertices() const
{
    return m_vertices.size() - 1;
}


size_t Graph::getNumberOfEdges() const
{
    return m_numOfEdges;
}


size_t Graph::getKargerMinCut()
{
/*
While there are more than 2 vertices:
•  pick a remaining edge (u,v) uniformly at random
•  merge (or “contract” ) u and v into a single vertex
•  remove self-loops
return cut represented by final 2 vertices.

    while (m_vertices.size() > (2 + 1))
    {
        
    }
*/

    return 0;
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


Edge Graph::getRandomEdge(uint32_t value) const
{
    uint32_t counter(0);
    bool edgeFound(false);
    Edge retVal;

    size_t verticesLen(m_vertices.size());
    for(size_t i(1); ((i < verticesLen) && (edgeFound == false)); ++i)
    {
        const Neighbours& neighbours = m_vertices[i].getNeighbours();
        Neighbours::const_iterator neighboursCit = neighbours.cbegin();
        Neighbours::const_iterator neighboursCitEnd = neighbours.cend();
        for(; neighboursCit != neighboursCitEnd; ++neighboursCit)
        {
            if (counter == value)
            {
                retVal.first = i;
                retVal.second = *neighboursCit;
                edgeFound = true;
                break; 
            }
            ++counter;
        }
    }

    return retVal;
}

