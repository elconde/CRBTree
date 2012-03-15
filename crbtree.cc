#include <iostream>
#include "crbtree.h"

using namespace std;

void node::grandparent( node* result) {
    if ( result->parent != 0 ) {
        result = result->parent->parent; 
    }
}

int main() {
    node myNode = new node(RED);
    cout<<"parent=" << myNode.parent << endl;
    cout << "hello" << endl;
}
