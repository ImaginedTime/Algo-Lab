// Java implementation of the approach
import java.util.*;
public class GFG {

	// par and rank will store the parent
	// and rank of particular node
	// in the Union Find Algorithm
	static int par[], rank[];

	// Find function of Union Find Algorithm
	static int find(int x)
	{
		if (par[x] != x)
			par[x] = find(par[x]);
		return par[x];
	}

	// Union function of Union Find Algorithm
	static void union(int u, int v)
	{
		int x = find(u);
		int y = find(v);
		if (x == y)
			return;
		if (rank[x] > rank[y])
			par[y] = x;
		else if (rank[x] < rank[y])
			par[x] = y;
		else {
			par[x] = y;
			rank[y]++;
		}
	}

	// Function to find the required spanning tree
	static void findSpanningTree(int deg[], int n,
								int m, ArrayList<Integer> g[])
	{
		par = new int[n + 1];
		rank = new int[n + 1];

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
			System.out.println(max + " " + v);
			union(max, v);
		}

		// Carrying out normal Kruskal Algorithm
		for (int u = 1; u <= n; u++) {
			for (int v : g[u]) {
				int x = find(u);
				int y = find(v);
				if (x == y)
					continue;
				union(x, y);
				System.out.println(u + " " + v);
			}
		}
	}

	// Driver code
	public static void main(String args[])
	{
		// Number of nodes
		int n = 5;

		// Number of edges
		int m = 5;

		// ArrayList to store the graph
		ArrayList<Integer> g[] = new ArrayList[n + 1];
		for (int i = 1; i <= n; i++)
			g[i] = new ArrayList<>();

		// Array to store the degree
		// of each node in the graph
		int deg[] = new int[n + 1];

		// Add edges and update degrees
		g[1].add(2);
		g[2].add(1);
		deg[1]++;
		deg[2]++;
		g[1].add(5);
		g[5].add(1);
		deg[1]++;
		deg[5]++;
		g[2].add(3);
		g[3].add(2);
		deg[2]++;
		deg[3]++;
		g[5].add(3);
		g[3].add(5);
		deg[3]++;
		deg[5]++;
		g[3].add(4);
		g[4].add(3);
		deg[3]++;
		deg[4]++;

		findSpanningTree(deg, n, m, g);
	}
}
