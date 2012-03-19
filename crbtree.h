enum COLOR { RED, BLACK, NONE };

class node {
    COLOR color;
    int value;
    node* parent;
    node* left;
    node* right;
    public:
        COLOR getColor();
        node(int, COLOR);
        int getValue();
        node* grandparent();
        node* uncle();
        void setColor(COLOR);
        node* getLeft();
        node* getRight();
        void setLeft(node*);
        void setRight(node*);
        const char* getColorString();
};

void insert(node* n, node* root);
