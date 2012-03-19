enum COLOR { RED, BLACK, NONE };

class node {
    COLOR color;
    int value;
    node* parent;
    node* left;
    node* right;
    public:
        COLOR getColor();
        node(int);
        int getValue();
        void attach(node*);
        node* grandparent();
        void setColor(COLOR);
        node* getLeft();
        node* getRight();
};


