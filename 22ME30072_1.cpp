// 22ME30072
// Uday om srivastava
// Assignment Number 3

#include <iostream>
#include <stdlib.h>

using namespace std;

int log10(int n) 
{
    int cnt = 0;
    while(n > 0)
    {
        cnt++;
        n /= 10;
    }
    return cnt - 1;
}

int init_t1(int *t1, int n) 
{
    if(n == 0)
        return t1[n] = 2;
    if(n == 1)
        return t1[n] = 1;

    return t1[n] = init_t1(t1, n - 1) - 2 * init_t1(t1, n - 2);
}

int init_t2(int *t2, int n) 
{
    if(n == 0)
        return t2[n] = 2;
    if(n == 1)
        return t2[n] = 1;

    return t2[n] = init_t2(t2, n - 1) - init_t2(t2, n - 2);
}

void merge(int *a, int n, int l, int mid, int e)
{
    int l1 = mid - l + 1;
    int l2 = e - mid;

    // creating temporary arrays to store the divided subarrays
    // then we'll merge then in O(n)
    int *p1 = (int *) malloc(sizeof(int) * l1);
    int *p2 = (int *) malloc(sizeof(int) * l2);

    for(int i = l; i <= mid; i++)
        p1[i - l] = a[i];
    for(int i = mid + 1; i <= e; i++)
        p2[i - mid - 1] = a[i];


    int x1 = 0, x2 = 0;
    int index = l;

    while(x1 < l1 && x2 < l2) {
        if(p1[x1] < p2[x2])
            a[index++] = p1[x1++];
        else
            a[index++] = p2[x2++];
    }
    while(x1 < l1) {
        a[index++] = p1[x1++];
    }

    while(x2 < l2) {
        a[index++] = p2[x2++];
    }
}

void bubbleSort(int *a, int l, int e)
{
    for(int i = l; i < e; i++)
    {
        for(int j = i + 1; j <= e; j++)
        {
            if(a[i] > a[j])
            {
                int temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
}

// Run Time for f(n) - combined Sort is O(n * f(n) + c * n * log(n / f(n)))
void partition(int *a, int n, int l, int e, int fn)
{
    int sz = e - l + 1;

    // using bubble sort if the size of the subarray is less than the value fn
    if(sz <= fn)
    {
        bubbleSort(a, l, e);
        return;
    }

    if(l >= e)
        return;


    int mid = l + (e - l) / 2;

    partition(a, n, l, mid, fn);
    partition(a, n, mid + 1, e, fn);

    merge(a, n, l, mid, e);
}


// Sorting alg for T2 - Run Time O(n)
void sortForT2(int* t2, int n)
{
    int minus1s = 0, minus2s = 0, ones = 0, twos = 0;

    for(int i = 0; i < n; i++)
    {
        if(t2[i] == -2)
            minus2s++;
        else if(t2[i] == -1)
            minus1s++;
        else if(t2[i] == 1)
            ones++;
        else
            twos++;
    }

    int index = 0;
    for(int i = 0; i < minus2s; i++)
        t2[index++] = -2;
    for(int i = 0; i < minus1s; i++)
        t2[index++] = -1;
    for(int i = 0; i < ones; i++)
        t2[index++] = 1;
    for(int i = 0; i < twos; i++)
        t2[index++] = 2;
}


int main()
{
    int n;
    cin >> n;

    int *t1 = (int*) malloc(sizeof(int) * n);
    int *t2 = (int*) malloc(sizeof(int) * n);

    init_t1(t1, n - 1);
    init_t2(t2, n - 1);


    // I select the function f(n) as log(n)
    // And by basic maths, we know that log(n) in base 10 is just the (number of digits in the number n) - 1
    // So we can save time there by calculating the number of digits in the number n,
    // rather than using the log function from the maths library
    // int fn = log(n);
    int fn = log10(n);

    // The best time complexity we get is when we choose f(n) to be 1
    // But I have chosen f(n) = log(n), to explore
    // by which we get the time complexity as O(nlogn + cnlog(n/logn))


    cout << endl;
    cout << "Unsorted Array T1:   ";
    for(int i = 0; i < n; i++)
        cout << t1[i] << " ";
    cout << endl;

    partition(t1, n, 0, n - 1, fn);

    cout << "Sorted Array T1:     ";
    for(int i = 0; i < n; i++)
        cout << t1[i] << " ";
    cout << endl << endl;


    // For T2, it can be seen that there emerges a pattern, which is, a repetition of a 6-cycle
    // the pattern is repetition of 2 1 -1 -2 -1 1
    // hence to sort this, we can just count the number of -1's -2's 1's and 2's
    // and just place them normally giving us a time complexity of O(n)
    cout << "Unsorted Array T2:   ";
    for(int i = 0; i < n; i++)
        cout << t2[i] << " ";
    cout << endl;

    // for fastest we choose fn to be 0
    sortForT2(t2, n);

    cout << "Sorted Array T2:     ";
    for(int i = 0; i < n; i++)
        cout << t2[i] << " ";
    cout << endl;
    
}