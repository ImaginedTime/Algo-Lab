/************************************************
    Uday om Srivastava 22ME30072 Assignment 5
*************************************************/

// DONE FOR MIN HEAP


#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <climits>

using namespace std;

// to get the index of the left child of the current ith index element
int left(int i)
{
    return 2 * i - 1;
}

// to get the index of the right child of the current ith index element
int right(int i)
{
    return 2 * i;
}

// to get the index of the parent of the current ith index element
int parent(int i)
{
    return (i + 1) / 2;
}

// inserts an element into the heap
void insert(int *heap, int newElement)
{
    if(heap[0] == heap[1])
    {
        cout << "Heap is Full" << endl;
        return;
    }

    int i = heap[0] + 2;
    heap[0]++;

    heap[i] = newElement;

    // int level = floor(log2(i - 1)) + 1;
    int level = ceil(log2(i));
  
    while (i != 2 && (
        heap[parent(i)] > heap[i]
            // (level % 2 == 0 && heap[parent(i)] > heap[i]) || 
            // (level % 2 == 1 && heap[parent(i)] < heap[i])
        ))
    {
        int temp = heap[i];
        heap[i] = heap[parent(i)];
        heap[parent(i)] = temp;

        i = parent(i);
        level = floor(log2(i - 1)) + 1;
    }
}

// the heapify function for the min Heap
void heapify(int *heap, int i) 
{ 
    int l = left(i); 
    int r = right(i);
    // int level = floor(log2(i - 1)) + 1;

    int smallest = i;
    if (l < heap[0] + 2 && heap[l] < heap[i]) 
        smallest = l; 
    if (r < heap[0] + 2 && heap[r] < heap[smallest]) 
        smallest = r; 
    if (smallest != i) 
    { 
        // swap(&heap[i], &heap[smallest]); 
        int temp = heap[i];
        heap[i] = heap[smallest];
        heap[smallest] = temp;

        heapify(heap, smallest); 
    } 
} 

// extracts the minimum element of the heap in O(logn) time
int extractMin(int *heap)
{
    // return heap[0];

    if (heap[0] <= 0) 
        return INT_MAX; 
    if (heap[0] == 1) 
    { 
        heap[0]--; 
        return heap[2]; 
    }
  
    // Store the minimum value, and remove it from heap 
    int root = heap[2];
    heap[2] = heap[heap[0]+1]; 
    heap[0]--; 
    heapify(heap, 2); 
  
    return root;
}

// extracts the maximum element of the heap in O(n) time
int extractMax(int *heap)
{
    if (heap[0] <= 0) 
        return INT_MIN; 
    if (heap[0] == 1) 
    { 
        heap[0]--; 
        return heap[2];
    }

    // int l = heap[left(0)];
    // int r = heap[right(0)];

    // int max = l > r ? l : r;

    // heap[2] = heap[heap[0]+1]; 
    // heap[0]--; 
    // heapify(heap, 2); 

    int max = heap[2];
    int maxIndex = 2;
    for(int i = 3; i < heap[0] + 2; i++)
    {
        if(heap[i] > max)
        {
            max = heap[i];
            maxIndex = i;
        }
    }

    heap[maxIndex] = heap[heap[0] + 1];
    heap[0]--;
    heapify(heap, 2);

    return max;
}

// auxillary function to print the heap array
void printHeap(int *heap)
{
    cout << "Heap Array: ";
    for(int i = 0; i < heap[0] + 2; i++)
    {
        int level = floor(log2(i - 1)) + 1;
        cout << heap[i] << " ";
    }
    cout << endl << endl;
}

// to insert the given n elements into the heap
void createMinMaxHeap(int *heap)
{
    int n = heap[0];
    heap[0] = 0;
    cout << "Enter " << n << " numbers: ";
    for(int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        insert(heap, x);
    }

    cout << endl << endl;
    printHeap(heap);
}

int main()
{
    int n;
    cout << "Enter n: ";
    cin >> n;

    // the heap array
    int *heap = (int*)malloc(2 * n * sizeof(int));

    // stores the heap Size and capacity of the heap as the first and the second elements of the heap
    heap[0] = n;
    heap[1] = 2 * n;

    createMinMaxHeap(heap);

    // for the user choices
    while(true)
    {
        cout << "1. Insert" << endl;
        cout << "2. Extract Min" << endl;
        cout << "3. Extract Max" << endl;
        cout << "4. Exit" << endl;
        cout << "Your Option: ";
        int choice;
        cin >> choice;

        switch(choice){
            case 1:
            {
                int x;
                cout << "Enter the number to be inserted: ";
                cin >> x;
                insert(heap, x);
                printHeap(heap);
                break;
            }
            case 2:
            {
                int min = extractMin(heap);
                if(min == INT_MAX)
                    cout << "Heap is empty";
                else
                    cout << "Minimum is " << min << endl;
                printHeap(heap);
                break;
            }
            case 3:
            {
                int max = extractMax(heap);
                if(max == INT_MIN)
                    cout << "Heap is empty";
                else
                    cout << "Maximum is " << max << endl;
                printHeap(heap);
                break;
            }
            case 4:
                return 0;
            default:
                cout << "Invalid Choice!" << endl;
        }
    }

    return 0;
}