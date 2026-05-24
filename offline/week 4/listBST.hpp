#ifndef LISTBST_H
#define LISTBST_H

#include "BST.hpp"
#include <iostream>
#include <stdexcept>

/**
 * Binary Search Tree implementation using linked list structure
 *
 * @tparam Key - The type of keys stored in the BST
 * @tparam Value - The type of values associated with keys
 */
template <typename Key, typename Value>
class ListBST : public BST<Key, Value>
{
private:
    /**
     * Node class for the binary search tree
     */
    class Node
    {
    public:
        Key key;
        Value value;
        Node *left;
        Node *right;

        Node(Key k, Value v) : key(k), value(v), left(nullptr), right(nullptr) {}
    };

    Node *root;
    size_t node_count;

    // TODO: Implement private helper functions as needed
    // Start your private helper functions here

    Node *insertNode(Node *node, Key key, Value value, bool &inserted)
    {
        if (node == nullptr)
        {
            inserted = true;
            return new Node(key, value);
        }
        if (key < node->key)
        {
            node->left = insertNode(node->left, key, value, inserted);
        }
        else if (key > node->key)
        {
            node->right = insertNode(node->right, key, value, inserted);
        }
        else
        {
            inserted = false;
        }
        return node;
    }
    Node *findNode(Node *node, Key key) const
    {
        if (node == nullptr)
        {
            return nullptr;
        }
        else if (key == node->key)
        {
            return node;
        }
        else if (key < node->key)
        {
            return findNode(node->left, key);
        }
        else if (key > node->key)
        {
            return findNode(node->right, key);
        }
        return nullptr;
    }
    // End your private helper functions here
    Node *getValue(Node *node, Key key) const
    {
        if (node == nullptr)
        {
            return nullptr;
        }
        if (node->key == key)
        {
            return node;
        }
        else if (key < node->key)
        {
            return getValue(node->left, key);
        }
        else if (key > node->key)
        {
            return getValue(node->right, key);
        }
        else
        {
            std::cout << "Not found!" << std::endl;
            return nullptr;
        }
    }
    Node *find_minimum(Node *node) const
    {
        if (node->left == nullptr)
        {
            return node;
        }
        return find_minimum(node->left);
    }
    Node *find_maximum(Node *node) const
    {
        if (node->right == nullptr)
        {
            return node;
        }
        return find_maximum(node->right);
    }
    void clearBST(Node *node)
    {
        if (node != nullptr)
        {
            clearBST(node->left);
            clearBST(node->right);
            delete node;
        }
    }
    Node *deleteNode(Node *node, Key key, bool &deleted)
    {
        if (node == nullptr)
        {
            deleted = false;
            return nullptr;
        }

        if (key < node->key)
        {
            node->left = deleteNode(node->left, key, deleted);
        }
        else if (key > node->key)
        {
            node->right = deleteNode(node->right, key, deleted);
        }
        else
        {

            deleted = true;

            if (node->left == nullptr && node->right == nullptr)
            {
                delete node;
                return nullptr;
            }

            if (node->left == nullptr)
            {
                Node *temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr)
            {
                Node *temp = node->left;
                delete node;
                return temp;
            }

            Node *successor = find_minimum(node->right);
            node->key = successor->key;
            node->value=successor->value;
            node->right = deleteNode(node->right, successor->key, deleted);
        }

        return node;
    }
    void printInOrder(Node *node) const
    {
        if (node == nullptr)
        {
            return;
        }
        printInOrder(node->left);
        std::cout << "(" << node->key << ":" << node->value << ") ";
        printInOrder(node->right);
    }
    void printPreOrder(Node *node) const
    {
        if (node == nullptr)
            return;
        std::cout << "(" << node->key << ":" << node->value << ") ";
        printPreOrder(node->left);
        printPreOrder(node->right);
    }
    void printPostOrder(Node *node) const
    {
        if (node == nullptr)
            return;
        printPostOrder(node->left);
        printPostOrder(node->right);
        std::cout << "(" << node->key << ":" << node->value << ") ";
    }
    void printDefault(Node *node) const
    {
        if (node == nullptr)
        {
            std::cout << "()";
            return;
        }
        std::cout << "(" << node->key << ":" << node->value;
        if (node->right != nullptr || node->left != nullptr)
        {
            std::cout << " ";
            printDefault(node->left);
            if (node->right != nullptr)
            {
                std::cout << " ";
                printDefault(node->right);
            }
        }
        std::cout << ")";
    }

public:
    /**
     * Constructor
     */
    ListBST() : root(nullptr), node_count(0)
    {
    }

    /**
     * Destructor
     */
    ~ListBST()
    {
        // TODO: Implement destructor to free memory
        clearBST(root);
    }

    /**
     * Insert a key-value pair into the BST
     */
    bool insert(Key key, Value value) override
    {
        // TODO: Implement insertion logic
        bool inserted = false;
        root = insertNode(root, key, value, inserted);
        if (inserted == true)
            node_count++;
        return inserted;
    }

    /**
     * Remove a key-value pair from the BST
     *
     */
    bool remove(Key key) override
    {
        // TODO: Implement removal logic
        bool deleted = false;
        root = deleteNode(root, key, deleted);
        if (deleted == true)
        {
            node_count--;
        }
        return deleted;
    }

    /**
     * Find if a key exists in the BST
     */
    bool find(Key key) const override
    {
        // TODO: Implement find logic
        return findNode(root, key) != nullptr;
    }

    /**
     * Find a value associated with a given key
     */
    Value get(Key key) const override
    {
        // TODO: Implement get logic
        Node *node = getValue(root, key);
        return node->value;
    }

    /**
     * Update the value associated with a given key
     */
    void update(Key key, Value value) override
    {
        // TODO: Implement update logic
        if (find(key) == true)
        {
            Node *node = findNode(root, key);
            node->value = value;
        }
    }

    /**
     * Clear all elements from the BST
     */
    void clear() override
    {
        // TODO: Implement clear logic
        clearBST(root);
        node_count = 0;
        root = nullptr;
    }

    /**
     * Get the number of keys in the BST
     */
    size_t size() const override
    {
        // TODO: Implement size logic
        return node_count;
    }

    /**
     * Check if the BST is empty
     */
    bool empty() const override
    {
        // TODO: Implement empty check logic
        return node_count == 0;
    }

    /**
     * Find the minimum key in the BST
     */
    Key find_min() const override
    {
        // TODO: Implement find_min logic
        return find_minimum(root)->key;
    }

    /**
     * Find the maximum key in the BST
     */
    Key find_max() const override
    {
        // TODO: Implement find_max logic
        return find_maximum(root)->key;
    }

    /**
     * Print the BST using specified traversal method
     */
    void print(char traversal_type = 'D') const override
    {
        // TODO: Implement print logic
        if (traversal_type == 'I')
        {
            std::cout << "BST (In-order): ";
            printInOrder(root);
            std::cout << std::endl;
        }
        else if (traversal_type == 'P')
        {
            std::cout << "BST (Pre-order): ";
            printPreOrder(root);
            std::cout << std::endl;
        }
        else if (traversal_type == 'O')
        {
            std::cout << "BST (Post-order): ";
            printPostOrder(root);
            std::cout << std::endl;
        }
        else if (traversal_type == 'D')
        {
            std::cout << "BST (Default): ";
            printDefault(root);
            std::cout << std::endl;
        }
    }
};

#endif // LISTBST_H