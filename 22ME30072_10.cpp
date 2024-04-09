#include <iostream>

using namespace std;

class Graph {
    
}

typedef struct Edge {
    int source, destination, weight;
} Edge;

int main() 
{
    int n, m;
    cout << "Enter the number of vertices: ";
    cin >> n;

    cout << "Enter the number of edges: ";
    cin >> m;

    int K;
    cout << "Enter the range for the weights of the edges (1-K): ";
    cin >> K;

    Edge edges[m];

    for(int i = 0; i < m; i++)
    {
        int src, dest, w;
        cout << "Write " << i << "th edge (vertices and weight): ";
        cin >> src >> dest >> w;

        edges[i] = { src, dest, w };
    }

    
    return 0;
}