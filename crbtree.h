class node {

    public:
        enum Color { RED, BLACK };
        node* parent;
        node(Color c );
        void grandparent(node* n);
        Color getColor();
};

