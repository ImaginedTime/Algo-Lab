/***********************************************
    Uday om srivastava 22ME30072 Lab Test 1
************************************************/

#include <iostream>

using namespace std;

// definition of the node struct
typedef struct node {
    int val;
    struct node* leftc;
    struct node* rightc;
    struct node* parent;
} node, *nodeprt;

// to insert a node in the BST
nodeprt insertNode(nodeprt root, int data)
{
    // if root is null, create a node and insert the value
    if(root == NULL)
    {
        root = new node();
        root -> val = data;
        root -> parent = NULL;
        return root;
    }

    if(data <= root -> val)
    {
        // if the value is smaller that the current value, insert in the left subtree
        nodeprt lchild = insertNode(root->leftc, data);
        root -> leftc = lchild;
        lchild -> parent = root;
    }
    else {
        // if the value is larger that the current value, insert in the right subtree
        nodeprt rchild = insertNode(root -> rightc, data);
        root -> rightc = rchild;
        rchild -> parent = root;
    }

    return root;
}

// to create the BST
nodeprt toBST(int *a, int n)
{
    if(n == 0)
        return NULL;
    
    // initialize the root to be null
    nodeprt root = NULL;
    // insert all the values, one by one
    for(int i = 0; i < n; i++)
        root = insertNode(root, a[i]);

    return root;
}

// inorder traversal of the tree and stores it in the given array
// left root right
void inorder(nodeprt root, int* a, int *i)
{
    if(root == NULL)
        return;
    inorder(root -> leftc, a, i);
    a[(*i)++] = root -> val;
    inorder(root -> rightc, a, i);
}

// postorder traversal of the tree and stores it in the given array
// left right root
void postorder(nodeprt root, int* a, int *i)
{
    if(root == NULL)
        return;
    postorder(root -> leftc, a, i);
    postorder(root -> rightc, a, i);
    a[(*i)++] = root -> val;
}

// to find the inorder of the given array a
void toInorder(int *a, int *b, int n)
{
    int i = 0;
    // create the BST and populate the other array with the inorder traversal values
    nodeprt root = toBST(a, n);
    inorder(root, b, &i);

    cout << "The inorder traversal for this BST: ";
    for(int i = 0; i < n; i++)
        cout << b[i] << " ";
    cout << endl;
}

// to find the postorder of the given array a
void toPostorder(int *a, int *b, int n)
{
    int i = 0;
    // create the BST and populate the other array with the postorder traversal values
    nodeprt root = toBST(a, n);
    postorder(root, b, &i);

    cout << "The postorder traversal for this BST: ";
    for(int i = 0; i < n; i++)
        cout << b[i] << " ";
    cout << endl;
}

// finds the sum of all the elements in the BST that lie in the given a to be range
double Sum(nodeprt root, int a, int b)
{
    if(root == NULL)
        return 0.0;
    
    double val = 0.0;
    if(root -> val >= a && root -> val <= b)
        val += root -> val;
    
    // sum from left + sum from right + current val
    return val + Sum(root -> leftc, a, b) + Sum(root -> rightc, a, b);
}

// finds the number of elements that lie in the given a to be range
int countInRange(nodeprt root, int a, int b)
{
    if(root == NULL)
        return 0;

    int ans = 0;
    if(root -> val >= a && root -> val <= b)
        ans++;
    
    // count from left + count from right + current count
    return ans + countInRange(root -> leftc, a, b) + countInRange(root -> rightc, a, b);
}

// finds the average of the elements in the BST that lie the a to be range
double Avg(nodeprt root, int a, int b)
{
    return Sum(root, a, b) / countInRange(root, a, b);
}

// finds the kth minimum node between the range a to b, and returns it
nodeprt kthMin(nodeprt root, int k, int* i, int a, int b)
{
    if(root == NULL)
        return NULL;
    
    // try to find the node in the left subtree
    nodeprt foundInLeft = kthMin(root -> leftc, k, i, a, b);

    // if the node is found the left subtree, return it
    if(foundInLeft != NULL)
        return foundInLeft;
    
    // if the current node is the kth Min node in the range a to b, return it
    if(root -> val >= a && root -> val <= b && (*i)++ == k)
    {
        return root;
    }

    // or else find it in the right subtree
    return kthMin(root -> rightc, k, i, a, b);
}

// finds the value of the kth min element in the BST and returns its value
// if not found, it returns -1
int Pos(nodeprt root, int k, int a, int b)
{
    int i = 0;
    nodeprt ans = kthMin(root, k - 1, &i, a, b);

    if(ans == NULL)
        return -1;
    return ans -> val;
}


int main()
{
    int n;
    cout << "Enter a value for n: ";
    cin >> n;

    int *a = (int*)malloc(n * sizeof(int));
    cout << "Input a preorder traversal for a BST on n nodes: ";
    for(int i = 0; i < n; i++)
        cin >> a[i];

    int *b = (int*)malloc(n * sizeof(int));
    int *c = (int*)malloc(n * sizeof(int));

    // for Inorder and PostOrder traversals of the given Preorder traversal of a BST
    toInorder(a, b, n);
    toPostorder(a, c, n);

    // creates a BST out of the given preorder traversal
    nodeprt root = toBST(a, n);

    // takes an integer m as input, and taken m new integers, to be inserted into the BST
    int m;
    cout << "Input a value for m: ";
    cin >> m;   
    cout << "Insert m new values to insert to the BST: ";
    // Taking the numbers as input and inserting them in the BST
    for(int i = 0; i < m; i++)
    {
        int x;
        cin >> x;
        root = insertNode(root, x);
    }

    // taking the lower and upper range as input
    // if by chance, lower > upper, we swap them, to create a valid range
    int lower, upper;
    cout << "Enter 2 positive integers to specify a range: ";
    cin >> lower >> upper;
    if(lower > upper)
    {
        int temp = lower;
        lower = upper;
        upper = temp;
    }

    cout << "The average for this range: ";
    // finding the avg
    cout << Avg(root, lower, upper) << endl;

    cout << "The median for this range: ";

    // finding the median
    int countWithRange = countInRange(root, lower, upper);
    if(countWithRange % 2 == 0)
        cout << Pos(root, countWithRange / 2, lower, upper) << endl;
    else
        cout << Pos(root, countWithRange / 2 + 1, lower, upper) << endl;

    return 0;    
}