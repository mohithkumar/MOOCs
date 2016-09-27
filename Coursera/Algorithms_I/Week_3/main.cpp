#include "Graph.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int main()
{
    Graph g;
    ifstream inFile("kargerMinCut.txt");
    if (inFile.is_open())
    {
        string line;
        while (getline(inFile, line))
        {
            istringstream iss(line);
            uint32_t baseVertex(0);
            iss >> baseVertex;
            // cout << "NEW (" << baseVertex << ") : ";
            uint32_t neighbour(0);
            while (iss >> neighbour)
            {
                // cout << neighbour << " ";
                g.addEdge(baseVertex, neighbour);
            }
            // cout << endl;
        }
        inFile.close();
    }

    // cout << g;
    cout << "Number of Vertices : " << g.getNumberOfVertices() << endl;
    cout << "Number of Edges : " << g.getNumberOfEdges() << endl;
    cout << "Karger Minimum Cut : " << g.getKargerMinCut() << endl;

    return 0;
}

