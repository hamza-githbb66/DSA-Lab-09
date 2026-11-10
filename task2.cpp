#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
using namespace std;

// BST Node
class Node {
public:
    string word;
    int frequency;

    Node* left;
    Node* right;

    Node(string w) {
        word = w;
        frequency = 1;

        left = right = NULL;
    }
};

// Insert word into BST
Node* insert(Node* root, string word) {

    if (root == NULL) {
        return new Node(word);
    }

    // If word already exists, increase frequency
    if (word == root->word) {
        root->frequency++;
    }

    // Smaller word goes to left
    else if (word < root->word) {
        root->left = insert(root->left, word);
    }

    // Greater word goes to right
    else {
        root->right = insert(root->right, word);
    }

    return root;
}

// Convert word into lowercase
string toLowerCase(string word) {

    transform(word.begin(), word.end(), word.begin(), ::tolower);

    return word;
}

// Display words in alphabetical order
void displayAlphabetical(Node* root) {

    if (root == NULL) {
        return;
    }

    displayAlphabetical(root->left);

    cout << root->word << " : "
         << root->frequency << endl;

    displayAlphabetical(root->right);
}

// Store all words and frequencies in vectors
void storeWords(Node* root, vector<string>& words,
                vector<int>& frequencies) {

    if (root == NULL) {
        return;
    }

    storeWords(root->left, words, frequencies);

    words.push_back(root->word);
    frequencies.push_back(root->frequency);

    storeWords(root->right, words, frequencies);
}

// Display words according to frequency (highest to lowest)
void displayByFrequency(Node* root) {

    vector<string> words;
    vector<int> frequencies;

    storeWords(root, words, frequencies);

    // Sort according to frequency
    for (int i = 0; i < frequencies.size(); i++) {

        for (int j = i + 1; j < frequencies.size(); j++) {

            if (frequencies[j] > frequencies[i]) {

                swap(frequencies[i], frequencies[j]);
                swap(words[i], words[j]);
            }
        }
    }

    cout << "Words sorted by frequency:" << endl;

    for (int i = 0; i < words.size(); i++) {

        cout << words[i] << " : "
             << frequencies[i] << endl;
    }
}

// Find the highest frequency
void findMostFrequentWord(Node* root) {

    vector<string> words;
    vector<int> frequencies;

    storeWords(root, words, frequencies);

    int maxFrequency = 0;

    // Find maximum frequency
    for (int i = 0; i < frequencies.size(); i++) {

        if (frequencies[i] > maxFrequency) {
            maxFrequency = frequencies[i];
        }
    }

    cout << "Most Frequent Word(s):" << endl;

    // Print all words having maximum frequency
    for (int i = 0; i < words.size(); i++) {

        if (frequencies[i] == maxFrequency) {

            cout << words[i] << " : "
                 << frequencies[i] << endl;
        }
    }
}

// Count unique words
int countUniqueWords(Node* root) {

    if (root == NULL) {
        return 0;
    }

    return 1 + countUniqueWords(root->left)
             + countUniqueWords(root->right);
}

// MAIN FUNCTION
int main() {

    string paragraph =
    "The quick brown fox jumps over the lazy dog. "
    "The fox is quick and smart.";

    Node* root = NULL;

    string word;
    string cleanedWord;

    int totalWords = 0;

    // Extract words from paragraph
    stringstream ss(paragraph);

    while (ss >> word) {

        // Remove punctuation from beginning and end
        cleanedWord = "";

        for (int i = 0; i < word.length(); i++) {

            if (isalpha(word[i])) {
                cleanedWord += word[i];
            }
        }

        // Convert to lowercase
        cleanedWord = toLowerCase(cleanedWord);

        if (cleanedWord != "") {

            root = insert(root, cleanedWord);

            totalWords++;
        }
    }

    // TASK 3: Display Operations

    cout << "Words in Alphabetical Order:" << endl;
    displayAlphabetical(root);

    cout << endl;

    displayByFrequency(root);

    cout << endl;

    findMostFrequentWord(root);

    // TASK 4: Summary Information

    cout << endl;

    cout << "Total Unique Words: "
         << countUniqueWords(root) << endl;

    cout << "Total Word Count: "
         << totalWords << endl;


    return 0;
}
