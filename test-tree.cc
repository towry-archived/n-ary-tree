
#define _HAS_EXCEPTIONS 0

#include "tree.hh"
#include <iostream>
#include <cassert>

using std::cout;

int 
main() {
    Tree<int>* tree = new Tree<int>();
    TreeNode<int>* tmp;
    TreeNode<int>* prev;

    tmp = new TreeNode<int>(2);
    prev = tree->insert(NULL, -1, tmp);

    tmp = new TreeNode<int>(5);
    prev = tree->insert(prev, -1, tmp);

    tmp = tree->search(2);
    assert(tmp->data && tmp->data == 2);

    tmp = tree->search(4);
    assert(tmp->data && tmp->data == 4);

    return(0);
}

