#include "binary_tree.h"
#include <iostream>
#include <vector>

// don't forget to make BinaryTree<T>::head and size public in binary_tree.h
template<class T>
static void print_node(std::vector<char*>& prefix, typename BinaryTree<T>::Node* node)
{
    if (node->left == nullptr && node->right == nullptr)
    {
        return;
    }

    std::vector<typename BinaryTree<T>::Node*> children = std::vector<typename BinaryTree<T>::Node*>();
    children.push_back(node->left);
    children.push_back(node->right);

    for (auto it = children.begin(); it != children.end(); it++)
    {
        for (int i = 0; i < prefix.size(); i++)
        {
            std::cout << prefix[i];
        }

        std::cout << "+---";

        if (*it == nullptr)
        {
            std::cout << "NULL" << std::endl;
        }
        else
        {
            std::cout << "(" << (*it)->key << ", " << (*it)->value << ")" << std::endl;

            prefix.push_back((it == children.begin()) ? (char*)"|   " : (char*)"    ");
            print_node<T>(prefix, (*it));
            prefix.pop_back();
        }
    }
}

template<class T>
void print_tree(const BinaryTree<T>& tree)
{
    if (tree.size == 0)
    {
        return;
    }

    std::vector<char*> prefix = std::vector<char*>();
    std::cout << "(" << tree.head->key << ", " << tree.head->value << ")" << std::endl;
    print_node<T>(prefix, tree.head);
}

static void assert(bool condition)
{
    if (!condition)
        throw std::logic_error(":(");
}

int main()
{
    BinaryTree<int> tree = BinaryTree<int>();

    tree.insert(5, 5);
    tree.insert(1, 1);
    tree.insert(2, 2);
    tree.insert(0, 0);
    tree.insert(7, 7);
    tree.insert(8, 8);
    tree.insert(9, 9);
    tree.insert(6, 6);

    print_tree(tree);

    std::cout << "Count: " << tree.size << std::endl;

    tree.remove(5);
    print_tree(tree);

    std::cout << "Count after remote: " << tree.size << std::endl;


    assert(tree.find(1) == 1);
    assert(tree.find(2) == 2);
    assert(tree.find(0) == 0);
    assert(tree.find(7) == 7);
    assert(tree.find(8) == 8);
    assert(tree.find(9) == 9);
    assert(tree.find(6) == 6);

    std::cout << "Traverse: " << std::endl;

    tree.Traverse([](int x)
                  {
                      std::cout << x << std::endl;
                      return -x;
                  });

    print_tree(tree);

    tree.remove(8);
    print_tree(tree);

    tree.remove(1);
    print_tree(tree);
}