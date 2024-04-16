/*************************************************
	Uday om srivastava 22ME30072 Assignment 10
**************************************************/

#include <iostream>
#include <limits.h>
using namespace std;

// A utility function to find the vertex with
// minimum key value, from the set of vertices
// not yet included in MST
int minKey(int key[], bool mstSet[], int n)
{
	// Initialize min value
	int min = INT_MAX, min_index;

	for (int v = 0; v < n; v++)
		if (mstSet[v] == false && key[v] < min)
			min = key[v], min_index = v;

	return min_index;
}

// A utility function to print the
// constructed MST stored in parent[]
void printMST(int parent[], int graph[100][100], int n)
{
	// cout << "Edge \tWeight\n";
	// for (int i = 1; i < V; i++)
	// 	cout << parent[i] + 1 << " - " << i + 1 << " \t"
	// 		<< graph[i][parent[i]] << " \n";

	cout << endl;
	for(int i = 1; i < n; i++)
		cout << "(" << parent[i] + 1 << "," << i + 1 << ") ";

	cout << endl;
}

// Function to construct and print MST for
// a graph represented using adjacency
// matrix representation
void primMST(int graph[100][100], int n)
{
	// Array to store constructed MST
	int parent[100];

	// Key values used to pick minimum weight edge in cut
	int key[100];

	// To represent set of vertices included in MST
	bool mstSet[100];

	// Initialize all keys as INFINITE
	for (int i = 0; i < n; i++)
		key[i] = INT_MAX, mstSet[i] = false;

	// Always include first 1st vertex in MST.
	// Make key 0 so that this vertex is picked as first
	// vertex.
	key[0] = 0;

	// First node is always root of MST
	parent[0] = -1;

	// The MST will have V vertices
	for (int count = 0; count < n - 1; count++) {
		
		// Pick the minimum key vertex from the
		// set of vertices not yet included in MST
		int u = minKey(key, mstSet, n);

		// Add the picked vertex to the MST Set
		mstSet[u] = true;

		// Update key value and parent index of
		// the adjacent vertices of the picked vertex.
		// Consider only those vertices which are not
		// yet included in MST
		for (int v = 0; v < n; v++)

			// graph[u][v] is non zero only for adjacent
			// vertices of m mstSet[v] is false for vertices
			// not yet included in MST Update the key only
			// if graph[u][v] is smaller than key[v]
			if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v])
				parent[v] = u, key[v] = graph[u][v];
	}

	// Print the constructed MST
	printMST(parent, graph, n);
}

// Driver's code
int main()
{
	int graph[100][100];

	for(int i = 0; i < 100; i++)
	{
		for(int j = 0; j < 100; j++)
		{
			graph[i][j] = 0;
		}
	}

	int n, m;
    cout << "Enter the number of vertices: ";
    cin >> n;

    cout << "Enter the number of edges: ";
    cin >> m;

    int K;
    cout << "Enter the range for the weights of the edges (1 to K): ";
    cin >> K;

	for(int i = 0; i < m; i++)
    {
        int src, dest, w;
        cout << "Write " << i << "th edge (vertices and weight): ";
        cin >> src >> dest >> w;

        graph[src - 1][dest - 1] = w;
		graph[dest - 1][src - 1] = w;
    }

	// Print the solution
	primMST(graph, n);

	return 0;
}
