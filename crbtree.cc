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

bool node::isRoot() {
    return  parent == 0 ;
}

bool node::operator==(const node &anotherNode) {
    // TODO: Need unit test for this function
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

void node::detach() {
    // Make this node a root node
    parent = 0;
}

void rotate_left(node* p) {
    node* g = p->getParent();
    node* n = p->getRight();
    if ( g == 0 ) {
        n->detach();
    }
    else if ( g->getLeft() == p ) {
        g->setLeft(n);
    }
    else {
        g->setRight(n);
    }
    p->setRight(n->getLeft());
    n->setLeft(p);
}

void rotate_right(node* p) { // TODO: merge with rotate_left
    node* g = p->getParent();
    node* n = p->getLeft();
    if ( g == 0 ) {
        n->detach();
    }
    else if ( g->getLeft() == p ) {
        g->setLeft(n);
    }
    else {
        g->setRight(n);
    }
    p->setLeft(n->getRight());
    n->setRight(p);
}

void BTreeInsert(node* n, node* root) {
    if ( root == 0 ) { return; }
    int nValue = n->getValue();
    int rValue = root->getValue();
    if ( nValue < rValue) {
        node* left = root->getLeft();
        if ( left == 0 || *left == leaf) { 
            root->setLeft(n); 
        }
        else { 
            BTreeInsert(n, left); 
        } 
    }
    else if ( nValue > rValue) {
        node* right = root->getRight();
        if ( right == 0 || *right == leaf) { 
            root->setRight(n);
        }
        else { 
            BTreeInsert(n, right); 
        }
    }
    else {
        // No duplicates allowed
        return; 
    }
}

void insert(node* n, node* root=0) {
    n->setColor(RED);
    n->setRight(&leaf);
    n->setLeft(&leaf);
    BTreeInsert(n, root);
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
        rotate_left(parent);
        insert_case5(n->getLeft());
    }
    else if ((n == parent->getLeft()) && (parent == grandparent->getRight())) {
        rotate_right(parent);
        insert_case5(n->getRight());
    }
    else {
        // Current node is left child and parent is left child.
        // -or-
        // Current node is right child and parent is right child.
        insert_case5(n);
    }
}


