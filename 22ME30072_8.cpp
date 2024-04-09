/************************************************
    UDAY OM SRIVASTAVA 22ME30072 Assignment 8
************************************************/

#include <iostream>

using namespace std;

int countPaths(int a[100][100], int n, int m, int i, int j, int k, int currCost, int dp[100][100][100])
{
    // if either of i or j exceeds the limit of the array, then the paths is 0
    if(i >= m || j >= n)
        return 0;
    
    // add the weight of the current cell to the currentCost
    currCost += a[i][j];

    // to count the number of paths from the current cell to the a[m-1][n-1]
    int pathsFromHere = 0;

    // if the same cell with the same cost has already been occured and is present in the dp, return the value from there, rather than calculating for it again
    if(dp[i][j][currCost] != -1)
        return dp[i][j][currCost];
    // if the limit for cost has been exceeded, and the last cell has still not been reached
    if(currCost >= k && !(i == n - 1 && j == m - 1))
        return dp[i][j][currCost] = 0;
    // if the last cell has been reached using the given cost
    if(currCost == k && (i == n - 1 && j == m - 1))
        return dp[i][j][currCost] = 1;

    // go down
    pathsFromHere += countPaths(a, n, m, i + 1, j, k, currCost, dp);
    // go right
    pathsFromHere += countPaths(a, n, m, i, j + 1, k, currCost, dp);
    // go right diagonal
    pathsFromHere += countPaths(a, n, m, i + 1, j + 1, k, currCost, dp);

    // return the pathsFromHere
    return dp[i][j][currCost] = pathsFromHere;
}

int main()
{
    int m, n;
    cout << "Input the value of M: ";
    cin >> m;
    cout << "Input the value of N: ";
    cin >> n;

    // Assuming the max size of the matrix to be 100 x 100
    int a[100][100];
    cout << "Input the weights of the cells in row major fashion: ";
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            cin >> a[i][j];
        }
    }

    int k;
    cout << "Input a cost: ";
    cin >> k;

    // making a dp array to store the values for each of 100 x 100 matrix 's costs
    // dp[M][N][costs]
    // Assuming the max cost to be 100
    int dp[100][100][100];

    // preset the value of the dp to be -1
    for(int i = 0; i < 100; i++)
        for(int j = 0; j < 100; j++)
            for(int c = 0; c < 100; c++)
                dp[i][j][c] = -1;

    int numberOfPaths = countPaths(a, n, m, 0, 0, k, 0, dp);


    if(numberOfPaths == 0)
        cout << "There is no path of weight " << k << endl;
    else if(numberOfPaths == 1)
        cout << "There is 1 path of weight " << k << endl;
    else
        cout << "There are " << numberOfPaths << " paths of weight " << k << endl;
}