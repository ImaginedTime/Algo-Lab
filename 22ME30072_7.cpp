/************************************************
    Uday om srivastava 22ME30072 Assignment 7
*************************************************/

#include <iostream>

using namespace std;

typedef struct node *nodeptr;
struct node
{
    int key;
    int priority;
    nodeptr left;
    nodeptr right;
    nodeptr parent;
};

// rotates the given BST to maintain the min heap property for the priority values
nodeptr rotate(nodeptr curr, nodeptr par)
{
    // grandparent of the curr which is also the parent of the par
    nodeptr gp = par -> parent;

    // if curr is the left child of the parent
    if(par -> left == curr)
    {
        par -> left = curr -> right;
        // try to access the parent of right of curr only if the right of curr exists
        if(curr -> right)
            curr -> right -> parent = par;

        curr -> parent = gp;
        // only if the grandparent exists, try to change it's left or right
        if(gp)
        {
            if(gp -> left == par)
                gp -> left = curr;
            else
                gp -> right = curr;
        }

        curr -> right = par;
        par -> parent = curr;

        return curr;
    }
    // if curr is the right child of the parent
    else
    {
        par -> right = curr -> left;
        // try to access the parent of left of curr only if the left of curr exists
        if(curr -> left)
            curr -> left -> parent = par;

        curr -> parent = gp;
        // only if the grandparent exists, try to change it's left or right
        if(gp)
        {
            if(gp -> right == par)
                gp -> right = curr;
            else
                gp -> left = curr;
        }

        curr -> left = par;
        par -> parent = curr;

        return curr;
    }
}

nodeptr heapify(nodeptr heap, nodeptr root) 
{
    // whenever the heap property for the priority values is not satisfied, perform the rotation
    while((heap -> parent) && (heap -> parent -> priority) > (heap -> priority))
    {
        // if the root is changed and the rotation has reached the root element
        if(heap -> parent == root)
        {
            heap = rotate(heap, heap -> parent);
            return heap;
        }
        // normally swap to maintain the heap property
        heap = rotate(heap, heap -> parent);
    }

    return root;
}

// it inserts the given key and priority in the BST and
// it returns an array of 2 elements
// the first is the root of the BST and the second is the new node that was inserted in the BST
nodeptr* insertBST(nodeptr root, int key, int priority) 
{

    if(root == nullptr)
    {
        root = new node();
        root -> key = key;
        root -> priority = priority;
        root -> parent = nullptr;

        nodeptr *r = (nodeptr*)malloc(2 * sizeof(nodeptr));
        r[0] = root;
        r[1] = root;
        return r;
    }

    // by the property of BST, goes to the left most greater part and insert the node there, and vice versa
    if(key <= root -> key)
    {
        nodeptr* r = insertBST(root -> left, key, priority);
        nodeptr lchild = r[0];
        root -> left = lchild;
        lchild -> parent = root;

        r[0] = root;
        return r;
    }
    else
    {
        nodeptr* r = insertBST(root -> right, key, priority);
        nodeptr rchild = r[0];
        root -> right = rchild;
        rchild -> parent = root;
        
        r[0] = root;
        return r;
    }
}

// It performs a Binary search on the BST
// ignoring the curr node if it even becomes the value that we are trying to find
// so that the same value does not repeat twice
nodeptr searchInBST(nodeptr root, int val, nodeptr curr)
{
    if(root == nullptr)
        return root;
    
    // if the root itself is the value to be found
    if(root -> key == val && root != curr)
        return root;
    
    // find in the left subtree
    nodeptr foundInLeft = searchInBST(root -> left, val, curr);
    if(foundInLeft)
        return foundInLeft;
    
    // else try to find the right subtree
    return searchInBST(root -> right, val, curr);
}

// finds 2 elements in the BST whose sum is equal to the given sum
// It does so in O(nlogn) time and O(1) space
// It does so by taking k1 to be the key of the root and trying to find the sum - k1 in the remaining BST
bool search(nodeptr root, int sum)
{
    if(root == nullptr)
        return false;

    nodeptr found = nullptr;
    if(sum > root -> key)
        found = searchInBST(root, sum - root -> key, root);

    if(found != nullptr)
    {
        cout << sum << " is the sum of " << root -> key << " and " << found -> key << endl;
        return true;
    }

    bool foundInRoot = search(root -> left, sum);
    if(foundInRoot)
        return true;

    return search(root -> right, sum);
}

// prints the preorder traversal of the tree
void preorder(nodeptr root)
{
    if(root == nullptr)
        return;

    cout << "(" << root -> key << "," << root -> priority << ")  ";
    preorder(root -> left);
    preorder(root -> right);
}


int main()
{
    cout << "1. Insert\n2. Search Sum\n3. Exit\n\n";

    nodeptr root = nullptr;

    while(true)
    {
        int choice;
        cin >> choice;

        switch(choice)
        {
            case 1:
            {
                cout << "Write key and priority values to be inserted: ";
                int k, pr;
                cin >> k >> pr;
                nodeptr* r = insertBST(root, k, pr);
                root = r[0];

                root = heapify(r[1], root);

                cout << "Preorder traversal:  ";
                preorder(root);
                cout << endl;
                break;
            }
            case 2:
            {
                cout << "Write the sum to be searched: ";
                int sum;
                cin >> sum;

                bool found = search(root, sum);
                if(!found)
                {
                    cout << "There are no 2 elements in the BST that sum upto the given sum" << endl;
                }
                break;
            }
            case 3:
                return 0;
            default:
                cout << "Invalid choice!" << endl;
        }
    }

    return 0;
}