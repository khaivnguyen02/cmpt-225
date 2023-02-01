#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;

// AVL Node Class
template <class K, class V>
class AVLTreeNode
{
public:
    // Should have attributes named:
    // parent - pointer to parent
    AVLTreeNode *parent;
    // left - pointer to left child
    AVLTreeNode *left;
    // right - pointer to right child
    AVLTreeNode *right;
    // key - node's key
    K key;
    // value - node's value
    V value;
    // height - node's height
    unsigned int height;
    // Constructors ...
    AVLTreeNode(K key, V value)
    {
        this->key = key;
        this->value = value;
        left = right = parent = nullptr;
        height = 0;
    }
};
// AVL Tree class
template <class K, class V>
class AVLTree
{
private:
    // Tree attributes go here
    // Your tree MUST have a root node named root
    unsigned int numberOfNodes;

    /* --- Helper methods --- */
    AVLTreeNode<K, V> *rightRotate(AVLTreeNode<K, V> *);
    AVLTreeNode<K, V> *leftRotate(AVLTreeNode<K, V> *);
    AVLTreeNode<K, V> *insert(AVLTreeNode<K, V> *, K, V);
    unsigned int getBalance(AVLTreeNode<K, V> *);
    V search(AVLTreeNode<K, V> *, K) const;
    K max(K, K);
    unsigned int height(AVLTreeNode<K, V> *);
    AVLTreeNode<K, V> *remove(AVLTreeNode<K, V> *, K);
    bool isExisted(K) const;
    AVLTreeNode<K, V> *min(AVLTreeNode<K, V> *);
    AVLTreeNode<K, V> *successor(AVLTreeNode<K, V> *);

    void values(AVLTreeNode<K, V> *, vector<V> &) const;
    void keys(AVLTreeNode<K, V> *, vector<K> &) const;

    AVLTreeNode<K, V> *copy(AVLTreeNode<K, V> *);
    void deleteTree(AVLTreeNode<K, V> *);

public:
    AVLTreeNode<K, V> *root;
    void *getRoot() const { return root; }; // DO NOT REMOVE
    // Constructor
    AVLTree();
    AVLTree(AVLTree<K, V> &);
    // Destructor
    ~AVLTree();
    // Assignment operator
    AVLTree<K, V> &operator=(AVLTree<K, V> &);
    // AVLTree<K, V> &operator=(AVLTree<K, V>);
    bool insert(K, V);
    bool remove(K);

    V search(K) const;

    vector<V> values() const;
    vector<K> keys() const;

    unsigned int size() const;
};

// AVL Tree Methods go here
template <class K, class V>
AVLTree<K, V>::AVLTree() : root(nullptr)
{
    numberOfNodes = 0;
}

template <class K, class V>
AVLTree<K, V>::AVLTree(AVLTree &tree)
{
    this->numberOfNodes = tree.numberOfNodes;
    this->root = copy(tree.root);
}

template <class K, class V>
AVLTree<K, V>::~AVLTree()
{
    deleteTree(root);
}

template <class K, class V>
AVLTree<K, V> &AVLTree<K, V>::operator=(AVLTree<K, V> &tree)
{
    if (this != &tree)
    {
        this->deleteTree(root);
        this->numberOfNodes = tree.numberOfNodes;
        this->root = copy(tree.root);
    }
    return *this;
}

template <class K, class V>
bool AVLTree<K, V>::insert(K key, V value)
{
    if (isExisted(key))
        return false;
    else
    {
        root = insert(root, key, value); // helper function
        numberOfNodes++;
        return true;
    }
}
template <class K, class V>
AVLTreeNode<K, V> *AVLTree<K, V>::insert(AVLTreeNode<K, V> *node, K key, V value)
{
    // BST insertion
    // Base case
    if (node == NULL)
    {
        return new AVLTreeNode<K, V>(key, value);
    }

    if (key < node->key)
    { // left subtree
        node->left = insert(node->left, key, value);
        node->left->parent = node;
    }
    else if (key > node->key)
    { // right subtree
        node->right = insert(node->right, key, value);
        node->right->parent = node;
    }

    node->height = 1 + max(height(node->left),
                           height(node->right));

    int balance = getBalance(node);

    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);
    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Left Case
    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Left Right Case
    if (balance > 1 && key > node->left->key)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    return node;
} // insert

