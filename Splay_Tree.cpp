#include <iostream>

using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;
    int num;
    int children;

    Node(int x) {
        data = x;
        left = NULL;
        right = NULL;
        num = 1;
        children = 0;
    }
};
class Splay {

public:
    Splay() {
        root = NULL;
    }
    Node* root;
    int count = 0;

    void rotateL(Node*& s) {
        Node* t = s->left;
        s->children = (s->right != NULL ? s->right->children + s->right->num : 0) + (t->right != NULL ? t->right->children + t->right->num : 0);
        t->children = s->children + s->num + (t->left != NULL ? t->left->children + t->left->num : 0);
        s->left = t->right;
        t->right = s;
        s = t;
    }

    void rotateR(Node*& s) {
        Node* t = s->right;
        s->children = (s->left != NULL ? s->left->children + s->left->num : 0) + (t->left != NULL ? t->left->children + t->left->num : 0);
        t->children = s->children + s->num + (t->right != NULL ? t->right->children + t->right->num : 0);
        s->right = t->left;
        t->left = s;
        s = t;
    }

    void dbl_rotateL(Node*& s)
    {
        rotateR(s->left);
        rotateL(s);
    }

    void dbl_rotateR(Node*& s)
    {
        rotateL(s->right);
        rotateR(s);
    }

    void splay(Node*& root, int data) {
        if (root == NULL || root->data == data) {
            return;
        }
        if (root->data > data) {
            if (root->left == NULL) {
                return;
            }

            if (root->left->data > data) {
                splay(root->left->left, data);
                rotateL(root);
            }

            else if (root->left->data < data) {
                splay(root->left->right, data);
                if (root->left->right != NULL)
                    rotateR(root->left);
            }

            if (root->left == NULL)
                return;
            else
                rotateL(root);
        }
        else {
            if (root->right == NULL) {
                return;
            }

            if (root->right->data > data) {

                splay(root->right->left, data);

                if (root->right->left != NULL) {
                    rotateL(root->right);
                }
            }

            else if (root->right->data < data) {
                splay(root->right->right, data);
                rotateR(root);
            }

            if (root->right == NULL)
                return;
            else
                rotateR(root);
        }
    }

    void insert(Node*& root, int data) {
        if (root == NULL) {
            root = new Node(data);
            splay(this->root, data);
            return;
        }

        else if (root->data > data) {
            insert(root->left, data);
        }
        else if (root->data < data) {
            insert(root->right, data);
        }
        else if (root->data == data) {
            root->num++;
            splay(this->root, data);
            return;
        }
    }

    void erase(Node*& root, int data) {
        if (root == NULL)
            return;
        splay(root, data);

        if (data != root->data)
            return;
        if (root->num > 1) {
            root->num--;
            splay(this->root, data);
            return;
        }
        if (root->left == NULL) {
            root = root->right;
        }

        else {
            splay(root->left, data);
            root->left->right = root->right;
            root = root->left;
        }
        return;
    }


    void find(Node* root, int& x) {
        if (root != NULL) {
            if (count > 0) {
                if (x > root->data) {
                    count += (root->left != NULL ? root->left->children + root->left->num : 0) + root->num;
                    find(root->right, x);
                }
                else if (x == root->data) {
                    count += (root->left != NULL ? root->left->children + root->left->num : 0);
                    cout << count << endl;
                    count = -1;
                    splay(this->root, root->data);
                }
                else {
                    find(root->left, x);
                }
            }
        }
    }

    void xthSmallest(Node*& root, int x) {
        if (count >= 0) {
            if (root != NULL) {
                if (count + (root->left != NULL ? root->left->children + root->left->num : 0) + 1 <= x &&
                    count + (root->left != NULL ? root->left->children + root->left->num : 0) + root->num >= x) {
                    cout << root->data << endl;
                    count = -1;
                    splay(this->root, root->data);
                }
                else if (count + (root->left != NULL ? root->left->children + root->left->num : 0) + 1 < x) {
                    count += ((root->left != NULL ? root->left->children + root->left->num : 0) + root->num);
                    xthSmallest(root->right, x);
                }
                else xthSmallest(root->left, x);
            }
        }
    }

    void prc(Node* root, Node*& precursor, int data) {
        if (root == NULL)
            return;

        if (root->data == data) {
            if (root->left != NULL) {
                Node* t = root->left;
                while (t->right != NULL)
                    t = t->right;
                precursor = t;
            }
        }

        else if (root->data > data)
            prc(root->left, precursor, data);

        else {
            precursor = root;
            prc(root->right, precursor, data);
        }
    }

    void scs(Node* root, Node*& successor, int data) {
        if (root == NULL)
            return;

        if (root->data == data) {
            if (root->right != NULL) {
                Node* t = root->right;
                while (t->left != NULL)
                    t = t->left;
                successor = t;
            }
        }
        else if (root->data > data) {
            successor = root;
            scs(root->left, successor, data);
        }

        else {
            scs(root->right, successor, data);
        }
    }

};

int main() {
    Splay a;
    int n, x;
    int opt;
    cin >> n;
    while (n--) {
        cin >> opt;
        cin >> x;
        if (opt == 1) {
            a.insert(a.root, x);
        }
        else if (opt == 2) {
            a.erase(a.root, x);
        }
        else if (opt == 3) {
            a.count = 1;
            a.find(a.root, x);
        }
        else if (opt == 4) {
            a.count = 0;
            a.xthSmallest(a.root, x);
        }
        else if (opt == 5) {
            Node* pre = new Node(-1);
            a.prc(a.root, pre, x);
            cout << pre->data << endl;
            a.splay(a.root, pre->data);
        }
        else if (opt == 6) {
            Node* suc = new Node(-1);
            a.scs(a.root, suc, x);
            cout << suc->data << endl;
            a.splay(a.root, suc->data);
        }
    }
}