#include<bits/stdc++.h>

#define NULL_VALUE -99999

using namespace std;

class Node
{
public:
    int data;
    Node *parent;
    Node *left;
    Node *right;

    Node() { data = NULL_VALUE; parent = left = right = NULL; }
    Node(int _data) { data = _data; parent = left = right = NULL; }
    Node(int _data, Node* _parent, Node* _left, Node* _right) { data = _data; parent = _parent; left = _left; right = _right; }

    void rightRotate();
    void leftRotate();
};

void Node::rightRotate() {
    Node *p_of_x = this->parent;
    Node *l_of_x = this->left;
    if(l_of_x == NULL) return;
    Node *l_of_r = l_of_x->right;

    if(p_of_x != NULL) {
        if(p_of_x->left == this) p_of_x->left = l_of_x;
        else p_of_x->right = l_of_x;
    }
    if(l_of_r) l_of_r->parent = this;
    l_of_x->parent = p_of_x;
    l_of_x->right = this;
    this->parent = l_of_x;
    this->left = l_of_r;
}

void Node::leftRotate() {
    Node *p_of_x = this->parent;
    Node *r_of_x = this->right;
    if(r_of_x == NULL) return;
    Node *l_of_r = r_of_x->left;

    if(p_of_x) {
        if(p_of_x->left == this) p_of_x->left = r_of_x;
        else p_of_x->right = r_of_x;
    }
    if(l_of_r) l_of_r->parent = this;
    r_of_x->parent = p_of_x;
    r_of_x->left = this;
    this->parent = r_of_x;
    this->right = l_of_r;
}

class SplayTree
{
public:
    Node *root;

    SplayTree() { root = NULL; }

    void splay(Node *x);
    Node* searchNode(int x);
    void insertNode(int x);
    void join(Node* leftSubTree, Node* rightSubTree);
    void deleteNode(int x);
    void print();
    void preorderPrint(Node *x);
    void inorderPrint(Node *x);

};

void SplayTree::splay(Node *x) {
    while(x->parent != NULL) {
        Node *P = x->parent;
        Node *G = P->parent;
        if(G == NULL) {
            if(P->left == x) P->rightRotate();
            else P->leftRotate();
        }
        else {
            if(G->left == P) {
                if(P->left == x) {
                    G->rightRotate();
                    P->rightRotate();
                } else {
                    P->leftRotate();
                    G->rightRotate();
                }
            }
            else {
                if(P->right == x) {
                    G->leftRotate();
                    P->leftRotate();
                } else {
                    P->rightRotate();
                    G->leftRotate();
                }
            }
        }
    }
    root = x;
}

Node *SplayTree::searchNode(int x) {
    Node *prev, *temp;
    if(!root) return NULL;
    temp = root;
    while (temp->data != x) {
        prev = temp;
        if(temp->data < x) temp = temp->right;
        else temp = temp->left;
        if(!temp) break;
    }

    if(!temp)
        temp = prev;
    splay(temp);

    if(temp->data == x) return temp;
    else return NULL;
}

void SplayTree::insertNode(int x) {
    if(!root) {
        root = new Node(x);
        return;
    }

    Node *prev=NULL, *temp=root;
    while (temp) {
        prev = temp;
        if(temp->data <= x) temp = temp->right;
        else temp = temp->left;
    }

    Node *newNode = new Node(x,prev,NULL,NULL);
    if(prev->data < x) prev->right = newNode;
    else prev->left = newNode;

    splay(newNode);

}

void SplayTree::join(Node *leftSubTree, Node *rightSubTree) {
    if(!leftSubTree) {
        root = rightSubTree;
        return;
    }
    Node *max_left = leftSubTree;
    while (max_left->right != NULL) {
        max_left = max_left->right;
    }
    splay(max_left);
    max_left->right = rightSubTree;
    if(rightSubTree) rightSubTree->parent = max_left;

    root = max_left;
}

void SplayTree::deleteNode(int x) {
    if(!root) return;
    Node *temp = searchNode(x);
    if(!temp) return;
    Node *left_sub = temp->left;
    Node *right_sub = temp->right;
    if(left_sub) left_sub->parent = NULL;
    if(right_sub) right_sub->parent = NULL;
    temp->left = NULL;
    temp->right = NULL;
    join(left_sub,right_sub);
    delete(temp);
}

void SplayTree::preorderPrint(Node *x) {
    if(!x) return;
    cout << x->data << " ";
    preorderPrint(x->left);
    preorderPrint(x->right);
}

void SplayTree::inorderPrint(Node *x) {
    if(!x) return;
    inorderPrint(x->left);
    cout << x->data << " ";
    inorderPrint(x->right);
}

void SplayTree::print() {
    cout << "\nPreOrder Traversal : " << endl;
    cout << "\t";
    preorderPrint(root);
    cout << "\nInOrder Traversal : " << endl;
    cout << "\t";
    inorderPrint(root);
    cout << endl;
}

int main(void)
{
    SplayTree splayTree;
    /*int choice=0, x;

    while(choice != 5) {
        cout << "\n\n1. print(T) 2. search(x)\n3. insert(x) 4. delete(x) 5.exit\nEnter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:

                break;
            case 2:

                break;
            case 3:

                break;
            case 4:

                break;
        }
    }*/

    splayTree.insertNode(45);
    splayTree.insertNode(5);
    splayTree.insertNode(84);
    splayTree.insertNode(100);
    splayTree.insertNode(7);
    splayTree.print();

    splayTree.searchNode(84);
    splayTree.print();
    splayTree.searchNode(100);
    splayTree.print();
    splayTree.deleteNode(5);
    splayTree.print();
    splayTree.deleteNode(1000);
    splayTree.print();
}
