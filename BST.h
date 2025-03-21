#pragma once
#include <iostream>
#include <memory>
#include <queue>
#include <vector>

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

    void insertNode(std::unique_ptr<Node<T>> &node)
    {
        if (node != nullptr)
        {
            insert(node->value);
            insertNode(node->right_);
            insertNode(node->left_);
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

    void erase(T value)
    {
        std::unique_ptr<Node<T>> *currentNode = &root_;

        while (*currentNode != nullptr)
        {
            if (value > (*currentNode)->value)
                currentNode = &(*currentNode)->right_;
            else if (value < (*currentNode)->value)
                currentNode = &(*currentNode)->left_;
            else
                break;
        }
        if (*currentNode != nullptr)
        {
            auto right = std::move((*currentNode)->right_);
            auto left = std::move((*currentNode)->left_);
            currentNode->release();
            insertNode(right);
            insertNode(left);
            root_ = balanceBST();
        }
    }

    void print()
    {
        print(root_);
        std::cout << '\n';
    }

    void storeInorder(std::unique_ptr<Node<T>> &root, std::vector<int> &nodes)
    {
        if (root == nullptr)
            return;

        storeInorder(root->left_, nodes);

        nodes.push_back(root->value);

        storeInorder(root->right_, nodes);
    }

    std::unique_ptr<Node<T>> buildBalancedTree(std::vector<T> &nodes, int start, int end)
    {

        if (start > end)
            return nullptr;

        int mid = (start + end) / 2;
        std::unique_ptr<Node<T>> root = std::make_unique<Node<T>>(nodes[mid]);

        root->left_ = buildBalancedTree(nodes, start, mid - 1);
        root->right_ = buildBalancedTree(nodes, mid + 1, end);

        return root;
    }

    std::unique_ptr<Node<T>> balanceBST()
    {
        std::vector<T> nodes;

        storeInorder(root_, nodes);

        return buildBalancedTree(nodes, 0, static_cast<int>(nodes.size() - 1));
    }
};
