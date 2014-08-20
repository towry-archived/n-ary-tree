#pragma once

#include <stdexcept>
#include <algorithm>
#include <cassert>

// traverse order
typedef enum {
    TREE_IN_ORDER,
    TREE_POST_ORDER,
    TREE_PRE_ORDER
} TraverseType;

// tree node
template <typename T>
class TreeNode {
 public:
     TreeNode();
     TreeNode(const T&);
     ~TreeNode();

     // parent
     TreeNode<T> *parent;
     // first, last child
     TreeNode<T> *first_child, *last_child;
     // brothers
     TreeNode<T> *prev_sibling, *next_sibling;

     // the data
     T data;
};

template <typename T>
TreeNode<T>::TreeNode() 
    : parent(0), first_child(0), 
    last_child(0), prev_sibling(0), 
    next_sibling(0) {}

template <typename T>
TreeNode<T>::TreeNode(const T& v) 
    : parent(0), first_child(0),
    last_child(0), prev_sibling(0),
    next_sibling(0), data(v) {
}

// tree
template <typename T, class tree_alloc = std::allocator<TreeNode<T> > >
class Tree {
 private:
    typedef TreeNode<T> _treenode;

 public:
    Tree();
    ~Tree();

    // ops
    _treenode* insert(_treenode*, int, _treenode*);
    _treenode* search(const T&);
    void remove(const T& data);

 private:
    _treenode *root;
    _treenode *last;
    tree_alloc _alloc;
};

// constructor
template <typename T, class tree_alloc>
Tree<T, tree_alloc>::Tree() {
    root = _alloc.allocate(1,0);
    root->parent = 0;
    root->first_child = 0;
    root->last_child = 0;
    root->prev_sibling = 0;
    root->next_sibling = 0;
}

// destructor
template <typename T, class tree_alloc>
Tree<T, tree_alloc>::~Tree() {
    _alloc.destory(root);
    _alloc.deallocate(root,1);
}

// insert a node under parent at position
template <typename T, class tree_alloc>
TreeNode<T>*
Tree<T, tree_alloc>::insert(TreeNode<T>* parent, int position, TreeNode<T>* node) {
    _treenode* tmp;
    int i = 0;

    assert(node != NULL);
    if (parent == NULL) {
        parent = root;
    }
    
    node->parent = parent;
    if (position == -1) {
        tmp = parent;
        while (tmp->next_sibling != 0) {
            tmp = tmp->next_sibling;
        }
        tmp->next_sibling = node;
        return node;
    } else {
        // get nth child of parent
        tmp = parent->first_child;
        if (tmp == 0) {
            parent->first_child = node;

            return node;
        }

        do {
            if (i == position) {
                node->prev_sibling = tmp->prev_sibling;
                tmp->prev_sibling = node;
                node->next_sibling = tmp;
                return node;
            }
            if (tmp->next_sibling == 0) {
                // if the position is greater,
                // just append the node
                tmp->next_sibling = node;
                node->prev_sibling = tmp;
                return node;
            }

            tmp = tmp->next_sibling;
            i++;
        } while (tmp != 0);
    }
}

// search
template <typename T, class tree_alloc>
TreeNode<T>*
Tree<T, tree_alloc>::search(const T& data) {
    TreeNode<T> *tmp;
    tmp = traverse(root, TREE_PRE_ORDER, -1, data);

    return tmp;
}

template <typename T>
TreeNode<T>*
traverse_in_order(TreeNode<T>* root, TraverseType order,
        int max_depth, const T& data);

template <typename T>
TreeNode<T>*
traverse_pre_order(TreeNode<T>* root, TraverseType order,
        int max_depth, const T& data);

template <typename T>
TreeNode<T>*
traverse_post_order(TreeNode<T>* root, TraverseType order,
        int max_depth, const T& data);

// traverse
template <typename T>
TreeNode<T>*
traverse(TreeNode<T>* root, TraverseType order,
        int max_depth, const T& data) {
    TreeNode<T>* node;
    if (order == 0 || order == TREE_PRE_ORDER) {
        node = traverse_pre_order(root, order, max_depth, data);
    } else if (order == TREE_IN_ORDER) {
        node = traverse_in_order(root, order, max_depth, data);
    } else {
        node = traverse_post_order(root, order, max_depth, data);
    }

    return node;
}

// pre order
template <typename T>
TreeNode<T>*
traverse_pre_order(TreeNode<T>* root, TraverseType order,
        int max_depth, const T& data) {
    TreeNode<T> *tmp;

    // visite node
    if (root == NULL) {
        return root;
    } else if (root->data == data) {
        return root;
    }

    // visite left
    tmp = traverse_pre_order(root->first_child, order, max_depth-1, data);
    if (tmp != NULL) {
        return tmp;
    }

    tmp = root->first_child;

    // visite right
    tmp = traverse_pre_order(tmp->next_sibling, order, max_depth-1, data);

    return tmp;
}


// in order
template <typename T>
TreeNode<T>*
traverse_in_order(TreeNode<T>* root, TraverseType order,
        int max_depth, const T& data) {
}

// post order
template <typename T>
TreeNode<T>*
traverse_post_order(TreeNode<T>* root, TraverseType order,
        int max_depth, const T& data) {
}

