/************************************************
    Uday om srivastava 22ME30072 Assigment 4
************************************************/

#include <iostream>
#include <stdlib.h>

using namespace std;

// defining the struct for the BST
typedef struct node{
    int value;
    struct node *left;
    struct node *right;
    struct node *parent;
} NODE, *NODEPRT;


// function to insert a value in the BST
NODEPRT insertNode(NODEPRT root, int data)
{
    // if root does not exist, make the node and insert the value
    // base case
    if(root == nullptr)
    {
        root = new NODE();
        root -> value = data;
        root -> parent = nullptr;
        return root;
    }

    // by the property of BST, goes to the left most greater part and insert the node there, and vice versa
    if(data <= root -> value)
    {
        NODEPRT lchild = insertNode(root -> left, data);
        root -> left = lchild;
        lchild -> parent = root;
    }
    else
    {
        NODEPRT rchild = insertNode(root -> right, data);
        root -> right = rchild;
        rchild -> parent = root;
    }

    return root;
}


// function to create the binary search tree
NODEPRT createBST(int* levelOrderTraversal, int n)
{
    if(n == 0)
        return nullptr;

    // creating an empty root
    NODEPRT root = nullptr;

    // inserting the values in the BST
    for(int i = 0; i < n; i++)
        root = insertNode(root, levelOrderTraversal[i]);

    return root;
}


// preorder traversal of the tree
// ROOT LEFT RIGHT
void preOrder(NODEPRT root)
{
    if(root == nullptr)
        return;
    cout << root -> value << ", ";
    preOrder(root -> left);
    preOrder(root -> right);
}


// inorder traversal of the tree
// LEFT ROOT RIGHT
void inOrder(NODEPRT root)
{
    if(root == nullptr)
        return;
    inOrder(root -> left);
    cout << root -> value << ", ";
    inOrder(root -> right);
}


// post order traversal of the tree
// LEFT RIGHT ROOT
void postOrder(NODEPRT root)
{
    if(root == nullptr)
        return;
    postOrder(root -> left);
    postOrder(root -> right);
    cout << root -> value << ", ";
}


// printing all the traversals of the tree; by calling the above 3 methods
void printBST(NODEPRT root)
{
    cout << endl << "PreOrder Traversal: ";
    preOrder(root);
    cout << endl;
    cout << "InOrder Traversal: ";
    inOrder(root);
    cout << endl;
    cout << "PostOrder Traversal: ";
    postOrder(root);
    cout << endl;
}


// finding the kth-minimum element of the BST using the inorder traversal of the tree
NODEPRT kth_Minimum(NODEPRT root, int k, int* i)
{
    if(root == nullptr)
        return nullptr;
    
    // if the kth minimum is in the left sub part
    NODEPRT foundInLeft = kth_Minimum(root -> left, k, i);
    if(foundInLeft != nullptr)
        return foundInLeft;
    
    // if root is the kth minimum, print it
    if((*i)++ == k)
    {
        cout << endl << k + 1 << "-th smallest element is " << root -> value << endl;
        return root;
    }

    // search in the right sub part for the kth minimum
    return kth_Minimum(root -> right, k, i);
}


// using the kth-minimum function here, to find the kth minimum element of the BST
void min_k(NODEPRT root, int k)
{
    // to index the BST for finding the kth minimum
    int i = 0;
    NODEPRT ans = kth_Minimum(root, k - 1, &i);

    // if k is larger than the number of elements in the BST, the kth min does not exist
    if(ans == nullptr)
        cout << k << "-th smallest element not found" << endl;
}


// function to find the node with the value l
NODEPRT findNode(NODEPRT root, int l)
{
    if(root == nullptr)
        return nullptr;
    // if the value is the root itself
    if(root -> value == l)
        return root;
    
    // if value to be found is in the left sub part, stop searching further
    NODEPRT findInLeft = findNode(root -> left, l);
    if(findInLeft != nullptr)
        return findInLeft;
    
    // find the value in the right sub part
    return findNode(root -> right, l);
}


// for the 3rd part of the question, which requires parent to be for each of the node
// with root node having the parent as nullptr
// void makeParent(NODEPRT root)
// {
//     if(root == nullptr)
//         return;

//     if(root-> left)
//     {
//         root -> left -> parent = root;
//         makeParent(root->left);
//     }
//     if(root -> right)
//     {
//         root -> right -> parent = root;
//         makeParent(root->right);
//     }

// }


// change part of the 3rd question
// NODEPRT change(NODEPRT root, NODEPRT node, NODEPRT new_par)
// {
//     if(node == root)
//     {
//         node->parent = new_par;
//         if(node->left == new_par)
//             node->left = nullptr;
//         if(node -> right == new_par)
//             node->right = nullptr;
//         return root;
//     }

//     if(node -> left != nullptr)
//     {
//         node->right = node-> left;
//     }
//     if(node->parent->left == node)
//     {
//         node -> parent -> left = nullptr;
//     }

//     node -> left = change(root, node -> parent, node);
//     node -> parent = new_par;
//     return node;
// }

NODEPRT flipBinaryTree(NODEPRT root, NODEPRT leaf) {
    NODEPRT curr = leaf, parent = nullptr;
    while (true) {
        NODEPRT child = curr->parent;
        curr->parent = parent;
        if (curr->left == parent) {
            curr->left = nullptr;
        } else {
            curr->right = nullptr;
        }
        if (curr == root) {
            break;
        }
        if (curr->left) {
            curr->right = curr->left;
        }
        curr->left = child;
        parent = curr;
        curr = child;
    }
    return leaf;
}


// function to find the value and rearrange the BST according to the value found
NODEPRT find_and_change(NODEPRT root, int l)
{
    NODEPRT newRoot = findNode(root, l);
    if(newRoot == nullptr)
    {
        cout << "No such node found in the BST" << endl;
        return nullptr;
    }

    // makeParent(root);

    return flipBinaryTree(root, newRoot);
}



int main()
{
    int n;
    cout << "Enter number of elements n: ";
    cin >> n;

    cout << "Enter level order traversal for creating a binary search tree: ";
    int *levelOrderTraversal = (int*)malloc(n * sizeof(int));
    for(int i = 0; i < n; i++)
        cin >> levelOrderTraversal[i];

    NODEPRT root = createBST(levelOrderTraversal, n);
    // prints all the traversals of the BST
    printBST(root);

    int k;
    cout << endl << "Enter k: ";
    cin >> k;
    // find the kth minimum element of the BST
    min_k(root, k);

    
    int l;
    cout << endl << "Enter l: ";
    cin >> l;
    // Node to rearrange the BST by
    NODEPRT ans = find_and_change(root, l);

    // printing the traversals after the rearrangement of the BST
    printBST(ans);

    return 0;
}