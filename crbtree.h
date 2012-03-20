enum COLOR { RED, BLACK, NONE };

class node {
    COLOR color;
    int value;
    node* parent;
    node* left;
    node* right;
    public:
    //TODO: Better organize these
        node(int, COLOR);

        COLOR getColor();
        void setColor(COLOR);
        const char* getColorString();

        int getValue();

        node* getGrandparent();

        node* getUncle();

        node* getLeft();
        void setLeft(node*);

        node* getRight();
        void setRight(node*);

        node* getParent();

        bool operator==(const node&);
};

node leaf(0, BLACK);

// http://en.wikipedia.org/w/index.php?title=Red%E2%80%93black_tree&oldid=482155076#Operations
void insert(node* n, node* root);
void insert_case1(node* n);
void insert_case2(node* n);
void insert_case3(node* n);
void insert_case4(node* n);
void insert_case5(node* n);

void rotate_left(node*);
void rotate_right(node*);

int treeLevel = -1; 
