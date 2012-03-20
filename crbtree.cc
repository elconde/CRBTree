#include <iostream>
#include "crbtree.h"
using namespace std;

node::node(int v, COLOR c=NONE) {
    value = v;
    parent = 0;
    left = 0;
    right = 0;
    color = c;
}

bool node::operator==(const node &anotherNode) {
    return anotherNode.value==value;
}

COLOR node::getColor() {
    return color;
}

int node::getValue() {
    return value;
}


node* node::getGrandparent() {
    if (parent != 0 ) { return parent->parent; }
    return 0;
}

void node::setColor(COLOR c) {
    color = c;
}

node* node::getLeft() {
    return left;
}

node* node::getRight() {
    return right;
}

node* node::getUncle() {
    node* g = getGrandparent();
    if ( g == 0 ) { return 0 ; }
    if ( parent == g->getLeft() ) { return g->getRight();}
    return g->getLeft();
}

void node::setLeft(node* n) {
    left = n;
    n->parent = this;
    return;
}

void node::setRight(node* n) {
    right = n;
    n->parent = this;
    return;
}

node* node::getParent() {
    return parent;
}

void insert(node* n, node* root=0) {
    if ( root != 0 ) {
        int nValue = n->getValue();
        int rValue = root->getValue();
        if ( nValue < rValue) {
            node* left = root->getLeft();
            if ( left == 0 || *left == leaf) { 
                root->setLeft(n); 
            }
            else { insert(n, left); } 
        }
        else if ( nValue > rValue) {
            node* right = root->getRight();
            if ( right == 0 || *right == leaf) { 
                root->setRight(n);
            }
            else { insert(n, right); }
        }
        else {
            // No duplicates allowed
            return; 
        }
    }
    n->setColor(RED);
    // Add the black leaves
    n->setRight(&leaf);
    n->setLeft(&leaf);
    // Now perform the Red-Black operations
    insert_case1(n);
}

void insert_case1(node* n) {
    // If no parents then color it black
    if ( n->getParent() == 0 ) {
        n->setColor(BLACK);
        return;
    }
    insert_case2(n);
}

void insert_case2(node* n) {
    //Parent is black, all good.
    if (n->getParent()->getColor() == BLACK ) {
        return;
    }
    insert_case3(n);
}

void insert_case3(node* n) {
    // Parent and uncle are both red
    node* uncle = n->getUncle();
    if ( ( uncle != 0 ) && ( uncle->getColor() == RED ) ) {
        n->getParent()->setColor(BLACK);
        uncle->setColor(BLACK);
        node* grandparent = n->getGrandparent();
        grandparent->setColor(RED);
        insert_case1(grandparent);
    }
    else {
        insert_case4(n);
    }
}

void insert_case4(node* n) {}

const char* node::getColorString() {
    switch (color) {
        case RED:
            return "RED";
            break;
        case BLACK:
            return "BLACK";
            break;
        case NONE:
            return "NONE";
            break;
        default:
            return "WTF?";
    }

}

int main() {
    node root(50);
    assert(root.getColor() == NONE);
    insert(&root);
    assert(root.getColor() == BLACK);

    node node100(100);
    assert (node100.getColor() == NONE);
    insert(&node100,&root);
    assert(node100.getColor() == RED);
    assert(node100.getLeft() == &leaf);
    assert(node100.getRight() == &leaf);
    assert(root.getLeft() == &leaf);
    assert(root.getRight() == &node100);

    node node25(25);
    insert(&node25, &root);
    assert(node25.getColor() == RED);
    assert(node25.getLeft() == &leaf);
    assert(node25.getRight() == &leaf);
    assert(root.getLeft() == &node25);
    assert(root.getRight() == &node100);

    node node10(10);
    insert(&node10, &root);
    assert(node10.getColor() == RED);
    assert(node10.getLeft() == &leaf);
    assert(node10.getRight() == &leaf);
    assert(node25.getColor() == BLACK);
    assert(node25.getLeft() == &node10);
    assert(node25.getRight() == &leaf);
    assert(root.getColor() == BLACK);
    assert(root.getLeft() == &node25);
    assert(root.getRight() == &node100);
    assert(node100.getColor() == BLACK);
    assert(node100.getLeft() == &leaf);
    assert(node100.getRight() == &leaf);




    return 0;
}

