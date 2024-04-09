#include<iostream>
#include<stdlib.h>

using namespace std;

// Time complexity : O(n * n!) expect for printing inversions tables
// Space Complexity : O(2 * n) => O(n) except for printing inversions tables

// Time complexity : O(n^2 * n!) for printing inversions tables
// Space Complexity : O(3 * n) => O(n) for printing inversions tables


void init(int* a, int* d, int n, int* invCount)
{
    for(int i = 0; i < n; i++)
        a[i] = i + 1;
    
    d[0] = 0;
    for(int i = 1; i < n; i++)
        d[i] = -1;

    *invCount = 0;
}

int index(int *a, int n)
{
    int ans = 0;

    for(int i = 1; i < n; i++)
        if(a[i - 1] > a[i])
            ans += i;
        
    return ans;
}

int genNext(int *a, int *d, int n, int* invCount)
{
    for(int i = 0; i < n; i++)
        cout << a[i] << " ";
    
    cout << "           ";
    // cout << endl << endl;

    // cout << "d : " << endl;
    // for(int i = 0; i < n; i++)
    //     cout << d[i] << " ";
    // cout << endl;


    int pos = 0;
    for(int i = 0; i < n; i++)
    {
        if(d[pos] == 0 || d[i] != 0 && d[i] >= d[pos])
        {
            pos = i;
        }
    }

    // cout << "pos: " << pos + 1 << endl << endl; 

    if(d[pos] == -1)
    {
        int temp = a[pos];
        a[pos] = a[pos - 1];
        a[pos - 1] = temp;

        temp = d[pos];
        d[pos] = d[pos - 1];
        d[pos - 1] = temp;
        
        pos = pos - 1;

        if(pos == 0)
            d[pos] = 0;
        // else{
            // for(int i = 1; pos - i >= 0; i++)
            // {
                int num = *invCount;
                if(a[pos] > a[pos + 1])
                    num ++;
                else
                    num --;
                *invCount = num;
            // }
        // }
    }
    else {
        int temp = a[pos];
        a[pos] = a[pos + 1];
        a[pos + 1] = temp;

        temp = d[pos];
        d[pos] = d[pos + 1];
        d[pos + 1] = temp;

        pos = pos + 1;

        if(pos == n - 1)
            d[pos] = 0;
        // else{
            // for(int i = 1; pos - i >= 0; i++)
            // {
                int num = *invCount;
                if(a[pos - 1] > a[pos])
                    num ++;
                else
                    num --;
                *invCount = num;
            // }
        // }
    }

    for(int i = 0; i < n; i++)
    {
        if(i == pos)
            continue;

        if(a[i] < a[pos] && d[i] == 0)
        {
            if(pos > i)
                d[i] = 1;
            else
                d[i] = -1;
        }
    }

    int ans = *invCount;
    return ans;
}

int factorial(int n)
{
    int ans = 1;
    for(int i = 2; i <= n; i++)
        ans *= i;
    return ans;
}


int main()
{
    int n;
    cin >> n;

    int *a = (int*)(malloc(sizeof(int) * n));
    int *d = (int*)(malloc(sizeof(int) * n));
    int invCount;

    init(a, d, n, &invCount);

    cout << "Permutations    Inversions    Index    Inversion Table" << endl;

    int *b = (int*)(malloc(sizeof(int) * n));
    for(int i = 0; i < n; i++)
        b[i] = 0;


    for(int i = 0; i < factorial(n); i++)
    {
        int iv = invCount;
        int id = index(a, n);


        for(int i = 0; i < n; i++)
        {
            for(int j = i + 1; j < n; j++)
            {
                if(a[i] > a[j])
                    b[a[j] - 1]++;
            }
        }

        genNext(a, d, n, &invCount);

        cout << iv << "           " << id << "           ";

        for(int i = 0; i < n; i++)
            cout << b[i] << " ";
        cout << endl;
    }
}