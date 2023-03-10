// genbst.cpp
// Implements class GenBST
// Oviya Seeniraj, 3/1/23

#include <iostream>
using std::cout;

// constructor sets up empty tree
template<typename T> GenBST<T>::GenBST()
{
    this->root = nullptr;
}

// destructor deletes all nodes
template<typename T> GenBST<T>::~GenBST()
{
    clear(this->root);
}

// recursive helper for destructor
template<typename T> void GenBST<T>::clear(Node *n)
{
    // post-order deletion

    if (n == nullptr)
    {
        return;
    }

    clear(n->left);
    clear(n->right);
    delete n;
}

// insert value in tree; return false if duplicate
template<typename T> bool GenBST<T>::insert(T value)
{
    return (insert(value, this->root));
}

// recursive helper for insert (assumes n is never 0)
template<typename T>
bool GenBST<T>::insert(T value, Node *n)
{
    // base case:
    if (n == nullptr)
    {
        n = new Node(value);
        this->root = n;

        return true;
    }

    else if (n->left == nullptr && value < n->info)
    {
        n->left = new Node(value);
        n->left->parent = n;
    }

    else if (n->right == nullptr && value > n->info)
    {
        n->right = new Node(value);
        n->right->parent = n;
    }

    else if (value < n->info)
    {
        insert(value, n->left);
    }

    else if (value > n->info)
    {
        insert(value, n->right);
    }

    return false;
}

// print tree data pre-order
template<typename T>
void GenBST<T>::printPreOrder() const
{
    printPreOrder(this->root);
}

// recursive helper for printPreOrder()
template<typename T>
void GenBST<T>::printPreOrder(Node *n) const
{
    if (n == nullptr)
    {
        return;
    }
    cout << n->info << " ";
    printPreOrder(n->left);
    printPreOrder(n->right);
}

// print tree data in-order, with helper
template<typename T>
void GenBST<T>::printInOrder() const
{
    printInOrder(this->root); // IMPLEMENT HERE
}

template<typename T>
void GenBST<T>::printInOrder(Node *n) const
{
    if (n == nullptr)
    {
        return;
    }
    printInOrder(n->left);
    cout << n->info << " ";
    printInOrder(n->right);
}

// prints tree data post-order, with helper
template<typename T>
void GenBST<T>::printPostOrder() const
{
    printPostOrder(this->root);
}

template<typename T>
void GenBST<T>::printPostOrder(Node *n) const
{
    if (n == nullptr)
    {
        return;
    }
    printPostOrder(n->left);
    printPostOrder(n->right);
    cout << n->info << " ";
}

// return sum of values in tree
template<typename T>
T GenBST<T>::sum() const
{
    return sum(this->root);
}

// recursive helper for sum
template<typename T>
T GenBST<T>::sum(Node *n) const
{
    if (n == nullptr)
    {
        return 0;
    }
    return n->info + sum(n->left) + sum(n->right);
}

// return count of values
template<typename T>
int GenBST<T>::count() const
{
    return count(this->root);
}

// recursive helper for count
template<typename T>
int GenBST<T>::count(Node *n) const
{
    if (n == nullptr)
    {
        return 0;
    }
    return 1 + count(n->left) + count(n->right);
}

// IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
// Parameters:
// T value: the value to be found
// Node* n: the node to start with (for a recursive call)
// Whenever you call this method from somewhere else, pass it
// the root node as "n"
template<typename T>
typename GenBST<T>::Node *GenBST<T>::getNodeFor(T value, Node *n) const
{

    if (n == nullptr)
    {
        return NULL;
    }

    if (n->info == value)
    {
        return n;
    }

    if (value < n->info)
    {
        return getNodeFor(value, n->left);
    }
    else
    {
        return getNodeFor(value, n->right);
    }
}

// returns true if value is in the tree; false if not
template<typename T>
bool GenBST<T>::contains(T value) const
{
    if (getNodeFor(value, this->root) != NULL)
    {
        return true;
    }
    return false;
}

