#include <iostream>
#include <vector>
#include <cassert>
#include "logger.cpp"
using namespace std;

#define MIN_SIZE 4
#define MAX_SIZE 1024

Logger logger("logs.txt");


void print_array(int* list, int size) {
    cout << '[';
    for(int i=0; i < size; ++i) {
        cout << list[i];
        if(i == size-1) cout << ']';
        else cout << ", ";
    }
}


struct Range {
    int left;
    int right;
};

/* ----- BINARY SEARCH -----
    Returns the range where the value can be found
    - If the value is in the list, left and right are the same
    - If the value is NOT in the list, left is bigger than right        */
Range binary_search(int* list, int l, int r, int value) {
    if(r < l) return {l, r};
    int m = l + (r-l)/2;
    if(list[m] == value) return {m, m};
    if(list[m] > value) return binary_search(list, l, m-1, value);
    else return binary_search(list, m+1, r, value);
}



class BTree {

    struct Node {
        int elements;
        int elems_inserted = 0;
        Node** children = NULL;
        Node* parent = NULL;

        Node(int node_size) {
        }
    };

    int node_size;
    Node* root = NULL;

    Node create_node() {
        Node n;
        n.elements = new int[node_size+1];
        n.children = new Node*[node_size+1];
        for(int i=0; i < node_size+1; ++i) children[i] = NULL;
        n.parent = NULL;
        return n;
    }

    Node& find_node(int e) {
        Node *current, *next;
        next = root;
        while(next != NULL) {
            current = next;
            int* elements = current->elements;
            Range r = binary_search(elements, 0, current->elems_inserted-1, e);
            if(r.left == r.right) return *current;
            next = current->children[r.left];
        }
        return *current;
    }

    int insert_in_node(Node& n, int e) {
        
    }

    void balance(Node& n) {
        if(n.parent == NULL) n.parent = new Node(node_size);

        int m = n.elems_inserted / 2;
        Node left(node_size);
        for(int i=0; i < m; ++i) left.elements[i] = n.elements[i];
        left.elems_inserted = m-1;

        Node right(node_size);
        for(int i=m+1; i < n.elems_inserted; ++i) right.elements[i] = n.elements[i];
        right.elems_inserted = n.elems_inserted - m;

        assert(false && "TODO: balance function not implemented.");
    }

public:
    
    BTree(int node_size=MIN_SIZE) {
        logger.log(DEBUG, "Start creating the BTree object...");
        
        if(node_size > MAX_SIZE) node_size = MAX_SIZE;
        if(node_size < MIN_SIZE) node_size = MIN_SIZE;
        root = new Node(node_size);
        this->node_size = node_size;
        
        logger.log(DEBUG, "BTree object created!");
    }

    void insert(int e) {
        Node node = find_node(e);
        Range r = binary_search(node.elements, 0, node.elems_inserted, e);
        if(r.left == r.right) {
            logger.log(ERROR, to_string(e) + " is already in the BTree. You can only have unique values in the BTree.");
            return;
        }

        node.elements[node.elems_inserted++] = e;
        int aux;
        for(int i = node.elems_inserted-1; i >= 0 && node.elements[i] < node.elements[i-1]; --i) {
            aux = node.elements[i-1];
            node.elements[i-1] = node.elements[i];
            node.elements[i] = aux;
        }
        
        cout << "Result array: ";
        print_array(node.elements, node.elems_inserted);
        cout << endl;
        if(node.elems_inserted > node_size) balance(node);
    }

};


int main() {
    BTree test;
    int x;
    while(cin >> x) {
        test.insert(x);
    }
    return 0;
}