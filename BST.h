#pragma once
#include <iostream>
#include <memory>

template <typename T> class BST
{
  private:
    template <typename T> struct Node
    {
        Node(T value) : value(value)
        {
        }
        ~Node()
        {
        }
        T value;
        std::unique_ptr<Node> left_ = nullptr;
        std::unique_ptr<Node> right_ = nullptr;
    };

    std::unique_ptr<Node<T>> root_ = nullptr;

    void print(std::unique_ptr<Node<T>> &currentNode)
    {
        if (currentNode != nullptr)
        {
            std::cout << currentNode->value << '\n';
            print(currentNode->right_);
            print(currentNode->left_);
        }
    }

  public:
    BST() = default;
    void insert(T value)
    {
        std::unique_ptr<Node<T>> *currentNode = &root_;

        while (*currentNode != nullptr)
        {
            if (value > (*currentNode)->value)
                currentNode = &(*currentNode)->right_;
            else if (value < (*currentNode)->value)
                currentNode = &(*currentNode)->left_;
            else
                return;
        }
        *currentNode = std::make_unique<Node<T>>(value);
    }

    void print()
    {
        print(root_);
    }
};
