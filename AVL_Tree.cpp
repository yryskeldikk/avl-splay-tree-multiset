#include <iostream>

using namespace std;

class Node {
public:
    long long data;
    Node* left;
    Node* right;
    long long height;
    int num;
    int children;

    Node(int x) {
        data = x;
        height = 1;
        right = NULL;
        left = NULL;
        children = 0;
        num = 1;
    }
};


long long max(long long x, long long y) {
    if (x >= y)
        return x;
    return y;
}

class AVL {
public:

    AVL() {
        root = NULL;
    }
    int count;
    Node* root;

    long long height(Node* N) {
        if (N == NULL)
            return 0;
        else
            return N->height;
    }

    void rotateL(Node*& s) {
        Node* t = s->left;
        s->children = (s->right != NULL ? s->right->children + s->right->num : 0) + (t->right != NULL ? t->right->children + t->right->num : 0);
        t->children = s->children + s->num + (t->left != NULL ? t->left->children + t->left->num : 0);
        s->left = t->right;
        t->right = s;
        s->height = max(height(s->left), height(s->right)) + 1;
        t->height = max(height(t->left), height(t->right)) + 1;
        s = t;
    }

    void rotateR(Node*& s) {
        Node* t = s->right;
        s->children = (s->left != NULL ? s->left->children + s->left->num : 0) + (t->left != NULL ? t->left->children + t->left->num : 0);
        t->children = s->children + s->num + (t->right != NULL ? t->right->children + t->right->num : 0);
        s->right = t->left;
        t->left = s;
        s->height = max(height(s->left), height(s->right)) + 1;
        t->height = max(height(t->right), height(t->left)) + 1;
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

    int getBalanceNode(Node* N) {
        if (N == NULL)
            return 0;
        return height(N->left) - height(N->right);
    }

    void insert(Node*& N, long long data) {
        if (N == NULL)
            N = new Node(data);
        else if (data < N->data) {
            N->children++;
            insert(N->left, data);
            int b = getBalanceNode(N);

            if (b > 1 && data < N->left->data)
                rotateL(N);

            else if (b > 1 && data > N->left->data)
            {
                dbl_rotateL(N);
            }
        }
        else if (data > N->data) {
            N->children++;
            insert(N->right, data);
            int b = getBalanceNode(N);
            if (b < -1 && data > N->right->data)
                rotateR(N);

            else if (b < -1 && data < N->right->data)
            {
                dbl_rotateR(N);
            }
        }
        else
            N->num++;

        N->height = 1 + max(height(N->left), height(N->right));
    }

    Node* minNode(Node* N) {
        Node* t = N;
        while (t->left != NULL)
            t = t->left;
        return t;
    }

    void erase(Node*& root, long long data) {
        if (root == NULL)
            return;
        if (data < root->data)
            erase(root->left, data);
        else if (data > root->data)
            erase(root->right, data);
        else {
            if (root->num == 1) {
                if ((root->left == NULL) || (root->right == NULL)) {
                    Node* t;
                    if (root->left != NULL)
                        t = root->left;
                    else
                        t = root->right;


                    if (t == NULL) {
                        t = root;
                        root = NULL;
                    }
                    else {
                        *root = *t;
                    }
                    delete t;
                }
                else {
                    Node* t = minNode(root->right);
                    root->data = t->data;
                    root->num = t->num;
                    t->num = 1;
                    erase(root->right, t->data);
                }
            }
            else {
                root->num--;
            }
        }
        if (root == NULL)
            return;

        root->height = 1 + max(height(root->left), height(root->right));
        root->children = (root->left != NULL ? root->left->children + root->left->num : 0) +
            (root->right != NULL ? root->right->children + root->right->num : 0);

        int b = getBalanceNode(root);
        if (b > 1 && getBalanceNode(root->left) >= 0)
            rotateL(root);

        if (b > 1 && getBalanceNode(root->left) < 0)
            dbl_rotateL(root);

        if (b < -1 && getBalanceNode(root->right) <= 0)
            rotateR(root);

        if (b < -1 && getBalanceNode(root->right) > 0)
            dbl_rotateR(root);
    }

    void find(Node* root, long long& x) {
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
                }
                else {
                    find(root->left, x);
                }
            }
        }
    }

    void xthSmallest(Node*& root, long long x) {
        if (count >= 0) {
            if (root != NULL) {
                if (count + (root->left != NULL ? root->left->children + root->left->num : 0) + 1 <= x &&
                    count + (root->left != NULL ? root->left->children + root->left->num : 0) + root->num >= x) {
                    cout << root->data << endl;
                    count = -1;
                }
                else if (count + (root->left != NULL ? root->left->children + root->left->num : 0) + 1 < x) {
                    count += ((root->left != NULL ? root->left->children + root->left->num : 0) + root->num);
                    xthSmallest(root->right, x);
                }
                else xthSmallest(root->left, x);
            }
        }
    }

    void prc(Node* root, Node*& precursor, long long data) {
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

    void scs(Node* root, Node*& successor, long long data) {
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
    AVL a;
    long long n, x;
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
        }
        else if (opt == 6) {
            Node* suc = new Node(-1);
            a.scs(a.root, suc, x);
            cout << suc->data << endl;
        }
    }
}