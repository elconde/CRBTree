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
        node* getParent();
        void setParent(node*);
        bool operator==(const node&);
};

node leaf(0, BLACK);

// http://en.wikipedia.org/w/index.php?title=Red%E2%80%93black_tree&oldid=482155076#Operations
void insert(node* n, node* root);
void insert_case1(node* n);
void insert_case2(node* n);
void insert_case3(node* n);

