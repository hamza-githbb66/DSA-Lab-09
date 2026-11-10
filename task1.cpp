#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = right = NULL;
    }
};

// Insert a new node in BST
Node* insert(Node* root, int val) {
    if (root == NULL) {
        return new Node(val);
    }

    if (val < root->data) {
        root->left = insert(root->left, val);
    } else {
        root->right = insert(root->right, val);
    }

    return root;
}

// Build BST using given array
Node* buildBST(int arr[], int n) {
    Node* root = NULL;

    for (int i = 0; i < n; i++) {
        root = insert(root, arr[i]);
    }

    return root;
}

// Inorder traversal (Left, Root, Right)
void inOrder(Node* root) {
    if (root == NULL) {
        return;
    }

    inOrder(root->left);
    cout << root->data << " ";
    inOrder(root->right);
}

// Find the rightmost node in left subtree
Node* rightMostInLeftSubTree(Node* root) {
    Node* ans = root;

    while (root != NULL) {
        ans = root;
        root = root->right;
    }

    return ans;
}

// Find the leftmost node in right subtree
Node* leftMostInRightSubTree(Node* root) {
    Node* ans = root;

    while (root != NULL) {
        ans = root;
        root = root->left;
    }

    return ans;
}

// Find inorder predecessor and successor
vector<int> getPredSucc(Node* root, int key) {
    Node* curr = root;
    Node* pred = NULL;
    Node* succ = NULL;

    while (curr != NULL) {
        if (key < curr->data) {
            succ = curr;
            curr = curr->left;
        }

        else if (key > curr->data) {
            pred = curr;
            curr = curr->right;
        } else {

            if (curr->left != NULL) {
                // Inorder predecessor
                pred = rightMostInLeftSubTree(curr->left);
            }

            if (curr->right != NULL) {
                // Inorder successor
                succ = leftMostInRightSubTree(curr->right);
            }

            break;
        }
    }

    vector<int> result;

    if (pred != NULL)
        result.push_back(pred->data);
    else
        result.push_back(-1);

    if (succ != NULL)
        result.push_back(succ->data);
    else
        result.push_back(-1);

    return result;
}


// TASK 3: Recursive Range Query

int recursiveComparisons = 0;

void rangeQueryRecursive(Node* root, int low, int high) {

    if (root == NULL) {
        return;
    }

    // Check left subtree
    recursiveComparisons++;

    if (root->data > low) {
        rangeQueryRecursive(root->left, low, high);
    }

    // Check if current node is within range
    recursiveComparisons++;

    if (root->data >= low && root->data <= high) {
        cout << root->data << " ";
    }

    // Check right subtree
    recursiveComparisons++;

    if (root->data < high) {
        rangeQueryRecursive(root->right, low, high);
    }
}


// TASK 4: Iterative Range Query

int iterativeComparisons = 0;

void rangeQueryIterative(Node* root, int low, int high) {

    stack<Node*> st;
    Node* curr = root;

    while (curr != NULL || !st.empty()) {

        // Go towards the left subtree
        while (curr != NULL) {

            iterativeComparisons++;

            if (curr->data >= low) {
                st.push(curr);
                curr = curr->left;
            }
            else {
                // Skip left subtree
                curr = curr->right;
            }
        }

        if (!st.empty()) {

            curr = st.top();
            st.pop();

            // Check if current node is within range
            iterativeComparisons++;

            if (curr->data >= low && curr->data <= high) {
                cout << curr->data << " ";
            }

            // Check right subtree
            iterativeComparisons++;

            if (curr->data < high) {
                curr = curr->right;
            }
            else {
                curr = NULL;
            }
        }
    }
}


// MAIN FUNCTION

int main() {

    int arr[11] = {50, 30, 70, 20, 40, 60, 80, 35, 45, 65, 85};

    // Build BST
    Node* root = buildBST(arr, 11);


    // TASK 1: Inorder Traversal

    cout << "Inorder Traversal: ";
    inOrder(root);
    cout << endl;


    // TASK 2: Predecessor and Successor

    int key = 40;

    vector<int> ans = getPredSucc(root, key);

    cout << "\nPredecessor: " << ans[0] << endl;
    cout << "Successor: " << ans[1] << endl;


    // TASK 3: Range Query

    int low = 30;
    int high = 70;

    cout << "\nRecursive Range Query: ";
    rangeQueryRecursive(root, low, high);
    cout << endl;

    cout << "Iterative Range Query: ";
    rangeQueryIterative(root, low, high);
    cout << endl;


    // TASK 4: Comparison Analysis

    cout << "\nComparison Analysis:" << endl;

    cout << "Recursive Comparisons: "
         << recursiveComparisons << endl;

    cout << "Iterative Comparisons: "
         << iterativeComparisons << endl;


    return 0;
}
