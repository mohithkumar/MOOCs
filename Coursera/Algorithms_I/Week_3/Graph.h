#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <set>
#include <cstdint>
#include <cstddef>
#include <ostream>

typedef std::set<uint32_t> Neighbours;

class Vertex
{
  public:
    Vertex();
    Vertex(const Neighbours& neighbours);
    ~Vertex();

    bool addNeighbour(uint32_t neighbour);
    bool addNeighbours(const Neighbours& neighbours);

    bool removeNeighbour(uint32_t neighbour);
    bool removeNeighbours(const Neighbours& neighbours);

    size_t getNeighboursCount() const;
    const Neighbours& getNeighbours() const;

  private:
    // Vertex(const& Vertex) = delete;
    // Vertex& operator=(const& Vertex) = delete;

    Neighbours m_neighbours;
};


typedef std::vector<Vertex> Vertices;
class Graph
{
  public:
    Graph();
    ~Graph();

    bool addEdge(uint32_t v1, uint32_t v2);
    bool removeEdge(uint32_t v1, uint32_t v2);

    size_t getNumberOfVertices() const;
    size_t getNumberOfEdges() const;

    friend std::ostream& operator<<(std::ostream& os, const Graph& g);

  private:
    Graph(const Graph&) = delete;
    Graph& operator=(const Graph&) = delete;

    bool addVertex(uint32_t v);
    bool addNeighbours(uint32_t v, Neighbours& neighbours);

    Vertices m_vertices;
    size_t m_numOfEdges;
};

#endif // GRAPH_H

