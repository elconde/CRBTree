#include <iostream>
using namespace std;


class node {
    public:
        int getColor();
};

enum COLOR { RED, BLACK };

int node::getColor() {
    return BLACK;
}

int main() {
    node myNode;
    //printf("myNode.getColor()=%s\n",myNode.getColor());
    if ( myNode.getColor() == BLACK) {
        printf("BLACK\n"); 
    } else if (myNode.getColor() == RED) {
        printf("RED\n");
    }
    return 0;
}
