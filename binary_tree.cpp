//
// Created by Ivan Istomin on 09/11/16.
//
#ifndef BINARY_TREE_BINARY_TREE_CPP
#define BINARY_TREE_BINARY_TREE_CPP

#include <stdexcept>
#include "binary_tree.h"

template<class T>
void BinaryTree<T>::insert(int key, T value) {

    // Get head address
    Node** tmp = &head;

    // Search null place
    while (*tmp != nullptr) {
        Node* const node = *tmp;

        if (key == node->key)
            throw std::logic_error("Key already exists!");
        else if (key < node->key) {
            tmp = &node->left;
        } else {
            tmp = &node->right;
        }
    }

    // Insert node
    *tmp = new Node(key, value);

    ++size;
}

// [ Auxiliary methods for removing ] Begin
template <typename T>
typename BinaryTree<T>::Node* findMin(typename BinaryTree<T>::Node* node){
    // While node is not a leaf, go to left
    while (node->left != nullptr)
        node = node->left;

    return node;
}

template <typename T>
typename BinaryTree<T>::Node* removeNode(typename BinaryTree<T>::Node* node, int key){
    if (node == nullptr)
        throw std::logic_error("Key does not exist");
    // Search node
    else if (key < node->key)
        node->left = removeNode<T>(node->left, key);
    else if (key > node->key)
        node->right = removeNode<T>(node->right, key);
    // Found the key
    else {
        // No Child
        if (node->left == nullptr && node->right == nullptr){
            delete node;
            node = nullptr;

        // Have Child
        } else if (node->left == nullptr){

            // Glue the end and remove node
            typename BinaryTree<T>::Node* tmp = node;
            node = node->right;

            delete tmp;
        } else if (node->right == nullptr){

            // Glue the end and remove node
            typename BinaryTree<T>::Node* tmp = node;
            node = node->left;

            delete tmp;
        } else {
            // Search min node from right side
            typename BinaryTree<T>::Node* tmp = findMin<T>(node->right);

            // Replace them
            node->key = tmp->key;
            node->value = tmp->value;

            // Remove min node from right side
            node->right = removeNode<T>(node->right, tmp->key);
        }
    }

    return node;
}
// [ Auxiliary methods for removing ] End

template<class T>
void BinaryTree<T>::remove(int key) {
    removeNode<T>(head, key);

    --size;
}

template<class T>
T BinaryTree<T>::find(int key) {

    // Get head address
    Node** tmp = &head;

    // Search node with this key
    while(*tmp != nullptr) {
        Node* const node = *tmp;

        if (key > node->key)
            tmp = &node->right;
        else if (key < node->key)
            tmp = &node->left;
        else if (key == node->key)
            return node->value;
    }

    // If the method did not return throw logic_error
    throw std::logic_error("Key does not exist");
}

template<class T>
void BinaryTree<T>::TraverseNode(Node *start, T (*func)(T)) {
    if (start != nullptr) {
        TraverseNode(start->left, func);
        start->value = func(start->value);
        TraverseNode(start->right, func);
    }
}

// [ Auxiliary method for destructor (because destructor can't be recursive) ] Begin
template <typename T>
void destructor(typename BinaryTree<T>::Node* node) {
    if (node != nullptr) {

        // Delete from leaf
        destructor<T>(node->left);
        destructor<T>(node->right);

        delete node;
    }
}
// [ Auxiliary method for destructor ] End

template<class T>
BinaryTree<T>::~BinaryTree() {
    destructor<T>(head);
}
#endif //BINARY_TREE_BINARY_TREE_CPP