template <class K, class V>
bool AVLTree<K, V>::remove(K key)
{
    if (isExisted(key))
    {
        root = remove(root, key);
        numberOfNodes--;
        return true;
    }
    return false;
}

template <class K, class V>
AVLTreeNode<K, V> *AVLTree<K, V>::remove(AVLTreeNode<K, V> *node, K key)
{
    // Find the node to be deleted
    if (node == NULL)
        return node;

    if (key < node->key)
        node->left = remove(node->left, key);
    else if (key > node->key)
        node->right = remove(node->right, key);
    else // key is found
    {
        if ((node->left == NULL) || (node->right == NULL))
        {
            AVLTreeNode<K, V> *temp = node->left ? node->left : node->right;

            if (temp == NULL)
            {
                temp = node;
                node = NULL;
            }
            else
            {
                *node = *temp;
            }
            free(temp);
        } // nodeToBeDeleted has only 1 child
        else
        {
            AVLTreeNode<K, V> *temp = successor(node);
            node->key = temp->key;
            node->value = temp->value;
            node->right = remove(node->right, temp->key);
        } // nodeToBeDeleted has 2 children
    }

    if (node == NULL)
        return node;

    node->height = 1 + max(height(node->left),
                           height(node->right));

    int balance = getBalance(node);

    // If node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 &&
        getBalance(node->left) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 &&
        getBalance(root->left) < 0)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Right Case
    if (balance < -1 &&
        getBalance(node->right) <= 0)
        return leftRotate(node);

    // Right Left Case
    if (balance < -1 &&
        getBalance(node->right) > 0)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

template <class K, class V>
V AVLTree<K, V>::search(K key) const
{
    return search(root, key);
}

template <class K, class V>
V AVLTree<K, V>::search(AVLTreeNode<K, V> *root, K key) const
{
    // Base case
    if (root == NULL)
        throw std::runtime_error("NaN");
    if (root->key == key)
        return root->value;
    if (key < root->key)
        return search(root->left, key);
    else
        return search(root->right, key);
} // search

template <class K, class V>
vector<V> AVLTree<K, V>::values() const
{
    vector<V> result = {};
    values(root, result); // helper function
    return result;
}

template <class K, class V>
void AVLTree<K, V>::values(AVLTreeNode<K, V> *node, vector<V> &result) const
{
    if (node != NULL)
    {
        values(node->left, result);
        result.push_back(node->value);

        values(node->right, result);
    }
}
template <class K, class V>
vector<K> AVLTree<K, V>::keys() const
{
    vector<K> result = {};
    keys(root, result); // helper function
    return result;
}

template <class K, class V>
void AVLTree<K, V>::keys(AVLTreeNode<K, V> *node, vector<K> &result) const
{
    if (node != NULL)
    {
        keys(node->left, result);
        result.push_back(node->key);

        values(node->right, result);
    }
}
template <class K, class V>
unsigned int AVLTree<K, V>::size() const
{
    return this->numberOfNodes;
}

template <class K, class V>
AVLTreeNode<K, V> *AVLTree<K, V>::rightRotate(AVLTreeNode<K, V> *node)
{
    AVLTreeNode<K, V> *parentNode = node->parent;
    AVLTreeNode<K, V> *leftNode = node->left;
    // Perform rotation
    node->left = leftNode->right;
    if (leftNode->right != NULL)
        leftNode->right->parent = node;

    leftNode->right = node;
    node->parent = leftNode;
    leftNode->parent = parentNode;

    if (parentNode != NULL)
    {
        if (parentNode->left == node)
            parentNode->left = leftNode;
        else
            parentNode->right = leftNode;
    }

    // Update heights
    node->height = max(height(node->left),
                       height(node->right)) +
                   1;
    leftNode->height = max(height(leftNode->left),
                           height(leftNode->right)) +
                       1;

    return leftNode;
}

