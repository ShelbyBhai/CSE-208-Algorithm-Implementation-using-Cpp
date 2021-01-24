#include <bits/stdc++.h>

#define NULL_VALUE -666

using namespace std;

class Node
{
public:
    Node *parent, *child, *sibling;
    int key, degree;

    Node() { parent = child = sibling = NULL; key = NULL_VALUE; degree = 0;  }
    Node(int tempKey) { parent = child = sibling = NULL; key = tempKey; degree = 0;  }

};

class BinomialHeap
{
public:
    Node *head;
    int length;

    BinomialHeap() { head = NULL;  length = 0; }

    void unionHeap(BinomialHeap *H2);
    Node* findMin();
    Node* extractMin();
    void insert(int key);
    void print();

};

void link(Node *y, Node *z) {
    y->parent = z;
    y->sibling = z->child;
    z->child = y;
    z->degree = z->degree + 1;
}

void BinomialHeap::unionHeap(BinomialHeap *H2) {
    Node *unitedHead=NULL, *newHead = NULL;
    Node *head1 = this->head, *head2 = H2->head;
    while(head1 && head2) {
        if(head1->degree <= head2->degree) {
            if(newHead) {
                newHead->sibling = head1;
                newHead = newHead->sibling;
            } else {
                unitedHead = head1;
                newHead = head1;
            }
            head1 = head1->sibling;
        } else {
            if(newHead) {
                newHead->sibling = head2;
                newHead = newHead->sibling;
            } else {
                unitedHead = head2;
                newHead = head2;
            }
            head2 = head2->sibling;
        }
    }
    while(head1) {
        if(newHead) {
            newHead->sibling = head1;
            newHead = newHead->sibling;
        } else {
            unitedHead = head1;
            newHead = head1;
        }
        head1 = head1->sibling;
    }
    while(head2) {
        if(newHead) {
            newHead->sibling = head2;
            newHead = newHead->sibling;
        } else {
            unitedHead = head2;
            newHead = head2;
        }
        head2 = head2->sibling;
    }

    int newLength = this->length + H2->length;
    if(!newHead) return;

    Node *prev=NULL, *cur=unitedHead, *next=cur->sibling;
    while (next) {
        if((cur->degree != next->degree) || ((next->sibling != NULL) && (next->sibling->degree == cur->degree))) {
            prev = cur;
            cur = next;
        } else if( cur->key <= next->key ) {
            cur->sibling = next->sibling;
            link(next, cur);
        } else {
            if(prev==NULL) unitedHead = next;
            else prev->sibling = next;
            link(cur, next);
            cur = next;
        }
        next = cur->sibling;
    }
    this->head = unitedHead;
    this->length = newLength;
    H2->length = 0;
    H2->head = NULL;
    delete(H2);
}

Node *BinomialHeap::findMin() {
    if(length>0) {
        Node *temp = head, *min = head;
        while (temp) {
            if(temp->key < head->key) min = temp;
            temp = temp->sibling;
        }
        return min;
    } else return NULL;
}

Node *BinomialHeap::extractMin() {
    if(length>0) {
        Node *temp = head, *min = head, *p_temp = NULL, *p_min = NULL;
        while (temp) {
            if(temp->key < head->key) {
                min = temp;
                p_min = p_temp;
            }
            p_temp = temp;
            temp = temp->sibling;
        }

        if(p_min != NULL) p_min->sibling = min->sibling;
        else head = head->sibling;
        min->sibling = NULL;

        Node *already_broken = min->child;
        min->child = NULL;
        Node *prev = NULL, *cur = already_broken, *next=NULL;

        while(cur) {

            next = cur->sibling;
            cur->sibling = prev;
            prev = cur;
            cur = next;
        }
        already_broken = prev;

        BinomialHeap *tempH = new BinomialHeap();
        tempH->head = already_broken;

        this->unionHeap(tempH);
        this->length = this->length - 1;

        delete(tempH);
        return min;

    } else return NULL;
}

void BinomialHeap::insert(int key) {
    BinomialHeap *tempH = new BinomialHeap();
    Node *newNode = new Node(key);
    tempH->head = newNode;
    tempH->length = 1;
    this->unionHeap(tempH);
}

void BinomialHeap::print() {
    cout << "Heap length: " << length << endl;
}

int main(void)
{
    BinomialHeap bh;

    bh.insert(1);
    bh.insert(2);
    bh.insert(3);
    bh.insert(4);
    bh.insert(9);
    bh.insert(10);
    bh.insert(11);
    bh.insert(5);
    bh.insert(6);
    bh.insert(7);
    bh.insert(8);


    cout << bh.length << endl;

    cout << bh.findMin()->key << endl;

    while(bh.length > 0) {

        cout << bh.extractMin()->key << endl;
    }



    return 0;
}
