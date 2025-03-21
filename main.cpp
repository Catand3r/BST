#include "BST.h"

int main()
{
    BST<int> bst;
    bst.insert(2);
    bst.insert(3);
    bst.insert(1);
    bst.insert(4);
    bst.insert(2);
    bst.print();
    bst.erase(1);
    bst.print();
}