template <class K, class V>
AVLTreeNode<K, V> *AVLTree<K, V>::leftRotate(AVLTreeNode<K, V> *node)
{
    AVLTreeNode<K, V> *parentNode = node->parent;
    AVLTreeNode<K, V> *rightNode = node->right;

    // Perform rotation
    node->right = rightNode->left;
    if (rightNode->left != NULL)
        rightNode->left->parent = node;

    rightNode->left = node;
    node->parent = rightNode;
    rightNode->parent = parentNode;

    if (parentNode != NULL)
    {
        if (parentNode->right == node)
            parentNode->right = rightNode;
        else
            parentNode->left = rightNode;
    }

    // Update heights
    node->height = max(height(node->left),
                       height(node->right)) +
                   1;
    rightNode->height = max(height(rightNode->left),
                            height(rightNode->right)) +
                        1;

    return rightNode;

    // Node *y = x->right;
    // Node *T2 = y->left;

    // // Perform rotation
    // y->left = x;
    // x->right = T2;

    // // Update heights
    // x->height = max(height(x->left),
    //                 height(x->right)) + 1;
    // y->height = max(height(y->left),
    //                 height(y->right)) + 1;

    // // Return new root
    // return y;
}

template <class K, class V>
unsigned int AVLTree<K, V>::height(AVLTreeNode<K, V> *node)
{
    if (node == NULL)
        return -1;
    return node->height;
}

template <class K, class V>
K AVLTree<K, V>::max(K k1, K k2)
{
    return (k1 > k2) ? k1 : k2;
}

template <class K, class V>
bool AVLTree<K, V>::isExisted(K key) const
{
    if (root == nullptr)
    {
        return false;
    }
    if (root->key == key)
    {
        return true;
    }
    AVLTreeNode<K, V> *curr = root;
    while (curr && curr->key != key)
    {
        if (key < curr->key)
        {
            curr = curr->left;
        }
        else
        {
            curr = curr->right;
        }
    }
    if (curr && curr->key == key)
    {
        return true;
    }
    return false;
} // search with while loop

template <class K, class V>
unsigned int AVLTree<K, V>::getBalance(AVLTreeNode<K, V> *node)
{
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
} // get Balance Factor

template <class K, class V>
AVLTreeNode<K, V> *AVLTree<K, V>::min(AVLTreeNode<K, V> *node)
{
    if (node->left == NULL)
        return node;

    return min(node->left);
} // min

template <class K, class V>
AVLTreeNode<K, V> *AVLTree<K, V>::successor(AVLTreeNode<K, V> *node)
{
    if (node->right)
        return min(node->right);

    for (; node->parent; node = node->parent)
    {
        if (node->parent->left == node)
            return node->parent;
    }
    return NULL;
} // successor

template <class K, class V>
AVLTreeNode<K, V> *AVLTree<K, V>::copy(AVLTreeNode<K, V> *node)
{
    if (node == NULL)
        return NULL;

    AVLTreeNode<K, V> *newNode = new AVLTreeNode<K, V>(node->key, node->value);
    newNode->height = node->height;

    newNode->left = copy(node->left);
    if (newNode->left)
        newNode->left->parent = newNode;

    newNode->right = copy(node->right);
    if (newNode->right)
        newNode->right->parent = newNode;

    return newNode;
}

template <class K, class V>
void AVLTree<K, V>::deleteTree(AVLTreeNode<K, V> *node)
{
    if (node != NULL)
    {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}