#include<bits/stdc++.h>
using namespace std;

// par and sz will store the parent
// and rank of particular node
// in the Union Find Algorithm
vector<int> par,sz;

// Find function of Union Find Algorithm
int find(int x)
{
	if(par[x]!=x)
		par[x]=find(par[x]);
	return par[x];
}

// Union function of Union Find Algorithm
void Union(int u, int v)
{
	int x = find(u);
	int y = find(v);
	if (x == y)
		return;
	if (sz[x] > sz[y])
		par[y] = x;
	else if (sz[x] < sz[y])
		par[x] = y;
	else {
		par[x] = y;
		sz[y]++;
	}
}

// Function to find the required spanning tree
void findSpanningTree(vector<int> deg,int n,int m,vector<vector<int>> g)
{
	par.resize(n+1);
	sz.resize(n+1);
	// Initialising parent of a node
	// by itself
	for (int i = 1; i <= n; i++)
		par[i] = i;

	// Variable to store the node
	// with maximum degree
	int max = 1;

	// Finding the node with maximum degree
	for (int i = 2; i <= n; i++)
		if (deg[i] > deg[max])
			max = i;

	// Union of all edges incident
	// on vertex with maximum degree
	for (int v : g[max]) {
		cout << max << " " << v << '\n';
		Union(max, v);
	}

	// Carrying out normal Kruskal Algorithm
	for (int u = 1; u <= n; u++) {
		for (int v : g[u]) {
			int x = find(u);
			int y = find(v);
			if (x == y)
				continue;
			Union(x, y);
			cout << u << " " << v << '\n';
		}
	} 
}

int main()
{
	// Number of nodes
	int n = 5;

	// Number of edges
	int m = 5;

	// store the graph
	vector<vector<int>> g(n+1);

	// store the degree
	// of each node in the graph
	vector<int> deg(n+1);

	// add edges and update degrees
	g[1].push_back(2);
	g[2].push_back(1);
	deg[1]++;
	deg[2]++;
	g[1].push_back(5);
	g[5].push_back(1);
	deg[1]++;
	deg[5]++;
	g[2].push_back(3);
	g[3].push_back(2);
	deg[2]++;
	deg[3]++;
	g[5].push_back(3);
	g[3].push_back(5);
	deg[3]++;
	deg[5]++;
	g[3].push_back(4);
	g[4].push_back(3);
	deg[3]++;
	deg[4]++;

	findSpanningTree(deg, n, m, g);
	return 0;
}
