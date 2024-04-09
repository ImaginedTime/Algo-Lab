/******************************************
    Uday om srivastava 22ME30072 Test 2
*******************************************/

#include <iostream>
#include <limits.h>
#include <string>

using namespace std;

void printDijkstra(int sourceVertex, int cost[1000], string paths[1000], int n){
    for (int i = 0; i < n; i++) {
        if(sourceVertex >= i)
            continue;
        cout << "[" << sourceVertex + 1 << ", " << i + 1 << "] = ";
        cout << paths[i] << " with cost ";
        cout << (cost[i] < 0 ? 0 : cost[i]) << endl;
    }
}

int getMinimumVertex(bool mst[1000], int cost[1000], int n) {
    int minKey = INT_MAX;
    int vertex = -1;
    for (int i = 0; i < n ; i++) {
        if(mst[i] == false && minKey > cost[i]){
            minKey = cost[i];
            vertex = i;
        }
    }
    return vertex;
}

void dijkstras(int sourceVertex, int n, int adj[1000][1000], int k){
    bool visited[n];
    int cost[n];
    int INFINITY = INT_MAX;

    string paths[1000];
    for(int i = 0; i < 1000; i++)
        paths[i] = to_string(sourceVertex + 1);

    //Initialize all the cost to infinity
    for (int i = 0; i < n ; i++) {
        cost[i] = INFINITY;
        visited[i] = false;
    }

    //start from the vertex 0
    cost[sourceVertex] = 0;

    for (int i = 0; i < n; i++) {
        int u = getMinimumVertex(visited, cost, n);

        visited[u] = true;

        for (int v = 0; v < n; v++) {
            int mx1 = 0, mx2 = 0, mx3 = 0, mx4 = 0, mx5 = 0;
            for(int j = 0; j < paths[v].length(); j++)
            {   
                if(j == paths[v].length() - 1)
                    break;
                int x = adj[paths[v][j] - '0' - 1][paths[v][j + 1] - '0' - 1];
                if(x > mx1)
                {
                    mx5 = mx4;
                    mx4 = mx3;
                    mx3 = mx2;
                    mx2 = mx1;
                    mx1 = x;
                }
                else if(x > mx2)
                {
                    mx5= mx4;
                    mx4 = mx3;
                    mx3 = mx2;
                    mx2 = x;
                }
                else if(x > mx3) {
                    mx5 = mx4;
                    mx4 = mx3;
                    mx3 = x;
                }
                else if(x > mx4) {
                    mx5 = mx4;
                    mx4 = x;
                }
                else if( x > mx5) {
                    mx5 = x;
                }
            }

            int mx = 0;

            if(k == 5)
                mx = mx1 + mx2 + mx3 + mx4 + mx5;
            else if(k == 4)
                mx = mx1 + mx2 + mx3 + mx4;
            else if(k == 3)
                mx = mx1 + mx2 + mx3;
            else if(k == 2)
                mx = mx1 + mx2;
            else if(k == 1)
                mx = mx1;

            if(visited[v] == false && adj[u][v] + cost[u] - mx < cost[v]) {
                cost[v] = adj[u][v] + cost[u];
                paths[v] = paths[u] + to_string(v + 1);
            }
        }
    }

    for(int v = 0; v < n; v++)
    {
        int mx1 = 0, mx2 = 0, mx3 = 0, mx4 = 0, mx5 = 0;
        for(int j = 0; j < paths[v].length(); j++)
        {   
            if(j == paths[v].length() - 1)
                break;
            int x = adj[paths[v][j] - '0' - 1][paths[v][j + 1] - '0' - 1];
            if(x > mx1)
            {
                mx5 = mx4;
                mx4 = mx3;
                mx3 = mx2;
                mx2 = mx1;
                mx1 = x;
            }
            else if(x > mx2)
            {
                mx5= mx4;
                mx4 = mx3;
                mx3 = mx2;
                mx2 = x;
            }
            else if(x > mx3) {
                mx5 = mx4;
                mx4 = mx3;
                mx3 = x;
            }
            else if(x > mx4) {
                mx5 = mx4;
                mx4 = x;
            }
            else if( x > mx5) {
                mx5 = x;
            }
        }

        int mx = 0;
        if(k == 5)
            mx = mx1 + mx2 + mx3 + mx4 + mx5;
        else if(k == 4)
            mx = mx1 + mx2 + mx3 + mx4;
        else if(k == 3)
            mx = mx1 + mx2 + mx3;
        else if(k == 2)
            mx = mx1 + mx2;
        else if(k == 1)
            mx = mx1;

        cost[v] -= mx;
    }

    // for(int i = 0; i < n; i++)
    //     paths[i] = to_string(sourceVertex + 1) + paths[i];

    printDijkstra(sourceVertex, cost, paths, n);
}

int main() {

    int n;
    cout << "Enter n: ";
    cin >> n;

    int adj[1000][1000];

    for(int i = 0; i < n; i++)
    {
        adj[i][i] = 0;
    }

    for(int i = 0; i < n; i++)
    {
        for(int j = i + 1; j < n; j++)
        {
            cout << "Between " << i + 1 << " and " << j + 1 << " : ";
            int x;
            cin >> x;
            adj[i][j] = x;
            adj[j][i] = x;
        }
    }

    cout << endl;
    cout << "0 Token-shortest routes: " << endl;
    for(int i = 0; i < n; i++)
        dijkstras(i, n, adj, 0);
    
    cout << endl;
    cout << "1 Token-shortest routes: " << endl;
    for(int i = 0; i < n; i++)
        dijkstras(i, n, adj, 1);

    int k;
    cout << endl << "Enter the value for k: ";
    cin >> k;

    if(k > 1)
    {
        cout << endl;
        cout << "2 Token-shortest routes: " << endl;
        for(int i = 0; i < n; i++)
            dijkstras(i, n, adj, 2);
    }

    if(k > 2)
    {
        cout << endl;
        cout << "3 Token-shortest routes: " << endl;
        for(int i = 0; i < n; i++)
            dijkstras(i, n, adj, 3);
    }

    if(k > 3)
    {
        cout << endl;
        cout << "4 Token-shortest routes: " << endl;
        for(int i = 0; i < n; i++)
            dijkstras(i, n, adj, 4);
    }

    if(k > 4)
    {
        cout << endl;
        cout << "5 Token-shortest routes: " << endl;
        for(int i = 0; i < n; i++)
            dijkstras(i, n, adj, 5);
    }


    return 0;
}