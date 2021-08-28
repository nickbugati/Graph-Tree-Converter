#include "AVLTree.h"

AVLTree::AVLTree() {
    root = nullptr;
    size = 0;
}

Node* AVLTree::search(int val1) {
    Node* root = this->root;

    while (root != nullptr) {
        if (val1 == root->val1) {
            return root;
        }
        else if (val1 >= root->val1) {
            root = root->right;
        }
        else {
            root = root->left;
        }
    }
    return nullptr;
}
Node* AVLTree::insert(Node* root, int val1, int val2, string name) {
    if (root == NULL) {
        size++;

        root = new Node;
        (root->namesAndVal2).push_back(make_pair(name, val2));
        root->val1 = val1;
        root->left = NULL;
        root->right = NULL;
        return root;
    }
    else if (val1 < root->val1) {
        root->left = insert(root->left, val1, val2, name);
    }
    else if (val1 > root->val1) {
        root->right = insert(root->right, val1, val2, name);
    }
    else {
        (root->namesAndVal2).push_back(make_pair(name, val2));
    }

    root = balance(root);
    return root;
}

Node* AVLTree::rrRotation(Node* parent) {
    Node* temp;
    temp = parent->right;
    parent->right = temp->left;
    temp->left = parent;
    return temp;
}


Node* AVLTree::llRotation(Node* parent) {
    Node* temp;
    temp = parent->left;
    parent->left = temp->right;
    temp->right = parent;
    return temp;
}


Node* AVLTree::lrRotation(Node* parent) {
    Node* temp;
    temp = parent->left;
    parent->left = rrRotation(temp);
    return llRotation(parent);
}


Node* AVLTree::rlRotation(Node* parent) {
    Node* temp;
    temp = parent->right;
    parent->right = llRotation(temp);
    return rrRotation(parent);
}

Node* AVLTree::balance(Node* temp) {
    int iBalance = getHeight(temp->left) - getHeight(temp->right);

    if (iBalance > 1) {
        if (getHeight(temp->left->left) - getHeight(temp->left->right) > 0) {
            temp = llRotation(temp);
        }
        else {
            temp = lrRotation(temp);
        }
    }
    else if (iBalance < -1) {
        if (getHeight(temp->right->left) - getHeight(temp->right->right) > 0) {
            temp = rlRotation(temp);
        }
        else {
            temp = rrRotation(temp);
        }
    }

    return temp;
}

int AVLTree::getHeight(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    int hl = getHeight(node->left);
    int hr = getHeight(node->right);

    if (hl > hr) {
        return 1 + hl;
    }
    else {
        return 1 + hr;
    }
}

void AVLTree::printInorder(Node* root) {
    if (!root) {
        return;
    }
    else {
        printInorder(root->left);
        for (int i = 0; i < root->namesAndVal2.size(); i++) {
            cout << get<0>(root->namesAndVal2.at(i));
            if (i != root->namesAndVal2.size() - 1) {
                cout << ", ";
            }
        }
        cout << ": " << root->val1 << endl << endl;
        printInorder(root->right);
    }
}

void AVLTree::sortNodes(Node* root) {
    if (!root) {
        return;
    }
    else {
        sortNodes(root->left);
        std::sort(root->namesAndVal2.begin(), root->namesAndVal2.end(),
            [](const pair<string, int>& a, const pair<string, int>& b) -> bool
            {
                return a.second < b.second;
            });
        sortNodes(root->right);
    }
}

void AVLTree::kthSmallest(Node* root, Node* destination, int& temp2, bool& found) {
    if (root->left != nullptr) {
            kthSmallest(root->left, destination, temp2, found);
    }
    
    if (root == destination) {
        found = true;

        return;
    }
    else if (!found) {
        temp2++;
    }

    if (root->right != nullptr) {
        kthSmallest(root->right, destination, temp2, found);
    }
}

pair<string,int> AVLTree::findOptimal(int val1) {
    Node* node = search(val1);
    return (node->namesAndVal2.at(0));
}
