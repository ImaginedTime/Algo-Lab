/***********************************************
    Uday om srivastava 22ME30072 Assignment 6
************************************************/

#include <iostream>

using namespace std;

typedef struct local_node *local_ptr;
struct local_node
{
    int data;
    local_ptr left;
    local_ptr right;
    local_ptr parent;
};

local_ptr rearrange(local_ptr node)
{
    while(node != nullptr && node -> parent != nullptr)
    {
        if(node -> parent -> parent == nullptr)
        {
            if(node -> parent -> left == node)
            {
                local_ptr par = node -> parent;
                node -> parent = nullptr;

                par -> left = node -> right;
                if(node -> right)
                    node -> right -> parent = par;

                node -> right = par;
                if(par)
                    par -> parent = node;

                continue;
            }
            else{

                local_ptr par = node -> parent;
                node -> parent = nullptr;

                par -> right = node -> left;
                if(node -> left)
                    node -> left -> parent = par;

                node -> left = par;
                if(par)
                    par -> parent = node;
                continue;
            }
        }

        if(node -> parent -> parent -> left && node -> parent -> parent -> left -> left == node)
        {
            local_ptr par = node -> parent;
            local_ptr gp = node -> parent -> parent;
            node -> parent = gp -> parent;

            if(gp -> parent)
            {
                if(gp -> parent -> left == gp)
                    gp -> parent -> left = node;
                else    
                    gp -> parent -> right = node;
            }

            gp -> left = par -> right;
            if(par -> right)
                par -> right -> parent = gp;

            par -> left = node -> right;
            if(node -> right)
                node -> right -> parent = par;

            node -> right = par;
            if(par)
                par -> parent = node;

            par -> right = gp;
            if(gp)
                gp -> parent = par;

            continue;
        }

        if(node -> parent -> parent -> right && node -> parent -> parent -> right -> right == node)
        {

            local_ptr par = node -> parent;
            local_ptr gp = node -> parent -> parent;
            node -> parent = gp -> parent;
            if(gp -> parent)
            {
                if(gp -> parent -> left == gp)
                    gp -> parent -> left = node;
                else    
                    gp -> parent -> right = node;
            }

            gp -> right = par -> left;
            if(par -> left)
                par -> left -> parent = gp;

            par -> right = node -> left;
            if(node -> left)
                node -> left -> parent = par;

            node -> left = par;
            if(par)
                par -> parent = node;

            par -> left = gp;
            if(gp)
                gp -> parent = par;

            continue;
        }

        if(node -> parent -> parent -> left && node -> parent -> parent -> left -> right == node)
        {

            local_ptr par = node -> parent;
            local_ptr gp = node -> parent -> parent;
            node -> parent = gp -> parent;
            if(gp -> parent)
            {
                if(gp -> parent -> left == gp)
                    gp -> parent -> left = node;
                else    
                    gp -> parent -> right = node;
            }


            par -> right = node -> left;
            if(node -> left)
                node -> left -> parent = par;

            gp -> left = node -> right;
            if(node -> right)
                node -> right -> parent = gp;

            node -> left = par;
            if(par)
                par -> parent = node;

            node -> right = gp;
            if(gp)
                gp -> parent = node;

            continue;
        }

        if(node -> parent -> parent -> right && node -> parent -> parent -> right -> left == node)
        {

            local_ptr par = node -> parent;
            local_ptr gp = node -> parent -> parent;
            node -> parent = gp -> parent;

            if(gp -> parent)
            {
                if(gp -> parent -> left == gp)
                    gp -> parent -> left = node;
                else    
                    gp -> parent -> right = node;
            }

            par -> left = node -> right;
            if(node -> right)
                node -> right -> parent = par;

            gp -> right = node -> left;
            if(node -> left)
                node -> left -> parent = gp;

            node -> right = par;
            if(par)
                par -> parent = node;

            node -> left = gp;
            if(gp)
                gp -> parent = node;

            continue;
        }
    }
    return node;
}

void preorder(local_ptr root)
{
    if(root == nullptr)
        return;

    cout << root -> data << ", ";
    preorder(root -> left);
    preorder(root -> right);
}

local_ptr insert(local_ptr root, int key)
{
    if(root == nullptr)
    {
        root = new struct local_node();
        root -> data = key;
        root -> parent = nullptr;
        return root;
    }

    // by the property of BST, goes to the left most greater part and insert the node there, and vice versa
    if(key <= root -> data)
    {
        local_ptr left_child = insert(root -> left, key);
        root -> left = left_child;
        left_child -> parent = root;
    }
    else
    {
        local_ptr right_child = insert(root -> right, key);
        root -> right = right_child;
        right_child -> parent = root;
    }

    return root;
}

local_ptr search(local_ptr root, int key)
{
    if(root == nullptr)
        return nullptr;
    if(root -> data == key)
        return root;
    
    local_ptr foundInLeft = search(root -> left, key);
    if(foundInLeft != nullptr)
        return foundInLeft;
    
    
    return search(root -> right, key);
}

int main()
{
    local_ptr root = nullptr;


    int choice;
    cout << "1. insert\n2. search\n3. exit\n\n";
    do{
        cin >> choice;
        switch(choice)
        {
            case 1:
            {
                cout << "Write key to be inserted: ";
                int key;
                cin >> key;

                root = insert(root, key);

                local_ptr node = search(root, key);
                root = rearrange(node);

                cout << "Preorder Traversal: ";
                preorder(root);
                cout << endl;
                break;
            }
            case 2:
            {
                cout << "Write key to be searched: ";
                int key;
                cin >> key;

                local_ptr node = search(root, key);
                root = rearrange(node);
                cout << "node value: " << node -> data << endl;

                cout << "Preorder Traversal: ";
                preorder(root);
                cout << endl;
                break;
            }
            case 3:
                return 0;
            default:
                cout << "Invalid choice!" << endl;
        }
    } while(choice != 3);

    return 0;
}