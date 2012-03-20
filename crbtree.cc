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

void rotate_left(node* p) {
    node* g = p->getParent();
    node* n = p->getRight();
    g->setLeft(n);
    p->setRight(n->getLeft());
    n->setLeft(p);
}

void rotate_right(node* p) {}

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
    // We have a parent
    insert_case2(n);
}

void insert_case2(node* n) {
    //If parent is black, all good.
    if (n->getParent()->getColor() == BLACK ) {
        return;
    }
    // Parent is red
    insert_case3(n);
}

void insert_case3(node* n) {
    // If uncle is red repaint it and parent black and apply case 1 to 
    // grandparent
    node* uncle = n->getUncle();
    if ( ( uncle != 0 ) && ( uncle->getColor() == RED ) ) {
        n->getParent()->setColor(BLACK);
        uncle->setColor(BLACK);
        node* grandparent = n->getGrandparent();
        grandparent->setColor(RED);
        insert_case1(grandparent);
    }
    else {
        // Parent is red and uncle is black
        insert_case4(n);
    }
}

void insert_case4(node* n) {
    // Current node is the right child of its parent, and the parent in turn
    // is the left child of its parent.
    // -or-
    // Current node is the left child of its parent, and the parent in turn
    // is the right child of its parent.
    node* grandparent = n->getGrandparent();
    node* parent = n->getParent();
    if ((n == parent->getRight()) && (parent == grandparent->getLeft())) {
    //     cout << "Rotating left." << endl;
    //     cout << "n <" <<n<<"> value="<<n->getValue()<<endl;
    //     cout << "parent <" <<parent<<"> value="<<parent->getValue()<<endl;
    //     cout << "left <" << n->getLeft() << "> value="<<n->getLeft()->getValue()<<endl;
        rotate_left(parent);
        cout << "Done rotating." << endl;
        cout << "n      <" <<n<<"> value="<<n->getValue()<<endl;
        cout << "left   <" << n->getLeft() << "> value="<<n->getLeft()->getValue()<<endl;
        //insert_case5(n->getLeft());
    }
    else if ((n == parent->getLeft()) && (parent == grandparent->getRight())) {
        rotate_right(parent);
        //insert_case5(n->getRight());
    }
    // Current node is left child and parent is left child.
    // -or-
    // Current node is right child and parent is right child.
}

void insert_case5(node* n) {}

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

    node node18(18);
    insert(&node18, &root);
    // assert(node10.getColor() == RED);
    // assert(node10.getLeft() == &leaf);
    // assert(node10.getRight() == &leaf);
    // assert(node25.getColor() == BLACK);
    // assert(node25.getLeft() == &node18);
    // assert(node25.getRight() == &leaf);
    // assert(root.getColor() == BLACK);
    // assert(root.getLeft() == &node25);
    // assert(root.getRight() == &node100);
    // assert(node100.getColor() == BLACK);
    // assert(node100.getLeft() == &leaf);
    // assert(node100.getRight() == &leaf);
    cout << "About to assert" << endl;
    cout << "n      <" <<&node18<<"> value="<<(&node18)->getValue()<<endl;
    cout << "left   <" << (&node18)->getLeft() << "> value="<<(&node18)->getLeft()->getValue()<<endl;
    assert(node18.getColor() == RED);
    assert(node18.getLeft() == &node10);
    assert(node18.getRight() == &leaf);



    return 0;
}