void insert_case5(node* n) {
    node* grandparent = n->getGrandparent();
    node* parent = n->getParent();
    if (n == parent->getLeft()) {
        rotate_right(grandparent);
    }
    else {
        rotate_left(grandparent);
    }
    parent->setColor(BLACK);
    grandparent->setColor(RED);
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
    node root(50);
    assert(root.getColor() == NONE);
    insert(&root);
    assert(root.getColor() == BLACK);

    node node100(100);
    insert(&node100,&root);
    assert(node100.getColor() == RED);
    assert(node100.getLeft() == &leaf);
    assert(node100.getRight() == &leaf);
    assert(root.getColor() == BLACK);
    assert(root.getLeft() == &leaf);
    assert(root.getRight() == &node100);

    node node25(25);
    insert(&node25, &root);
    assert(node25.getColor() == RED);
    assert(node25.getLeft() == &leaf);
    assert(node25.getRight() == &leaf);
    assert(node100.getColor() == RED);
    assert(node100.getLeft() == &leaf);
    assert(node100.getRight() == &leaf);
    assert(root.getColor() == BLACK);
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
    assert(node100.getColor() == BLACK);
    assert(node100.getLeft() == &leaf);
    assert(node100.getRight() == &leaf);
    assert(root.getColor() == BLACK);
    assert(root.getLeft() == &node25);
    assert(root.getRight() == &node100);


    node node18(18);
    insert(&node18, &root);
    assert(node18.getColor() == BLACK);
    assert(node18.getLeft() == &node10);
    assert(node18.getRight() == &node25);
    assert(node10.getColor() == RED);
    assert(node10.getLeft() == &leaf);
    assert(node10.getRight() == &leaf);
    assert(node25.getColor() == RED);
    assert(node25.getLeft() == &leaf);
    assert(node25.getRight() == &leaf);
    assert(node100.getColor() == BLACK);
    assert(node100.getLeft() == &leaf);
    assert(node100.getRight() == &leaf);
    assert(root.getColor() == BLACK);
    assert(root.getLeft() == &node18);
    assert(root.getRight() == &node100);

    root = node(50);
    insert(&root);

    node100 = node(100);
    insert(&node100,&root);
    assert(node100.getColor() == RED);
    assert(node100.getLeft() == &leaf);
    assert(node100.getRight() == &leaf);
    assert(root.getColor() == BLACK);
    assert(root.getLeft() == &leaf);
    assert(root.getRight() == &node100);

    node25 = node(25);
    insert(&node25, &root);
    assert(node25.getColor() == RED);
    assert(node25.getLeft() == &leaf);
    assert(node25.getRight() == &leaf);
    assert(node100.getColor() == RED);
    assert(node100.getLeft() == &leaf);
    assert(node100.getRight() == &leaf);
    assert(root.getColor() == BLACK);
    assert(root.getLeft() == &node25);
    assert(root.getRight() == &node100);

    node node150 = node(150);
    insert(&node150, &root);
    assert(node150.getColor() == RED);
    assert(node150.getLeft() == &leaf);
    assert(node150.getRight() == &leaf);
    assert(node25.getColor() == BLACK);
    assert(node25.getLeft() == &leaf);
    assert(node25.getRight() == &leaf);
    assert(node100.getColor() == BLACK);
    assert(node100.getLeft() == &leaf);
    assert(node100.getRight() == &node150);
    assert(root.getColor() == BLACK);
    assert(root.getLeft() == &node25);
    assert(root.getRight() == &node100);

    node node125 = node(125);
    insert(&node125, &root);
    assert(node125.getColor() == BLACK);
    assert(node125.getLeft() == &node100);
    assert(node125.getRight() == &node150);
    assert(node150.getColor() == RED);
    assert(node150.getLeft() == &leaf);
    assert(node150.getRight() == &leaf);
    assert(node25.getColor() == BLACK);
    assert(node25.getLeft() == &leaf);
    assert(node25.getRight() == &leaf);
    assert(node100.getColor() == RED);
    assert(node100.getLeft() == &leaf);
    assert(node100.getRight() == &leaf);
    assert(root.getColor() == BLACK);
    assert(root.getLeft() == &node25);
    assert(root.getRight() == &node125);

    node nnode25(25);
    insert(&nnode25);
    assert(nnode25.getColor()==BLACK);
    assert(nnode25.getLeft() == &leaf );
    assert(nnode25.getRight() == &leaf );
    node nnode53(53);
    insert(&nnode53,&nnode25);
    assert(nnode25.getColor()==BLACK);
    assert(nnode25.getLeft() == &leaf );
    assert(nnode25.getRight() == &nnode53 );
    assert(nnode53.getColor()==RED);
    assert(nnode53.getLeft() == &leaf );
    assert(nnode53.getRight() == &leaf );
    node nnode98(98);
    insert(&nnode98,&nnode25);
    assert(nnode25.getColor()==RED);
    assert(nnode25.getLeft() == &leaf );
    assert(nnode25.getRight() == &leaf );
    assert(nnode53.getColor()==BLACK);
    assert(nnode53.getLeft() == &nnode25 );
    assert(nnode53.getRight() == &nnode98 );
    assert(nnode98.getColor()==RED);
    assert(nnode98.getLeft() == &leaf );
    assert(nnode98.getRight() == &leaf );
    node nnode36(36);
    insert(&nnode36,&nnode25);
    assert(nnode25.getColor()==BLACK);
    assert(nnode25.getLeft() == &leaf );
    assert(nnode25.getRight() == &nnode36 );
    assert(nnode53.getColor()==BLACK);
    assert(nnode53.getLeft() == &nnode25 );
    assert(nnode53.getRight() == &nnode98 );
    assert(nnode98.getColor()==BLACK);
    assert(nnode98.getLeft() == &leaf );
    assert(nnode98.getRight() == &leaf );
    assert(nnode36.getColor()==RED);
    assert(nnode36.getLeft() == &leaf );
    assert(nnode36.getRight() == &leaf );
    node nnode97(97);
    insert(&nnode97,&nnode25);
    assert(nnode25.getColor()==BLACK);
    assert(nnode25.getLeft() == &leaf );
    assert(nnode25.getRight() == &nnode36 );
    assert(nnode53.getColor()==BLACK);
    assert(nnode53.getLeft() == &nnode25 );
    assert(nnode53.getRight() == &nnode98 );
    assert(nnode98.getColor()==BLACK);
    assert(nnode98.getLeft() == &nnode97 );
    assert(nnode98.getRight() == &leaf );
    assert(nnode36.getColor()==RED);
    assert(nnode36.getLeft() == &leaf );
    assert(nnode36.getRight() == &leaf );
    assert(nnode97.getColor()==RED);
    assert(nnode97.getLeft() == &leaf );
    assert(nnode97.getRight() == &leaf );






    // node node97(97);
    // insert(&node97,&rootA);
    // assert(node53.getParent() == 0 );
    // node node43(43);
    // insert(&node43,&rootA);
    // assert(node53.getParent() == 0 );
    // node node32(32);
    // insert(&node32,&rootA);
    // assert(node53.getParent() == 0 );
    // node node52(52);
    // insert(&node52,&rootA);
    // assert(node53.getParent() == 0 );
    // node node35(35);
    // insert(&node35,&rootA);
    // assert(node53.getParent() == 0 );
    // node node59(59);
    // insert(&node59,&rootA);

    // assert(node53.getParent() == 0 );



}

