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

COLOR node::getColor() {
    return color;
}

int node::getValue() {
    return value;
}


node* node::grandparent() {
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

node* node::uncle() {
    node* g = grandparent();
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

void node::setParent(node* n) {
    parent = n;
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
            if ( left == 0 ) { 
                root->setLeft(n); 
            }
            else { insert(n, left); } 
        }
        else if ( nValue > rValue) {
            node* right = root->getRight();
            if ( right == 0 ) { 
                root->setRight(n);
            }
            else { insert(n, right); }
        }
    }
    n->setColor(RED);
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
}
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
    node root(51);
    node node28(28);
    node node83(83);
    node node64(64);
    node node90(90);
    insert(&root);
    insert(&node28,&root);
    insert(&node83,&root);
    insert(&node64,&root);
    insert(&node90,&root);

    printf("ROOT value: %d,%s\n", root.getValue(), root.getColorString());
    printf("ROOT left: %d\n", root.getLeft()->getValue());
    printf("ROOT right: %d\n", root.getRight()->getValue());
    printf("83 left: %d\n", node83.getLeft()->getValue());
    printf("83 right: %d\n", node83.getRight()->getValue());


    return 0;
}

