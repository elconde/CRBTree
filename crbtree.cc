#include <iostream>
#include "crbtree.h"
using namespace std;

node::node(int v) {
    value = v;
    parent = 0;
    left = 0;
    right = 0;
    color = NONE;
}

COLOR node::getColor() {
    return color;
}

int node::getValue() {
    return value;
}

void node::attach(node* anotherNode) {
    parent = anotherNode;
    if ( value < parent->value ) {
        parent->left = this;
    }
    else { parent->right = this; }
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

int main() {
    node node01(20120319);
    node node02(20120318);
    node02.attach(&node01);

    printf("Node 01 LEFT: %d\n",node01.getLeft()->getValue());

    return 0;
}