// returns the Node containing the predecessor of the given value
template<typename T>
typename GenBST<T>::Node *GenBST<T>::getPredecessorNode(T value) const
{
    if (count() == 0 || count() == 1)
    {
        return nullptr;
    }

    Node* n  = getNodeFor(value, this->root);

    if (n == nullptr)
        return 0;

    if (!n->left)
    {
        Node *temp = n;
        while (temp->parent)
        {
            temp = temp->parent;
            if (temp->info < value)
            {
                n = temp;
                break;
            }
        }
        if (n->info == value)
        {
            return 0;
        }
        else
        {
            return n;
        }
    }

    if (n->left)
    {
        n = n->left;
        while (n->right)
        {
            n = n->right;
        }
        return n;
    }
}

// returns the predecessor value of the given value or 0 if there is none
template<typename T>
T GenBST<T>::getPredecessor(T value) const
{
    if (getPredecessorNode(value))
    {
        return getPredecessorNode(value)->info;
    }

    return 0;
}

// returns the Node containing the successor of the given value
template<typename T>
typename GenBST<T>::Node *GenBST<T>::getSuccessorNode(T value) const
{
    if (count() == 0 || count() == 1)
    {
        return nullptr;
    }

    Node* n  = getNodeFor(value, this->root);

    if (n == nullptr)
        return 0;

    if (!n->right)
    {
        if (n->parent)
        {

        }
        Node *temp = n;
        while (temp->parent)
        {
            temp = temp->parent;
            if (temp->info > value)
            {
                n = temp;
                break;
            }
        }
        if (n->info == value)
        {
            return 0;
        }
        else
        {
            return n;
        }
    }

    if (n->right)
    {
        n = n->right;
        while (n->left)
        {
            n = n->left;
        }
        return n;
    }
}

// returns the successor value of the given value or 0 if there is none
template<typename T>
T GenBST<T>::getSuccessor(T value) const
{

    if (getSuccessorNode(value))
    {
        return getSuccessorNode(value)->info;
    }

    return 0;
}

// deletes the Node containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not exist
template<typename T>
bool GenBST<T>::remove(T value)
{
    Node* n = getNodeFor(value,this->root);


    if (!n) // node does not exist
    {
        return false;
    } 

    bool isLeftChild;
    if (n->parent)
        isLeftChild = (n->info < n->parent->info);
    else
        isLeftChild = false;

    if (count() == 1) // one node case
    {
        this->root = nullptr;
        delete n;
        return true;
    }

    if (!n->left && !n->right) // no children case
    {
        // if (n == this->root) // one node case
        // {
        //     this->root = NULL;
        // } 
        if (isLeftChild) 
        {
            n->parent->left = NULL;
        } 
        else 
        {
            n->parent->right = NULL;
        }
        delete n;
        return true;
    } 

    // one child cases:

    else if (!n->left) 
    {
        if (n == this->root) // root case: does not have parent
        {
            this->root = n->right;
            this->root->parent = nullptr;
            delete n;
            return true;
        } 
        else if (isLeftChild) 
        {
            n->parent->left = n->right;
            n->right->parent = n->parent;
            delete n;
            return true;
        } 
        else 
        {
            n->parent->right = n->right;
            n->right->parent = n->parent;
            delete n;
            return true;
        }
    } 

    else if (!n->right) 
    {
        if (n == this->root) // root case, no parent
        {
            this->root = n->left;
            this->root->parent = nullptr;
            delete n;
            return true;
        } 
        else if (isLeftChild) 
        {
            n->parent->left = n->left;
            n->left->parent = n->parent;
            delete n;
            return true;
        } 
        else 
        {
            n->parent->right = n->left;
            n->left->parent = n->parent;
            delete n;
            return true;
        }
    } 
    else // two node case
    {
        Node* pre = getPredecessorNode(value);
        if (!pre) 
            return false;

        T newVal = pre->info;
        remove(pre->info);
        n->info = newVal;
        return true;
    }
}
